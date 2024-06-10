#pragma once
#include <stdexcept>
#include <string>

class SSDException :public std::exception {
public:
	SSDException(const std::string& strBaseMessage);
	SSDException(const std::string& strBaseMessage, const std::string& strMessage);
	char const* what() const override;
protected:
	std::string strMessage;
};

class Invalid_LBA : public SSDException {
public:
	Invalid_LBA();
	Invalid_LBA(const std::string strMessage);
};

class Invalid_BlockCount : public SSDException {
public:
	Invalid_BlockCount();
	Invalid_BlockCount(const std::string strMessage);
};

class Invalid_Data : public SSDException {
public:
	Invalid_Data();
	Invalid_Data(const std::string strMessage);
};