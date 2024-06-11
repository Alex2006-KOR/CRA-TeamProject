#include "Logger.h"
#include "TestLibrary.h"
#include "ShellException.h"

TestLibWrite::TestLibWrite(Device& pstDevice)
	:m_pstDevice(pstDevice){}

bool TestLibWrite::execute() const
{
	try {
		m_pstDevice.Write(m_vCommandList);
		return true;
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
}

TestLibRead::TestLibRead(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibRead::execute() const
{
	string ret;
	try {
		ret = m_pstDevice.Read(m_vCommandList);
		LOG(ret);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}

TestLibErase::TestLibErase(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibErase::execute() const
{
	try {
		m_pstDevice.Erase(m_vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}

TestLibFlush::TestLibFlush(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibFlush::execute() const
{
	try {
		m_pstDevice.Flush(m_vCommandList);
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}

TestLibFullWrite::TestLibFullWrite(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibFullWrite::execute() const
{
	for (int nLBA = m_pstDevice.GetMinLba(); nLBA < m_pstDevice.GetMaxLba(); nLBA++) {
		try {
			int nIndex = nLBA - m_pstDevice.GetMinLba();

			if (m_vCommandList.size() == 0) throw invalid_argument("check help - fullwrite [data]");
			string strData = m_vCommandList[nIndex % m_vCommandList.size()];
			m_pstDevice.Write({ to_string(nLBA), strData });
		}
		catch (exception& e) {
			LOG(e.what());
			return false;
		}
	}
	return true;
}

TestLibFullRead::TestLibFullRead(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibFullRead::execute() const
{
	string ret;
	for (int nLBA = m_pstDevice.GetMinLba(); nLBA < m_pstDevice.GetMaxLba(); nLBA++) {
		try {
			ret = m_pstDevice.Read({ to_string(nLBA) });

			if (m_vCommandList.size() > 0) {
				int nIndex = nLBA - m_pstDevice.GetMinLba();
				string strCompareData = m_vCommandList[nIndex % m_vCommandList.size()];
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

TestLibWriteRange::TestLibWriteRange(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibWriteRange::execute() const
{
	for (int nLBA = m_nStartLba; nLBA <= m_nEndLba; nLBA++) {
		try {
			m_pstDevice.Write({ to_string(nLBA), m_strData });
		}
		catch (exception& e) {
			LOG(e.what());
			return false;
		}
	}
	return true;
}

TestLibReadRange::TestLibReadRange(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibReadRange::execute() const
{
	string ret;
	for (int nLBA = m_nStartLba; nLBA <= m_nEndLba; nLBA++) {
		try {
			ret = m_pstDevice.Read({ to_string(nLBA) });
			if (m_strData.size() == 10 && ret != m_strData)
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

TestLibEraseRange::TestLibEraseRange(Device& pstDevice)
	:m_pstDevice(pstDevice) {}

bool TestLibEraseRange::execute() const
{
	int nStartLba = m_nStartLba;
	int nEndLba = m_nEndLba;
	if (m_vCommandList.size() > 0) {
		try {
			nStartLba = stoi(m_vCommandList[0]);
			nEndLba = stoi(m_vCommandList[1]);
		}
		catch (exception& e) {
			LOG(e.what());
			return;
		}
	}
	try {
		m_pstDevice.Erase({ to_string(nStartLba), to_string(nEndLba - nStartLba) });
	}
	catch (exception& e) {
		LOG(e.what());
		return false;
	}
	return true;
}
