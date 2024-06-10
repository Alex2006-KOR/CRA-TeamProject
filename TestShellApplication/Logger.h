#pragma once
#include "LoggerPrinter.h"
#include "OutstreamLoggerPrinter.h"
#include "FileLoggerPrinter.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

#define LOG(msg) Logger::getInstance().Print(msg, __FUNCTION__);


class Logger
{
public:
	static Logger& getInstance();

private:
	Logger();
	virtual ~Logger() = default;

public:
	void Print(string strMessage, string strCallerName);
	void EnableConsoleLog(bool b);
	void SetOutStream(std::ostream& os);

	void AddLoggerPrinter(LoggerPrinter* p);
	void RemoveLoggerPrinter(LoggerPrinter* p);

private:
	vector<LoggerPrinter*> m_vLoggerPrinters;
	OutstreamLoggerPrinter m_outStreamLoggerPrinter;
	FileLoggerPrinter m_fileLoggerPrinter;
};
