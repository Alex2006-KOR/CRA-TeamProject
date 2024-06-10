#pragma once
#include "Device.h"
#include "TestLibraryInterface.h"

#include <iomanip>
#include <iostream>

class TestLibWrite : public TestLibrary {
public:
	TestLibWrite(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;

};

class TestLibRead : public TestLibrary {
public:
	TestLibRead(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibErase : public TestLibrary {
public:
	TestLibErase(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibFlush : public TestLibrary {
public:
	TestLibFlush(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibFullWrite : public TestLibrary {
public:
	TestLibFullWrite(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibFullRead : public TestLibrary {
public:
	TestLibFullRead(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibWriteRange : public TestLibrary {
public:
	TestLibWriteRange(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibReadRange : public TestLibrary {
public:
	TestLibReadRange(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
};

class TestLibEraseRange : public TestLibrary {
public:
	TestLibEraseRange(Device* pstDevice);
	void execute(const vector<string>& vCommandList = {}, int nStartLba = -1, int nEndLba = -1, const string& strData = "") const override;
private:
	Device* m_pstDevice;
	void _validateArguments(const std::vector<std::string>& vCommandList) const;

};