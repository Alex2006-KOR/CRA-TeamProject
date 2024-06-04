#pragma once

#include "DriverInterface.h"

#include <iostream>

class Shell
{
public:
	Shell(DriverInterface* pSSDDriver);

public:
	void Run(std::istream& input, std::ostream& output);
};

