#include "ReadCommand.h"
#include "ShellException.h"

#include <stdexcept>

ReadCommand::ReadCommand(DriverInterface* pstDriver)
    : m_pstDriver(pstDriver)
    , m_nLBA(-1)
{
}

ReadCommand& ReadCommand::setLBA(string strLBA)
{
    _checkLBAFormat(strLBA);
    _updateLBA(strLBA);
    _checkLBARange();
    return *this;
}

string ReadCommand::execute()
{
    m_pstDriver->Read(m_nLBA);
    return m_pstDriver->ReadBuffer();
}

bool ReadCommand::CheckArgCnt(vector<string> vArgs) const
{
    return vArgs.size() == this->REQUIRED_COMMAND_COUNT;
}

void ReadCommand::_checkLBAFormat(string strLBA)
{
    if (strLBA.substr(0, 2) == "0x") {
        throw Invalid_LBA("not a decimal format");
    }
    for (const char ch : strLBA) {
        if ((ch >= '0') && (ch <= '9')) continue;
        throw Invalid_LBA("not a decimal number found");
    }
}

void ReadCommand::_updateLBA(string strLBA)
{
    try {
        m_nLBA = stoi(strLBA);
    }
    catch (const out_of_range& e) {
        m_nLBA = -1;
    }
}

void ReadCommand::_checkLBARange()
{
    if (m_nLBA < m_pstDriver->GetMinLba() || m_nLBA >= m_pstDriver->GetMaxLba())
        throw Invalid_LBA("LBA out of range");
}