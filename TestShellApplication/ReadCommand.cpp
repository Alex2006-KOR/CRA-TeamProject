#include "ReadCommand.h"

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
        throw invalid_argument("INVALID LBA");
    }
    for (const char ch : strLBA) {
        if ((ch >= '0') && (ch <= '9')) continue;
        throw invalid_argument("INVALID LBA");
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
    if (m_nLBA < 0 || m_nLBA >= 100)
        throw invalid_argument("INVALID LBA");
}