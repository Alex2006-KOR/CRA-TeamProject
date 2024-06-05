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
	BaseSSDCommand(vector<string>vCommandList);
	virtual ~BaseSSDCommand() = default;

public:
	void Execute() override;

protected:
	virtual bool _parseCommand() = 0;
	virtual void _execute() = 0;

protected:
	vector<string> m_vCommandList;
};
