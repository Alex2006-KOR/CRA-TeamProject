#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>


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
    const string LOG_FILE_NAME = "latest.log";

    string formatMessage = _makeFormatMessage(strCallerName, strMessage);

    std::ofstream ofs(".\\" + LOG_FILE_NAME, std::ios::app);
    if (ofs.is_open() == false) {
        throw std::exception("Failed to open log file.");
    }
    ofs << formatMessage << std::endl;
    ofs.close();
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
