#pragma once
#include "TestScriptBase.h"

class FailTestApp : public TestScriptBase {
public:
	FailTestApp(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker);

	void _setup() override;
	void _main() override;
	void _cleanup() override;

private:
	string m_Data;
};