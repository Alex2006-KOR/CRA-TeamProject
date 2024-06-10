#include "Device.h"

Device::Device(DriverInterface* pstDriver)
	: m_pstDriver(pstDriver)
{
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

int Device::GetMinLba()
{
	return m_pstDriver->GetMinLba();
}

int Device::GetMaxLba()
{
	return m_pstDriver->GetMaxLba();
}
