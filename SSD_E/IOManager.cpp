#include "IOManager.h"
#include "DeviceDriver.h"
#include "ssd.cpp"

void IOManager::DoCommand(string strCommand, int nLbaNumber, string strData) {
	SSDInterface* pstSSDInterface = new SSD();
//	SSDInterface* pstSSDInterface = new SSDMock();
	DeviceDriver stDeviceDriver{ pstSSDInterface };

	if (strCommand == "W") {
		if(_CheckInvalidArgument(nLbaNumber, strData)) return;
		stDeviceDriver.WriteData(nLbaNumber, strData);
	}
	if (strCommand == "R") {
		if (_CheckInvalidArgument(nLbaNumber)) return;
		stDeviceDriver.ReadData(nLbaNumber);
	}
}

bool IOManager::_CheckInvalidArgument(int nLbaNumber, string strData) {
	if (nLbaNumber < 0 || nLbaNumber >= 100) return true;
	if (strData == "NoData") return false;
	
	if (strData.size() != 10) return true;
	if (strData.rfind("0x", 0) != 0) return true;
	return false;
}