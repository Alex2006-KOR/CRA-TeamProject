#include "OutstreamLoggerPrinter.h"

#include <iostream>


OutstreamLoggerPrinter::OutstreamLoggerPrinter()
	: m_os{ std::cout }
{
}

void OutstreamLoggerPrinter::Print(string strMessage, string strCallerName)
{
	if (_isEnable() == false) return;
	m_os << strMessage << std::endl;
}

void OutstreamLoggerPrinter::SetOutStream(std::ostream& os)
{
	m_os.rdbuf(os.rdbuf());
}
