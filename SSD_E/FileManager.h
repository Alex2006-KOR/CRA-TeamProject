#pragma once
#include <string>
#include <fstream>

using namespace std;

class FileManager {
public:
	FileManager(string sFileName);

	void OpenReadStream();
	void OpenWriteStream();
	void CloseReadStream();
	void CloseWriteStream();
	bool IsFileExist();
	string Read();
	void Write(string sData);

private:
	string m_sFileName;
	ifstream m_ifstreamRead;
	ofstream m_ofstreamWrite;
};