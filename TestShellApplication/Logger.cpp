#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <regex>


void Logger::Print(string strMessage, string strCallerName)
{
    _printMessageToConsole(strMessage);
    _printMessageToLogFile(strMessage, strCallerName);
}

void Logger::_printMessageToConsole(const string& strMessage)
{
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

    long long llFileSize = _getLogFileSize();
    if (llFileSize > 10 * 1024) {
        string strNewFileName;
        std::time_t now = std::time(nullptr);
        std::tm localTime;
        errno_t err = localtime_s(&localTime, &now);
        std::ostringstream oss;
        oss << std::put_time(&localTime, "until_%y%m%d_%Hh_%Mm_%Ss.log");
        strNewFileName = oss.str();

        if (MoveFileA(LOG_FILE_NAME.c_str(), strNewFileName.c_str()) == FALSE) {
            throw std::exception("Failed to make old log file");
        }

        vector<string> vOldLogFiles = _getOldLogFiles(strNewFileName);
        for (string oldLogFile : vOldLogFiles) {
            _compressLogFile(oldLogFile);
        }
    }
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

long long Logger::_getLogFileSize()
{
    std::ifstream file(LOG_FILE_NAME, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::exception("Failed to open log file.");
    }
    return file.tellg();
}

vector<string> Logger::_getOldLogFiles(const string& strNewFileName) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(".\\*.log", &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return vector<string>();
    }

    vector<string> fileList;
    std::regex regexFilter("until_\\d{6}_\\d{2}h_\\d{2}m_\\d{2}s\\.log");
    do {
        std::string strFileName = findData.cFileName;
        if (std::regex_match(strFileName, regexFilter)) {
            if (strFileName == strNewFileName) continue;
            fileList.push_back(strFileName);
        }
    } while (FindNextFileA(hFind, &findData) != 0);
    FindClose(hFind);

    return fileList;
}

void Logger::_compressLogFile(const string& strFileName)
{
    auto nPos = strFileName.find_last_of('.');
    string strCompressedName = strFileName.substr(0, nPos) + ".zip";

    if (MoveFileA(strFileName.c_str(), strCompressedName.c_str()) == FALSE) {
        throw std::exception("Failed to compress old log file");
    }
}
