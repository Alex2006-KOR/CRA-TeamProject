#pragma once
#include "../Device.h"
#include "../TestLibraryCommandInvokerInterface.h"
#include "TestScriptInterface.h"

class TestScriptBase
	: public TestScriptInterface
{
public:
	TestScriptBase(TestLibCommandInvokerdInterface* pstTestLibCommandInvoker, string name);
	void Run();

protected:
	virtual void _setup() = 0;
	virtual void _main() = 0;
	virtual void _cleanup() = 0;

	string Name() override;
	virtual bool Verdict() override;

	TestLibCommandInvokerdInterface* m_pstTestLibCommandInvoker;
	string m_name;
	bool m_verdict;
};