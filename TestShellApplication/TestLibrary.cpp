#include "Logger.h"
#include "TestLibrary.h"
#include "ShellException.h"

TestLibWrite::TestLibWrite(Device* pstDevice)
	:m_pstDevice(pstDevice){}

bool TestLibWrite::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Write(vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
}

TestLibRead::TestLibRead(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibRead::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	string ret;
	try {
		ret = m_pstDevice->Read(vCommandList);
		LOG(ret);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}

TestLibErase::TestLibErase(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibErase::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Erase(vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}

TestLibFlush::TestLibFlush(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibFlush::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	try {
		m_pstDevice->Flush(vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}

TestLibFullWrite::TestLibFullWrite(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibFullWrite::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
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
			return false;
		}
	}
	return true;
}

TestLibFullRead::TestLibFullRead(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibFullRead::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
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
			return false;
		}
	}
	return true;
}

TestLibWriteRange::TestLibWriteRange(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibWriteRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	for (int nLBA = nStartLba; nLBA <= nEndLba; nLBA++) {
		try {
			m_pstDevice->Write({ to_string(nLBA), strData });
		}
		catch (exception& e) {
			LOG(e.what());
			return false;
		}
	}
	return true;
}

TestLibReadRange::TestLibReadRange(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibReadRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
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
			return false;
		}
	}
	return true;
}

TestLibEraseRange::TestLibEraseRange(Device* pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibEraseRange::execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const
{
	if (vCommandList.size() > 0) {
		try {
			nStartLba = stoi(vCommandList[0]);
			nEndLba = stoi(vCommandList[1]);
		}
		catch (exception& e) {
			LOG(e.what());
			return;
		}
	}
	try {
		m_pstDevice->Erase({ to_string(nStartLba), to_string(nEndLba - nStartLba) });
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}
