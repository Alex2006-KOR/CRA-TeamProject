#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.h"
#include "SSDCommandInvoker.h"
#include "TestApp1Command.cpp"
#include "TestApp2Command.cpp"

using namespace testing;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(void, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
	MOCK_METHOD(std::string, ReadBuffer, (), (override));
	MOCK_METHOD(int, GetMinLba, (), (override));
	MOCK_METHOD(int, GetMaxLba, (), (override));
};

class TestAppCommandTestFixture : public testing::Test {
public:
	SsdDeviceDriverMock ssd;
	SSDComamnd* testApp1Command = nullptr;
	SSDComamnd* testApp2Command = nullptr;

protected:
	void SetUp() override {
		EXPECT_CALL(ssd, GetMinLba)
			.WillRepeatedly(Return(0));
		EXPECT_CALL(ssd, GetMaxLba)
			.WillRepeatedly(Return(100));

		SSDCommandInvoker pCommandInvoker(&ssd, std::cout);
		testApp1Command = pCommandInvoker.GetCommand("testapp1");
		testApp2Command = pCommandInvoker.GetCommand("testapp2");
	}
};