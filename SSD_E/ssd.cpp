#include <iostream>
#include <fstream>
#include <vector>

#include "ssd_interface.h"
#include "FileManager.cpp"

using namespace std;

class SSD: public SSDInterface {
public:
	const string RESULT = "result.txt";
	const string NAND = "nand.txt";
	const string INITIAL_VALUE = "0x00000000";
	const int LBA_NUM = 100;

	SSD(): m_stNandFile(NAND), m_stResultFile(RESULT) {
		init();
	}

	void init() {
		if (m_stNandFile.IsFileExist()) return;

		try {
			m_stNandFile.OpenWriteStream();
		} catch (exception e) {
			cout << e.what() << endl;
		}

		for (int lineNum = 0; lineNum < LBA_NUM; lineNum++) {
			m_stNandFile.Write(INITIAL_VALUE);
		}

		m_stNandFile.CloseWriteStream();
	}

	bool read(int nLba) {
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

	bool write(int nLba, string sData) {
		vector<string> vLines = _ExtractNandValue();
		vLines[nLba] = sData;
		_UpdateNandValues(vLines);

		return true;
	}

private:
	FileManager m_stNandFile;
	FileManager m_stResultFile;

	void _UpdateNandValues(vector<string>& vLines)
	{
		try {
			m_stNandFile.OpenWriteStream();
		} catch (exception e) {
			cout << e.what() << endl;
		}

		for (const auto& line : vLines) {
			m_stNandFile.Write(line);
		}

		m_stNandFile.CloseWriteStream();
	}

	vector<string> _ExtractNandValue(void)
	{
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
};