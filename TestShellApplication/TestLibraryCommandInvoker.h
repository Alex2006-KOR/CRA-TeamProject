#pragma once
#include "TestLibrary.h"
#include "TestLibraryCommandInvokerInterface.h"
#include <map>

class TestLibCommandInvoker
	: public TestLibCommandInvokerdInterface
{
public:
	TestLibCommandInvoker(DriverInterface* pstDriver);
	
	TestLibrary* GetFunction(string strCommand) override;
	void Run(TestLibrary* stFunction, const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") override;

private:
	std::map<string, TestLibrary*> m_mapCommand;

	void _initCommands(Device* pstDevice);
};