#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IOManager.cpp"

using namespace testing;

class DeviceDriverMock : public DeviceDriver {
public:
	DeviceDriverMock()
		: DeviceDriver(nullptr) {}

	MOCK_METHOD(void, ReadData, (int nLbaNumber), ());
	MOCK_METHOD(void, WriteData, (int nLbaNumber, string sData), ());
};

class IOManagerTestFixture : public testing::Test {
public:
	DeviceDriverMock deviceDriverMock;
	IOManager* pStIOManager = nullptr;

protected:
	// �ʱ�ȭ
	virtual void SetUp() {
		std::cout << "\IOManagerTestFixture - SetUp" << std::endl;
		pStIOManager = new IOManager(&deviceDriverMock);
	}

	// ����
	virtual void TearDown() {
		std::cout << "\IOManagerTestFixture - TearDown" << std::endl;
		delete pStIOManager;
	}
};

TEST_F(IOManagerTestFixture, InvalidCommand) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	try {
		pStIOManager->DoCommand(string("Q"), 12, string("0x0000ABCD"));
	}
	catch (exception& e) {
		FAIL();
	}
}

TEST_F(IOManagerTestFixture, WriteInvalidData) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	try {
		pStIOManager->DoCommand("W", 0, "0xQWERZXCV");
	}
	catch (exception& e) {
		FAIL();
	}
}

TEST_F(IOManagerTestFixture, ReadInvalidData) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	try {
		pStIOManager->DoCommand("R", 0, "0xQWERZXCV");
	}
	catch (exception& e) {
		FAIL();
	}
}