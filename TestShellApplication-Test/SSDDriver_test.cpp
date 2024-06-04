#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.cpp"

using namespace testing;
using std::string;

class SSDDriverTestFixture : public SSDDriver, public testing::Test {
public:
	string expectedCommand;

	void doWriteCommandTest(int lba, int data) {
		expectedCommand = "VirtualSSD.exe W " + to_string(lba) + " " + to_string(data);
		Write(lba, data);
	}

	void doReadCommandTest(int lba) {
		expectedCommand = "VirtualSSD.exe R " + to_string(lba);
		Read(lba);
	}

protected:
	int ExecuteCommand(string command) override {
		if (expectedCommand != "")
			EXPECT_EQ(expectedCommand, command);
		return 1;
	}

	void SetUp() override {
		expectedCommand = "";
	}
};

TEST_F(SSDDriverTestFixture, InterfaceTest) {
	Write(0, 0);
	EXPECT_EQ(1, Read(0));
}

TEST_F(SSDDriverTestFixture, CommandTest) {
	doWriteCommandTest(50, 0xFFFFABCD);
	doReadCommandTest(50);
}