#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(SSDInterface* pstSSDInterface) : m_pstSSDInterface(pstSSDInterface)
{}

void DeviceDriver::ReadData(int nLbaNumber)
{
    m_pstSSDInterface->read();
}

void DeviceDriver::WriteData(int nLbaNumber, string data)
{
    m_pstSSDInterface->write();
}