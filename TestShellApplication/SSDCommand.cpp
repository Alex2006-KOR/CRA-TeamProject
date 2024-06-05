#include "SSDCommand.h"

BaseSSDCommand::BaseSSDCommand(vector<string> vCommandList, std::ostream& output)
	: m_vCommandList(vCommandList)
	, m_out(output)
{
}

bool BaseSSDCommand::Execute()
{
	if (_parseCommand() == false) {
		return false;
	}
	_execute();
	return true;
}
