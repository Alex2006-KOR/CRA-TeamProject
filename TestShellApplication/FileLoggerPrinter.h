#pragma once
#include "LoggerPrinter.h"

#include <vector>
using std::vector;

class FileLoggerPrinter :
    public LoggerPrinter
{
public:
    FileLoggerPrinter() = delete;
    FileLoggerPrinter(string strRootPath = ".\\");

public:
    void Print(string strMessage, string strCallerName) override;

private:
	void _createRootDirectory();
	string _makeFormatMessage(const string& strCallerName, const string& msg);
	string _getDateString();
	string _getFormatMessage(string strCallerName, const string& msg);
	void _splitLogFileOnSize();
	bool _isNeedToSplitLogFile();
	void _createBackupLogFile();
	long long _getLogFileSize();
	string _getNewBackupLogFileName();
	void _checkAndCompressOldBackupLogFiles();
	vector<string> _getOldBackupLogFiles();
	void _compressLogFile(const string& strFileName);


private:
    const string m_strRootPath;
    const string LOG_FILE_NAME = "latest.log";
	string m_strBackupLogFileName = "";
};

