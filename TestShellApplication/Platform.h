#pragma once
#include "Device.h"

#include <iomanip>

class Platform {
public:
	Platform(DriverInterface* pstDevice, ostream& output);
	void SingleWrite(vector<string> vCommandList);
	void SingleRead(vector<string> vCommandList);
	void FullWrite(vector<string> vCommandList);
	void FullRead();

private:
	ostream& m_out;
	Device* m_pstDriver;
};