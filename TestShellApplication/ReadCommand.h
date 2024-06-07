#pragma once
#include "SSDCommand.h"
#include "DriverInterface.h"

class ReadCommand
	: public BaseSSDCommand
{
public:
	ReadCommand(DriverInterface* pSSDDriver, std::ostream& output);

protected:
	bool _parseCommand() override;
	bool _checkValidityLBA();
	bool _hasEnoughArgs();
	bool _isValidFormat();
	void _updateLBA();
	bool _isLBAInRange();
	void _execute() override;

private:
	DriverInterface* m_pstSSDDriver;

	const int m_nExpectedArgCnt = 1;
	
	int m_nLBA;
};
