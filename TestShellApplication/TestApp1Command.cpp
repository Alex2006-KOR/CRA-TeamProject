#include "TestApp1Command.h"
#include <iomanip>
#include <stdexcept>

class TestApp1Exception : public std::exception {
public:
	explicit TestApp1Exception(const int lbaIdx) {
		_msg = "Read Different value from LBA Index " + to_string(lbaIdx);
	}

	char const* what() const override {
		return _msg.c_str();
	}

private:
	string _msg;
};

TestApp1Command::TestApp1Command(vector<string> vCommandList, DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(vCommandList)
	, m_pstSSDDriver(pSSDDriver)
	, m_out(output)
{
}

bool TestApp1Command::_parseCommand() {
	constexpr int REQUIRED_COMMAND_COUNT = 0;
	if (m_vCommandList.size() != REQUIRED_COMMAND_COUNT) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}
	return true;
}

void TestApp1Command::_execute()
{
	int expected = 0xABCD1234;
	_fullWrite(expected);

	try {
		_fullWriteCheck(expected);
	}
	catch (exception& e) {
		m_out << e.what() << endl;
	}
}

void TestApp1Command::_fullWrite(int expected) {
	for (int lbaIdx = 0; lbaIdx < 100; lbaIdx++)
		m_pstSSDDriver->Write(lbaIdx, expected);
}

void TestApp1Command::_fullWriteCheck(int expected) {
	for (int lbaIdx = 0; lbaIdx < 100; lbaIdx++) {
		int readValue = m_pstSSDDriver->Read(lbaIdx);
		if (readValue != expected)
			throw TestApp1Exception(lbaIdx);
	}
}