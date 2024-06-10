#pragma once
#include "TestApp1.h"
#include "TestApp2.h"
#include <map>

class TestScriptInvoker {
public:
	TestScriptInvoker(TestLibCommandInvoker* pstTestLibCommandInvoker);
	TestScriptBase* GetTestScript(string strCommand);
	void Run(TestScriptBase* stFunction);

private:
	std::map<string, TestScriptBase*> m_mapCommand;

	void _initCommands(TestLibCommandInvoker* pstTestLibCommandInvoker);
};