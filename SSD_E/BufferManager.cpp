#include "BufferManager.h"

using namespace std;

BufferManager::BufferManager() :
	m_stWriteBufferFile(WRITE_BUFFER) {
	ExtractWriteBufferList();
};

void BufferManager::ExtractWriteBufferList()
{
	try {
		m_stWriteBufferFile.OpenReadStream();
		m_vWriteBufferList.clear();
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

vector<string> BufferManager::_TrimFullCommand(string sFullCommand) {
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

vector<string> BufferManager::ReadFromWriteBuffer(int nLba)
{
	vector<string> vEmptyResult;

	for (int nWriteBufferIndex = m_vWriteBufferList.size() - 1; nWriteBufferIndex >= 0; --nWriteBufferIndex) {
		string sFullCommand = m_vWriteBufferList[nWriteBufferIndex];
		vector<string> vWriteBufferTrimWords = _TrimFullCommand(sFullCommand);

		if (_IsExistLbaInWriteBuffer(vWriteBufferTrimWords, nLba)) {
			return vWriteBufferTrimWords;
		}
	}
	return vEmptyResult;
}

void BufferManager::AddWriteBuffer(string sCmd, string sParam1, string sParam2) {
	string sWriteBufferInput = sCmd + " " + sParam1 + " " + sParam2;

	try {
		m_stWriteBufferFile.OpenWriteStream("append");
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	m_stWriteBufferFile.Write(sWriteBufferInput);
	m_vWriteBufferList.push_back(sWriteBufferInput);

	m_stWriteBufferFile.CloseWriteStream();
}

void BufferManager::OptimizeWriteBuffer() {
	int	 nLastIndex = m_vWriteBufferList.size() - 1;
	if (nLastIndex == 0) return;

	vector<string> vSearchCommandWords = GetCmdInBuffer(nLastIndex);
	
	if (vSearchCommandWords[0] == "W") {
		for (int nIndex = nLastIndex - 1; nIndex >= 0; nIndex--) {
			vector<string> vCompareCommandWords = GetCmdInBuffer(nIndex);
			int nSearchLba = stoi(vSearchCommandWords[1]);
			string nCompareCmd = vCompareCommandWords[0];
			int nCompareLba = stoi(vCompareCommandWords[1]);
			
			if (nCompareCmd == "W" && nCompareLba == nSearchLba) {
				m_vWriteBufferList.erase(m_vWriteBufferList.begin() + nIndex);
			}
		}
	}
	else if (vSearchCommandWords[0] == "E") {
		for (int nIndex = nLastIndex - 1; nIndex >= 0; nIndex--) {
			vector<string> vCompareCommandWords = GetCmdInBuffer(nIndex);
			int nSearchStartLba = stoi(vSearchCommandWords[1]);
			int nSearchLbaSize = stoi(vSearchCommandWords[2]);
			int nSearchEndLba = nSearchStartLba + nSearchLbaSize - 1;

			string nCompareCmd = vCompareCommandWords[0];
			int nCompareLba = stoi(vCompareCommandWords[1]);

			if (nCompareCmd == "W" && nSearchStartLba <= nCompareLba && nSearchEndLba >= nCompareLba) {
				m_vWriteBufferList.erase(m_vWriteBufferList.begin() + nIndex);
				continue;
			}

			if (nIndex != nLastIndex - 1) continue;

			// 제약사항. 연속된 Erase만 검사한다.
			if (nCompareCmd == "E") {
				int nCompareStartLba = nCompareLba;
				int nCompareLbaSize = stoi(vSearchCommandWords[2]);
				int nCompareEndLba = nCompareStartLba + nCompareLbaSize - 1;

				if ((nCompareStartLba <= nSearchStartLba && nSearchStartLba <= nCompareEndLba) ||
					(nSearchStartLba <= nCompareStartLba && nCompareStartLba <= nSearchEndLba)) {
					int nNewStartLba = min(nSearchStartLba, nCompareStartLba);
					int nNewEndLba = max(nSearchEndLba, nCompareEndLba);
					int nNewLbaSize = nNewEndLba - nNewStartLba + 1;
					string sInputString = "E " + to_string(nNewStartLba) + " " + to_string(nNewLbaSize);
					m_vWriteBufferList.erase(m_vWriteBufferList.begin() + nIndex);
					m_vWriteBufferList.pop_back();
					m_vWriteBufferList.push_back(sInputString);

				}
			}
		}
	}

	// 새로 write
	try {
		m_stWriteBufferFile.OpenWriteStream("trunc");
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	for (const auto& sElement : m_vWriteBufferList) {	
		m_stWriteBufferFile.Write(sElement);
	}

	m_stWriteBufferFile.CloseWriteStream();
}

int BufferManager::GetWriteBufferSize() {
	return m_vWriteBufferList.size();
}

bool BufferManager::_IsExistLbaInWriteBuffer(vector<string> vWriteBufferTrimWords, int nLba) {
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



vector<string> BufferManager::GetCmdInBuffer(int nWriteBufferIndex)
{
	string sFullCommand = m_vWriteBufferList[nWriteBufferIndex];
	return _TrimFullCommand(sFullCommand);
}

void BufferManager::ClearWriteBuffer() {
	try {
		m_stWriteBufferFile.OpenWriteStream("trunc");
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	m_vWriteBufferList.clear();

	m_stWriteBufferFile.CloseWriteStream();
}
