#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include "SSDDriver.h"

using namespace std;

const string SSD_FILE = "result.txt";

class ExecutionCommandBuilder {
public:
    ExecutionCommandBuilder() : command("VirtualSSD.exe") {}

    ExecutionCommandBuilder& setAccessType(std::string accessType) {
        command += (" " + accessType);
        return *this;
    }

    ExecutionCommandBuilder& setLbaIndex(int lbaIdx) {
        command += (" " + std::to_string(lbaIdx));
        return *this;
    }

    ExecutionCommandBuilder& setWriteData(int data) {
        command += (" " + std::to_string(data));
        return *this;
    }

    const char* build() {
        return command.c_str();
    }

private:
    string command;
};

void SSDDriver::Read(int lba)
{
    _executeCommand(
        ExecutionCommandBuilder()
        .setAccessType("R")
        .setLbaIndex(lba)
        .build()
    );
}

void SSDDriver::Write(int lba, int data)
{
    _executeCommand(
        ExecutionCommandBuilder()
        .setAccessType("W")
        .setLbaIndex(lba)
        .setWriteData(data)
        .build()
    );
}

std::string SSDDriver::ReadBuffer()
{
    if (_getSsdExisted())
        return _getSsdResult();
    return string();
}

int SSDDriver::GetMinLba()
{
    return MIN_LBA;
}

int SSDDriver::GetMaxLba()
{
    return MAX_LBA;
}

void SSDDriver::_executeCommand(const char* strCommand) {
    system(strCommand);
}

bool SSDDriver::_getSsdExisted(void)
{
    bool ret = false;
    ifstream ifstreamRead(SSD_FILE);

    if (ifstreamRead.good())
        ret = true;
    ifstreamRead.close();
    return ret;
}

std::string SSDDriver::_getSsdResult(void)
{
    ifstream ifstreamRead(SSD_FILE);
    if (ifstreamRead.is_open() == false)
        throw exception("Open SSD Result file fail");

    string readData;
    getline(ifstreamRead, readData);
    ifstreamRead.close();

    return readData;
}