#include "TestApp2.h"

TestApp2::TestApp2(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker)
	: TestScriptBase(pstTestLibCommandInvoker, "testapp2")
{
}

void TestApp2::_setup()
{
	m_strDataPrev = "0xA5A5A5A5";
	m_strDataNew = "0xFFFF0000";
}

void TestApp2::_main()
{
	for (int cnt = 0; cnt < AGING_CNT; cnt++) {
		m_verdict &= m_pstTestLibCommandInvoker->GetFunction("write_range")
			->setStartLba(0)
			.setEndLba(5)
			.setData(m_strDataPrev)
			.execute();
	}

	m_verdict &= m_pstTestLibCommandInvoker->GetFunction("write_range")
		->setStartLba(0)
		.setEndLba(5)
		.setData(m_strDataNew)
		.execute();

	m_verdict &= m_pstTestLibCommandInvoker->GetFunction("read_range")
		->setStartLba(0)
		.setEndLba(5)
		.setData(m_strDataNew)
		.execute();
}

void TestApp2::_cleanup()
{
}
