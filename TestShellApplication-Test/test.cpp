#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(int, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
};

class TestShellApplicationTestFixture : public testing::Test {
public:
	SSDDriver ssdDriver;
	SsdDeviceDriverMock ssdMock;

protected:
	void SetUp() override {
		EXPECT_CALL(ssdMock, Read(_))
			.WillRepeatedly(Return(0x0));

		EXPECT_CALL(ssdMock, Write(_, _))
			.WillRepeatedly(Return());
	}
};

TEST_F(TestShellApplicationTestFixture, InterfaceTest) {
	ssdDriver.Write(0, 0);
	EXPECT_EQ(0x0, ssdDriver.Read(0));
}