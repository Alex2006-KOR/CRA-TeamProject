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
    : m_fileLoggerPrinter{".\\log\\"}
{
    AddLoggerPrinter(&m_outStreamLoggerPrinter);
    AddLoggerPrinter(&m_fileLoggerPrinter);
}

void Logger::Print(string strMessage, string strCallerName)
{
    for (const auto printer : m_vLoggerPrinters) {
        printer->Print(strMessage, strCallerName);
    }
}

void Logger::EnableConsoleLog(bool b)
{
    m_outStreamLoggerPrinter.Enable(b);
}

void Logger::SetOutStream(std::ostream& os)
{
    m_outStreamLoggerPrinter.SetOutStream(os);
}

void Logger::AddLoggerPrinter(LoggerPrinter* p)
{
    auto iterFind = std::find(m_vLoggerPrinters.begin(), m_vLoggerPrinters.end(), p);
    if (iterFind != m_vLoggerPrinters.end()) return;
    
    m_vLoggerPrinters.push_back(p);
}

void Logger::RemoveLoggerPrinter(LoggerPrinter* p)
{
    auto iterFind = std::find(m_vLoggerPrinters.begin(), m_vLoggerPrinters.end(), p);
    if (iterFind == m_vLoggerPrinters.end()) return;

    m_vLoggerPrinters.erase(iterFind);
}
