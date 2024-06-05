#include <string>
#include <iostream>

#include "IOManager.h"
#include "ssd.cpp"

using namespace std;

void DoCommand(char* argv[])
{
	SSDInterface* pstSSDInterface = new SSD();
	DeviceDriver stDeviceDriver{ pstSSDInterface };
	IOManager stIOManager{ &stDeviceDriver };

	string strCommand = string(argv[1]);
	int nLbaNumber = stoi(string(argv[2]));
	string strData = "";
	if (strCommand == "W") strData = string(argv[3]);

	try {
		stIOManager.DoCommand(strCommand, nLbaNumber, strData);
	}
	catch (exception e) {
		// This Program must not cause runtime err!
		std::cout << e.what() << std::endl;
	}
}

bool CheckInvalidArgument(int argc)
{
	const int THERE_IS_NO_ARGUMENT = 1;

	if (argc == THERE_IS_NO_ARGUMENT) {
		cout << "There is no argument." << endl;
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	if (CheckInvalidArgument(argc)) return 0;
	
	DoCommand(argv);
	return 0;
}