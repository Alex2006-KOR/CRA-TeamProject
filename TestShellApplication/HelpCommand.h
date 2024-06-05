#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class HelpCommand
	: public BaseSSDCommand
{
public:
	HelpCommand(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;
};
