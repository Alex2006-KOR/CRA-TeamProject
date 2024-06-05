#include "SSDCommand.h"

#include <stdexcept>

BaseSSDCommand::BaseSSDCommand(vector<string> commandList) {
	m_vCommandList = commandList;
}

bool BaseSSDCommand::Execute()
{
	if (_parseCommand() == false) {
		return false;
	}
	_execute();
	return true;
}
