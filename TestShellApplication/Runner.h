#pragma once

class Runner
{
public:
	Runner(Shell& shell);
	void RunShell();
	bool SetScenario(string scenarioList);

private:
	Shell& _shell;

protected:
	string _scenarioList;

	void _runCmdLineMode();
	void _runScenarioMode();
	virtual bool _getScenarioExisted(string listFile);
	virtual void _getScenarioList(string listFile);
};

