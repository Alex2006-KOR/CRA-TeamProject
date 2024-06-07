#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(SSDInterface* pstSSDInterface) : m_pstSSDInterface(pstSSDInterface)
{}

void DeviceDriver::SetCmd(Command* pstCommand) {
    m_pstCommand = pstCommand;
}

void DeviceDriver::Execute() {
    m_pstCommand->ExecuteCmd(m_pstSSDInterface);
}

void DeviceDriver::FlushNand()
{
    m_pstSSDInterface->Flush();
}