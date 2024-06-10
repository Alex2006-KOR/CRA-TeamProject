#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Runner.cpp"

using namespace testing;
using std::string;

class SsdDeviceDriverMock : public DriverInterface {
public:
	MOCK_METHOD(void, Read, (int lba), (override));
	MOCK_METHOD(void, Write, (int lba, int dat), (override));
	MOCK_METHOD(std::string, ReadBuffer, (), (override));
	MOCK_METHOD(int, GetMinLba, (), (override));
	MOCK_METHOD(int, GetMaxLba, (), (override));
};

class RunnerMock : public Runner {
public:
	RunnerMock (Shell&shell)
		: Runner(shell) {}

	MOCK_METHOD(bool, _getScenarioExisted, (string listFile), (override));

protected:
	void _getScenarioList(string listFile) override
	{
		_scenarioList = "testapp1\ntestapp2\nexit\n";
	}
};

class RunnerTestFixture : public testing::Test {
public:
	SsdDeviceDriverMock ssd;
	Shell* shell;
	RunnerMock* runner;

protected:
	void SetUp() override {
		shell = new Shell(&ssd);
		runner = new RunnerMock(*shell);

		EXPECT_CALL(ssd, ReadBuffer)
			.WillRepeatedly(Return(string("0xABCD1234")));

		EXPECT_CALL(ssd, Read)
			.WillRepeatedly(Return());

		EXPECT_CALL(ssd, Write)
			.WillRepeatedly(Return());

		EXPECT_CALL(ssd, GetMinLba)
			.WillRepeatedly(Return(0));

		EXPECT_CALL(ssd, GetMaxLba)
			.WillRepeatedly(Return(100));
	}

	void TearDown() override {
		delete shell;
		delete runner;
	}
};

TEST_F(RunnerTestFixture, SetScenarioAndRunShell) {
	EXPECT_CALL(*runner, _getScenarioExisted)
		.WillRepeatedly(Return(true));

	runner->SetScenario("C:\\CRA\\SSD_E\\TestShellApplication-Test\\x64\\Debug\\run_list.lst");
	runner->RunShell();
}