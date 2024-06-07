#pragma once
#include "LoggerPrinter.h"

class OutstreamLoggerPrinter :
    public LoggerPrinter
{
public:
    OutstreamLoggerPrinter();

public:
    void Print(string strMessage, string strCallerName) override;

    inline void Enable(bool b) { m_bEnable = b; }
    void SetOutStream(std::ostream& os);

private:
    inline bool _isEnable() { return m_bEnable; }

private:
    bool m_bEnable = true;
    std::ostream& m_os;
};

