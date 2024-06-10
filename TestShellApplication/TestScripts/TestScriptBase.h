#pragma once
#include "../Device.h"
#include "../TestLibraryCommandInvoker.h"

class TestScriptBase{
public:
	TestScriptBase(TestLibCommandInvoker* pstTestLibCommandInvoker, ostream& output);
	void Run();

protected:
	virtual void _setup() = 0;
	virtual void _main() = 0;
	virtual void _cleanup() = 0;

	TestLibCommandInvoker* m_pstTestLibCommandInvoker;
	ostream& m_out;
};