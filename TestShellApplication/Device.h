#pragma once
#include "WriteCommand.h"
#include "ReadCommand.h"
#include "EraseCommand.h"

#include <stdexcept>

class Device {
public:
	Device(DriverInterface* pstDriver);
	void Write(vector<string> vCommandList);
	string Read(vector<string> vCommandList);
	void Erase(vector<string> vCommandList);

	int GetMinLba();
	int GetMaxLba();

private:
	DriverInterface* m_pstDriver;
	WriteCommand m_stWrite{ m_pstDriver };
	ReadCommand m_stRead{ m_pstDriver };
	EraseCommand m_stErase{ m_pstDriver };
};
