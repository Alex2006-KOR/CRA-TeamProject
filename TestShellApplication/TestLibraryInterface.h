#pragma once

#define interface struct

#include <string>
#include <vector>

using std::string;
using std::vector;

interface TestLibrary {
public:
	virtual ~TestLibrary() {}

public:
	virtual bool execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const = 0;
};
