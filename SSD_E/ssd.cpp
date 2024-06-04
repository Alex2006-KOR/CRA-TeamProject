#include <fstream>
#include <vector>
#include "ssd_interface.h"

using namespace std;

class SSD: public SSDInterface {
	const string RESULT = "result.txt";
	const string NAND = "nand.txt";

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
			}
			++nLineIdx;
		}

		return true;
	}

	bool write(int nLba, string sData) {
		fstream fstreamReadWrite(NAND, ios::in | ios::out);
		if (fstreamReadWrite.is_open() == false) throw exception("Open file fail");

		vector<string> vLines;
		string sLine;

		while (getline(fstreamReadWrite, sLine)) {
			vLines.push_back(sLine);
		}

		fstreamReadWrite.close();

		vLines[nLba] = sData;

		for (const auto& line : vLines) {
			fstreamReadWrite << line << std::endl;
		}

		return true;
	}
};