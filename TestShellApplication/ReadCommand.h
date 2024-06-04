#pragma once
#include "SSDCommand.h"

class ReadCommand
	: public BaseSSDCommand
{
public:
	ReadCommand(vector<string>commandList)
		: BaseSSDCommand(commandList) {}

public:
	void Execute() override;

protected:
	void parseCommand() override;
};
