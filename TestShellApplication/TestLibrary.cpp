#include "TestLibrary.h"

#include "Logger.h"

TestLibrary* TestLibrary::m_Instance = nullptr;

TestLibrary* TestLibrary::GetLibrary(DriverInterface* pstDriver)
{
	if (m_Instance == nullptr) m_Instance = new TestLibrary();
	if (pstDriver != nullptr) m_Instance->m_pstDevice = new Device(pstDriver);
	return m_Instance;
}

void TestLibrary::Write(vector<string> vCommandList)
{
	try {
		m_pstDevice->Write(vCommandList);
	}
	catch (exception e) {
		LOG(e.what());
	}
}

void TestLibrary::Read(vector<string> vCommandList)
{
	string ret;
	try {
		ret = m_pstDevice->Read(vCommandList);
	}
	catch (exception e) {
		ret = e.what();
	}
	LOG(ret);
}

void TestLibrary::FullWrite(vector<string> vCommandList)
{
	vCommandList.insert(vCommandList.begin(), "DummyLBA");
	for (int nLBA = m_pstDevice->GetMinLba(); nLBA < m_pstDevice->GetMaxLba(); nLBA++) {

		try {
			vCommandList[0] = to_string(nLBA);
			m_pstDevice->Write(vCommandList);
		}
		catch (exception e) {
			LOG(e.what());
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
			LOG(ret);
		}
		catch (exception e) {
			LOG(e.what());
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
		catch (exception e) {
			LOG(e.what());
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
			LOG(ret);
		}
		catch (exception e) {
			LOG(e.what());
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
