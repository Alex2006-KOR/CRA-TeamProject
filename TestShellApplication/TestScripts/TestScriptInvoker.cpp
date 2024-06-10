#include "TestScriptInvoker.h"

TestScriptInvoker::TestScriptInvoker(TestLibCommandInvoker* pstTestLibCommandInvoker, ostream* output)
{
	_initCommands(pstTestLibCommandInvoker, output);
}

TestScriptBase* TestScriptInvoker::GetTestScript(string strCommand)
{
	auto iterFind = m_mapCommand.find(strCommand);
	if (iterFind == m_mapCommand.end()) {
		return nullptr;
	}
	return iterFind->second;
}

void TestScriptInvoker::Run(TestScriptBase* stFunction)
{
	stFunction->Run();
}

void TestScriptInvoker::_initCommands(TestLibCommandInvoker* pstTestLibCommandInvoker, ostream* output)
{
	m_mapCommand["testapp1"] = new TestApp1(pstTestLibCommandInvoker, *output);
	m_mapCommand["testapp2"] = new TestApp2(pstTestLibCommandInvoker, *output);
}
