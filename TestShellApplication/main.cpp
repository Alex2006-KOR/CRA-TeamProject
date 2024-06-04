#include <iostream>

#include "SSDDriver.h"
#include "Shell.h"

int main() {
	SSDDriver ssd;
	Shell shell{ &ssd };
	shell.Run(std::cin, std::cout);
	return 0;
}