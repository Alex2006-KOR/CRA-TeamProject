#pragma once
#include "TestScriptBase.h"

class TestApp1 : public TestScriptBase {
public:
	TestApp1(DriverInterface* pstDriver);
	void _setup() override;
	void _main() override;
	void _cleanup() override;

private:
	string m_Data;
};