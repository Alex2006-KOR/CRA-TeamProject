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

bool ReadCommand::_parseCommand() {
	if (_checkValidityLBA() == false) return false;
	return true;
}

bool ReadCommand::_checkValidityLBA()
{
	if (_hasEnoughArgs() == false) return false;
	if (_isDecimalFormat() == false) return false;
	if (_isValidCharacter() == false) return false;
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

bool ReadCommand::_isDecimalFormat()
{
	if (m_vCommandList[0].substr(0, 2) == "0x") {
		m_out << "INVALID LBA\n";
		return false;
	}
	return true;
}

bool ReadCommand::_isValidCharacter()
{
	try {
		stoi(m_vCommandList[0]);
		return true;
	}
	catch (const invalid_argument& e) {
		//m_out << "Invalid argument: " << e.what() << endl;
		m_out << "INVALID LBA\n";
		return false;
	}
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