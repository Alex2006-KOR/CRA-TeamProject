#include "TestScriptBase.h"

TestScriptBase::TestScriptBase(TestLibCommandInvoker* pstTestLibCommandInvoker, ostream& output)
	: m_pstTestLibCommandInvoker(pstTestLibCommandInvoker)
	, m_out(output)
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
