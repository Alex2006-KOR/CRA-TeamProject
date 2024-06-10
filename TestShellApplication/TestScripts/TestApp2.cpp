#include "TestApp2.h"

TestApp2::TestApp2(TestLibCommandInvoker* pstTestLibCommandInvoker, ostream& output)
	: TestScriptBase(pstTestLibCommandInvoker, output)
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
		m_pstTestLibCommandInvoker->Run(
			m_pstTestLibCommandInvoker->GetFunction("write_range"),
			{}, 0, 5, m_strDataPrev
		);
	}

	m_pstTestLibCommandInvoker->Run(
		m_pstTestLibCommandInvoker->GetFunction("write_range"),
		{}, 0, 5, m_strDataNew
	);

	m_pstTestLibCommandInvoker->Run(
		m_pstTestLibCommandInvoker->GetFunction("read_range"),
		{}, 0, 5, m_strDataNew
	);
}

void TestApp2::_cleanup()
{
}
