#include "SSDCommand.h"

BaseSSDCommand::BaseSSDCommand(std::ostream& output)
	: m_out(output)
{
}

void BaseSSDCommand::SetCommandList(vector<string> vCommandList)
{
	m_vCommandList = vCommandList;
}

bool BaseSSDCommand::Execute()
{
	if (_parseCommand() == false) {
		return false;
	}
	_execute();
	return true;
}
