#include "TestLibrary.h"

TestLibrary::TestLibrary(DriverInterface* pstDriver, ostream& output)
	: m_out(output)
{
	m_pstDriver = new Device(pstDriver);
}

void TestLibrary::SingleWrite(vector<string> vCommandList)
{
	try {
		m_pstDriver->Write(vCommandList);
	}
	catch (exception e) {
		m_out << e.what() << endl;
	}
}

void TestLibrary::SingleRead(vector<string> vCommandList)
{
	string ret;
	try {
		ret = m_pstDriver->Read(vCommandList);
	}
	catch (exception e) {
		ret = e.what();
	}
	m_out << ret << endl;
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
			m_out << e.what() << endl;
			return;
		}
	}
}

void TestLibrary::FullRead()
{
	string ret;
	for (int nLBA = m_pstDriver->GetMinLba(); nLBA < m_pstDriver->GetMaxLba(); nLBA++) {
		try {
			ret = m_pstDriver->Read({ to_string(nLBA) });
		}
		catch (exception e) {
			ret = e.what();
		}
		m_out << ret << endl;
	}
}
