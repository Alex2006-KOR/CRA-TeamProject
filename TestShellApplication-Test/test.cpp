#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShellApplication/SSDCommand.cpp"
#include "../TestShellApplication/ReadCommand.cpp"
#include "../TestShellApplication/Shell.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(int, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
};

class TestShellApplicationTestFixture : public testing::Test {
public:
	SsdDeviceDriverMock ssdMock;

protected:
	void SetUp() override {
	}
};

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

TEST_F(TestShellApplicationTestFixture, ReadExceptionTestInvalidChar) {
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));

	Shell shell(&ssdMock);
	std::istringstream input("read ABC\n");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), invalid_argument);
}

TEST_F(TestShellApplicationTestFixture, ReadExceptionTestLBARangeExceeded) {
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));
	std::string expected = "0x00000000\n";

	Shell shell(&ssdMock);
	std::istringstream input("read -10\n");
	std::ostringstream output;

	EXPECT_THROW(shell.Run(input, output), invalid_argument);
}

TEST_F(TestShellApplicationTestFixture, ReadReturnFormat) {
	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));
	std::string expected_prefix = "0x";
	std::string expected_postfix = "\n";

	Shell shell(&ssdMock);
	std::istringstream input("read 10\n");
	std::ostringstream output;

	shell.Run(input, output);

	string strOutput = output.str();

	EXPECT_EQ(strOutput.substr(0, 2), expected_prefix);
	EXPECT_EQ(strOutput.substr(strOutput.size()-1), expected_postfix);
}

TEST_F(TestShellApplicationTestFixture, WriteAndReadOnceTest) {
	EXPECT_CALL(ssdMock, Write(10, 0xAA))
		.Times(1);
	EXPECT_CALL(ssdMock, Read(10))
		.Times(1)
		.WillRepeatedly(Return(0x000000AA));
	std::string expected = "0x000000AA\n";

	Shell shell(&ssdMock);
	std::istringstream input("write 10 0x000000AA\nread 10\n");
	std::ostringstream output;

	shell.Run(input, output);

	EXPECT_EQ(output.str(), expected);
}
