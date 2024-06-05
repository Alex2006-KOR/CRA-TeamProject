#include "WriteCommand.h"

#include <iostream>
#include <iomanip>

using std::string;

WriteCommand::WriteCommand(vector<string> commandList, DriverInterface* pSSDDriver, std::ostream& output)
	: BaseSSDCommand(commandList)
	, m_pstSSDDriver(pSSDDriver)
	, m_out(output)
	, m_nLBA(-1)
	, m_nData(0x00000000)
{
}

bool WriteCommand::_parseCommand()
{
	if (m_vCommandList.size() != 2) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}

	m_nLBA = std::stoi(m_vCommandList[0], nullptr, 10);
	m_nData = std::stol(m_vCommandList[1], nullptr, 16);
}

void WriteCommand::_execute()
{
	m_pstSSDDriver->Write(m_nLBA, m_nData);
}
