#pragma once
#include "../Device.h"
#include "../TestLibrary.h"

class TestScriptBase{
public:
	TestScriptBase(DriverInterface* pstDriver, ostream& output);
	void Run();

protected:
	virtual void _setup() = 0;
	virtual void _main() = 0;
	virtual void _cleanup() = 0;

	TestLibrary* m_pstTestLib;
	Device* m_pstDevice;
	ostream& m_out;
};