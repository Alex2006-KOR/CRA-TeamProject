#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.h"
#include "SSDCommandInvoker.h"
#include "TestApp1Command.cpp"
#include "TestApp2Command.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(int, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
};

class TestAppCommandTestFixture : public testing::Test {
public:
	SsdDeviceDriverMock ssd;
	SSDComamnd* testApp1Command = nullptr;
	SSDComamnd* testApp2Command = nullptr;

protected:
	void SetUp() override {
		SSDCommandInvoker pCommandInvoker(&ssd, std::cout);
		testApp1Command = pCommandInvoker.GetCommand("testapp1");
		testApp2Command = pCommandInvoker.GetCommand("testapp2");
	}
};

TEST_F(TestAppCommandTestFixture, TestApp1ExecuteMatchCase) {
	EXPECT_CALL(ssd, Read)
		.Times(100)
		.WillRepeatedly(Return(0xABCD1234));

	EXPECT_CALL(ssd, Write)
		.Times(100);

	EXPECT_NO_THROW(testApp1Command->Execute());
}

TEST_F(TestAppCommandTestFixture, TestApp1ExecuteMisMatchCase) {
	EXPECT_CALL(ssd, Read)
		.Times(1)
		.WillRepeatedly(Return(0xABCDFFFF));

	EXPECT_CALL(ssd, Write)
		.Times(100);

	EXPECT_NO_THROW(testApp1Command->Execute());
}


TEST_F(TestAppCommandTestFixture, TestApp2ExecuteMatchCase) {
	EXPECT_CALL(ssd, Read)
		.Times(6)
		.WillRepeatedly(Return(0x12345678));

	EXPECT_CALL(ssd, Write)
		.Times(6 * 30 + 6);

	EXPECT_NO_THROW(testApp2Command->Execute());
}

TEST_F(TestAppCommandTestFixture, TestApp2ExecuteMisMatchCase) {
	EXPECT_CALL(ssd, Read)
		.Times(1)
		.WillRepeatedly(Return(0xAAAABBBB));

	EXPECT_CALL(ssd, Write)
		.Times(6*30 + 6);

	EXPECT_NO_THROW(testApp2Command->Execute());
}