#include "DriverInterface.h"

class SSDDriver : public DriverInterface {
public:
	void Read(int lba) override;
	void Write(int lba, int data) override;
	std::string ReadBuffer() override;

private:
	bool _getSsdExisted(void);
	std::string _getSsdResult(void);
};