#include "FQ_Std.h"
#include "Bt.h"
#include "AppMain.h"
#include "ChineseCode.h"
#include "Mzd.h"
#include "mylog.h"
#include "MzdTypedef.h"
#include "MZD_INI.h"
#include "json.h"

_btcGetFlags					m_fnbtcGetFlags;						//
_btcSockInitial					m_fnbtcSockInitial;						//
_btcSockRelease					m_fnbtcSockRelease;						//
_btcInitConnect					m_fnbtcInitConnect;						//
_btcReleaseEx					m_fnbtcReleaseEx;						//
//--------------
_btcConnectServ 				m_fnbtcConnectServ;						//联机BT服务
_btcUILogin						m_fnbtcUILogin;							//UI登录
_btcGetLoginInfo				m_fnbtcGetLoginInfo;					//获取UI登录信息
_btcSetConnectPassword			m_fnbtcSetConnectPassword;				//设置联机密码
_btcSyncData					m_fnbtcSyncData;						//同步数据
_btcGetSyncProgress				m_fnbtcGetSyncProgress;					//获取同步进度
_btcGetServerWorkStatus			m_fnbtcGetServerWorkStatus;				//获取BT服务工作状态
_btcGetBtConfig					m_fnbtcGetBtConfig;						//获取BT配置环境
_btcSetBtConfig					m_fnbtcSetBtConfig;						//设置BT配置环境
_btcGetMenuConfig				m_fnbtcGetMenuConfig;					//获取菜单配置环境
_btcSetMenuConfig				m_fnbtcSetMenuConfig;					//设置菜单配置环境
//--------------
_btcGetGamesInfo				m_fnbtcGetGamesInfo;					//获取游戏信息	

_btcReleaseGamesInfo			m_fnbtcReleaseGamesInfo;				//释放辅游戏信息
_btcGetWgsInfo					m_fnbtcGetWgsInfo;						//获取辅助工具信息
_btcReleaseWgsInfo				m_fnbtcReleaseWgsInfo;					//释放辅助工具信息
_btcGetParentClassInfo			m_fnbtcGetParentClassInfo;				//获取菜单大类信息
_btcReleaseParentClassInfo		m_fnbtcReleaseParentClassInfo;			//释放菜单大类信息
_btcGetSubClassInfo				m_fnbtcGetSubClassInfo;					//获取菜单小类信息
_btcReleaseSubClassInfo			m_fnbtcReleaseSubClassInfo;				//释放菜单小类信息
_btcGetMovieInfo				m_fnbtcGetMovieInfo;					//获取T_MovieInfo数据
_btcReleaseMovieInfo			m_fnbtcReleaseMovieInfo;				//释放T_MovieInfo数据
_btcGetOnlineInfo				m_fnbtcGetOnlineInfo;					//获取T_Online数据	
_btcReleaseOnlineInfo			m_fnbtcReleaseOnlineInfo;				//释放T_Online数据
_btcGetPlayerListInfo			m_fnbtcGetPlayerListInfo;				//获取T_Player数据		
_btcReleasePlayerListInfo		m_fnbtcReleasePlayerListInfo;			//释放T_Player数据
_btcSetParentClassInfo			m_fnbtcSetParentClassInfo;				//设置T_ParentClass大类数据
_btcSetSubClassInfo				m_fnbtcSetSubClassInfo;					//设置T_SubClass小类数据
_btcSetMovieInfo				m_fnbtcSetMovieInfo;					//设置T_MovieInfo数据
_btcSetOnlineInfo				m_fnbtcSetOnlineInfo;					//设置T_Online数据
_btcSetPlayerListInfo			m_fnbtcSetPlayerListInfo;				//设置T_Player数据
//--------------公共游戏资源设置、操作指令
_btcGameGetSuperfluousInfo		m_fnbtcGameGetSuperfluousInfo;			//获取多余的已停止更新的资源数据
_btcReleaseGameSuperfluousInfo	m_fnbtcReleaseGameSuperfluousInfo;		//释放多余的已停止更新的资源数据
_btcGameGetDeleteSort			m_fnbtcGameGetDeleteSort;				//获取游戏删除顺序数据
_btcReleaseGameDeleteSort		m_fnbtcReleaseGameDeleteSort;			//释放游戏删除顺序数据
_btcGetSimpleProperty			m_fnbtcGetSimpleProperty;				//获取指定资源的简单属性
_btcSetSimpleProperty			m_fnbtcSetSimpleProperty;				//设置指定资源的简单属性
_btcGetBtSystemInfo				m_fnbtcGetBtSystemInfo;					//获取BT系统概况信息
_btcGetResourceNumber			m_fnbtcGetResourceNumber;				//获取资源数
_btcGameDelete					m_fnbtcGameDelete;						//删除资源
_btcGameClearFileDir			m_fnbtcGameClearFileDir;				//清除多余文件目录	
_btcGameMoveDirectory			m_fnbtcGameMoveDirectory;				//移动游戏目录
_btcGameRepair					m_fnbtcGameRepair;						//游戏修复
_btcGameSetAutoUpdate			m_fnbtcGameSetAutoUpdate;				//资源设置自动更新方式
_btcGameSetManualUpdate			m_fnbtcGameSetManualUpdate;				//资源设置手动更新方式
//--------------自定义游戏资源操作指令
_btcAddCustomGame				m_fnbtcAddCustomGame;					//添加自定义资源
_btcAddCustomWeb				m_fnbtcAddCustomWeb;					//添加用户自定义的WEB资源
_btcGetCustomGameMaxId			m_fnbtcGetCustomGameMaxId;				//自动获取最大自定义游戏编号
_btcGetCustomGameProperty		m_fnbtcGetCustomGameProperty;			//获取自定义游戏属性
_btcModifyCustomGameProperty	m_fnbtcModifyCustomGameProperty;		//修改自定义游戏属性
_btcDeleteCustomGame			m_fnbtcDeleteCustomGame;				//删除自定义游戏
//--------------Task操作指令
_btcGetTaskInfo					m_fnbtcGetTaskInfo;						//获取所有活动任务信息
_btcTaskGetTrackerInfo			m_fnbtcTaskGetTrackerInfo;				//获取指定任务的Tracker信息
_btcTaskGetPeerInfo				m_fnbtcTaskGetPeerInfo;					//获取指定任务的节点信息
_btcTaskAddDownload				m_fnbtcTaskAddDownload;					//添加一个下载任务
_btcTaskSSDDownload				m_fnbtcTaskSSDDownload;					//SSD磁盘方式下载
_btcTaskPropertyDownload		m_fnbtcTaskPropertyDownload;			//属性方式添加下载
_btcTaskAddSeed					m_fnbtcTaskAddSeed;						//添加一个做种任务
_btcTaskAddSeedSource			m_fnbtcTaskAddSeedSource;				//给指定任务添加一个种源
_btcTaskStart					m_fnbtcTaskStart;						//开始任务
_btcTaskStop					m_fnbtcTaskStop;						//停止任务
_btcTaskCheck					m_fnbtcTaskCheck;						//检查任务
_btcTaskRemove					m_fnbtcTaskRemove;						//移除任务
_btcTaskTop						m_fnbtcTaskTop;							//任务置顶
_btcTaskUp						m_fnbtcTaskUp;							//任务上移
_btcTaskDown					m_fnbtcTaskDown;						//任务下移
_btcTaskLimitSpeed				m_fnbtcTaskLimitSpeed;					//任务限制速度
_btcTaskSort					m_fnbtcTaskSort;						//任务排序
_btcTaskRefreshTracker			m_fnbtcTaskRefreshTracker;				//任务强制重连一次
//--------------分组、工作站、服务器
_btcInsertGroup					m_fnbtcInsertGroup;						//添加一个分组信息
_btcModifyGroup					m_fnbtcModifyGroup;						//修改一个分组信息
_btcDeleteGroup					m_fnbtcDeleteGroup;						//删除一个分组信息
_btcGetGroupInfo				m_fnbtcGetGroupInfo;					//获取所有分组信息
_btcGetWorkstationInfo			m_fnbtcGetWorkstationInfo;				//获取指定分组中的工作站信息	
_btcReleaseWorkstationInfo		m_fnbtcReleaseWorkstationInfo;			//释放指定分组中的工作站信息
_btcGetServerInfo				m_fnbtcGetServerInfo;					//获取指定分组中的服务器信息
_btcReleaseServerInfo			m_fnbtcReleaseServerInfo;				//释放指定分组中的服务器信息
_btcDeleteWorkstation			m_fnbtcDeleteWorkstation;				//删除一台工作站
_btcDeleteServer				m_fnbtcDeleteServer;					//删除一台服务器
_btcGetWorkstationProperty		m_fnbtcGetWorkstationProperty;			//获取一台工作站属性
_btcSetWorkstationProperty		m_fnbtcSetWorkstationProperty;			//设置一台工作站属性(如果没有找到对应的工作站，就新加)
_btcGetServerProperty			m_fnbtcGetServerProperty;				//获取一台服务器属性
_btcSetServerProperty			m_fnbtcSetServerProperty;				//设置一台服务器属性(如果没有找到对应的服务器，就新加)
//--------------磁盘目录操作指令
_btcGetDiskInfo					m_fnbtcGetDiskInfo;						//获取磁盘信息
_btcReleaseDiskInfo				m_fnbtcReleaseDiskInfo;					//释放磁盘信息
_btcGetFileDirectoryInfo		m_fnbtcGetFileDirectoryInfo;			//获取文件目录信息
_btcReleaseDirectoryInfo		m_fnbtcReleaseDirectoryInfo;			//释放文件目录信息
_btcGetFileDirectoryProperty	m_fnbtcGetFileDirectoryProperty;		//获取文件目录属性
_btcGetDirectorySize			m_fnbtcGetDirectorySize;				//获取目录大小(单位Byte）



_btcStartSearch					m_fnbtcStartSearch;						//开始游戏定位搜索	
_btcStopSearch					m_fnbtcStopSearch;						//结束游戏定位搜索
_btcGetLocate					m_fnbtcGetLocate;						//获取游戏定位信息
_btcGetLocateStatus				m_fnbtcGetLocateStatus;					//获取游戏定位状态
_btcSetLocate					m_fnbtcSetLocate;						//设置游戏定位信息
_btcCoverLocate					m_fnbtcCoverLocate;

_btcGetSingleGameInfo			m_fnbtcGetSingleGameInfo;			
_btcGetLimitTimePeriodInfo		m_fnbtcGetLimitTimePeriodInfo;
_btcClearBtRegInfo				m_fnbtcClearBtRegInfo;


_btcSyncMzdWorkstation			m_fnbtcSyncMzdWorkstation;
_btcSyncMzdServer				m_fnbtcSyncMzdServer;

_btcSendCommand					m_fnbtcCall;


void	AddChar(const wchar_t* pwszSource,wchar_t* pwszBuff,int iBuffSize)
{
	int i = 0;
	for(;i<iBuffSize;i++)
	{
		if(*pwszSource == '\0')
			break;
		pwszBuff[i] = *pwszSource;
		if(*pwszSource == '\\')
		{
			i++;
			pwszBuff[i] = '\\';
		}
		pwszSource++;
	}
	pwszBuff[i] = '\0';
}

#define		ARGB	DWORD

enum
{
	AlphaShift  = 24,
	RedShift    = 16,
	GreenShift  = 8,
	BlueShift   = 0
};

ARGB MakeARGB(IN BYTE a,
			  IN BYTE r,
			  IN BYTE g,
			  IN BYTE b)
{
	return (((ARGB) (b) <<  BlueShift) |
		((ARGB) (g) << GreenShift) |
		((ARGB) (r) <<   RedShift) |
		((ARGB) (a) << AlphaShift));
}

DWORD	GetRGB(DWORD	dwOldRGB)
{
	return MakeARGB(0,GetRValue(dwOldRGB),GetGValue(dwOldRGB),GetBValue(dwOldRGB));
}

CBt::CBt(void)
{
}

CBt::~CBt(void)
{
}


//初始化BT接口
BOOL	CBt::Init()
{
	HMODULE	m_hCModule = LoadLibrary(_T("Communication.dll"));
	if (m_hCModule == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载BT动态库");
		return FALSE;
	}
	//m_fnbtcGetFlags = (_btcGetFlags)::GetProcAddress(m_hCModule,"btcGetFlags");
	//if(NULL == m_fnbtcGetFlags) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetFlags");
	//m_fnbtcSockInitial = (_btcSockInitial)::GetProcAddress(m_hCModule,"btcSockInitial");
	//if(NULL == m_fnbtcSockInitial) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSockInitial");
	//m_fnbtcSockRelease = (_btcSockRelease)::GetProcAddress(m_hCModule,"btcSockRelease");
	//if(NULL == m_fnbtcSockRelease) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSockRelease");
	m_fnbtcInitConnect = (_btcInitConnect)::GetProcAddress(m_hCModule,"btcInitConnect");	//bt初始化
	if(NULL == m_fnbtcInitConnect)
		WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcInitConnect");

	m_fnbtcReleaseEx = (_btcReleaseEx)::GetProcAddress(m_hCModule,"btcReleaseEx");
	if(NULL == m_fnbtcReleaseEx) 
		WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseEx");
	////--------------
	//m_fnbtcConnectServ = (_btcConnectServ)::GetProcAddress(m_hCModule,"btcConnectServ");												//联机BT服务
	//if(NULL == m_fnbtcConnectServ) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcConnectServ");
	//m_fnbtcUILogin = (_btcUILogin)::GetProcAddress(m_hCModule,"btcUILogin");															//UI登录
	//if(NULL == m_fnbtcUILogin) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcUILogin");
	//m_fnbtcGetLoginInfo = (_btcGetLoginInfo)::GetProcAddress(m_hCModule,"btcGetLoginInfo");												//获取UI登录信息
	//if(NULL == m_fnbtcGetLoginInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetLoginInfo");
	//m_fnbtcSetConnectPassword = (_btcSetConnectPassword)::GetProcAddress(m_hCModule,"btcSetConnectPassword");							//设置联机密码
	//if(NULL == m_fnbtcSetConnectPassword) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetConnectPassword");

	//if(NULL == m_fnbtcSyncData) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSyncData");
	//m_fnbtcGetSyncProgress = (_btcGetSyncProgress)::GetProcAddress(m_hCModule,"btcGetSyncProgress");									//获取同步进度
	//if(NULL == m_fnbtcGetSyncProgress) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetSyncProgress");
	//m_fnbtcGetServerWorkStatus = (_btcGetServerWorkStatus)::GetProcAddress(m_hCModule,"btcGetServerWorkStatus");						//获取BT服务工作状态
	//if(NULL == m_fnbtcGetServerWorkStatus) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetServerWorkStatus");
	//m_fnbtcGetBtConfig = (_btcGetBtConfig)::GetProcAddress(m_hCModule,"btcGetBtConfig");												//获取BT配置环境
	//if(NULL == m_fnbtcGetBtConfig) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetBtConfig");
	//m_fnbtcSetBtConfig = (_btcSetBtConfig)::GetProcAddress(m_hCModule,"btcSetBtConfig");												//设置BT配置环境
	//if(NULL == m_fnbtcSetBtConfig) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetBtConfig");
	//m_fnbtcGetMenuConfig = (_btcGetMenuConfig)::GetProcAddress(m_hCModule,"btcGetMenuConfig");											//获取菜单配置环境
	//if(NULL == m_fnbtcGetMenuConfig) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetMenuConfig");
	//m_fnbtcSetMenuConfig = (_btcSetMenuConfig)::GetProcAddress(m_hCModule,"btcSetMenuConfig");											//设置菜单配置环境
	//if(NULL == m_fnbtcSetMenuConfig) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetMenuConfig");
	////--------------
	//m_fnbtcGetGamesInfo = (_btcGetGamesInfo)::GetProcAddress(m_hCModule,"btcGetGamesInfo");												//获取游戏信息		
	//if(NULL == m_fnbtcGetGamesInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetGamesInfo");
	//m_fnbtcReleaseGamesInfo = (_btcReleaseGamesInfo)::GetProcAddress(m_hCModule,"btcReleaseGamesInfo");									//释放辅游戏信息
	//if(NULL == m_fnbtcReleaseGamesInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseGamesInfo");
	//m_fnbtcGetWgsInfo = (_btcGetWgsInfo)::GetProcAddress(m_hCModule,"btcGetWgsInfo");													//获取辅助工具信息
	//if(NULL == m_fnbtcGetWgsInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetWgsInfo");
	//m_fnbtcReleaseWgsInfo = (_btcReleaseWgsInfo)::GetProcAddress(m_hCModule,"btcReleaseWgsInfo");										//释放辅助工具信息
	//if(NULL == m_fnbtcReleaseWgsInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseWgsInfo");
	//m_fnbtcGetParentClassInfo = (_btcGetParentClassInfo)::GetProcAddress(m_hCModule,"btcGetParentClassInfo");							//获取菜单大类信息
	//if(NULL == m_fnbtcGetParentClassInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetParentClassInfo");
	//m_fnbtcReleaseParentClassInfo = (_btcReleaseParentClassInfo)::GetProcAddress(m_hCModule,"btcReleaseParentClassInfo");				//释放菜单大类信息
	//if(NULL == m_fnbtcReleaseParentClassInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseParentClassInfo");
	//m_fnbtcGetSubClassInfo = (_btcGetSubClassInfo)::GetProcAddress(m_hCModule,"btcGetSubClassInfo");									//获取菜单小类信息
	//if(NULL == m_fnbtcGetSubClassInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetSubClassInfo");
	//m_fnbtcReleaseSubClassInfo = (_btcReleaseSubClassInfo)::GetProcAddress(m_hCModule,"btcReleaseSubClassInfo");						//释放菜单小类信息
	//if(NULL == m_fnbtcReleaseSubClassInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseSubClassInfo");
	//m_fnbtcGetMovieInfo = (_btcGetMovieInfo)::GetProcAddress(m_hCModule,"btcGetMovieInfo");												//获取T_MovieInfo数据
	//if(NULL == m_fnbtcGetMovieInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetMovieInfo");
	//m_fnbtcReleaseMovieInfo = (_btcReleaseMovieInfo)::GetProcAddress(m_hCModule,"btcReleaseMovieInfo");									//释放T_MovieInfo数据
	//if(NULL == m_fnbtcReleaseMovieInfo)  WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseMovieInfo");
	//m_fnbtcGetOnlineInfo = (_btcGetOnlineInfo)::GetProcAddress(m_hCModule,"btcGetOnlineInfo");											//获取T_Online数据	
	//if(NULL == m_fnbtcGetOnlineInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetOnlineInfo");
	//m_fnbtcReleaseOnlineInfo = (_btcReleaseOnlineInfo)::GetProcAddress(m_hCModule,"btcReleaseOnlineInfo");								//释放T_Online数据
	//if(NULL == m_fnbtcReleaseOnlineInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseOnlineInfo");
	//m_fnbtcGetPlayerListInfo = (_btcGetPlayerListInfo)::GetProcAddress(m_hCModule,"btcGetPlayerListInfo");								//获取T_Player数据		
	//if(NULL == m_fnbtcGetPlayerListInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetPlayerListInfo");
	//m_fnbtcReleasePlayerListInfo = (_btcReleasePlayerListInfo)::GetProcAddress(m_hCModule,"btcReleasePlayerListInfo");					//释放T_Player数据
	//if(NULL == m_fnbtcReleasePlayerListInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleasePlayerListInfo");
	//m_fnbtcSetParentClassInfo = (_btcSetParentClassInfo)::GetProcAddress(m_hCModule,"btcSetParentClassInfo");							//设置T_ParentClass大类数据
	//if(NULL == m_fnbtcSetParentClassInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetParentClassInfo");
	//m_fnbtcSetSubClassInfo = (_btcSetSubClassInfo)::GetProcAddress(m_hCModule,"btcSetSubClassInfo");									//设置T_SubClass小类数据
	//if(NULL == m_fnbtcSetSubClassInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetSubClassInfo");
	//m_fnbtcSetMovieInfo = (_btcSetMovieInfo)::GetProcAddress(m_hCModule,"btcSetMovieInfo");												//设置T_MovieInfo数据
	//if(NULL == m_fnbtcSetMovieInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetMovieInfo");
	//m_fnbtcSetOnlineInfo = (_btcSetOnlineInfo)::GetProcAddress(m_hCModule,"btcSetOnlineInfo");											//设置T_Online数据
	//if(NULL == m_fnbtcSetOnlineInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetOnlineInfo");
	//m_fnbtcSetPlayerListInfo = (_btcSetPlayerListInfo)::GetProcAddress(m_hCModule,"btcSetPlayerListInfo");								//设置T_Player数据
	//if(NULL == m_fnbtcSetPlayerListInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetPlayerListInfo");
	////--------------公共游戏资源设置、操作指令
	//m_fnbtcGameGetSuperfluousInfo = (_btcGameGetSuperfluousInfo)::GetProcAddress(m_hCModule,"btcGameGetSuperfluousInfo");				//获取多余的已停止更新的资源数据
	//if(NULL == m_fnbtcGameGetSuperfluousInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameGetSuperfluousInfo");
	//m_fnbtcReleaseGameSuperfluousInfo = (_btcReleaseGameSuperfluousInfo)::GetProcAddress(m_hCModule,"btcReleaseGameSuperfluousInfo");	//释放多余的已停止更新的资源数据
	//if(NULL == m_fnbtcReleaseGameSuperfluousInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseGameSuperfluousInfo");
	//m_fnbtcGameGetDeleteSort = (_btcGameGetDeleteSort)::GetProcAddress(m_hCModule,"btcGameGetDeleteSort");						//获取游戏删除顺序数据
	//if(NULL == m_fnbtcGameGetDeleteSort) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameGetDeleteSort");
	//m_fnbtcReleaseGameDeleteSort = (_btcReleaseGameDeleteSort)::GetProcAddress(m_hCModule,"btcReleaseGameDeleteSort");			//释放游戏删除顺序数据
	//if(NULL == m_fnbtcReleaseGameDeleteSort) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseGameDeleteSort");
	//m_fnbtcGetSimpleProperty = (_btcGetSimpleProperty)::GetProcAddress(m_hCModule,"btcGetSimpleProperty");						//获取指定资源的简单属性
	//if(NULL == m_fnbtcGetSimpleProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetSimpleProperty");
	//m_fnbtcSetSimpleProperty = (_btcSetSimpleProperty)::GetProcAddress(m_hCModule,"btcSetSimpleProperty");						//设置指定资源的简单属性
	//if(NULL == m_fnbtcSetSimpleProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetSimpleProperty");
	//m_fnbtcGetBtSystemInfo = (_btcGetBtSystemInfo)::GetProcAddress(m_hCModule,"btcGetBtSystemInfo");							//获取BT系统概况信息
	//if(NULL == m_fnbtcGetBtSystemInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetBtSystemInfo");
	//m_fnbtcGetResourceNumber = (_btcGetResourceNumber)::GetProcAddress(m_hCModule,"btcGetResourceNumber");						//获取资源数
	//if(NULL == m_fnbtcGetResourceNumber) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetResourceNumber");
	//m_fnbtcGameDelete = (_btcGameDelete)::GetProcAddress(m_hCModule,"btcGameDelete");											//删除资源
	//if(NULL == m_fnbtcGameDelete) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameDelete");
	//m_fnbtcGameClearFileDir = (_btcGameClearFileDir)::GetProcAddress(m_hCModule,"btcGameClearFileDir");							//清除多余文件目录	
	//if(NULL == m_fnbtcGameClearFileDir) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameClearFileDir");
	//m_fnbtcGameMoveDirectory = (_btcGameMoveDirectory)::GetProcAddress(m_hCModule,"btcGameMoveDirectory");						//移动游戏目录
	//if(NULL == m_fnbtcGameMoveDirectory) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameMoveDirectory");
	//m_fnbtcGameRepair = (_btcGameRepair)::GetProcAddress(m_hCModule,"btcGameRepair");											//游戏修复
	//if(NULL == m_fnbtcGameRepair) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameRepair");
	//m_fnbtcGameSetAutoUpdate = (_btcGameSetAutoUpdate)::GetProcAddress(m_hCModule,"btcGameSetAutoUpdate");						//资源设置自动更新方式
	//if(NULL == m_fnbtcGameSetAutoUpdate) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameSetAutoUpdate");
	//m_fnbtcGameSetManualUpdate = (_btcGameSetManualUpdate)::GetProcAddress(m_hCModule,"btcGameSetManualUpdate");				//资源设置手动更新方式
	//if(NULL == m_fnbtcGameSetManualUpdate) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGameSetManualUpdate");
	////--------------自定义游戏资源操作指令
	//m_fnbtcAddCustomGame = (_btcAddCustomGame)::GetProcAddress(m_hCModule,"btcAddCustomGame");									//添加自定义资源
	//if(NULL == m_fnbtcAddCustomGame) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcAddCustomGame");
	//m_fnbtcGetCustomGameMaxId = (_btcGetCustomGameMaxId)::GetProcAddress(m_hCModule,"btcGetCustomGameMaxId");					//自动获取最大自定义游戏编号
	//if(NULL == m_fnbtcGetCustomGameMaxId) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetCustomGameMaxId");
	//m_fnbtcGetCustomGameProperty = (_btcGetCustomGameProperty)::GetProcAddress(m_hCModule,"btcGetCustomGameProperty");			//获取自定义游戏属性
	//if(NULL == m_fnbtcGetCustomGameProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetCustomGameProperty");
	//m_fnbtcModifyCustomGameProperty = (_btcModifyCustomGameProperty)::GetProcAddress(m_hCModule,"btcModifyCustomGameProperty");	//修改自定义游戏属性
	//if(NULL == m_fnbtcModifyCustomGameProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcModifyCustomGameProperty");
	//m_fnbtcDeleteCustomGame = (_btcDeleteCustomGame)::GetProcAddress(m_hCModule,"btcDeleteCustomGame");							//删除自定义游戏
	//if(NULL == m_fnbtcDeleteCustomGame) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcDeleteCustomGame");
	////--------------Task操作指令
	//m_fnbtcGetTaskInfo = (_btcGetTaskInfo)::GetProcAddress(m_hCModule,"btcGetTaskInfo");										//获取所有活动任务信息
	//if(NULL == m_fnbtcGetTaskInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetTaskInfo");
	//m_fnbtcTaskGetTrackerInfo = (_btcTaskGetTrackerInfo)::GetProcAddress(m_hCModule,"btcTaskGetTrackerInfo");					//获取指定任务的Tracker信息
	//if(NULL == m_fnbtcTaskGetTrackerInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskGetTrackerInfo");
	//m_fnbtcTaskGetPeerInfo = (_btcTaskGetPeerInfo)::GetProcAddress(m_hCModule,"btcTaskGetPeerInfo");							//获取指定任务的节点信息
	//if(NULL == m_fnbtcTaskGetPeerInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskGetPeerInfo");
	//m_fnbtcTaskAddDownload = (_btcTaskAddDownload)::GetProcAddress(m_hCModule,"btcTaskAddDownload");							//添加一个下载任务
	//if(NULL == m_fnbtcTaskAddDownload) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskAddDownload");
	//m_fnbtcTaskSSDDownload = (_btcTaskSSDDownload)::GetProcAddress(m_hCModule,"btcTaskSSDDownload");							//SSD磁盘方式下载
	//if(NULL == m_fnbtcTaskSSDDownload) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskSSDDownload");
	//m_fnbtcTaskPropertyDownload = (_btcTaskPropertyDownload)::GetProcAddress(m_hCModule,"btcTaskPropertyDownload");				//属性方式添加下载
	//if(NULL == m_fnbtcTaskPropertyDownload) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskPropertyDownload");
	//m_fnbtcTaskAddSeed = (_btcTaskAddSeed)::GetProcAddress(m_hCModule,"btcTaskAddSeed");										//添加一个做种任务
	//if(NULL == m_fnbtcTaskAddSeed) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskAddSeed");
	//m_fnbtcTaskAddSeedSource = (_btcTaskAddSeedSource)::GetProcAddress(m_hCModule,"btcTaskAddSeedSource");						//给指定任务添加一个种源
	//if(NULL == m_fnbtcTaskAddSeedSource) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskAddSeedSource");
	//m_fnbtcTaskStart = (_btcTaskStart)::GetProcAddress(m_hCModule,"btcTaskStart");												//开始任务
	//if(NULL == m_fnbtcTaskStart) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskStart");
	//m_fnbtcTaskStop = (_btcTaskStop)::GetProcAddress(m_hCModule,"btcTaskStop");													//停止任务
	//if(NULL == m_fnbtcTaskStop) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskStop");
	//m_fnbtcTaskCheck = (_btcTaskCheck)::GetProcAddress(m_hCModule,"btcTaskCheck");												//检查任务
	//if(NULL == m_fnbtcTaskCheck) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskCheck");
	//m_fnbtcTaskRemove = (_btcTaskRemove)::GetProcAddress(m_hCModule,"btcTaskRemove");											//移除任务
	//if(NULL == m_fnbtcTaskRemove) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskRemove");
	//m_fnbtcTaskTop = (_btcTaskTop)::GetProcAddress(m_hCModule,"btcTaskTop");													//任务置顶
	//if(NULL == m_fnbtcTaskTop) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskTop");
	//m_fnbtcTaskUp = (_btcTaskUp)::GetProcAddress(m_hCModule,"btcTaskUp");														//任务上移
	//if(NULL == m_fnbtcTaskUp) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskUp");
	//m_fnbtcTaskDown = (_btcTaskDown)::GetProcAddress(m_hCModule,"btcTaskDown");													//任务下移
	//if(NULL == m_fnbtcTaskDown) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskDown");
	//m_fnbtcTaskLimitSpeed = (_btcTaskLimitSpeed)::GetProcAddress(m_hCModule,"btcTaskLimitSpeed");								//任务限制速度
	//if(NULL == m_fnbtcTaskLimitSpeed) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskLimitSpeed");
	//m_fnbtcTaskSort = (_btcTaskSort)::GetProcAddress(m_hCModule,"btcTaskSort");													//任务排序
	//if(NULL == m_fnbtcTaskSort) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskSort");
	//m_fnbtcTaskRefreshTracker = (_btcTaskRefreshTracker)::GetProcAddress(m_hCModule,"btcTaskRefreshTracker");					//任务强制重连一次
	//if(NULL == m_fnbtcTaskRefreshTracker) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcTaskRefreshTracker");
	////--------------分组、工作站、服务器
	//m_fnbtcInsertGroup = (_btcInsertGroup)::GetProcAddress(m_hCModule,"btcInsertGroup");										//添加一个分组信息
	//if(NULL == m_fnbtcInsertGroup) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcInsertGroup");
	//m_fnbtcModifyGroup = (_btcModifyGroup)::GetProcAddress(m_hCModule,"btcModifyGroup");										//修改一个分组信息
	//if(NULL == m_fnbtcModifyGroup) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcModifyGroup");
	//m_fnbtcDeleteGroup = (_btcDeleteGroup)::GetProcAddress(m_hCModule,"btcDeleteGroup");										//删除一个分组信息
	//if(NULL == m_fnbtcDeleteGroup) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcDeleteGroup");
	//m_fnbtcGetGroupInfo = (_btcGetGroupInfo)::GetProcAddress(m_hCModule,"btcGetGroupInfo");										//获取所有分组信息
	//if(NULL == m_fnbtcGetGroupInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetGroupInfo");
	//m_fnbtcGetWorkstationInfo = (_btcGetWorkstationInfo)::GetProcAddress(m_hCModule,"btcGetWorkstationInfo");					//获取指定分组中的工作站信息	
	//if(NULL == m_fnbtcGetWorkstationInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetWorkstationInfo");
	//m_fnbtcReleaseWorkstationInfo = (_btcReleaseWorkstationInfo)::GetProcAddress(m_hCModule,"btcReleaseWorkstationInfo");		//释放指定分组中的工作站信息
	//if(NULL == m_fnbtcReleaseWorkstationInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseWorkstationInfo");
	//m_fnbtcGetServerInfo = (_btcGetServerInfo)::GetProcAddress(m_hCModule,"btcGetServerInfo");									//获取指定分组中的服务器信息
	//if(NULL == m_fnbtcGetServerInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetServerInfo");
	//m_fnbtcReleaseServerInfo = (_btcReleaseServerInfo)::GetProcAddress(m_hCModule,"btcReleaseServerInfo");						//释放指定分组中的服务器信息
	//if(NULL == m_fnbtcReleaseServerInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseServerInfo");
	//m_fnbtcDeleteWorkstation = (_btcDeleteWorkstation)::GetProcAddress(m_hCModule,"btcDeleteWorkstation");						//删除一台工作站
	//if(NULL == m_fnbtcDeleteWorkstation) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcDeleteWorkstation");
	//m_fnbtcDeleteServer = (_btcDeleteServer)::GetProcAddress(m_hCModule,"btcDeleteServer");										//删除一台服务器
	//if(NULL == m_fnbtcDeleteServer) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcDeleteServer");
	//m_fnbtcGetWorkstationProperty = (_btcGetWorkstationProperty)::GetProcAddress(m_hCModule,"btcGetWorkstationProperty");		//获取一台工作站属性
	//if(NULL == m_fnbtcGetWorkstationProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetWorkstationProperty");
	//m_fnbtcSetWorkstationProperty = (_btcSetWorkstationProperty)::GetProcAddress(m_hCModule,"btcSetWorkstationProperty");		//设置一台工作站属性(如果没有找到对应的工作站，就新加)
	//if(NULL == m_fnbtcSetWorkstationProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetWorkstationProperty");
	//m_fnbtcGetServerProperty = (_btcGetServerProperty)::GetProcAddress(m_hCModule,"btcGetServerProperty");						//获取一台服务器属性
	//if(NULL == m_fnbtcGetServerProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetServerProperty");
	//m_fnbtcSetServerProperty = (_btcSetServerProperty)::GetProcAddress(m_hCModule,"btcSetServerProperty");						//设置一台服务器属性(如果没有找到对应的服务器，就新加)
	//if(NULL == m_fnbtcSetServerProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetServerProperty");
	//m_fnbtcGetDiskInfo = (_btcGetDiskInfo)GetProcAddress(m_hCModule,"btcGetDiskInfo");
	//if(NULL == m_fnbtcGetDiskInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetDiskInfo");
	//m_fnbtcReleaseDiskInfo = (_btcReleaseDiskInfo)GetProcAddress(m_hCModule,"btcReleaseDiskInfo");
	//if(NULL == m_fnbtcReleaseDiskInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseDiskInfo");
	//m_fnbtcGetFileDirectoryInfo = (_btcGetFileDirectoryInfo)GetProcAddress(m_hCModule,"btcGetFileDirectoryInfo");
	//if(NULL == m_fnbtcGetFileDirectoryInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetFileDirectoryInfo");
	//m_fnbtcReleaseDirectoryInfo = (_btcReleaseDirectoryInfo)GetProcAddress(m_hCModule,"btcReleaseDirectoryInfo");
	//if(NULL == m_fnbtcReleaseDirectoryInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcReleaseDirectoryInfo");
	//m_fnbtcGetFileDirectoryProperty = (_btcGetFileDirectoryProperty)GetProcAddress(m_hCModule,"btcGetFileDirectoryProperty");
	//if(NULL == m_fnbtcGetFileDirectoryProperty) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetFileDirectoryProperty");
	//m_fnbtcGetDirectorySize = (_btcGetDirectorySize)GetProcAddress(m_hCModule,"btcGetDirectorySize");
	//if(NULL == m_fnbtcGetDirectorySize) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetDirectorySize");
	//m_fnbtcStartSearch = (_btcStartSearch)GetProcAddress(m_hCModule,"btcStartSearch");
	//if(NULL == m_fnbtcStartSearch) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcStartSearch");
	//m_fnbtcStopSearch = (_btcStopSearch)GetProcAddress(m_hCModule,"btcStopSearch");
	//if(NULL == m_fnbtcStopSearch) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcStopSearch");
	//m_fnbtcGetLocate = (_btcGetLocate)GetProcAddress(m_hCModule,"btcGetLocate");
	//if(NULL == m_fnbtcGetLocate) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetLocate");
	//m_fnbtcGetLocateStatus = (_btcGetLocateStatus)GetProcAddress(m_hCModule,"btcGetLocateStatus");
	//if(NULL == m_fnbtcGetLocateStatus) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetLocateStatus");
	//m_fnbtcSetLocate = (_btcSetLocate)GetProcAddress(m_hCModule,"btcSetLocate");
	//if(NULL == m_fnbtcSetLocate) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSetLocate");
	//m_fnbtcGetSingleGameInfo = (_btcGetSingleGameInfo)GetProcAddress(m_hCModule,"btcGetSingleGameInfo");
	//if (NULL == m_fnbtcGetSingleGameInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetSingleGameInfo");

	//m_fnbtcGetLimitTimePeriodInfo = (_btcGetLimitTimePeriodInfo)GetProcAddress(m_hCModule,"btcGetLimitTimePeriodInfo");
	//if (NULL == m_fnbtcGetLimitTimePeriodInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetLimitTimePeriodInfo");

	//m_fnbtcClearBtRegInfo = (_btcClearBtRegInfo)GetProcAddress(m_hCModule,"btcClearBtRegInfo");
	//if (NULL == m_fnbtcClearBtRegInfo) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcClearBtRegInfo");

	//m_fnbtcCoverLocate = (_btcCoverLocate)GetProcAddress(m_hCModule,"btcCoverLocate");
	//if (NULL == m_fnbtcCoverLocate) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcCoverLocate");

	//m_fnbtcAddCustomWeb = (_btcAddCustomWeb)GetProcAddress(m_hCModule,"btcAddCustomWeb");
	//if (NULL == m_fnbtcAddCustomWeb) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcAddCustomWeb");

	//m_fnbtcSyncMzdWorkstation = (_btcSyncMzdWorkstation)GetProcAddress(m_hCModule,"btcSyncMzdWorkstation");
	//if ( NULL == m_fnbtcSyncMzdWorkstation) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSyncMzdWorkstation");

	//m_fnbtcSyncMzdServer = (_btcSyncMzdServer)GetProcAddress(m_hCModule,"btcSyncMzdServer");
	//if ( NULL == m_fnbtcSyncMzdServer) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcSyncMzdServer");

	//m_fnGetGamesInfo_1 = (_btcGetGamesInfo_1)GetProcAddress(m_hCModule,"btcGetGamesInfo_1");
	//if (NULL == m_fnGetGamesInfo_1) WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载 : btcGetGamesInfo_1");

	m_fnbtcCall = (_btcSendCommand)GetProcAddress(m_hCModule,"btcSendCommand");
	if (m_fnbtcCall == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"无法加载 : btcSendCommand");
	}

	CAppMain*	pAppMain = CAppMain::GetAppMain();
	int nErrorRet = m_fnbtcInitConnect(_T("127.0.0.1"),pAppMain->m_CommunicationPassWord.GetBuffer()/*_T("972D361")*/);
	if (!nErrorRet)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"无法连接BT服务器。 错误码：%d",nErrorRet);
		return FALSE;
	}
	
	if (!m_JsonEx.InitStBt())	//加载BT中的结构
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"%s","加载BT资源文件失败！");
		return FALSE;
	}
	//HANDLE hThread = CreateThread(NULL,0,UpdateGameListThread,this,0,NULL);
	//CloseHandle(hThread);
	return TRUE;
}

