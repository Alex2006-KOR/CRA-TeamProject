#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDCommand.cpp"
#include "ReadCommand.cpp"
#include "WriteCommand.cpp"
#include "FullReadCommand.cpp"
#include "FullWriteCommand.cpp"
#include "ExitCommand.cpp"
#include "HelpCommand.cpp"
#include "InvalidCommand.cpp"
#include "SSDCommandInvoker.cpp"
#include "Shell.cpp"

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

	std::string RunCommands(string strCommandLines) {
		std::istringstream input(strCommandLines);
		std::ostringstream output;

		shell.Run(input, output);

		return output.str();
	}

	std::string RunSingleCommand(string strCommandLine) {
		std::ostringstream output;

		shell.handleCommand(strCommandLine, output);

		return output.str();
	}

protected:
	void SetUp() override {
	}
};

// Read Command
// Read	Success Case

TEST_F(TestShellApplicationTestFixture, ReadZeroTest) {
	std::string strCommandLine = "read 10";
	std::string strExpectedResult = "0x00000000\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ReadReturnFormat) {
	std::string strCommandLine = "read 10";
	std::string strExpectedResult_prefix = "0x";
	std::string strExpectedResult_postfix = "\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(1)
		.WillRepeatedly(Return(0x00000000));

	string strOutput = RunSingleCommand(strCommandLine);

	EXPECT_EQ(strOutput.substr(0, 2), strExpectedResult_prefix);
	EXPECT_EQ(strOutput.substr(strOutput.size() - 1), strExpectedResult_postfix);
}

// Read	Exception Case

TEST_F(TestShellApplicationTestFixture, ExceptionTestInvalidCharCase1) {
	std::string strCommandLine = "read ABC";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}


TEST_F(TestShellApplicationTestFixture, ExceptionTestInvalidCharCase2) {
	std::string strCommandLine = "read 0ABD";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ExceptionTestLBANonInDecimal) {
	std::string strCommandLine = "read 0x100";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ExceptionTestLBAOverMaxLBA) {
	std::string strCommandLine = "read -10";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, ExceptionTestLBAUnderMinLBA) {
	std::string strCommandLine = "read 100";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullReadAllZero) {
	std::string strCommandLine = "fullread";
	std::string strExpectedResult = "0x00000000\n";
	std::string strExpectedResultFull;

	const int LBA_CNT = 100;
	for (int i = 0; i < LBA_CNT; ++i) {
		strExpectedResultFull += strExpectedResult;
	}

	EXPECT_CALL(ssdMock, Read)
		.Times(LBA_CNT)
		.WillRepeatedly(Return(0x00000000));

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResultFull);
}

TEST_F(TestShellApplicationTestFixture, FullReadSomeValidData) {
	std::string strCommandLine = "fullread";
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

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResultFull);
}



TEST_F(TestShellApplicationTestFixture, WriteAndReadOnceTest) {
	std::string strCommandLine = "write 10 0x000000AA\nread 10\nexit\n";
	std::string strExpectedResult = "0x000000AA\n";

	EXPECT_CALL(ssdMock, Write(10, 0xAA))
		.Times(1);

	EXPECT_CALL(ssdMock, Read(10))
		.Times(1)
		.WillRepeatedly(Return(0x000000AA));

	EXPECT_EQ(RunCommands(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidCharacterLBATest) {
	std::string strCommandLine = "write 0A 0x000000AA";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidRangeLBATest) {
	std::string strCommandLine = "write 101 0x000000AA";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteInvalidCharacterDataTest) {
	std::string strCommandLine = "write 10 0x0000GED0";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteNotStart0xDataTest) {
	std::string strCommandLine = "write 10 000000AA";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, WriteNot8CharacterDataTest) {
	std::string strCommandLine = "write 10 0x123456";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullWriteTest) {
	std::string strCommandLine = "fullwrite 0xABCDFFFF";

	EXPECT_CALL(ssdMock, Write(_, 0xABCDFFFF))
		.Times(100);

	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
}

TEST_F(TestShellApplicationTestFixture, FullWriteInvalidCharacterDataTest) {
	std::string strCommandLine = "fullwrite 0x0000GED0";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullWriteNotStart0xDataTest) {
	std::string strCommandLine = "fullwrite 000000AA";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, FullWriteNot8CharacterDataTest) {
	std::string strCommandLine = "fullwrite 0x123456";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}


// Other Commands

 // help
TEST_F(TestShellApplicationTestFixture, HelpWithoutNoError) {
	std::string strCommandLine = "help";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
}

TEST_F(TestShellApplicationTestFixture, HelpNoErrorReturn) {
	std::string strCommandLine = "help";
	std::string strExpectedResult = "INVALID COMMAND\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_NE(RunSingleCommand(strCommandLine), strExpectedResult);
}

 // exit 
TEST_F(TestShellApplicationTestFixture, ExitWithNoError) {
	std::string strCommandLine = "exit";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
}

TEST_F(TestShellApplicationTestFixture, ExitIgnoreFollowingCommands) {
	std::string strCommandLines = "exit\nread 10\n";
	std::string strExpectedResult = "";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunCommands(strCommandLines), strExpectedResult);
}

 // other commands

TEST_F(TestShellApplicationTestFixture, InvalidCommand) {
	std::string strCommandLine = "Read 10";
	std::string strExpectedResult = "INVALID COMMAND\n";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, EmptyCommand) {
	std::string strCommandLine = "";
	std::string strExpectedResult = "";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(TestShellApplicationTestFixture, EmptyCommandWithSpace) {
	std::string strCommandLine = " ";
	std::string strExpectedResult = "";

	EXPECT_CALL(ssdMock, Read)
		.Times(0);

	EXPECT_CALL(ssdMock, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}
