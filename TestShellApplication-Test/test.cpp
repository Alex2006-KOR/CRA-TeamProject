#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "TestScripts/TestScriptBase.cpp"
#include "TestScripts/TestApp1.cpp"
#include "TestScripts/TestApp2.cpp"
#include "ReadCommand.cpp"
#include "WriteCommand.cpp"
#include "Device.cpp"
#include "TestLibrary.cpp"
#include "Shell.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(void, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
	MOCK_METHOD(std::string, ReadBuffer, (), (override));
	MOCK_METHOD(int, GetMinLba, (), (override));
	MOCK_METHOD(int, GetMaxLba, (), (override));
};


class ShellTestFixture : public Test {
public:
	SsdDeviceDriverMock mockDevice;
	std::ostringstream output;
	Shell shell{ &mockDevice };

	std::string RunCommands(std::string strCommandLines) {
		std::istringstream input(strCommandLines);

		shell.Run(input);

		return output.str();
	}

	std::string RunSingleCommand(std::string strCommandLine) {
		shell.handleCommand(strCommandLine);

		return output.str();
	}

protected:
	void SetUp() override {
		EXPECT_CALL(mockDevice, GetMinLba)
			.WillRepeatedly(Return(0));
		EXPECT_CALL(mockDevice, GetMaxLba)
			.WillRepeatedly(Return(100));
	}
};

// Read Command
// Read	Success Case

