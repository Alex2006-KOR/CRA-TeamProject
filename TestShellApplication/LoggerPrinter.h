#pragma once

#include <string>
using std::string;

#define interface struct

interface LoggerPrinter
{
public:
	virtual ~LoggerPrinter() {}

public:
	virtual void Print(string strMessage, string strCallerName) = 0;
};
