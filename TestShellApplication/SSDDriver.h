#pragma once
#include "DriverInterface.h"

class SSDDriver : public DriverInterface {
public:
	int Read(int lba) override;
	void Write(int lba, int data) override;

protected:
	virtual int _executeCommand(std::string command);
	virtual bool _getSsdExisted(void);
	virtual int _getSsdResult(void);
	virtual int _getReadResult(void);
};