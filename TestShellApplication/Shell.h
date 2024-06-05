#pragma once

#include "DriverInterface.h"

#include <iostream>
#include <vector>

using namespace std;

class Shell
{
public:
	Shell(DriverInterface* pSSDDriver);

	void Run(istream& input, ostream& output);

private:
	DriverInterface* m_pSSDDriver;

	void handleCommand(string lineString, ostream& output);

	vector<string> SplitLine(string& strCommandLine);
};

