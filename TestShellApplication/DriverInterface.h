#pragma once

#define Interface struct

Interface DriverInterface{
public:
	virtual int Read(int lba) = 0;
	virtual void Write(int lba, int data) = 0;
};