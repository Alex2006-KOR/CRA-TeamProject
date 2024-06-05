#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class TestApp2Command
	: public BaseSSDCommand
{
public:
	TestApp2Command(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;
	void _agingWrite(int expected);
	void _agingWriteCheck(int expected);

private:
	DriverInterface* m_pstSSDDriver;
};