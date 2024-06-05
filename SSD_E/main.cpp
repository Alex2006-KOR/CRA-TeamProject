#include <string>
#include <iostream>

#include "IOManager.h"
#include "ssd.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	const int ERROR_RETURN_CODE = -1;
	const int NORMAL_RETURN_CODE = 0;

	SSDInterface* pstSSDInterface = new SSD();
	DeviceDriver stDeviceDriver{ pstSSDInterface };
	IOManager stIOManager{ &stDeviceDriver };

	try {
		stIOManager.DoCommand(argc, argv);
	}
	catch (exception e) {
		// This Program must not cause runtime err!
		std::cout << e.what() << std::endl;
		return ERROR_RETURN_CODE;
	}
	return NORMAL_RETURN_CODE;
}