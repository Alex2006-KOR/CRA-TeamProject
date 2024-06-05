#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSD.cpp"
#include "DeviceDriver.cpp"
#include "FileManager.cpp"

using namespace testing;

class SSDMock : public SSDInterface {
public:
	MOCK_METHOD(bool, Read, (int nLba), (override));
	MOCK_METHOD(bool, Write, (int nLba, string sData), (override));
};

class DeviceDriverTestFixture : public testing::Test {
public:
	SSDMock ssdMock;
	DeviceDriver* pDeviceDriver = nullptr;

protected:
	// setup
	virtual void SetUp() {
		std::cout << "\tDeviceDriverTestFixture - SetUp" << std::endl;
		pDeviceDriver = new DeviceDriver(&ssdMock);
	}

	// teardown
	virtual void TearDown() {
		std::cout << "\tDeviceDriverTestFixture - TearDown" << std::endl;
		delete pDeviceDriver;
	}
};

TEST_F(DeviceDriverTestFixture, SimpleRead) {
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillOnce(Return(true));
	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	pDeviceDriver->ReadData(0);
}

TEST_F(DeviceDriverTestFixture, SimpleWrite) {
	EXPECT_CALL(ssdMock, Read)
		.Times(0);
	EXPECT_CALL(ssdMock, Write)
		.Times(1)
		.WillOnce(Return(true));

	pDeviceDriver->WriteData(0, "0x00000000");
}

TEST(RealSSDTestSuite, SimpleRead) {
	SSD stSSD;
	DeviceDriver* pDeviceDriver = new DeviceDriver(&stSSD);

	pDeviceDriver->WriteData(0, "0x0000ABCD");
	pDeviceDriver->ReadData(0);

	FileManager stResultFile("Result.txt");
	stResultFile.OpenReadStream();
	EXPECT_EQ(stResultFile.Read(), "0x0000ABCD");
	stResultFile.CloseReadStream();
}

TEST(RealSSDTestSuite, SimpleWrite) {
	SSD stSSD;
	DeviceDriver* pDeviceDriver = new DeviceDriver(&stSSD);

	pDeviceDriver->WriteData(0, "0xDEADDEAD");

	FileManager stNandFile("Nand.txt");
	stNandFile.OpenReadStream();
	EXPECT_EQ(stNandFile.Read(), "0xDEADDEAD");
	stNandFile.CloseReadStream();
}