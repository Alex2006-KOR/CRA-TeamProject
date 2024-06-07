#include "TestLibrary.h"

TestLibrary* TestLibrary::m_Instance = nullptr;

TestLibrary* TestLibrary::GetLibrary(DriverInterface* pstDriver, ostream* output)
{
	if (m_Instance == nullptr) m_Instance = new TestLibrary();
	if (pstDriver != nullptr) m_Instance->m_pstDriver = new Device(pstDriver);
	if (output != nullptr) m_Instance->m_out = output;
	return m_Instance;
}

void TestLibrary::Write(vector<string> vCommandList)
{
	try {
		m_pstDriver->Write(vCommandList);
	}
	catch (exception e) {
		*m_out << e.what() << endl;
	}
}

void TestLibrary::Read(vector<string> vCommandList)
{
	string ret;
	try {
		ret = m_pstDriver->Read(vCommandList);
	}
	catch (exception e) {
		ret = e.what();
	}
	*m_out << ret << endl;
}

void TestLibrary::FullWrite(vector<string> vCommandList)
{
	vCommandList.insert(vCommandList.begin(), "DummyLBA");
	for (int nLBA = m_pstDriver->GetMinLba(); nLBA < m_pstDriver->GetMaxLba(); nLBA++) {

		try {
			vCommandList[0] = to_string(nLBA);
			m_pstDriver->Write(vCommandList);
		}
		catch (exception e) {
			*m_out << e.what() << endl;
			return;
		}
	}
}

void TestLibrary::FullRead(string strExpected)
{
	string ret;
	for (int nLBA = m_pstDriver->GetMinLba(); nLBA < m_pstDriver->GetMaxLba(); nLBA++) {
		try {
			ret = m_pstDriver->Read({ to_string(nLBA) });
			if (strExpected.size() == 10 && ret != strExpected)
				throw runtime_error("Data Mismatch!!");
			*m_out << ret << endl;
		}
		catch (exception e) {
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
			m_pstDriver->Write({to_string(nLBA), strData});
		}
		catch (exception e) {
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
			ret = m_pstDriver->Read({ to_string(nLBA) });
			if (strExpected.size() == 10 && ret != strExpected)
				throw runtime_error("Data Mismatch!!");
			*m_out << ret << endl;
		}
		catch (exception e) {
			*m_out << e.what() << endl;
			return;
		}
	}
}

TestLibrary::~TestLibrary()
{
}


TestLibrary::TestLibrary()
{
}
