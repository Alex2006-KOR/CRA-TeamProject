#pragma once
#include "../TestLibraryCommandInvoker.h"
#include "TestScriptInterface.h"

#include <map>

class TestScriptInvoker {
public:
	TestScriptInvoker(TestLibCommandInvoker* pstTestLibCommandInvoker);
	TestScriptInterface* GetTestScript(string strCommand);
	void Run(TestScriptInterface* stFunction);

private:
	std::map<string, TestScriptInterface*> m_mapCommand;

	void _initCommands(TestLibCommandInvoker* pstTestLibCommandInvoker);
};
