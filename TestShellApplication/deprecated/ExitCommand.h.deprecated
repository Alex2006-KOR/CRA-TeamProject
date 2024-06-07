#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class ExitCommand
	: public BaseSSDCommand
{
public:
	ExitCommand(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;
};
