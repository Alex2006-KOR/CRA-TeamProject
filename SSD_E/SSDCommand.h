#pragma once
#include "SSDInterface.h"

class Command {
public:
	virtual bool ExecuteCmd(SSDInterface *pstSSDInterface) = 0;
};

class ReadCommand : public Command {
public:
	ReadCommand(int nLba);
	bool ExecuteCmd(SSDInterface* pstSSDInterface) override;

private:
	int m_nLba;
};

class WriteCommand : public Command {
public:
	WriteCommand(int nLba, string sData);
	bool ExecuteCmd(SSDInterface* pstSSDInterface) override;

private:
	int m_nLba;
	string m_sData;
};