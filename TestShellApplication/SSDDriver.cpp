#include <cstdlib>
#include <string>

#include "SSDDriver.h"

using namespace std;

int SSDDriver::Read(int lba)
{
    return ExecuteCommand("VirtualSSD.exe R " + to_string(lba));
}

void SSDDriver::Write(int lba, int data)
{
    ExecuteCommand("VirtualSSD.exe W " + to_string(lba) + " " + to_string(data));
}

int SSDDriver::ExecuteCommand(string command)
{
    int result = system(command.c_str());
    return result;
}