//DWORD	CBt::UpdateGameListThread(LPVOID	lpvoid)
//{
//	CBt*	pBt = (CBt*)lpvoid;
//
//Bigen:
//	RESOURCE_INFO*	pGameList = NULL;
//	COMMAND_PARAM	GameParam; 
//	int		nGameCount;
//	CString	strData;
//	int nErrorRet = m_fnbtcGetGamesInfo(&pGameList,&GameParam,&nGameCount);
//	if (nErrorRet != SCMD_OK)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,"%s","UpdateGameListThread中获取游戏资源命令失败！");
//		goto End;
//	}
//	if (nGameCount == 0)
//	{
//		goto End;
//	}
//	if (pGameList->cbSize != sizeof(RESOURCE_INFO))
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
//	}
//	WRITE_LOG(LOG_LEVEL_DEBUG,_T("接收到游戏资源个数%d"),nGameCount);
//	strData += _T("{\"Array\":[");
//	for (int i = 0; i < nGameCount; i++)
//	{
//		CString	strJson;
//		wchar_t	wzsGame_OnlyBuffer[128] = { 0 };
//		AddChar(pGameList[i].gi.wszGame_Only,wzsGame_OnlyBuffer,128);
//
//		wchar_t	wzsGame_PathBuffer[128] = { 0 };
//		AddChar(pGameList[i].gi.wszGame_Path,wzsGame_PathBuffer,128);
//
//		wchar_t	wszGame_RegBuffer[128] = { 0 };
//		AddChar(pGameList[i].gi.wszGame_Reg,wszGame_RegBuffer,128);
//
//		wchar_t wszGame_SaveBuffer[128] = { 0 };
//		AddChar(pGameList[i].gi.wszGame_Save,wszGame_SaveBuffer,128);
//		wchar_t	wszGame_Exe_ParamBuffer[128] = { 0 };
//		AddChar(pGameList[i].gi.wszGame_Exe_Param,wszGame_Exe_ParamBuffer,128);
//
//		CString strInstTime;
//		strInstTime.Format(_T("%4d-%2d-%2d %2d:%2d:%2d"),pGameList[i].gi.InstTime.wYear,pGameList[i].gi.InstTime.wMonth,pGameList[i].gi.InstTime.wDay,pGameList[i].gi.InstTime.wHour,pGameList[i].gi.InstTime.wMinute,pGameList[i].gi.InstTime.wSecond);
//		CString	strNetInstTime;
//		strNetInstTime.Format(_T("%4d-%2d-%2d %2d:%2d:%2d"),pGameList[i].gi.NetInstTime.wYear,pGameList[i].gi.NetInstTime.wMonth,pGameList[i].gi.NetInstTime.wDay,pGameList[i].gi.NetInstTime.wHour,pGameList[i].gi.NetInstTime.wMinute,pGameList[i].gi.NetInstTime.wSecond);
//		CString	strNetUpdateTime;
//		strNetUpdateTime.Format(_T("%4d-%2d-%2d %2d:%2d:%2d"),pGameList[i].gi.NetUpdateTime.wYear,pGameList[i].gi.NetUpdateTime.wMonth,pGameList[i].gi.NetUpdateTime.wDay,pGameList[i].gi.NetUpdateTime.wHour,pGameList[i].gi.NetUpdateTime.wMinute,pGameList[i].gi.NetUpdateTime.wSecond);
//		CString	strUpdateTime;
//		strUpdateTime.Format(_T("%4d-%2d-%2d %2d:%2d:%2d"),pGameList[i].gi.UpdateTime.wYear,pGameList[i].gi.UpdateTime.wMonth,pGameList[i].gi.UpdateTime.wDay,pGameList[i].gi.UpdateTime.wHour,pGameList[i].gi.UpdateTime.wMinute,pGameList[i].gi.UpdateTime.wSecond);
//		strJson.Format(_T("{\"RESOURCE_INFO\":[{\"cbSize\":\"%d\",\
//						  \"dwFlags\":\"%d\",\
//						  \"gi_InstTime\":\"%s\",\
//						  \"gi_NetInstTime\":\"%s\",\
//						  \"gi_NetUpdateTime\":\"%s\",\
//						  \"gi_UpdateTime\":\"%s\",\
//						  \"gi_bClearFile\":\"%d\",\
//						  \"gi_bIsPlan\":\"%d\",\
//						  \"gi_bRestoreTime\":\"%d\",\
//						  \"gi_cbSize\":\"%ld\",\
//						  \"gi_dwDeleteGrade\":\"%ld\",\
//						  \"gi_dwFlags\":\"%ld\",\
//						  \"gi_dwFlags1\":\"%ld\",\
//						  \"gi_dwGameSize\":\"%ld\",\
//						  \"gi_dwGame_Click_Rate\":\"%ld\",\
//						  \"gi_dwGame_Show\":\"%ld\",\
//						  \"gi_dwGame_Sort\":\"%ld\",\
//						  \"gi_dwGame_Type\":\"%ld\",\
//						  \"gi_dwNet_Sort\":\"%ld\",\
//						  \"gi_dwOSType\":\"%ld\",\
//						  \"gi_dwRunMode\":\"%ld\",\
//						  \"gi_dwTopGrade\":\"%ld\",\
//						  \"gi_dwUpdate_Click_Rate\":\"%ld\",\
//						  \"gi_fMonthClick\":\"%02f\",\
//						  \"gi_nGame_Flag\":\"%d\",\
//						  \"gi_wszClass\":\"%s\",\
//						  \"gi_wszFuzzyIndex\":\"%s\",\
//						  \"gi_wszGame_Abc\":\"%s\",\
//						  \"gi_wszGame_Exe_Param\":\"%s\",\
//						  \"gi_wszGame_Id\":\"%s\",\
//						  \"gi_wszGame_Only\":\"%s\",\
//						  \"gi_wszGame_Path\":\"%s\",\
//						  \"gi_wszGame_Reg\":\"%s\",\
//						  \"gi_wszGame_Save\":\"%s\",\
//						  \"gi_wszGame_Text\":\"%s\",\
//						  \"gi_wszGame_URL\":\"%s\",\
//						  \"giex_bIsCustom\":\"%d\",\
//						  \"giex_cbSize\":\"%ld\",\
//						  \"giex_dwFlags\":\"%ld\",\
//						  \"giex_dwGame_Id\":\"%ld\",\
//						  \"giex_fInstalledDay\":\"%02f\",\
//						  \"giex_nImage\":\"%d\",\
//						  \"giex_nServerGameStatus\":\"%d\",\
//						  \"giex_nUpdateStatus\":\"%d\",\
//						  \"giex_wszUpdateStatus\":\"%s\"}]},"),
//						  pGameList[i].cbSize,
//						  pGameList[i].dwFlags,
//						  strInstTime,
//						  strNetInstTime,
//						  strNetUpdateTime,
//						  strUpdateTime,
//						  pGameList[i].gi.bClearFile,
//						  pGameList[i].gi.bIsPlan,
//						  pGameList[i].gi.bRestoreTime,
//						  pGameList[i].gi.cbSize,
//						  pGameList[i].gi.dwDeleteGrade,
//						  pGameList[i].gi.dwFlags,
//						  pGameList[i].gi.dwFlags1,
//						  pGameList[i].gi.dwGameSize,
//						  pGameList[i].gi.dwGame_Click_Rate,
//						  pGameList[i].gi.dwGame_Show,
//						  pGameList[i].gi.dwGame_Sort,
//						  pGameList[i].gi.dwGame_Type,
//						  pGameList[i].gi.dwNet_Sort,
//						  pGameList[i].gi.dwOSType,
//						  pGameList[i].gi.dwRunMode,
//						  pGameList[i].gi.dwTopGrade,
//						  pGameList[i].gi.dwUpdate_Click_Rate,
//						  pGameList[i].gi.fMonthClick,
//						  pGameList[i].gi.nGame_Flag,
//						  pGameList[i].gi.wszClass,
//						  pGameList[i].gi.wszFuzzyIndex,
//						  pGameList[i].gi.wszGame_Abc,
//						  wszGame_Exe_ParamBuffer,
//						  pGameList[i].gi.wszGame_Id,
//						  wzsGame_OnlyBuffer,
//						  wzsGame_PathBuffer,
//						  wszGame_RegBuffer,
//						  wszGame_SaveBuffer,
//						  pGameList[i].gi.wszGame_Text,
//						  pGameList[i].gi.wszGame_URL,
//						  pGameList[i].giex.bIsCustom,
//						  pGameList[i].giex.cbSize,
//						  pGameList[i].giex.dwFlags,
//						  pGameList[i].giex.dwGame_Id,
//						  pGameList[i].giex.fInstalledDay,
//						  pGameList[i].giex.nImage,
//						  pGameList[i].giex.nServerGameStatus,
//						  pGameList[i].giex.nUpdateStatus,
//						  pGameList[i].giex.wszUpdateStatus);
//		//WRITE_LOG(LOG_LEVEL_DEBUG,_T("%s"),strJson.GetBuffer());
//		strData += strJson;
//	}
//	pBt->m_strGameList.ReleaseBuffer();
//	pBt->m_strGameList = strData.Left(strData.GetLength() - 1);
//	pBt->m_strGameList += _T("]}");
//	m_fnbtcReleaseGamesInfo(&pGameList);
//
//	strData.ReleaseBuffer();
//End:
//	Sleep(1000 * 60);
//	goto Bigen;
//}

int		CBt::GetGameListInfo(CString	strJson, CString &strResult)
{
	//strJson = _T("{\"StTable\":\"COMMAND_PARAM\",\"cbSize\":\"0\",\"dwFlags\":\"0\",\"pgg\":\"0\",\"qt\":\"0\",\"qsc\":\"0\",\"iSortItem\":\"0\",\"iSortFlag\":\"0\",\"wszGroupName\":\"\"}");

	//COMMAND_PARAM	stCommand;
	//CString	strCommand;
	//m_JsonEx.ToJsonEx(_T("COMMAND_PARAM"),&stCommand,strCommand);


	//PVOID	pStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("COMMAND_PARAM"),&pStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//COMMAND_PARAM*	pGameParam = (COMMAND_PARAM*)pStData;
	//if (m_fnbtcGetGamesInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//pGameParam->cbSize = sizeof(COMMAND_PARAM);
	//pGameParam->dwFlags = m_fnbtcGetFlags(9);
	//RESOURCE_INFO*	pGameList = NULL;

	//int			nGameCount;
	//char*	pResuletData = NULL;
	//int nErrorChar = m_fnbtcGetGamesInfo((RESOURCE_INFO**)&pResuletData,pGameParam,&nGameCount);
	//if (nErrorChar != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取BT资源信息失败。 错误码：%d",nErrorChar);
	//	strResult.Format(_T("%d"),nErrorChar);
	//	return -1;
	//}

	//MZD_INI	MZDINI;
	//MZDINI.Load(pResuletData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("COMMAND_PARAM"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50001命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;
	
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_GAMES_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50001命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50001命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		DWORD	dwColor;
		OutIni.ReadFromINI(_T("T_GamesInfoEx"),i,_T("giex_dwWorkColor"),dwColor,0);
		DWORD	NewColor = GetRGB(dwColor);
		TCHAR	wszColor[32] = { 0 };
		wsprintf(wszColor,_T("%06X"),NewColor);
		OutIni.Write2INI(_T("T_GamesInfoEx"),i,_T("giex_dwWorkColor"),wszColor);
		m_JsonEx.ToJsonByIni(&OutIni,_T("RESOURCE_INFO"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);


	//int ErrorRet = m_fnbtcGetGamesInfo(&pGameList,pGameParam,&nGameCount);
	//if (ErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取BT资源信息失败。 错误码：%d",ErrorRet);
	//	strResult.Format(_T("%d"),ErrorRet);
	//	return -1;
	//}
	//if (nGameCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	WRITE_LOG(LOG_LEVEL_ERROR,L"数据条数为 %d",nGameCount);
	//	return 0;
	//}
	//if (pGameList->cbSize != sizeof(RESOURCE_INFO))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}

	//int		nBegin = pGameParam->nPage * pGameParam->nCount;
	//if (nBegin > nGameCount)
	//{
	//	strResult.Format(_T("5002"));
	//	return -1;
	//}
	//int		nEnd = nBegin + pGameParam->nCount;
	//if (nEnd > nGameCount)
	//{
	//	int nSub = nEnd - nGameCount;
	//	if (nSub >= pGameParam->nCount)
	//	{
	//		strResult.Format(_T("5002"));
	//		return -1;
	//	}
	//	nEnd = nBegin + (pGameParam->nCount - nSub);
	//}

	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nGameCount; i++)
	//{
	//	CString	strJson;
	//	//m_JsonEx.ToJsonEx(_T("RESOURCE_INFO"),&pGameList[i],strJson);
	//	m_JsonEx.ToJsonByIni(&MZDINI,_T("RESOURCE_INFO"),i,strJson);
	//	strData += strJson;
	//	strData += _T(",");

		//wchar_t	wzsGame_OnlyBuffer[128] = { 0 };
		//AddChar(pGameList[i].gi.wszGame_Only,wzsGame_OnlyBuffer,128);

		//wchar_t	wzsGame_PathBuffer[128] = { 0 };
		//AddChar(pGameList[i].gi.wszGame_Path,wzsGame_PathBuffer,128);

		//wchar_t	wszGame_RegBuffer[128] = { 0 };
		//AddChar(pGameList[i].gi.wszGame_Reg,wszGame_RegBuffer,128);

		//wchar_t wszGame_SaveBuffer[128] = { 0 };
		//AddChar(pGameList[i].gi.wszGame_Save,wszGame_SaveBuffer,128);

		//wchar_t	wszGame_Exe_ParamBuffer[128] = { 0 };
		//AddChar(pGameList[i].gi.wszGame_Exe_Param,wszGame_Exe_ParamBuffer,128);

		//wchar_t	wszGame_URL_Buffer[128] = { 0 };
		//AddChar(pGameList[i].gi.wszGame_URL,wszGame_URL_Buffer,128);

		//DWORD dwRGB = GetRGB(pGameList[i].giex.dwWorkColor);

		//CString strInstTime;
		//strInstTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pGameList[i].gi.InstTime.wYear,pGameList[i].gi.InstTime.wMonth,pGameList[i].gi.InstTime.wDay,pGameList[i].gi.InstTime.wHour,pGameList[i].gi.InstTime.wMinute,pGameList[i].gi.InstTime.wSecond);
		//CString	strNetInstTime;
		//strNetInstTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pGameList[i].gi.NetInstTime.wYear,pGameList[i].gi.NetInstTime.wMonth,pGameList[i].gi.NetInstTime.wDay,pGameList[i].gi.NetInstTime.wHour,pGameList[i].gi.NetInstTime.wMinute,pGameList[i].gi.NetInstTime.wSecond);
		//CString	strNetUpdateTime;
		//strNetUpdateTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pGameList[i].gi.NetUpdateTime.wYear,pGameList[i].gi.NetUpdateTime.wMonth,pGameList[i].gi.NetUpdateTime.wDay,pGameList[i].gi.NetUpdateTime.wHour,pGameList[i].gi.NetUpdateTime.wMinute,pGameList[i].gi.NetUpdateTime.wSecond);
		//CString	strUpdateTime;
		//strUpdateTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pGameList[i].gi.UpdateTime.wYear,pGameList[i].gi.UpdateTime.wMonth,pGameList[i].gi.UpdateTime.wDay,pGameList[i].gi.UpdateTime.wHour,pGameList[i].gi.UpdateTime.wMinute,pGameList[i].gi.UpdateTime.wSecond);
		//strJson.Format(_T("{\"RESOURCE_INFO\":[{\"cbSize\":\"%d\",\
		//				  \"dwFlags\":\"%d\",\
		//				  \"gi_InstTime\":\"%s\",\
		//				  \"gi_NetInstTime\":\"%s\",\
		//				  \"gi_NetUpdateTime\":\"%s\",\
		//				  \"gi_UpdateTime\":\"%s\",\
		//				  \"gi_bClearFile\":\"%d\",\
		//				  \"gi_bIsPlan\":\"%d\",\
		//				  \"gi_bRestoreTime\":\"%d\",\
		//				  \"gi_cbSize\":\"%ld\",\
		//				  \"gi_dwDeleteGrade\":\"%ld\",\
		//				  \"gi_dwFlags\":\"%ld\",\
		//				  \"gi_dwFlags1\":\"%ld\",\
		//				  \"gi_dwGameSize\":\"%ld\",\
		//				  \"gi_dwGame_Click_Rate\":\"%ld\",\
		//				  \"gi_dwGame_Show\":\"%ld\",\
		//				  \"gi_dwGame_Sort\":\"%ld\",\
		//				  \"gi_dwGame_Type\":\"%ld\",\
		//				  \"gi_dwNet_Sort\":\"%ld\",\
		//				  \"gi_dwOSType\":\"%ld\",\
		//				  \"gi_dwRunMode\":\"%ld\",\
		//				  \"gi_dwTopGrade\":\"%ld\",\
		//				  \"gi_dwUpdate_Click_Rate\":\"%ld\",\
		//				  \"gi_fMonthClick\":\"%02f\",\
		//				  \"gi_nGame_Flag\":\"%d\",\
		//				  \"gi_wszClass\":\"%s\",\
		//				  \"gi_wszFuzzyIndex\":\"%s\",\
		//				  \"gi_wszGame_Abc\":\"%s\",\
		//				  \"gi_wszGame_Exe_Param\":\"%s\",\
		//				  \"gi_wszGame_Id\":\"%s\",\
		//				  \"gi_wszGame_Only\":\"%s\",\
		//				  \"gi_wszGame_Path\":\"%s\",\
		//				  \"gi_wszGame_Reg\":\"%s\",\
		//				  \"gi_wszGame_Save\":\"%s\",\
		//				  \"gi_wszGame_Text\":\"%s\",\
		//				  \"gi_wszGame_URL\":\"%s\",\
		//				  \"gi_dwShortcut\":\"%d\",\
		//				  \"giex_cbSize\":\"%ld\",\
		//				  \"giex_dwFlags\":\"%ld\",\
		//				  \"giex_dwGame_Id\":\"%ld\",\
		//				  \"giex_fInstalledDay\":\"%02f\",\
		//				  \"giex_nServerGameStatus\":\"%d\",\
		//				  \"giex_dwWorkStatus\":\"%d\",\
		//				  \"giex_wszWorkStatus\":\"%s\",\
		//				  \"giex_dwWorkImage\":\"%ld\",\
		//				  \"giex_dwWorkColor\":\"%06X\"}]},"),
		//				  pGameList[i].cbSize,
		//				  pGameList[i].dwFlags,
		//				  strInstTime,
		//				  strNetInstTime,
		//				  strNetUpdateTime,
		//				  strUpdateTime,
		//				  pGameList[i].gi.bClearFile,
		//				  pGameList[i].gi.bIsPlan,
		//				  pGameList[i].gi.bRestoreTime,
		//				  pGameList[i].gi.cbSize,
		//				  pGameList[i].gi.dwDeleteGrade,
		//				  pGameList[i].gi.dwFlags,
		//				  pGameList[i].gi.dwFlags1,
		//				  pGameList[i].gi.dwGameSize,
		//				  pGameList[i].gi.dwGame_Click_Rate,
		//				  pGameList[i].gi.dwGame_Show,
		//				  pGameList[i].gi.dwGame_Sort,
		//				  pGameList[i].gi.dwGame_Type,
		//				  pGameList[i].gi.dwNet_Sort,
		//				  pGameList[i].gi.dwOSType,
		//				  pGameList[i].gi.dwRunMode,
		//				  pGameList[i].gi.dwTopGrade,
		//				  pGameList[i].gi.dwUpdate_Click_Rate,
		//				  pGameList[i].gi.fMonthClick,
		//				  pGameList[i].gi.nGame_Flag,
		//				  pGameList[i].gi.wszClass,
		//				  pGameList[i].gi.wszFuzzyIndex,
		//				  pGameList[i].gi.wszGame_Abc,
		//				  wszGame_Exe_ParamBuffer,
		//				  pGameList[i].gi.wszGame_Id,
		//				  wzsGame_OnlyBuffer,
		//				  wzsGame_PathBuffer,
		//				  wszGame_RegBuffer,
		//				  wszGame_SaveBuffer,
		//				  pGameList[i].gi.wszGame_Text,
		//				  wszGame_URL_Buffer,
		//				  pGameList[i].gi.dwShortcut,
		//				  pGameList[i].giex.cbSize,
		//				  pGameList[i].giex.dwFlags,
		//				  pGameList[i].giex.dwGame_Id,
		//				  pGameList[i].giex.fInstalledDay,
		//				  pGameList[i].giex.nServerGameStatus,
		//				  pGameList[i].giex.dwWorkStatus,
		//				  pGameList[i].giex.wszWorkStatus,
		//				  pGameList[i].giex.dwWorkImage,
		//				  dwRGB);

		//strData += strJson;
	//	Sleep(1);
	//}
	////WRITE_LOG(LOG_LEVEL_DEBUG,L"一共接收条数：%d   一共处理了：%d   总大小：%ld",nGameCount, nu, strData.GetBuffer());

	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseGamesInfo(&pGameList);
	//m_JsonEx.ToStructRelease(pStData);
	return 1;
}

