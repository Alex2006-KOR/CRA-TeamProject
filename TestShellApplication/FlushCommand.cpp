#include "FlushCommand.h"

FlushCommand::FlushCommand(DriverInterface* pstDriver)
	: m_pstDriver(pstDriver)
{
}

void FlushCommand::execute()
{
	m_pstDriver->Flush();
}

bool FlushCommand::CheckArgCnt(vector<string> vArgs) const
{
	return vArgs.size() == this->REQUIRED_COMMAND_COUNT;
}
