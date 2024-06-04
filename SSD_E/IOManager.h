#pragma once
#include <string>

using namespace std;

#define interface struct
interface IOManager
{
public:
	void DoCommand(string strCommand, int nLbaNumber, string strData);
private:
	bool _CheckInvalidArgument(int nLbaNumber, string strData = "NoData");
};