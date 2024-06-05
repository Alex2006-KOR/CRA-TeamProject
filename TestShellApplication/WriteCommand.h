#pragma once
#include "SSDCommand.h"

class WriteCommand
	: public BaseSSDCommand
{
public:
	WriteCommand(vector<string>commandList)
		: BaseSSDCommand(commandList) {}

protected:
	bool _parseCommand() override;
	void _execute() override;
};
