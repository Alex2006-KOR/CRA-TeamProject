#pragma once
#include "WriteCommand.h"
#include "ReadCommand.h"
#include "EraseCommand.h"
#include "FlushCommand.h"

#include <stdexcept>

class Device {
public:
	static Device& GetDevice(DriverInterface* pstDevice);
	void Write(vector<string> vCommandList);
	string Read(vector<string> vCommandList);
	void Erase(vector<string> vCommandList);
	void Flush(vector<string> vCommandList);

	int GetMinLba();
	int GetMaxLba();

	Device(const Device&) = delete;
	Device& operator=(const Device&) = delete;

private:
	static Device* m_pstIntstance;
	DriverInterface* m_pstDriver;

	Device(DriverInterface* pstDevice);
	WriteCommand m_stWrite{ m_pstDriver };
	ReadCommand m_stRead{ m_pstDriver };
	EraseCommand m_stErase{ m_pstDriver };
	FlushCommand m_stFlush{ m_pstDriver };
};
