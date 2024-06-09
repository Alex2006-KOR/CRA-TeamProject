#include "TestLibrary.h"
#include "ShellException.h"

TestLibrary* TestLibrary::m_Instance = nullptr;

TestLibrary* TestLibrary::GetLibrary(DriverInterface* pstDriver, ostream* output)
{
	if (m_Instance == nullptr) m_Instance = new TestLibrary();
	if (pstDriver != nullptr) m_Instance->m_pstDevice = new Device(pstDriver);
	if (output != nullptr) m_Instance->m_out = output;
	return m_Instance;
}

void TestLibrary::Write(vector<string> vCommandList)
{
	try {
		m_pstDevice->Write(vCommandList);
	}
	catch (exception& e) {
		*m_out << e.what() << endl;
	}
}

void TestLibrary::Read(vector<string> vCommandList)
{
	string ret;
	try {
		ret = m_pstDevice->Read(vCommandList);
	}
	catch (exception& e) {
		ret = e.what();
	}
	*m_out << ret << endl;
}

void TestLibrary::Erase(vector<string> vCommandList)
{
	try {
		m_pstDevice->Erase(vCommandList);
	}
	catch (exception& e) {
		*m_out << e.what() << endl;
	}
}

void TestLibrary::Flush(vector<string> vCommandList)
{
	try {
		m_pstDevice->Flush(vCommandList);
	}
	catch (exception& e) {
		*m_out << e.what() << endl;
	}
}

void TestLibrary::FullWrite(vector<string> vCommandList)
{
	vCommandList.insert(vCommandList.begin(), "DummyLBA");
	for (int nLBA = m_pstDevice->GetMinLba(); nLBA < m_pstDevice->GetMaxLba(); nLBA++) {

		try {
			vCommandList[0] = to_string(nLBA);
			m_pstDevice->Write(vCommandList);
		}
		catch (exception& e) {
			*m_out << e.what() << endl;
			return;
		}
	}
}

void TestLibrary::FullRead(string strExpected)
{
	string ret;
	for (int nLBA = m_pstDevice->GetMinLba(); nLBA < m_pstDevice->GetMaxLba(); nLBA++) {
		try {
			ret = m_pstDevice->Read({ to_string(nLBA) });
			if (strExpected.size() == 10 && ret != strExpected)
				throw runtime_error("Data Mismatch!!");
			*m_out << ret << endl;
		}
		catch (exception& e) {
			ret = e.what();
			*m_out << ret << endl;
			return;
		}
	}
}

void TestLibrary::WriteRange(int nStartLba, int nEndLba, string strData)
{
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			m_pstDevice->Write({to_string(nLBA), strData});
		}
		catch (exception& e) {
			*m_out << e.what() << endl;
			return;
		}
	}
}

void TestLibrary::ReadRange(int nStartLba, int nEndLba, string strExpected)
{
	string ret;
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			ret = m_pstDevice->Read({ to_string(nLBA) });
			if (strExpected.size() == 10 && ret != strExpected)
				throw runtime_error("Data Mismatch!!");
			*m_out << ret << endl;
		}
		catch (exception& e) {
			*m_out << e.what() << endl;
			return;
		}
	}
}

void TestLibrary::EraseRangeInString(vector<string> vCommandList)
{
	_ValidateArguemnts(vCommandList);
	EraseRange(stoi(vCommandList[0]), stoi(vCommandList[1]));
}

void TestLibrary::_ValidateArguemnts(std::vector<std::string>& vCommandList)
{
	if (vCommandList.size() < 2)
		throw invalid_argument("invalid # of args. please check help.");
	for (int nArgIndex = 0; nArgIndex < 2; nArgIndex++) {
		try {
			m_pstDevice->Erase({ vCommandList[nArgIndex], to_string(-1) });
		}
		catch (Invalid_BlockCount& e) {
			// pass
		}
	}
}

void TestLibrary::EraseRange(int nStartLba, int nEndLba)
{
	try {
		int nBlkCnt;
		while (nStartLba <= nEndLba) {
			nBlkCnt = ((nEndLba - nStartLba) > 10) ? 10 : nEndLba - nStartLba;
			m_pstDevice->Erase({ to_string(nStartLba), to_string(nBlkCnt) });
			nStartLba += nBlkCnt;
		}
	}
	catch (exception& e) {
		*m_out << e.what() << endl;
	}
}

TestLibrary::TestLibrary()
	: m_pstDevice(nullptr)
	, m_out(nullptr)
{
}

TestLibrary::~TestLibrary()
{
}
