#pragma once
#include "Device.h"

#include <iomanip>
#include <iostream>

class TestLibrary {
public:
	virtual ~TestLibrary() = default;
	virtual void execute(const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData) const = 0;
};

class TestLibWrite : public TestLibrary {
public:
	TestLibWrite(Device* pstDevice, ostream* output = nullptr);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	ostream* m_out;

};

class TestLibRead : public TestLibrary {
public:
	TestLibRead(Device* pstDevice, ostream* output = nullptr);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	ostream* m_out;
};

class TestLibFullWrite : public TestLibrary {
public:
	TestLibFullWrite(Device* pstDevice, ostream* output = nullptr);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	ostream* m_out;
};

class TestLibFullRead : public TestLibrary {
public:
	TestLibFullRead(Device* pstDevice, ostream* output = nullptr);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	ostream* m_out;
};

class TestLibWriteRange : public TestLibrary {
public:
	TestLibWriteRange(Device* pstDevice, ostream* output = nullptr);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	ostream* m_out;
};

class TestLibReadRange : public TestLibrary {
public:
	TestLibReadRange(Device* pstDevice, ostream* output = nullptr);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	ostream* m_out;
};