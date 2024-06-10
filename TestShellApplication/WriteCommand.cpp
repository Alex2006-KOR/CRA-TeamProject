#include "WriteCommand.h"
#include "ShellException.h"

#include <stdexcept>

WriteCommand::WriteCommand(DriverInterface* pstDriver)
	: m_pstDriver(pstDriver)
	, m_nLBA(-1)
	, m_nData(0x00000000)
{
}

WriteCommand& WriteCommand::setLBA(string strLBA)
{
	_checkLBAFormat(strLBA);
	_updateLBA(strLBA);
	_checkLBARange();
	return *this;
}

WriteCommand& WriteCommand::setData(string strData)
{
	_checkDataFormat(strData);
	_checkSpelling(strData);
	_updateData(strData);
	return *this;
}

void WriteCommand::execute()
{
	m_pstDriver->Write(m_nLBA, m_nData);
}

bool WriteCommand::CheckArgCnt(vector<string> vArgs) const
{
	return vArgs.size() == this->REQUIRED_COMMAND_COUNT;
}

void WriteCommand::_checkLBAFormat(string strLBA)
{
	if (strLBA.substr(0, 2) == "0x") {
		throw Invalid_LBA("not a decimal format");
	}
	for (const char ch : strLBA) {
		if ((ch >= '0') && (ch <= '9')) continue;
		throw Invalid_LBA("not a decimal number found");
	}
}

void WriteCommand::_updateLBA(string strLBA)
{
	try {
		m_nLBA = stoi(strLBA);
	}
	catch (const out_of_range& e) {
		m_nLBA = -1;
	}
}

void WriteCommand::_checkLBARange()
{
	if (m_nLBA < m_pstDriver->GetMinLba() || m_nLBA >= m_pstDriver->GetMaxLba())
		throw Invalid_LBA("LBA out of range");
}


void WriteCommand::_checkDataFormat(string& strData) const
{
	if (strData.substr(0, 2).compare("0x") != 0
		|| strData.size() != REQUIRED_DATA_LENGTH)
		throw Invalid_Data("not a hexadecimal format");
}

void WriteCommand::_checkSpelling(string& strData)
{
	bool bCheckResult = true;
	strData = strData.substr(2);
	for (const char ch : strData) {
		if ((ch >= '0') && (ch <= '9')) continue;
		if ((ch >= 'a') && (ch <= 'f')) continue;
		if ((ch >= 'A') && (ch <= 'F')) continue;
		throw Invalid_Data("not a hexadecial number found");
	}
}

void WriteCommand::_updateData(std::string& strData)
{
	m_nData = stoll(strData, nullptr, 16);
}