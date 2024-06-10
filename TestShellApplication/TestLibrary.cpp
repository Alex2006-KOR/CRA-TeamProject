#include "Logger.h"
#include "TestLibrary.h"
#include "ShellException.h"

TestLibWrite::TestLibWrite(Device* pstDevice)
	:m_pstDevice(pstDevice){}

void TestLibWrite::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Write(vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
	}
}

TestLibRead::TestLibRead(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibRead::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	string ret;
	try {
		ret = m_pstDevice->Read(vCommandList);
	}
	catch (exception& e) {
		ret = e.what();
	}
	LOG(ret);
}

TestLibErase::TestLibErase(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibErase::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Erase(vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
	}
}

TestLibFlush::TestLibFlush(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibFlush::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Flush(vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
	}
}

TestLibFullWrite::TestLibFullWrite(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibFullWrite::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	for (int nLBA = m_pstDevice->GetMinLba(); nLBA < m_pstDevice->GetMaxLba(); nLBA++) {

		try {
			int nIndex = nLBA - m_pstDevice->GetMinLba();

			if (vCommandList.size() == 0) throw invalid_argument("check help - fullwrite [data]");
			string strData = vCommandList[nIndex % vCommandList.size()];
			m_pstDevice->Write({ to_string(nLBA), strData });
		}
		catch (exception& e) {
			LOG(e.what());
			return;
		}
	}
}

TestLibFullRead::TestLibFullRead(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

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
			LOG(ret);
		}
		catch (exception& e) {
			LOG(e.what());
			return;
		}
	}
}

TestLibWriteRange::TestLibWriteRange(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibWriteRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			m_pstDevice->Write({ to_string(nLBA), strData });
		}
		catch (exception& e) {
			LOG(e.what());
			return;
		}
	}
}

TestLibReadRange::TestLibReadRange(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibReadRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	string ret;
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			ret = m_pstDevice->Read({ to_string(nLBA) });
			if (strData.size() == 10 && ret != strData)
				throw runtime_error("Data Mismatch!!");
			LOG(ret);
		}
		catch (exception& e) {
			LOG(e.what());
			return;
		}
	}
}

TestLibEraseRange::TestLibEraseRange(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

void TestLibEraseRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	if (vCommandList.size() > 0) {
		_validateArguments(vCommandList);
		nStartLba = stoi(vCommandList[0]);
		nEndLba = stoi(vCommandList[1]);
	}
	try {
		m_pstDevice->Erase({ to_string(nStartLba), to_string(nEndLba - nStartLba) });
	}
	catch (exception& e) {
		LOG(e.what());
	}
}

void TestLibEraseRange::_validateArguments(const std::vector<std::string>& vCommandList) const
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