int		CBt::GetWgsInfo(CString &strResult)
{
	//if (m_fnbtcGetWgsInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//T_WgsInfo*	pWgsList;
	//int nCount;
	//int nErrorRet = m_fnbtcGetWgsInfo(&pWgsList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取辅助工具信息失败。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if(pWgsList->cbSize != sizeof(T_WgsInfo))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("WgsInfo"),&pWgsList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseWgsInfo(&pWgsList);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_WG_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50002命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50002命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("WgsInfo"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetParentClassInfo(CString strJson, CString& strResult)
{
	//if (m_fnbtcGetParentClassInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//T_ClassInfo*	pClassList = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetParentClassInfo(&pClassList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取菜单大类信息失败。 错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}

	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pClassList->cbSize != sizeof(T_ClassInfo))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("ClassInfo"),&pClassList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseParentClassInfo(&pClassList);
	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50003命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_PARENT_CLASS_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50003命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50003命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("T_ClassInfo"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetSubClassInfo(CString	strJson, CString& strResult)
{
	//if (m_fnbtcGetSubClassInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//T_ClassInfo*	pClassList = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetSubClassInfo(&pClassList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取菜单小类信息失败。 错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pClassList->cbSize != sizeof(T_ClassInfo))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("ClassInfo"),&pClassList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseSubClassInfo(&pClassList);
	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50003命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);
	;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SUB_CLASS_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50004命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50004命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("T_ClassInfo"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetMovieInfo(CString &strResult)
{
	//if (m_fnbtcGetMovieInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//T_Movie*	pMovieList = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetMovieInfo(&pMovieList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取T_MovieInfo数据失败。 错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pMovieList->cbSize != sizeof(T_Movie))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("Movie"),&pMovieList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseMovieInfo(&pMovieList);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_MOVIE_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50005命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50005命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("T_Movie"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetOnlineInfo(CString &strResult)
{
	//if (m_fnbtcGetOnlineInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//T_Online*	pOnlineList = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetOnlineInfo(&pOnlineList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取T_Online数据失败。 错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pOnlineList->cbSize != sizeof(T_Online))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("Online"),&pOnlineList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseOnlineInfo(&pOnlineList);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_ONLINE_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50006命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50006命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("T_Online"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetPlayerListInfo(CString &strResult)
{
	//if (m_fnbtcGetPlayerListInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//T_PlayerList*	pPlayerList = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetPlayerListInfo(&pPlayerList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"获取T_Player数据失败。 错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pPlayerList->cbSize != sizeof(T_PlayerList))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("PlayerList"),&pPlayerList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleasePlayerListInfo(&pPlayerList);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_PLAYER_LIST_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50007命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50007命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("T_PlayerList"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::ConnectServ(CString &strResult)
{
	//if (m_fnbtcConnectServ == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//int nErrorRet = m_fnbtcConnectServ();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50008号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CONNECT_SERV,NULL,0,NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50008号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::UILogin(CString strJson, CString &strResult)
{
	//if (m_fnbtcUILogin == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("UI_LOGING_USERPSW"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//UI_LOGING_USERPSW* pUiInfo = (UI_LOGING_USERPSW*)lpStData;
	//pUiInfo->cbSize = sizeof(UI_LOGING_USERPSW);
	//pUiInfo->dwFlags = m_fnbtcGetFlags(2);

	//UI_LOGIN_REPLY	pReply;
	//pReply.cbSize = sizeof(UI_LOGIN_REPLY);
	//pReply.dwFlags = m_fnbtcGetFlags(8);

	//int nErrorRet = m_fnbtcUILogin(pUiInfo,&pReply);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50009号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("UI_LOGIN_REPLY"),&pReply,strResult);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("UI_LOGING_USERPSW"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50009命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;


	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_UI_LOGIN,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)	//命令执行失败
	{
		if (nErrorRet == 10061)	//错误原因为网络错误
		{
			//检查是否为服务未开启导致
			if(CAppMain::GetAppMain()->m_FQ.Web_GetBtCurrentStatus(strResult) == 0)
			{
				nErrorRet = 70085;
			}
		}
		WRITE_LOG(LOG_LEVEL_ERROR,"50009命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("UI_LOGIN_REPLY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50009命令转JSON失败");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetLoginInfo(CString& strResult)
{
	//if (m_fnbtcGetLoginInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//UI_LOGIN_REPLY	UserInfo;
	//UserInfo.cbSize = sizeof(UI_LOGIN_REPLY);
	//UserInfo.dwFlags = m_fnbtcGetFlags(8);
	//int nErrorRet = m_fnbtcGetLoginInfo(&UserInfo);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50010号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (UserInfo.cbSize != sizeof(UI_LOGIN_REPLY))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"50010号命令需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("UI_LOGIN_REPLY"),&UserInfo,strResult);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_LOGIN_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50010命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("UI_LOGIN_REPLY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50010命令转JSON失败");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

//此接口过于危险。
int		CBt::SetConnectPassword(CString strJson, CString &strResult)
{
	//if (m_fnbtcSetConnectPassword == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//int nErrorRet = m_fnbtcSetConnectPassword(strJson.GetBuffer());
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50011号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	return 1;
}

int		CBt::SyncData(CString &strResult)
{
	//if (m_fnbtcSyncData == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//int nErrorRet = m_fnbtcSyncData();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50012号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SYNC_DATA,NULL,0,NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50012号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}
int		CBt::GetSyncProgress(CString &strResult)
{
	//if (m_fnbtcGetSyncProgress == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//SYNC_DATA_PROGRESS	SyncData;
	//SyncData.cbSize = sizeof(SYNC_DATA_PROGRESS);
	//SyncData.dwFlags = m_fnbtcGetFlags(6);
	//int nErrorRet = m_fnbtcGetSyncProgress(&SyncData);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50013号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (SyncData.cbSize != sizeof(SYNC_DATA_PROGRESS))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"50013号命令需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("SYNC_DATA_PROGRESS"),&SyncData,strResult);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SYNC_PROGRESS,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50013命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("SYNC_DATA_PROGRESS"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50013命令转JSON失败");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);

	return 1;
}

int		CBt::GetServerWorkStatus(CString& strResult)
{
	//if (m_fnbtcGetServerWorkStatus == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//DWORD	dwStatus;
	//int nErrorRet = m_fnbtcGetServerWorkStatus(&dwStatus);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50014号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("%ld"),dwStatus);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SERV_WORK_STATUS,NULL,0,&pOutData,&nCount,NULL);	//获取bt服务状态
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50014命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_DWORD_VALUE"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50014命令转JSON失败");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetBtConfig(CString &strResult)
{
	//if (m_fnbtcGetBtConfig == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//BT_CONFIG_INFO	BtInfo;

	//int nErrorRet = m_fnbtcGetBtConfig(&BtInfo);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50015号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (BtInfo.cbSize != sizeof(BT_CONFIG_INFO))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50015号命令。需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("BT_CONFIG_INFO"),&BtInfo,strResult);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_BT_CONFIG,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50015命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_CONFIG_INFO"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50015命令转JSON失败");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetBtConfig(CString strJson, CString& strResult)
{
	//if (m_fnbtcSetBtConfig == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("BT_CONFIG_INFO"), &lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//BT_CONFIG_INFO*	pBtConfig = (BT_CONFIG_INFO*)lpStData;
	//pBtConfig->cbSize = sizeof(BT_CONFIG_INFO);
	//pBtConfig->dwFlags = m_fnbtcGetFlags(32);
	//pBtConfig->dwFlags1 = m_fnbtcGetFlags(29);

	//int nErrorRet = m_fnbtcSetBtConfig(pBtConfig);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50016号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_CONFIG_INFO"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50016命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;



	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SET_BT_CONFIG,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50016命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetMenuConfig(CString &strResult)
{
	//if (m_fnbtcGetMenuConfig == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//MENU_CONFIG	BtMenu;
	//BtMenu.cbSize = sizeof(MENU_CONFIG);
	//BtMenu.dwFlags = m_fnbtcGetFlags(2);
	//BtMenu.manager.cbSize = sizeof(T_Manager);
	//BtMenu.manager.dwFlags = m_fnbtcGetFlags(32);
	//BtMenu.manager.dwFlags1 = m_fnbtcGetFlags(32);
	//BtMenu.manager.dwFlags2 = m_fnbtcGetFlags(4);
	//BtMenu.mcex.cbSize = sizeof(MENU_CONFIG_EX);
	//BtMenu.mcex.dwFlags = m_fnbtcGetFlags(2);


	//int nErrorRet = m_fnbtcGetMenuConfig(&BtMenu);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50017号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (BtMenu.cbSize != sizeof(MENU_CONFIG))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50017号命令。需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("MENU_CONFIG"),&BtMenu,strResult);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_MENU_CONFIG,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50017命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("MENU_CONFIG"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50017命令转JSON失败");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetMenuConfig(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("MENU_CONFIG"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//MENU_CONFIG*	pMeun = (MENU_CONFIG*)lpStData;
	//pMeun->cbSize = sizeof(MENU_CONFIG);
	//pMeun->dwFlags = m_fnbtcGetFlags(2);

	//int nErrorRet = m_fnbtcSetMenuConfig(pMeun);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50018号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("MENU_CONFIG"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50018命令转INI失败");
		return -1;
	}
	TCHAR*	pwszBnoticeBuffer = new TCHAR[4096];
	char*	pszBnoticeBuffer = new char[4096]; 
	InIni.ReadFromINI(_T("T_Manager"),0,_T("wszShowBoardText"),pwszBnoticeBuffer,4096,NULL);
	WideCharToMultiByte(CP_ACP,0,pwszBnoticeBuffer,4096,pszBnoticeBuffer,4096,NULL,NULL);

	CString	strAppPath = CAppMain::GetAppPath() + _T("Notice\\");
	CString	strNoticeBakPath = strAppPath + _T("nbnotice.bak");
	HANDLE	hFile = CreateFile(strNoticeBakPath.GetBuffer(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == (HANDLE)-1)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50018无法打开文件：%ws",strNoticeBakPath.GetBuffer());
		return -1;
	}
	ULONG	ulFileSize = GetFileSize(hFile,NULL);
	char*	pData = new char[ulFileSize];
	ULONG	ulRead;
	ReadFile(hFile,pData,ulFileSize,&ulRead,NULL);
	CloseHandle(hFile);

	CString	strNoticePath = strAppPath + _T("nbnotice.htm");
	DeleteFile(strNoticePath.GetBuffer());
	CString	strNotice2Path = strAppPath + _T("nbboard.htm");
	DeleteFile(strNotice2Path.GetBuffer());

	static	const char*	pszEndData = "</td></tr></table></body></html>";
	int nStaticLen = strlen(pszEndData);

	ULONG	ulWrite;
	HANDLE	hTargetFile = CreateFile(strNoticePath.GetBuffer(),GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hTargetFile == (HANDLE)-1)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50018无法被创建：%ws",strNoticePath.GetBuffer());
		return -1;
	}
	WriteFile(hTargetFile,pData,ulFileSize,&ulWrite,NULL);
	WriteFile(hTargetFile,pszBnoticeBuffer,strlen(pszBnoticeBuffer),&ulWrite,NULL);
	WriteFile(hTargetFile,pszEndData,nStaticLen,&ulWrite,NULL);
	CloseHandle(hTargetFile);

	HANDLE	hTarget2File = CreateFile(strNotice2Path.GetBuffer(),GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hTarget2File == (HANDLE)-1)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50018无法被创建：%ws",strNotice2Path.GetBuffer());
		return -1;
	}
	WriteFile(hTarget2File,pData,ulFileSize,&ulWrite,NULL);
	WriteFile(hTarget2File,pszBnoticeBuffer,strlen(pszBnoticeBuffer),&ulWrite,NULL);
	WriteFile(hTarget2File,pszEndData,nStaticLen,&ulWrite,NULL);
	CloseHandle(hTarget2File);

	delete []pData;
	delete []pszBnoticeBuffer;
	delete []pwszBnoticeBuffer;

	char* pOutData = NULL;
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SET_MENU_CONFIG,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50018命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GameGetSuperfluousInfo(CString&	strResult)
{
	//RESOURCE_INFO*	pGame = NULL;
	//int		nCount;
	//int nErrorRet = m_fnbtcGameGetSuperfluousInfo(&pGame,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50019号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pGame->cbSize != sizeof(RESOURCE_INFO))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50019号命令。需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("RESOURCE_INFO"),&pGame[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseGameSuperfluousInfo(&pGame);


	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_GET_SUPERFLUOUS_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50019命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50019命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	DWORD	dwColor;
	OutIni.ReadFromINI(_T("T_GamesInfoEx"),0,_T("giex_dwWorkColor"),dwColor,0);
	DWORD	NewColor = GetRGB(dwColor);
	TCHAR	wszColor[32] = { 0 };
	wsprintf(wszColor,_T("%06X"),NewColor);
	OutIni.Write2INI(_T("T_GamesInfoEx"),0,_T("giex_dwWorkColor"),wszColor);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("RESOURCE_INFO"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GameGetDeleteSort(CString &strResult)
{
	//GAME_DELETE_SORT*	pGame = NULL;
	//int		nCount;
	//int		nErrorRet = m_fnbtcGameGetDeleteSort(&pGame,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50020号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (pGame->cbSize != sizeof(GAME_DELETE_SORT))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50020号命令。需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"50020\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("GAME_DELETE_SORT"),&pGame[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseGameDeleteSort(&pGame);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_GET_DELETE_SORT,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50020命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if(nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50020命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("GAME_DELETE_SORT"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return	1;
}

int		CBt::GetSimpleProperty(CString	strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("GET_GAME_SIMPLE_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//GET_GAME_SIMPLE_PROPERTY*	pSimple = (GET_GAME_SIMPLE_PROPERTY*)lpStData;
	//pSimple->cbSize = sizeof(GET_GAME_SIMPLE_PROPERTY);
	//pSimple->dwFlags = m_fnbtcGetFlags(9);

	//int		nErrorRet = m_fnbtcGetSimpleProperty(pSimple);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50021号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	m_JsonEx.ToStructRelease(lpStData);
	//	return -1;
	//}
	//if (pSimple->cbSize != sizeof(GET_GAME_SIMPLE_PROPERTY))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50021号命令。需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("GET_GAME_SIMPLE_PROPERTY"),pSimple,strResult);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50021命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_GET_SIMPLE_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50021命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("GET_GAME_SIMPLE_PROPERTY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50021号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetSimpleProperty(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("SET_GAME_SIMPLE_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//SET_GAME_SIMPLE_PROPERTY*	pSimple = (SET_GAME_SIMPLE_PROPERTY*)lpStData;
 //	pSimple->cbSize = sizeof(SET_GAME_SIMPLE_PROPERTY);
 //	pSimple->dwFlags = m_fnbtcGetFlags(7);

	//int nErrorRet = m_fnbtcSetSimpleProperty(pSimple);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50022号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	m_JsonEx.ToStructRelease(lpStData);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("SET_GAME_SIMPLE_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50022命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_SET_SIMPLE_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50022命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetBtSystemInfo(CString &strResult)
{
	//BT_SYSTEM_INFO	btSystem;
	//btSystem.cbSize = sizeof(BT_SYSTEM_INFO);
	//btSystem.dwFlags = m_fnbtcGetFlags(13);

	//int nErrorRet = m_fnbtcGetBtSystemInfo(&btSystem);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50023号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (btSystem.cbSize != sizeof(BT_SYSTEM_INFO))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50023号命令。需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("BT_SYSTEM_INFO"),&btSystem,strResult);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_BT_SYSTEM_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50023命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_SYSTEM_INFO"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50023号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetResourceNumber(CString& strResult)
{
	//BT_RESOURCE_NUMBER	btResource;
	////btResource.cbSize = sizeof(BT_RESOURCE_NUMBER);
	////btResource.dwFlags = m_fnbtcGetFlags(12);

	//int nErrorRet = m_fnbtcGetResourceNumber(&btResource);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50024号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (btResource.cbSize != sizeof(BT_RESOURCE_NUMBER))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50024号命令。需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("BT_RESOURCE_NUMBER"),&btResource,strResult);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_RESOURCE_NUMBER,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50024命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_RESOURCE_NUMBER"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50024号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return	1;
}

int		CBt::GameDelete(CString strJson, CString& strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcGameDelete(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50025号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50025命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;


	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_DELETE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50025命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));

	return 1;
}

int		CBt::GameClearFileDir(CString strJson, CString &strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcGameClearFileDir(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50026号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50026命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;


	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_CLEAR_FILEDIR,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50026命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GameMoveDirectory(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("GAME_MOVE_DIRECTORY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//GAME_MOVE_DIRECTORY*	pGameDirectory = (GAME_MOVE_DIRECTORY*)lpStData;
	//pGameDirectory->cbSize = sizeof(GAME_MOVE_DIRECTORY);
	//pGameDirectory->dwFlags = m_fnbtcGetFlags(3);

	//int nErrorRet = m_fnbtcGameMoveDirectory(pGameDirectory);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50027号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("GAME_MOVE_DIRECTORY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50027命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_MOVE_DIRECTORY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50027命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GameRepair(CString strJson, CString &strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcGameRepair(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50028号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50028命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_REPAIR,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50028命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GameSetAutoUpdate(CString strJson, CString& strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcGameSetAutoUpdate(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50029号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50029命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_SET_AUTO_UPDATE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50029命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));

	return 1;
}

int		CBt::GameSetManualUpdate(CString strJson, CString& strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcGameSetManualUpdate(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50030号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50030命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_SET_MANUAL_UPDATE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50030命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::AddCustomGame(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("RESOURCE_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//RESOURCE_PROPERTY*	pGame = (RESOURCE_PROPERTY*)lpStData;
	//pGame->gi.cbSize = sizeof(_T_GamesInfo);
	//pGame->dwFlags = BTS_FLAGS_32[32];
	//pGame->dwFlags = BTS_FLAGS_32[8];
	//pGame->cbSize = sizeof(RESOURCE_PROPERTY);
	//pGame->dwFlags = m_fnbtcGetFlags(2);

	//int nErrorRet = m_fnbtcAddCustomGame(pGame);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50031号命令。错误码：%d",nErrorRet);
	//	m_JsonEx.ToStructRelease(lpStData);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("RESOURCE_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50031命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CUSTOM_GAME_ADD,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50031命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetCustomGameMaxId(CString& strResult)
{
	//DWORD	dwGameId;
	//int nErrorRet = m_fnbtcGetCustomGameMaxId(&dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50032号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("%ld"),dwGameId);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CUSTOM_GAME_GET_MAXID,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50032命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_DWORD_VALUE"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50032号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetCustomGameProperty(CString strJson, CString& strResult)
{
//	DWORD	dwGameId = _ttol(strJson);
//	RESOURCE_PROPERTY	ResourceProperty;
//// 	ResourceProperty.cbSize = sizeof(RESOURCE_PROPERTY);
//// 	ResourceProperty.dwFlags = m_fnbtcGetFlags(2);
//
//	int nErrorRet = m_fnbtcGetCustomGameProperty(dwGameId,&ResourceProperty);
//	if (nErrorRet != SCMD_OK)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,"50033号命令。错误码：%d",nErrorRet);
//		strResult.Format(_T("%d"),nErrorRet);
//		return -1;
//	}
//	if (ResourceProperty.cbSize != sizeof(RESOURCE_PROPERTY))
//	{
//		WRITE_LOG(LOG_LEVEL_WARN,"%s","50033号命令。需要更新");
//	}
//	m_JsonEx.ToJsonEx(_T("RESOURCE_PROPERTY"),&ResourceProperty,strResult);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50033命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CUSTOM_GAME_GET_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50033命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("RESOURCE_PROPERTY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50033号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::ModifyCustomGameProperty(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("RESOURCE_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//RESOURCE_PROPERTY*	pGame = (RESOURCE_PROPERTY*)lpStData;
	//pGame->cbSize = sizeof(RESOURCE_PROPERTY);
	//pGame->dwFlags = m_fnbtcGetFlags(2);

	//int nErrorRet = m_fnbtcModifyCustomGameProperty(pGame);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50034号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("RESOURCE_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50034命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CUSTOM_GAME_MODIFY_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50034命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::DeleteCustomGame(CString strJson, CString& strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcDeleteCustomGame(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50035号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50035命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);


	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CUSTOM_GAME_DELETE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50035命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetTaskInfo(CString& strResult)
{
	//TASK_INFO*	pTaskList = NULL;
	//int		nCount;

	//int nErrorRet = m_fnbtcGetTaskInfo(&pTaskList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50036号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	////int size = sizeof(TASK_INFO);
	//if(pTaskList->cbSize != sizeof(TASK_INFO))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50036号命令需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	wchar_t	wszIdxPathBuffer[360] = { 0 };
	//	AddChar(pTaskList[i].bti.wszIdxPath,wszIdxPathBuffer,360);
	//	wchar_t	wszDirectoryBuffer[360] = { 0 };
	//	AddChar(pTaskList[i].bti.wszDirectory,wszDirectoryBuffer,360);
	//	wchar_t	wszCacheDirectoryBuffer[360] = { 0 };
	//	AddChar(pTaskList[i].bti.wszCacheDirectory,wszCacheDirectoryBuffer,360);
	//	wchar_t wszWorkStatusBuffer[360] = { 0 };
	//	AddChar(pTaskList[i].bti.wszWorkStatus,wszWorkStatusBuffer,360);

	//	wchar_t	wszErrorInfo[128] = { 0 };
	//	CChineseCode::AsciiToUnicode(wszErrorInfo, pTaskList[i].bti.szErrorInfo);
	//	wchar_t	wszErrorInfoEx[128] = { 0 };
	//	AddChar(wszErrorInfo,wszErrorInfoEx,128);

	//	CString	strtmAdd;
	//	strtmAdd.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),pTaskList[i].bti.tmAdd.wYear,pTaskList[i].bti.tmAdd.wMonth,pTaskList[i].bti.tmAdd.wDay,pTaskList[i].bti.tmAdd.wHour,pTaskList[i].bti.tmAdd.wMinute,pTaskList[i].bti.tmAdd.wSecond);
	//	CString	strtmStart;
	//	strtmStart.Format(_T("04d-%02d-%02d %02d:%02d:%02d"),pTaskList[i].bti.tmStart.wYear,pTaskList[i].bti.tmStart.wMonth,pTaskList[i].bti.tmStart.wDay,pTaskList[i].bti.tmStart.wHour,pTaskList[i].bti.tmStart.wMinute,pTaskList[i].bti.tmStart.wSecond);
	//	CString	strtmFinished;
	//	strtmFinished.Format(_T("04d-%02d-%02d %02d:%02d:%02d"),pTaskList[i].bti.tmFinished.wYear,pTaskList[i].bti.tmFinished.wMonth,pTaskList[i].bti.tmFinished.wDay,pTaskList[i].bti.tmFinished.wHour,pTaskList[i].bti.tmFinished.wMinute,pTaskList[i].bti.tmFinished.wSecond);
	//	CString	strJson;

	//	float f = (100.00 - pTaskList[i].pdi.di.currentTaskProgress) / 100.00;
	//	INT64	I64SurplusSize = f * pTaskList[i].pdi.di.totalFileSizeExcludePadding;
	//	DWORD	dwSurplusTime = 0;
	//	if (pTaskList[i].pdi.di.downloadSpeed > 0)
	//	{
	//		dwSurplusTime = I64SurplusSize / pTaskList[i].pdi.di.downloadSpeed;
	//	}

	//	//m_JsonEx.ToJsonEx(_T("TASK_INFO"),&pTaskList[i],strJson);
	//	//strData += strJson;
	//	//strData +=_T(",");
	//	strJson.Format(_T("{\"TASK_INFO\":[{\"cbSize\":\"%d\",\
	//					  \"dwFlags\":\"%d\",\
	//					  \"downloader_state\":\"%d\",\
	//					  \"downloader_percentDone\":\"%2f\",\
	//					  \"downloader_downConnectionCount\":\"%d\",\
	//					  \"downloader_downloadLimit\":\"%d\",\
	//					  \"downloader_connectionCount\":\"%d\",\
	//					  \"downloader_totalCompletedSeeds\":\"%d\",\
	//					  \"downloader_inCompleteNum\":\"%d\",\
	//					  \"downloader_seedConnected\":\"%d\",\
	//					  \"downloader_totalCurrentSeedCount\":\"%d\",\
	//					  \"downloader_totalCurrentPeerCount\":\"%d\",\
	//					  \"downloader_currentTaskProgress\":\"%2f\",\
	//					  \"downloader_bPaused\":\"%d\",\
	//					  \"downloader_bError\":\"%d\",\
	//					  \"downloader_downloadSpeed\":\"%d\",\
	//					  \"downloader_uploadSpeed\":\"%d\",\
	//					  \"downloader_wastedByteCount\":\"%I64d\",\
	//					  \"downloader_totalDownloadedBytes\":\"%I64d\",\
	//					  \"downloader_totalUploadedBytes\":\"%I64d\",\
	//					  \"downloader_totalFileSize\":\"%I64d\",\
	//					  \"downloader_totalFileSizeExcludePadding\":\"%I64d\",\
	//					  \"downloader_totalPaddingSize\":\"%I64d\",\
	//					  \"downloader_pieceCount\":\"%d\",\
	//					  \"downloader_pieceSize\":\" %d\",\
	//					  \"downloader_infoHash\":\"%s\",\
	//					  \"downloader_torrentName\":\"%s\",\
	//					  \"basic_cbSize\":\"%ld\",\
	//					  \"basic_dwFlags\":\"%ld\",\
	//					  \"basic_dwID\":\"%ld\",\
	//					  \"basic_dwIndex\":\"%ld\",\
	//					  \"basic_tsAutoState\":\"%ld\",\
	//					  \"basic_tsUseDirType\":\"%ld\",\
	//					  \"basic_tsTrigger\":\"%ld\",\
	//					  \"basic_tmAdd\":\"%s\",\
	//					  \"basic_tmStart\":\"%s\",\
	//					  \"basic_tmFinished\":\"%s\",\
	//					  \"basic_hDownloader\":\"%ld\",\
	//					  \"basic_wszGame_Name\":\"%s\",\
	//					  \"basic_wszDirectoryName\":\"%s\",\
	//					  \"basic_wszIdxPath\":\"%s\",\
	//					  \"basic_wszDirectory\":\"%s\",\
	//					  \"basic_wszCacheDirectory\":\"%s\",\
	//					  \"basic_wszHash\":\"%s\",\
	//					  \"basic_szErrorInfo\":\"%s\",\
	//					  \"basic_tsDirState\":\"%ld\",\
	//					  \"basic_iChangePieces\":\"%d\",\
	//					  \"basic_pChangePiecesArray\":\"%d\",\
	//					  \"basic_wszWorkStatus\":\"%s\",\
	//					  \"basic_dwWorkImage\":\"%ld\",\
	//					  \"SurplusSize\":\"%I64d\",\
	//					  \"dwSurplusTime\":\"%ld\"}]}"),
	//					  pTaskList[i].cbSize,
	//					  pTaskList[i].dwFlags,
	//					  pTaskList[i].pdi.di.state,
	//					  pTaskList[i].pdi.di.percentDone,
	//					  pTaskList[i].pdi.di.downConnectionCount,
	//					  pTaskList[i].pdi.di.downloadLimit,
	//					  pTaskList[i].pdi.di.connectionCount,
	//					  pTaskList[i].pdi.di.totalCompletedSeeds,
	//					  pTaskList[i].pdi.di.inCompleteNum,
	//					  pTaskList[i].pdi.di.seedConnected,
	//					  pTaskList[i].pdi.di.totalCurrentSeedCount,
	//					  pTaskList[i].pdi.di.totalCurrentPeerCount,
	//					  pTaskList[i].pdi.di.currentTaskProgress,
	//					  pTaskList[i].pdi.di.bPaused,
	//					  pTaskList[i].pdi.di.bError,
	//					  pTaskList[i].pdi.di.downloadSpeed,
	//					  pTaskList[i].pdi.di.uploadSpeed,
	//					  pTaskList[i].pdi.di.wastedByteCount,
	//					  pTaskList[i].pdi.di.totalDownloadedBytes,
	//					  pTaskList[i].pdi.di.totalUploadedBytes,
	//					  pTaskList[i].pdi.di.totalFileSize,
	//					  pTaskList[i].pdi.di.totalFileSizeExcludePadding,
	//					  pTaskList[i].pdi.di.totalPaddingSize,
	//					  pTaskList[i].pdi.di.pieceCount,
	//					  pTaskList[i].pdi.di.pieceSize,
	//					  pTaskList[i].pdi.di.infoHash,
	//					  pTaskList[i].pdi.di.torrentName,
	//					  pTaskList[i].bti.cbSize,
	//					  pTaskList[i].bti.dwFlags,
	//					  pTaskList[i].bti.dwID,
	//					  pTaskList[i].bti.dwIndex,
	//					  pTaskList[i].bti.tsAutoState,
	//					  pTaskList[i].bti.tsUseDirType,
	//					  pTaskList[i].bti.tsTrigger,
	//					  strtmAdd,
	//					  strtmStart,
	//					  strtmFinished,
	//					  pTaskList[i].bti.hDownloader,
	//					  pTaskList[i].bti.wszGame_Name,
	//					  pTaskList[i].bti.wszDirectoryName,
	//					  wszIdxPathBuffer,
	//					  wszDirectoryBuffer,
	//					  wszCacheDirectoryBuffer,
	//					  pTaskList[i].bti.wszHash,
	//					  wszErrorInfoEx,
	//					  pTaskList[i].bti.tsDirState,
	//					  pTaskList[i].bti.iChangePieces,
	//					  pTaskList[i].bti.pChangePiecesArray,
	//					  wszWorkStatusBuffer,
	//					  pTaskList[i].bti.dwWorkImage,
	//					  I64SurplusSize,
	//					  dwSurplusTime);
	//		strData += strJson;
	//		strData += _T(",");
	//		Sleep(1);
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseEx((byte**)&pTaskList);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_TASKS_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50036命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50036命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		TCHAR	wszCruuentProgress[36] = { 0 };
		TCHAR	wszFileSize[64] = { 0 };
		TCHAR	wszSpeed[32] = { 0 };

		OutIni.ReadFromINI(_T("DL_DOWNLOADER_INFO"),i,_T("downloader_currentTaskProgress"),wszCruuentProgress,36,_T(""));
		float	fCurrentProgress = _wtof(wszCruuentProgress);

		OutIni.ReadFromINI(_T("DL_DOWNLOADER_INFO"),i,_T("downloader_totalFileSizeExcludePadding"),wszFileSize,64,_T(""));
		INT64 i64SizeFile = _wtoi64(wszFileSize);

		OutIni.ReadFromINI(_T("DL_DOWNLOADER_INFO"),i,_T("downloader_downloadSpeed"),wszSpeed,36,_T(""));
		DWORD	dwSpeed = _wtol(wszSpeed);

		float f = (100.00 - fCurrentProgress) / 100.00;
		INT64	I64SurplusSize = f * i64SizeFile;
		DWORD	dwSurplusTime = 0;
		if (dwSpeed > 0)
		{
			dwSurplusTime = I64SurplusSize / dwSpeed;
		}
		OutIni.Write2INI(_T("TASK_INFO"),i,_T("SurplusSize"),I64SurplusSize);
		OutIni.Write2INI(_T("TASK_INFO"),i,_T("dwSurplusTime"),dwSurplusTime);

		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("TASK_INFO"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::TaskGetTrackerInfo(CString strJson, CString& strResult)
{
//	DWORD	dwTaskId = _ttol(strJson);
//	PACK_TRACKER_INFO_ENTRY	TrackerInfo;
//// 	TrackerInfo.cbSize = sizeof(PACK_TRACKER_INFO_ENTRY);
//// 	TrackerInfo.dwFlags = m_fnbtcGetFlags(1);
//
//	int nErrorRet = m_fnbtcTaskGetTrackerInfo(dwTaskId,&TrackerInfo);
//	if (nErrorRet != SCMD_OK)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,"50037号命令。错误码：%d",nErrorRet);
//		strResult.Format(_T("%d"),nErrorRet);
//		return -1;
//	}
//	if (TrackerInfo.cbSize != sizeof(PACK_TRACKER_INFO_ENTRY))
//	{
//		WRITE_LOG(LOG_LEVEL_WARN,"%s","50037号命令。需要更新");
//	}
//	m_JsonEx.ToJsonEx(_T("PACK_TRACKER_INFO_ENTRY"),&TrackerInfo,strResult);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50037命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_TASK_TRACKER_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50037命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("PACK_TRACKER_INFO_ENTRY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50037号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::TaskGetPeerInfo(CString	strJson, CString &strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//PACK_PEER_INFO_ENTRY*	pPeerInfo = NULL;
	//int nCount;

	//int nErrorRet = m_fnbtcTaskGetPeerInfo(dwTaskId,&pPeerInfo,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50038号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("50038号命令没有数据或者错误."));
	//	return 0;
	//}
	//if (pPeerInfo->cbSize != sizeof(PACK_PEER_INFO_ENTRY))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50038号命令需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("PACK_PEER_INFO_ENTRY"),&pPeerInfo[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseEx((byte**)&pPeerInfo);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50038命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_TASK_PEER_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50038命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50038命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("PACK_PEER_INFO_ENTRY"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);

	return 1;
}

int		CBt::TaskAddDownload(CString strJson, CString& strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskAddDownload(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50039号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50039命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_ADD_DOWNLOAD,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50039命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskSSDDownload(CString strJson, CString& strResult)
{
	//DWORD	dwGameId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskSSDDownload(dwGameId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50040号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50040命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_SSD_DOWNLOAD,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50040命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskPropertyDownload(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("SET_GAME_SIMPLE_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}

	//SET_GAME_SIMPLE_PROPERTY*	pGameSimple = (SET_GAME_SIMPLE_PROPERTY*)lpStData;
	//pGameSimple->cbSize = sizeof(SET_GAME_SIMPLE_PROPERTY);
	//pGameSimple->dwFlags = m_fnbtcGetFlags(7);

	//int nErrorRet = m_fnbtcTaskPropertyDownload(pGameSimple);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50041号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("SET_GAME_SIMPLE_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50041命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_PROPERTY_DOWNLOAD,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50041命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskAddSeed(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("TASK_SEED_DATA"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//TASK_SEED_DATA*	pSeedData = (TASK_SEED_DATA*)lpStData;
	//pSeedData->cbSize = sizeof(TASK_SEED_DATA);
	//pSeedData->dwFlags = m_fnbtcGetFlags(4);

	//int nErrorRet = m_fnbtcTaskAddSeed(pSeedData);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50042号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("TASK_SEED_DATA"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50042命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_ADD_SEED,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50042命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}
int		CBt::TaskAddSeedSource(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("ADD_SEED_SOURCE"), &lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//ADD_SEED_SOURCE*	pAddSeed = (ADD_SEED_SOURCE*)lpStData;
	//pAddSeed->cbSize = sizeof(ADD_SEED_SOURCE);
	//pAddSeed->dwFlags = m_fnbtcGetFlags(3);

	//int nErrorRet = m_fnbtcTaskAddSeedSource(pAddSeed);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50043号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("ADD_SEED_SOURCE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50043命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_ADD_SEED_SOURCE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50043命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskStart(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskStart(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50044号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50044命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_START,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50044命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskStop(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskStop(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50045号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50045命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_STOP,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50045命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskCheck(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskCheck(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50046号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50046命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_CHECK,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50046命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskRemove(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskRemove(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50047号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50047命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_REMOVE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50047命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskTop(CString strJson, CString& strResult)
{
// 	DWORD	dwTaskId = _ttol(strJson);
// 	int nErrorRet = m_fnbtcTaskTop(dwTaskId);
// 	if (nErrorRet != SCMD_OK)
// 	{
// 		WRITE_LOG(LOG_LEVEL_ERROR,"50048号命令。错误码：%d",nErrorRet);
// 		strResult.Format(_T("%d"),nErrorRet);
// 		return -1;
// 	}
// 	strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50048命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_TOP,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50048命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskUp(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskTop(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50049号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50049命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_UP,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50049命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskDown(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskDown(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50050号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50050命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_DOWN,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50050命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskLimitSpeed(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskLimitSpeed(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50051号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50051命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_LIMIT_SPEED,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50051命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskSort(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskSort(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50052号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50052命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_SORT,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50052命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::TaskRefreshTracker(CString strJson, CString& strResult)
{
	//DWORD	dwTaskId = _ttol(strJson);
	//int nErrorRet = m_fnbtcTaskRefreshTracker(dwTaskId);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50053号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50053命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_TASK_REFRESH_TRACKER,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50053命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::InsertGroup(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("BT_GROUP_NAME"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//BT_GROUP_NAME*	pGroupName = (BT_GROUP_NAME*)lpStData;
	//int nErrorRet = m_fnbtcInsertGroup(pGroupName);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50054号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_GROUP_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50054命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_INSERT_GROUP,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50054命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::ModifyGroup(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("MODIFY_GROUP_NAME"), &lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//MODIFY_GROUP_NAME*	pGroupName = (MODIFY_GROUP_NAME*)lpStData;
	//int nErrorRet = m_fnbtcModifyGroup(pGroupName);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50055号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("MODIFY_GROUP_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50055命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_MODIFY_GROUP,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50055命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::DeleteGroup(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("GROUP_NAME"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//BT_GROUP_NAME*	pGroupName = (BT_GROUP_NAME*)lpStData;
	//int nErrorRet = m_fnbtcDeleteGroup(pGroupName);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50056号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_GROUP_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50056命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_DELETE_GROUP,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50056命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetGroupInfo(CString& strResult)
{
	//GroupInfo	Group = { 0 };
	//int	nErrorRet = m_fnbtcGetGroupInfo(&Group);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50057号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("GroupInfo"),&Group,strResult);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_GROUP_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50057命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("GroupInfo"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50057号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetWorkstationInfo(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("GROUP_NAME"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//BT_GROUP_NAME	GroupName;
	//memcpy(&GroupName,lpStData,sizeof(BT_GROUP_NAME));
	//T_WorkstationInfo*	pGroupWks = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetWorkstationInfo(&pGroupWks,GroupName,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50058号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pGroupWks->cbSize != sizeof(T_WorkstationInfo))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50058号命令需要更新");
	//}

	//CAppMain*	pAppMain = CAppMain::GetAppMain();
	//GetWksCfg	fnGetWorkstationList = (GetWksCfg)pAppMain->m_Mzd.GetWorkstationAddress();
	//tagWkstationEx*	pWks = NULL;
	//DWORD	dwCount;
	//int nErrorRetMzd = fnGetWorkstationList(dwCount,&pWks);
	//if (nErrorRetMzd)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50058中获取MZD工作站失败，错误码：%d",nErrorRetMzd);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pWks->cbSize != sizeof(tagWkstationEx))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40012命令需要更新！");
	//}
	//int nFlagCount = 0;
	//CString	strData;
	//strData += _T("{\"Array\":[");


	//for (int i = 0; i < nCount; i++)
	//{
	//	for (int ii = 0; ii < dwCount; ii++)
	//	{
	//		if (pGroupWks[i].dwID == pWks[ii].wksNumber)
	//		{
	//			CString	strJson;
	//			pAppMain->m_Mzd.m_JsonEx.ToJsonEx(_T("tagWkstationEx"),&pWks[ii],strJson);
	//			strData += strJson;
	//			strData +=_T(",");
	//			nFlagCount++;
	//		}
	//	}
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");

	//if (nFlagCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}

	//MzdAgentFree	MzdFree = (MzdAgentFree)pAppMain->m_Mzd.GetMzdReleaseAddress();
	//MzdFree(pWks);

	//m_fnbtcReleaseWorkstationInfo(&pGroupWks);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_GROUP_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50058命令转INI失败");
		return -1;
	}

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	char* pOutData = NULL;
	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_GROUP_WORKSTATION,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50058命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50058命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return -1;
	}

	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	strWksJson;
	int nWksError = pAppMain->m_Mzd.Mzd_GetWksCfg(strWksJson);
	if (nWksError != 1)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50058命令获取工作站数据错误");
		strResult.Format(_T("%s"),strWksJson);
		return -1;
	}
	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strWksJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strWksJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);
	if (!Object.parse(pDocument,Root))
	{
		delete []pDocument;
		return -1;
	}
	delete []pDocument;

	int nWksCount = Root["Array"].size();

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		DWORD	dwGroupBt;
		OutIni.ReadFromINI(_T("T_WorkstationInfo"),i,_T("dwID"),dwGroupBt,-1);
		for (int x = 0; x < nWksCount; x++)
		{
			char*	pWksId = (char*)Root["Array"][x]["wksNumber"].asCString();
			DWORD	dwWksId = atol(pWksId);
			if (dwGroupBt == dwWksId)
			{
				Json::FastWriter	JsonWriter;
				std::string stdJsonstr = JsonWriter.write(Root["Array"][x]);
				CString	strWksData(stdJsonstr.c_str());
				strData += strWksData;
				strData +=_T(",");
			}
		}
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return	1;
}

int		CBt::GetServerInfo(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("GROUP_NAME"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//BT_GROUP_NAME	GroupName;
	//memcpy(&GroupName,lpStData,sizeof(BT_GROUP_NAME));
	//T_ServerInfo*	pServerInfo = NULL;
	//int nCount;
	//int nErrorRet = m_fnbtcGetServerInfo(&pServerInfo,GroupName,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50059号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("50059号命令没有数据或者错误."));
	//	return 0;
	//}
	//if (pServerInfo->cbSize != sizeof(T_ServerInfo))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50059号命令需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("T_ServerInfo"),&pServerInfo[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseServerInfo(&pServerInfo);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_GROUP_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50059命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;
	int		nCount;
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int nErrorRet = m_fnbtcCall(COMMAND_GET_GROUP_SERVER,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50059命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50059命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return -1;
	}

	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	strServerJson;
	int nServerError = pAppMain->m_Mzd.Mzd_GetSvrCfg(strServerJson);	//获取所有服务器消息
	if (nServerError != 1)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50059命令获取工作站数据错误");
		strResult.Format(_T("%s"),strServerJson);
		return -1;
	}

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strServerJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strServerJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);
	if (!Object.parse(pDocument,Root))
	{
		delete []pDocument;
		return -1;
	}
	delete []pDocument;

	int nServerCount = Root["Array"].size();

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		TCHAR	wszServerName[128] = { 0 };
		OutIni.ReadFromINI(_T("T_ServerInfo"),i,_T("wszName"),wszServerName,128,_T(""));
		for (int x = 0; x < nServerCount; x++)
		{
			TCHAR	wszGroupServerName[128] = { 0 };
			CChineseCode::AsciiToUnicode(wszGroupServerName,(char*)Root["Array"][x]["serverName"].asCString());
			if (lstrcmp(wszServerName,wszGroupServerName) == NULL)
			{
				Json::FastWriter	JsonWriter;
				std::string stdJsonstr = JsonWriter.write(Root["Array"][x]);
				CString	strWksData(stdJsonstr.c_str());
				strData += strWksData;
				strData +=_T(",");
			}
		}
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::DeleteWorkstation(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("COMPUTER_ID"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//COMPUTER_ID	Id;
	//memcpy(&Id,lpStData,sizeof(COMPUTER_ID));
	//int nErrorRet = m_fnbtcDeleteWorkstation(Id);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50060号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("COMPUTER_ID"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50060命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_DELETE_WORKSTATION,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50060命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::DeleteServer(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("COMPUTER_NAME"), &lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//COMPUTER_NAME	Name;
	//memcpy(&Name,lpStData,sizeof(COMPUTER_NAME));
	//int nErrorRet = m_fnbtcDeleteServer(Name);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50061号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("COMPUTER_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50061命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_DELETE_SERVER,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50061命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetWorkstationProperty(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("WORKSTATION_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//WORKSTATION_PROPERTY*	pGroupWks = (WORKSTATION_PROPERTY*)lpStData;
	//pGroupWks->cbSize = sizeof(WORKSTATION_PROPERTY);
	//pGroupWks->dwFlags = m_fnbtcGetFlags(5);

	//int nErrorRet = m_fnbtcGetWorkstationProperty(pGroupWks);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50062号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (pGroupWks->cbSize != sizeof(WORKSTATION_PROPERTY))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50061号命令需要更新");
	//}

	//m_JsonEx.ToJsonEx(_T("WORKSTATION_PROPERTY"),pGroupWks,strResult);
	//m_JsonEx.ToStructRelease(lpStData);


	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("COMPUTER_NAME"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50062命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_WORKSTATION_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50062命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("WORKSTATION_PROPERTY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50062号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetWorkstationProperty(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("WORKSTATION_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//WORKSTATION_PROPERTY*	pWks = (WORKSTATION_PROPERTY*)lpStData;
	//pWks->cbSize = sizeof(WORKSTATION_PROPERTY);
	//pWks->dwFlags = m_fnbtcGetFlags(5);

	//int nErrorRet = m_fnbtcSetWorkstationProperty(pWks);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50063号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("WORKSTATION_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50063命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SET_WORKSTATION_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50063命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetServerProperty(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("SERVER_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//SERVER_PROPERTY*	pServer = (SERVER_PROPERTY*)lpStData;
	//pServer->cbSize = sizeof(SERVER_PROPERTY);
	//pServer->dwFlags = m_fnbtcGetFlags(3);

	//int nErrorRet = m_fnbtcGetServerProperty(pServer);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50064号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (pServer->cbSize != sizeof(SERVER_PROPERTY))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"%s","50063号命令需要更新");
	//}
	//m_JsonEx.ToJsonEx(_T("SERVER_PROPERTY"),pServer,strResult);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("SERVER_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50064命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SERVER_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50064命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("SERVER_PROPERTY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50064号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetServerProperty(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("SERVER_PROPERTY"),&lpStData))
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//SERVER_PROPERTY*	pServer = (SERVER_PROPERTY*)lpStData;
	//pServer->cbSize = sizeof(SERVER_PROPERTY);
	//pServer->dwFlags = m_fnbtcGetFlags(3);

	//int nErrorRet = m_fnbtcSetServerProperty(pServer);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50065号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("SERVER_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50065命令转INI失败");
		return -1;
	}

	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SET_SERVER_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50065命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetDiskInfo(CString& strResult)
{
	//DISK_INFO*	pDisk = NULL;
	//int		nCount;

	//int nErrorRet = m_fnbtcGetDiskInfo(&pDisk,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50066号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == NULL)
	//{
	//	strResult.Format(_T("50065号命令没有数据或者错误."));
	//	return 0;
	//}
	//if (pDisk->cbSize != sizeof(DISK_INFO))
	//{
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("DISK_INFO"),&pDisk[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseDiskInfo(&pDisk);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_DISK_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50066命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50066命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("DISK_INFO"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetFileDirectoryInfo(CString strJson, CString& strResult)
{
	//FILE_DIRECTORY_INFO*	pFileInfo = NULL;
	//int		nCount;

	//int nErrorRet = m_fnbtcGetFileDirectoryInfo(strJson.GetBuffer(),&pFileInfo,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50067号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == NULL)
	//{
	//	strResult.Format(_T("50066号命令没有数据或者错误."));
	//	return 0;
	//}
	//if (pFileInfo->cbSize != sizeof(FILE_DIRECTORY_INFO))
	//{
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("FILE_DIRECTORY_INFO"),&pFileInfo[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseDirectoryInfo(&pFileInfo);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_PATH_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50067命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_FILE_DIRECTORY_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50067命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50067命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("FILE_DIRECTORY_INFO"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetFileDirectoryProperty(CString strJson, CString& strResult)
{
//	FILE_DIRECTORY_PROPERTY	FileDirectory;
////	FileDirectory.cbSize = sizeof(FILE_DIRECTORY_PROPERTY);
////	FileDirectory.dwFlags = m_fnbtcGetFlags(4);
//
//	int nErrorRet = m_fnbtcGetFileDirectoryProperty(strJson.GetBuffer(),&FileDirectory);
//	if (nErrorRet != SCMD_OK)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,"50068号命令。错误码：%d",nErrorRet);
//		strResult.Format(_T("%d"),nErrorRet);
//		return -1;
//	}
//	if (FileDirectory.cbSize != sizeof(FILE_DIRECTORY_PROPERTY))
//	{
//	}
//	m_JsonEx.ToJsonEx(_T("FILE_DIRECTORY_PROPERTY"),&FileDirectory,strResult);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_PATH_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50068命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_FILE_DIRECTORY_PROPERTY,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50068命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("FILE_DIRECTORY_PROPERTY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50068号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetDirectorySize(CString strJson, CString& strResult)
{
	//INT64	I64DiskSize;

	//int nErrorRet = m_fnbtcGetDirectorySize(strJson.GetBuffer(),&I64DiskSize);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50069号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("%I64d"),I64DiskSize);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_PATH_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50069命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_DIRECTORY_SIZE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50069命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_INT64_VALUE"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50069号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetParentClassInfo(CString strJson, CString& strResult)
{
	//int nCount = 0;
	//T_ClassInfo*	pClassInfo = NULL;
	//if (strJson.IsEmpty())
	//{
	//	int nErrorRet = m_fnbtcSetParentClassInfo(&pClassInfo,&nCount);
	//	if (nErrorRet != SCMD_OK)
	//	{
	//		WRITE_LOG(LOG_LEVEL_ERROR,"50070号命令。错误码：%d",nErrorRet);
	//		strResult.Format(_T("%d"),nErrorRet);
	//		return -1;
	//	}
	//	strResult.Format(_T("0"));
	//	return 1;
	//}
	//PVOID	lpStData = NULL;
	//nCount = m_JsonEx.ToStructCount(strJson,_T("ClassInfo"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//pClassInfo = (T_ClassInfo*)lpStData;
	//for (int i = 0; i < nCount; i++)
	//{
	//	pClassInfo[i].cbSize = sizeof(T_ClassInfo);
	//	pClassInfo[i].dwFlags = m_fnbtcGetFlags(5);
	//}
	//int nErrorRet = m_fnbtcSetParentClassInfo(&pClassInfo,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50070号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json无法识别 ：%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	int nCount = Root["Array"].size();

	if (nCount == 0)
	{
		int nErrorRet = m_fnbtcCall(COMMAND_SET_PARENT_CLASS_INFO,NULL,0,NULL,&nCount,NULL);
		if (nErrorRet != 70000)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"50070命令失败。 错误码：%d",nErrorRet);
			strResult.Format(_T("%d"),nErrorRet);
			return -1;
		}
		strResult.Format(_T("0"));
		return 1;
	}
	MZD_INI	InIni;
	for (int i = 0; i < nCount; i++)
	{
		int nCountNumber;
		m_JsonEx.ToIniByJsonEx(Root["Array"][i],_T("T_ClassInfo"),nCountNumber,&InIni);
	}
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int nErrorRet = m_fnbtcCall(COMMAND_SET_PARENT_CLASS_INFO,strMessageData.c_str(),strMessageData.size(),NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50070命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::SetSubClassInfo(CString strJson, CString& strResult)
{
	//int nCount = 0;
	//T_ClassInfo*	pClassInfo = NULL;
	//if (strJson.IsEmpty())
	//{
	//	int nErrorRet = m_fnbtcSetSubClassInfo(&pClassInfo,&nCount);
	//	if (nErrorRet != SCMD_OK)
	//	{
	//		WRITE_LOG(LOG_LEVEL_ERROR,"50071号命令。错误码：%d",nErrorRet);
	//		strResult.Format(_T("%d"),nErrorRet);
	//		return -1;
	//	}
	//	strResult.Format(_T("0"));
	//	return 1;
	//}

	//PVOID	lpStData = NULL;
	//nCount = m_JsonEx.ToStructCount(strJson,_T("ClassInfo"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//pClassInfo = (T_ClassInfo*)lpStData;
	//for (int i = 0; i < nCount; i++)
	//{
	//	pClassInfo[i].cbSize = sizeof(T_ClassInfo);
	//	pClassInfo[i].dwFlags = m_fnbtcGetFlags(5);
	//}
	//int nErrorRet = m_fnbtcSetSubClassInfo(&pClassInfo,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50071号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json无法识别 ：%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	int nCount = Root["Array"].size();

	if (nCount == 0)
	{
		int nErrorRet = m_fnbtcCall(COMMAND_SET_SUB_CLASS_INFO,NULL,0,NULL,&nCount,NULL);
		if (nErrorRet != 70000)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"50071命令失败。 错误码：%d",nErrorRet);
			strResult.Format(_T("%d"),nErrorRet);
			return -1;
		}
		strResult.Format(_T("0"));
		return 1;
	}
	MZD_INI	InIni;
	for (int i = 0; i < nCount; i++)
	{
		int nCountNumber;
		m_JsonEx.ToIniByJsonEx(Root["Array"][i],_T("T_ClassInfo"),nCountNumber,&InIni);
	}
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);
	int nErrorRet = m_fnbtcCall(COMMAND_SET_SUB_CLASS_INFO,strMessageData.c_str(),strMessageData.size(),NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50071命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::SetMovieInfo(CString strJson, CString& strResult)
{
	//T_Movie*	pMovie = NULL;
	//int nCount = 0;
	//if (strJson.IsEmpty())
	//{
	//	int nErrorRet = m_fnbtcSetMovieInfo(&pMovie,&nCount);
	//	if (nErrorRet != SCMD_OK)
	//	{
	//		WRITE_LOG(LOG_LEVEL_ERROR,"50072号命令。错误码：%d",nErrorRet);
	//		strResult.Format(_T("%d"),nErrorRet);
	//		return -1;
	//	}
	//	strResult.Format(_T("0"));
	//	return 1;
	//}
	//PVOID	lpStData = NULL;
	//nCount = m_JsonEx.ToStructCount(strJson,_T("Movie"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//pMovie = (T_Movie*)lpStData;
	//for (int i = 0; i < nCount; i++)
	//{
	//	pMovie[i].cbSize = sizeof(T_Movie);
	//	pMovie[i].dwFlags = m_fnbtcGetFlags(8);
	//}
	//int nErrorRet = m_fnbtcSetMovieInfo(&pMovie,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50072号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json无法识别 ：%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	int nCount = Root["Array"].size();

	if (nCount == 0)
	{
		int nErrorRet = m_fnbtcCall(COMMAND_SET_MOVIE_INFO,NULL,0,NULL,&nCount,NULL);
		if (nErrorRet != 70000)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"50072命令失败。 错误码：%d",nErrorRet);
			strResult.Format(_T("%d"),nErrorRet);
			return -1;
		}
		strResult.Format(_T("0"));
		return 1;
	}
	MZD_INI	InIni;
	for (int i = 0; i < nCount; i++)
	{
		int nCountNumber;
		m_JsonEx.ToIniByJsonEx(Root["Array"][i],_T("T_Movie"),nCountNumber,&InIni);
	}
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int nErrorRet = m_fnbtcCall(COMMAND_SET_MOVIE_INFO,strMessageData.c_str(),strMessageData.size(),NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50072命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::SetOnlineInfo(CString strJson, CString& strResult)
{
	//int nCount = 0;
	//T_Online*	pOnline = NULL;
	//if (strJson.IsEmpty())
	//{
	//	int nErrorRet = m_fnbtcSetOnlineInfo(&pOnline,&nCount);
	//	if (nErrorRet != SCMD_OK)
	//	{
	//		WRITE_LOG(LOG_LEVEL_ERROR,"50073号命令。错误码：%d",nErrorRet);
	//		strResult.Format(_T("%d"),nErrorRet);
	//		return -1;
	//	}
	//	strResult.Format(_T("0"));
	//	return 1;
	//}

	//PVOID	lpStData = NULL;
	//nCount = m_JsonEx.ToStructCount(strJson,_T("Online"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//pOnline = (T_Online*)lpStData;
	//for (int i = 0; i < nCount; i++)
	//{
	//	pOnline[i].cbSize = sizeof(T_Online);
	//	pOnline[i].dwFlags = m_fnbtcGetFlags(5);
	//}
	//int nErrorRet = m_fnbtcSetOnlineInfo(&pOnline,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50073号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json无法识别 ：%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	int nCount = Root["Array"].size();

	if (nCount == 0)
	{
		int nErrorRet = m_fnbtcCall(COMMAND_SET_ONLINE_INFO,NULL,0,NULL,&nCount,NULL);
		if (nErrorRet != 70000)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"50073命令失败。 错误码：%d",nErrorRet);
			strResult.Format(_T("%d"),nErrorRet);
			return -1;
		}
		strResult.Format(_T("0"));
		return 1;
	}
	MZD_INI	InIni;
	for (int i = 0; i < nCount; i++)
	{
		int nCountNumber;
		m_JsonEx.ToIniByJsonEx(Root["Array"][i],_T("T_Online"),nCountNumber,&InIni);
	}
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);
	int nErrorRet = m_fnbtcCall(COMMAND_SET_ONLINE_INFO,strMessageData.c_str(),strMessageData.size(),NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50073命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::SetPlayerListInfo(CString strJson, CString& strResult)
{
	//int nCount = 0;
	//T_PlayerList*	pPlayerList = NULL;
	//if (strJson.IsEmpty())
	//{
	//	int nErrorRet = m_fnbtcSetPlayerListInfo(&pPlayerList,&nCount);
	//	if (nErrorRet != SCMD_OK)
	//	{
	//		WRITE_LOG(LOG_LEVEL_ERROR,"50074号命令。错误码：%d",nErrorRet);
	//		strResult.Format(_T("%d"),nErrorRet);
	//		return -1;
	//	}
	//	strResult.Format(_T("0"));
	//	return 1;
	//}

	//PVOID	lpStData = NULL;
	//nCount = m_JsonEx.ToStructCount(strJson,_T("PlayerList"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//pPlayerList = (T_PlayerList*)lpStData;
	//for (int i = 0; i < nCount; i++)
	//{
	//	pPlayerList[i].cbSize = sizeof(T_PlayerList);
	//	pPlayerList[i].dwFlags = m_fnbtcGetFlags(8);
	//}
	//int nErrorRet = m_fnbtcSetPlayerListInfo(&pPlayerList,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50074号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json无法识别 ：%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	int nCount = Root["Array"].size();

	if (nCount == 0)
	{
		int nErrorRet = m_fnbtcCall(COMMAND_SET_PLAYER_LIST_INFO,NULL,0,NULL,&nCount,NULL);
		if (nErrorRet != 70000)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"50074命令失败。 错误码：%d",nErrorRet);
			strResult.Format(_T("%d"),nErrorRet);
			return -1;
		}
		strResult.Format(_T("0"));
		return 1;
	}
	MZD_INI	InIni;
	for (int i = 0; i < nCount; i++)
	{
		int nCountNumber;
		m_JsonEx.ToIniByJsonEx(Root["Array"][i],_T("T_PlayerList"),nCountNumber,&InIni);
	}
	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int nErrorRet = m_fnbtcCall(COMMAND_SET_PLAYER_LIST_INFO,strMessageData.c_str(),strMessageData.size(),NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50074命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::StartSearch(CString	strJson, CString& strResult)
{
	//if (m_fnbtcStartSearch == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//int nErrorRet = m_fnbtcStartSearch(strJson.GetBuffer());
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50075号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_PATH_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50069命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_START_SEARCH,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50075命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 0;
}

int		CBt::StopSearch(CString& strResult)
{
	//int nErrorRet = m_fnbtcStopSearch();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50076号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_END_SEARCH,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50076命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 0;
}

int		CBt::GetLocate(CString strJson, CString& strResult)
{
	//if (m_fnbtcGetLocate == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//SEARCH_INFO*	pSearchInfo = NULL;
	//int nCount = 0;
	//int nErrorRet = m_fnbtcGetLocate(&pSearchInfo,&nCount);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50077号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pSearchInfo->cbSize != sizeof(SEARCH_INFO))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"%s","需要更新");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("SEARCH_INFO"),&pSearchInfo[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnbtcReleaseEx((byte**)&pSearchInfo);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_GET_LOCATE,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50077命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	if (nCount == 0)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50077命令获取数据为空");
		strResult.Format(_T("%d"),5007);
		return 1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	CString	strData;
	strData += _T("{\"Array\":[");
	for (int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("SEARCH_INFO"),i,strJson);
		strData += strJson;
		strData += _T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetLocateStatus(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//int nCount = m_JsonEx.ToStruct(strJson,_T("GET_GAME_LOCATE_STATUS_REQUEST"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//GET_GAME_LOCATE_STATUS_REQUEST*	pGameStatusQuest = (GET_GAME_LOCATE_STATUS_REQUEST*)lpStData;

	//GET_GAME_LOCATE_STATUS_REPLY	GameStatus = { 0 };

	//int nErrorRet = m_fnbtcGetLocateStatus(pGameStatusQuest,&GameStatus);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50078号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("GET_GAME_LOCATE_STATUS_REPLY"),&GameStatus,strResult);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("GET_GAME_LOCATE_STATUS_REQUEST"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50078命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_GET_LOCATE_STATUS,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50078命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("GET_GAME_LOCATE_STATUS_REPLY"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50078号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::SetLocate(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//int nCount = m_JsonEx.ToStruct(strJson,_T("SET_GAME_LOCATE_INFO"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//SET_GAME_LOCATE_INFO*	pGameInfo = (SET_GAME_LOCATE_INFO*)lpStData;
	//int nErrorRet = m_fnbtcSetLocate(pGameInfo);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50079号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("SET_GAME_LOCATE_INFO"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50079命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_SET_LOCATE,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50079命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetSingleGameInfo(CString strJson, CString& strResult)
{
	//RESOURCE_INFO	BtResource;
	//BtResource.giex.dwGame_Id = _ttoi(strJson);

	//int nErrorRet = m_fnbtcGetSingleGameInfo(&BtResource);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50080号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("RESOURCE_INFO"),&BtResource,strResult);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_DWORD_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50080命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SINGLE_GAME_INFO,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50080命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	DWORD	dwColor;
	OutIni.ReadFromINI(_T("T_GamesInfoEx"),0,_T("giex_dwWorkColor"),dwColor,0);
	DWORD	NewColor = GetRGB(dwColor);
	TCHAR	wszColor[32] = { 0 };
	wsprintf(wszColor,_T("%06X"),NewColor);
	OutIni.Write2INI(_T("T_GamesInfoEx"),0,_T("giex_dwWorkColor"),wszColor);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("RESOURCE_INFO"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50080号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetLimitTimePeriodInfo(CString& strResult)
{
	//if (m_fnbtcGetLimitTimePeriodInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//LIMIT_TIME_PERIOD_INFO LimitTime = { 0 };

	//int nErrorRet = m_fnbtcGetLimitTimePeriodInfo(&LimitTime);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50081号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("LIMIT_TIME_PERIOD_INFO"),&LimitTime,strResult);

	char* pOutData = NULL;

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_LIMIT_TIME_PERIOD_INFO,NULL,0,&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50081命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("LIMIT_TIME_PERIOD_INFO"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50081号命令。错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::ClearBtRegInfo(CString& strResult)
{
	//if (m_fnbtcClearBtRegInfo == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}

	//int nErrorRet = m_fnbtcClearBtRegInfo();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50082号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	int	nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CLEAR_BT_REG_INFO,NULL,0,NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50082命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::CoverLocate(CString& strResult)
{
	//if (m_fnbtcCoverLocate == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//int nErrorRet = m_fnbtcCoverLocate();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50083号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));


	int	nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GAME_COVER_LOCATE,NULL,0,NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50083命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::AddCustomWeb(CString strJson, CString& strResult)
{
	//if (m_fnbtcAddCustomWeb == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//PVOID	lpStData = NULL;
	//int nCount = m_JsonEx.ToStruct(strJson,_T("RESOURCE_PROPERTY"),&lpStData);
	//if (!nCount)
	//{
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//RESOURCE_PROPERTY*	pResource = (RESOURCE_PROPERTY*)lpStData;
	//pResource->cbSize = sizeof(RESOURCE_PROPERTY);
	//pResource->dwFlags = BTS_FLAGS_32[2];

	//int nErrorRet = m_fnbtcAddCustomWeb(pResource);
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50084号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("RESOURCE_PROPERTY"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50084命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);

	int		nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_CUSTOM_WEB_ADD,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50084命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::SyncMzdWorkstation(CString& strResult)
{
	//if (m_fnbtcSyncMzdWorkstation == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//int nErrorRet = m_fnbtcSyncMzdWorkstation();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50085号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	int	nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SYNC_MZD_WORKSTATION,NULL,0,NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50085命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::SyncMzdServer(CString& strResult)
{
	//if (m_fnbtcSyncMzdServer == NULL)
	//{
	//	strResult.Format(_T("5001"));
	//	return -1;
	//}
	//int nErrorRet = m_fnbtcSyncMzdServer();
	//if (nErrorRet != SCMD_OK)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"50086号命令。错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	int	nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_SYNC_MZD_SERVER,NULL,0,NULL,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50086命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CBt::GetSingleParentClassName(CString strJson, CString &strResult)
{
	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_PATH_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50087命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);
	int	nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SINGLE_PARENT_CLASS_NAME,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50087命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);
	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_PATH_VALUE"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50087号命令传出数据不正确");
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

int		CBt::GetSingleSubClassName(CString strJson, CString &strResult)
{
	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("BT_PATH_VALUE"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50088命令转INI失败");
		return -1;
	}
	char* pOutData = NULL;

	std::string	strMessageData;
	InIni.Format2Str(strMessageData);
	int	nCount;
	int nErrorRet = m_fnbtcCall(COMMAND_GET_SINGLE_SUB_CLASS_NAME,strMessageData.c_str(),strMessageData.size(),&pOutData,&nCount,NULL);
	if (nErrorRet != 70000)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50088命令失败。 错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pOutData);
	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("BT_PATH_VALUE"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"50088号命令传出数据不正确");
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	m_fnbtcReleaseEx(pOutData);
	return 1;
}

//
//CString	CBt::SetClass_Parent(T_ClassInfo*	pClassInfo, int nCount)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	m_fnbtcSetParentClassInfo()
//
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString	CBt::SetClass_Sub(CPtrArray& SubArray)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(T_ClassInfo) * SubArray.GetCount();
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pbTemp = pSendBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_SET_SUB_CLASS_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = SubArray.GetCount();
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	memcpy(pbTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
//	int iCount = SubArray.GetCount();
//	for (int i = 0; i < iCount; i++)
//	{
//		T_ClassInfo*	pClassInfo = (T_ClassInfo*)SubArray.GetAt(i);
//		memcpy(pbTemp,pClassInfo,sizeof(T_ClassInfo));
//		pbTemp += sizeof(T_ClassInfo);
//		delete []pClassInfo;
//	}
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp失败"));
//		return StrResult;
//	}
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp失败"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp失败"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp"));
//	return StrResult;
//}
//
//int		CBt::GetClass_Parent(CStringArray& ParentArray,int nFlag)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(int);
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pbTemp = pSendBuffer;
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_GET_PARENT_CLASS_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	memcpy(pbTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pbTemp,&nFlag,sizeof(int));
//
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	T_ClassInfo	Bt_ClassInfo;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		iSocketRet = Receive(&Bt_ClassInfo,sizeof(T_ClassInfo));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			return -1;
//		}
//		CString	StrParentData;
//		StrParentData.Format(_T("['%s','%s','%ld','%ld','%s'],"),
//			Bt_ClassInfo.wszID,
//			Bt_ClassInfo.wszName,
//			Bt_ClassInfo.dwShowIndex,
//			Bt_ClassInfo.dwShow,
//			Bt_ClassInfo.wszTypeId);
//		ParentArray.Add(StrParentData);
//	}
//	return ParentArray.GetCount();
//}
//
//int		CBt::GetClass_Sub(CStringArray& SubArray)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_SUB_CLASS_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 0;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	DWORD	dwMemory = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[dwMemory];
//	byte*	pbTemp = pRecvBuffer;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		iSocketRet = Receive(pbTemp,sizeof(T_ClassInfo));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			return -1;
//		}
//		pbTemp += sizeof(T_ClassInfo);
//	}
//	T_ClassInfo*	pBt_ClassInfo = (T_ClassInfo*)pRecvBuffer;
//	for (int iCount = 0; iCount < Bt_Reply_Head.dwCount; iCount++)
//	{
//		CString	StrParentData;
//		StrParentData.Format(_T("['%s','%s','%ld','%ld','%s'],"),
//			pBt_ClassInfo->wszID,
//			pBt_ClassInfo->wszName,
//			pBt_ClassInfo->dwShowIndex,
//			pBt_ClassInfo->dwShow,
//			pBt_ClassInfo->wszTypeId);
//		pBt_ClassInfo++;
//		SubArray.Add(StrParentData);
//	}
//	delete []pRecvBuffer;
//	return 1;
//}
//
//int		CBt::LoadBtConfig(char* pBtConfigData,CONFIG_INFO* pConfigInfo)
//{
//	int iSeparate = strlen("&nbsp");
//	char*	pPos = NULL;
//	char	szBuffer[260] = { 0 };
//	TCHAR	wszBuffer[260] = { 0 };
//	pPos = strstr(pBtConfigData,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//		pConfigInfo->bUPNP = atoi(szBuffer);  //1
//		pBtConfigData += strlen(szBuffer);
//		pBtConfigData += iSeparate;
//		memset(szBuffer,0,260);
//		pPos = strstr(pBtConfigData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//			pConfigInfo->bLimitLocalBandwidth = atoi(szBuffer);//2
//			pBtConfigData += strlen(szBuffer);
//			pBtConfigData += iSeparate;
//			memset(szBuffer,0,260);
//			pPos = strstr(pBtConfigData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//				pConfigInfo->dwMaxActiveTask = atol(szBuffer);//3
//				pBtConfigData += strlen(szBuffer);
//				pBtConfigData += iSeparate;
//				memset(szBuffer,0,260);
//				pPos = strstr(pBtConfigData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//					pConfigInfo->dwMaxDownloadTask = atol(szBuffer);//4
//					pBtConfigData += strlen(szBuffer);
//					pBtConfigData += iSeparate;
//					memset(szBuffer,0,260);
//					pPos = strstr(pBtConfigData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//						pConfigInfo->dwMaxDownloadSpeed = atol(szBuffer);//5
//						pBtConfigData += strlen(szBuffer);
//						pBtConfigData += iSeparate;
//						memset(szBuffer,0,260);
//						pPos = strstr(pBtConfigData,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//							pConfigInfo->dwMaxUploadSpeed = atol(szBuffer);//6
//							pBtConfigData += strlen(szBuffer);
//							pBtConfigData += iSeparate;
//							memset(szBuffer,0,260);
//							pPos = strstr(pBtConfigData,"&nbsp");
//							if (pPos)
//							{
//								memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//								pConfigInfo->dwHoldDiskSpace = atol(szBuffer);//7
//								pBtConfigData += strlen(szBuffer);
//								pBtConfigData += iSeparate;
//								memset(szBuffer,0,260);
//								pPos = strstr(pBtConfigData,"&nbsp");
//								if (pPos)
//								{
//									memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//									pConfigInfo->dwUserNetLineType = atol(szBuffer);//8
//									pBtConfigData += strlen(szBuffer);
//									pBtConfigData += iSeparate;
//									memset(szBuffer,0,260);
//									pPos = strstr(pBtConfigData,"&nbsp");
//									if (pPos)
//									{
//										memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//										pConfigInfo->dwPort = atol(szBuffer);//9
//										pBtConfigData += strlen(szBuffer);
//										pBtConfigData += iSeparate;
//										memset(szBuffer,0,260);
//										pPos = strstr(pBtConfigData,"&nbsp");
//										if (pPos)
//										{
//											memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//											pConfigInfo->dwRouterPort = atol(szBuffer);//10
//											pBtConfigData += strlen(szBuffer);
//											pBtConfigData += iSeparate;
//											memset(szBuffer,0,260);
//											pPos = strstr(pBtConfigData,"&nbsp");
//											if (pPos)
//											{
//												memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//												pConfigInfo->bNoManualToAuto = atoi(szBuffer);//11
//												pBtConfigData += strlen(szBuffer);
//												pBtConfigData += iSeparate;
//												memset(szBuffer,0,260);
//												pPos = strstr(pBtConfigData,"&nbsp");
//												if (pPos)
//												{
//													memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//													pConfigInfo->bAutoRemoveCompletedTask = atoi(szBuffer);//12
//													pBtConfigData += strlen(szBuffer);
//													pBtConfigData += iSeparate;
//													memset(szBuffer,0,260);
//													pPos = strstr(pBtConfigData,"&nbsp");
//													if (pPos)
//													{
//														memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//														pConfigInfo->bAutoRemoveSpeed = atoi(szBuffer);//13
//														pBtConfigData += strlen(szBuffer);
//														pBtConfigData += iSeparate;
//														memset(szBuffer,0,260);
//														pPos = strstr(pBtConfigData,"&nbsp");
//														if (pPos)
//														{
//															memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//															pConfigInfo->bAutoRemoveTime = atoi(szBuffer);//14
//															pBtConfigData += strlen(szBuffer);
//															pBtConfigData += iSeparate;
//															memset(szBuffer,0,260);
//															pPos = strstr(pBtConfigData,"&nbsp");
//															if (pPos)
//															{
//																memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																pConfigInfo->dwAutoRemoveSpeed = atoi(szBuffer);//15
//																pBtConfigData += strlen(szBuffer);
//																pBtConfigData += iSeparate;
//																memset(szBuffer,0,260);
//																pPos = strstr(pBtConfigData,"&nbsp");
//																if (pPos)
//																{
//																	memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																	pConfigInfo->dwAutoRemoveTime = atoi(szBuffer);//16
//																	pBtConfigData += strlen(szBuffer);
//																	pBtConfigData += iSeparate;
//																	memset(szBuffer,0,260);
//																	pPos = strstr(pBtConfigData,"&nbsp");
//																	if (pPos)
//																	{
//																		memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																		pConfigInfo->bAutoDeleteStopUpdate = atoi(szBuffer);//17
//																		pBtConfigData += strlen(szBuffer);
//																		pBtConfigData += iSeparate;
//																		memset(szBuffer,0,260);
//																		pPos = strstr(pBtConfigData,"&nbsp");
//																		if (pPos)
//																		{
//																			memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																			pConfigInfo->bAutoClearSpace = atoi(szBuffer);//18
//																			pBtConfigData += strlen(szBuffer);
//																			pBtConfigData += iSeparate;
//																			memset(szBuffer,0,260);
//																			pPos = strstr(pBtConfigData,"&nbsp");
//																			if (pPos)
//																			{
//																				memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																				pConfigInfo->bAutoAcceptNew = atoi(szBuffer);//19
//																				pBtConfigData += strlen(szBuffer);
//																				pBtConfigData += iSeparate;
//																				memset(szBuffer,0,260);
//																				pPos = strstr(pBtConfigData,"&nbsp");
//																				if (pPos)
//																				{
//																					memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																					pConfigInfo->bAutoAcceptNetGame = atoi(szBuffer);//20
//																					pBtConfigData += strlen(szBuffer);
//																					pBtConfigData += iSeparate;
//																					memset(szBuffer,0,260);
//																					pPos = strstr(pBtConfigData,"&nbsp");
//																					if (pPos)
//																					{
//																						memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																						pConfigInfo->bAutoAcceptHDGame = atoi(szBuffer);//21
//																						pBtConfigData += strlen(szBuffer);
//																						pBtConfigData += iSeparate;
//																						memset(szBuffer,0,260);
//																						pPos = strstr(pBtConfigData,"&nbsp");
//																						if (pPos)
//																						{
//																							memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																							pConfigInfo->bAutoAcceptToolSoft = atoi(szBuffer);//22
//																							pBtConfigData += strlen(szBuffer);
//																							pBtConfigData += iSeparate;
//																							memset(szBuffer,0,260);
//																							pPos = strstr(pBtConfigData,"&nbsp");
//																							if (pPos)
//																							{
//																								memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																								pConfigInfo->bAutoAcceptFZTool = atoi(szBuffer);//23
//																								pBtConfigData += strlen(szBuffer);
//																								pBtConfigData += iSeparate;
//																								memset(szBuffer,0,260);
//																								pPos = strstr(pBtConfigData,"&nbsp");
//																								if (pPos)
//																								{
//																									memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																									pConfigInfo->bAutoAcceptSize = atoi(szBuffer);//24
//																									pBtConfigData += strlen(szBuffer);
//																									pBtConfigData += iSeparate;
//																									memset(szBuffer,0,260);
//																									pPos = strstr(pBtConfigData,"&nbsp");
//																									if (pPos)
//																									{
//																										memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																										pConfigInfo->dwAutoAcceptSize = atol(szBuffer);//25
//																										pBtConfigData += strlen(szBuffer);
//																										pBtConfigData += iSeparate;
//																										memset(szBuffer,0,260);
//																										pPos = strstr(pBtConfigData,"&nbsp");
//																										if (pPos)
//																										{
//																											memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																											pConfigInfo->bAutoAcceptRank = atol(szBuffer);//26
//																											pBtConfigData += strlen(szBuffer);
//																											pBtConfigData += iSeparate;
//																											memset(szBuffer,0,260);
//																											pPos = strstr(pBtConfigData,"&nbsp");
//																											if (pPos)
//																											{
//																												memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																												pConfigInfo->dwAutoAcceptRank = atol(szBuffer);//27
//																												pBtConfigData += strlen(szBuffer);
//																												pBtConfigData += iSeparate;
//																												memset(szBuffer,0,260);
//																												pPos = strstr(pBtConfigData,"&nbsp");
//																												if (pPos)
//																												{
//																													memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																													pConfigInfo->bStartupRun_1 = atol(szBuffer);//28
//																													pBtConfigData += strlen(szBuffer);
//																													pBtConfigData += iSeparate;
//																													memset(szBuffer,0,260);
//																													pPos = strstr(pBtConfigData,"&nbsp");
//																													if (pPos)
//																													{
//																														memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																														pConfigInfo->bStartupRun_2 = atol(szBuffer);//29
//																														pBtConfigData += strlen(szBuffer);
//																														pBtConfigData += iSeparate;
//																														memset(szBuffer,0,260);
//																														pPos = strstr(pBtConfigData,"&nbsp");
//																														if (pPos)
//																														{
//																															memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																															pConfigInfo->bStartupRun_3 = atol(szBuffer);//30
//																															pBtConfigData += strlen(szBuffer);
//																															pBtConfigData += iSeparate;
//																															memset(szBuffer,0,260);
//																															pPos = strstr(pBtConfigData,"&nbsp");
//																															if (pPos)
//																															{
//																																memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																pConfigInfo->bExitRun_1 = atol(szBuffer);//31
//																																pBtConfigData += strlen(szBuffer);
//																																pBtConfigData += iSeparate;
//																																memset(szBuffer,0,260);
//																																pPos = strstr(pBtConfigData,"&nbsp");
//																																if (pPos)
//																																{
//																																	memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																	pConfigInfo->bExitRun_2 = atol(szBuffer);//32
//																																	pBtConfigData += strlen(szBuffer);
//																																	pBtConfigData += iSeparate;
//																																	memset(szBuffer,0,260);
//																																	pPos = strstr(pBtConfigData,"&nbsp");
//																																	if (pPos)
//																																	{
//																																		memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																		pConfigInfo->bExitRun_3 = atol(szBuffer);//33
//																																		pBtConfigData += strlen(szBuffer);
//																																		pBtConfigData += iSeparate;
//																																		memset(szBuffer,0,260);
//																																		pPos = strstr(pBtConfigData,"&nbsp");
//																																		if (pPos)
//																																		{
//																																			memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																			CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszStartupExe_1);//34
//																																			pBtConfigData += strlen(szBuffer);
//																																			pBtConfigData += iSeparate;
//																																			memset(szBuffer,0,260);
//																																			pPos = strstr(pBtConfigData,"&nbsp");
//																																			if (pPos)
//																																			{
//																																				memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																				CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszStartupExe_2);//35
//																																				pBtConfigData += strlen(szBuffer);
//																																				pBtConfigData += iSeparate;
//																																				memset(szBuffer,0,260);
//																																				pPos = strstr(pBtConfigData,"&nbsp");
//																																				if (pPos)
//																																				{
//																																					memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																					CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszStartupExe_3);//36
//																																					pBtConfigData += strlen(szBuffer);
//																																					pBtConfigData += iSeparate;
//																																					memset(szBuffer,0,260);
//																																					pPos = strstr(pBtConfigData,"&nbsp");
//																																					if (pPos)
//																																					{
//																																						memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																						CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszStartupParam_1);//37
//																																						pBtConfigData += strlen(szBuffer);
//																																						pBtConfigData += iSeparate;
//																																						memset(szBuffer,0,260);
//																																						pPos = strstr(pBtConfigData,"&nbsp");
//																																						if (pPos)
//																																						{
//																																							memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																							CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszStartupParam_2);//38
//																																							pBtConfigData += strlen(szBuffer);
//																																							pBtConfigData += iSeparate;
//																																							memset(szBuffer,0,260);
//																																							pPos = strstr(pBtConfigData,"&nbsp");
//																																							if (pPos)
//																																							{
//																																								memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																								CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszStartupParam_3);//39
//																																								pBtConfigData += strlen(szBuffer);
//																																								pBtConfigData += iSeparate;
//																																								memset(szBuffer,0,260);
//																																								pPos = strstr(pBtConfigData,"&nbsp");
//																																								if (pPos)
//																																								{
//																																									memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																									CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszExitExe_1);//40
//																																									pBtConfigData += strlen(szBuffer);
//																																									pBtConfigData += iSeparate;
//																																									memset(szBuffer,0,260);
//																																									pPos = strstr(pBtConfigData,"&nbsp");
//																																									if (pPos)
//																																									{
//																																										memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																										CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszExitExe_2);//41
//																																										pBtConfigData += strlen(szBuffer);
//																																										pBtConfigData += iSeparate;
//																																										memset(szBuffer,0,260);
//																																										pPos = strstr(pBtConfigData,"&nbsp");
//																																										if (pPos)
//																																										{
//																																											memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																											CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszExitExe_3);//42
//																																											pBtConfigData += strlen(szBuffer);
//																																											pBtConfigData += iSeparate;
//																																											memset(szBuffer,0,260);
//																																											pPos = strstr(pBtConfigData,"&nbsp");
//																																											if (pPos)
//																																											{
//																																												memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																												CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszExitParam_1);//43
//																																												pBtConfigData += strlen(szBuffer);
//																																												pBtConfigData += iSeparate;
//																																												memset(szBuffer,0,260);
//																																												pPos = strstr(pBtConfigData,"&nbsp");
//																																												if (pPos)
//																																												{
//																																													memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																													CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszExitParam_2);//44
//																																													pBtConfigData += strlen(szBuffer);
//																																													pBtConfigData += iSeparate;
//																																													memset(szBuffer,0,260);
//																																													pPos = strstr(pBtConfigData,"&nbsp");
//																																													if (pPos)
//																																													{
//																																														memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																														CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszExitParam_3);//45
//																																														pBtConfigData += strlen(szBuffer);
//																																														pBtConfigData += iSeparate;
//																																														memset(szBuffer,0,260);
//																																														pPos = strstr(pBtConfigData,"&nbsp");
//																																														if (pPos)
//																																														{
//																																															memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																															CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszCacheDirectory);//46
//																																															pBtConfigData += strlen(szBuffer);
//																																															pBtConfigData += iSeparate;
//																																															memset(szBuffer,0,260);
//																																															pPos = strstr(pBtConfigData,"&nbsp");
//																																															if (pPos)
//																																															{
//																																																memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[0]);//47
//																																																pBtConfigData += strlen(szBuffer);
//																																																pBtConfigData += iSeparate;
//																																																memset(szBuffer,0,260);
//																																																pPos = strstr(pBtConfigData,"&nbsp");
//																																																if (pPos)
//																																																{
//																																																	memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																	CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[1]);//48
//																																																	pBtConfigData += strlen(szBuffer);
//																																																	pBtConfigData += iSeparate;
//																																																	memset(szBuffer,0,260);
//																																																	pPos = strstr(pBtConfigData,"&nbsp");
//																																																	if (pPos)
//																																																	{
//																																																		memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																		CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[2]);//49
//																																																		pBtConfigData += strlen(szBuffer);
//																																																		pBtConfigData += iSeparate;
//																																																		memset(szBuffer,0,260);
//																																																		pPos = strstr(pBtConfigData,"&nbsp");
//																																																		if (pPos)
//																																																		{
//																																																			memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																			CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[3]);//50
//																																																			pBtConfigData += strlen(szBuffer);
//																																																			pBtConfigData += iSeparate;
//																																																			memset(szBuffer,0,260);
//																																																			pPos = strstr(pBtConfigData,"&nbsp");
//																																																			if (pPos)
//																																																			{
//																																																				memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																				CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[4]);//51
//																																																				pBtConfigData += strlen(szBuffer);
//																																																				pBtConfigData += iSeparate;
//																																																				memset(szBuffer,0,260);
//																																																				pPos = strstr(pBtConfigData,"&nbsp");
//																																																				if (pPos)
//																																																				{
//																																																					memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																					CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[5]);//52
//																																																					pBtConfigData += strlen(szBuffer);
//																																																					pBtConfigData += iSeparate;
//																																																					memset(szBuffer,0,260);
//																																																					pPos = strstr(pBtConfigData,"&nbsp");
//																																																					if (pPos)
//																																																					{
//																																																						memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																						CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[6]);//53
//																																																						pBtConfigData += strlen(szBuffer);
//																																																						pBtConfigData += iSeparate;
//																																																						memset(szBuffer,0,260);
//																																																						pPos = strstr(pBtConfigData,"&nbsp");
//																																																						if (pPos)
//																																																						{
//																																																							memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																							CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszDefaultDirectory[7]);//54
//																																																							pBtConfigData += strlen(szBuffer);
//																																																							pBtConfigData += iSeparate;
//																																																							memset(szBuffer,0,260);
//																																																							pPos = strstr(pBtConfigData,"&nbsp");
//																																																							if (pPos)
//																																																							{
//																																																								memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																								CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszLimitSpeedTimePeriod);//55
//																																																								pBtConfigData += strlen(szBuffer);
//																																																								pBtConfigData += iSeparate;
//																																																								memset(szBuffer,0,260);
//																																																								pPos = strstr(pBtConfigData,"&nbsp");
//																																																								if (pPos)
//																																																								{
//																																																									memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																									pConfigInfo->dwLimitUploadRate = atoi(szBuffer);//56
//																																																									pBtConfigData += strlen(szBuffer);
//																																																									pBtConfigData += iSeparate;
//																																																									memset(szBuffer,0,260);
//																																																									pPos = strstr(pBtConfigData,"&nbsp");
//																																																									if (pPos)
//																																																									{
//																																																										memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																										pConfigInfo->dwLimitDownloadRate = atoi(szBuffer);//57
//																																																										pBtConfigData += strlen(szBuffer);
//																																																										pBtConfigData += iSeparate;
//																																																										memset(szBuffer,0,260);
//																																																										pPos = strstr(pBtConfigData,"&nbsp");
//																																																										if (pPos)
//																																																										{
//																																																											memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																											CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszServerIP);//58
//																																																											pBtConfigData += strlen(szBuffer);
//																																																											pBtConfigData += iSeparate;
//																																																											memset(szBuffer,0,260);
//																																																											pPos = strstr(pBtConfigData,"&nbsp");
//																																																											if (pPos)
//																																																											{
//																																																												memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																												pConfigInfo->iSoftMode = atoi(szBuffer); // 59
//																																																												pBtConfigData += strlen(szBuffer);
//																																																												pBtConfigData += iSeparate;
//																																																												memset(szBuffer,0,260);
//																																																												pPos = strstr(pBtConfigData,"&nbsp");
//																																																												if (pPos)
//																																																												{
//																																																													memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																													pConfigInfo->bDisablePublishGames = atoi(szBuffer); //60
//																																																													pBtConfigData += strlen(szBuffer);
//																																																													pBtConfigData += iSeparate;
//																																																													memset(szBuffer,0,260);
//																																																													pPos = strstr(pBtConfigData,"&nbsp");
//																																																													if (pPos)
//																																																													{
//																																																														memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																														CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszSSD);//61
//																																																														pBtConfigData += strlen(szBuffer);
//																																																														pBtConfigData += iSeparate;
//																																																														memset(szBuffer,0,260);
//
//																																																														pPos = strstr(pBtConfigData,"&nbsp");
//																																																														if (pPos)
//																																																														{
//																																																															memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																															pConfigInfo->bMapPort = atoi(szBuffer);
//																																																															pBtConfigData += strlen(szBuffer);
//																																																															pBtConfigData += iSeparate;
//																																																															memset(szBuffer,0,260);
//																																																															pPos = strstr(pBtConfigData,"&nbsp");
//																																																															if (pPos)
//																																																															{
//																																																																memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																																pConfigInfo->bMapRouterPort = atoi(szBuffer);
//																																																																pBtConfigData += strlen(szBuffer);
//																																																																pBtConfigData += iSeparate;
//																																																																memset(szBuffer,0,260);
//																																																																pPos = strstr(pBtConfigData,"&nbsp");
//																																																																if (pPos)
//																																																																{
//																																																																	memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																																	CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszUserName);
//																																																																	pBtConfigData += strlen(szBuffer);
//																																																																	pBtConfigData += iSeparate;
//																																																																	memset(szBuffer,0,260);
//																																																																	pPos = strstr(pBtConfigData,"&nbsp");
//																																																																	if (pPos)
//																																																																	{
//																																																																		memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																																		CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszPassword);
//																																																																		pBtConfigData += strlen(szBuffer);
//																																																																		pBtConfigData += iSeparate;
//																																																																		memset(szBuffer,0,260);
//																																																																		pPos = strstr(pBtConfigData,"&nbsp");
//																																																																		if (pPos)
//																																																																		{
//																																																																			memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																																			CChineseCode::Utf8ToUniCode(szBuffer,pConfigInfo->wszOldPID);
//																																																																			pBtConfigData += strlen(szBuffer);
//																																																																			pBtConfigData += iSeparate;
//																																																																			memset(szBuffer,0,260);
//																																																																			pPos = strstr(pBtConfigData,"&nbsp");
//																																																																			if (pPos)
//																																																																			{
//																																																																				memcpy(szBuffer,pBtConfigData,pPos - pBtConfigData);
//																																																																				pConfigInfo->dwSyncIntervalTime = atol(szBuffer);
//																																																																				pBtConfigData += strlen(szBuffer);
//																																																																				pBtConfigData += iSeparate;
//																																																																				memset(szBuffer,0,260);
//																																																																				return 1;
//																																																																			}
//																																																																		}
//																																																																	}
//																																																																}
//																																																															}
//																																																														}
//
//																																																													}
//																																																												}
//																																																											}
//																																																										}
//																																																									}
//																																																								}
//																																																							}
//																																																						}
//																																																					}
//																																																				}
//																																																			}
//																																																		}
//																																																	}
//																																																}
//																																															}
//																																														}
//																																													}
//																																												}
//																																											}
//																																										}
//																																									}
//																																								}
//																																							}
//																																						}
//																																					}
//																																				}
//																																			}
//																																		}
//																																	}
//																																}
//																															}
//																														}
//																													}
//																												}
//																											}
//																										}
//																									}
//																								}
//																							}
//																						}
//																					}
//																				}
//																			}
//																		}
//																	}
//																}
//															}
//														}
//													}
//												}
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//CString		CBt::SetBtConfig(_BT_CONFIG_INFO* pConfigInfo)
//{
//	CString	strResult;
//	pConfigInfo->cbSize = sizeof(BT_CONFIG_INFO);
//	int ErrorRet = m_fnbtcSetBtConfig(pConfigInfo);
//	strResult.Format(_T("1&nbsp%d&nbsp"),ErrorRet);
//	return strResult;
//}
//
//CString	CBt::GetBtConfig()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString		strResult;
//
//	BT_CONFIG_INFO*	pConfig_Info = new BT_CONFIG_INFO;
//	pConfig_Info->cbSize = sizeof(BT_CONFIG_INFO);
//	int ErrorRet = m_fnbtcGetBtConfig(pConfig_Info);
//	if (ErrorRet != SCMD_OK)
//	{
//		strResult.Format(_T("%d"),ErrorRet);
//		return strResult;
//	}
//	
//	wchar_t	wszStartExe1PathBuffer[64] = { 0 };
//	wchar_t	wszStartExe2PathBuffer[64] = { 0 };
//	wchar_t	wszStartExe3PathBuffer[64] = { 0 };
//	wchar_t	wszStartupParam1Buffer[64] = { 0 };
//	wchar_t	wszStartupParam2Buffer[64] = { 0 };
//	wchar_t	wszStartupParam3Buffer[64] = { 0 };
//	wchar_t	wszExitExe1Buffer[64] = { 0 };
//	wchar_t	wszExitExe2Buffer[64] = { 0 };
//	wchar_t	wszExitExe3Buffer[64] = { 0 };
//	wchar_t	wszExitParam1Buffer[64] = { 0 };
//	wchar_t	wszExitParam2Buffer[64] = { 0 };
//	wchar_t	wszExitParam3Buffer[64] = { 0 };
//	wchar_t	wszCacheDirectoryBuffer[128] = { 0 };
//	wchar_t	wszDefaultDirectoryBuffer[8][64] = { 0 };
//	AddChar(pConfig_Info->wszStartupExe_1,(wchar_t*)wszStartExe1PathBuffer,63);
//	AddChar(pConfig_Info->wszStartupExe_2,(wchar_t*)wszStartExe2PathBuffer,63);
//	AddChar(pConfig_Info->wszStartupExe_3,(wchar_t*)wszStartExe3PathBuffer,63);
//	AddChar(pConfig_Info->wszStartupParam_1,(wchar_t*)wszStartupParam1Buffer,63);
//	AddChar(pConfig_Info->wszStartupParam_2,(wchar_t*)wszStartupParam2Buffer,63);
//	AddChar(pConfig_Info->wszStartupParam_3,(wchar_t*)wszStartupParam3Buffer,63);
//	AddChar(pConfig_Info->wszExitExe_1,(wchar_t*)wszExitExe1Buffer,63);
//	AddChar(pConfig_Info->wszExitExe_2,(wchar_t*)wszExitExe2Buffer,63);
//	AddChar(pConfig_Info->wszExitExe_3,(wchar_t*)wszExitExe3Buffer,63);
//	AddChar(pConfig_Info->wszExitParam_1,(wchar_t*)wszExitParam1Buffer,63);
//	AddChar(pConfig_Info->wszExitParam_2,(wchar_t*)wszExitParam2Buffer,63);
//	AddChar(pConfig_Info->wszExitParam_3,(wchar_t*)wszExitParam3Buffer,63);
//	AddChar(pConfig_Info->wszCacheDirectory,wszCacheDirectoryBuffer,127);
//	AddChar(pConfig_Info->wszDefaultDirectory[0],(wchar_t*)wszDefaultDirectoryBuffer[0],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[1],(wchar_t*)wszDefaultDirectoryBuffer[1],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[2],(wchar_t*)wszDefaultDirectoryBuffer[2],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[3],(wchar_t*)wszDefaultDirectoryBuffer[3],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[4],(wchar_t*)wszDefaultDirectoryBuffer[4],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[5],(wchar_t*)wszDefaultDirectoryBuffer[5],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[6],(wchar_t*)wszDefaultDirectoryBuffer[6],63);
//	AddChar(pConfig_Info->wszDefaultDirectory[7],(wchar_t*)wszDefaultDirectoryBuffer[7],63);
//
//	TCHAR	lpwzsSSD[32] = { 0 };
//	AddChar(pConfig_Info->wszSSD,lpwzsSSD,31);
//
//	strResult.Format(_T("1&nbsp['%d','%d','%ld','%ld','%ld','%ld','%ld','%ld','%ld','%ld','%d','%d','%d','%d','%ld','%ld','%d','%d','%d','%d','%d','%d','%d','%d','%ld','%d','%ld','%d','%d','%d','%d','%d','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%d','%s','%d','%d','%s','%d','%d','%s','%s','%s','%ld']"),
//		pConfig_Info->bUPNP,//1										//是否开启UPNP自动端口映射
//		pConfig_Info->bLimitLocalBandwidth,//2						//是否限制本地带宽(内网下载、上传速度)
//		pConfig_Info->dwMaxActiveTask,//3							//最大活动任务数
//		pConfig_Info->dwMaxDownloadTask,//4							//最大下载任务数
//		pConfig_Info->dwMaxDownloadSpeed,//5						//全局最大下载速度
//		pConfig_Info->dwMaxUploadSpeed,//6							//全局最大上传速度
//		pConfig_Info->dwHoldDiskSpace,//7							//需要预留的磁盘空间大小
//		pConfig_Info->dwUserNetLineType,//8							//用户上网线路类型
//		pConfig_Info->dwPort,//9									//BT端口
//		pConfig_Info->dwRouterPort,//10								//补种端口
//		pConfig_Info->bNoManualToAuto,//11							//下载时不改变更新方式为"自动更新"
//		pConfig_Info->bAutoRemoveCompletedTask,//12					//是否自动移除已完成的活动任务
//		pConfig_Info->bAutoRemoveSpeed,//13							//是否设置移除速度(下载速度小于此值时允许移除)
//		pConfig_Info->bAutoRemoveTime,//14							//是否设置移除时间(上传时间达到此值时允许移除)
//		pConfig_Info->dwAutoRemoveSpeed,//15						//自动移除需要下载速度小于此值
//		pConfig_Info->dwAutoRemoveTime,//16							//自动移除需要上传时间超过此值
//		pConfig_Info->bAutoDeleteStopUpdate,//17					//是否自动删除已停止更新的游戏
//		pConfig_Info->bAutoClearSpace,//18							//是否自动清理空间(在磁盘空间不够时)
//		pConfig_Info->bAutoAcceptNew,//19							//是否自动接受新增加资源
//		pConfig_Info->bAutoAcceptNetGame,//20						//是否自动接受新的网络游戏
//		pConfig_Info->bAutoAcceptHDGame,//21						//是否自动接受新的单机游戏
//		pConfig_Info->bAutoAcceptToolSoft,//22						//是否自动接受新的工具软件
//		pConfig_Info->bAutoAcceptFZTool,//23						//是否自动接受新的辅助工具
//		pConfig_Info->bAutoAcceptSize,//24							//是否限制自动接收的新资源的大小
//		pConfig_Info->dwAutoAcceptSize,//25							//自动接受新游戏时游戏大小不得大于此值
//		pConfig_Info->bAutoAcceptRank,//26							//是否限制自动接收的新资源的排行
//		pConfig_Info->dwAutoAcceptRank,//27							//自动接受新游戏时游戏网络排行不得大于此值
//		pConfig_Info->bStartupRun_1,//28
//		pConfig_Info->bStartupRun_2,//29
//		pConfig_Info->bStartupRun_3,//30
//		pConfig_Info->bExitRun_1,//31
//		pConfig_Info->bExitRun_2,//32
//		pConfig_Info->bExitRun_3,//33
//		wszStartExe1PathBuffer,//34
//		wszStartExe2PathBuffer,//35
//		wszStartExe3PathBuffer,//36
//		wszStartupParam1Buffer,//37
//		wszStartupParam2Buffer,//38
//		wszStartupParam3Buffer,//39
//		wszExitExe1Buffer,//40
//		wszExitExe2Buffer,//41
//		wszExitExe3Buffer,//42
//		wszExitParam1Buffer,//43
//		wszExitParam2Buffer,//44
//		wszExitParam3Buffer,//45
//		wszCacheDirectoryBuffer,//46
//		wszDefaultDirectoryBuffer[0],//47
//		wszDefaultDirectoryBuffer[1],//48
//		wszDefaultDirectoryBuffer[2],//49
//		wszDefaultDirectoryBuffer[3],//50
//		wszDefaultDirectoryBuffer[4],//51
//		wszDefaultDirectoryBuffer[5],//52
//		wszDefaultDirectoryBuffer[6],//53
//		wszDefaultDirectoryBuffer[7],//54
//		pConfig_Info->wszLimitSpeedTimePeriod,//55				//速度限制时间段
//		pConfig_Info->dwLimitUploadRate,//56					//上传速度限制值
//		pConfig_Info->dwLimitDownloadRate,//57					//下载速度限制值
//		pConfig_Info->wszServerIP,//58							//外网IP地址(内网连接外网时用)
//		pConfig_Info->iSoftMode,//59							//程序模式(0:外网模式,1:无盘内网模式,2:有盘内网模式
//		pConfig_Info->bDisablePublishGames,//60				//禁止内网铺送游戏
//		lpwzsSSD,
//		pConfig_Info->bMapPort,								//是否映射BT端口
//		pConfig_Info->bMapRouterPort,						//是否映射补种端口
//		pConfig_Info->wszUserName,							//用户账号
//		pConfig_Info->wszPassword,							//用户密码
//		pConfig_Info->wszOldPID,							//上次成功登录的PID
//		pConfig_Info->dwSyncIntervalTime);				//与服务器同步数据间隔时间
//	delete	[]pConfig_Info;
//	return strResult;
//}
//
//int 	CBt::SetUserPassWord(CString StrPassWord, CString	&StrResult)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	int nPacketLen = sizeof(SOCKET_HEAD_REQUEST) + StrPassWord.GetLength() * 2;
//	Bt_Quest_Head.dwRequestSize = nPacketLen;
//	Bt_Quest_Head.uCommand = COMMAND_SET_PASSWORD;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte	szSendBuffer[1024] = { 0 };
//	byte*	pszSendBuffer = szSendBuffer;
//	memcpy(pszSendBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pszSendBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pszSendBuffer,StrPassWord.GetBuffer(),StrPassWord.GetLength() * 2);
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(szSendBuffer,nPacketLen);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return iResult;
//	}
//	Sleep(100);
//	byte	szRecvBuffer[1024] = { 0 };
//	iSocketRet = Receive(szRecvBuffer,1024);
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return iResult;
//	}
//	byte*	pszRecvBuffer = szRecvBuffer;
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	memcpy(&Bt_Reply_Head,pszRecvBuffer,sizeof(SOCKET_HEAD_REPLY));
//	pszRecvBuffer += sizeof(SOCKET_HEAD_REPLY);
//	TCHAR	wzRecvPassWord[MAX_PATH] = { 0 };
//	memcpy(wzRecvPassWord,pszRecvBuffer,Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY));
//	if (StrPassWord == wzRecvPassWord)
//	{
//		StrResult.Format(_T("1&nbsp%s&nbsp修改BT密码成功！"),wzRecvPassWord);
//		return 1;
//	}
//	StrResult.Format(_T("0&nbsp修改BT密码不成功！"));
//	return iResult;
//}
//
//CString	CBt::GetPeer_Entry(CString StrId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	DWORD	dwMemory = sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	CString	StrResult;
//
//	byte*	pbBuffer = new	byte[dwMemory];
//	byte*	pTemp = pbBuffer;
//
//	DWORD	dwId = _ttol(StrId);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_GET_TASK_PEER_INFO;
//	Bt_Quest_Head.dwCount = 1;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	memcpy(pTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTemp,&dwId,sizeof(int));
//
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	PEER_INFO_ENTRY	Peer_Info;
//	iSocketRet = Receive(&Peer_Info,sizeof(PEER_INFO_ENTRY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("1&nbsp0&nbsp"));
//		return StrResult;
//	}
//	CString	StrIp(Peer_Info.ip);
//	StrResult.Format(_T("1&nbsp['%s','%d','%d','%d','%d','%I64d','%I64d']"),
//		StrIp,
//		Peer_Info.port,
//		Peer_Info.connectionType,
//		Peer_Info.downloadSpeed,
//		Peer_Info.uploadSpeed,
//		Peer_Info.downloadedBytes,
//		Peer_Info.uploadedBytes);
//	return StrResult;
//}
//

//
//CString	CBt::GetGameClassType(CString Game_Id)
//{
//	CString	StrRet;
//	CString	StrType = Game_Id.Left(2);
//	int iType = _ttoi(StrType);
//	switch (iType)
//	{
//	case	21:
//		{
//			StrRet = _T("网络游戏");
//			break;
//		}
//	case	11:
//		{
//			StrRet = _T("单机游戏");
//			break;
//		}
//	case	22:
//		{
//			StrRet = _T("棋牌对战");
//			break;
//		}
//	case	31:
//		{
//			StrRet = _T("工具软件");
//			break;
//		}
//	case	32:
//		{
//			StrRet = _T("金融证券");
//			break;
//		}
//	case	23:
//		{
//			StrRet = _T("聊天工具");
//			break;
//		}
//	case	12:
//		{
//			StrRet = _T("休闲游戏");
//			break;
//		}
//	case	61:
//		{
//			StrRet = _T("辅助工具");
//			break;
//		}
//	}
//	return StrRet;
//}
//
//int		CBt::GetDelete_Game_Sort(CStringArray& DeleteGameArray)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_DELETE_GAME_SORT;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	DWORD	dwAllRecv = 0;
//	DWORD	dwMemory = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[dwMemory];
//	byte*	pTemp = pRecvBuffer;
//	while (dwAllRecv != dwMemory)
//	{
//		iSocketRet = Receive(pRecvBuffer,sizeof(DELETE_GAME_SORT));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pTemp;
//			return -1;
//		}
//		dwAllRecv += iSocketRet;
//		pRecvBuffer += iSocketRet;
//	}
//	DELETE_GAME_SORT*	pDeleteGame = (DELETE_GAME_SORT*)pTemp;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		CString		StrData;
//		CString	StrGameType = GetGameClassType(pDeleteGame->wszGame_Id);
//		TCHAR	RegPathBuffer[MAX_PATH] = { 0 };
//		AddChar(pDeleteGame->wszGame_Reg,RegPathBuffer,MAX_PATH);
//		StrData.Format(_T("['%s','%s','%ld','%s','%ld','%ld','%s','%0.2f','%d'],"),
//			pDeleteGame->wszGame_Id,
//			pDeleteGame->wszGame_Text,
//			pDeleteGame->dwGameSize,
//			StrGameType,
//			pDeleteGame->dwNet_Sort,
//			pDeleteGame->dwTopGrade,
//			RegPathBuffer,
//			pDeleteGame->fMonthClick,
//			pDeleteGame->nGame_Flag);
//		DeleteGameArray.Add(StrData);
//		pDeleteGame++;
//	}
//	delete []pTemp;
//	return DeleteGameArray.GetSize();
//}
//
//int		CBt::GetSuperFluous_Game(CStringArray& SuperGameArray)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_SUPERFLUOUS_GAME_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//
//	DWORD	dwMemory = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[dwMemory];
//	DWORD	dwAllRecv = 0;
//	byte*	pTemp = pRecvBuffer;
//	while (dwAllRecv != dwMemory)
//	{
//		iSocketRet = Receive(pRecvBuffer,sizeof(RESOURCE_INFO));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pTemp;
//			return -1;
//		}
//		dwAllRecv += iSocketRet;
//		pRecvBuffer += iSocketRet;
//	}
//	RESOURCE_INFO*	pGameInfo = (RESOURCE_INFO*)pTemp;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		CString	StrGameData;
//		CString	StrGameType = GetGameClassType(pGameInfo->gi.wszGame_Id);
//		CString	StrUpdateTime;
//		TCHAR	RegPathBuffer[MAX_PATH] = { 0 };
//		AddChar(pGameInfo->gi.wszGame_Reg,RegPathBuffer,MAX_PATH);
//		StrUpdateTime.Format(_T("%d-%d-%d %d:%d:%d"),pGameInfo->gi.InstTime.wYear,pGameInfo->gi.InstTime.wMonth,pGameInfo->gi.InstTime.wDayOfWeek,pGameInfo->gi.InstTime.wHour,pGameInfo->gi.InstTime.wMilliseconds,pGameInfo->gi.InstTime.wSecond);
//		StrGameData.Format(_T("['%s','%s','%ld','%ld','%ld','%s','%s','%s','%d'],"),
//			pGameInfo->gi.wszGame_Id,
//			pGameInfo->gi.wszGame_Text,
//			pGameInfo->gi.dwGameSize,
//			pGameInfo->gi.bIsPlan,
//			pGameInfo->gi.nGame_Flag,
//			StrUpdateTime,
//			RegPathBuffer,
//			StrGameType,
//			pGameInfo->gi.wszGame_Abc,
//			pGameInfo->nServerGameStatus);
//		SuperGameArray.Add(StrGameData);
//		pGameInfo++;
//	}
//	delete	[]pTemp;
//	return	SuperGameArray.GetSize();
//}
//
//CString		CBt::SetDelete_Sort(CDWordArray& DeleteGameArray)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	DWORD	dwMemory = DeleteGameArray.GetSize() * sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	CString	StrResult;
//	
//	byte*	pbBuffer = new	byte[dwMemory];
//	byte*	pTemp = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_SET_DELETE_SORT;
//	Bt_Quest_Head.dwCount = DeleteGameArray.GetSize();
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	memcpy(pTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTemp += sizeof(SOCKET_HEAD_REQUEST);
//
//	for (int i = 0; i < DeleteGameArray.GetSize(); i++)
//	{
//		int Id_Game = DeleteGameArray.GetAt(i);
//		memcpy(pTemp,&Id_Game,sizeof(int));
//		pTemp += sizeof(int);
//	}
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误。"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误。"));
//		return StrResult;
//	}
//
//	if (Bt_Reply_Head.iErrorCode == SCMD_OK)
//	{
//		StrResult.Format(_T("1&nbsp设置成功！"));
//	}
//	else
//	{
//		StrResult.Format(_T("1&nbsp设置失败！"));
//	}
//	return StrResult;
//}
//
//int		CBt::GetDelete_Sort_Click(CStringArray& DeleteGameArray, int Grade)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemoryPacket = sizeof(SOCKET_HEAD_REQUEST) + sizeof(int);
//	byte*	pbBuffer = new byte[dwMemoryPacket];
//	byte*	pTempBuffer = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemoryPacket;
//	Bt_Quest_Head.uCommand = COMMAND_GET_DELETE_GAME_SORT;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&Grade,sizeof(int));
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(pbBuffer,dwMemoryPacket);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	delete	[]pbBuffer;
//
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	DWORD	dwAllRecv = 0;
//	DWORD	dwMemory = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[dwMemory];
//	byte*	pTemp = pRecvBuffer;
//	while (dwAllRecv != dwMemory)
//	{
//		iSocketRet = Receive(pRecvBuffer,sizeof(DELETE_GAME_SORT));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pTemp;
//			return -1;
//		}
//		dwAllRecv += iSocketRet;
//		pRecvBuffer += iSocketRet;
//	}
//	DELETE_GAME_SORT*	pDeleteGame = (DELETE_GAME_SORT*)pTemp;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		CString		StrData;
//		CString	StrGameType = GetGameClassType(pDeleteGame->wszGame_Id);
//		TCHAR	RegPathBuffer[MAX_PATH] = { 0 };
//		AddChar(pDeleteGame->wszGame_Reg,RegPathBuffer,MAX_PATH);
//		StrData.Format(_T("['%s','%s','%ld','%s','%ld','%ld','%s','%0.2f','%d'],"),
//			pDeleteGame->wszGame_Id,
//			pDeleteGame->wszGame_Text,
//			pDeleteGame->dwGameSize,
//			StrGameType,
//			pDeleteGame->dwNet_Sort,
//			pDeleteGame->dwTopGrade,
//			RegPathBuffer,
//			pDeleteGame->fMonthClick,
//			pDeleteGame->nGame_Flag);
//		DeleteGameArray.Add(StrData);
//		pDeleteGame++;
//	}
//	delete []pTemp;
//	return DeleteGameArray.GetSize();
//}
//
//int		CBt::GetDelete_Sort_Grade(CStringArray& DeleteGameArray, int Grade)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemoryPacket = sizeof(SOCKET_HEAD_REQUEST) + sizeof(int);
//	byte*	pbBuffer = new byte[dwMemoryPacket];
//	byte*	pTempBuffer = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemoryPacket;
//	Bt_Quest_Head.uCommand = COMMAND_GET_DELETE_GAME_SORT;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&Grade,sizeof(int));
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(pbBuffer,dwMemoryPacket);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	delete	[]pbBuffer;
//
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	DWORD	dwAllRecv = 0;
//	DWORD	dwMemory = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[dwMemory];
//	byte*	pTemp = pRecvBuffer;
//	while (dwAllRecv != dwMemory)
//	{
//		iSocketRet = Receive(pRecvBuffer,sizeof(DELETE_GAME_SORT));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pTemp;
//			return -1;
//		}
//		dwAllRecv += iSocketRet;
//		pRecvBuffer += iSocketRet;
//	}
//	DELETE_GAME_SORT*	pDeleteGame = (DELETE_GAME_SORT*)pTemp;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		CString		StrData;
//		CString	StrGameType = GetGameClassType(pDeleteGame->wszGame_Id);
//		TCHAR	RegPathBuffer[MAX_PATH] = { 0 };
//		AddChar(pDeleteGame->wszGame_Reg,RegPathBuffer,MAX_PATH);
//		StrData.Format(_T("['%s','%s','%ld','%s','%ld','%ld','%s','%0.2f','%d'],"),
//			pDeleteGame->wszGame_Id,
//			pDeleteGame->wszGame_Text,
//			pDeleteGame->dwGameSize,
//			StrGameType,
//			pDeleteGame->dwNet_Sort,
//			pDeleteGame->dwTopGrade,
//			RegPathBuffer,
//			pDeleteGame->fMonthClick,
//			pDeleteGame->nGame_Flag);
//		DeleteGameArray.Add(StrData);
//		pDeleteGame++;
//	}
//	delete []pTemp;
//	return DeleteGameArray.GetSize();
//}
//
//int		CBt::GetTasksList(CStringArray& TasksList)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_TASKS_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		return -1;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	DWORD	dwAllRecv = 0;
//	DWORD	dwMemory = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[dwMemory];
//	byte*	pTemp = pRecvBuffer;
//	while (dwAllRecv != dwMemory)
//	{
//		iSocketRet = Receive(pRecvBuffer,sizeof(TASK_INFO));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pTemp;
//			return 0;
//		}
//		dwAllRecv += iSocketRet;
//		pRecvBuffer += iSocketRet;
//	}
//	TASK_INFO*	pTask_Info = (TASK_INFO*)pTemp;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		CString	StrMessageData;
//		INT64	i64FileSize = 0;
//		INT64	i64Downloade = 0;
//		INT64	dwSurplusSize = 0;
//		DWORD	dwSpeed = 0;
//		DWORD	dwState = 0;
//		DWORD	dwTime = 0;
//		DWORD	dwCurrentSeedCount = 0;
//		DWORD	dwCurrentPeerCount = 0;
//		CString	StrHask;
//		CString	StrSaveFile, StrIdxFile;
//		TCHAR	wzsSaveFilePath[MAX_PATH] = { 0 };
//		TCHAR	wzsIdxFilePath[MAX_PATH] = { 0 };
//		if (pTask_Info->dwType == FALSE)
//		{
//			i64FileSize = pTask_Info->wti.dwTotalBtye;
//			i64Downloade = pTask_Info->wti.dwCompletedBtye;
//			dwState = pTask_Info->wti.dwStatus;
//		}
//		if (pTask_Info->dwType == TRUE)
//		{
//			i64FileSize = pTask_Info->di.totalFileSizeExcludePadding;
//			i64Downloade = pTask_Info->di.totalDownloadedBytes;
//			dwSpeed = pTask_Info->di.downloadSpeed;
//			dwState = pTask_Info->di.state;
//			if (dwSpeed != NULL)
//			{
//				dwTime = (i64FileSize - i64Downloade) / dwSpeed;
//			}
//			StrHask = pTask_Info->di.infoHash;
//			if (pTask_Info->dwCacheDirectoryStatus == NULL)
//			{
//				StrSaveFile = pTask_Info->wszDirectory;
//			}
//			else
//			{
//				StrSaveFile = pTask_Info->wszCacheDirectory;
//			}
//			StrIdxFile = pTask_Info->wszIdxPath;
//			AddChar(StrSaveFile.GetBuffer(),(wchar_t*)wzsSaveFilePath,MAX_PATH);
//			AddChar(StrIdxFile.GetBuffer(),(wchar_t*)wzsIdxFilePath,MAX_PATH);
//			dwCurrentSeedCount = pTask_Info->di.totalCurrentSeedCount;
//			dwCurrentPeerCount = pTask_Info->di.totalCurrentPeerCount;
//			dwSurplusSize = i64FileSize - i64Downloade;
//		}
//		StrMessageData.Format(_T("['%ld','%s','%ld','%I64d','%I64d','%I64d','%ld','%ld','%s','%d','%s','%s','%d','%d','%d','%d'],"),
//			pTask_Info->dwID,
//			pTask_Info->wszGame_Name,
//			pTask_Info->dwIndex,
//			i64FileSize,
//			i64Downloade,
//			dwSurplusSize,
//			dwState,
//			dwTime,
//			StrHask,
//			pTask_Info->dwType,
//			wzsSaveFilePath,
//			wzsIdxFilePath,
//			pTask_Info->dwImageIndex,
//			dwCurrentSeedCount,
//			dwCurrentPeerCount,
//			dwSpeed);
//		TasksList.Add(StrMessageData);
//		pTask_Info++;
//	}
//	delete []pTemp;
//	return TasksList.GetCount();
//}
//
//CString	CBt::SetTaskInfo(CString StrId, int nFlag)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	DWORD	dwMemory = sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	CString	StrResult;
//
//	byte*	pbBuffer = new	byte[dwMemory];
//	byte*	pTemp = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	switch (nFlag)
//	{
//	case	0:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_START;
//			break;
//		}
//	case	1:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_STOP;
//			break;
//		}
//	case	2:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_REMOVE;
//			break;
//		}
//	case	3:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_UP;
//			break;
//		}
//	case	4:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_DOWN;
//			break;
//		}
//	case	5:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_TOP;
//			break;
//		}
//	case	6:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_CHECK;
//			break;
//		}
//	}
//	DWORD	dwId = _ttol(StrId);
//	memcpy(pTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTemp,&dwId,sizeof(int));
//	
//	int			iSocketRet;
//	int			iResult = 0;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp操作成功！"));
//	return StrResult;
//}
//
//CString		CBt::SetSimple_Property(SET_GAME_SIMPLE_PROPERTY PropertyInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(GAME_SIMPLE_PROPERTY);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_SET_SIMPLE_PROPERTY;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&PropertyInfo,sizeof(GAME_SIMPLE_PROPERTY));
//	pTempBuffer += sizeof(GAME_SIMPLE_PROPERTY);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString	CBt::GetSimple_Property(int iId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString		StrResult;
//
//	DWORD	dwMemory = sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_GET_SIMPLE_PROPERTY;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&iId,sizeof(int));
//	
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	GET_GAME_SIMPLE_PROPERTY	Get_PropertyInfo;
//	iSocketRet = Receive(&Get_PropertyInfo,sizeof(GET_GAME_SIMPLE_PROPERTY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	TCHAR	lpwzsDirectory[260] = { 0 };
//	TCHAR	lpwszDirectoryName[64] = { 0 };
//	AddChar(Get_PropertyInfo.wszDirectory,lpwzsDirectory,260);
//	AddChar(Get_PropertyInfo.wszDirectoryName,lpwszDirectoryName,64);
//	StrResult.Format(_T("1&nbsp['%ld','%ld','%ld','%ld','%ld','%s','%s','%s']"),
//		Get_PropertyInfo.nGame_Flag,
//		Get_PropertyInfo.dwIsPlan,
//		Get_PropertyInfo.dwClearFile,
//		Get_PropertyInfo.dwTopGrade,
//		Get_PropertyInfo.dwGroupMode,
//		lpwszDirectoryName,
//		lpwzsDirectory,
//		Get_PropertyInfo.wszAllGroupName);
//	return StrResult;
//}
//
//CString	CBt::OperationSimple_Property(int iId, int nFlag)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString		StrResult;
//
//	DWORD	dwMemory = sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	switch (nFlag)
//	{
//	case	1:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_TASK_ADD;
//			break;
//		}
//	case	2:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_GAME_DELETE;
//			break;
//		}
//	case	4:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_GAME_CLEAR_FILEDIR;
//			break;
//		}
//	}
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&iId,sizeof(int));
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//int		CBt::LoadBtGameInfo(char* pBtGameData,MENU_CONFIG* pMenu_Manager)
//{
//	int iSeparate = strlen("&nbsp");
//	char*	pPos = NULL;
//	char	szBuffer[128] = { 0 };
//	USHORT nPicSpacingX,nPicSpacingY,nNormalIconSpacingX,nNormalIconSpacingY,nSmallIconSpacingX,nSmallIconSpacingY,nBigIconSpacingX,nBigIconSpacingY;
//	pPos = strstr(pBtGameData,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//		pMenu_Manager->manager.nShowAsIcon = atoi(szBuffer);
//		pBtGameData += strlen(szBuffer);
//		pBtGameData += iSeparate;
//		memset(szBuffer,0,128);
//		pPos = strstr(pBtGameData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//			pMenu_Manager->manager.nRunIsMode = atoi(szBuffer);
//			pBtGameData += strlen(szBuffer);
//			pBtGameData += iSeparate;
//			memset(szBuffer,0,128);
//			pPos = strstr(pBtGameData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//				CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszSkinFileName);
//				pBtGameData += strlen(szBuffer);
//				pBtGameData += iSeparate;
//				memset(szBuffer,0,128);
//				pPos = strstr(pBtGameData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//					CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszBgFileName);
//					pBtGameData += strlen(szBuffer);
//					pBtGameData += iSeparate;
//					memset(szBuffer,0,128);
//					pPos = strstr(pBtGameData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//						nPicSpacingX = atoi(szBuffer);
//						pBtGameData += strlen(szBuffer);
//						pBtGameData += iSeparate;
//						memset(szBuffer,0,128);
//						pPos = strstr(pBtGameData,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//							nPicSpacingY = atoi(szBuffer);
//							pBtGameData += strlen(szBuffer);
//							pBtGameData += iSeparate;
//							memset(szBuffer,0,128);
//							pPos = strstr(pBtGameData,"&nbsp");
//							if (pPos)
//							{
//								memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//								nNormalIconSpacingX = atoi(szBuffer);
//								pBtGameData += strlen(szBuffer);
//								pBtGameData += iSeparate;
//								memset(szBuffer,0,128);
//								pPos = strstr(pBtGameData,"&nbsp");
//								if (pPos)
//								{
//									memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//									nNormalIconSpacingY = atoi(szBuffer);
//									pBtGameData += strlen(szBuffer);
//									pBtGameData += iSeparate;
//									memset(szBuffer,0,128);
//									pPos = strstr(pBtGameData,"&nbsp");
//									if (pPos)
//									{
//										memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//										nSmallIconSpacingX = atoi(szBuffer);
//										pBtGameData += strlen(szBuffer);
//										pBtGameData += iSeparate;
//										memset(szBuffer,0,128);
//										pPos = strstr(pBtGameData,"&nbsp");
//										if (pPos)
//										{
//											memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//											nSmallIconSpacingY = atoi(szBuffer);
//											pBtGameData += strlen(szBuffer);
//											pBtGameData += iSeparate;
//											memset(szBuffer,0,128);
//											pPos = strstr(pBtGameData,"&nbsp");
//											if (pPos)
//											{
//												memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//												nBigIconSpacingX = atoi(szBuffer);
//												pBtGameData += strlen(szBuffer);
//												pBtGameData += iSeparate;
//												memset(szBuffer,0,128);
//												pPos = strstr(pBtGameData,"&nbsp");
//												if (pPos)
//												{
//													memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//													nBigIconSpacingY = atoi(szBuffer);
//													pBtGameData += strlen(szBuffer);
//													pBtGameData += iSeparate;
//													memset(szBuffer,0,128);
//													pPos = strstr(pBtGameData,"&nbsp");
//													if (pPos)
//													{
//														memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//														pMenu_Manager->manager.nHideGameTools = atoi(szBuffer);
//														pBtGameData += strlen(szBuffer);
//														pBtGameData += iSeparate;
//														memset(szBuffer,0,128);
//														pPos = strstr(pBtGameData,"&nbsp");
//														if (pPos)
//														{
//															memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//															pMenu_Manager->manager.nHideCallBoard = atoi(szBuffer);
//															pBtGameData += strlen(szBuffer);
//															pBtGameData += iSeparate;
//															memset(szBuffer,0,128);
//															pPos = strstr(pBtGameData,"&nbsp");
//															if (pPos)
//															{
//																memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszQQ_Exe);
//																pBtGameData += strlen(szBuffer);
//																pBtGameData += iSeparate;
//																memset(szBuffer,0,128);
//																pPos = strstr(pBtGameData,"&nbsp");
//																if (pPos)
//																{
//																	memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																	CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszMusic_Exe);
//																	pBtGameData += strlen(szBuffer);
//																	pBtGameData += iSeparate;
//																	memset(szBuffer,0,128);
//																	pPos = strstr(pBtGameData,"&nbsp");
//																	if (pPos)
//																	{
//																		memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																		CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomName1);
//																		pBtGameData += strlen(szBuffer);
//																		pBtGameData += iSeparate;
//																		memset(szBuffer,0,128);
//																		pPos = strstr(pBtGameData,"&nbsp");
//																		if (pPos)
//																		{
//																			memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																			CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomName2);
//																			pBtGameData += strlen(szBuffer);
//																			pBtGameData += iSeparate;
//																			memset(szBuffer,0,128);
//																			pPos = strstr(pBtGameData,"&nbsp");
//																			if (pPos)
//																			{
//																				memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																				CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomName3);
//																				pBtGameData += strlen(szBuffer);
//																				pBtGameData += iSeparate;
//																				memset(szBuffer,0,128);
//																				pPos = strstr(pBtGameData,"&nbsp");
//																				if (pPos)
//																				{
//																					memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																					CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomName4);
//																					pBtGameData += strlen(szBuffer);
//																					pBtGameData += iSeparate;
//																					memset(szBuffer,0,128);
//																					pPos = strstr(pBtGameData,"&nbsp");
//																					if (pPos)
//																					{
//																						memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																						CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomExe1);
//																						pBtGameData += strlen(szBuffer);
//																						pBtGameData += iSeparate;
//																						memset(szBuffer,0,128);
//																						pPos = strstr(pBtGameData,"&nbsp");
//																						if (pPos)
//																						{
//																							memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																							CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomExe2);
//																							pBtGameData += strlen(szBuffer);
//																							pBtGameData += iSeparate;
//																							memset(szBuffer,0,128);
//																							pPos = strstr(pBtGameData,"&nbsp");
//																							if (pPos)
//																							{
//																								memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																								CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomExe3);
//																								pBtGameData += strlen(szBuffer);
//																								pBtGameData += iSeparate;
//																								memset(szBuffer,0,128);
//																								pPos = strstr(pBtGameData,"&nbsp");
//																								if (pPos)
//																								{
//																									memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																									CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszCustomExe4);
//																									pBtGameData += strlen(szBuffer);
//																									pBtGameData += iSeparate;
//																									memset(szBuffer,0,128);
//																									pPos = strstr(pBtGameData,"&nbsp");
//																									if (pPos)
//																									{
//																										memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																										CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszNetwork_Disk);
//																										pBtGameData += strlen(szBuffer);
//																										pBtGameData += iSeparate;
//																										memset(szBuffer,0,128);
//																										pPos = strstr(pBtGameData,"&nbsp");
//																										if (pPos)
//																										{
//																											memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																											CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszTools_Disk);
//																											pBtGameData += strlen(szBuffer);
//																											pBtGameData += iSeparate;
//																											memset(szBuffer,0,128);
//																											pPos = strstr(pBtGameData,"&nbsp");
//																											if (pPos)
//																											{
//																												memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																												pMenu_Manager->dwMenuStyle = atoi(szBuffer);
//																												pBtGameData += strlen(szBuffer);
//																												pBtGameData += iSeparate;
//																												memset(szBuffer,0,128);
//																												pPos = strstr(pBtGameData,"&nbsp");
//																												if (pPos)
//																												{
//																													memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																													pMenu_Manager->dwClassTemplate = atoi(szBuffer);
//																													pBtGameData += strlen(szBuffer);
//																													pBtGameData += iSeparate;
//																													memset(szBuffer,0,128);
//																													pPos = strstr(pBtGameData,"&nbsp");
//																													if (pPos)
//																													{
//																														memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																														int ShowMode = atoi(szBuffer);
//																														if (ShowMode)
//																														{
//																															pMenu_Manager->manager.nShowBoardTime |= 0x02;
//																														}
//																														pBtGameData += strlen(szBuffer);
//																														pBtGameData += iSeparate;
//																														memset(szBuffer,0,128);
//																														pPos = strstr(pBtGameData,"&nbsp");
//																														if (pPos)
//																														{
//																															memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																															int ShowMode1 = atoi(szBuffer);
//																															if (ShowMode1 == 1)
//																															{
//																																pMenu_Manager->manager.nShowBoardTime |= 0x01;
//																															}
//																															pBtGameData += strlen(szBuffer);
//																															pBtGameData += iSeparate;
//																															memset(szBuffer,0,128);
//																															pPos = strstr(pBtGameData,"&nbsp");
//																															if (pPos)
//																															{
//																																memcpy(szBuffer,pBtGameData,pPos - pBtGameData);
//																																CChineseCode::Utf8ToUniCode(szBuffer,pMenu_Manager->manager.wszShowBoardText);
//																																pBtGameData += strlen(szBuffer);
//																																pBtGameData += iSeparate;
//																																memset(szBuffer,0,128);
//																																int nTemp = nPicSpacingY;
//																																nTemp = nTemp << 16 | nPicSpacingX;
//																																pMenu_Manager->manager.nPicSpacing = nTemp;
//																																nTemp = nNormalIconSpacingY;
//																																nTemp = nTemp << 16 | nNormalIconSpacingX;
//																																pMenu_Manager->manager.nNormalIconSpacing = nTemp;
//																																nTemp = nSmallIconSpacingY;
//																																nTemp = nTemp << 16 | nSmallIconSpacingX;
//																																pMenu_Manager->manager.nSmallIconSpacing = nTemp;
//																																nTemp = nBigIconSpacingY;
//																																nTemp = nTemp << 16 | nBigIconSpacingX;
//																																pMenu_Manager->manager.nBigIconSpacing = nTemp;
//																																return 1;
//																															}
//																														}
//																													}
//																												}
//																											}
//																										}
//																									}
//																								}
//																							}
//																						}
//																					}
//																				}
//																			}
//																		}
//																	}
//																}
//															}
//														}
//													}
//												}
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//CString	CBt::GetBtGameInfo()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_GET_MENU_CONFIG;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//
//	int			iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	Sleep(100);
//
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	int RecvSize = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	MENU_MANAGER*	Bt_MessageInfo = (MENU_MANAGER*)GlobalAlloc(GPTR,RecvSize);
//	iSocketRet = Receive(Bt_MessageInfo,RecvSize);
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	TCHAR	wszQQ_ExeBuffer[64] = { 0 };
//	TCHAR	wszMusic_ExeBuffer[128] = { 0 };
//	TCHAR	wszCustomExe1Buffer[128] = { 0 };
//	TCHAR	wszCustomExe2Buffer[128] = { 0 };
//	TCHAR	wszCustomExe3Buffer[128] = { 0 };
//	TCHAR	wszCustomExe4Buffer[128] = { 0 };
//	TCHAR	wszNetwork_DiskBuffer[128] = { 0 };
//	TCHAR	wszTools_DiskBuffer[128] = { 0 };
//	AddChar(Bt_MessageInfo->manager.wszQQ_Exe,(wchar_t*)wszQQ_ExeBuffer,64);
//	AddChar(Bt_MessageInfo->manager.wszMusic_Exe,(wchar_t*)wszMusic_ExeBuffer,128);
//	AddChar(Bt_MessageInfo->manager.wszCustomExe1,(wchar_t*)wszCustomExe1Buffer,128);
//	AddChar(Bt_MessageInfo->manager.wszCustomExe2,(wchar_t*)wszCustomExe2Buffer,128);
//	AddChar(Bt_MessageInfo->manager.wszCustomExe3,(wchar_t*)wszCustomExe3Buffer,128);
//	AddChar(Bt_MessageInfo->manager.wszCustomExe4,(wchar_t*)wszCustomExe4Buffer,128);
//	AddChar(Bt_MessageInfo->manager.wszNetwork_Disk,(wchar_t*)wszNetwork_DiskBuffer,128);
//	AddChar(Bt_MessageInfo->manager.wszTools_Disk,(wchar_t*)wszTools_DiskBuffer,128);
//	int nPicSpacingX = LOWORD(Bt_MessageInfo->manager.nPicSpacing);
//	int nPicSpacingY = HIWORD(Bt_MessageInfo->manager.nPicSpacing);
//
//	int nNormalIconSpacingX = LOWORD(Bt_MessageInfo->manager.nNormalIconSpacing);
//	int nNormalIconSpacingY = HIWORD(Bt_MessageInfo->manager.nNormalIconSpacing);
//
//	int nSmallIconSpacingX = LOWORD(Bt_MessageInfo->manager.nSmallIconSpacing);
//	int nSmallIconSpacingY = HIWORD(Bt_MessageInfo->manager.nSmallIconSpacing);
//
//	int nBigIconSpacingX = LOWORD(Bt_MessageInfo->manager.nBigIconSpacing);
//	int nBigIconSpacingY = HIWORD(Bt_MessageInfo->manager.nBigIconSpacing);
//	int	ShowMode1 = Bt_MessageInfo->manager.nShowBoardTime & 2;
//	int ShowMode2 = Bt_MessageInfo->manager.nShowBoardTime & 1;
//
//	srand((unsigned)time( NULL ));
//	int	ValueKey = rand();
//
//	StrResult.Format(_T("1&nbsp['%d','%d','%d','%s','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%d','%d','%d','%s']"),
//		ValueKey,							//虚拟标示符
//		Bt_MessageInfo->manager.nShowAsIcon,//显示方式：图片图标
//		Bt_MessageInfo->manager.nRunIsMode,//运行游戏后最小化或隐藏
//		Bt_MessageInfo->manager.wszSkinFileName,//皮肤文件
//		Bt_MessageInfo->manager.wszBgFileName,	//背景文件
//		nPicSpacingX,						//图片间距X
//		nPicSpacingY,						//图片间距Y
//		nNormalIconSpacingX,				//标准图标间距X
//		nNormalIconSpacingY,				//标准图标间距Y
//		nSmallIconSpacingX,					//经典图标间距X
//		nSmallIconSpacingY,					//经典图标间距Y
//		nBigIconSpacingX,					//超大图标间距X
//		nBigIconSpacingY,					//超大图标间距Y
//		Bt_MessageInfo->manager.nHideGameTools,//隐藏辅助工具
//		Bt_MessageInfo->manager.nHideCallBoard,//隐藏公告板
//		wszQQ_ExeBuffer,//QQ文件
//		wszMusic_ExeBuffer,//千千静听文件
//		Bt_MessageInfo->manager.wszCustomName1,
//		Bt_MessageInfo->manager.wszCustomName2,
//		Bt_MessageInfo->manager.wszCustomName3,
//		Bt_MessageInfo->manager.wszCustomName4,
//		wszCustomExe1Buffer,
//		wszCustomExe2Buffer,
//		wszCustomExe3Buffer,
//		wszCustomExe4Buffer,
//		wszNetwork_DiskBuffer,//网游主路径
//		wszTools_DiskBuffer,//辅助工具磁盘
//		Bt_MessageInfo->dwMenuStyle,//游戏菜单风格(0:经典版,1:卡通版,2:传奇版)
//		Bt_MessageInfo->dwClassTemplate,//游戏大类模板(0:无模板 1~3默认模板一二三,4自定义模板)
//		ShowMode1,//是否弹出公告板
//		ShowMode2,//是否弹出公告板??????????????????????
//		Bt_MessageInfo->manager.wszShowBoardText);//公告板文本
//	pAppMain->m_StorageStrct.SaveStorageStruct(ValueKey,Bt_MessageInfo);
//	return StrResult;
//}
//
//CString	CBt::SetBtGameInfo(MENU_CONFIG *pMenu_Manager)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(MENU_MANAGER);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_SET_MENU_CONFIG;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pMenu_Manager,sizeof(MENU_MANAGER));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	StrResult.Format(_T("1&nbsp"));
//	return	StrResult;
//}
//
//CString	CBt::GetBtSystemInfo()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_BT_SYSTEM_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	BT_SYSTEM_INFO	BtSystem;
//	iSocketRet = Receive(&BtSystem,sizeof(BT_SYSTEM_INFO));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp['%ld','%ld','%ld','%ld','%d','%d','%d','%ld','%ld','%I64d','%ld','%I64d','%ld']"),
//		BtSystem.dwDownloads,
//		BtSystem.dwLimitDownloads,
//		BtSystem.dwWaitDownloads,
//		BtSystem.dwTimePeriodLimitSpeed,
//		BtSystem.bTimePeriodLimitSpeed,
//		BtSystem.bPortUPNP,
//		BtSystem.iLine,
//		BtSystem.dwDownloadSpeed,
//		BtSystem.dwTotalGames,
//		BtSystem.ulTotalGameSize,
//		BtSystem.dwLocalGames,
//		BtSystem.ulLocalGameSize,
//		BtSystem.dwLocalHaveUpdateGames);
//	return StrResult;
//}
//
//CString	CBt::GetResourcesInfo()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_RESOURCE_NUMBER;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	BT_RESOURCE_NUMBER	BtResources;
//	iSocketRet = Receive(&BtResources,sizeof(BT_SYSTEM_INFO));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp['%d','%d','%d','%d','%d','%d','%d','%d','%d','%I64d','%I64d','%I64d']"),
//		BtResources.nNetResource,
//		BtResources.nTodayUpdate,
//		BtResources.nHaveUpdate,
//		BtResources.nUndownload,
//		BtResources.nNew,
//		BtResources.nStopUpdate,
//		BtResources.nLocal,
//		BtResources.nNetGame,
//		BtResources.nDiskGame,
//		BtResources.ulNetGameSize,
//		BtResources.ulDiskGameSize,
//		BtResources.ulResourceSize);
//	return StrResult;
//}
//
//CString	CBt::ClearGameFileAndDir(int		GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_CLEAR_FILEDIR;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&GameId,sizeof(int));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	StrResult.Format(_T("1&nbsp"));
//	return	StrResult;
//}
//
//CString	CBt::MoveGame(GAME_MOVE_DIRECTORY*	pGameDirInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(GAME_MOVE_DIRECTORY);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_MOVE_DIRECTORY;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pGameDirInfo,sizeof(GAME_MOVE_DIRECTORY));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	StrResult.Format(_T("1&nbsp"));
//	return	StrResult;
//}
//
//CString	CBt::RegUserLogin(CString StrUserName, CString StrPassWord)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += 64 * sizeof(wchar_t);
//	dwMemory += 32 * sizeof(wchar_t);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.uCommand = COMMAND_LOGIN;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	LOGING_USERPSW	LoginInfo = { 0 };
//	lstrcpy(LoginInfo.wszUserName,StrUserName.GetBuffer());
//	lstrcpy(LoginInfo.wszPassword,StrPassWord.GetBuffer());
//	
//	byte*	pSendBuffer = new	byte[dwMemory];
//	byte*	pTempBuffer = pSendBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&LoginInfo,sizeof(LOGING_USERPSW));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//
//	struct timeval tv_out;
//	tv_out.tv_sec = 1000 * 60 * 10;
//	tv_out.tv_usec = 0;
//	setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));
//	
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//		return StrResult;
//	}
//	UI_LOGIN_REPLY	Bt_User_Info = { 0 };
//	iSocketRet = Receive(&Bt_User_Info,sizeof(UI_LOGIN_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp['%s','%s','%d','%ld','%d','%s']"),
//		Bt_User_Info.wszNetbarName,
//		Bt_User_Info.wszAgentName,
//		Bt_User_Info.wDay,
//		Bt_User_Info.dwLoginStatus,
//		Bt_User_Info.wUserStatus,
//		Bt_User_Info.wszUserName);
//	return	StrResult;
//}
//
//int		CBt::LoadNewGame(RESOURCE_PROPERTY*	pNewGame,char*	pDataBuffer)
//{
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[260] = { 0 };
//	char*	pPos = NULL;
//	pPos = strstr(pDataBuffer,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//		CString	StrGameId(szBuffer);
//		lstrcpy(pNewGame->gi.wszGame_Id,StrGameId.GetBuffer());
//		pDataBuffer += strlen(szBuffer);
//		pDataBuffer += iSeparate;
//		memset(szBuffer,0,260);
//		pPos = strstr(pDataBuffer,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//			TCHAR	wzsBufferName[64] = { 0 };
//			CChineseCode::Utf8ToUniCode(szBuffer,wzsBufferName);
//			lstrcpy(pNewGame->gi.wszGame_Text,wzsBufferName);
//			pDataBuffer += strlen(szBuffer);
//			pDataBuffer += iSeparate;
//			memset(szBuffer,0,260);
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				pNewGame->gi.dwGameSize = atol(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					TCHAR	wzsGameDirBuffer[64] = { 0 };
//					CChineseCode::Utf8ToUniCode(szBuffer,wzsGameDirBuffer);
//					lstrcpy(pNewGame->gi.wszGame_Reg,wzsGameDirBuffer);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					memset(szBuffer,0,260);
//					pPos = strstr(pDataBuffer,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//						TCHAR	wzsGameExeBuffer[64] = { 0 };
//						CChineseCode::Utf8ToUniCode(szBuffer,wzsGameExeBuffer);
//						lstrcpy(pNewGame->gi.wszGame_Path,wzsGameExeBuffer);
//						pDataBuffer += strlen(szBuffer);
//						pDataBuffer += iSeparate;
//						memset(szBuffer,0,260);
//						pPos = strstr(pDataBuffer,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//							CString	StrGame_Exe_Param(szBuffer);
//							lstrcpy(pNewGame->gi.wszGame_Exe_Param,StrGame_Exe_Param.GetBuffer());
//							pDataBuffer += strlen(szBuffer);
//							pDataBuffer += iSeparate;
//							memset(szBuffer,0,260);
//							pPos = strstr(pDataBuffer,"&nbsp");
//							if (pPos)
//							{
//								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//								TCHAR	lpwzsURL[32] = { 0 };
//								CChineseCode::Utf8ToUniCode(szBuffer,pNewGame->gi.wszGame_URL);
//								pDataBuffer += strlen(szBuffer);
//								pDataBuffer += iSeparate;
//								memset(szBuffer,0,260);
//								pPos = strstr(pDataBuffer,"&nbsp");
//								if (pPos)
//								{
//									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//									CString	StrGame_Abc(szBuffer);
//									lstrcpy(pNewGame->gi.wszGame_Abc,StrGame_Abc.GetBuffer());
//									pDataBuffer += strlen(szBuffer);
//									pDataBuffer += iSeparate;
//									memset(szBuffer,0,260);
//									pPos = strstr(pDataBuffer,"&nbsp");
//									if (pPos)
//									{
//										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//										CString	StrGame_Class(szBuffer);
//										lstrcpy(pNewGame->gi.wszClass,StrGame_Class.GetBuffer());
//										pDataBuffer += strlen(szBuffer);
//										pDataBuffer += iSeparate;
//										memset(szBuffer,0,260);
//										pPos = strstr(pDataBuffer,"&nbsp");
//										if (pPos)
//										{
//											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//											pNewGame->gi.dwTopGrade = atoi(szBuffer);
//											pDataBuffer += strlen(szBuffer);
//											pDataBuffer += iSeparate;
//											memset(szBuffer,0,260);
//											pPos = strstr(pDataBuffer,"&nbsp");
//											if (pPos)
//											{
//												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//												pNewGame->gi.dwOSType = atoi(szBuffer);
//												pDataBuffer += strlen(szBuffer);
//												pDataBuffer += iSeparate;
//												memset(szBuffer,0,260);
//												pPos = strstr(pDataBuffer,"&nbsp");
//												if (pPos)
//												{
//													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//													TCHAR	lpwzsGameSave[128] = { 0 };
//													CChineseCode::Utf8ToUniCode(szBuffer,pNewGame->gi.wszGame_Save);
//													pDataBuffer += strlen(szBuffer);
//													pDataBuffer += iSeparate;
//													memset(szBuffer,0,260);
//													pPos = strstr(pDataBuffer,"&nbsp");
//													if (pPos)
//													{
//														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//														pNewGame->gi.dwRunMode = atoi(szBuffer);
//														pDataBuffer += strlen(szBuffer);
//														pDataBuffer += iSeparate;
//														memset(szBuffer,0,260);
//														pPos = strstr(pDataBuffer,"&nbsp");
//														if (pPos)
//														{
//															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//															pNewGame->gi.dwGame_Show = atoi(szBuffer);
//															pDataBuffer += strlen(szBuffer);
//															pDataBuffer += iSeparate;
//															memset(szBuffer,0,260);
//															pPos = strstr(pDataBuffer,"&nbsp");
//															if (pPos)
//															{
//																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//																CChineseCode::Utf8ToUniCode(szBuffer,pNewGame->gi.wszGame_Only);
//																pDataBuffer += strlen(szBuffer);
//																pDataBuffer += iSeparate;
//																memset(szBuffer,0,260);
//																pPos = strstr(pDataBuffer,"&nbsp");
//																if (pPos)
//																{
//																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//																	CChineseCode::Utf8ToUniCode(szBuffer,pNewGame->wszAllGroupName);
//																	pDataBuffer += strlen(szBuffer);
//																	pDataBuffer += iSeparate;
//																	memset(szBuffer,0,260);
//																	return 1;
//																}
//															}
//														}
//													}
//												}
//											}
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//CString	CBt::Game_Operation(int nFlag, RESOURCE_PROPERTY*	pNewGame)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(RESOURCE_PROPERTY);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	switch (nFlag)
//	{
//	case	0:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_GAME_CUSTOM_ADD;
//			break;
//		}
//	case	1:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_CUSTOM_GAME_MODIFY_PROPERTY;
//			break;
//		}
//	}
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pSendBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pNewGame,sizeof(RESOURCE_PROPERTY));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString	CBt::GetGameCustomId()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GAME_CUSTOM_MAXID;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	int CustomCustomId;
//	iSocketRet = Receive(&CustomCustomId,sizeof(int));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),CustomCustomId);
//	return StrResult;
//}
//
//CString	CBt::UpdateBt()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_SYNC_DATA;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp无法和BT服务器通信"));
//		return StrResult;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString	CBt::GetTaskTracke(int GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(int);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GET_TASK_TRACKER_INFO;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pSendBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&GameId,sizeof(int));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	TASK_TRACKER_INFO	Task_Tracker = { 0 };
//	iSocketRet = Receive(&Task_Tracker,sizeof(TASK_TRACKER_INFO));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Task_Tracker.url == '\0')
//	{
//		StrResult.Format(_T("获取Tracker连接失败。[%d]"),Task_Tracker.trackerError);
//	}
//	else
//	{
//		CString	StrUrl(Task_Tracker.url);
//		CString	StrMessage(Task_Tracker.message);
//		StrResult.Format(_T("%s [error:%d %s][%s%s]"),
//			StrUrl,
//			Task_Tracker.trackerError,
//			StrMessage,
//			Task_Tracker.announcing ? _T("当前正在连接中…… ") : _T(""),
//			Task_Tracker.haveResponsed ? _T("收到回复") : _T("未收到回复"));
//	}
//	return StrResult;
//}
//
//int		CBt::GetGameGroup(CStringArray&	GroupList)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_GAME_GROUP;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	int		nMunber = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pbBuffer = new byte[nMunber];
//	byte*	pTemp = pbBuffer;
//	int		nCount = 0;
//	while (nCount != nMunber)
//	{
//		iSocketRet = Receive(pTemp,sizeof(GameGroupInfo));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			return -1;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	
//	GameGroupInfo*	pGameGroupInfo = (GameGroupInfo*)pbBuffer;
//	for (int i = 0; i < 32; i++)
//	{
//		CString	StrData;
//		StrData.Format(_T("'%s',"),pGameGroupInfo->wszGroupName[i]);
//		GroupList.Add(StrData);
//	}
//	delete	[]pbBuffer;
//	return GroupList.GetCount();
//}
//
//int		CBt::LoadGemeGroup(GameGroupInfo*	pGameGroupInfo,char*	pBtGoupData)
//{
//	int iSeparate = strlen("&nbsp");
//	char*	pPos = NULL;
//	char	szBuffer[16] = { 0 };
//	wchar_t	wzsBuffer[16] = { 0 };
//	for (int i = 0; i < 32; i++)
//	{
//		pPos = strstr(pBtGoupData,"&nbsp");
//		if (pPos == NULL)
//		{
//			return 0;
//		}
//		memcpy(szBuffer,pBtGoupData,pPos - pBtGoupData);
//		CChineseCode::Utf8ToUniCode(szBuffer,wzsBuffer);
//		lstrcpy(pGameGroupInfo->wszGroupName[i],wzsBuffer);
//		pBtGoupData += strlen(szBuffer);
//		pBtGoupData += iSeparate;
//		memset(szBuffer,0,16);
//		memset(wzsBuffer,0,16 * sizeof(wchar_t));
//	}
//	return 1;
//}
//
//CString	CBt::SetGameGroup(GameGroupInfo*	pGameGroupInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(GameGroupInfo);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_SET_GAME_GROUP;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,pGameGroupInfo,sizeof(GameGroupInfo));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//int		CBt::GetWkstationGroup(QUERY_PARAM_WORKSTATION*	pParam_Workstation, CStringArray&	GroupWks)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(QUERY_PARAM_WORKSTATION);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GET_GROUP_WORKSTATION;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,pParam_Workstation,sizeof(QUERY_PARAM_WORKSTATION));
//
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//	int		nLen = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pRecvBuffer = new byte[nLen];
//	byte*	pTempRecv = pRecvBuffer;
//	for (int i = 0; i != nLen; )
//	{
//		iSocketRet = Receive(pTempRecv,sizeof(T_WorkstationInfo));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pRecvBuffer;
//			return -1;
//		}
//		pTempRecv += iSocketRet;
//		i += iSocketRet;
//	}
//
//	CMzd*	pMzd = new	CMzd;
//	pMzd->Init(pAppMain->m_MZD_IpAddress,pAppMain->m_MZD_Port);
//	if (!pMzd->ConnectServer())
//	{
//		delete	[]pRecvBuffer;
//		return -1;
//	}
//	int nMzdSocket = 0;
//	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
//	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Mzd_Quest_Head.uCommand = MZD_GET_ALL_WKS_EX_MSG;
//	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
//	nMzdSocket = pMzd->Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		delete	[]pRecvBuffer;
//		return -1;
//	}
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
//	iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		delete	[]pRecvBuffer;
//		return -1;
//	}
//	if (Mzd_Reply_Head.iErrorCode != NULL)
//	{
//		return -1;
//	}
//
//	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pbBuffer = (byte*)GlobalAlloc(GPTR,DataSizeof);
//	byte*	pTemp = pbBuffer;
//	DWORD	dwCumulative = 0;
//	while (dwCumulative != DataSizeof)
//	{
//		iSocketRet = pMzd->Receive(pTemp,sizeof(_tagWkstationEx));
//		if (iSocketRet == SOCKET_ERROR)
//		{
//			delete	[]pRecvBuffer;
//			delete []pbBuffer;
//			return -1;
//		}
//		dwCumulative += iSocketRet;
//		pTemp += iSocketRet;
//	}
//	//tagWkstationEx*	pWkstation = (tagWkstationEx*)pbBuffer;
//
//	T_WorkstationInfo*	pGroupList = (T_WorkstationInfo*)pRecvBuffer;
//	for (int ii = 0; ii < Bt_Reply_Head.dwCount; ii++)
//	{
//		tagWkstationEx*	pWkstation = (tagWkstationEx*)pbBuffer;
//		CString	StrData;
//		for (int u = 0; u < Mzd_Reply_Head.dwCount; u++)
//		{
//			if (pGroupList->dwID == pWkstation->wksNumber)
//			{
//				CString	strWksName(pWkstation->wksName);
//				CString	strWksIp(pWkstation->wksIp);
//				CString	strWksMac(pWkstation->wksMac);
//				CString	strWksMask(pWkstation->subMask);
//				CString	strWksGateway(pWkstation->gateway);
//				CString	strWksScrRes(pWkstation->scrRes);
//				CString	strPre(pWkstation->comPre);
//				CString	strAfx(pWkstation->comAfx);
//				CString strDns1(pWkstation->dns1);
//				CString strDns2(pWkstation->dns2);
//				CString	strStartServerIp(pWkstation->startServerIp);
//
//				TCHAR	strWksMenuDisplay1[64] = { 0 };
//				TCHAR	strWksMenuDisplay2[64] = { 0 };
//				TCHAR	strWksMenuDisplay3[64] = { 0 };
//				TCHAR	strWksMenuDisplay4[64] = { 0 };
//
//				TCHAR	strWksMenName1[4][64] = { 0 };
//				TCHAR	strWksMenName2[4][64] = { 0 };
//				TCHAR	strWksMenName3[4][64] = { 0 };
//				TCHAR	strWksMenName4[4][64] = { 0 };
//
//				CChineseCode::AsciiToUnicode(strWksMenuDisplay1,pWkstation->menuGroup[0].diskName[0]);
//				CChineseCode::AsciiToUnicode(strWksMenuDisplay2,pWkstation->menuGroup[1].diskName[1]);
//				CChineseCode::AsciiToUnicode(strWksMenuDisplay3,pWkstation->menuGroup[2].diskName[2]);
//				CChineseCode::AsciiToUnicode(strWksMenuDisplay4,pWkstation->menuGroup[3].diskName[3]);
//
//				CChineseCode::AsciiToUnicode(strWksMenName1[0],pWkstation->menuGroup[0].diskName[0]);
//				CChineseCode::AsciiToUnicode(strWksMenName1[1],pWkstation->menuGroup[0].diskName[1]);
//				CChineseCode::AsciiToUnicode(strWksMenName1[2],pWkstation->menuGroup[0].diskName[2]);
//				CChineseCode::AsciiToUnicode(strWksMenName1[3],pWkstation->menuGroup[0].diskName[3]);
//
//				CChineseCode::AsciiToUnicode(strWksMenName2[0],pWkstation->menuGroup[1].diskName[0]);
//				CChineseCode::AsciiToUnicode(strWksMenName2[1],pWkstation->menuGroup[1].diskName[1]);
//				CChineseCode::AsciiToUnicode(strWksMenName2[2],pWkstation->menuGroup[1].diskName[2]);
//				CChineseCode::AsciiToUnicode(strWksMenName2[3],pWkstation->menuGroup[1].diskName[3]);
//
//				CChineseCode::AsciiToUnicode(strWksMenName3[0],pWkstation->menuGroup[2].diskName[0]);
//				CChineseCode::AsciiToUnicode(strWksMenName3[1],pWkstation->menuGroup[2].diskName[1]);
//				CChineseCode::AsciiToUnicode(strWksMenName3[2],pWkstation->menuGroup[2].diskName[2]);
//				CChineseCode::AsciiToUnicode(strWksMenName3[3],pWkstation->menuGroup[2].diskName[3]);
//
//				CChineseCode::AsciiToUnicode(strWksMenName4[0],pWkstation->menuGroup[3].diskName[0]);
//				CChineseCode::AsciiToUnicode(strWksMenName4[1],pWkstation->menuGroup[3].diskName[1]);
//				CChineseCode::AsciiToUnicode(strWksMenName4[2],pWkstation->menuGroup[3].diskName[2]);
//				CChineseCode::AsciiToUnicode(strWksMenName4[3],pWkstation->menuGroup[3].diskName[3]);
//
//				TCHAR	lpwzsGroupName[18] = { 0 };
//				CChineseCode::AsciiToUnicode(lpwzsGroupName,pWkstation->groupName);
//
//				CString	StrData;
//				StrData.Format(_T("['%ld','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%d','%d','%d','%s','%s','%s','%s','%s','%d','%d','%d'],"),
//					pWkstation->wksNumber,
//					strWksName,
//					strWksIp,
//					strWksMac,
//					strWksMask,
//					strWksGateway,
//					strWksScrRes,
//					lpwzsGroupName,
//					pWkstation->numberLength,
//					strWksMenuDisplay1,
//					strWksMenName1[0],
//					strWksMenName1[1],
//					strWksMenName1[2],
//					strWksMenName1[3],
//					strWksMenuDisplay2,
//					strWksMenName2[0],
//					strWksMenName2[1],
//					strWksMenName2[2],
//					strWksMenName2[3],
//					strWksMenuDisplay3,
//					strWksMenName3[0],
//					strWksMenName3[1],
//					strWksMenName3[2],
//					strWksMenName3[3],
//					strWksMenuDisplay4,
//					strWksMenName4[0],
//					strWksMenName4[1],
//					strWksMenName4[2],
//					strWksMenName4[3],
//					pWkstation->startMode,
//					pWkstation->LocalMemoryCache,
//					pWkstation->bStartHotBack,
//					pWkstation->bAutoRestore,
//					strPre,
//					strAfx,
//					strDns1,
//					strDns2,
//					strStartServerIp,
//					pWkstation->bSuperMode,
//					pWkstation->bOnlineStatus,
//					pWkstation->bForbidStatus);
//				GroupWks.Add(StrData);
//			}
//			pWkstation++;
//		}
//		pGroupList++;
//	}
//	pMzd->Close();
//	delete pMzd;
//	delete	[]pRecvBuffer;
//	GlobalFree(pbBuffer);
//	return GroupWks.GetCount();
//}
//
//int		CBt::LoadWksGameGroup(SET_WORKSTATION_PROPERTY* pWksGroup,char* pBtData)
//{
//	int iSeparate = strlen("&nbsp");
//	char*	pPos = NULL;
//	char	szBuffer[576] = { 0 };
//	wchar_t	wzsBuffer[576] = { 0 };
//	pPos = strstr(pBtData,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pBtData,pPos - pBtData);
//		pWksGroup->dwComputerID = atol(szBuffer);
//		pBtData += strlen(szBuffer);
//		pBtData += iSeparate;
//		memset(szBuffer,0,576);
//		pPos = strstr(pBtData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pBtData,pPos - pBtData);
//			CChineseCode::Utf8ToUniCode(szBuffer,pWksGroup->wszComputerName);
//			pBtData += strlen(szBuffer);
//			pBtData += iSeparate;
//			memset(szBuffer,0,576);
//			pPos = strstr(pBtData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pBtData,pPos - pBtData);
//				CChineseCode::Utf8ToUniCode(szBuffer,pWksGroup->wszIP);
//				pBtData += strlen(szBuffer);
//				pBtData += iSeparate;
//				memset(szBuffer,0,576);
//				pPos = strstr(pBtData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pBtData,pPos - pBtData);
//					CChineseCode::Utf8ToUniCode(szBuffer,pWksGroup->wszMAC);
//					pBtData += strlen(szBuffer);
//					pBtData += iSeparate;
//					memset(szBuffer,0,576);
//					pPos = strstr(pBtData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pBtData,pPos - pBtData);
//						CChineseCode::Utf8ToUniCode(szBuffer,pWksGroup->wszAllGroupName);
//						pBtData += strlen(szBuffer);
//						pBtData += iSeparate;
//						memset(szBuffer,0,576);
//						return 1;
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//CString		CBt::SetWksGameGroup(SET_WORKSTATION_PROPERTY*	pWksGroup)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(SET_WORKSTATION_PROPERTY);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_SET_WORKSTATION_PROPERTY;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,pWksGroup,sizeof(SET_WORKSTATION_PROPERTY));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString		CBt::GetWksGroupInfo(COMMAND_PARAM_GET_WORKSTATION_PROPERTY*	pWksGroupInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(COMMAND_PARAM_GET_WORKSTATION_PROPERTY);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GET_WORKSTATION_PROPERTY;
//	Bt_Quest_Head.dwCount = 1;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,pWksGroupInfo,sizeof(COMMAND_PARAM_GET_WORKSTATION_PROPERTY));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	SET_WORKSTATION_PROPERTY	WksGroupInfo;
//	iSocketRet = Receive(&WksGroupInfo,sizeof(SET_WORKSTATION_PROPERTY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp['%s','%s','%s','%s']"),
//		WksGroupInfo.wszComputerName,
//		WksGroupInfo.wszIP,
//		WksGroupInfo.wszMAC,
//		WksGroupInfo.wszAllGroupName);
//	return	StrResult;
//}
//
//CString	CBt::GetDiskPartition()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_DISK_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,sizeof(DISK_INFO));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			StrResult.Format(_T("0&nbsp错误,长度%d"),nCount);
//			return StrResult;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	CString	Str = _T("1&nbsp[");
//	DISK_INFO*	pDisk = (DISK_INFO*)pReceiveBuffer;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		TCHAR	lpwszDisk[12] = { 0 };
//		AddChar(pDisk->wszDisk,lpwszDisk,12);
//		TCHAR	lpwszVolumnInfo[64] = { 0 };
//		AddChar(pDisk->wszVolumnInfo,lpwszVolumnInfo,64);
//		CString	StrData;
//		StrData.Format(_T("['%s','%s','%d','%I64d','%I64d'],"),
//			lpwszDisk,
//			lpwszVolumnInfo,
//			pDisk->uDiskType,
//			pDisk->ulTotal,
//			pDisk->ulRemaining);
//		Str += StrData;
//		pDisk++;
//	}
//	delete	[]pReceiveBuffer;
//	StrResult = Str.Left(Str.GetLength() - 1);
//	StrResult += _T("]");
//	return	StrResult;
//}
//
//CString	CBt::GetDiskToFile(CString Path)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(TCHAR) * (Path.GetLength() + 1);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GET_FILE_DIRECTORY_INFO;
//	Bt_Quest_Head.dwCount = 1;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memset(pSendBuffer,0,dwMemory);
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,Path.GetBuffer(),sizeof(TCHAR) * Path.GetLength());
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,1024);
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			StrResult.Format(_T("0&nbsp错误"));
//			return StrResult;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	if (Bt_Reply_Head.dwCount == NULL)
//	{
//		StrResult.Format(_T("1&nbsp"));
//		return StrResult;
//	}
//	CString	Str = _T("1&nbsp[");
//	SOCK_FILE_DIRECTORY*	pDiskFile = (SOCK_FILE_DIRECTORY*)pReceiveBuffer;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		TCHAR	lpwszName[128] = { 0 };
//		AddChar(pDiskFile->wszName,lpwszName,128);
//		CString	StrData;
//		StrData.Format(_T("['%d','%s'],"),
//			pDiskFile->bIsFile,
//			lpwszName);
//		Str += StrData;
//		pDiskFile++;
//	}
//	delete	[]pReceiveBuffer;
//	StrResult = Str.Left(Str.GetLength() - 1);
//	StrResult += _T("]");
//	return	StrResult;
//}
//
//CString		CBt::GetDirInfo(CString	Path)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(TCHAR) * (Path.GetLength() + 1);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GET_FILE_DIRECTORY_PROPERTY;
//	Bt_Quest_Head.dwCount = 1;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memset(pSendBuffer,0,dwMemory);
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,Path.GetBuffer(),sizeof(TCHAR) * Path.GetLength());
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,1024);
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			StrResult.Format(_T("0&nbsp错误"));
//			return StrResult;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	FILE_DIRECTORY_PROPERTY*	pDirInfo = (FILE_DIRECTORY_PROPERTY*)pReceiveBuffer;
//
//	StrResult.Format(_T("1&nbsp['%d','%d','%d','%I64d']"),
//		pDirInfo->bDirectory,
//		pDirInfo->dwFileCount,
//		pDirInfo->dwDirectory,
//		pDirInfo->ulTotalSize);
//
//	delete	[]pReceiveBuffer;
//	return	StrResult;
//}
//
//int			CBt::Load_Simple_Property(GAME_SIMPLE_PROPERTY*	pSimpleProperty, char*	pData)
//{
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[576] = { 0 };
//	char*	pPos = strstr(pData,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pData,pPos - pData);
//		pSimpleProperty->dwGame_Id = atoi(szBuffer);
//		pData += strlen(szBuffer);
//		pData += iSeparate;
//		memset(szBuffer,0,576);
//		char*	pPos = strstr(pData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pData,pPos - pData);
//			pSimpleProperty->dwIsPlan = atoi(szBuffer);
//			pData += strlen(szBuffer);
//			pData += iSeparate;
//			memset(szBuffer,0,576);
//			char*	pPos = strstr(pData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pData,pPos - pData);
//				pSimpleProperty->dwClearFile = atoi(szBuffer);
//				pData += strlen(szBuffer);
//				pData += iSeparate;
//				memset(szBuffer,0,576);
//				char*	pPos = strstr(pData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pData,pPos - pData);
//					pSimpleProperty->dwTopGrade = atoi(szBuffer);
//					pData += strlen(szBuffer);
//					pData += iSeparate;
//					memset(szBuffer,0,576);
//					char*	pPos = strstr(pData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pData,pPos - pData);
//						pSimpleProperty->dwGroupMode = atoi(szBuffer);
//						pData += strlen(szBuffer);
//						pData += iSeparate;
//						memset(szBuffer,0,576);
//						char*	pPos = strstr(pData,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pData,pPos - pData);
//							CChineseCode::Utf8ToUniCode(szBuffer,pSimpleProperty->wszDirectory);
//							pData += strlen(szBuffer);
//							pData += iSeparate;
//							memset(szBuffer,0,576);
//							char*	pPos = strstr(pData,"&nbsp");
//							if (pPos)
//							{
//								memcpy(szBuffer,pData,pPos - pData);
//								CChineseCode::Utf8ToUniCode(szBuffer,pSimpleProperty->wszGroupName);
//								pData += strlen(szBuffer);
//								pData += iSeparate;
//								memset(szBuffer,0,576);
//								return 1;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//CString	CBt::AutoUpdate(int GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(int);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_SET_AUTO_UPDATE;
//	Bt_Quest_Head.dwCount = 1;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memset(pSendBuffer,0,dwMemory);
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,&GameId,sizeof(int));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString	CBt::ManualUpdate(int GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(int);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_SET_MANUAL_UPDATE;
//	Bt_Quest_Head.dwCount = 1;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memset(pSendBuffer,0,dwMemory);
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,&GameId,sizeof(int));
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString		CBt::PropertyAddTask(GAME_SIMPLE_PROPERTY*	pSimpleProperty)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(GAME_SIMPLE_PROPERTY);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_TASK_PROPERTY_ADD;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pSimpleProperty,sizeof(GAME_SIMPLE_PROPERTY));
//	pTempBuffer += sizeof(GAME_SIMPLE_PROPERTY);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString		CBt::GetGame(int	GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_CUSTOM_GAME_GET_PROPERTY;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&GameId,sizeof(int));
//	pTempBuffer += sizeof(int);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,sizeof(RESOURCE_PROPERTY));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			StrResult.Format(_T("0&nbsp错误"));
//			return StrResult;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	RESOURCE_PROPERTY*	pResource = (RESOURCE_PROPERTY*)pReceiveBuffer;
//	TCHAR	lpwzsGamePath[128] = { 0 };
//	AddChar(pResource->gi.wszGame_Reg,lpwzsGamePath,128);
//
//	TCHAR	lpwzsGameExe[64] = { 0 };
//	AddChar(pResource->gi.wszGame_Path,lpwzsGameExe,64);
//
//	TCHAR	lpwzsGameParam[128] = { 0 };
//	AddChar(pResource->gi.wszGame_Exe_Param,lpwzsGameParam,128);
//
//	TCHAR	lpwzsGameURL[32] = { 0 };
//	AddChar(pResource->gi.wszGame_URL,lpwzsGameURL,32);
//
//	TCHAR	lpwzsGameSave[128] = { 0 };
//	AddChar(pResource->gi.wszGame_Save,lpwzsGameSave,128);
//
//	StrResult.Format(_T("1&nbsp['%s','%s','%d','%s','%s','%s','%s','%s','%s','%d','%d','%s','%d','%d','%s','%s']"),
//		pResource->gi.wszGame_Id,
//		pResource->gi.wszGame_Text,
//		pResource->gi.dwGameSize,
//		lpwzsGamePath,
//		lpwzsGameExe,
//		lpwzsGameParam,
//		lpwzsGameURL,
//		pResource->gi.wszGame_Abc,
//		pResource->gi.wszClass,
//		pResource->gi.dwTopGrade,
//		pResource->gi.dwOSType,
//		lpwzsGameSave,
//		pResource->gi.dwRunMode,
//		pResource->gi.dwGame_Show,
//		pResource->gi.wszGame_Only,
//		pResource->wszAllGroupName);
//	return	StrResult;
//}
//
//CString		CBt::DeleteGame(int GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_CUSTOM_GAME_DELETE;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&GameId,sizeof(int));
//	pTempBuffer += sizeof(int);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString	CBt::DownloadGameSSD(int GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_TASK_SSD_ADD;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&GameId,sizeof(int));
//	pTempBuffer += sizeof(int);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString		CBt::FepairGame(int	GameId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(int);
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_REPAIR;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&GameId,sizeof(int));
//	pTempBuffer += sizeof(int);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString	CBt::BeginGameSearch()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GAME_START_SEARCH;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString	CBt::EndGameSearch()
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GAME_END_SEARCH;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return StrResult;
//}
//
//CString		CBt::GetGameSearchInfo(CString	strGamePath)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(TCHAR) * (strGamePath.GetLength() + 1);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_GET_LOCATE;
//	Bt_Quest_Head.dwCount = 1;
//
//	byte*	pSendBuffer = new byte[dwMemory];
//	byte*	pSendTemp = pSendBuffer;
//	memset(pSendBuffer,0,dwMemory);
//	memcpy(pSendTemp,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pSendTemp,strGamePath.GetBuffer(),sizeof(TCHAR) * strGamePath.GetLength());
//
//	CString	StrResult;
//	int iSocketRet;
//	iSocketRet = Send(pSendBuffer,dwMemory);
//	delete []pSendBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return StrResult;
//	}
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,sizeof(GET_GAME_LOCATE_INFO));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			StrResult.Format(_T("0&nbsp错误"));
//			return StrResult;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	GET_GAME_LOCATE_INFO*	pSearchInfo = (GET_GAME_LOCATE_INFO*)pReceiveBuffer;
//	
//	StrResult.Format(_T("1&nbsp['%d','%d','%s']"),
//		pSearchInfo->bSuccess,
//		pSearchInfo->dwID,
//		pSearchInfo->wszGameName);
//	return StrResult;
//}
//
//int		CBt::LoadSearchStatus(GET_GAME_LOCATE_STATUS_REQUEST*	pStatus, char*	pBuffer)
//{
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[128] = { 0 };
//	char*	pPos = strstr(pBuffer,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pBuffer,pPos - pBuffer);
//		pStatus->iMode = atoi(szBuffer);
//		pBuffer += strlen(szBuffer);
//		pBuffer += iSeparate;
//		memset(szBuffer,0,128);
//		pPos = strstr(pBuffer,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pBuffer,pPos - pBuffer);
//			pStatus->dwID = atol(szBuffer);
//			pBuffer += strlen(szBuffer);
//			pBuffer += iSeparate;
//			memset(szBuffer,0,128);
//			pPos = strstr(pBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pBuffer,pPos - pBuffer);
//				CChineseCode::Utf8ToUniCode(szBuffer,pStatus->wszDirectory);
//				pBuffer += strlen(szBuffer);
//				pBuffer += iSeparate;
//				memset(szBuffer,0,128);
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
//CString		CBt::GetSearchStatus(GET_GAME_LOCATE_STATUS_REQUEST*	pStatus)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(GET_GAME_LOCATE_STATUS_REQUEST);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_GET_LOCATE_STATUS;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pStatus,sizeof(GET_GAME_LOCATE_STATUS_REQUEST));
//	pTempBuffer += sizeof(GET_GAME_LOCATE_STATUS_REQUEST);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	int		nErrorMessage;
//	iSocketRet = Receive(&nErrorMessage,sizeof(int));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),nErrorMessage);
//	return	StrResult;
//}
//
//int			CBt::LoadSearchInfo(SET_GAME_LOCATE_INFO*	pSearchInfo, char*	pBuffer)
//{
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[128] = { 0 };
//	char*	pPos = strstr(pBuffer,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pBuffer,pPos - pBuffer);
//		pSearchInfo->dwID = atol(szBuffer);
//		pBuffer += strlen(szBuffer);
//		pBuffer += iSeparate;
//		memset(szBuffer,0,128);
//		pPos = strstr(pBuffer,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pBuffer,pPos - pBuffer);
//			pSearchInfo->iFlag = atol(szBuffer);
//			pBuffer += strlen(szBuffer);
//			pBuffer += iSeparate;
//			memset(szBuffer,0,128);
//			pPos = strstr(pBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pBuffer,pPos - pBuffer);
//				CChineseCode::Utf8ToUniCode(szBuffer,pSearchInfo->wszDirectory);
//				pBuffer += strlen(szBuffer);
//				pBuffer += iSeparate;
//				memset(szBuffer,0,128);
//				return 1;
//			}
//		}
//	}
//	return 0;
//}
//
//CString		CBt::SetSearchInfo(SET_GAME_LOCATE_INFO* pSearchInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(SET_GAME_LOCATE_INFO);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_GAME_SET_LOCATE;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pSearchInfo,sizeof(SET_GAME_LOCATE_INFO));
//	pTempBuffer += sizeof(SET_GAME_LOCATE_INFO);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString		CBt::BtGroup_Operation(int	nFlags, InstDelGroupInfo*	pGroupInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(InstDelGroupInfo);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	switch(nFlags)
//	{
//	case	0:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_INSERT_GROUP;
//			break;
//		}
//	case	1:
//		{
//			Bt_Quest_Head.uCommand = COMMAND_DELETE_GROUP;
//			break;
//		}
//	}
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pGroupInfo,sizeof(InstDelGroupInfo));
//	pTempBuffer += sizeof(InstDelGroupInfo);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString		CBt::BtGroup_Modify(ModifyGroupInfo*	pMGroupInfo)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(ModifyGroupInfo);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_MODIFY_GROUP;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pMGroupInfo,sizeof(ModifyGroupInfo));
//	pTempBuffer += sizeof(ModifyGroupInfo);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//int		CBt::GetMovie(CStringArray&	MovieList)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_MOVIE_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,sizeof(T_Movie));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			return -1;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	T_Movie*	pMovie = (T_Movie*)pReceiveBuffer;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		TCHAR	MoviePath[255] = { 0 };
//		AddChar(pMovie->wszMovie_Path,MoviePath,255);
//
//		CString	strData;
//		strData.Format(_T("['%ld','%s','%s','%s','%s','%s','%ld','%ld'],"),
//			pMovie->dwMovie_Index,
//			MoviePath,
//			pMovie->wszMovie_Disk,
//			pMovie->wszLogin_Name,
//			pMovie->wszLogin_Pass,
//			pMovie->wszMovie_Name,
//			pMovie->dwMovie_Show,
//			pMovie->dwIsDefault);
//		pMovie++;
//		MovieList.Add(strData);
//	}
//	delete []pReceiveBuffer;
//	return MovieList.GetCount();
//}
//
//int		CBt::LoadMovie(int nCount, T_Movie* pMovie, char* pData)
//{
//	int nRet = 0;
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[255] = { 0 };
//	char*	pPos = NULL;
//
//	T_Movie*	p = pMovie;
//
//	for (int i = 0; i < nCount; i++)
//	{
//		pPos = strstr(pData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pData,pPos - pData);
//			pMovie->dwMovie_Index = atol(szBuffer);
//			pData += strlen(szBuffer);
//			pData += iSeparate;
//			memset(szBuffer,0,255);
//			pPos = strstr(pData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pData,pPos - pData);
//				CChineseCode::Utf8ToUniCode(szBuffer,pMovie->wszMovie_Path);
//				pData += strlen(szBuffer);
//				pData += iSeparate;
//				memset(szBuffer,0,255);
//				pPos = strstr(pData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pData,pPos - pData);
//					CChineseCode::Utf8ToUniCode(szBuffer,pMovie->wszMovie_Disk);
//					pData += strlen(szBuffer);
//					pData += iSeparate;
//					memset(szBuffer,0,255);
//					pPos = strstr(pData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pData,pPos - pData);
//						CChineseCode::Utf8ToUniCode(szBuffer,pMovie->wszLogin_Name);
//						pData += strlen(szBuffer);
//						pData += iSeparate;
//						memset(szBuffer,0,255);
//						pPos = strstr(pData,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pData,pPos - pData);
//							CChineseCode::Utf8ToUniCode(szBuffer,pMovie->wszLogin_Pass);
//							pData += strlen(szBuffer);
//							pData += iSeparate;
//							memset(szBuffer,0,255);
//							pPos = strstr(pData,"&nbsp");
//							if (pPos)
//							{
//								memcpy(szBuffer,pData,pPos - pData);
//								CChineseCode::Utf8ToUniCode(szBuffer,pMovie->wszMovie_Name);
//								pData += strlen(szBuffer);
//								pData += iSeparate;
//								memset(szBuffer,0,255);
//								pPos = strstr(pData,"&nbsp");
//								if (pPos)
//								{
//									memcpy(szBuffer,pData,pPos - pData);
//									CChineseCode::Utf8ToUniCode(szBuffer,pMovie->wszMovie_Name);
//									pData += strlen(szBuffer);
//									pData += iSeparate;
//									memset(szBuffer,0,255);
//									pPos = strstr(pData,"&nbsp");
//									if (pPos)
//									{
//										memcpy(szBuffer,pData,pPos - pData);
//										pMovie->dwMovie_Show = atol(szBuffer);
//										pData += strlen(szBuffer);
//										pData += iSeparate;
//										memset(szBuffer,0,255);
//										pPos = strstr(pData,"&nbsp");
//										if (pPos)
//										{
//											memcpy(szBuffer,pData,pPos - pData);
//											pMovie->dwIsDefault = atol(szBuffer);
//											pData += strlen(szBuffer);
//											pData += iSeparate;
//											memset(szBuffer,0,255);
//											p++;
//											nRet++;
//											continue;
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		return 0;
//	}
//	return nRet;
//}
//
//CString	CBt::SetMovie(int nCount, T_Movie* pMovie)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(T_Movie) * nCount;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = nCount;
//	Bt_Quest_Head.uCommand = COMMAND_SET_MOVIE_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//
//	T_Movie*	p = pMovie;
//
//	for (int i = 0; i < nCount; i++)
//	{
//		memcpy(pTempBuffer,p,sizeof(T_Movie));
//		pTempBuffer += sizeof(T_Movie);
//		p++;
//	}
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//int		CBt::GetOnline(CStringArray &OnlineList)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_ONLINE_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,sizeof(T_Online));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			return -1;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	T_Online*	pOnline = (T_Online*)pReceiveBuffer;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		TCHAR	OnlinePath[255] = { 0 };
//		AddChar(pOnline->wszLink,OnlinePath,255);
//
//		CString	strData;
//		strData.Format(_T("['%d','%s','%s','%d','%d'],"),
//			pOnline->dwIdx,
//			OnlinePath,
//			pOnline->wszCaption,
//			pOnline->dwShow,
//			pOnline->dwIsDefault);
//		pOnline++;
//		OnlineList.Add(strData);
//	}
//	delete []pReceiveBuffer;
//	return OnlineList.GetCount();
//}
//
//int		CBt::LoadOnline(int nCount, T_Online* pOnline, char* pData)
//{
//	int nRet = 0;
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[255] = { 0 };
//	char*	pPos = NULL;
//
//	T_Online* p = pOnline;
//
//	for (int i = 0; i < nCount; i++)
//	{
//		pPos = strstr(pData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pData,pPos - pData);
//			pOnline->dwIdx = atoi(szBuffer);
//			pData += strlen(szBuffer);
//			pData += iSeparate;
//			memset(szBuffer,0,255);
//			pPos = strstr(pData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pData,pPos - pData);
//				CChineseCode::Utf8ToUniCode(szBuffer,pOnline->wszLink);
//				pData += strlen(szBuffer);
//				pData += iSeparate;
//				memset(szBuffer,0,255);
//				pPos = strstr(pData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pData,pPos - pData);
//					CChineseCode::Utf8ToUniCode(szBuffer,pOnline->wszCaption);
//					pData += strlen(szBuffer);
//					pData += iSeparate;
//					memset(szBuffer,0,255);
//					pPos = strstr(pData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pData,pPos - pData);
//						pOnline->dwShow = atoi(szBuffer);
//						pData += strlen(szBuffer);
//						pData += iSeparate;
//						memset(szBuffer,0,255);
//						pPos = strstr(pData,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pData,pPos - pData);
//							pOnline->dwIsDefault = atoi(szBuffer);
//							pData += strlen(szBuffer);
//							pData += iSeparate;
//							memset(szBuffer,0,255);
//							p++;
//							nRet++;
//							continue;
//						}
//					}
//				}
//			}
//		}
//		return 0;
//	}
//	return nRet;
//}
//
//CString	CBt::SetOnline(int nCount, T_Online* pOnline)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(T_Online) * nCount;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = nCount;
//	Bt_Quest_Head.uCommand = COMMAND_SET_ONLINE_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//
//	T_Online*	p = pOnline;
//	for (int i = 0; i < nCount; i++)
//	{
//		memcpy(pTempBuffer,p,sizeof(T_Online));
//		pTempBuffer += sizeof(T_Online);
//		p++;
//	}
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//int		CBt::GetPlayer(CStringArray& PlayerList)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	CString	StrResult;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
//	Bt_Quest_Head.uCommand = COMMAND_GET_PLAYER_LIST_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	int iSocketRet;
//	iSocketRet = Send(&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		return -1;
//	}
//	if (Bt_Reply_Head.iErrorCode != SCMD_OK)
//	{
//		return -1;
//	}
//
//	int Total = Bt_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
//	byte*	pReceiveBuffer = new byte[Total];
//	byte*	pTemp = pReceiveBuffer;
//	int		nCount = 0;
//	while (Total != nCount)
//	{
//		iSocketRet = Receive(pTemp,sizeof(T_PlayerList));
//		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//		{
//			delete	[]pReceiveBuffer;
//			return -1;
//		}
//		pTemp += iSocketRet;
//		nCount += iSocketRet;
//	}
//	T_PlayerList*	pPlayer = (T_PlayerList*)pReceiveBuffer;
//	for (int i = 0; i < Bt_Reply_Head.dwCount; i++)
//	{
//		TCHAR	PlayerFile[255] = { 0 };
//		AddChar(pPlayer->wszPlayerFile,PlayerFile,255);
//
//		TCHAR	PlayerExt[255] = { 0 };
//		AddChar(pPlayer->wszPlayerExt,PlayerExt,255);
//
//		CString	strData;
//		strData.Format(_T("['%s','%s','%d'],"),
//			PlayerFile,
//			PlayerExt,
//			pPlayer->dwPlayerType);
//		pPlayer++;
//		PlayerList.Add(strData);
//	}
//	delete []pReceiveBuffer;
//	return PlayerList.GetCount();
//}
//
//int		CBt::LoadPlayer(int nCount, T_PlayerList* pPlayer, char* pData)
//{
//	int nRet = 0;
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[255] = { 0 };
//	char*	pPos = NULL;
//
//	T_PlayerList* p = pPlayer;
//
//	for (int i = 0; i < nCount; i++)
//	{
//		pPos = strstr(pData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pData,pPos - pData);
//			CChineseCode::Utf8ToUniCode(szBuffer,pPlayer->wszPlayerFile);
//			pData += strlen(szBuffer);
//			pData += iSeparate;
//			memset(szBuffer,0,255);
//			pPos = strstr(pData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pData,pPos - pData);
//				CChineseCode::Utf8ToUniCode(szBuffer,pPlayer->wszPlayerExt);
//				pData += strlen(szBuffer);
//				pData += iSeparate;
//				memset(szBuffer,0,255);
//				pPos = strstr(pData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pData,pPos - pData);
//					pPlayer->dwPlayerType = atoi(szBuffer);
//					pData += strlen(szBuffer);
//					pData += iSeparate;
//					memset(szBuffer,0,255);
//					nRet++;
//					p++;
//					continue;
//				}
//			}
//		}
//		return 0;
//	}
//	return nRet;
//}
//
//CString	CBt::SetPlayer(int nCount, T_PlayerList* pPlayer)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(T_Online) * nCount;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = nCount;
//	Bt_Quest_Head.uCommand = COMMAND_SET_PLAYER_LIST_INFO;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//
//	T_PlayerList*	p = pPlayer;
//	for (int i = 0; i < nCount; i++)
//	{
//		memcpy(pTempBuffer,p,sizeof(T_PlayerList));
//		pTempBuffer += sizeof(T_PlayerList);
//		p++;
//	}
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString	CBt::SetServerGroup(SERVER_PROPERTY* pServerGroup)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(SERVER_PROPERTY);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_SET_SERVER_PROPERTY;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pServerGroup,sizeof(SERVER_PROPERTY));
//	pTempBuffer += sizeof(SERVER_PROPERTY);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//int			CBt::LoadServerGroup(SERVER_PROPERTY*	pServerGroup, char*	pData)
//{
//	int nRet = 0;
//	int iSeparate = strlen("&nbsp");
//	char	szBuffer[576] = { 0 };
//	char*	pPos = NULL;
//
//	pPos = strstr(pData,"&nbsp");
//	if (pPos)
//	{
//		memcpy(szBuffer,pData,pPos - pData);
//		CChineseCode::Utf8ToUniCode(szBuffer,pServerGroup->wszComputerName);
//		pData += strlen(szBuffer);
//		pData += iSeparate;
//		memset(szBuffer,0,576);
//		pPos = strstr(pData,"&nbsp");
//		if (pPos)
//		{
//			memcpy(szBuffer,pData,pPos - pData);
//			CChineseCode::Utf8ToUniCode(szBuffer,pServerGroup->wszIP[0]);
//			pData += strlen(szBuffer);
//			pData += iSeparate;
//			memset(szBuffer,0,576);
//			pPos = strstr(pData,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pData,pPos - pData);
//				CChineseCode::Utf8ToUniCode(szBuffer,pServerGroup->wszIP[1]);
//				pData += strlen(szBuffer);
//				pData += iSeparate;
//				memset(szBuffer,0,576);
//				pPos = strstr(pData,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pData,pPos - pData);
//					CChineseCode::Utf8ToUniCode(szBuffer,pServerGroup->wszIP[2]);
//					pData += strlen(szBuffer);
//					pData += iSeparate;
//					memset(szBuffer,0,576);
//					pPos = strstr(pData,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pData,pPos - pData);
//						CChineseCode::Utf8ToUniCode(szBuffer,pServerGroup->wszIP[3]);
//						pData += strlen(szBuffer);
//						pData += iSeparate;
//						memset(szBuffer,0,576);
//						pPos = strstr(pData,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pData,pPos - pData);
//							CChineseCode::Utf8ToUniCode(szBuffer,pServerGroup->wszAllGroupName);
//							pData += strlen(szBuffer);
//							pData += iSeparate;
//							memset(szBuffer,0,576);
//							return 1;
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}
//
//CString	CBt::DeleteWksGroup(int WksId)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += sizeof(int);
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_DELETE_WORKSTATION;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,&WksId,sizeof(int));
//	pTempBuffer += sizeof(SERVER_PROPERTY);
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//CString	CBt::DeleteServerGroup(TCHAR* pServerName)
//{
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//	int nNameLen = sizeof(TCHAR) * 32;
//	DWORD	dwMemory = 0;
//	dwMemory += sizeof(SOCKET_HEAD_REQUEST);
//	dwMemory += nNameLen;
//
//	SOCKET_HEAD_REQUEST	Bt_Quest_Head = { 0 };
//	Bt_Quest_Head.wHead = 1978;
//	Bt_Quest_Head.dwRequestSize = dwMemory;
//	Bt_Quest_Head.dwCount = 1;
//	Bt_Quest_Head.uCommand = COMMAND_DELETE_SERVER;
//	lstrcpy(Bt_Quest_Head.wszPassword,pAppMain->m_CommunicationPassWord.GetBuffer());
//	Bt_Quest_Head.wUIVer = CAppMain::m_Ver;
//
//	byte*	pbBuffer = new byte[dwMemory];
//	byte*	pTempBuffer = pbBuffer;
//	memcpy(pTempBuffer,&Bt_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
//	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
//	memcpy(pTempBuffer,pServerName,nNameLen);
//	pTempBuffer += nNameLen;
//
//	CString	StrResult;
//	int			iSocketRet;
//	iSocketRet = Send(pbBuffer,dwMemory);
//	if (iSocketRet == SOCKET_ERROR)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	delete	[]pbBuffer;
//	Sleep(100);
//	SOCKET_HEAD_REPLY	Bt_Reply_Head;
//	iSocketRet = Receive(&Bt_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
//	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
//	{
//		StrResult.Format(_T("0&nbsp错误"));
//		return StrResult;
//	}
//	StrResult.Format(_T("1&nbsp%d&nbsp"),Bt_Reply_Head.iErrorCode);
//	return	StrResult;
//}
//
//int		CBt::Bt_Message(int iRequestFlag, char *pDataBuffer, CString &StrResult)
//{
// 	int iResult = 0;
//
//	if (!ConnectServer())
//	{
//		StrResult.Format(_T("0&nbsp无法连接BT服务器!"));
//		return 1;
//	}
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	switch (iRequestFlag)
//	{
//	case	COMMAND_GET_LOGIN_INFO:
//		{
//			StrResult = GetLoginInfo(pAppMain->m_CommunicationPassWord,COMMAND_GET_LOGIN_INFO);
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_GAMES_INFO:
//		{
//			CStringArray	GameArray;
//			CString			StrRetData;
//			COMMAND_PARAM	Command;
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			wchar_t	wzsBuffer[64] = { 0 };
//			char*	pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				Command.pgg = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					Command.qt = atoi(szBuffer);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					memset(szBuffer,0,64);
//					pPos = strstr(pDataBuffer,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//						Command.qsc = atoi(szBuffer);
//						pDataBuffer += strlen(szBuffer);
//						pDataBuffer += iSeparate;
//						memset(szBuffer,0,64);
//						pPos = strstr(pDataBuffer,"&nbsp");
//						if (pPos)
//						{
//							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//							Command.iSortItem = atoi(szBuffer);
//							pDataBuffer += strlen(szBuffer);
//							pDataBuffer += iSeparate;
//							memset(szBuffer,0,64);
//							pPos = strstr(pDataBuffer,"&nbsp");
//							if (pPos)
//							{
//								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//								Command.iSortFlag = atoi(szBuffer);
//								pDataBuffer += strlen(szBuffer);
//								pDataBuffer += iSeparate;
//								memset(szBuffer,0,64);
//								pPos = strstr(pDataBuffer,"&nbsp");
//								if (pPos)
//								{
//									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//									CChineseCode::Utf8ToUniCode(szBuffer,wzsBuffer);
//									lstrcpy(Command.wszName,wzsBuffer);
//									pDataBuffer += strlen(szBuffer);
//									pDataBuffer += iSeparate;
//									memset(szBuffer,0,64);
//									int iRet = GetGame_Info(GameArray,&Command);
//									if (iRet == -1)
//									{
//										StrResult.Format(_T("0&nbsp错误。"));
//										iResult = 1;
//										break;
//									}
//									if (iRet == 0)
//									{
//										StrResult.Format(_T("1&nbsp"));
//										iResult = 1;
//										break;
//									}
//									StrRetData += _T("1&nbsp[");
//									for (int i = 0;i < GameArray.GetSize(); i++)
//									{
//										StrRetData += GameArray.GetAt(i);
//									}
//									StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//									StrResult += _T("]");
//									iResult = 1;
//									break;
//								}
//							}
//						}
//					}
//				}
//			}
//			break;
//		}
//	case	COMMAND_GET_DELETE_GAME_SORT:
//		{
//			CStringArray	DeleteGameArray;
//			CString			StrRetData;
//			int iRet = GetDelete_Game_Sort(DeleteGameArray);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < DeleteGameArray.GetSize(); i++)
//			{
//				StrRetData += DeleteGameArray.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_SUPERFLUOUS_GAME_INFO:
//		{
//			CStringArray	SuperGameArray;
//			CString			StrRetData;
//			int iRet = GetSuperFluous_Game(SuperGameArray);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < SuperGameArray.GetSize(); i++)
//			{
//				StrRetData += SuperGameArray.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	FQ_DELETE_SORT_Grade:
//		{
//			CStringArray	SuperGameArray;
//			CString			StrRetData;
//
//			int iRet = GetDelete_Sort_Grade(SuperGameArray,0);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < SuperGameArray.GetSize(); i++)
//			{
//				StrRetData += SuperGameArray.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	FQ_DELETE_SORT_Click:
//		{
//			CStringArray	SuperGameArray;
//			CString			StrRetData;
//
//			int iRet = GetDelete_Sort_Click(SuperGameArray,1);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < SuperGameArray.GetSize(); i++)
//			{
//				StrRetData += SuperGameArray.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_DELETE_SORT:
//		{
//			CDWordArray	SetDeleteSortArray;
//			int iSeparate = strlen("&nbsp");
//			for (int i = 0; ; i++)
//			{
//				char*	pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					char	szBuffer[MAX_PATH] = { 0 };
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					DWORD	Game_ID;
//					Game_ID = atol(szBuffer);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					SetDeleteSortArray.Add(Game_ID);
//					continue;
//				}
//				break;
//			}
//			StrResult = SetDelete_Sort(SetDeleteSortArray);
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_TASKS_INFO:
//		{
//			CStringArray	TaskArray;
//			CString			StrRetData;
//			int iRet = GetTasksList(TaskArray);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < TaskArray.GetSize(); i++)
//			{
//				StrRetData += TaskArray.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	FQ_TASK_SET:
//		{
//			char*	pPos = strstr(pDataBuffer,"&nbsp");
//			int iSeparate = strlen("&nbsp");
//			if (pPos)
//			{
//				char	szBufferId[MAX_PATH] = { 0 };
//				memcpy(szBufferId,pDataBuffer,pPos - pDataBuffer);
//				pDataBuffer += strlen(szBufferId);
//				pDataBuffer += iSeparate;
//				char*	pnPos = strstr(pDataBuffer,"&nbsp");
//				if (pnPos)
//				{
//					char	szBufferFlag[64] = { 0 };
//					memcpy(szBufferFlag,pDataBuffer,pnPos - pDataBuffer);
//					int	nFlag = atoi(szBufferFlag);
//					CString	StrId(szBufferId);
//					StrResult = SetTaskInfo(StrId,nFlag);
//					iResult = 1;
//					break;
//				}
//			}
//			break;
//		}
//	case	COMMAND_GET_TASK_PEER_INFO:
//		{
//			char*	pPos = strstr(pDataBuffer,"&nbsp");
//			int iSeparate = strlen("&nbsp");
//			if (pPos)
//			{
//				char	szBuffer[MAX_PATH] = { 0 };
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				CString	StrId(szBuffer);
//				StrResult = GetPeer_Entry(StrId);
//			}
//			else
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//			}
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_PARENT_CLASS_INFO:
//		{
//			CStringArray	ParentArray;
//			CString			StrRetData;
//			char*	pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				char	szBuffer[32] = { 0 };
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nFlag = atoi(szBuffer);
//				int iRet = GetClass_Parent(ParentArray,nFlag);
//				if (iRet == -1)
//				{
//					StrResult.Format(_T("0&nbsp错误。"));
//					iResult = 1;
//					break;
//				}
//				if (iRet == 0)
//				{
//					StrResult.Format(_T("1&nbsp"));
//					iResult = 1;
//					break;
//				}
//				StrRetData += _T("1&nbsp[");
//				for (int i = 0;i < ParentArray.GetSize(); i++)
//				{
//					StrRetData += ParentArray.GetAt(i);
//				}
//				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//				StrResult += _T("]");
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GET_SUB_CLASS_INFO:
//		{
//			CStringArray	SubArray;
//			CString			StrRetData;
//			int iRet = GetClass_Sub(SubArray);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < SubArray.GetSize(); i++)
//			{
//				StrRetData += SubArray.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_SIMPLE_PROPERTY:
//		{
//			GAME_SIMPLE_PROPERTY	PropertyInfo = { 0 };
//			iResult = Load_Simple_Property(&PropertyInfo,pDataBuffer);
//			if (iResult == NULL)
//			{
//				break;
//			}
//			StrResult = SetSimple_Property(PropertyInfo);
//			break;
//		}
//	case	COMMAND_GET_SIMPLE_PROPERTY:
//		{
//			char*	pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				char	szBuffer[64] = { 0 };
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int iId = atoi(szBuffer);
//				StrResult = GetSimple_Property(iId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	FQ_Operation:
//		{
//			int iSeparate = strlen("&nbsp");
//			char*	pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				char	szBuffer[64] = { 0 };
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int iId = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					int nFlag = atoi(szBuffer);
//					StrResult = OperationSimple_Property(iId,nFlag);
//					iResult = 1;
//					break;
//				}
//			}
//			break;
//		}
//	case	COMMAND_GET_CONFIG:
//		{
//			StrResult = GetBtConfig();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_CONFIG:
//		{
//			CONFIG_INFO	ConfigInfo = { 0 };
//			int iRet = LoadBtConfig(pDataBuffer,&ConfigInfo);
//			if (iRet)
//			{
//				StrResult = SetBtConfig(&ConfigInfo);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GET_MENU_CONFIG:
//		{
//			StrResult = GetBtGameInfo();
//			iResult =1;
//			break;
//		}
//	case	COMMAND_SET_MENU_CONFIG:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			CPtrArray	ParentArray;
//			char* pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int ValueKey = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				MENU_MANAGER*	pMenu_GameManager = (MENU_MANAGER*)pAppMain->m_StorageStrct.GetStorageStruct(ValueKey);
//				if (pMenu_GameManager == NULL)
//				{
//					iResult = 1;
//					StrResult.Format(_T("1&nbsp1001&nbsp"));
//					break;
//				}
//				int iRet = LoadBtGameInfo(pDataBuffer,pMenu_GameManager);
//				if (iRet)
//				{
//					StrResult = SetBtGameInfo(pMenu_GameManager);
//					pAppMain->m_StorageStrct.DeleteStorageStruct(ValueKey);
//					iResult = 1;
//				}
//				break;
//			}
//		}
//	case	COMMAND_SET_PARENT_CLASS_INFO:
//		{
//			int iCount = 0;
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char* pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				iCount = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				T_ClassInfo*	pClassInfo = (T_ClassInfo*)GlobalAlloc(GPTR,sizeof(T_ClassInfo) * iCount);
//				T_ClassInfo*	pTempClassInfo = pClassInfo;
//				for (int i = 0; i < iCount; i++)
//				{
//					char* pDataPos = NULL;
//					pDataPos = strstr(pDataBuffer,"&nbsp");
//					if (pDataPos)
//					{
//						memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//						CChineseCode::Utf8ToUniCode(szBuffer,pTempClassInfo->wszID);
//						pDataBuffer += strlen(szBuffer);
//						pDataBuffer += iSeparate;
//						memset(szBuffer,0,64);
//						pDataPos = strstr(pDataBuffer,"&nbsp");
//						if (pDataPos)
//						{
//							memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//							CChineseCode::Utf8ToUniCode(szBuffer,pTempClassInfo->wszName);
//							pDataBuffer += strlen(szBuffer);
//							pDataBuffer += iSeparate;
//							memset(szBuffer,0,64);
//							pDataPos = strstr(pDataBuffer,"&nbsp");
//							if (pDataPos)
//							{
//								memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//								pTempClassInfo->dwShowIndex = atol(szBuffer);
//								pDataBuffer += strlen(szBuffer);
//								pDataBuffer += iSeparate;
//								memset(szBuffer,0,64);
//								pDataPos = strstr(pDataBuffer,"&nbsp");
//								if (pDataPos)
//								{
//									memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//									pTempClassInfo->dwShow = atol(szBuffer);
//									pDataBuffer += strlen(szBuffer);
//									pDataBuffer += iSeparate;
//									memset(szBuffer,0,64);
//									pDataPos = strstr(pDataBuffer,"&nbsp");
//									if (pDataPos)
//									{
//										memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//										CChineseCode::Utf8ToUniCode(szBuffer,pTempClassInfo->wszTypeId);
//										pDataBuffer += strlen(szBuffer);
//										pDataBuffer += iSeparate;
//										memset(szBuffer,0,64);
//										pTempClassInfo++;
//										continue;
//									}
//								}
//							}
//						}
//					}
//				}
//				StrResult = SetClass_Parent(pClassInfo,iCount);
//				GlobalFree(pClassInfo);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_SET_SUB_CLASS_INFO:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			CPtrArray	SubArray;
//			char* pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int iCount = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				for (int i = 0; i < iCount; i++)
//				{
//					T_ClassInfo*	pClassInfo = new T_ClassInfo;
//					memset(pClassInfo,0,sizeof(T_ClassInfo));
//					char* pDataPos = NULL;
//					pDataPos = strstr(pDataBuffer,"&nbsp");
//					if (pDataPos)
//					{
//						memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//						CChineseCode::Utf8ToUniCode(szBuffer,pClassInfo->wszID);
//						pDataBuffer += strlen(szBuffer);
//						pDataBuffer += iSeparate;
//						memset(szBuffer,0,64);
//						pDataPos = strstr(pDataBuffer,"&nbsp");
//						if (pDataPos)
//						{
//							memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//							CChineseCode::Utf8ToUniCode(szBuffer,pClassInfo->wszName);
//							pDataBuffer += strlen(szBuffer);
//							pDataBuffer += iSeparate;
//							memset(szBuffer,0,64);
//							pDataPos = strstr(pDataBuffer,"&nbsp");
//							if (pDataPos)
//							{
//								memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//								pClassInfo->dwShowIndex = atol(szBuffer);
//								pDataBuffer += strlen(szBuffer);
//								pDataBuffer += iSeparate;
//								memset(szBuffer,0,64);
//								pDataPos = strstr(pDataBuffer,"&nbsp");
//								if (pDataPos)
//								{
//									memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//									pClassInfo->dwShow = atol(szBuffer);
//									pDataBuffer += strlen(szBuffer);
//									pDataBuffer += iSeparate;
//									memset(szBuffer,0,64);
//									pDataPos = strstr(pDataBuffer,"&nbsp");
//									if (pDataPos)
//									{
//										memcpy(szBuffer,pDataBuffer,pDataPos - pDataBuffer);
//										CChineseCode::Utf8ToUniCode(szBuffer,pClassInfo->wszTypeId);
//										pDataBuffer += strlen(szBuffer);
//										pDataBuffer += iSeparate;
//										memset(szBuffer,0,64);
//										SubArray.Add(pClassInfo);
//										continue;
//									}
//								}
//							}
//						}
//					}
//				}
//				StrResult = SetClass_Sub(SubArray);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GET_BT_SYSTEM_INFO:
//		{
//			StrResult = GetBtSystemInfo();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_RESOURCE_NUMBER:
//		{
//			StrResult = GetResourcesInfo();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GAME_CLEAR_FILEDIR:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int GameId = atoi(szBuffer);
//				StrResult = ClearGameFileAndDir(GameId);
//				iResult = 1;
//				break;
//			}
//			break;
//		}
//	case	COMMAND_GAME_MOVE_DIRECTORY:
//		{
//			GAME_MOVE_DIRECTORY	Game_MoveInfo = { 0 };
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				Game_MoveInfo.dwID = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					CChineseCode::Utf8ToUniCode(szBuffer,Game_MoveInfo.wszOrgDirectory);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					memset(szBuffer,0,260);
//					pPos = strstr(pDataBuffer,"&nbsp");
//					if (pPos)
//					{
//						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//						CChineseCode::Utf8ToUniCode(szBuffer,Game_MoveInfo.wszDestDirectory);
//						pDataBuffer += strlen(szBuffer);
//						pDataBuffer += iSeparate;
//						memset(szBuffer,0,260);
//						StrResult = MoveGame(&Game_MoveInfo);
//						iResult = 1;
//						break;
//					}
//				}
//			}
//			break;
//		}
//	case	COMMAND_LOGIN:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				CString	StrUsreName(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					CString	StrUsrePassWord(szBuffer);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					memset(szBuffer,0,260);
//					StrResult = RegUserLogin(StrUsreName,StrUsrePassWord);
//					iResult = 1;
//					break;
//				}
//			}
//			break;
//		}
//	case	FQ_Game_Operation:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nFlag = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//				RESOURCE_PROPERTY	NewGameInfo = { 0 };
//				iResult = LoadNewGame(&NewGameInfo,pDataBuffer);
//				if (iResult == NULL)
//				{
//					break;
//				}
//				StrResult = Game_Operation(nFlag,&NewGameInfo);
//				break;
//			}
//			break;
//		}
//	case	COMMAND_GAME_CUSTOM_MAXID:
//		{
//			StrResult = GetGameCustomId();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SYNC_DATA:
//		{
//			StrResult = UpdateBt();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_TASK_TRACKER_INFO:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int GameId = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//				StrResult = GetTaskTracke(GameId);
//				iResult = 1;
//				break;
//			}
//			break;
//		}
//	case	COMMAND_GET_GAME_GROUP:
//		{
//			CStringArray	GroupList;
//			CString			StrRetData;
//			int iRet = GetGameGroup(GroupList);
//			if (iRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp错误。"));
//				iResult = 1;
//				break;
//			}
//			if (iRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < GroupList.GetCount(); i++)
//			{
//				StrRetData += GroupList.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_GAME_GROUP:
//		{
//			GameGroupInfo	GameGroup = { 0 };
//			int iRet = LoadGemeGroup(&GameGroup,pDataBuffer);
//			if (iRet == NULL)
//			{
//				StrResult.Format(_T("0&nbsp数据错误&nbsp"));
//				iResult = 1;
//				break;
//			}
//			StrResult = SetGameGroup(&GameGroup);
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_GROUP_WORKSTATION:
//		{
//			QUERY_PARAM_WORKSTATION	Param_Wks = { 0 };
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				CChineseCode::Utf8ToUniCode(szBuffer,Param_Wks.wszGroupName);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//
//				CStringArray	GroupWks;
//
//				int nRet = GetWkstationGroup(&Param_Wks,GroupWks);
//				if (nRet == NULL)
//				{
//					StrResult.Format(_T("1&nbsp"));
//					iResult = 1;
//					break;
//				}
//				if (nRet == -1)
//				{
//					StrResult.Format(_T("0&nbsp"));
//					iResult = 1;
//					break;
//				}
//				CString	StrRetData;
//				StrRetData += _T("1&nbsp[");
//				for (int i = 0;i < GroupWks.GetSize(); i++)
//				{
//					StrRetData += GroupWks.GetAt(i);
//				}
//				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//				StrResult += _T("]");
//				iResult = 1;
//				break;
//			}
//			break;
//		}
//	case	COMMAND_SET_WORKSTATION_PROPERTY:
//		{
//			SET_WORKSTATION_PROPERTY	SetWksGoup = { 0 };
//			iResult = LoadWksGameGroup(&SetWksGoup,pDataBuffer);
//			if (iResult == NULL)
//			{
//				break;
//			}
//			StrResult = SetWksGameGroup(&SetWksGoup);
//			break;
//		}
//	case	COMMAND_GET_WORKSTATION_PROPERTY:
//		{
//			COMMAND_PARAM_GET_WORKSTATION_PROPERTY	WksGroupInfo = { 0 };
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				WksGroupInfo.dwID = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,260);
//				StrResult = GetWksGroupInfo(&WksGroupInfo);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GET_DISK_INFO:
//		{
//			StrResult = GetDiskPartition();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GET_FILE_DIRECTORY_INFO:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[260] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				TCHAR	lpwzsPath[128] = { 0 };
//				CChineseCode::Utf8ToUniCode(szBuffer,lpwzsPath);
//				StrResult = GetDiskToFile(lpwzsPath);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GAME_SET_AUTO_UPDATE:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nGameId = atoi(szBuffer);
//				StrResult = AutoUpdate(nGameId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GAME_SET_MANUAL_UPDATE:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nGameId = atoi(szBuffer);
//				StrResult = ManualUpdate(nGameId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_TASK_PROPERTY_ADD:
//		{
//			GAME_SIMPLE_PROPERTY	PropertyInfo = { 0 };
//			iResult = Load_Simple_Property(&PropertyInfo,pDataBuffer);
//			if (iResult == NULL)
//			{
//				break;
//			}
//			StrResult = PropertyAddTask(&PropertyInfo);
//			break;
//		}
//	case	COMMAND_CUSTOM_GAME_GET_PROPERTY:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nGameId = atoi(szBuffer);
//				StrResult = GetGame(nGameId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_CUSTOM_GAME_DELETE:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nGameId = atoi(szBuffer);
//				StrResult = DeleteGame(nGameId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_TASK_SSD_ADD:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nGameId = atoi(szBuffer);
//				StrResult = DownloadGameSSD(nGameId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GET_FILE_DIRECTORY_PROPERTY:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				TCHAR	lpwzsBuffer[260] = { 0 };
//				CChineseCode::Utf8ToUniCode(szBuffer,lpwzsBuffer);
//				StrResult = GetDirInfo(lpwzsBuffer);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GAME_START_SEARCH:
//		{
//			StrResult = BeginGameSearch();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GAME_END_SEARCH:
//		{
//			StrResult = EndGameSearch();
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_GAME_GET_LOCATE:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				TCHAR	lpwzsBuffer[260] = { 0 };
//				CChineseCode::Utf8ToUniCode(szBuffer,lpwzsBuffer);
//				StrResult = GetGameSearchInfo(lpwzsBuffer);
//				iResult = 1;
//				break;
//			}
//			break;
//		}
//	case	COMMAND_GAME_GET_LOCATE_STATUS:
//		{
//			GET_GAME_LOCATE_STATUS_REQUEST	GameStatus = { 0 };
//			iResult = LoadSearchStatus(&GameStatus,pDataBuffer);
//			if (iResult == NULL)
//			{
//				break;
//			}
//			StrResult = GetSearchStatus(&GameStatus);
//			break;
//		}
//	case	COMMAND_GAME_SET_LOCATE:
//		{
//			SET_GAME_LOCATE_INFO	GameInfo = { 0 };
//			iResult = LoadSearchInfo(&GameInfo,pDataBuffer);
//			if (iResult == NULL)
//			{
//				break;
//			}
//			StrResult = SetSearchInfo(&GameInfo);
//			break;
//		}
//	case	FQ_GameGroup_Operation:
//		{
//			InstDelGroupInfo	GroupInfo = { 0 };
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nFlags = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					CChineseCode::Utf8ToUniCode(szBuffer,GroupInfo.wszGroupName);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					memset(szBuffer,0,64);
//					StrResult = BtGroup_Operation(nFlags,&GroupInfo);
//					iResult = 1;
//					break;
//				}
//			}
//			break;
//		}
//	case	COMMAND_MODIFY_GROUP:
//		{
//			ModifyGroupInfo	MGroupInfo = { 0 };
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				CChineseCode::Utf8ToUniCode(szBuffer,MGroupInfo.wszOldGroupName);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				pPos = strstr(pDataBuffer,"&nbsp");
//				if (pPos)
//				{
//					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//					CChineseCode::Utf8ToUniCode(szBuffer,MGroupInfo.wszNewGroupName);
//					pDataBuffer += strlen(szBuffer);
//					pDataBuffer += iSeparate;
//					memset(szBuffer,0,64);
//					StrResult = BtGroup_Modify(&MGroupInfo);
//					iResult = 1;
//					break;
//				}
//			}
//			break;
//		}
//	case	COMMAND_GAME_REPAIR:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nGameId = atoi(szBuffer);
//				StrResult = FepairGame(nGameId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_GET_MOVIE_INFO:
//		{
//			CStringArray	MovieList;
//			int nRet = GetMovie(MovieList);
//			if (nRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp"));
//				iResult = 1;
//				break;
//			}
//			if (nRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			CString	StrRetData;
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < MovieList.GetCount(); i++)
//			{
//				StrRetData += MovieList.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_MOVIE_INFO:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nCount = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				T_Movie*	pMovie = new T_Movie[nCount];
//				memset(pMovie,0,sizeof(T_Movie) * nCount);
//				iResult = LoadMovie(nCount,pMovie,pDataBuffer);
//				if (iResult == NULL)
//				{
//					break;
//				}
//				StrResult = SetMovie(nCount,pMovie);
//				delete	[]pMovie;
//			}
//			break;
//		}
//	case	COMMAND_GET_ONLINE_INFO:
//		{
//			CStringArray	OnlineList;
//			int nRet = GetOnline(OnlineList);
//			if (nRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp"));
//				iResult = 1;
//				break;
//			}
//			if (nRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			CString	StrRetData;
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < OnlineList.GetCount(); i++)
//			{
//				StrRetData += OnlineList.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_ONLINE_INFO:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nCount = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				T_Online*	pOnline = new T_Online[nCount];
//				memset(pOnline,0,sizeof(T_Online) * nCount);
//				iResult = LoadOnline(nCount,pOnline,pDataBuffer);
//				if (iResult == NULL)
//				{
//					break;
//				}
//				StrResult = SetOnline(nCount,pOnline);
//				delete	[]pOnline;
//			}
//			break;
//		}
//	case	COMMAND_GET_PLAYER_LIST_INFO:
//		{
//			CStringArray	PlayerList;
//			int	nRet = GetPlayer(PlayerList);
//			if (nRet == -1)
//			{
//				StrResult.Format(_T("0&nbsp"));
//				iResult = 1;
//				break;
//			}
//			if (nRet == 0)
//			{
//				StrResult.Format(_T("1&nbsp"));
//				iResult = 1;
//				break;
//			}
//			CString	StrRetData;
//			StrRetData += _T("1&nbsp[");
//			for (int i = 0;i < PlayerList.GetCount(); i++)
//			{
//				StrRetData += PlayerList.GetAt(i);
//			}
//			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
//			StrResult += _T("]");
//			iResult = 1;
//			break;
//		}
//	case	COMMAND_SET_PLAYER_LIST_INFO:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int nCount = atoi(szBuffer);
//				pDataBuffer += strlen(szBuffer);
//				pDataBuffer += iSeparate;
//				memset(szBuffer,0,64);
//				T_PlayerList*	pPlayer = new T_PlayerList[nCount];
//				memset(pPlayer,0,sizeof(T_PlayerList) * nCount);
//				iResult = LoadPlayer(nCount,pPlayer,pDataBuffer);
//				if (iResult == NULL)
//				{
//					break;
//				}
//				StrResult = SetPlayer(nCount,pPlayer);
//				delete	[]pPlayer;
//			}
//			break;
//		}
//	case	COMMAND_SET_SERVER_PROPERTY:
//		{
//			SERVER_PROPERTY	ServerGroup = { 0 };
//			iResult = LoadServerGroup(&ServerGroup,pDataBuffer);
//			if (iResult == NULL)
//			{
//				break;
//			}
//			StrResult = SetServerGroup(&ServerGroup);
//			break;
//		}
//	case	COMMAND_DELETE_WORKSTATION:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				int WksId = atol(szBuffer);
//				StrResult = DeleteWksGroup(WksId);
//				iResult = 1;
//			}
//			break;
//		}
//	case	COMMAND_DELETE_SERVER:
//		{
//			int iSeparate = strlen("&nbsp");
//			char	szBuffer[64] = { 0 };
//			char*	pPos = NULL;
//			pPos = strstr(pDataBuffer,"&nbsp");
//			if (pPos)
//			{
//				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
//				TCHAR	lpwzsServerName[32] = { 0 };
//				CChineseCode::Utf8ToUniCode(szBuffer,lpwzsServerName);
//				StrResult = DeleteServerGroup(lpwzsServerName);
//				iResult = 1;
//			}
//			break;
//		}
//	}
//	Close();
//	return iResult;
//}
//
//
