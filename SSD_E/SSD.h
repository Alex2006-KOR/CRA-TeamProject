#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "SSDInterface.h"
#include "FileManager.h"

using namespace std;

class SSD : public SSDInterface {
public:
	const string RESULT = "result.txt";
	const string NAND = "nand.txt";
	const string INITIAL_VALUE = "0x00000000";
	const int LBA_NUM = 100;

	SSD();

	void Init();
	bool Read(int nLba) override;
	bool Write(int nLba, string sData) override;

private:
	FileManager m_stNandFile;
	FileManager m_stResultFile;

	void _UpdateNandValues(vector<string>& vLines);
	vector<string> _ExtractNandValue(void);

};