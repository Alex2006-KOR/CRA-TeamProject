#include "TestLibrary.h"
#include "Logger.h"

TestLibWrite::TestLibWrite(Device* pstDevice, ostream* output)
	:m_pstDevice(pstDevice), m_out(output) {}

void TestLibWrite::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Write(vCommandList);
	}
	catch (exception e) {
		//*m_out << e.what() << endl;
		LOG(e.what());
	}
}

TestLibRead::TestLibRead(Device* pstDevice, ostream* output)
	:m_pstDevice(pstDevice), m_out(output) {}

void TestLibRead::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	string ret;
	try {
		ret = m_pstDevice->Read(vCommandList);
	}
	catch (exception e) {
		ret = e.what();
	}
	//*m_out << ret << endl;
	LOG(ret);
}

TestLibFullWrite::TestLibFullWrite(Device* pstDevice, ostream* output)
	:m_pstDevice(pstDevice), m_out(output) {}

void TestLibFullWrite::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	for (int nLBA = m_pstDevice->GetMinLba(); nLBA < m_pstDevice->GetMaxLba(); nLBA++) {

		try {
			int nIndex = nLBA - m_pstDevice->GetMinLba();

			if (vCommandList.size() == 0) throw invalid_argument("check help - fullwrite [data]");
			string strData = vCommandList[nIndex % vCommandList.size()];
			m_pstDevice->Write({ to_string(nLBA), strData });
		}
		catch (exception e) {
			//*m_out << e.what() << endl;
			LOG(e.what());
			return;
		}
	}
}

TestLibFullRead::TestLibFullRead(Device* pstDevice, ostream* output)
	:m_pstDevice(pstDevice), m_out(output) {}

void TestLibFullRead::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	string ret;
	for (int nLBA = m_pstDevice->GetMinLba(); nLBA < m_pstDevice->GetMaxLba(); nLBA++) {
		try {
			ret = m_pstDevice->Read({ to_string(nLBA) });

			if (vCommandList.size() > 0) {
				int nIndex = nLBA - m_pstDevice->GetMinLba();
				string strCompareData = vCommandList[nIndex % vCommandList.size()];
				if (strCompareData.size() == 10 && ret != strCompareData)
					throw runtime_error("Data Mismatch!!");
			}

			//*m_out << ret << endl;
			LOG(ret);
		}
		catch (exception e) {
			//*m_out << e.what() << endl;
			LOG(e.what());
			return;
		}
	}
}

TestLibWriteRange::TestLibWriteRange(Device* pstDevice, ostream* output)
	:m_pstDevice(pstDevice), m_out(output) {}

void TestLibWriteRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			m_pstDevice->Write({ to_string(nLBA), strData });
		}
		catch (exception e) {
			//*m_out << e.what() << endl;
			LOG(e.what());
			return;
		}
	}
}

TestLibReadRange::TestLibReadRange(Device* pstDevice, ostream* output)
	:m_pstDevice(pstDevice), m_out(output) {}

void TestLibReadRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	string ret;
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			ret = m_pstDevice->Read({ to_string(nLBA) });
			if (strData.size() == 10 && ret != strData)
				throw runtime_error("Data Mismatch!!");
			//*m_out << ret << endl;
			LOG(ret);
		}
		catch (exception e) {
			//*m_out << e.what() << endl;
			LOG(e.what());
			return;
		}
	}
}