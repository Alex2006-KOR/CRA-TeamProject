#pragma once
#include "CommandInterface.h"
#include "DriverInterface.h"
#include <vector>

using namespace std;

class FlushCommand
	: public NonDataCommand
{
public:
	FlushCommand(DriverInterface* pstDriver);
	void execute() override;

	bool CheckArgCnt(vector<string> vArgs) const override;

private:
	DriverInterface* m_pstDriver;
	vector<string> m_vArguemnts;

	const int REQUIRED_COMMAND_COUNT = 0;
};