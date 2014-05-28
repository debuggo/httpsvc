#include "FQ_Std.h"
#include "StorageStruct.h"

CStorageStruct::CStorageStruct(void)
{
}

CStorageStruct::~CStorageStruct(void)
{
}

VOID	CStorageStruct::SaveStorageStruct(int ValueKey, LPVOID pData)
{
	Iter_StorageStruct	Iter = m_StorageStruct.find(ValueKey);
	if (Iter != m_StorageStruct.end())
	{
		DeleteStorageStruct(ValueKey);
	}
	m_StorageStruct.insert(Map_StorageStruct::value_type(ValueKey,pData));
}

VOID	CStorageStruct::DeleteStorageStruct(int ValueKey)
{
	Iter_StorageStruct	Iter = m_StorageStruct.find(ValueKey);
	LPVOID	p = Iter->second;
	GlobalFree(p);
	m_StorageStruct.erase(Iter);
}

LPVOID	CStorageStruct::GetStorageStruct(int ValueKey)
{
	Iter_StorageStruct	Iter = m_StorageStruct.find(ValueKey);
	if (Iter != m_StorageStruct.end())
	{
		return Iter->second;
	}
	return NULL;
}