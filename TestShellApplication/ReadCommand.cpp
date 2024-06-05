#include "ReadCommand.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>


ReadCommand::ReadCommand(DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(output)
	, m_pstSSDDriver(pSSDDriver)
	, m_nLBA(-1)
{
}

bool ReadCommand::_parseCommand() {
	if (_checkValidityLBA() == false) return false;
	return true;
}

bool ReadCommand::_checkValidityLBA()
{
	if (_hasEnoughArgs() == false) return false;
	if (_isValidFormat() == false) return false;
	_updateLBA();
	if (_isLBAInRange() == false) return false;
	return true;
}

bool ReadCommand::_hasEnoughArgs()
{
	if (m_vCommandList.size() != m_nExpectedArgCnt) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}
	return true;
}

bool ReadCommand::_isValidFormat()
{
	if (m_vCommandList[0].substr(0, 2) == "0x") {
		m_out << "INVALID LBA\n";
		return false;
	}
	for (const char ch : m_vCommandList[0]) {
		if ((ch >= '0') && (ch <= '9')) continue;
		m_out << "INVALID LBA\n";
		return false;
	}
	return true;
}

void ReadCommand::_updateLBA()
{
	try {
		m_nLBA = stoi(m_vCommandList[0]);
	}
	catch (const out_of_range& e) {
		m_nLBA = -1;
	}
}

bool ReadCommand::_isLBAInRange()
{
	if (m_nLBA < 0 || m_nLBA > 99) {
		m_out << "INVALID LBA\n";
		return false;
	}
	return true;
}

void ReadCommand::_execute()
{
	int nData = m_pstSSDDriver->Read(m_nLBA);
	m_out << "0x";
	m_out << hex << uppercase << setw(8) << setfill('0') << nData;
	m_out << endl;
}