#include "Shell.h"

#include <sstream>
#include <vector>

Shell::Shell(DriverInterface* pstDriver)
    : m_out(std::cout)
{
    m_pstTestLib = TestLibrary::GetLibrary(pstDriver, &m_out);
    m_pstTestApp1 = new TestApp1(pstDriver, m_out);
    m_pstTestApp2 = new TestApp2(pstDriver, m_out);
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
    vCommandList.erase(vCommandList.begin());
    if (strCommand == "") {
    }
    else if (strCommand == "write") {
        m_pstTestLib->Write(vCommandList);
    }
    else if (strCommand == "read") {
        m_pstTestLib->Read(vCommandList);
    }
    else if (strCommand == "fullwrite") {
        m_pstTestLib->FullWrite(vCommandList);
    }
    else if (strCommand == "fullread") {
        m_pstTestLib->FullRead();
    }
    else if (strCommand == "testapp1") {
        m_pstTestApp1->Run();
    }
    else if (strCommand == "testapp2") {
        m_pstTestApp2->Run();
    }
    else if (strCommand == "help") {
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