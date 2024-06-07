#pragma once

#include <string>
using std::string;

class Logger
{
public:
	Logger() = default;
	virtual ~Logger() = default;

public:
	void Print(string strMessage, string strCallerName);

private:
	void _printMessageToConsole(const string& strMessage);
	void _printMessageToLogFile(const string& strMessage, const string& strCallerName);
	string _makeFormatMessage(const string& strCallerName, const string& msg);
	string _getDateString();
	string _getFormatMessage(string strCallerName, const string& msg);
};
