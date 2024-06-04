#pragma once
#include "SSDCommand.h"

class WriteCommand
	: public BaseSSDCommand
{
public:
	WriteCommand(vector<string>commandList)
		: BaseSSDCommand(commandList) {}

public:
	void Execute() override;

protected:
	void parseCommand() override;
};
