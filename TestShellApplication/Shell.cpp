#include "Shell.h"
#include "ReadCommand.h"
#include "WriteCommand.h"
#include "FullWriteCommand.h"
#include "FullReadCommand.h"

Shell::Shell(DriverInterface* pSSDDriver)
	: m_pSSDDriver(pSSDDriver)
{
}

void Shell::Run(istream& input, ostream& output)
{
    while (true) {
        string line;
        while (getline(input, line)) {
            bool bExit = handleCommand(line, output);
            if (bExit) return;
        }
    }
}

bool Shell::handleCommand(string strCommandLine, ostream& output)
{
    vector<string> vCommandList = SplitLine(strCommandLine);
    
    string strCommand = trim(vCommandList[0]);
    vCommandList.erase(vCommandList.begin());
    if (strCommand == "") { return false; }

    if (strCommand == "write") {
        WriteCommand cmd(vCommandList, m_pSSDDriver, output);
        cmd.Execute();
    }
    else if (strCommand == "read") {
        ReadCommand read(vCommandList, m_pSSDDriver, output);
        read.Execute();
    }
    else if (strCommand == "fullwrite") {
        FullWriteCommand cmd(vCommandList, m_pSSDDriver, output);
        cmd.Execute();
    }
    else if (strCommand == "fullread") {
        FullReadCommand cmd(vCommandList, m_pSSDDriver, output);
        cmd.Execute();
    }
    else if (strCommand == "help") {
        output << strHelp;
    }
    else if (strCommand == "exit") { 
        return true; 
    }
    else {
        output << "INVALID COMMAND\n";
    }
    return false;
}

vector<string> Shell::SplitLine(string& strCommandLine)
{
    vector<string> vCommandList;
    strCommandLine += " ";
    auto nPos = strCommandLine.find(" ");
    while (nPos != string::npos) {
        vCommandList.push_back(strCommandLine.substr(0, nPos));
        strCommandLine = strCommandLine.substr(nPos + 1);
        nPos = strCommandLine.find(" ");
    }
    return vCommandList;
}

string Shell::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}