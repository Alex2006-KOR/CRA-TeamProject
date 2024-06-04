#include <string>
#include "IOManager.h"
#include "ssd.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	SSDInterface* pstSSDInterface = new SSD();
	DeviceDriver stDeviceDriver{ pstSSDInterface };
	IOManager stIOManager{ &stDeviceDriver };

	if (argc == 1) return 0; // param 없는 경우

	string strCommand = string(argv[1]);
	int nLbaNumber = stoi(string(argv[2]));
	string strData = "";
	if (strCommand == "W") strData = string(argv[3]);

	stIOManager.DoCommand(strCommand, nLbaNumber, strData);

	return 0;
}