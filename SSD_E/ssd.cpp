#include <fstream>
#include <vector>
#include "ssd_interface.h"

using namespace std;

class SSD: public SSDInterface {
public:
	const string RESULT = "result.txt";
	const string NAND = "nand.txt";
	const string INITIAL_VALUE = "0x00000000";
	const int LBA_NUM = 100;

	SSD() {
		init();
	}

	void init() {
		if (_IsFileExist()) return;

		ofstream ofstreamWrite(NAND);
		if (ofstreamWrite.is_open() == false) throw exception("Open output file fail");
		for (int lineNum = 0; lineNum < LBA_NUM; lineNum++) {
			ofstreamWrite << INITIAL_VALUE << std::endl;
		}
		ofstreamWrite.close();
	}

	bool read(int nLba) {
		ifstream ifstreamRead(NAND);
		ofstream ofstreamWrite(RESULT);

		if (ifstreamRead.is_open() == false) throw exception("Open input file fail");
		if (ofstreamWrite.is_open() == false) throw exception("Open output file fail");

		int nLineIdx = 0;
		string sData;

		while (getline(ifstreamRead, sData)) {
			if (nLineIdx == nLba) {
				ofstreamWrite << sData << std::endl;
				ifstreamRead.close();
				ofstreamWrite.close();
				return true;
			}
			++nLineIdx;
		}

		ifstreamRead.close();
		ofstreamWrite.close();
		return false;
	}

	bool write(int nLba, string sData) {
		vector<string> vLines = _ExtractNandValue();
		vLines[nLba] = sData;
		_UpdateNandValues(vLines);

		return true;
	}

private:
	void _UpdateNandValues(vector<string>& vLines)
	{
		ofstream ofstreamWrite(NAND);
		if (ofstreamWrite.is_open() == false) throw exception("Open output file fail");
		for (const auto& line : vLines) {
			ofstreamWrite << line << std::endl;
		}
		ofstreamWrite.close();
	}

	vector<string> _ExtractNandValue(void)
	{
		vector<string> vLines;
		string sLine;

		ifstream ifstreamRead(NAND);
		if (ifstreamRead.is_open() == false) throw exception("Open input file fail");

		while (getline(ifstreamRead, sLine)) {
			vLines.push_back(sLine);
		}

		ifstreamRead.close();

		return vLines;
	}

	bool _IsFileExist(void) {
		ifstream ifstreamRead(NAND);

		if (ifstreamRead.good()) {
			ifstreamRead.close();

			return true;
		}
		ifstreamRead.close();

		return false;
	}
};