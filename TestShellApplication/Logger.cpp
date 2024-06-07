#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
#include <windows.h>


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
