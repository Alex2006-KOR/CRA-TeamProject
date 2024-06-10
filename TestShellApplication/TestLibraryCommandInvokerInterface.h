#pragma once

#include "TestLibraryInterface.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

#define interface struct

interface TestLibCommandInvokerdInterface
{
public:
	virtual ~TestLibCommandInvokerdInterface() {}

public:
	virtual TestLibrary* GetFunction(string strCommand) = 0;
	virtual bool Run(TestLibrary* stFunction, const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") = 0;

};
