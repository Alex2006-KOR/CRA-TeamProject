#include "ShellException.h"

SSDException::SSDException (const std::string& strBaseMessage)
	: strMessage(strBaseMessage)
{
}

SSDException::SSDException(const std::string& strBaseMessage, const std::string& strMessage)
	: strMessage(strBaseMessage + " - " + strMessage)
{
}

char const* SSDException::what() const
{
	return strMessage.c_str();
}

Invalid_LBA::Invalid_LBA()
	:SSDException("INVALID LBA")
{
}

Invalid_LBA::Invalid_LBA(const std::string strMessage)
	:SSDException("INVALID LBA", strMessage)
{
}

Invalid_BlockCount::Invalid_BlockCount()
	:SSDException("INVALID BLOCK COUNT")
{
}

Invalid_BlockCount::Invalid_BlockCount(const std::string strMessage)
	:SSDException("INVALID BLOCK COUNT", strMessage)
{
}

Invalid_Data::Invalid_Data()
	:SSDException("INVALID DATA")
{
}

Invalid_Data::Invalid_Data(const std::string strMessage)
	:SSDException("INVALID DATA", strMessage)
{
}