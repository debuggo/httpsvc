#pragma once
#include <map>
#include <vector>
#include "MZD_INI.h"
#include "json.h"

using namespace std;

//typedef	std::map<CString, CString>			Map_BtConfigInfo;
//typedef	Map_BtConfigInfo::iterator			Iter_BtConfigInfo;
//
//typedef	std::map<CString, CString>			Map_BtMenuConfig;
//typedef	Map_BtMenuConfig::iterator			Iter_BtMenuConfig;
//
//typedef	std::map<CString, CString>			Map_GamesInfo;
//typedef	Map_GamesInfo::iterator				Iter_GamesInfo;
//
//typedef std::map<CString, CString>			Map_TrackerInfo;
//typedef	Map_TrackerInfo::iterator			Iter_TrackerInfo;
//
//typedef	std::map<CString, CString>			Map_PeerInfo;
//typedef	Map_PeerInfo::iterator				Iter_PeerInfo;
//
//typedef	std::map<CString, CString>			Map_DownLoaderInfo;
//typedef	Map_DownLoaderInfo::iterator		Iter_DownLoaderInfo;
//
//typedef	std::map<CString, CString>			Map_CommandParam;
//typedef	Map_CommandParam::iterator			Iter_CommandParam;
//
//typedef	std::map<CString, CString>			Map_TaskInfo;
//typedef	Map_TaskInfo::iterator				Iter_TaskInfo;
//
//typedef	std::map<CString, CString>			Map_ResourceProperty;
//typedef	Map_ResourceProperty::iterator		Iter_ResourceProperty;
//
//typedef	std::map<CString, CString>			Map_WgsInfo;
//typedef	Map_WgsInfo::iterator				Iter_WgsInfo;
//
//typedef	std::map<CString, CString>			Map_ClassInfo;
//typedef	Map_ClassInfo::iterator				Iter_ClassInfo;
//
//typedef	std::map<CString, CString>			Map_Promotion;
//typedef Map_Promotion::iterator				Iter_Promotion;
//
//typedef	std::map<CString, CString>			Map_WorkstationInfo;
//typedef	Map_WorkstationInfo::iterator		Iter_WorkstationInfo;
//
//typedef	std::map<CString, CString>			Map_ServerInfo;
//typedef	Map_ServerInfo::iterator			Iter_ServerInfo;
//
//typedef	std::map<CString, CString>			Map_Movie;
//typedef	Map_Movie::iterator					Iter_Movie;
//
//typedef	std::map<CString, CString>			Map_Online;
//typedef	Map_Online::iterator				Iter_Online;
//
//typedef	std::map<CString, CString>			Map_PlayerList;
//typedef Map_PlayerList::iterator			Iter_PlayerList;
//
//typedef	std::map<CString, CString>			Map_BtSystemInfo;
//typedef	Map_BtSystemInfo::iterator			Iter_BtSystemInfo;
//
//typedef std::map<CString, CString>			Map_ResourceNumber;
//typedef Map_ResourceNumber::iterator		Iter_ResourceNumber;
//
//typedef	std::map<CString, CString>			Map_GameDirectory;
//typedef	Map_GameDirectory::iterator			Iter_GameDirectory;
//
//typedef	std::map<CString, CString>			Map_GameDirectoryProperss;
//typedef	Map_GameDirectoryProperss::iterator Iter_GameDirectoryProperss;
//
//typedef	std::map<CString, CString>			Map_SeedData;
//typedef	Map_SeedData::iterator				Iter_SeedData;
//
//typedef	std::map<CString, CString>			Map_SeedSource;
//typedef	Map_SeedSource::iterator			Iter_SeedSource;
//
//typedef	std::map<CString, CString>			Map_DirectoryInfo;
//typedef	Map_DirectoryInfo::iterator			Iter_DirectoryInfo;
//
//typedef	std::map<CString, CString>			Map_DirectoryProperty;
//typedef	Map_DirectoryProperty::iterator		Iter_DirectoryProperty;
//
//typedef	std::map<CString, CString>			Map_DiskInfo;
//typedef	Map_DiskInfo::iterator				Iter_DiskInfo;
typedef	struct _StVirtual
{
	CString			strName;
	CString			strVirtualType;
	int				nLen;
	CString			strClass;
}StVirtual, *pStVirtual;

typedef	std::vector<pStVirtual>							Vect_BtVirtual;
typedef::Vect_BtVirtual::iterator						Iter_BtVirtual;

typedef	std::map<CString, Vect_BtVirtual*>				Map_StBt;
typedef	Map_StBt::iterator								Iter_St_Bt;


#define			TypeInt			1
#define			TypeDWORD		2
#define			TypeFloat		3
#define			TypeDouble		4
#define			TypeInt64		5
#define			TypeTime		6
#define			TypeAcsii		7
#define			typeUniCode		8

class CJsonEx
{
public:
	CJsonEx(void);
	~CJsonEx(void);
	BOOL			InitStBt();

	BOOL			InitStMzd();

	BOOL			InitStWeb();

	VOID			ToStructRelease(PVOID	lpStData);

	int				ToStruct(CString	strJson, CString	strTableName, PVOID*	lpStData);
	int				ToStructFrom(byte*	pStByte, CString	strName, CString	strData, CString	DataType, int	nLen);

	int				ToJsonEx(CString	strStTable,PVOID	lpStData, CString&	strJson);
	int				ToJsonExFrom(byte*	pStByte, CString	strName, CString	DataType, int	nLen,	CString&	strData);

	int				ToStructCount(CString	strJson, CString	strTableName, PVOID*	lpStData);

	int				ToIniByJson(CString		strJson, CString	strTableName, MZD_INI*	pstMZDINI);

	int				ToIniByJsonEx(Json::Value	JsonObjet,	CString	strTableName, int& nCount, MZD_INI*	pstMZDINI);

	int				ToJsonByIni(MZD_INI*	pstMZDINI,CString	strTableName, int nCount, CString&	strJson);
private:
	Map_StBt		m_StBt;
};