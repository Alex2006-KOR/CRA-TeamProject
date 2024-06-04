#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ssd_interface.h"
#include "DeviceDriver.cpp"
#include "IOManager.cpp"

using namespace testing;

class SSDMock : public SSDInterface {
public:
	MOCK_METHOD(bool, read, (int nLba), (override));
	MOCK_METHOD(bool, write, (int nLba, string sData), (override));
};

class DeviceDriverTestFixture : public testing::Test {
public:
	SSDMock ssdMock;
	DeviceDriver* pDeviceDriver = nullptr;
	IOManager* pStIOManager = nullptr;

protected:
	// 초기화
	virtual void SetUp() {
		std::cout << "\tDeviceDriverTestFixture - SetUp" << std::endl;
		pDeviceDriver = new DeviceDriver(&ssdMock);
		pStIOManager = new IOManager(pDeviceDriver);
	}

	// 정리
	virtual void TearDown() {
		std::cout << "\tDeviceDriverTestFixture - TearDown" << std::endl;
		delete pDeviceDriver;
		delete pStIOManager;
	}
};

TEST_F(DeviceDriverTestFixture, SimpleRead) {
	EXPECT_CALL(ssdMock, read)
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(ssdMock, write)
		.Times(0);

	pDeviceDriver->ReadData(0);
}

TEST_F(DeviceDriverTestFixture, SimpleWrite) {
	EXPECT_CALL(ssdMock, read)
		.Times(0);
	EXPECT_CALL(ssdMock, write)
		.Times(1)
		.WillOnce(Return(true));

	pDeviceDriver->WriteData(0, "0x00000000");
}

TEST_F(DeviceDriverTestFixture, InvalidCommand) {
	EXPECT_CALL(ssdMock, read)
		.Times(0);
	EXPECT_CALL(ssdMock, write)
		.Times(0);

	try {
		pStIOManager->DoCommand(string("Q"), 12, string("0x0000ABCD"));
	}
	catch (exception& e) {
		FAIL();
	}	
}

TEST_F(DeviceDriverTestFixture, WriteInvalidData) {
	EXPECT_CALL(ssdMock, read)
		.Times(0);
	EXPECT_CALL(ssdMock, write)
		.Times(0);

	try {
		pStIOManager->DoCommand("W", 0, "0xQWERZXCV");
	}
	catch (exception& e) {
		FAIL();
	}
}

TEST_F(DeviceDriverTestFixture, ReadInvalidData) {
	EXPECT_CALL(ssdMock, read)
		.Times(0);
	EXPECT_CALL(ssdMock, write)
		.Times(0);

	try {
		pStIOManager->DoCommand("R", 0, "0xQWERZXCV");
	}
	catch (exception& e) {
		FAIL();
	}
}