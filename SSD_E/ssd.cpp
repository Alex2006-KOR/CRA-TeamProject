#include "SSD.h"

SSD::SSD() : m_stNandFile(NAND), m_stResultFile(RESULT) {
	Init();
}

void SSD::Init() {
	m_stBufferManager.ExtractWriteBufferList();
	_InitiateNandFile();
}

bool SSD::Read(int nLba) {
	vector<string> vCachedRead = m_stBufferManager.ReadFromWriteBuffer(nLba);

	if (vCachedRead.empty()) {
		_ReadFromNandFile(nLba);
	}
	else {
		_UpdateResultFile(vCachedRead);
	}


	return true;
}

bool SSD::Write(int nLba, string sData) {
	m_stBufferManager.AddWriteBuffer("W", to_string(nLba), sData);
	m_stBufferManager.OptimizeWriteBuffer();
	if (m_stBufferManager.GetWriteBufferSize() >= MAX_WRITE_BUFFER_NUM) Flush();

	return true;
}

bool SSD::Erase(int nLba, int nSize) {
	m_stBufferManager.AddWriteBuffer("E", to_string(nLba), to_string(nSize));
	m_stBufferManager.OptimizeWriteBuffer();
	if (m_stBufferManager.GetWriteBufferSize() >= MAX_WRITE_BUFFER_NUM) Flush();

	return true;
}

bool SSD::Flush() {
	for (int nWriteBufferIndex = 0; nWriteBufferIndex < m_stBufferManager.GetWriteBufferSize(); nWriteBufferIndex++) {
		vector<string> vWriteBufferTrimWords = m_stBufferManager.GetCmdInBuffer(nWriteBufferIndex);

		string sCmd = vWriteBufferTrimWords[0];
		if (sCmd == "W") {
			int nLineLba = stoi(vWriteBufferTrimWords[1]);
			string sData = vWriteBufferTrimWords[2];
			_WriteToNandFile(nLineLba, sData);
		}
		if (sCmd == "E") {
			int nStartLba = stoi(vWriteBufferTrimWords[1]);
			int nLbaSize = stoi(vWriteBufferTrimWords[2]);
			_EraseToNandFile(nStartLba, nLbaSize);
		}
	}

	m_stBufferManager.ClearWriteBuffer();
	return true;
}

void SSD::_EraseToNandFile(int nLba, int nSize) {
	vector<string> vLines = _ExtractNandValue();

	for (int lineNum = nLba; lineNum < nLba + nSize; lineNum++) {
		vLines[lineNum] = INITIAL_VALUE;
	}

	_UpdateNandValues(vLines);
}

void SSD::_WriteToNandFile(int nLba, string sData)
{
	vector<string> vLines = _ExtractNandValue();
	vLines[nLba] = sData;
	_UpdateNandValues(vLines);
}

void SSD::_InitiateNandFile()
{
	if (m_stNandFile.IsFileExist()) return;

	try {
		m_stNandFile.OpenWriteStream();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	for (int lineNum = 0; lineNum < LBA_NUM; lineNum++) {
		m_stNandFile.Write(INITIAL_VALUE);
	}

	m_stNandFile.CloseWriteStream();
}

void SSD::_ReadFromNandFile(int nLba)
{
	try {
		m_stNandFile.OpenReadStream();
		m_stResultFile.OpenWriteStream();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	int nLineIdx = 0;
	string sData;

	while (nLineIdx != nLba) {
		m_stNandFile.Read();
		++nLineIdx;
	}
	sData = m_stNandFile.Read();
	m_stResultFile.Write(sData);

	m_stNandFile.CloseReadStream();
	m_stResultFile.CloseWriteStream();
}

void SSD::_UpdateResultFile(vector<string> vWriteBufferTrimWords) {
	try {
		m_stResultFile.OpenWriteStream();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	string sCmd = vWriteBufferTrimWords[0];

	if (sCmd == "W") m_stResultFile.Write(vWriteBufferTrimWords[2]);
	if (sCmd == "E") m_stResultFile.Write(INITIAL_VALUE);

	m_stResultFile.CloseWriteStream();
}

void SSD::_UpdateNandValues(vector<string>& vLines) {
	try {
		m_stNandFile.OpenWriteStream();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	for (const auto& line : vLines) {
		m_stNandFile.Write(line);
	}

	m_stNandFile.CloseWriteStream();
}

vector<string> SSD::_ExtractNandValue(void) {
	vector<string> vLines;
	string sLine;

	try {
		m_stNandFile.OpenReadStream();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	for (int lineNum = 0; lineNum < LBA_NUM; lineNum++) {
		vLines.push_back(m_stNandFile.Read());
	}

	m_stNandFile.CloseReadStream();

	return vLines;
}