#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "ssd_interface.h"
#include "DeviceDriver.cpp"

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

protected:
	// 초기화
	virtual void SetUp() {
		std::cout << "\tDeviceDriverTestFixture - SetUp" << std::endl;
		pDeviceDriver = new DeviceDriver(&ssdMock);
	}

	// 정리
	virtual void TearDown() {
		std::cout << "\tDeviceDriverTestFixture - TearDown" << std::endl;
		delete pDeviceDriver;
	}
};

TEST_F(DeviceDriverTestFixture, Read) {
	EXPECT_CALL(ssdMock, read)
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(ssdMock, write)
		.Times(0);

	pDeviceDriver->ReadData(0);
}

TEST_F(DeviceDriverTestFixture, ReadOverflowIndex) {
	EXPECT_CALL(ssdMock, read)
		.Times(0)
		.WillOnce(Return(true));
	EXPECT_CALL(ssdMock, write)
		.Times(1);

	pDeviceDriver->WriteData(0, 0);
}