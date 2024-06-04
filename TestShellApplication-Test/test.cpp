#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.cpp"
#include "../TestShellApplication/Shell.cpp"

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
	}
};

TEST_F(TestShellApplicationTestFixture, InterfaceTest) {
	ssdDriver.Write(0, 0);
	EXPECT_EQ(0x0, ssdDriver.Read(0));
}

TEST_F(TestShellApplicationTestFixture, ReadZeroTest) {
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));
	std::string expected = "0x00000000\n";

	Shell shell(&ssdMock);
	std::istringstream input("read 10\n");
	std::ostringstream output;

	shell.Run(input, output);

	EXPECT_EQ(output.str(), expected);
}

TEST_F(TestShellApplicationTestFixture, WriteAndReadOnceTest) {
	EXPECT_CALL(ssdMock, Write(10, 0xAA))
		.Times(1);
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x000000AA));
	std::string expected = "0x000000AA\n";

	Shell shell(&ssdMock);
	std::istringstream input("write 10 0x000000AA\nread 10\n");
	std::ostringstream output;

	shell.Run(input, output);

	EXPECT_EQ(output.str(), expected);
}
