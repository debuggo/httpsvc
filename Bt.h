#pragma once
#include "FQ_Socket.h"
#include <list>
using namespace std;
#include "BtTypedef.h"
#include "CriticalSectionLock.h"
#include "JsonEx.h"

void	AddChar(const wchar_t* pwszSource,wchar_t* pwszBuff,int iBuffSize);
DWORD	GetRGB(DWORD	dwOldRGB);

class CBt
{
public:
	CBt(void);
	~CBt(void);
	BOOL		Init();
	//CString		GetGameClassType(CString	Game_Id);
	//int 		SetUserPassWord(CString StrPassWord, CString&	StrResult);
	//CString		GetBtConfig();
	//CString		SetBtConfig(_BT_CONFIG_INFO*	pConfigInfo);
	//int			LoadBtConfig(char*	pBtConfigData,_BT_CONFIG_INFO*	pConfigInfo);
	//int 		GetGame_Info(CStringArray&	GameArray,COMMAND_PARAM*	pCommand);
	//int			LoadNewGame(RESOURCE_PROPERTY*	pNewGame,char*	pDataBuffer);
	//CString		Game_Operation(int nFlag, RESOURCE_PROPERTY*	pNewGame);
	//int			GetDelete_Game_Sort(CStringArray&	DeleteGameArray);
	//int			GetSuperFluous_Game(CStringArray&	SuperGameArray);
	//int			GetDelete_Sort_Grade(CStringArray&	DeleteGameArray, int Grade);
	//int			GetDelete_Sort_Click(CStringArray&	DeleteGameArray, int Grade);
	//CString		SetDelete_Sort(CDWordArray&		DeleteGameArray);
	//int			GetTasksList(CStringArray&			TasksList);
	//CString		SetTaskInfo(CString	StrId,	int nFlag);
	//CString		GetPeer_Entry(CString	StrId);
	//int			GetClass_Parent(CStringArray&	ParentArray,int nFlag);
	//CString		SetClass_Parent(T_ClassInfo*	pClassInfo, int nCount);
	//int			GetClass_Sub(CStringArray&	SubArray);
	//CString		SetClass_Sub(CPtrArray&	SubArray);
	//CString		SetSimple_Property(SET_GAME_SIMPLE_PROPERTY	PropertyInfo);
	//CString		GetSimple_Property(int iId);
	//CString		OperationSimple_Property(int iId, int nFlag);
	//CString		GetBtGameInfo();
	//int			LoadBtGameInfo(char*	pBtGameData,MENU_CONFIG*	pMenu_Manager);
	//CString		SetBtGameInfo(MENU_MANAGER*	pMenu_Manager);
	//CString		GetBtSystemInfo();
	//CString		GetResourcesInfo();
	//CString		ClearGameFileAndDir(int		GameId);
	//CString		MoveGame(GAME_MOVE_DIRECTORY*	pGameDirInfo);
	//CString		RegUserLogin(CString	StrUserName,	CString	StrPassWord);
	//CString		GetGameCustomId();
	//CString		UpdateBt();
	//CString		GetTaskTracke(int GameId);
	//int			GetGameGroup(CStringArray&	GroupList);
	//int			LoadGemeGroup(GameGroupInfo*	pGameGroupInfo,char*	pBtGoupData);
	//CString		SetGameGroup(GameGroupInfo*	pGameGroupInfo);
	//int 		GetWkstationGroup(QUERY_PARAM_WORKSTATION*	pParam_Workstation, CStringArray&	GroupWks);
	//int			LoadWksGameGroup(SET_WORKSTATION_PROPERTY*	pWksGroup,char*	pBtData);
	//CString		SetWksGameGroup(SET_WORKSTATION_PROPERTY*	pWksGroup);
	//CString		GetWksGroupInfo(COMMAND_PARAM_GET_WORKSTATION_PROPERTY*	pWksGroupInfo);
	//CString		GetDiskPartition();
	//CString		GetDiskToFile(CString	Path);
	//int			Load_Simple_Property(GAME_SIMPLE_PROPERTY*	pSimpleProperty, char*	pData);
	//CString		AutoUpdate(int	GameId);
	//CString		ManualUpdate(int GameId);
	//CString		PropertyAddTask(GAME_SIMPLE_PROPERTY*	pSimpleProperty);
	//CString		GetGame(int	GameId);
	//CString		DeleteGame(int GameId);
	//CString		DownloadGameSSD(int GameId);
	//CString		FepairGame(int	GameId);
	//CString		GetDirInfo(CString	Path);

