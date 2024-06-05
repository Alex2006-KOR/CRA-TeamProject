#include "FullReadCommand.h"
#include "ReadCommand.h"


FullReadCommand::FullReadCommand(vector<string> commandList, DriverInterface* pSSDDriver, std::ostream& output)
	: BaseSSDCommand(commandList, output)
	, m_pstSSDDriver(pSSDDriver)
{
}

bool FullReadCommand::_parseCommand()
{
	return true;
}

void FullReadCommand::_execute()
{
	for (int nLba = 0; nLba < 100; nLba++) {
		ReadCommand read({ to_string(nLba) }, m_pstSSDDriver, m_out);
		read.Execute();
	}
}
