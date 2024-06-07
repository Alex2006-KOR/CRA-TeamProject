#include "TestApp2Command.h"
#include <iomanip>
#include <stdexcept>

class TestApp2Exception : public std::exception {
public:
	explicit TestApp2Exception(const int lbaIdx) {
		_msg = "Read Different value from LBA Index " + to_string(lbaIdx);
	}

	char const* what() const override {
		return _msg.c_str();
	}

private:
	string _msg;
};

TestApp2Command::TestApp2Command(DriverInterface* pSSDDriver, ostream& output)
	: BaseSSDCommand(output)
	, m_pstSSDDriver(pSSDDriver)
{
}

bool TestApp2Command::_parseCommand() {
	constexpr int REQUIRED_COMMAND_COUNT = 0;
	if (m_vCommandList.size() != REQUIRED_COMMAND_COUNT) {
		m_out << "Invalid usage.\nCheck help message.\n";
		return false;
	}
	return true;
}

void TestApp2Command::_execute()
{
	int expected = 0x12345678;
	_agingWrite(expected);

	try {
		_agingWriteCheck(expected);
	}
	catch (exception& e) {
		m_out << e.what() << endl;
	}
}

void TestApp2Command::_agingWrite(int expected)
{
	for (int agingCnt = 0; agingCnt < 30; agingCnt++) {
		for (int lbaIdx = 0; lbaIdx < 6; lbaIdx++)
			m_pstSSDDriver->Write(lbaIdx, 0xAAAABBBB);
	}

	for (int lbaIdx = 0; lbaIdx < 6; lbaIdx++)
		m_pstSSDDriver->Write(lbaIdx, expected);
}

void TestApp2Command::_agingWriteCheck(int expected)
{
	for (int lbaIdx = 0; lbaIdx < 6; lbaIdx++) {
		int readValue = m_pstSSDDriver->Read(lbaIdx);
		if (readValue != expected)
			throw TestApp2Exception(lbaIdx);
	}
}