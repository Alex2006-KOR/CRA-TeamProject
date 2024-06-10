#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.cpp"

using namespace testing;
using std::string;

class SSDDriverInterfaceTestFixture : public SSDDriver, public testing::Test {
public:
	string expectedCommand;
	MOCK_METHOD(void, _executeCommand, (const char* strCommand), ());

	void doWriteCommandTest(int lba, int data) {
		std::stringstream ss;
		ss << "0x" << hex << std::uppercase
			<< setw(8) << setfill('0') << data;

		expectedCommand = "VirtualSSD.exe W " +
			to_string(lba) + " " + ss.str();
		Write(lba, data);
	}

	void doReadCommandTest(int lba) {
		expectedCommand = "VirtualSSD.exe R " +
			to_string(lba);
		Read(lba);
	}


protected:
	void SetUp() override {
		expectedCommand = "";
		EXPECT_CALL(*this, _executeCommand(_))
			.WillRepeatedly(Return());
	}
};

TEST_F(SSDDriverInterfaceTestFixture, InterfaceTest) {
	doWriteCommandTest(50, 0xFFFFABCD);
	doReadCommandTest(50);
}

class SSDDriverExecuteTestFixture : public SSDDriver, public testing::Test {
public:
	MOCK_METHOD(void, _executeCommand, (const char* strCommand), ());
	MOCK_METHOD(bool, _getSsdExisted, (), ());
	MOCK_METHOD(string, _getSsdResult, (), ());

protected:

	void SetUp() override {
		// set default case return value
		EXPECT_CALL(*this, _getSsdExisted)
			.WillRepeatedly(Return(true));
		EXPECT_CALL(*this, _getSsdResult)
			.WillRepeatedly(Return("0x00000000"));
	}
};

TEST_F(SSDDriverExecuteTestFixture, BasicReadWriteTest) {
	EXPECT_CALL(*this, _executeCommand)
		.WillRepeatedly(Return());
	EXPECT_CALL(*this, _getSsdResult)
		.WillRepeatedly(Return("0x1234FFFF"));
	Write(0, 0x1234FFFF);
	Read(0);
	EXPECT_EQ("0x1234FFFF", ReadBuffer());
}

TEST_F(SSDDriverExecuteTestFixture, ReadExecutionExceptionTest) {
	EXPECT_CALL(*this, _executeCommand)
		.WillRepeatedly(Throw(exception()));
	try {
		Read(-1);
		ReadBuffer();
		FAIL();
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}

TEST_F(SSDDriverExecuteTestFixture, WriteExecutionExceptionTest) {
	EXPECT_CALL(*this, _executeCommand)
		.WillRepeatedly(Throw(exception()));
	try {
		Write(0, 0x1234FFFF);
		FAIL();
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}