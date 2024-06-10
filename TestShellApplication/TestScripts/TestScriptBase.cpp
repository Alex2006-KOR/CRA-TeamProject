#include "TestScriptBase.h"

TestScriptBase::TestScriptBase(TestLibCommandInvoker* pstTestLibCommandInvoker)
	: m_pstTestLibCommandInvoker(pstTestLibCommandInvoker)
{
}

void TestScriptBase::Run()
{
	try {
		_setup();
		_main();
		_cleanup();
	}
	catch (exception e) {
	}
}
