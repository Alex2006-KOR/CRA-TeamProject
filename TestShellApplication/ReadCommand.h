#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class ReadCommand
	: public BaseSSDCommand
{
public:
	ReadCommand(vector<string>commandList, DriverInterface* pSSDDriver, std::ostream& output);

protected:
	void _execute() override;
	void _parseCommand() override;

private:
	DriverInterface* m_pSSDDriver;
	std::ostream& m_out;

	int m_nLBA;
};
