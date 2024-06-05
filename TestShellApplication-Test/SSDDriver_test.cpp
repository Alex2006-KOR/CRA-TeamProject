#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.cpp"

using namespace testing;
using std::string;

class SSDDriverInterfaceTestFixture : public SSDDriver, public testing::Test {
public:
	string expectedCommand;

	void doWriteCommandTest(int lba, int data) {
		expectedCommand = "VirtualSSD.exe W " + 
			to_string(lba) + " " + to_string(data);
		Write(lba, data);
	}

	void doReadCommandTest(int lba) {
		expectedCommand = "VirtualSSD.exe R " + 
			to_string(lba);
		Read(lba);
	}

protected:
	int _executeCommand(string command) override {
		if (expectedCommand != "")
			EXPECT_EQ(expectedCommand, command);
		return 1;
	}

	void SetUp() override {
		expectedCommand = "";
	}
};

TEST_F(SSDDriverInterfaceTestFixture, InterfaceTest) {
	doWriteCommandTest(50, 0xFFFFABCD);
	doReadCommandTest(50);
}

class SSDDriverExecuteTestFixture : public SSDDriver, public testing::Test {
protected:
	MOCK_METHOD(int, _executeCommand, (string command), (override));
	MOCK_METHOD(bool, _getSsdExisted, (), (override));
	MOCK_METHOD(int, _getSsdResult, (), (override));

	void SetUp() override {
		// set default case return value
		EXPECT_CALL(*this, _executeCommand)
			.WillRepeatedly(Return(0));
		EXPECT_CALL(*this, _getSsdExisted)
			.WillRepeatedly(Return(true));
		EXPECT_CALL(*this, _getSsdResult)
			.WillRepeatedly(Return(0));
	}
};

TEST_F(SSDDriverExecuteTestFixture, BasicReadWriteTest) {
	EXPECT_CALL(*this, _getSsdResult)
		.WillRepeatedly(Return(0x1234FFFF));
	Write(0, 0x1234FFFF);
	EXPECT_EQ(0x1234FFFF, Read(0));
}

TEST_F(SSDDriverExecuteTestFixture, ReadExecutionExceptionTest) {
	EXPECT_CALL(*this, _executeCommand)
		.WillRepeatedly(Return(-1));

	try {
		EXPECT_EQ(0, Read(0));
	}
	catch (exception& e) {
		cout << e.what() << endl;
		FAIL();
	}
}

TEST_F(SSDDriverExecuteTestFixture, WriteExecutionExceptionTest) {
	EXPECT_CALL(*this, _executeCommand)
		.WillRepeatedly(Return(-1));

	try {
		Write(0, 0x1234FFFF);
	}
	catch (exception& e) {
		cout << e.what() << endl;
		FAIL();
	}
}