#pragma once
#include "SSDCommand.h"

class ReadCommand
	: public BaseSSDCommand
{
public:
	ReadCommand(vector<string>commandList)
		: BaseSSDCommand(commandList) {}

protected:
	void _execute() override;
	void _parseCommand() override;
};
