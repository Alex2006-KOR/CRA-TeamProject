#include <Windows.h>

#include "TestScriptInvoker.h"


TestScriptInvoker::TestScriptInvoker(TestLibCommandInvoker* pstTestLibCommandInvoker)
{
	_initCommands(pstTestLibCommandInvoker);
}

TestScriptInterface* TestScriptInvoker::GetTestScript(string strCommand)
{
	auto iterFind = m_mapCommand.find(strCommand);
	if (iterFind == m_mapCommand.end()) {
		return nullptr;
	}
	return iterFind->second;
}

void TestScriptInvoker::Run(TestScriptInterface* stFunction)
{
	stFunction->Run();
}

void TestScriptInvoker::_initCommands(TestLibCommandInvoker* pstTestLibCommandInvoker)
{
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	string strPath = path;
	int nPos = strPath.find_last_of("\\");
	strPath = strPath.substr(0, nPos + 1);
	strPath += "TestScriptLib.dll";

	typedef void (*GetTestSciprtList)(TestLibCommandInvoker*, std::map<string, TestScriptInterface*>&);

	HMODULE hDLL = LoadLibraryA(strPath.c_str());
	if (hDLL == nullptr) {
		return;
	}

	GetTestSciprtList getTestScriptListFunc = (GetTestSciprtList)GetProcAddress(hDLL, "GetTestSciprtList");
	if (getTestScriptListFunc == NULL) {
		return;
	}

	getTestScriptListFunc(pstTestLibCommandInvoker, m_mapCommand);
}