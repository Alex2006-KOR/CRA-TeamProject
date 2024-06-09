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

    ExecutionCommandBuilder& setLbaIndex(int nLba) {
        command += (" " + std::to_string(nLba));
        return *this;
    }

    ExecutionCommandBuilder& setWriteData(int nData) {
        command += (" " + std::to_string(nData));
        return *this;
    }

    ExecutionCommandBuilder& setBlockCount(int nBlkCnt) {
        command += (" " + std::to_string(nBlkCnt));
        return *this;
    }

    const char* build() {
        return command.c_str();
    }

private:
    string command;
};

void SSDDriver::Read(int nLba)
{
    _executeCommand(
        ExecutionCommandBuilder()
        .setAccessType("R")
        .setLbaIndex(nLba)
        .build()
    );
}

void SSDDriver::Write(int nLba, int nData)
{
    _executeCommand(
        ExecutionCommandBuilder()
        .setAccessType("W")
        .setLbaIndex(nLba)
        .setWriteData(nData)
        .build()
    );
}

void SSDDriver::Erase(int nLba, int nBlkCnt)
{
    _executeCommand(
        ExecutionCommandBuilder()
        .setAccessType("E")
        .setLbaIndex(nLba)
        .setBlockCount(nBlkCnt)
        .build()
    );
}

void SSDDriver::Flush()
{
    _executeCommand(
        ExecutionCommandBuilder()
        .setAccessType("F")
        .build()
    );
}

void SSDDriver::_executeCommand(const char* strCommand) {
    system(strCommand);
}

std::string SSDDriver::ReadBuffer()
{
    if (_getSsdExisted())
        return _getSsdResult();
    return string();
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

int SSDDriver::GetMinLba()
{
    return MIN_LBA;
}

int SSDDriver::GetMaxLba()
{
    return MAX_LBA;
}

int SSDDriver::GetMaxBlkCntPerErase()
{
    return MAX_BLK_CNT_PER_ERASE;
}