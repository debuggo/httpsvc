#pragma once
#include <map>

using namespace std;

typedef	std::map<int, LPVOID>			Map_StorageStruct;
typedef	Map_StorageStruct::iterator		Iter_StorageStruct;


class CStorageStruct
{
public:
	CStorageStruct(void);
	~CStorageStruct(void);
	LPVOID			GetStorageStruct(int	ValueKey);
	VOID			SaveStorageStruct(int	ValueKey, LPVOID	pData);
	VOID			DeleteStorageStruct(int		ValueKey);
private:
	Map_StorageStruct	m_StorageStruct;
};
