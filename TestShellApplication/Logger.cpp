#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <regex>


Logger& Logger::getInstance()
{
    static Logger inst;
    return inst;
}

Logger::Logger()
	: m_os{ std::cout }
{
}

void Logger::Print(string strMessage, string strCallerName)
{
    _printMessageToConsole(strMessage);
    _printMessageToLogFile(strMessage, strCallerName);
}

void Logger::_printMessageToConsole(const string& strMessage)
{
    if(m_bEnableConsoleLog)
        std::cout << strMessage << std::endl;
}

void Logger::_printMessageToLogFile(const string& strMessage, const string& strCallerName)
{
    string formatMessage = _makeFormatMessage(strCallerName, strMessage);

    std::ofstream ofs(".\\" + LOG_FILE_NAME, std::ios::app);
    if (ofs.is_open() == false) {
        throw std::exception("Failed to open log file.");
    }
    ofs << formatMessage << std::endl;
    ofs.close();

    _splitLogFileOnSize();
}

void Logger::SetOutStream(std::ostream& os)
{
    m_os.rdbuf(os.rdbuf());
}

string Logger::_makeFormatMessage(const string& strCallerName, const string& msg)
{
    return _getDateString() + " " + _getFormatMessage(strCallerName, msg);
}

string Logger::_getDateString()
{
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    errno_t err = localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "[%y.%m.%d %H:%M]");

    return oss.str();
}

string Logger::_getFormatMessage(string strCallerName, const string& msg)
{
    constexpr int FORMAT_MESAGE_SIZE = 30;

    std::ostringstream ossMessage;
    strCallerName += "()";
    ossMessage << std::setw(FORMAT_MESAGE_SIZE) << std::left << strCallerName;
    ossMessage << ": " << msg;

    return ossMessage.str();
}

void Logger::_splitLogFileOnSize()
{
    if (_isNeedToSplitLogFile() == false) {
        return;
	}

    string strBackupLogFileName = _getNewBackupLogFileName();
	if (MoveFileA(LOG_FILE_NAME.c_str(), strBackupLogFileName.c_str()) == FALSE) {
		throw std::exception("Failed to make old log file");
	}

    _checkAndCompressOldLogFiles(strBackupLogFileName);
}

bool Logger::_isNeedToSplitLogFile()
{
    constexpr int MAX_LOG_FILE_SIZE = 10 * 1024;

    long long llFileSize = _getLogFileSize();
    if (llFileSize > MAX_LOG_FILE_SIZE) {
        return true;
    }
    return false;
}

long long Logger::_getLogFileSize()
{
    std::ifstream file(LOG_FILE_NAME, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::exception("Failed to open log file.");
    }
    return file.tellg();
}

string Logger::_getNewBackupLogFileName()
{
    const string LOG_FILE_NAME_FORMAT = "until_%y%m%d_%Hh_%Mm_%Ss.log";

    std::time_t now = std::time(nullptr);
    std::tm localTime;
    errno_t err = localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, LOG_FILE_NAME_FORMAT.c_str());
 
    return oss.str();
}

void Logger::_checkAndCompressOldLogFiles(const string& strNewFileName)
{
    vector<string> vOldLogFiles = _getOldLogFiles(strNewFileName);
    for (string oldLogFile : vOldLogFiles) {
        _compressLogFile(oldLogFile);
    }
}

vector<string> Logger::_getOldLogFiles(const string& strNewFileName) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(".\\*.log", &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return vector<string>();
    }

    vector<string> vFileList;
    std::regex regexFilter("until_\\d{6}_\\d{2}h_\\d{2}m_\\d{2}s\\.log");
    do {
        std::string strFileName = findData.cFileName;
        if (std::regex_match(strFileName, regexFilter)) {
            if (strFileName == strNewFileName) continue;
            vFileList.push_back(strFileName);
        }
    } while (FindNextFileA(hFind, &findData) != 0);
    FindClose(hFind);

    return vFileList;
}

void Logger::_compressLogFile(const string& strFileName)
{
    auto nPos = strFileName.find_last_of('.');
    string strCompressedName = strFileName.substr(0, nPos) + ".zip";

    if (MoveFileA(strFileName.c_str(), strCompressedName.c_str()) == FALSE) {
        throw std::exception("Failed to compress old log file");
    }
}
