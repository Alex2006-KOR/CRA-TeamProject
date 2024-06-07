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
	void FullRead();

private:
	TestLibrary();
	~TestLibrary();
	TestLibrary(const TestLibrary&) = delete;
	TestLibrary& operator=(const TestLibrary&) = delete;

	static TestLibrary* m_Instance;
	Device* m_pstDriver;
	ostream* m_out;
};