	//CString		BeginGameSearch();
	//CString		EndGameSearch();
	//CString		GetGameSearchInfo(CString	strGamePath);
	//int			LoadSearchStatus(GET_GAME_LOCATE_STATUS_REQUEST*	pStatus, char*	pBuffer);
	//CString		GetSearchStatus(GET_GAME_LOCATE_STATUS_REQUEST*	pStatus);
	//int			LoadSearchInfo(SET_GAME_LOCATE_INFO*	pSearchInfo, char*	pBuffer);
	//CString		SetSearchInfo(SET_GAME_LOCATE_INFO* pSearchInfo);

	//CString		BtGroup_Operation(int	nFlags, InstDelGroupInfo*	pGroupInfo);
	//CString		BtGroup_Modify(ModifyGroupInfo*	pMGroupInfo);

	//int			GetMovie(CStringArray&	MovieList);
	//int			LoadMovie(int nCount, T_Movie*	pMovie, char*	pData);
	//CString		SetMovie(int nCount, T_Movie*	pMovie);

	//int			GetOnline(CStringArray&	OnlineList);
	//int			LoadOnline(int nCount, T_Online* pOnline, char*	pData);
	//CString		SetOnline(int nCount, T_Online*	pOnline);

	//int			GetPlayer(CStringArray&	PlayerList);
	//int			LoadPlayer(int	nCount, T_PlayerList*	pPlayer, char*	pData);
	//CString		SetPlayer(int	nCount, T_PlayerList*	pPlayer);

	//CString		SetServerGroup(SERVER_PROPERTY*	pServerGroup);
	//int			LoadServerGroup(SERVER_PROPERTY*	pServerGroup, char*	pData);

	//CString		DeleteWksGroup(int	WksId);
	//CString		DeleteServerGroup(TCHAR*	pServerName);

