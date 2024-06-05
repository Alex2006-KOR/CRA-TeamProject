#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class TestApp1Command
	: public BaseSSDCommand
{
public:
	TestApp1Command(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;
	void _fullWrite(int expected);
	void _fullWriteCheck(int expected);

private:
	DriverInterface* m_pstSSDDriver;
};