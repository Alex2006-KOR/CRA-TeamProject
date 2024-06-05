#include "ExitCommand.h"

ExitCommand::ExitCommand(DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(output)
{
}

bool ExitCommand::_parseCommand() {
	return true;
}

void ExitCommand::_execute()
{
	throw ExitShellException();
}