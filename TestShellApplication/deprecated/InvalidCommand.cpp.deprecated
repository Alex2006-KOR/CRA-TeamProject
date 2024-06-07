#include "InvalidCommand.h"

#include <iostream>

InvalidCommand::InvalidCommand(DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(output)
{
}

bool InvalidCommand::_parseCommand() {
	return true;
}

void InvalidCommand::_execute()
{
	m_out << "INVALID COMMAND\n";
}