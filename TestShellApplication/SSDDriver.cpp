#include "SSDDriver.h"
#include <cstdlib>
#include <string>

using namespace std;

int SSDDriver::Read(int lba)
{
    string command = "VirtualSSD.exe R " + to_string(lba);
    int result = std::system(command.c_str());
    return result;
}

void SSDDriver::Write(int lba, int data)
{
    string command = "VirtualSSD.exe W " + to_string(lba) + " " + to_string(lba);
    int result = std::system(command.c_str());
}