TEST_F(ShellTestFixture, ReadZeroTest) {
	std::string strCommandLine = "read 10";
	std::string strExpectedResult = "0x00000000\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(1);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(1)
		.WillRepeatedly(Return("0x00000000"));

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, ReadZeroTest_2) {
	std::string strCommandLine = "read 10\nread 10\nexit\n";
	std::string strExpectedResult = "0x00000000\n0x00000000\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(2);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(2)
		.WillRepeatedly(Return("0x00000000"));

	EXPECT_EQ(RunCommands(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, ReadReturnFormat) {
	std::string strCommandLine = "read 10";
	std::string strExpectedResult_prefix = "0x";
	std::string strExpectedResult_postfix = "\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(1);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(1)
		.WillRepeatedly(Return("0x00000000"));

	std::string strOutput = RunSingleCommand(strCommandLine);

	EXPECT_EQ(strOutput.substr(0, 2), strExpectedResult_prefix);
	EXPECT_EQ(strOutput.substr(strOutput.size() - 1), strExpectedResult_postfix);
}

// Read	Exception Case

TEST_F(ShellTestFixture, ExceptionTestInvalidCharCase1) {
	std::string strCommandLine = "read ABC\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}


TEST_F(ShellTestFixture, ExceptionTestInvalidCharCase2) {
	std::string strCommandLine = "read 0ABD\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, ExceptionTestLBANonInDecimal) {
	std::string strCommandLine = "read 0x100\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, ExceptionTestLBAOverMaxLBA) {
	std::string strCommandLine = "read -10\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, ExceptionTestLBAUnderMinLBA) {
	std::string strCommandLine = "read 100\n";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

// full read command

TEST_F(ShellTestFixture, FullReadAllZero) {
	std::string strCommandLine = "fullread";
	std::string strExpectedResult = "0x00000000\n";
	std::string strExpectedResultFull;

	const int LBA_CNT = 100;
	for (int i = 0; i < LBA_CNT; ++i) {
		strExpectedResultFull += strExpectedResult;
	}

	EXPECT_CALL(mockDevice, Read)
		.Times(LBA_CNT);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(LBA_CNT)
		.WillRepeatedly(Return("0x00000000"));

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResultFull);
}



TEST_F(ShellTestFixture, FullReadSomeValidData) {
	std::string strCommandLine = "fullread";
	std::string strExpectedResult = "0x00000000\n";
	std::string strExpectedResultFull;

	const int LBA_CNT = 100;
	strExpectedResultFull += "0x00000001\n";
	strExpectedResultFull += "0x00000011\n";

	for (int i = 0; i < LBA_CNT - 2; ++i) {
		strExpectedResultFull += strExpectedResult;
	}

	EXPECT_CALL(mockDevice, Read)
		.Times(LBA_CNT);
	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(LBA_CNT)
		.WillOnce(Return("0x00000001"))
		.WillOnce(Return("0x00000011"))
		.WillRepeatedly(Return("0x00000000"));

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResultFull);
}

// Write Command
// Write Success case

TEST_F(ShellTestFixture, WriteAndReadOnceTest) {
	std::string strCommandLine = "write 10 0x000000AA\nread 10\nexit\n";
	std::string strExpectedResult = "0x000000AA\n";

	EXPECT_CALL(mockDevice, Write(10, 0xAA))
		.Times(1);

	EXPECT_CALL(mockDevice, Read(10))
		.Times(1);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(1)
		.WillRepeatedly(Return("0x000000AA"));

	EXPECT_EQ(RunCommands(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, WriteInvalidCharacterLBATest) {
	std::string strCommandLine = "write 0A 0x000000AA";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, WriteInvalidRangeLBATest) {
	std::string strCommandLine = "write 101 0x000000AA";
	std::string strExpectedResult = "INVALID LBA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, WriteInvalidCharacterDataTest) {
	std::string strCommandLine = "write 10 0x0000GED0";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, WriteNotStart0xDataTest) {
	std::string strCommandLine = "write 10 000000AA";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, WriteNot8CharacterDataTest) {
	std::string strCommandLine = "write 10 0x123456";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

// fullwrite


TEST_F(ShellTestFixture, FullWriteTest) {
	std::string strCommandLine = "fullwrite 0xABCDFFFF";

	EXPECT_CALL(mockDevice, Write(_, 0xABCDFFFF))
		.Times(100);

	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
}

TEST_F(ShellTestFixture, FullWriteInvalidCharacterDataTest) {
	std::string strCommandLine = "fullwrite 0x0000GED0";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, FullWriteNotStart0xDataTest) {
	std::string strCommandLine = "fullwrite 000000AA";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, FullWriteNot8CharacterDataTest) {
	std::string strCommandLine = "fullwrite 0x123456";
	std::string strExpectedResult = "INVALID DATA\n";

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}


// Other Commands

 // help
TEST_F(ShellTestFixture, HelpWithoutNoError) {
	std::string strCommandLine = "help";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
}

TEST_F(ShellTestFixture, HelpNoErrorReturn) {
	std::string strCommandLine = "help";
	std::string strExpectedResult = "INVALID COMMAND\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_NE(RunSingleCommand(strCommandLine), strExpectedResult);
}

// exit 
TEST_F(ShellTestFixture, ExitWithNoError) {
	std::string strCommandLine = "exit";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
}

TEST_F(ShellTestFixture, ExitIgnoreFollowingCommands) {
	std::string strCommandLines = "exit\nread 10\n";
	std::string strExpectedResult = "";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunCommands(strCommandLines), strExpectedResult);
}

// other commands

TEST_F(ShellTestFixture, InvalidCommand) {
	std::string strCommandLine = "Read 10";
	std::string strExpectedResult = "INVALID COMMAND\n";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, EmptyCommand) {
	std::string strCommandLine = "";
	std::string strExpectedResult = "";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

TEST_F(ShellTestFixture, EmptyCommandWithSpace) {
	std::string strCommandLine = " ";
	std::string strExpectedResult = "";

	EXPECT_CALL(mockDevice, Read)
		.Times(0);

	EXPECT_CALL(mockDevice, Write)
		.Times(0);

	EXPECT_CALL(mockDevice, ReadBuffer)
		.Times(0);

	EXPECT_EQ(RunSingleCommand(strCommandLine), strExpectedResult);
}

//// TestCase
//
//
//TEST_F(ShellTestFixture, TestApp1ExecuteMatchCase) {
//	std::string strCommandLine = "testapp1";
//	EXPECT_CALL(mockDevice, Write)
//		.Times(100);
//
//	EXPECT_CALL(mockDevice, Read)
//		.Times(100);
//
//	EXPECT_CALL(mockDevice, ReadBuffer)
//		.Times(100)
//		.WillRepeatedly(Return(0xABCD1234));
//
//	EXPECT_NO_THROW(RunSingleCommand(strCommandLine));
//}
//
//TEST_F(ShellTestFixture, TestApp1ExecuteMisMatchCase) {
//	EXPECT_CALL(mockDevice, Write)
//		.Times(100);
//
//	EXPECT_CALL(mockDevice, Read)
//		.Times(1);
//
//	EXPECT_CALL(mockDevice, ReadBuffer)
//		.Times(1)
//		.WillRepeatedly(Return(0xABCDFFFF));
//
//	EXPECT_NO_THROW(testApp1Command->Execute());
//}
//
//
//TEST_F(ShellTestFixture, TestApp2ExecuteMatchCase) {
//	EXPECT_CALL(mockDevice, Read)
//		.Times(6)
//		.WillRepeatedly(Return(0x12345678));
//
//	EXPECT_CALL(mockDevice, Write)
//		.Times(6 * 30 + 6);
//
//	EXPECT_NO_THROW(testApp2Command->Execute());
//}
//
//TEST_F(ShellTestFixture, TestApp2ExecuteMisMatchCase) {
//	EXPECT_CALL(mockDevice, Read)
//		.Times(1)
//		.WillRepeatedly(Return(0xAAAABBBB));
//
//	EXPECT_CALL(mockDevice, Write)
//		.Times(6 * 30 + 6);
//
//	EXPECT_NO_THROW(testApp2Command->Execute());
//}