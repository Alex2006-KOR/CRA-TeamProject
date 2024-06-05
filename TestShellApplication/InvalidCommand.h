#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class InvalidCommand
	: public BaseSSDCommand
{
public:
	InvalidCommand(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;
};
