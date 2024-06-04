#pragma once
#include <string>
#include "DeviceDriver.h"

using namespace std;

#define interface struct
interface IOManager
{
public:
	IOManager(DeviceDriver* pstDeviceDriver);
	void DoCommand(string strCommand, int nLbaNumber, string strData);
private:
	DeviceDriver* m_pstDeviceDriver;

	bool _CheckInvalidArgument(int nLbaNumber, string strData = "NoData");
};