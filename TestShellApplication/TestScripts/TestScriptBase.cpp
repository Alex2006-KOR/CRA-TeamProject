#include "TestScriptBase.h"

TestScriptBase::TestScriptBase(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker, string name)
	: m_pstTestLibCommandInvoker(pstTestLibCommandInvoker), m_name(name), m_verdict(true)
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

string TestScriptBase::Name()
{
	return m_name;
}

bool TestScriptBase::Verdict()
{
	return m_verdict;
}