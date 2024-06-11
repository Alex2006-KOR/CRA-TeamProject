#include "FailTestApp.h"

FailTestApp::FailTestApp(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker)
	: TestScriptBase(pstTestLibCommandInvoker, "failtestapp")
{
}

void FailTestApp::_setup()
{
	m_Data = "0xKKKKKKKK";	// Invalid Character
}

void FailTestApp::_main()
{
	m_verdict &= m_pstTestLibCommandInvoker->GetFunction("fullwrite")
		->setCommandList({ m_Data })
		.execute();
}

void FailTestApp::_cleanup()
{
}
