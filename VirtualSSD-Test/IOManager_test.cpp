#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IOManager.cpp"

using namespace testing;

class DeviceDriverMock : public DeviceDriver {
public:
	DeviceDriverMock()
		: DeviceDriver(nullptr) {}

	MOCK_METHOD(void, ReadData, (int nLbaNumber), ());
	MOCK_METHOD(void, WriteData, (int nLbaNumber, string sData), ());
};

class IOManagerTestFixture : public testing::Test {
public:
	DeviceDriverMock deviceDriverMock;
	IOManager* pStIOManager = nullptr;

	int argc;
	char* argv[IOManager::MAX_CMD_ARGUMENT_NUM];

	void makeArgument(char* argu1, char* argu2, char* argu3 = "") {
		if (string(argu1) == "W") argc = IOManager::WRITE_CMD_ARGUMENT_NUM;
		else if (string(argu1) == "R") argc = IOManager::READ_CMD_ARGUMENT_NUM;
		else argc = IOManager::THERE_IS_NO_ARGUMENT;

		argv[1] = argu1;
		argv[2] = argu2;
		argv[3] = argu3;
	}

protected:
	// setup
	virtual void SetUp() {
		std::cout << "\IOManagerTestFixture - SetUp" << std::endl;
		pStIOManager = new IOManager(&deviceDriverMock);
	}

	// teardown
	virtual void TearDown() {
		std::cout << "\IOManagerTestFixture - TearDown" << std::endl;
		delete pStIOManager;
	}
};

TEST_F(IOManagerTestFixture, InvalidCommand) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	makeArgument("Q", "0", "0x0000ABCD");
	try {
		pStIOManager->DoCommand(argc, argv);
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}

TEST_F(IOManagerTestFixture, InvalidArguemnt) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	makeArgument("W", "0", "0x0000ABCD");
	argc = 10;

	try {
		pStIOManager->DoCommand(argc, argv);
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}

TEST_F(IOManagerTestFixture, WriteInvalidData00) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	makeArgument("W", "0", "0xQWERQWER");

	try {
		pStIOManager->DoCommand(argc, argv);
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}

TEST_F(IOManagerTestFixture, WriteInvalidData01) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	makeArgument("W", "-5", "0x00001111");

	try {
		pStIOManager->DoCommand(argc, argv);
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}


TEST_F(IOManagerTestFixture, ReadInvalidData) {
	EXPECT_CALL(deviceDriverMock, ReadData)
		.Times(0);
	EXPECT_CALL(deviceDriverMock, WriteData)
		.Times(0);

	makeArgument("R", "-5");

	try {
		pStIOManager->DoCommand(argc, argv);
		FAIL();
	}
	catch (exception& e) {
		// PASS
	}
}