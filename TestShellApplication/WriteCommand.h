#pragma once
#include "SSDCommand.h"

class WriteCommand
	: public BaseSSDCommand
{
public:
	WriteCommand(vector<string>commandList)
		: BaseSSDCommand(commandList) {}

protected:
	void _execute() override;
	void _parseCommand() override;
};
