#include "TestLibraryCommandInvoker.h"

TestLibCommandInvoker::TestLibCommandInvoker(DriverInterface* pstDriver, ostream* output)
{
	_initCommands(new Device(pstDriver), output);
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

void TestLibCommandInvoker::_initCommands(Device* pstDevice, ostream* output)
{
	m_mapCommand["write"] = new TestLibWrite(pstDevice, output);
	m_mapCommand["read"] = new TestLibRead(pstDevice, output);
	m_mapCommand["fullwrite"] = new TestLibFullWrite(pstDevice, output);
	m_mapCommand["fullread"] = new TestLibFullRead(pstDevice, output);
	m_mapCommand["write_range"] = new TestLibWriteRange(pstDevice, output);
	m_mapCommand["read_range"] = new TestLibReadRange(pstDevice, output);
}
