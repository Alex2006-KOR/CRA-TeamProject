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
	// 초기화
	virtual void SetUp() {
		std::cout << "\IOManagerTestFixture - SetUp" << std::endl;
		pStIOManager = new IOManager(&deviceDriverMock);
	}

	// 정리
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
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}

TEST_F(IOManagerTestFixture, WriteInvalidData00) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	try {
		pStIOManager->DoCommand(string("W"), 0, string("0xQWERZXCV"));
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}

TEST_F(IOManagerTestFixture, WriteInvalidData01) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	try {
		pStIOManager->DoCommand(string("W"), -5, string("0x00001111"));
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}


TEST_F(IOManagerTestFixture, ReadInvalidData) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	try {
		pStIOManager->DoCommand(string("R"), -5);
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}