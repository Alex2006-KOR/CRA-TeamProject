#include "Shell.h"

Shell::Shell(DriverInterface* pSSDDriver)
	: m_pSSDDriver(pSSDDriver)
    , m_pCommandInvoker(nullptr)
{
}

Shell::~Shell()
{
    if (m_pCommandInvoker != nullptr) {
        delete m_pCommandInvoker;
        m_pCommandInvoker = nullptr;
    }
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

    SSDComamnd* pCommand = _getCommandInvoker(output)->GetCommand(strCommand);
    if (pCommand) {
        pCommand->SetCommandList(vCommandList);
        pCommand->Execute();
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

SSDCommandInvoker* Shell::_getCommandInvoker(ostream& output)
{
    if (m_pCommandInvoker == nullptr) {
        m_pCommandInvoker = new SSDCommandInvoker(m_pSSDDriver, output);
    }
    return m_pCommandInvoker;
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