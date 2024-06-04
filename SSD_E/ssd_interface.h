#include <string>

using namespace std;

class SSDInterface {
	virtual bool read(int nLba) = 0;
	virtual bool write(int nLba, string sData) = 0;
};