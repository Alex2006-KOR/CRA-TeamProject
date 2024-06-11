#pragma once
#include "TestScriptBase.h"

class TestApp2 : public TestScriptBase {
public:
	TestApp2(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker);

	void _setup() override;
	void _main() override;
	void _cleanup() override;

private:
	string m_strDataPrev;
	string m_strDataNew;
	const int AGING_CNT = 30;
};