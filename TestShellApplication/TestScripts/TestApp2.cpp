#include "TestApp2.h"

TestApp2::TestApp2(DriverInterface* pstDriver)
	: TestScriptBase(pstDriver)
{
}

void TestApp2::_setup()
{
	m_pstTestLib = TestLibrary::GetLibrary();
	m_strDataPrev = "0xA5A5A5A5";
	m_strDataNew = "0xFFFF0000";
}

void TestApp2::_main()
{
	for (int cnt = 0; cnt < AGING_CNT; cnt++) {
		m_pstTestLib->WriteRange(0, 5, m_strDataPrev);
	}

	m_pstTestLib->WriteRange(0, 5, m_strDataNew);

	m_pstTestLib->ReadRange(0, 5, m_strDataNew);
}

void TestApp2::_cleanup()
{
}
