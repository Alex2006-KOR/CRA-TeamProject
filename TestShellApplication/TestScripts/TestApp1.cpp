#include "TestApp1.h"

TestApp1::TestApp1(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker)
	: TestScriptBase(pstTestLibCommandInvoker, "testapp1")
{
}

void TestApp1::_setup()
{
	m_Data = "0xA5A5A5A5";
}

void TestApp1::_main()
{
	m_verdict &= m_pstTestLibCommandInvoker->Run(
		m_pstTestLibCommandInvoker->GetFunction("fullwrite"),
		{ m_Data }
	);
	m_verdict &= m_pstTestLibCommandInvoker->Run(
		m_pstTestLibCommandInvoker->GetFunction("fullread"),
		{ m_Data }
	);
}

void TestApp1::_cleanup()
{
}
