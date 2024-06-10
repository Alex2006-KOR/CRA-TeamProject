#pragma once
#include <string>

using namespace std;

class SSDInterface {
public:
	virtual bool Read(int nLba) = 0;
	virtual bool Write(int nLba, string sData) = 0;
	virtual bool Erase(int nLba, int nSize) = 0;
};