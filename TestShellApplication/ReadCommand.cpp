#include "ReadCommand.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>


ReadCommand::ReadCommand(vector<string> vCommandList, DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(vCommandList)
	, m_pstSSDDriver(pSSDDriver)
	, m_nLBA(-1)
	, m_out(output)
{
}

bool ReadCommand::_parseCommand()
{
	return true;
}

void ReadCommand::_execute()
{
	int nData = m_pstSSDDriver->Read(m_nLBA);
	m_out << "0x";
	m_out << hex << uppercase << setw(8) << setfill('0') << nData;
	m_out << endl;
}