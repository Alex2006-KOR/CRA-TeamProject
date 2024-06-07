#include "Platform.h"

Platform::Platform(DriverInterface* pstDriver, ostream& output)
	: m_out(output)
{
	m_pstDriver = new Device(pstDriver);
}

void Platform::SingleWrite(vector<string> vCommandList)
{
	try {
		m_pstDriver->Write(vCommandList);
	}
	catch (exception e) {
		m_out << e.what() << endl;
	}
}

void Platform::SingleRead(vector<string> vCommandList)
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

void Platform::FullWrite(vector<string> vCommandList)
{
	vCommandList.insert(vCommandList.begin(), "DummyLBA");
	for (int nLBA = 0; nLBA < 100; nLBA++) {

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

void Platform::FullRead()
{
	string ret;
	for (int nLBA = 0; nLBA < 100; nLBA++) {
		try {
			ret = m_pstDriver->Read({ to_string(nLBA) });
		}
		catch (exception e) {
			ret = e.what();
		}
		m_out << ret << endl;
	}
}
