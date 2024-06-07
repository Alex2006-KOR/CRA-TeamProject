#pragma once

#include <string>
using std::string;

class Logger
{
public:
	Logger() = default;
	virtual ~Logger() = default;

public:
	void print(string msg, string strCallerName);
};
