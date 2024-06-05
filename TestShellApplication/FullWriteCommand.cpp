#include "FullWriteCommand.h"
#include "WriteCommand.h"

#include <sstream>
#include <vector>

FullWriteCommand::FullWriteCommand(vector<string> commandList, DriverInterface* pSSDDriver, std::ostream& output)
	: BaseSSDCommand(commandList)
	, m_out(output)
	, m_pstSSDDriver(pSSDDriver)
{
}

bool FullWriteCommand::_parseCommand()
{
	constexpr int REQUIRED_COMMAND_COUNT = 1;
	if (m_vCommandList.size() != REQUIRED_COMMAND_COUNT) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}

	m_sData = m_vCommandList[0];
	return true;
}

void FullWriteCommand::_execute()
{
	for (int lba = 0; lba < 100; lba++) {
		std::vector<string> commandList;

		std::stringstream lbaStringStream;
		lbaStringStream << lba;

		commandList.push_back(lbaStringStream.str());
		commandList.push_back(m_sData);

		WriteCommand command(commandList, m_pstSSDDriver, m_out);
		if (command.Execute() == false) {
			return;
		}
	}
}