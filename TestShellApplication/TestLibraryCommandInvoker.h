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

private:
	std::map<string, TestLibrary*> m_mapCommand;

	void _initCommands(DriverInterface* pstDriver);
};