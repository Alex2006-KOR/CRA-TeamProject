#pragma once
#include "DriverInterface.h"
#include <vector>

using namespace std;

class ReadCommand
{
public:
	ReadCommand(DriverInterface* pstDriver);
	ReadCommand& setLBA(string strLba);
	string execute();

	bool CheckArgCnt(vector<string> vArgs) const;

private:
	DriverInterface* m_pstDriver;
	vector<string> m_vArguemnts;
	int m_nLBA;

	const int REQUIRED_COMMAND_COUNT = 1;

	void _checkLBAFormat(string strLBA);
	void _updateLBA(string strLBA);
	void _checkLBARange();
};
