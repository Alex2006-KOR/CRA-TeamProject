#pragma once
#include "../TestLibraryCommandInvoker.h"
#include "TestScriptInterface.h"

#include <map>

class TestScriptInvoker {
public:
	TestScriptInvoker(TestLibCommandInvoker* pstTestLibCommandInvoker);
	TestScriptInterface* GetTestScript(string strCommand);
	bool Run(TestScriptInterface* stFunction, bool isScriptMode);

private:
	std::map<string, TestScriptInterface*> m_mapCommand;

	void _initCommands(TestLibCommandInvoker* pstTestLibCommandInvoker);
};
