#pragma once
#include "CommandInterface.h"
#include "DriverInterface.h"
#include <vector>

using namespace std;

class EraseCommand
	: public NonDataCommand, public LbaArgument, public BlkCntArgument
{
public:
	EraseCommand(DriverInterface* pstDriver);
	EraseCommand& setLBA(string strLba) override;
	EraseCommand& setBlkCnt(string strData) override;
	void execute() override;

	bool CheckArgCnt(vector<string> vArgs) const override;

private:
	DriverInterface* m_pstDriver;
	vector<string> m_vArguemnts;
	int m_nLBA;
	int m_nBlkCnt;

	const int REQUIRED_COMMAND_COUNT = 2;
	const int REQUIRED_DATA_LENGTH = 10;

	void _checkLBAFormat(string strLBA) override;
	void _updateLBA(string strLBA) override;
	void _checkLBARange() override;


	void _checkLBAIsValid() override;
	void _checkBlkCntFormat(std::string strLBA) override;
	void _updateBlkCnt(std::string strBlkCnt) override;
	void _checkBlkRange() override;
};
