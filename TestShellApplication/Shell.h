#pragma once

#include "DriverInterface.h"

#include <iostream>

class Shell
{
public:
	Shell(DriverInterface* pSSDDriver);

public:
	void Run(std::istream& input, std::ostream& output);

private:
	void handleCommand(std::string lineString, std::ostream& output);

private:
	DriverInterface* m_pSSDDriver;
};

