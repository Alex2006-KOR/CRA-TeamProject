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

	// FIXME: move to private fuction ? use as public ?
	bool handleCommand(string lineString, ostream& output); 

private:
	DriverInterface* m_pSSDDriver;

	vector<string> SplitLine(string& strCommandLine);
	string trim(const string& str);
};

