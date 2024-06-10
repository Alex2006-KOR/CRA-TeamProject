#pragma once

#define interface struct

interface TestScriptInterface {
public:
	virtual ~TestScriptInterface() {}

public:
	virtual void Run() = 0;
};
