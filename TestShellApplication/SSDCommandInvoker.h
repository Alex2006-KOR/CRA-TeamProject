#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

#include <string>
#include <map>

using std::string;
using std::map;

class SSDCommandInvoker
{
public:
	SSDCommandInvoker(DriverInterface* pSSDDriver, ostream& output);

	SSDComamnd* GetCommand(string command);

private:
	void _initCommands(DriverInterface* pSSDDriver, ostream& output);

private:
	map<string, SSDComamnd*> m_mapCommand;
	SSDComamnd* m_pInvalidCommand;
};

