#include "SSD.h"

SSD::SSD() : m_stNandFile(NAND), m_stResultFile(RESULT), m_stWriteBufferFile(WRITE_BUFFER) {
	Init();
}

void SSD::Init() {
	_ExtractWriteBufferList();
	_InitiateNandFile();
}

bool SSD::Read(int nLba) {
	if (_ReadFromWriteBuffer(nLba)) return true;
	_ReadFromNandFile(nLba);

	return true;
}

bool SSD::Write(int nLba, string sData) {
	vector<string> vLines = _ExtractNandValue();
	vLines[nLba] = sData;
	_UpdateNandValues(vLines);

	return true;
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

void SSD::_ExtractWriteBufferList()
{
	try {
		m_stWriteBufferFile.OpenReadStream();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	string sData;
	for (int lineNum = 0; lineNum < MAX_WRITE_BUFFER_NUM; lineNum++) {
		string sData = m_stWriteBufferFile.Read();
		if (sData == "") break;
		m_vWriteBufferList.push_back(sData);
	}

	m_stWriteBufferFile.CloseReadStream();
}

bool SSD::_ReadFromWriteBuffer(int nLba)
{
	for (int nWriteBufferIndex = m_vWriteBufferList.size() - 1; nWriteBufferIndex >= 0; --nWriteBufferIndex) {
		string sFullCommand = m_vWriteBufferList[nWriteBufferIndex];
		vector<string> vWriteBufferTrimWords = _TrimFullCommand(sFullCommand);

		if (_IsExistLbaInWriteBuffer(vWriteBufferTrimWords, nLba)) {
			_UpdateResultFile(vWriteBufferTrimWords, nLba);
			return true;
		}
	}
	return false;
}

void SSD::_UpdateResultFile(vector<string> vWriteBufferTrimWords, int nLba) {
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

bool SSD::_IsExistLbaInWriteBuffer(vector<string> vWriteBufferTrimWords, int nLba) {
	string sCmd = vWriteBufferTrimWords[0];
	if (sCmd == "W") {
		int nLineLba = stoi(vWriteBufferTrimWords[1]);
		if (nLineLba == nLba) return true;
	}
	if (sCmd == "E") {
		int nStartLba = stoi(vWriteBufferTrimWords[1]);
		int nLbaNum = stoi(vWriteBufferTrimWords[2]);
		if (nLba >= nStartLba && nLba < (nStartLba + nLbaNum)) return true;
	}

	return false;
}

vector<string> SSD::_TrimFullCommand(string sFullCommand) {
	vector<string> vWriteBufferTrimWords{};

	int pos = 0;
	string spaceDelimiter = " ";
	while ((pos = sFullCommand.find(spaceDelimiter)) != string::npos) {
		vWriteBufferTrimWords.push_back(sFullCommand.substr(0, pos));
		sFullCommand.erase(0, pos + spaceDelimiter.length());
	}
	vWriteBufferTrimWords.push_back(sFullCommand);

	return vWriteBufferTrimWords;
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

bool SSD::Erase(int nLba, int nSize) {
	vector<string> vLines = _ExtractNandValue();

	for (int lineNum = nLba; lineNum < nLba + nSize; lineNum++) {
		vLines[lineNum] = INITIAL_VALUE;
	}

	_UpdateNandValues(vLines);

	return true;
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