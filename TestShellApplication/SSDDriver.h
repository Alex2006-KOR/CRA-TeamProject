#include "DriverInterface.h"

class SSDDriver : public DriverInterface {
public:
	void Read(int lba) override;
	void Write(int lba, int data) override;
	std::string ReadBuffer() override;

	int GetMinLba() override;
	int GetMaxLba() override;

protected:
	const int MIN_LBA = 0;
	const int MAX_LBA = 100;

	virtual void _executeCommand(const char* strCommand);
	virtual bool _getSsdExisted(void);
	virtual std::string _getSsdResult(void);
};