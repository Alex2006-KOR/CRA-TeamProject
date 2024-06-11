#pragma once

#define interface struct

#include <string>
#include <vector>

using std::string;
using std::vector;

interface TestLibrary {
public:
	virtual ~TestLibrary() {}

public:
	virtual bool execute() const = 0;

	TestLibrary& setCommandList(const std::vector<std::string>& vCommandList = {}) {
		m_vCommandList = vCommandList;
		return *this;
	}
	TestLibrary& setStartLba(int nStartLba = -1) {
		m_nStartLba = nStartLba;
		return *this;
	}
	TestLibrary& setEndLba(int nEndLba = -1) {
		m_nEndLba = nEndLba;
		return *this;
	}
	TestLibrary& setData(const std::string& strData = "") {
		m_strData = strData;
		return *this;
	}

protected:
	std::vector<std::string> m_vCommandList;
	int m_nStartLba;
	int m_nEndLba;
	std::string m_strData;
};
