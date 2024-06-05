#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.h"
#include "SSDCommandInvoker.h"
#include "TestApp1Command.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(int, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
};

class TestApp1CommandTestFixture : public testing::Test {
public:
	SsdDeviceDriverMock ssd;
	SSDComamnd* testApp1Command;

protected:
	void SetUp() override {
		SSDCommandInvoker pCommandInvoker(&ssd, std::cout);
		testApp1Command = pCommandInvoker.GetCommand("testapp1");
	}

	void TearDown() override {
	}
};

TEST_F(TestApp1CommandTestFixture, CommandExecuteMatchCase) {
	EXPECT_CALL(ssd, Read)
		.Times(100)
		.WillRepeatedly(Return(0xABCD1234));

	EXPECT_CALL(ssd, Write)
		.Times(100);

	EXPECT_NO_THROW(testApp1Command->Execute());
}

TEST_F(TestApp1CommandTestFixture, CommandExecuteMisMatchCase) {
	EXPECT_CALL(ssd, Read)
		.Times(1)
		.WillRepeatedly(Return(0xABCDFFFF));

	EXPECT_CALL(ssd, Write)
		.Times(100);

	EXPECT_NO_THROW(testApp1Command->Execute());
}