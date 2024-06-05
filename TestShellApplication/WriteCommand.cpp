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

	string lbaString = m_vCommandList[0];
	for (const char ch : lbaString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		m_out << "INVALID LBA\n";
		return false;
	}
	int lba = std::stoi(lbaString, nullptr, 10);
	if (lba < 0 || lba > 99) {
		m_out << "INVALID LBA\n";
		return false;
	}
	m_nLBA = lba;

	string dataString = m_vCommandList[1];
	if (dataString.substr(0, 2).compare("0x") != 0) {
		m_out << "INVALID DATA\n";
		return false;
	}
	dataString = dataString.substr(2);

	if (dataString.size() != 8) {
		m_out << "INVALID DATA\n";
		return false;
	}

	for (const char ch : dataString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		if ((ch >= 'a') && (ch <= 'f')) continue;
		if ((ch >= 'A') && (ch <= 'F')) continue;
		m_out << "INVALID DATA\n";
		return false;
	}
	m_nData = std::stoi(dataString, nullptr, 16);
}

void WriteCommand::_execute()
{
	m_pstSSDDriver->Write(m_nLBA, m_nData);
}