#include "WriteCommand.h"

#include <iostream>
#include <iomanip>

using std::string;

WriteCommand::WriteCommand(vector<string> commandList, DriverInterface* pSSDDriver, std::ostream& output)
	: BaseSSDCommand(commandList, output)
	, m_pstSSDDriver(pSSDDriver)
	, m_nLBA(-1)
	, m_nData(0x00000000)
{
}

bool WriteCommand::_parseCommand()
{
	constexpr int REQUIRED_COMMAND_COUNT = 2;
	if (m_vCommandList.size() != REQUIRED_COMMAND_COUNT) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}

	try {
		m_nLBA = _checkAndGetLBA(m_vCommandList[0]);
		m_nData = _checkAndGetData(m_vCommandList[1]);
	}
	catch (std::exception& e) {
		m_out << e.what();
		return false;
	}
}

void WriteCommand::_execute()
{
	m_pstSSDDriver->Write(m_nLBA, m_nData);
}

int WriteCommand::_checkAndGetLBA(string paramString)
{
	for (const char ch : paramString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		throw std::exception("INVALID LBA\n");
	}

	int result = std::stoi(paramString, nullptr, 10);
	if (result < 0 || result > 99) {
		throw std::exception("INVALID LBA\n");
	}

	return result;
}

int WriteCommand::_checkAndGetData(string paramString)
{
	if (paramString.substr(0, 2).compare("0x") != 0) {
		throw std::exception("INVALID DATA\n");
	}
	paramString = paramString.substr(2);

	if (paramString.size() != 8) {
		throw std::exception("INVALID DATA\n");
	}

	for (const char ch : paramString) {
		if ((ch >= '0') && (ch <= '9')) continue;
		if ((ch >= 'a') && (ch <= 'f')) continue;
		if ((ch >= 'A') && (ch <= 'F')) continue;
		throw std::exception("INVALID DATA\n");
	}

	return std::stoll(paramString, nullptr, 16);
}
