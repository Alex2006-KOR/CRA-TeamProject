#pragma once
#include "CommandInterface.h"
#include "DriverInterface.h"
#include <vector>

using namespace std;

class WriteCommand
	: public NonDataCommand, public LbaArgument, public DataArguement
{
public:
	WriteCommand(DriverInterface* pstDriver);
	WriteCommand& setLBA(string strLba) override;
	WriteCommand& setData(string strData) override;
	void execute() override;

	bool CheckArgCnt(vector<string> vArgs) const override;

private:
	DriverInterface* m_pstDriver;
	vector<string> m_vArguemnts;
	int m_nLBA;
	int m_nData;

	const int REQUIRED_COMMAND_COUNT = 2;
	const int REQUIRED_DATA_LENGTH = 10;

	void _checkLBAFormat(string strLBA) override;
	void _updateLBA(string strLBA) override;
	void _checkLBARange() override;

	void _updateData(std::string& strData) override;
	void _checkSpelling(std::string& strData) override;
	void _checkDataFormat(std::string& strData) const override;
};
