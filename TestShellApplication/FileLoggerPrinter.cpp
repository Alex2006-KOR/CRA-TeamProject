#include "FileLoggerPrinter.h"

#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <regex>


FileLoggerPrinter::FileLoggerPrinter(string rootPath)
	: m_strRootPath(rootPath)
{
    _createRootDirectory();
}

void FileLoggerPrinter::Print(string strMessage, string strCallerName)
{
    string formatMessage = _makeFormatMessage(strCallerName, strMessage);

    std::ofstream ofs(m_strRootPath + LOG_FILE_NAME, std::ios::app);
    if (ofs.is_open() == false) {
        throw std::exception("Failed to open log file.");
    }
    ofs << formatMessage << std::endl;
    ofs.close();

    _splitLogFileOnSize();
}

void FileLoggerPrinter::_createRootDirectory()
{
    CreateDirectoryA(m_strRootPath.c_str(), nullptr);
}

string FileLoggerPrinter::_makeFormatMessage(const string& strCallerName, const string& msg)
{
    return _getDateString() + " " + _getFormatMessage(strCallerName, msg);
}

string FileLoggerPrinter::_getDateString()
{
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    errno_t err = localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "[%y.%m.%d %H:%M]");

    return oss.str();
}

string FileLoggerPrinter::_getFormatMessage(string strCallerName, const string& msg)
{
    constexpr int FORMAT_MESAGE_SIZE = 30;

    std::ostringstream ossMessage;
    strCallerName += "()";
    ossMessage << std::setw(FORMAT_MESAGE_SIZE) << std::left << strCallerName;
    ossMessage << ": " << msg;

    return ossMessage.str();
}

void FileLoggerPrinter::_splitLogFileOnSize()
{
    if (_isNeedToSplitLogFile() == false) {
        return;
    }
    _createBackupLogFile();
    _checkAndCompressOldBackupLogFiles();
}

bool FileLoggerPrinter::_isNeedToSplitLogFile()
{
    constexpr int MAX_LOG_FILE_SIZE = 10 * 1024;

    long long llFileSize = _getLogFileSize();
    if (llFileSize > MAX_LOG_FILE_SIZE) {
        return true;
    }
    return false;
}

void FileLoggerPrinter::_createBackupLogFile()
{
    string logFilePath = m_strRootPath + LOG_FILE_NAME;
    m_strBackupLogFileName = _getNewBackupLogFileName();
    string strBackupLogFilePath = m_strRootPath + m_strBackupLogFileName;
    if (MoveFileA(logFilePath.c_str(), strBackupLogFilePath.c_str()) == FALSE) {
        throw std::exception("Failed to make backup log file");
    }
}

long long FileLoggerPrinter::_getLogFileSize()
{
    string logFilePath = m_strRootPath + LOG_FILE_NAME;
    std::ifstream file(logFilePath.c_str(), std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::exception("Failed to open log file.");
    }
    return file.tellg();
}

string FileLoggerPrinter::_getNewBackupLogFileName()
{
    const string LOG_FILE_NAME_FORMAT = "until_%y%m%d_%Hh_%Mm_%Ss.log";

    std::time_t now = std::time(nullptr);
    std::tm localTime;
    errno_t err = localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, LOG_FILE_NAME_FORMAT.c_str());

    return oss.str();
}

void FileLoggerPrinter::_checkAndCompressOldBackupLogFiles()
{
    vector<string> vOldLogFiles = _getOldBackupLogFiles();
    for (string oldLogFile : vOldLogFiles) {
        _compressLogFile(oldLogFile);
    }
}

vector<string> FileLoggerPrinter::_getOldBackupLogFiles() {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((m_strRootPath + "*.log").c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return vector<string>();
    }

    vector<string> vFileList;
    std::regex regexFilter("until_\\d{6}_\\d{2}h_\\d{2}m_\\d{2}s\\.log");
    do {
        std::string strFileName = findData.cFileName;
        if (std::regex_match(strFileName, regexFilter)) {
            if (strFileName == m_strBackupLogFileName) continue;
            vFileList.push_back(strFileName);
        }
    } while (FindNextFileA(hFind, &findData) != 0);
    FindClose(hFind);

    return vFileList;
}

void FileLoggerPrinter::_compressLogFile(const string& strFileName)
{
    auto nPos = strFileName.find_last_of('.');
    string strCompressedFilePath = m_strRootPath + strFileName.substr(0, nPos) + ".zip";
 
    string originFilePath = m_strRootPath + strFileName;
    if (MoveFileA(originFilePath.c_str(), strCompressedFilePath.c_str()) == FALSE) {
        throw std::exception("Failed to compress old backup log file");
    }
}