#include "SSDCommand.h"

#include <stdexcept>

BaseSSDCommand::BaseSSDCommand(vector<string> commandList) {
	m_vCommandList = commandList;
}

void BaseSSDCommand::Execute()
{
	bool bSuccess = _parseCommand();
	if (bSuccess) _execute();
}
