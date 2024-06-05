#pragma once
#include "DriverInterface.h"

class SSDDriver : public DriverInterface {
public:
	int Read(int lba) override;
	void Write(int lba, int data) override;

protected:
	virtual int _executeCommand(std::string command);

};