#include "IOManager.h"

void IOManager::DoCommand(string strCommand, int nLbaNumber, string strData) {
	if (strCommand == "W") {
		pstDeviceDriver->WriteData(nLbaNumber, strData);
	}
	if (strCommand == "R") {
		pstDeviceDriver->ReadData(nLbaNumber);
	}
}