#include "Logger.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>


void Logger::print(string msg, string strCallerName)
{
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    errno_t err = localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "[%y.%m.%d %H:%M]");
    string strDate = oss.str();

    std::ostringstream ossMessage;
    strCallerName += "()";
    ossMessage << std::setw(30) << std::left << strCallerName;
    ossMessage << ": " << msg;
    string strMessage = ossMessage.str();

    string strTotalMessage = strDate + " " + strMessage;

    std::cout << strTotalMessage << std::endl;
    std::ofstream ofs(".\\latest.log", std::ios::app);
    if (ofs.is_open() == false) {
        throw std::exception("Failed to open log file.");
    }
    ofs << strTotalMessage << std::endl;
    ofs.close();
}
