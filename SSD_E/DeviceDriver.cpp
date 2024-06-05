#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(SSDInterface* pstSSDInterface) : m_pstSSDInterface(pstSSDInterface)
{}

void DeviceDriver::ReadData(int nLbaNumber)
{
    m_pstSSDInterface->Read(nLbaNumber);
}

void DeviceDriver::WriteData(int nLbaNumber, string sData)
{
    m_pstSSDInterface->Write(nLbaNumber, sData);
}