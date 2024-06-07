#include <iostream>

#include "SSDDriver.h"
#include "Shell.h"
#include "Runner.h"

int main(int argc, char* argv[]) {
	SSDDriver ssd;
	Shell shell{ &ssd };
	Runner runner(shell);

	if (argc == 2) {
		int result = runner.SetScenario(argv[1]);
		if (result == false) return 0;
	}
	runner.RunShell();

	return 0;
}