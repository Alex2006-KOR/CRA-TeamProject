#include <iostream>

#include "SSDDriver.h"
#include "Shell.h"

int main(int argc, char* argv[]) {
	SSDDriver ssdDriver;
	Shell shell{ &ssdDriver, std::cout };
	shell.Run(std::cin);
	return 0;
}