#pragma once
#include "CommandInterface.h"
#include "DriverInterface.h"
#include <vector>

using namespace std;

class ReadCommand
	: public DataCommand, public LbaArgument
{
public:
	ReadCommand(DriverInterface* pstDriver);
	ReadCommand& setLBA(string strLba) override;
	string execute() override;

	bool CheckArgCnt(vector<string> vArgs) const override;

private:
	DriverInterface* m_pstDriver;
	vector<string> m_vArguemnts;
	int m_nLBA;

	const int REQUIRED_COMMAND_COUNT = 1;

	void _checkLBAFormat(string strLBA) override;
	void _updateLBA(string strLBA) override;
	void _checkLBARange() override;
};
