#include <stdexcept>

#include "IOManager.h"

IOManager::IOManager(DeviceDriver* pstDeviceDriver) : m_pstDeviceDriver(pstDeviceDriver)
{}

void IOManager::DoCommand(string strCommand, int nLbaNumber, string strData) {
	if (strCommand != "W" && strCommand != "R") throw std::invalid_argument("Invalid Argument.");
	if (strCommand == "W") {
		if (_CheckInvalidArgument(nLbaNumber, strData)) throw std::invalid_argument("Invalid Argument.");
		m_pstDeviceDriver->WriteData(nLbaNumber, strData);
	}
	if (strCommand == "R") {
		if (_CheckInvalidArgument(nLbaNumber)) throw std::invalid_argument("Invalid Argument.");
		m_pstDeviceDriver->ReadData(nLbaNumber);
	}

}

bool IOManager::_CheckInvalidArgument(int nLbaNumber, string strData) {
	if (nLbaNumber < 0 || nLbaNumber >= 100) return true;
	if (strData == "NoData") return false;

	if (strData.size() != 10) return true;
	if (strData.rfind("0x", 0) != 0) return true;

	string strSubstring = strData.substr(2, 10 - 2);
	for (const auto& cChar : strSubstring) {
		if (cChar >= '0' && cChar <= '9') continue;
		if (cChar >= 'A' && cChar <= 'F') continue;
		return true;
	}
	return false;
}