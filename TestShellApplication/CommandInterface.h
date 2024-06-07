#pragma once
#include <string>
#include <vector>

#define Interface struct

Interface NonDataCommand{
public:
	virtual void execute() = 0;
	virtual bool CheckArgCnt(std::vector<std::string> vArgs) const = 0;
};

Interface DataCommand{
public:
	virtual std::string execute() = 0;
	virtual bool CheckArgCnt(std::vector<std::string> vArgs) const = 0;
};

Interface LbaArgument{
	virtual LbaArgument & setLBA(std::string strLBA) = 0;

	virtual void _checkLBAFormat(std::string strLBA) = 0;
	virtual void _updateLBA(std::string strLBA) = 0;
	virtual void _checkLBARange() = 0;
};

Interface DataArguement{
	virtual DataArguement& setData(std::string strData) = 0;

	virtual void _updateData(std::string& strData) = 0;
	virtual void _checkSpelling(std::string& strData) = 0;
	virtual void _checkDataFormat(std::string& strData) const = 0;
};