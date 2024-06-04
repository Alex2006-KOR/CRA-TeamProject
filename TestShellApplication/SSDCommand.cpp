#include "SSDCommand.h"

BaseSSDCommand::BaseSSDCommand(vector<string> commandList) {
	m_commandList = commandList;
	parseCommand();
}
