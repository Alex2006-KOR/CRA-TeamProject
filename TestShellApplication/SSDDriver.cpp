#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

#include "SSDDriver.h"

using namespace std;

const string SSD_FILE = "result.txt";

int SSDDriver::Read(int lba)
{
    int retCode = _executeCommand("VirtualSSD.exe R " + to_string(lba));
    int ret = 0;

    if (retCode != -1) {
        if (_getSsdExisted()) {
            ifstream ifstreamRead(SSD_FILE);
            if (ifstreamRead.is_open() == false)
                throw exception("Open SSD Result file fail");
    
            string readData;
            getline(ifstreamRead, readData);
            ret = stoi(readData);
            ifstreamRead.close();
        }
    }
    else {
        cout << "Virtual SSD execution failed" << endl;
    }

    return ret;
}

void SSDDriver::Write(int lba, int data)
{
    int retCode = _executeCommand("VirtualSSD.exe W " + to_string(lba) + " " + to_string(data));
    if (retCode == -1)
        cout << "Virtual SSD execution failed" << endl;
}

int SSDDriver::_executeCommand(string command)
{
    int retCode = system(command.c_str());
    return retCode;
}

bool SSDDriver::_getSsdExisted(void) {
    bool ret = false;
	ifstream ifstreamRead(SSD_FILE);

	if (ifstreamRead.good())
        ret = true;
	ifstreamRead.close();

	return ret;
}

int SSDDriver::_getSsdResult(void) {
    bool ret = false;
    ifstream ifstreamRead(SSD_FILE);

    if (ifstreamRead.good())
        ret = true;
    ifstreamRead.close();

    return ret;
}