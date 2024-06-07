#pragma once

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
	inline void EnableConsoleLog(bool b) { m_bEnableConsoleLog = b; }
	void SetOutStream(std::ostream& os);

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
	bool m_bEnableConsoleLog = true;
	std::ostream& m_os;
};
