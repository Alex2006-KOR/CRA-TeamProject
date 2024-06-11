#include "HelpCommand.h"

#include <iostream>

HelpCommand::HelpCommand(DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(output)
{
}

bool HelpCommand::_parseCommand() {
	return true;
}

void HelpCommand::_execute()
{
	static std::string strHelp = "\n\
[[Shell Test Application]]\n\
\n\
<< Command Usage >> \n\
- write [lba] [data]\n\
- read [lba]\n\
- fullwrite [data]\n\
- fullread\n\
- exit\n\
\n\
[lba] : decimal only, range = [0, 99]\n\
[data] : hexadecimal only, range = [0x00000000, 0xFFFFFFFF]\n\
";

	m_out << strHelp;
}