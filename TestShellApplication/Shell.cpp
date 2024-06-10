#include "Shell.h"

#include <sstream>
#include <vector>

Shell::Shell(DriverInterface* pstDriver, ostream& output)
    : m_out(output)
{
    m_pstTestLibCommandInvoker = new TestLibCommandInvoker(pstDriver, &output);
    m_pstTestScriptInvoker = new TestScriptInvoker(m_pstTestLibCommandInvoker, &output);
}

void Shell::Run(istream& input)
{
    string strLine;
    while (true) {
        while (getline(input, strLine)) {
            bool bExit = handleCommand(strLine);
            if (bExit) return;
        }
    }
}

bool Shell::handleCommand(string strLine)
{
    vector<string> vCommandList = _splitLine(strLine);

    string strCommand = _trim(vCommandList[0]);
    if (strCommand == "") return false;

    vCommandList.erase(vCommandList.begin());

    TestLibrary* targetFunction = m_pstTestLibCommandInvoker->GetFunction(strCommand);
    if (targetFunction) {
        m_pstTestLibCommandInvoker->Run(targetFunction, vCommandList);
        return false;
    }

    TestScriptBase* targetScript = m_pstTestScriptInvoker->GetTestScript(strCommand);
    if (targetScript) {
        m_pstTestScriptInvoker->Run(targetScript);
        return false;
    }
    
    if (strCommand == "help") {
        _printHelp();
    }
    else if (strCommand == "exit") {
        return true;
    }
    else {
        m_out << "INVALID COMMAND\n";
    }
    return false;
}

void Shell::_printHelp()
{
    string strHelp = "\n\
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
    cout << strHelp;
}

vector<string> Shell::_splitLine(std::string& strLine)
{
    vector<string> vCommandList;
    strLine += " ";
    auto nPos = strLine.find(" ");
    while (nPos != string::npos) {
        vCommandList.push_back(strLine.substr(0, nPos));
        strLine = strLine.substr(nPos + 1);
        nPos = strLine.find(" ");
    }
    return vCommandList;
}

string Shell::_trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}