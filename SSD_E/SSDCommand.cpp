#include "SSDCommand.h"

ReadCommand::ReadCommand(int nLba) : m_nLba(nLba) {}

bool ReadCommand::ExecuteCmd(SSDInterface* pstSSDInterface) {
	return pstSSDInterface->Read(m_nLba);
}

WriteCommand::WriteCommand(int nLba, string sData) : m_nLba(nLba), m_sData(sData) {}

bool WriteCommand::ExecuteCmd(SSDInterface* pstSSDInterface) {
	return pstSSDInterface->Write(m_nLba, m_sData);
}

EraseCommand::EraseCommand(int nLba, int nSize) : m_nLba(nLba), m_nSize(nSize) {}

bool EraseCommand::ExecuteCmd(SSDInterface* pstSSDInterface) {
	return pstSSDInterface->Erase(m_nLba, m_nSize);
}
