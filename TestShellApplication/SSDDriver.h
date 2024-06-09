#include "DriverInterface.h"

class SSDDriver : public DriverInterface {
public:
	void Read(int nLba) override;
	void Write(int nLba, int nData) override;
	void Erase(int nLba, int blkCnt) override;
	std::string ReadBuffer() override;

	int GetMinLba() override;
	int GetMaxLba() override;
	int GetMaxBlkCntPerErase() override;

protected:
	const int MIN_LBA = 0;
	const int MAX_LBA = 100;
	const int MAX_BLK_CNT_PER_ERASE = 10;

	virtual void _executeCommand(const char* strCommand);
	virtual bool _getSsdExisted(void);
	virtual std::string _getSsdResult(void);
};