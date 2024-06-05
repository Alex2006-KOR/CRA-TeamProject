#pragma once

#include <string>

#include "DeviceDriver.h"

using namespace std;

#define interface struct
interface IOManager
{
public:
	IOManager(DeviceDriver* pstDeviceDriver);
	void DoCommand(string strCommand, int nLbaNumber, string strData = "NoData");

private:
	DeviceDriver* m_pstDeviceDriver;

	bool _CheckInvalidArgument(string strCommand, int nLbaNumber, string strData);
	bool _CheckReadCmdInvalidArgument(int nLbaNumber);
	bool _CheckWriteCmdInvalidArgument(int nLbaNumber, string strData);
	bool _IsInvalidSubString(string strData);
	bool _IsInvalidCmd(string strCommand);
};