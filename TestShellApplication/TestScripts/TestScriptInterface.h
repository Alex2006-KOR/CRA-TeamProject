#pragma once

#define interface struct

interface TestScriptInterface {
public:
	virtual ~TestScriptInterface() {}

public:
	virtual void Run() = 0;
	virtual string Name() = 0;
	virtual bool Verdict() = 0;
};
