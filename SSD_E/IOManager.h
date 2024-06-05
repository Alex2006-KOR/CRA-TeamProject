#pragma once

#include <string>

#include "DeviceDriver.h"

using namespace std;

#define interface struct
interface IOManager
{
public:
	static const int MAX_CMD_ARGUMENT_NUM = 4;
	static const int THERE_IS_NO_ARGUMENT = 1;
	static const int WRITE_CMD_ARGUMENT_NUM = 4;
	static const int READ_CMD_ARGUMENT_NUM = 3;

	IOManager(DeviceDriver* pstDeviceDriver);
	void DoCommand(int argc, char* argv[]);

private:
	DeviceDriver* m_pstDeviceDriver;
	string m_strCommand;
	int m_nLbaNumber;
	string m_strData;

	void _AddLog();
	void _ProcessArgument(int argc, char* argv[]);
	void _ExtractArgument(char* argv[]);
	bool _CheckInvalidArgumentNumber(int argc, char* argv[]);
	bool _CheckInvalidArgumentValue();
	bool _CheckReadCmdInvalidArgument();
	bool _CheckWriteCmdInvalidArgument();
	bool _IsInvalidSubString();
	bool _IsInvalidCmd();
};