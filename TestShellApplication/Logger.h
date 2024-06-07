#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

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
	void _splitLogFileOnSize();
	bool _isNeedToSplitLogFile();
	long long _getLogFileSize();
	string _getNewBackupLogFileName();
	void _checkAndCompressOldLogFiles(const string& strNewFileName);
	vector<string> _getOldLogFiles(const string& strNewFileName);
	void _compressLogFile(const string& strFileName);

private:
	const string LOG_FILE_NAME = "latest.log";
};
