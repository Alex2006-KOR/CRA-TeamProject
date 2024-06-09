#pragma once
#include <string>

#define Interface struct

Interface DriverInterface{
public:
	virtual void Read(int nLba) = 0;
	virtual void Write(int nLba, int nData) = 0;
	virtual void Erase(int nLba, int nBlkCnt) = 0;
	virtual std::string ReadBuffer() = 0;

	virtual int GetMinLba() = 0;
	virtual int GetMaxLba() = 0;
};