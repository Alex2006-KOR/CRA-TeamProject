#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class FullWriteCommand
	: public BaseSSDCommand
{
public:
	FullWriteCommand(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;

private:
	DriverInterface* m_pstSSDDriver;

	string m_sData;
};
