#include "TestLibraryCommandInvoker.h"

TestLibCommandInvoker::TestLibCommandInvoker(DriverInterface* pstDriver)
{
	_initCommands(new Device(pstDriver));
}

TestLibrary* TestLibCommandInvoker::GetFunction(string strCommand)
{
	auto iterFind = m_mapCommand.find(strCommand);
	if (iterFind == m_mapCommand.end()) {
		return nullptr;
	}
	return iterFind->second;
}

void TestLibCommandInvoker::Run(TestLibrary* stFunction, const vector<string>& vCommandList, int nStartLba, int nEndLba, const string& strData)
{
	stFunction->execute(vCommandList, nStartLba, nEndLba, strData);
}

void TestLibCommandInvoker::_initCommands(Device* pstDevice)
{
	m_mapCommand["write"] = new TestLibWrite(pstDevice);
	m_mapCommand["read"] = new TestLibRead(pstDevice);
	m_mapCommand["fullwrite"] = new TestLibFullWrite(pstDevice);
	m_mapCommand["fullread"] = new TestLibFullRead(pstDevice);
	m_mapCommand["write_range"] = new TestLibWriteRange(pstDevice);
	m_mapCommand["read_range"] = new TestLibReadRange(pstDevice);
}