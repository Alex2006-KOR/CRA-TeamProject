#include "ReadCommand.h"

#include <iostream>
#include <iomanip>

using std::string;

ReadCommand::ReadCommand(vector<string> commandList, DriverInterface* pSSDDriver, std::ostream& output)
	: BaseSSDCommand(commandList)
	, m_pSSDDriver(pSSDDriver)
	, m_nLBA(-1)
	, m_out(output)
{
}

void ReadCommand::_execute()
{
	int nData = m_pSSDDriver->Read(m_nLBA);
	m_out << "0x";
	m_out << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << nData;
	m_out << std::endl;
}

void ReadCommand::_parseCommand()
{
	if (m_commandList.size() != 1) {
		throw std::exception();
	}

	m_nLBA = atoi(m_commandList[0].c_str());
}
