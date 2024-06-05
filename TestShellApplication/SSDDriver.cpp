#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include "SSDDriver.h"

using namespace std;

const string SSD_FILE = "result.txt";

int SSDDriver::Read(int lba)
{
    int retCode = _executeCommand(
        "VirtualSSD.exe R " +
        to_string(lba)
    );

    if (retCode == -1)
        return 0;
    return _getReadResult();
}

void SSDDriver::Write(int lba, int data)
{
    int retCode = _executeCommand(
        "VirtualSSD.exe W " +
        to_string(lba) + " " + to_string(data)
    );
}

int SSDDriver::_executeCommand(string command)
{
    try {
        int retCode = system(command.c_str());
        return retCode;
    }
    catch (exception& e) {
        cout << "Virtual SSD execution failed" << endl;
        cout << e.what() << endl;
        return -1;
    }
}

int SSDDriver::_getReadResult(void)
{
    try {
        if (_getSsdExisted())
            return _getSsdResult();
        return 0;
    }
    catch (exception& e) {
        cout << e.what() << endl;
        return 0;
    }
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

int SSDDriver::_getSsdResult(void)
{
    ifstream ifstreamRead(SSD_FILE);
    if (ifstreamRead.is_open() == false)
        throw exception("Open SSD Result file fail");

    int ret = 0;
    string readData;
    getline(ifstreamRead, readData);
    ret = stoi(readData, nullptr, 16);

    ifstreamRead.close();

    return ret;
}