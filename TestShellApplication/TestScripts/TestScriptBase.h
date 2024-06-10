#pragma once
#include "../Device.h"
#include "../TestLibraryCommandInvokerInterface.h"
#include "TestScriptInterface.h"

class TestScriptBase
	: public TestScriptInterface
{
public:
	TestScriptBase(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker);
	void Run() override;

protected:
	virtual void _setup() = 0;
	virtual void _main() = 0;
	virtual void _cleanup() = 0;

	TestLibCommandInvokerdInterface* m_pstTestLibCommandInvoker;
};