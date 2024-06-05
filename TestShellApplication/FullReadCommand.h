#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class FullReadCommand
	: public BaseSSDCommand
{
public:
	FullReadCommand(vector<string>commandList, DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;

private:
	DriverInterface* m_pstSSDDriver;

	string m_sData;
};
