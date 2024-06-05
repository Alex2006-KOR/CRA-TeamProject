#pragma once
#include <string>
#include <fstream>

using namespace std;

class FileManager {
public:
	FileManager(string sFileName) :
		m_sFileName(sFileName) {}

	void OpenReadStream() {
		m_ifstreamRead.open(m_sFileName);

		if (m_ifstreamRead.is_open() == false) {
			throw exception("Open input file fail");
		}
	}

	void OpenWriteStream() {
		m_ofstreamWrite.open(m_sFileName);

		if (m_ofstreamWrite.is_open() == false) {
			throw exception("Open input file fail");
		}
	}

	void CloseReadStream() {
		m_ifstreamRead.close();
	}

	void CloseWriteStream() {
		m_ofstreamWrite.close();
	}

	bool IsFileExist() {
		m_ifstreamRead.open(m_sFileName);

		if (m_ifstreamRead.good()) {
			m_ifstreamRead.close();

			return true;
		}
		m_ifstreamRead.close();

		return false;
	}

	string Read() {
		string sData;
		getline(m_ifstreamRead, sData);
		
		return sData;
	}

	void Write(string sData) {
		m_ofstreamWrite << sData << std::endl;
	}

private:
	string m_sFileName;
	ifstream m_ifstreamRead;
	ofstream m_ofstreamWrite;
};