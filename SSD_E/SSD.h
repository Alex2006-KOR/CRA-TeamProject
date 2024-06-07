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
	const string WRITE_BUFFER = "WriteBuffer.txt";
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
	FileManager m_stWriteBufferFile;
	vector<string> m_vWriteBufferList;

	// init
	void _InitiateNandFile();
	void _ExtractWriteBufferList();
	
	// read
	bool _ReadFromWriteBuffer(int nLba);
	void _ReadFromNandFile(int nLba);
	vector<string> _TrimFullCommand(string sFullCommand);
	bool _IsExistLbaInWriteBuffer(vector<string> vWriteBufferTrimWords, int nLba);
	void _UpdateResultFile(vector<string> vWriteBufferTrimWords, int nLba);
	
	// write, erase
	void _WriteToNandFile(int nLba, string sData);
	void _AddWriteBuffer(string sCmd, int nLba, string sData);
	void _OptimizeWriteBuffer();
	void _UpdateNandValues(vector<string>& vLines);
	vector<string> _ExtractNandValue(void);
	
	// flush
	void _FlushWriteBuffer();
	void _ClearWriteBuffer();
};
