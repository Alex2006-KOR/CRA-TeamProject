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

public:
	void Execute() override;

protected:
	virtual void _execute() = 0;
	virtual void _parseCommand() = 0;

protected:
	vector<string> m_commandList;
};
