#pragma once
#include <string>
#include "SSDInterface.h"
#include "SSDCommand.h"

using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(SSDInterface* pstSSDInterface);
    void SetCmd(Command* pstCommand);
    void Execute();
    void FlushNand();

protected:
    SSDInterface* m_pstSSDInterface;

private:
    Command *m_pstCommand;
};