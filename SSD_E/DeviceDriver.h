#pragma once
#include <string>
#include "SSDInterface.h"

using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(SSDInterface* pstSSDInterface);
    void ReadData(int nLbaNumber);
    void WriteData(int nLbaNumber, string data);

protected:
    SSDInterface* m_pstSSDInterface;

private:

};