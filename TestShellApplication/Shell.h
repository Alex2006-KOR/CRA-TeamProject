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
	string trim(const string& str);
};

