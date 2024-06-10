#include "TestApp1.h"

TestApp1::TestApp1(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker)
	: TestScriptBase(pstTestLibCommandInvoker)
{
}

void TestApp1::_setup()
{
	m_Data = "0xA5A5A5A5";
}

void TestApp1::_main()
{
	m_pstTestLibCommandInvoker->GetFunction("fullwrite")
		->setCommandList({ m_Data })
		.execute();

	m_pstTestLibCommandInvoker->GetFunction("fullread")
		->setCommandList({ m_Data })
		.execute();
}

void TestApp1::_cleanup()
{
}
