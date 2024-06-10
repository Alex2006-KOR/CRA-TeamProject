#include <iostream>

#include "SSDDriver.h"
#include "Shell.h"
#include "Runner.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
	SSDDriver ssd;
	Shell shell{ &ssd, std::cout };
	Runner runner(shell);

	if (argc == 2) {
		Logger::getInstance().EnableConsoleLog(false);
		int result = runner.SetScenario(argv[1]);
		if (result == false) return 0;
	}
	runner.RunShell();
	return 0;
}