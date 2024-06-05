#include "SSDCommandInvoker.h"

#include "ReadCommand.h"
#include "WriteCommand.h"
#include "FullReadCommand.h"
#include "FullWriteCommand.h"
#include "ExitCommand.h"

SSDCommandInvoker::SSDCommandInvoker(DriverInterface* pSSDDriver, ostream& output)
{
	_initCommands(pSSDDriver, output);
}

SSDComamnd* SSDCommandInvoker::GetCommand(string command)
{
	auto iterFind = m_mapCommand.find(command);
	if (iterFind == m_mapCommand.end()) {
		return nullptr;
	}
	return iterFind->second;
}

void SSDCommandInvoker::_initCommands(DriverInterface* pSSDDriver, ostream& output)
{
	m_mapCommand["read"] = new ReadCommand(pSSDDriver, output);
	m_mapCommand["write"] = new WriteCommand(pSSDDriver, output);
	m_mapCommand["fullread"] = new FullReadCommand(pSSDDriver, output);
	m_mapCommand["fullwrite"] = new FullWriteCommand(pSSDDriver, output);
	m_mapCommand["exit"] = new ExitCommand(pSSDDriver, output);
}
