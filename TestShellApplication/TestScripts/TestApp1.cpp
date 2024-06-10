#include "TestApp1.h"

TestApp1::TestApp1(DriverInterface* pstDriver)
	: TestScriptBase(pstDriver)
{
}

void TestApp1::_setup()
{
	m_pstTestLib = TestLibrary::GetLibrary();
	m_Data = "0xA5A5A5A5";
}

void TestApp1::_main()
{
	m_pstTestLib->FullWrite({ m_Data });
	m_pstTestLib->FullRead(m_Data);
}

void TestApp1::_cleanup()
{
}
