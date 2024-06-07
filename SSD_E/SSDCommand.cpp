#include "SSDCommand.h"

ReadCommand::ReadCommand(int nLba) : m_nLba(nLba) {}

bool ReadCommand::ExecuteCmd(SSDInterface* pstSSDInterface) {
	return pstSSDInterface->Read(m_nLba);
}

WriteCommand::WriteCommand(int nLba, string sData) : m_nLba(nLba), m_sData(sData) {}

bool WriteCommand::ExecuteCmd(SSDInterface* pstSSDInterface) {
	return pstSSDInterface->Write(m_nLba, m_sData);
}