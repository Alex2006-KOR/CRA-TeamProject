#include <stdexcept>
#include "IOManager.h"
#include "FileManager.h"
#include "SSDCommand.h"

IOManager::IOManager(DeviceDriver* pstDeviceDriver) : m_pstDeviceDriver(pstDeviceDriver)
{
	string m_strCommand = "";
	int m_nLbaNumber = 0;
	string m_strData = "";
	int m_nSize = 0;
}

void IOManager::DoCommand(int argc, char* argv[]) {
	_ProcessArgument(argc, argv);
	Command* pstCommand = nullptr;

	if (m_strCommand == "W") pstCommand = new WriteCommand(m_nLbaNumber, m_strData);
	if (m_strCommand == "R") pstCommand = new ReadCommand(m_nLbaNumber);
	if (m_strCommand == "E") pstCommand = new EraseCommand(m_nLbaNumber, m_nSize);
	if (m_strCommand == "F") pstCommand = new FlushCommand();

	m_pstDeviceDriver->SetCmd(pstCommand);
	m_pstDeviceDriver->Execute();

	_AddLog();
}

void IOManager::_AddLog() {
	FileManager stLogFile("CommandLog.txt");

	string log = "Command: " + m_strCommand;
	if (m_strCommand != "F") log += "\tLBA: " + to_string(m_nLbaNumber);
	if (m_strCommand == "W") log += "\tData: " + m_strData;
	else if (m_strCommand == "E") log += "\tSize: " + m_nSize;

	stLogFile.OpenWriteStream("append");
	stLogFile.Write(log);
	stLogFile.CloseWriteStream();
}

void IOManager::_ProcessArgument(int argc, char* argv[]) {
	if (_CheckInvalidArgumentNumber(argc, argv)) throw std::invalid_argument("Invalid Argument Number.");
	_ExtractArgument(argv);
	if (_CheckInvalidArgumentValue()) throw std::invalid_argument("Invalid Argument Value.");
}

bool IOManager::_CheckInvalidArgumentNumber(int argc, char* argv[]) {
	if (argc == THERE_IS_NO_ARGUMENT) return true;
	if (string(argv[1]) == "W" && argc != WRITE_CMD_ARGUMENT_NUM) return true;
	if (string(argv[1]) == "R" && argc != READ_CMD_ARGUMENT_NUM) return true;
	if (string(argv[1]) == "E" && argc != ERASE_CMD_ARGUMENT_NUM) return true;
	if (string(argv[1]) == "F" && argc != FLUSH_CMD_ARGUMENT_NUM) return true;

	return false;
}

void IOManager::_ExtractArgument(char* argv[]) {
	m_strCommand = string(argv[1]);
	if (m_strCommand == "R") {
		m_nLbaNumber = stoi(string(argv[2]));
		return;
	}
	if (m_strCommand == "W") {
		m_nLbaNumber = stoi(string(argv[2]));
		m_strData = string(argv[3]);
		return;
	}
	if (m_strCommand == "E") {
		m_nLbaNumber = stoi(string(argv[2]));
		m_nSize = stoi(string(argv[3]));
		return;
	}
}

bool IOManager::_CheckInvalidArgumentValue() {
	if (_IsInvalidCmd()) return true;
	if (m_strCommand == "W" && _CheckWriteCmdInvalidArgument()) return true;
	if (m_strCommand == "R" && _CheckReadCmdInvalidArgument()) return true;
	if (m_strCommand == "E" && _CheckEraseCmdInvalidArgument()) return true;
	return false;
}

bool IOManager::_CheckReadCmdInvalidArgument() {
	if (m_nLbaNumber < 0 || m_nLbaNumber >= 100) return true;
	return false;
}

bool IOManager::_CheckWriteCmdInvalidArgument() {
	if (m_nLbaNumber < 0 || m_nLbaNumber >= 100) return true;
	if (m_strData.size() != 10) return true;
	if (m_strData.rfind("0x", 0) != 0) return true;
	if (_IsInvalidSubString()) return true;
	return false;
}

bool IOManager::_CheckEraseCmdInvalidArgument() {
	if (m_nLbaNumber < 0 || m_nLbaNumber >= 100) return true;
	if (m_nSize < 0 || m_nSize >= 100) return true;
	if (m_nLbaNumber + m_nSize > 100) return true;
	return false;
}

bool IOManager::_IsInvalidSubString() {
	string strSubstring = m_strData.substr(2, 10 - 2);
	for (const auto& cChar : strSubstring) {
		if (cChar >= '0' && cChar <= '9') continue;
		if (cChar >= 'A' && cChar <= 'F') continue;
		return true;
	}
	return false;
}

bool IOManager::_IsInvalidCmd() {
	if (m_strCommand == "W") return false;
	if (m_strCommand == "R") return false;
	if (m_strCommand == "E") return false;
	if (m_strCommand == "F") return false;
	return true;
}