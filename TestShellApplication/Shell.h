#pragma once

#include "Platform.h"
#include "DriverInterface.h"

#include <iostream>

using namespace std;

class Shell
{
public:
	Shell(DriverInterface* pstDevice, ostream& output);

public:
	void Run(istream& input);
	bool handleCommand(string lineString);

private:
	ostream& m_out;
	Platform* m_pstTestList;

	void _printHelp();

	vector<string> _splitLine(std::string& strLine);
	string _trim(const string& str);
};