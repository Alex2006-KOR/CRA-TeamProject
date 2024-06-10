#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

#include "FileManager.h"

class BufferManager {
public:
	const int MAX_WRITE_BUFFER_NUM = 10;
	string WRITE_BUFFER = "WriteBuffer.txt";

	BufferManager();
	void ExtractWriteBufferList();
	vector<string> ReadFromWriteBuffer(int nLba);
	void AddWriteBuffer(string sCmd, string sParam1, string sParam2);
	void OptimizeWriteBuffer();
	int GetWriteBufferSize();
	vector<string> GetCmdInBuffer(int nWriteBufferIndex);
	void ClearWriteBuffer();

private:
	FileManager m_stWriteBufferFile;
	vector<string> m_vWriteBufferList;

	vector<string> _TrimFullCommand(string sFullCommand);
	bool _IsExistLbaInWriteBuffer(vector<string> vWriteBufferTrimWords, int nLba);
};