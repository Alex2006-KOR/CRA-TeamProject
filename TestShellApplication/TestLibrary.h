#pragma once
#include "Device.h"

#include <iomanip>
#include <iostream>

class TestLibrary {
public:
	static TestLibrary* GetLibrary(DriverInterface * pstDevice = nullptr, ostream* output = nullptr);

	void Write(vector<string> vCommandList);
	void Read(vector<string> vCommandList);
	void FullWrite(vector<string> vCommandList);
	void FullRead(string strExpected = "");
	void WriteRange(int nStartLba, int nEndLba, string strData);
	void ReadRange(int nStartLba, int nEndLba, string strData = "");

private:
	TestLibrary();
	~TestLibrary();
	TestLibrary(const TestLibrary&) = delete;
	TestLibrary& operator=(const TestLibrary&) = delete;

	static TestLibrary* m_Instance;
	Device* m_pstDriver;
	ostream* m_out;
};