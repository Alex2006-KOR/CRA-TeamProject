#include "FullReadCommand.h"
#include "ReadCommand.h"


FullReadCommand::FullReadCommand(DriverInterface* pSSDDriver, std::ostream& output)
	: BaseSSDCommand(output)
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
		ReadCommand read(m_pstSSDDriver, m_out);
		read.SetCommandList({ to_string(nLba) });
		read.Execute();
	}
}
