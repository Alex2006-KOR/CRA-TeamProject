#include "EraseCommand.h"
#include "ShellException.h"

#include <stdexcept>

EraseCommand::EraseCommand(DriverInterface* pstDriver)
	: m_pstDriver(pstDriver)
	, m_nLBA(-1)
	, m_nBlkCnt(0x00000000)
{
}

EraseCommand& EraseCommand::setLBA(string strLBA)
{
	_checkLBAFormat(strLBA);
	_updateLBA(strLBA);
	_checkLBARange();
	return *this;
}

EraseCommand& EraseCommand::setBlkCnt(string strData)
{
	_checkLBAIsValid();
	_updateBlkCnt(strData);
	_checkBlkRange();
	return *this;
}

void EraseCommand::execute()
{
	m_pstDriver->Erase(m_nLBA, m_nBlkCnt);
}

bool EraseCommand::CheckArgCnt(vector<string> vArgs) const
{
	return vArgs.size() == this->REQUIRED_COMMAND_COUNT;
}

void EraseCommand::_checkLBAFormat(string strLBA)
{
	if (strLBA.substr(0, 2) == "0x") {
		throw Invalid_LBA("not a decimal format");
	}
	for (const char ch : strLBA) {
		if ((ch >= '0') && (ch <= '9')) continue;
		throw Invalid_LBA("not a decimal number found");
	}
}

void EraseCommand::_updateLBA(string strLBA)
{
	try {
		m_nLBA = stoi(strLBA);
	}
	catch (const out_of_range& e) {
		m_nLBA = -1;
	}
}

void EraseCommand::_checkLBARange()
{
	if (m_nLBA < m_pstDriver->GetMinLba() || m_nLBA >= m_pstDriver->GetMaxLba())
		throw Invalid_LBA("LBA out of range");
}


void EraseCommand::_checkLBAIsValid()
{
	_checkLBARange();
}

void EraseCommand::_checkBlkCntFormat(std::string strBlkCnt)
{
	if (strBlkCnt.substr(0, 2) == "0x") {
		throw Invalid_BlockCount("not a decimal format");
	}
	for (const char ch : strBlkCnt) {
		if ((ch >= '0') && (ch <= '9')) continue;
		throw Invalid_BlockCount("not a decimal number found");
	}
}

void EraseCommand::_updateBlkCnt(std::string strBlkCnt)
{
	try {
		m_nBlkCnt = stoi(strBlkCnt);
	}
	catch (const out_of_range& e) {
		m_nBlkCnt = -1;
	}
}

void EraseCommand::_checkBlkRange()
{
	if (m_nBlkCnt < m_pstDriver->GetMinLba()) 
		throw Invalid_BlockCount("Block Count out of range");
	else if (m_nBlkCnt < m_pstDriver->GetMaxBlkCntPerErase()) 
		throw Invalid_BlockCount("use 'erase_range [start_LBA] [end_LBA]'");
	// TODO : check more conditions ?
}