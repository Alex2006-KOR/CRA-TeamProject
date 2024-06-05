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
	if (m_vCommandList.size() != 1) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}

	if (m_vCommandList[0].substr(0, 2) == "0x") {
		m_out << "INVALID LBA\n";
		return false;
	}

	try {
		m_nLBA = stoi(m_vCommandList[0]);
		if (m_nLBA < 0 || m_nLBA > 99) {
			m_out << "INVALID LBA\n";
			return false;
		}
		return true;
	}
	catch (const invalid_argument& e) {
		//m_out << "Invalid argument: " << e.what() << endl;
		m_out << "INVALID LBA\n";
		return false;
	}
	catch (const out_of_range& e) {
		//m_out << "Out of range: " << e.what() << endl;
		m_out << "INVALID LBA\n";
		return false;
	}
}

void ReadCommand::_execute()
{
	int nData = m_pstSSDDriver->Read(m_nLBA);
	m_out << "0x";
	m_out << hex << uppercase << setw(8) << setfill('0') << nData;
	m_out << endl;
}