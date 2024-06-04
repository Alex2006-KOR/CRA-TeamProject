#pragma once

#include <string>
#include <vector>
using namespace std;

#define interface struct

interface SSDComamnd {
	virtual void Execute() = 0;
};

class BaseSSDCommand
	: public SSDComamnd
{
public:
	BaseSSDCommand(vector<string>commandList);
	virtual ~BaseSSDCommand() = default;

protected:
	virtual void parseCommand() {}

protected:
	vector<string> m_commandList;
};
