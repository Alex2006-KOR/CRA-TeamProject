#pragma once

#include "DriverInterface.h"
#include "TestLibraryCommandInvoker.h"
#include "./TestScripts/TestScriptInvoker.h"

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
	TestLibCommandInvoker* m_pstTestLibCommandInvoker;
	TestScriptInvoker* m_pstTestScriptInvoker;

	void _printHelp();

	vector<string> _splitLine(std::string& strLine);
	string _trim(const string& str);
};