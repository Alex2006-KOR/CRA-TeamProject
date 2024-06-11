#include "Device.h"

Device* Device::m_pstIntstance = nullptr;

Device& Device::GetDevice(DriverInterface* pstDevice)
{
	if (!m_pstIntstance && pstDevice) {
		m_pstIntstance = new Device(pstDevice);
	}
	return *m_pstIntstance;
}

void Device::Write(vector<string> vCommandList)
{
	if (m_stWrite.CheckArgCnt(vCommandList) == false)
		throw invalid_argument("invalid # of args. please check help.");

	return m_stWrite.setLBA(vCommandList[0])
		.setData(vCommandList[1])
		.execute();
}

string Device::Read(vector<string> vCommandList)
{
	if (m_stRead.CheckArgCnt(vCommandList) == false)
		throw invalid_argument("invalid # of args. please check help.");

	return m_stRead.setLBA(vCommandList[0])
		.execute();
}

void Device::Erase(vector<string> vCommandList)
{
	if (m_stErase.CheckArgCnt(vCommandList) == false)
		throw invalid_argument("invalid # of args. please check help.");

	return m_stErase.setLBA(vCommandList[0])
		.setBlkCnt(vCommandList[1])
		.execute();
}

void Device::Flush(vector<string> vCommandList)
{
	if (m_stFlush.CheckArgCnt(vCommandList) == false)
		throw invalid_argument("invalid # of args. please check help.");

	return m_stFlush.execute();
}

int Device::GetMinLba()
{
	return m_pstDriver->GetMinLba();
}

int Device::GetMaxLba()
{
	return m_pstDriver->GetMaxLba();
}


Device::Device(DriverInterface* pstDevice)
	: m_pstDriver(pstDevice) {}