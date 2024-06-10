#include "TestScriptBase.h"

TestScriptBase::TestScriptBase(DriverInterface* pstDriver)
	: m_pstTestLib(nullptr)
{
	m_pstDevice = new Device(pstDriver);
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
