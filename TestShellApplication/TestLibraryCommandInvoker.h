#pragma once
#include "TestLibrary.h"
#include <map>

class TestLibCommandInvoker {
public:
	TestLibCommandInvoker(DriverInterface* pstDriver);
	TestLibrary* GetFunction(string strCommand);
	void Run(TestLibrary* stFunction, const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "");

private:
	std::map<string, TestLibrary*> m_mapCommand;

	void _initCommands(Device* pstDevice);
};