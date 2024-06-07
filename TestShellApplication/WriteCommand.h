#pragma once
#include "DriverInterface.h"
#include <vector>

using namespace std;

class WriteCommand
{
public:
	WriteCommand(DriverInterface* pstDriver);
	WriteCommand& setLBA(string strLba);
	WriteCommand& setData(string strData);
	void execute();

	bool CheckArgCnt(vector<string> vArgs) const;

private:
	DriverInterface* m_pstDriver;
	vector<string> m_vArguemnts;
	int m_nLBA;
	int m_nData;

	const int REQUIRED_COMMAND_COUNT = 2;
	const int REQUIRED_DATA_LENGTH = 10;

	void _checkValidLBAFormat(string strLBA);
	void _updateLBA(string strLBA);
	void _checkLBARange();

	void _updateData(std::string& strData);
	void _checkSpelling(std::string& strData);
	void _checkDataFormat(std::string& strData) const;
};
