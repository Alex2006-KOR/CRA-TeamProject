#pragma once

#include "TestLibrary.h"
#include "DriverInterface.h"
#include "./TestScripts/TestApp1.h"
#include "./TestScripts/TestApp2.h"

#include <iostream>

using namespace std;

class Shell
{
public:
	Shell(DriverInterface* pstDevice);

public:
	void Run(istream& input);
	bool handleCommand(string lineString);

private:
	ostream& m_out;
	TestLibrary* m_pstTestLib;
	TestApp1* m_pstTestApp1;
	TestApp2* m_pstTestApp2;

	void _printHelp();

	vector<string> _splitLine(std::string& strLine);
	string _trim(const string& str);
};