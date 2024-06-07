#include "SSD.h"

SSD::SSD() : m_stNandFile(NAND), m_stResultFile(RESULT) {
	Init();
}

void SSD::Init() {
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

bool SSD::Read(int nLba) {
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

	return true;
}

bool SSD::Write(int nLba, string sData) {
	vector<string> vLines = _ExtractNandValue();
	vLines[nLba] = sData;
	_UpdateNandValues(vLines);

	return true;
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