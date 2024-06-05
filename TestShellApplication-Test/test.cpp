#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TestShellApplication/SSDCommand.cpp"
#include "../TestShellApplication/ReadCommand.cpp"
#include "../TestShellApplication/WriteCommand.cpp"
#include "../TestShellApplication/FullWriteCommand.cpp"
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
	Shell shell{ &ssdMock };

	std::string RunCommand(string strCommandLine) {
		std::istringstream input(strCommandLine);
		std::ostringstream output;

		shell.Run(input, output);

		return output.str();
	}

protected:
	void SetUp() override {
	}
};

// Read Command
// Read	Success Case

TEST_F(TestShellApplicationTestFixture, ReadZeroTest) {
	std::string strCommandLine = "read 10\n";
	std::string strExpectedResult = "0x00000000\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ReadReturnFormat) {
	std::string strCommandLine = "read 10\n";
	std::string strExpectedResult_prefix = "0x";
	std::string strExpectedResult_postfix = "\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));

	string strOutput = RunCommand(strCommandLine);

	EXPECT_EQ(strOutput.substr(0, 2), strExpectedResult_prefix);
	EXPECT_EQ(strOutput.substr(strOutput.size() - 1), strExpectedResult_postfix);
}

// Read	Exception Case

TEST_F(TestShellApplicationTestFixture, ExceptionTestInvalidCharCase1) {
	std::string strCommandLine = "read ABC\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}


TEST_F(TestShellApplicationTestFixture, ExceptionTestInvalidCharCase2) {
	std::string strCommandLine = "read 0ABD\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ExceptionTestLBANonInDecimal) {
	std::string strCommandLine = "read 0x100\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ExceptionTestLBAOverMaxLBA) {
	std::string strCommandLine = "read -10\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ExceptionTestLBAUnderMinLBA) {
	std::string strCommandLine = "read 100\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullReadAllZero) {
	std::string strCommandLine = "fullread\n";
	std::string strExpectedResult = "0x00000000\n";
	std::string strExpectedResultFull;

	const int LBA_CNT = 100;
	for (int i = 0; i < LBA_CNT; ++i) {
		strExpectedResultFull += strExpectedResult;
	}

	EXPECT_CALL(ssdMock, Read)
		.Times(LBA_CNT)
		.WillRepeatedly(Return(0x00000000));

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResultFull);
}

TEST_F(TestShellApplicationTestFixture, FullReadSomeValidData) {
	std::string strCommandLine = "fullread\n";
	std::string strExpectedResult = "0x00000000\n";
	std::string strExpectedResultFull;

	const int LBA_CNT = 100;
	strExpectedResultFull += "0x00000001\n";
	strExpectedResultFull += "0x00000011\n";

	for (int i = 0; i < LBA_CNT - 2; ++i) {
		strExpectedResultFull += strExpectedResult;
	}

	EXPECT_CALL(ssdMock, Read)
		.Times(LBA_CNT)
		.WillOnce(Return(0x00000001))
		.WillOnce(Return(0x00000011))
		.WillRepeatedly(Return(0x00000000));

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResultFull);
}



TEST_F(TestShellApplicationTestFixture, WriteAndReadOnceTest) {
	std::string strCommandLine = "write 10 0x000000AA\nread 10\n";
	std::string strExpectedResult = "0x000000AA\n";

	EXPECT_CALL(ssdMock, Write(10, 0xAA))
		.Times(1);
	
	EXPECT_CALL(ssdMock, Read(10))
		.Times(1)
		.WillRepeatedly(Return(0x000000AA));

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidCharacterLBATest) {
	std::string strCommandLine = "write 0A 0x000000AA\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidRangeLBATest) {
	std::string strCommandLine = "write 101 0x000000AA\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidCharacterDataTest) {
	std::string strCommandLine = "write 10 0x0000GED0\n";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteNotStart0xDataTest) {
	std::string strCommandLine = "write 10 000000AA\n";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteNot8CharacterDataTest) {
	std::string strCommandLine = "write 10 0x123456\n";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullWriteTest) {
	std::string strCommandLine = "fullwrite 0xABCDFFFF\n";

	EXPECT_CALL(ssdMock, Write(_, 0xABCDFFFF))
		.Times(100);

	RunCommand(strCommandLine);
}

TEST_F(TestShellApplicationTestFixture, FullWriteInvalidCharacterDataTest) {
	std::string strCommandLine = "fullwrite 0x0000GED0\n";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullWriteNotStart0xDataTest) {
	std::string strCommandLine = "fullwrite 000000AA\n";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullWriteNot8CharacterDataTest) {
	std::string strCommandLine = "fullwrite 0x123456\n";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommand(strCommandLine), strExpectedResult);
}
