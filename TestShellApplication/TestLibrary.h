#pragma once
#include "Device.h"

#include <iomanip>

class TestLibrary {
public:
	TestLibrary(DriverInterface* pstDevice, ostream& output);
	void SingleWrite(vector<string> vCommandList);
	void SingleRead(vector<string> vCommandList);
	void FullWrite(vector<string> vCommandList);
	void FullRead();

private:
	ostream& m_out;
	Device* m_pstDriver;
};