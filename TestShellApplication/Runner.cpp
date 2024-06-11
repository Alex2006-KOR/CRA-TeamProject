#include "Shell.h"
#include "Logger.h"
#include "Runner.h"
#include "fstream"
#include "sstream"

Runner::Runner(Shell& shell)
	:_shell(shell), _scenarioList("") {}

void Runner::RunShell()
{
	_runCmdLineMode();
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
	if (_scenarioList.length() != 0)
		return;
	_shell.Run(std::cin);
}

void Runner::_runScenarioMode()
{
	if (_scenarioList.length() == 0)
		return;
	std::istringstream scenario(_scenarioList);
	_shell.Run(scenario, true);
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