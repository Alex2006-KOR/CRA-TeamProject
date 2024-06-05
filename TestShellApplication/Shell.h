#pragma once

#include "DriverInterface.h"
#include "SSDCommandInvoker.h"

#include <iostream>
#include <vector>

using namespace std;

class Shell
{
public:
	Shell(DriverInterface* pSSDDriver);
	virtual ~Shell();

	void Run(istream& input, ostream& output);

	// FIXME: move to private fuction ? use as public ?
	bool handleCommand(string lineString, ostream& output); 

private:
	SSDCommandInvoker* _getCommandInvoker(ostream& output);
	vector<string> SplitLine(string& strCommandLine);
	string trim(const string& str);

private:
	DriverInterface* m_pSSDDriver;
	SSDCommandInvoker* m_pCommandInvoker;

	string strHelp = "\n\
[[Shell Test Application]]\n\
\n\
<< Command Usage >> \n\
- write [lba] [data]\n\
- read [lba]\n\
- fullwrite [data]\n\
- fullread\n\
- exit\n\
\n\
[lba] : decimal only, range = [0, 99]\n\
[data] : hexadecimal only, range = [0x00000000, 0xFFFFFFFF]\n\
";
};

