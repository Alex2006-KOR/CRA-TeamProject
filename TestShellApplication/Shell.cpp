#include "Shell.h"

#include "ReadCommand.h"

#include <sstream>
#include <vector>

using std::vector;
using std::string;

Shell::Shell(DriverInterface* pSSDDriver)
	: m_pSSDDriver(pSSDDriver)
{
}

void Shell::Run(std::istream& input, std::ostream& output)
{
    string line;
    while (std::getline(input, line)) {
        handleCommand(line, output);
    }
}

void Shell::handleCommand(string lineString, std::ostream& output)
{
    vector<string> commandList;
    lineString += " ";
    auto nPos = lineString.find(" ");
    while (nPos != string::npos) {
        commandList.push_back(lineString.substr(0, nPos));
        lineString = lineString.substr(nPos + 1);
        nPos = lineString.find(" ");
    }
    
    string command = commandList[0];
    commandList.erase(commandList.begin());

    if (command == "read") {
        ReadCommand cmd(commandList, m_pSSDDriver, output);
        cmd.Execute();
    }
}
