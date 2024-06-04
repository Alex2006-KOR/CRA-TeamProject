#include "IOManager.h"

IOManager::IOManager(DeviceDriver* pstDeviceDriver) : m_pstDeviceDriver(pstDeviceDriver)
{}

void IOManager::DoCommand(string strCommand, int nLbaNumber, string strData) {
	if (strCommand == "W") {
		if(_CheckInvalidArgument(nLbaNumber, strData)) return;
		m_pstDeviceDriver->WriteData(nLbaNumber, strData);
	}
	if (strCommand == "R") {
		if (_CheckInvalidArgument(nLbaNumber)) return;
		m_pstDeviceDriver->ReadData(nLbaNumber);
	}
}

bool IOManager::_CheckInvalidArgument(int nLbaNumber, string strData) {
	if (nLbaNumber < 0 || nLbaNumber >= 100) return true;
	if (strData == "NoData") return false;
	
	if (strData.size() != 10) return true;
	if (strData.rfind("0x", 0) != 0) return true;
	return false;
}