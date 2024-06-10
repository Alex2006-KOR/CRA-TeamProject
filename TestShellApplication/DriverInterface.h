#pragma once
#include <string>

#define Interface struct

Interface DriverInterface{
public:
	virtual void Read(int lba) = 0;
	virtual void Write(int lba, int data) = 0;
	virtual std::string ReadBuffer() = 0;

	virtual int GetMinLba() = 0;
	virtual int GetMaxLba() = 0;
};