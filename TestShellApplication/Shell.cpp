#include "Shell.h"
#include "Logger.h"

#include <sstream>
#include <vector>

Shell::Shell(DriverInterface* pstDriver)
{
    m_pstTestLibCommandInvoker = new TestLibCommandInvoker(pstDriver);
    m_pstTestScriptInvoker = new TestScriptInvoker(m_pstTestLibCommandInvoker);
}

void Shell::Run(istream& input, bool isScriptMode)
{
    string strLine;
    while (true) {
        while (getline(input, strLine)) {
            bool bExit = handleCommand(strLine, isScriptMode);
            if (bExit) return;
        }
    }
}

bool Shell::handleCommand(string strLine, bool isScriptMode)
{
    vector<string> vCommandList = _splitLine(strLine);
    if (vCommandList.size() == 0) return false;
    string strCommand = _trim(vCommandList[0]);
    if (strCommand == "") return false;

    vCommandList.erase(vCommandList.begin());

    TestLibrary* targetFunction = m_pstTestLibCommandInvoker->GetFunction(strCommand);
    if (targetFunction) {
        m_pstTestLibCommandInvoker->Run(targetFunction, vCommandList);
        return false;
    }

    TestScriptInterface* targetScript = m_pstTestScriptInvoker->GetTestScript(strCommand);
    if (targetScript) {
        return !m_pstTestScriptInvoker->Run(targetScript, isScriptMode);
    }
    
    if (strCommand == "help") {
        _printHelp();
    }
    else if (strCommand == "exit") {
        return true;
    }
    else {
        LOG("INVALID COMMAND");
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
- erase [lba] [block count]\n\
- fullwrite [data]\n\
- fullread\n\
- erase_range [start lba] [end lba]\n\
- exit\n\
\n\
[lba] : decimal only, range = [0, 99]\n\
[data] : hexadecimal only, range = [0x00000000, 0xFFFFFFFF]\n\
[block count] : decimal only, range = [0, 10] (erase) \n\
";
    LOG(strHelp);
}

vector<string> Shell::_splitLine(std::string& strLine)
{
    vector<string> vCommandList;
    strLine += " ";
    auto nPos = strLine.find(" ");
    while (nPos != string::npos) {
        string strSubString = strLine.substr(0, nPos);
        if (strSubString.size() > 0) vCommandList.push_back(strSubString);
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