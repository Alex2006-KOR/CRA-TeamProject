#pragma once

#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#define interface struct

interface SSDComamnd {
	virtual void SetCommandList(vector<string> vCommandList) = 0;
	virtual bool Execute() = 0;
};

class BaseSSDCommand
	: public SSDComamnd
{
public:
	BaseSSDCommand(std::ostream& output);
	virtual ~BaseSSDCommand() = default;

public:
	void SetCommandList(vector<string> vCommandList) override;
	bool Execute() override;

protected:
	virtual bool _parseCommand() = 0;
	virtual void _execute() = 0;

protected:
	vector<string> m_vCommandList;
	std::ostream& m_out;
};

class ExitShellException : public std::exception {
};