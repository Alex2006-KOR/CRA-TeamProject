#pragma once
#include <string>

#include "DeviceDriver.h"

using namespace std;

#define interface struct
interface IOManager
{
public:
	void DoCommand(string strCommand, int nLbaNumber, string strData);
private:
	DeviceDriver* pstDeviceDriver;
};