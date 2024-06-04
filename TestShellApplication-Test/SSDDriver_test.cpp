#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "SSDDriver.cpp"

using namespace testing;

class SSDDriverTestFixture : public SSDDriver, public testing::Test {
public:
	//MOCK_METHOD(int, Read, (int lba), ());
	//MOCK_METHOD(void, Write, (int lba, int dat), ());

protected:
	void SetUp() override {
	}
};

TEST_F(SSDDriverTestFixture, InterfaceTest) {
	Write(0, 0);
	EXPECT_EQ(0x0, Read(0));
}