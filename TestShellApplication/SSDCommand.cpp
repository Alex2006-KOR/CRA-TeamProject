#include "SSDCommand.h"

BaseSSDCommand::BaseSSDCommand(vector<string> commandList) {
	m_commandList = commandList;
}

void BaseSSDCommand::Execute()
{
	_parseCommand();
	_execute();
}