	//int			Bt_Message(int iRequestFlag, char*	pDataBuffer,CString&	StrResult);
// private:
// 	CString		m_BtServerIpAddress;
// 	UINT		m_BtServerPort;
// 	CCriticalSectionLock	m_Lock;
	int				GetGameListInfo(CString	strJson, CString&	strResult);
	int				GetWgsInfo(CString&	strResult);
	int				GetParentClassInfo(CString	strJson, CString&	strResult);
	int				GetSubClassInfo(CString	strJson, CString&	strResult);
	int				GetMovieInfo(CString&		strResult);
	int				GetOnlineInfo(CString&		strResult);
	int				GetPlayerListInfo(CString&	strResult);
	int				ConnectServ(CString&		strResult);
	int				UILogin(CString	strJson,	CString&	strResult);
	int				GetLoginInfo(CString&		strResult);
	int				SetConnectPassword(CString	strJson,	CString&	strResult);
	int				SyncData(CString&	strResult);
	int				GetSyncProgress(CString&	strResult);
	int				GetServerWorkStatus(CString&	strResult);
	int				GetBtConfig(CString&	strResult);
	int				SetBtConfig(CString	strJson,	CString&	strResult);
	int				GetMenuConfig(CString&	strResult);
	int				SetMenuConfig(CString	strJson,	CString&	strResult);
	int				GameGetSuperfluousInfo(CString&	strResult);
	int				GameGetDeleteSort(CString&		strResult);
	int				GetSimpleProperty(CString	strJson, CString&		strResult);
	int				SetSimpleProperty(CString	strJson, CString&		strResult);
	int				GetBtSystemInfo(CString&	strResult);
	int				GetResourceNumber(CString&	strResult);
	int				GameDelete(CString	strJson,	CString&	strResult);
	int				GameClearFileDir(CString	strJson, CString&	strResult);
	int				GameMoveDirectory(CString	strJson, CString&	strResult);
	int				GameRepair(CString	strJson,	CString&	strResult);
	int				GameSetAutoUpdate(CString	strJson,	CString&	strResult);
	int				GameSetManualUpdate(CString	strJson,	CString&	strResult);
	int				AddCustomGame(CString	strJson,		CString&	strResult);
	int				GetCustomGameMaxId(CString&	strResult);
	int				GetCustomGameProperty(CString	strJson,	CString&	strResult);
	int				ModifyCustomGameProperty(CString	strJson,	CString&	strResult);
	int				DeleteCustomGame(CString	strJson,	CString&	strResult);
	int				GetTaskInfo(CString&	strResult);
	int				TaskGetTrackerInfo(CString	strJson,	CString&	strResult);
	int				TaskGetPeerInfo(CString	strJson, CString&	strResult);
	int				TaskAddDownload(CString	strJson,	CString&	strResult);
	int				TaskSSDDownload(CString	strJson,	CString&	strResult);
	int				TaskPropertyDownload(CString	strJson,	CString&	strResult);
	int				TaskAddSeed(CString	strJson,	CString&	strResult);
	int				TaskAddSeedSource(CString	strJson,	CString&	strResult);
	int				TaskStart(CString	strJson,	CString&	strResult);
	int				TaskStop(CString	strJson,	CString&	strResult);
	int				TaskCheck(CString	strJson,	CString&	strResult);
	int				TaskRemove(CString	strJson,	CString&	strResult);
	int				TaskTop(CString	strJson,	CString&	strResult);
	int				TaskUp(CString	strJson,	CString&	strResult);
	int				TaskDown(CString	strJson,	CString&	strResult);
	int				TaskLimitSpeed(CString	strJson,	CString&	strResult);
	int				TaskSort(CString	strJson,	CString&	strResult);
	int				TaskRefreshTracker(CString	strJson,	CString&	strResult);
	int				InsertGroup(CString	strJson,	CString&	strResult);
	int				ModifyGroup(CString	strJson,	CString&	strResult);
	int				DeleteGroup(CString strJson,	CString&	strResult);
	int				GetGroupInfo(CString&	strResult);
	int				GetWorkstationInfo(CString	strJson,	CString&	strResult);
	int				GetServerInfo(CString	strJson,	CString&	strResult);
	int				DeleteWorkstation(CString	strJson,	CString&	strResult);
	int				DeleteServer(CString	strJson,	CString&	strResult);
	int				GetWorkstationProperty(CString	strJson,	CString&	strResult);
	int				SetWorkstationProperty(CString	strJson,	CString&	strResult);
	int				GetServerProperty(CString	strJson,	CString&	strResult);
	int				SetServerProperty(CString	strJson,	CString&	strResult);
	int				GetDiskInfo(CString&	strResult);
	int				GetFileDirectoryInfo(CString	strJson,	CString&	strResult);
	int				GetFileDirectoryProperty(CString	strJson,	CString&	strResult);
	int				GetDirectorySize(CString	strJson,	CString&	strResult);
	int				SetParentClassInfo(CString	strJson,	CString&	strResult);
	int				SetSubClassInfo(CString	strJson,	CString&	strResult);
	int				SetMovieInfo(CString	strJson,	CString&	strResult);
	int				SetOnlineInfo(CString	strJson,	CString&	strResult);
	int				SetPlayerListInfo(CString	strJson,	CString&	strResult);
	int				StartSearch(CString	strJson, CString&	strResult);
	int				StopSearch(CString&		strResult);
	int				GetLocate(CString	strJson, CString&		strResult);
	int				GetLocateStatus(CString	strJson,	CString&	strResult);
	int				SetLocate(CString	strJson,	CString&	strResult);
	int				GetSingleGameInfo(CString	strJson,	CString&	strResult);
	int				GetLimitTimePeriodInfo(CString&	strResult);
	int				ClearBtRegInfo(CString&	strResult);
	int				CoverLocate(CString&	strResult);
	int				AddCustomWeb(CString	strJson,	CString&	strResult);
	int				SyncMzdWorkstation(CString&	strResult);
	int				SyncMzdServer(CString&		strResult);
	int				GetSingleParentClassName(CString	strJson,	CString&	strResult);
	int				GetSingleSubClassName(CString	strJson,	CString&	strResult);

	//static			DWORD		WINAPI	UpdateGameListThread(LPVOID	lpvoid);
public:
	CString			m_strGameList;
private:
	CJsonEx			m_JsonEx;	//½âÎö
};