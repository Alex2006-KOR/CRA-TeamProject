#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class WriteCommand
	: public BaseSSDCommand
{
public:
	WriteCommand(vector<string>commandList, DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	void _execute() override;

private:
	int _checkAndGetLBA(string paramString);
	int _checkAndGetData(string paramString);

private:
	DriverInterface* m_pstSSDDriver;

	int m_nLBA;
	int m_nData;
};
