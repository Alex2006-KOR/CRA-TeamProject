#include "Runner.h"
#include "fstream"
#include "sstream"

Runner::Runner(Shell& shell)
	:_shell(shell), _scenarioList("") {}

void Runner::RunShell()
{
	if (_scenarioList.length() == 0)
		_runCmdLineMode();
	else
		_runScenarioMode();
}

bool Runner::SetScenario(string scenarioList)
{
	if (_getScenarioExisted(scenarioList) == false)
		return false;
	_getScenarioList(scenarioList);
	return true;
}

void Runner::_runCmdLineMode()
{
	_shell.Run(std::cin, std::cout);
}

void Runner::_runScenarioMode()
{
	std::istringstream scenario(_scenarioList);
	_shell.Run(scenario, std::cout);
}

bool Runner::_getScenarioExisted(string listFile)
{
	bool ret = false;
	ifstream ifstreamRead(listFile);

	if (ifstreamRead.good())
		ret = true;
	ifstreamRead.close();

	return ret;
}

void Runner::_getScenarioList(string listFile)
{
	ifstream ifstreamRead(listFile);
	string  scenario;
	while (getline(ifstreamRead, scenario))
		_scenarioList += (scenario + "\n");
	_scenarioList += "exit\n";
}