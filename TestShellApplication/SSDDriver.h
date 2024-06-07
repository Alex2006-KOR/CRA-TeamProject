#include "DriverInterface.h"

class SSDDriver : public DriverInterface {
public:
	void Read(int lba) override;
	void Write(int lba, int data) override;
	std::string ReadBuffer() override;

	int GetMinLba() override;
	int GetMaxLba() override;

private:
	const int MIN_LBA = 0;
	const int MAX_LBA = 100;

	bool _getSsdExisted(void);
	std::string _getSsdResult(void);
};