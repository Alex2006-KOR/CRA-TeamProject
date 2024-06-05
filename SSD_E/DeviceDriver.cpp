#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(SSDInterface* pstSSDInterface) : m_pstSSDInterface(pstSSDInterface)
{}

void DeviceDriver::ReadData(int nLbaNumber)
{
    m_pstSSDInterface->read(nLbaNumber);
}

void DeviceDriver::WriteData(int nLbaNumber, string sData)
{
    m_pstSSDInterface->write(nLbaNumber, sData);
}