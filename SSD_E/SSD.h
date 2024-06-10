#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "BufferManager.h"
#include "SSDInterface.h"
#include "FileManager.h"

using namespace std;

class SSD : public SSDInterface {
public:
	const string RESULT = "result.txt";
	const string NAND = "nand.txt";
	const string INITIAL_VALUE = "0x00000000";
	const int LBA_NUM = 100;
	const int MAX_WRITE_BUFFER_NUM = 10;

	SSD();

	void Init();
	bool Read(int nLba) override;
	bool Write(int nLba, string sData) override;
	bool Erase(int nLba, int nSize) override;
	bool Flush() override;


private:
	FileManager m_stNandFile;
	FileManager m_stResultFile;
	BufferManager m_stBufferManager;

	// init
	void _InitiateNandFile();
	
	// read
	void _ReadFromNandFile(int nLba);
	void _UpdateResultFile(vector<string> vWriteBufferTrimWords);
	
	// write, erase
	void _WriteToNandFile(int nLba, string sData);
	void _EraseToNandFile(int nLba, int nSize);
	void _UpdateNandValues(vector<string>& vLines);
	vector<string> _ExtractNandValue(void);
	
};
