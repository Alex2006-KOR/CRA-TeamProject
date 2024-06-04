#include <string>
#include "IOManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	IOManager stIOManager;

	if (argc == 1) return 0; // param 없는 경우

	string strCommand = string(argv[1]);
	int nLbaNumber = stoi(string(argv[2]));
	string strData = "";
	if (strCommand == "W") strData = string(argv[3]);

	stIOManager.DoCommand(strCommand, nLbaNumber, strData);

	return 0;
}