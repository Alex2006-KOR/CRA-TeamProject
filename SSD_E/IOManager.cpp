#include <stdexcept>

#include "IOManager.h"

IOManager::IOManager(DeviceDriver* pstDeviceDriver) : m_pstDeviceDriver(pstDeviceDriver)
{}

void IOManager::DoCommand(string strCommand, int nLbaNumber, string strData) {
	if (_CheckInvalidArgument(strCommand, nLbaNumber, strData)) throw std::invalid_argument("Invalid Argument.");;
	if (strCommand == "W") m_pstDeviceDriver->WriteData(nLbaNumber, strData);
	if (strCommand == "R") m_pstDeviceDriver->ReadData(nLbaNumber);
}

bool IOManager::_CheckInvalidArgument(string strCommand, int nLbaNumber, string strData) {
	if (_IsInvalidCmd(strCommand)) return true;
	if (strCommand == "W" && _CheckWriteCmdInvalidArgument(nLbaNumber, strData)) return true;
	if (strCommand == "R" && _CheckReadCmdInvalidArgument(nLbaNumber)) return true;
	return false;
}

bool IOManager::_CheckReadCmdInvalidArgument(int nLbaNumber) {
	if (nLbaNumber < 0 || nLbaNumber >= 100) return true;
	return false;
}

bool IOManager::_CheckWriteCmdInvalidArgument(int nLbaNumber, string strData) {
	if (nLbaNumber < 0 || nLbaNumber >= 100) return true;
	if (strData.size() != 10) return true;
	if (strData.rfind("0x", 0) != 0) return true;
	if (_IsInvalidSubString(strData)) return true;
	return false;
}

bool IOManager::_IsInvalidSubString(string strData) {
	string strSubstring = strData.substr(2, 10 - 2);
	for (const auto& cChar : strSubstring) {
		if (cChar >= '0' && cChar <= '9') continue;
		if (cChar >= 'A' && cChar <= 'F') continue;
		return true;
	}
	return false;
}

bool IOManager::_IsInvalidCmd(string strCommand) {
	return strCommand != "W" && strCommand != "R";
}