#if !defined COMMUNICATION_H
#define COMMUNICATION_H
//----------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------常量-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------
const		DWORD	SCMD_OK					=	70000;	//UI操作指令返回成功
const		WORD	SU_SOCKET_HEAD_VALUE	=	1978;	//服务(Service)与用户界面(UI)通讯包头值
const		WORD	CS_SOCKET_HEAD_VALUE	=	2012;	//内网与外网通讯包头值
//----------资源状态值常量
//const		int		RS_FLAG_INVALID			=  -3;		//无效数据(未启用)	***
const		int		RS_FLAG_MANUAL_DELETE	=  -2;		//已删除(手动)
const		int		RS_FLAG_AUTO_DELETED	=  -1;		//已删除(自动)
const		int		RS_FLAG_UNDOWNLOAD		=	0;		//未下载
const		int		RS_FLAG_HAVEUPDATE		=	1;		//有更新
const		int		RS_FLAG_FINISHED		=	2;		//已完成更新


//----------资源当前工作状态	
//低位
const		int		RSWS_NONE				=	0x00;	// 没有工作状态			
const		int		RSWS_ACTIVING			=	0x01;	// 活动中
const		int		RSWS_ACTIVE_SUPPLY_SEED	=	0x02;	// 活动中(补种中)
const		int		RSWS_MOVE_DIRECTORY		=	0x04;	// 正在移动目录中
const		int		RSWS_DELETE_DIRECTORY	=	0x08;	// 正在删除目录中
const		int		RSWS_REPLACE_PIECE_DATA	=	0x10;	// 回切临时目录数据到源目录
//高位
const		int		RSWS_INVALID_DATA		=	0x10000;// 无效数据(无法提供更新)
const		int		RSWS_UNKNOW				=	0x20000;// 未知状态
//----------非核心任务当前操作状态
const		int		NONCORE_TASK_STATUS_NONE			=0;						//无
const		int		NONCORE_TASK_STATUS_DOWNLOAD_FILE	=1;						//下载文件
const		int		NONCORE_TASK_STATUS_CREATE_IDX		=2;						//创建索引
const		int		NONCORE_TASK_ERROR					=3;						//错误

//资源或任务的异步状态
enum _rtAsynState
{
	rtAsynStateNone = 0,								// 没有异步状态

	//	rtAsynStateWaitFileDownload,						// 排队等待下载文件
	//	rtAsynStateWaitCreateIdxFile,						// 排队等待创建索引
	rtAsynStateWaitClearRedundant,						// 排队等待清除多余文件目录
	rtAsynStateWaitMoveDirectory,						// 排队等待移动目录
	rtAsynStateWaitDeleteDirectory,						// 排队等待删除目录
	rtAsynStateWaitReplacePieceData,					// 排队等待缓存目录回切数据 (此状态包含了rtAsynStateClearRedundant状态)

	rtAsynStateFileDownload,							// 下载文件
	rtAsynStateCreateIdxFile,							// 创建索引
	rtAsynStateClearRedundant,							// 清除多余文件目录
	rtAsynStateMoveDirectory,							// 移动目录
	rtAsynStateDeleteDirectory,							// 删除目录
	rtAsynStateReplacePieceData,						// 缓存目录回切数据 (此状态包含了rtAsynStateClearRedundant状态)
	//rtAsynStateRepair,									// 修复(如果不需要更新，则改变状态为rtAsynStateWaitClearRedundant等待清除多余文件)		
};
/*
//临时缓存目录状态
enum _taskCacheDirectoryState
{
tsCacheDirNone = 0,									//未使用临时目录
tsCacheDirNoneCheck,								
tsCacheDirNoneContrast,
tsCacheDirCheck,									//在使用原始目录校验文件
tsCacheDirContrast,									//在使用idx文件对比
tsCacheDirDownloading,								//正在临时缓存目录中下载
//	tsCacheDirWaitReplace,								//缓存目录下载完成，等待数据切换
//	tsCacheDirReplacing,								//缓存目录正在切换数据
};*/
//当前任务使用的目录类型
enum _taskUseDirectoryType
{
	tsUseDirTypeOriginal = 0,
	tsUseDirTypeCache,
};
//当前任务目录的状态
enum _taskDirectoryState
{
	tsDirStateNone = 0,
	tsDirStateInitCheck,
	tsDirStateInitContrast,
	tsDirStateDownloading,
};

//任务自动状态
enum _taskAutoState
{
	tsAutoStateWait = 0,								//任务处于排队等待中(自动停止)
	tsAutoStateWaitChecked,								//正在处于等待检查完成
	tsAutoStateActive,									//任务处于活动状态
	tsAutoStateManualStop,								//任务处于手动停止状态
};
//----------资源扩展类型
const		int		RSET_NONE				=	0x00;	// 无类型
const		int		RSET_STOP_UPDATE		=	0x01;	// 已停止支持更新
const		int		RSET_FORCE_PROMOTE		=	0x02;	// 强制推广类型
const		int		RSET_FORCE_CHANGE		=	0x04;	// 强制修改类型
const		int		RSET_FORCE_DELETE		=	0x08;	// 强制删除类型

enum _resExType
{
	resExTypeNone = 0,
	resExTypeStopSupport,
	resExTypePromote,
	resExTypeChange,
	resExTypeDelete,
};
//任务类型值常量
enum _taskType
{
	tsTypeNone = 0,										//非活动任务
	tsTypeNonCore,										//非核心活动任务
	tsTypeCore,											//核心活动任务
};
//任务已触发的工作状态
enum _taskTrigger
{
	tsTriggerNone =	0,									//无任何触发
	tsTriggerDownload,									//下载被触发
	tsTriggerFinished,									//下载完成被触发
};
//----------服务初始化状态值常量
const		UINT	SRV_WS_INITIAL			=	0;
const		UINT	SRV_WS_INITIALED		=	1;
const		UINT	SRVIS_FINISHED			=	100;

enum _srvInitState
{
	srvInitStateNone = 0,
	srvInitStateFinished,
};
//----------用户注册状态值常量
const		UINT	USER_STATUS_UNKNOWN		=	0;		//未知用户
const		UINT	USER_STATUS_FREE		=	1;		//免费用户
const		UINT	USER_STATUS_VIP			=	2;		//VIP用户

enum _regUserState
{
	regUserStateUnknow = 0,
	regUserStateFree,
	regUserStateVIP,
};
//----------BT结构中的Flags值
const		DWORD	BTS_FLAGS_32[33]		=   {0x00000000,
0x00000001,0x00000003,0x00000007,0x0000000F,
0x0000001F,0x0000003F,0x0000007F,0x000000FF,
0x000001FF,0x000003FF,0x000007FF,0x00000FFF,
0x00001FFF,0x00003FFF,0x00007FFF,0x0000FFFF,
0x0001FFFF,0x0003FFFF,0x0007FFFF,0x000FFFFF,
0x001FFFFF,0x003FFFFF,0x007FFFFF,0x00FFFFFF,
0x01FFFFFF,0x03FFFFFF,0x07FFFFFF,0x0FFFFFFF,
0x1FFFFFFF,0x3FFFFFFF,0x7FFFFFFF,0xFFFFFFFF};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------界面操作指令-----------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------系统指令
#define		COMMAND_CONNECT_SERV				100		//联机BT服务						//
#define		COMMAND_UI_LOGIN					101		//UI登录							//
#define		COMMAND_GET_LOGIN_INFO				102		//获取UI登录信息					//
#define		COMMAND_SET_PASSWORD				103		//设置联机密码						//
#define		COMMAND_SYNC_DATA					106		//同步数据							//
#define		COMMAND_GET_SYNC_PROGRESS			107		//获取同步进度
#define		COMMAND_GET_SERV_WORK_STATUS		270		//获取BT服务工作状态				//
#define		COMMAND_GET_LOG_INFO				119		//获取日志信息
#define		COMMAND_GET_BT_CONFIG				104		//获取BT配置信息					//
#define		COMMAND_SET_BT_CONFIG				105		//设置BT配置信息					//
#define		COMMAND_GET_MENU_CONFIG				113		//获取游戏菜单配置信息				//
#define		COMMAND_SET_MENU_CONFIG				120		//设置游戏菜单设置信息				//
#define		COMMAND_GET_LIMIT_TIME_PERIOD_INFO	267		//获取限制时段信息
#define		COMMAND_CLEAR_BT_REG_INFO			268		//清除注册信息
//----------获取数据库表信息指令
#define		COMMAND_GET_GAMES_INFO				108		//获取T_GamesInfo游戏资源数据		//
#define		COMMAND_GET_WG_INFO					110		//获取T_WgsInf辅助工具数据			//
#define		COMMAND_GET_PARENT_CLASS_INFO		111		//获取T_ParentClass大类数据			//
#define		COMMAND_GET_SUB_CLASS_INFO			112		//获取T_SubClass小类数据			//
#define		COMMAND_GET_MOVIE_INFO				260		//获取T_MovieInfo数据				//
#define		COMMAND_GET_ONLINE_INFO				262		//获取T_Online数据					//
#define		COMMAND_GET_PLAYER_LIST_INFO		264		//获取T_Player数据					//
#define		COMMAND_GET_SINGLE_GAME_INFO		266		//获取单个游戏资源信息
//----------设置数据库表信息指令
#define		COMMAND_SET_PARENT_CLASS_INFO		121		//设置T_ParentClass大类数据			//
#define		COMMAND_SET_SUB_CLASS_INFO			122		//设置T_SubClass小类数据			//
#define		COMMAND_SET_MOVIE_INFO				261		//设置T_MovieInfo数据				//
#define		COMMAND_SET_ONLINE_INFO				263		//设置T_Online数据					//
#define		COMMAND_SET_PLAYER_LIST_INFO		265		//设置T_Player数据					//
//----------公共游戏资源设置、操作指令
#define		COMMAND_GET_BT_SYSTEM_INFO			123		//获取BT系统概况信息				//
#define		COMMAND_GET_RESOURCE_NUMBER			124		//获取资源数						//
#define		COMMAND_GAME_GET_SUPERFLUOUS_INFO	109		//获取多余的已停止更新的资源数据	//
#define		COMMAND_GAME_GET_DELETE_SORT		114		//获取游戏删除顺序数据				//
#define		COMMAND_GAME_SET_SIMPLE_PROPERTY	117		//设置BT资源简单属性				//
#define		COMMAND_GAME_GET_SIMPLE_PROPERTY	118		//获取BT资源简单属性				//
#define		COMMAND_GAME_DELETE					213		//删除资源							//
#define		COMMAND_GAME_CLEAR_FILEDIR			214		//清除多余文件目录					//
#define		COMMAND_GAME_MOVE_DIRECTORY			215		//移动游戏目录						//
#define		COMMAND_GAME_REPAIR					239		//游戏修复							//
#define		COMMAND_GAME_SET_AUTO_UPDATE		242		//资源设置自动更新方式				//
#define		COMMAND_GAME_SET_MANUAL_UPDATE		243		//资源设置手动更新方式				//

//----------自定义游戏资源操作指令
#define		COMMAND_CUSTOM_GAME_ADD				216		//添加自定义游戏资源				//
#define		COMMAND_CUSTOM_WEB_ADD				217		//添加自定义WEB资源

#define		COMMAND_CUSTOM_GAME_GET_MAXID       218     //自动获取最大自定义游戏编号		//
#define		COMMAND_CUSTOM_GAME_GET_PROPERTY	247		//获取用户自定义游戏属性			//(自定义非自定义统一命令)
#define		COMMAND_CUSTOM_GAME_MODIFY_PROPERTY	248		//修改用户自定义游戏属性			//
#define		COMMAND_CUSTOM_GAME_DELETE			249		//用户自定义游戏删除				//
//----------活动任务获取信息、操作指令
#define		COMMAND_GET_TASKS_INFO				196		//获取所有活动任务信息				//
#define		COMMAND_GET_TASK_TRACKER_INFO		197		//获取指定任务的Tracker信息			//
#define		COMMAND_GET_TASK_PEER_INFO			198		//获取指定任务的节点信息			//
#define		COMMAND_TASK_ADD_DOWNLOAD			200		//添加一个下载任务					//(由COMMAND_TASK_ADD修改)
#define		COMMAND_TASK_SSD_DOWNLOAD			240		//SSD磁盘方式下载					//(由COMMAND_TASK_SSD_ADD修改)
#define		COMMAND_TASK_PROPERTY_DOWNLOAD		241		//属性方式添加下载					//(由COMMAND_TASK_PROPERTY_ADD修改)
#define		COMMAND_TASK_ADD_SEED				199		//添加一个做种任务					//(由COMMAND_TASK_SEED修改)
#define		COMMAND_TASK_ADD_SEED_SOURCE		219		//给指定任务添加一个种源			//
#define		COMMAND_TASK_START					202		//开始任务							//
#define		COMMAND_TASK_STOP					203		//停止任务							//
#define		COMMAND_TASK_CHECK					204		//检查任务							//
#define		COMMAND_TASK_REMOVE					205		//移除任务							//
#define		COMMAND_TASK_TOP					207     //置顶								//
#define		COMMAND_TASK_UP						208		//上移								//
#define		COMMAND_TASK_DOWN					209		//下移								//
#define		COMMAND_TASK_LIMIT_SPEED			210		//限制上传、下载速度				//
#define		COMMAND_TASK_SORT					211		//排序								//
#define		COMMAND_TASK_REFRESH_TRACKER		212		//强制重连一次Tracker				//				
//----------分组、工作站、服务器
#define		COMMAND_INSERT_GROUP				244		//添加一个分组信息					//
#define		COMMAND_MODIFY_GROUP				245		//修改一个分组信息					//
#define		COMMAND_DELETE_GROUP				246		//删除一个分组信息					//
#define		COMMAND_GET_GROUP_INFO				221		//获取所有分组信息					//
#define		COMMAND_GET_GROUP_WORKSTATION		222		//获取指定分组中的工作站信息		//
#define		COMMAND_GET_GROUP_SERVER			229		//获取指定分组中的服务器信息		//
#define		COMMAND_DELETE_WORKSTATION			253		//删除一台工作站					//
#define		COMMAND_DELETE_SERVER				254		//删除一台服务器					//
#define		COMMAND_SET_WORKSTATION_PROPERTY	223		//设置一台工作站属性(没有就新加)	//
#define		COMMAND_GET_WORKSTATION_PROPERTY    224     //获取一台工作站属性				//
#define		COMMAND_SET_SERVER_PROPERTY			251		//设置一台服务器属性(没有就新加)	//
#define		COMMAND_GET_SERVER_PROPERTY			252		//获取一台服务器属性				//
#define		COMMAND_SYNC_MZD_WORKSTATION		255		//同步MZD工作站信息
#define		COMMAND_SYNC_MZD_SERVER				256		//同步MZD服务器信息
//----------磁盘目录操作指令
#define		COMMAND_GET_DISK_INFO				225		//获取磁盘信息						//
#define     COMMAND_GET_FILE_DIRECTORY_INFO     226     //获取文件目录信息					//
#define		COMMAND_GET_FILE_DIRECTORY_PROPERTY 227		//获取文件目录属性					//
#define		COMMAND_GET_DIRECTORY_SIZE			228		//获取目录大小(单位Byte）			//
//----------资源搜索定位操作指令
#define		COMMAND_GAME_START_SEARCH			230		//开始游戏定位搜索					
#define     COMMAND_GAME_COVER_LOCATE			235		//覆盖方式定位
#define		COMMAND_GAME_END_SEARCH				231		//结束游戏定位搜索					//作废
#define		COMMAND_GAME_GET_LOCATE				232		//获取游戏定位信息					//作废
#define		COMMAND_GAME_GET_LOCATE_STATUS		233		//获取游戏定位状态					//作废
#define		COMMAND_GAME_SET_LOCATE				234		//设置游戏定位信息

//----------娱乐平台操作指令
#define		COMMAND_MENU_GET_SINGLE_GAME_INFO	331		//获取单个游戏信息
#define		COMMAND_MENU_CLOSE					332		//关闭单个游戏
//----------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------获取指定项目类型的资源定义值------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

#define		COMMAND_GET_SINGLE_PARENT_CLASS_NAME 271	//获取单个大类默认名称
#define		COMMAND_GET_SINGLE_SUB_CLASS_NAME	272		//获取单个小类默认名称

//获取资源信息命令参数
enum ParamGetGames
{
	getAll	= 0,										// 获取所有BT资源
	getToday,											// 获取今日更新资源
	getHaveUpdat,										// 有更新资源
	getUndownload,										// 获取未下载资源
	getNew,												// 获取新增加资源
	getLocal,											// 获取本地BT资源
	getDelete,											// 获取本地已删除资源记录
	getMenuClassGame,									// 获取菜单分类资源信息(game类)
	getMenuClassWeb,									// 获取菜单分类资源信息(web类)
	//getGroupGame										// 获取分组游戏信息
};
//查询资源类型
enum QueryType
{
	qtAll = 0,											// 所有
	qtGamesOnline,										// 网络游戏
	qtGamesLAN,											// 单机游戏
	qtChess,											// 棋牌对战
	qtTools,											// 工具软件
	qtFinancial,										// 金融证券
	qtInternet,											// 聊天工具
	qtGamesFUN,											// 休闲游戏
	qtApplications,										// 辅助工具
	//菜单资源类型(A~Z)
	//qtMenuClass											// 菜单大类
};
//菜单资源小类
enum QuerySubClass
{
	qscAll = 0,									
	qscSubClass1,
	qscSubClass2,
	qscSubClass3,
	qscSubClass4,
	qscSubClass5,
	qscSubClass6,
	qscSubClass7,
	qscSubClass8,
	qscSubClass9,
};
//给活动任务添加种源的方式
enum ADD_SEED_SOURCE_MODE
{
	modeIpaddr = 0,										// IPPORT模式
	modeHttpUrl = 1										// HTTP模式
};
// 单个下载的状态
enum DL_DLBT_DOWNLOAD_STATE
{	
	P_BTDS_QUEUED,										// 已添加	
	P_BTDS_CHECKING_FILES,								// 正在检查校验文件
	P_BTDS_DOWNLOADING_TORRENT,							// 无种子模式下，正在获取种子的信息	
	P_BTDS_DOWNLOADING,									// 正在下载中
	P_BTDS_FINISHED,									// 指定的文件下载完成
	P_BTDS_SEEDING,										// 供种中（种子中的所有文件下载完成） 	
	P_BTDS_ALLOCATING,									// 正在预分配磁盘空间 -- 预分配空间，减少磁盘碎片，和 
	// 启动选项有关，启动时如果选择预分配磁盘方式，可能进入该状态
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------结构-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------begin  [注:不需要单字节对齐]
//任务连接Tracker服务器信息1
struct DL_TRACKER_INFO_ENTRY
{
	int				tier;               
	int				failCount;							// 连续失败了多少次了（成功后，会被清零，只记录距离上次成功后的失败次数）

	char			url[128];
	char			trackerID[128];   
	char			message[128];						// tracker在error或者warning下返回的message，或者Http协议中的一些错误信息

	DWORD			trackerError;						// 是否失败，> 0 是失败，一般的信息会在message里面获取到，因为失败的值很多，没一一开放，如果有失败，可以记录这个数值，我查看下是什么方式的失败
	bool			announcing;							// 当前正在连接中……
	bool			haveResponsed;						// 是否收到过回复
};

// 每个连接上的节点（用户）的信息1  
struct DL_PEER_INFO_ENTRY
{
	int				connectionType;						// 连接类型 0：标准BT(tcp); 1: P2SP（http） 2: udp（可能是直接连接或者穿透）
	int             downloadSpeed;						// 下载速度
	int             uploadSpeed;						// 上传速度
	UINT64          downloadedBytes;					// 下载的字节数
	UINT64          uploadedBytes;						// 上传的字节数

	DWORD           peerFlag;							// tracker返回的PeerFlag，如果不是通过tracker获得的，则为0
	USHORT          port;
	char            ip [64];							// 对方IP
	char            client [64];						// 对方使用的客户端
};

// 单个下载任务的基本信息1
struct DL_DOWNLOADER_INFO
{
	DL_DLBT_DOWNLOAD_STATE          state;				// 下载的状态
	float           percentDone;						// 完成的比例
	int             downConnectionCount;				// 下载建立的连接数
	int             downloadLimit;						// 该任务的下载限速
	int             connectionCount;					// 总建立的连接数（包括上传）
	int             totalCompletedSeeds;				// Tracker启动以来，总下载完成的人数，如果Tracker不支持scrap，则返回-1
	int             inCompleteNum;						// 总的未完成的人数，如果Tracker不支持scrap，则返回-1
	int             seedConnected;						// 连上的下载完成的人数
	int             totalCurrentSeedCount;				// 当前在线的总的下载完成的人数（包括连上的和未连上的）
	int             totalCurrentPeerCount;				// 当前在线的总的下载的人数（包括连上的和未连上的）
	float           currentTaskProgress;				// 当前任务的进度

	BOOL            bPaused;							// 是否暂停
	BOOL            bError;								// 是否出错，可能是写磁盘出错等原因，详细原因可以通过调用DLBT_Downloader_GetLastError获知
	BOOL            bReleasingFIles;					// 是否正在使用IO句柄

	UINT            downloadSpeed;						// 下载的速度
	UINT            uploadSpeed;						// 上传的速度
	UINT64          wastedByteCount;					// 非数据的字节数（控制信息等）
	UINT64          totalDownloadedBytes;				// 下载的数据的字节数
	UINT64          totalUploadedBytes;					// 上传的数据的字节数

	// Torrent信息
	UINT64          totalFileSize;						// 所有文件的总大小
	UINT64          totalFileSizeExcludePadding;		// 实际文件的大小，不含padding文件
	UINT64          totalPaddingSize;					// 所有padding的大小
	int             pieceCount;							// 分块数
	int             pieceSize;							// 每个块的大小
	char            infoHash [256];						// 文件的Hash值
	WCHAR           torrentName[260];					// torrentName
};
//------------------------------------------------------end

#pragma pack(push)//保存对齐状态
#pragma pack(1)//保存对齐状态

//任务连接Tracker服务器信息2
typedef struct _PACK_TRACKER_INFO_ENTRY
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 管理的是tie结构中的项目

	DL_TRACKER_INFO_ENTRY	tie;

	_PACK_TRACKER_INFO_ENTRY()
	{
		memset(this,0,sizeof(_PACK_TRACKER_INFO_ENTRY));
		cbSize = sizeof(_PACK_TRACKER_INFO_ENTRY);
		dwFlags = BTS_FLAGS_32[8];
	}
}PACK_TRACKER_INFO_ENTRY;

// 每个连接上的节点（用户）的信息2  
typedef struct _PACK_PEER_INFO_ENTRY
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 管理的是pie结构中的项目

	DL_PEER_INFO_ENTRY	pie;

	_PACK_PEER_INFO_ENTRY()
	{
		memset(this,0,sizeof(_PACK_PEER_INFO_ENTRY));
		cbSize = sizeof(_PACK_PEER_INFO_ENTRY);
		dwFlags = BTS_FLAGS_32[9];
	}
}PACK_PEER_INFO_ENTRY;

// 单个下载任务的基本信息2
typedef struct _PACK_DOWNLOADER_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 管理di结构中的项目

	DL_DOWNLOADER_INFO	di;

	_PACK_DOWNLOADER_INFO()
	{
		memset(this,0,sizeof(_PACK_DOWNLOADER_INFO));
		cbSize = sizeof(_PACK_DOWNLOADER_INFO);
		dwFlags = BTS_FLAGS_32[25];
	}
}PACK_DOWNLOADER_INFO;

//SOCKET接收请求包头结构
typedef struct _BT_SOCKET_HEAD_REQUEST
{	
	DWORD			cbSize;
	DWORD			dwFlags;

	WORD			wHead;								// 1978
	WORD			wUIVer;								// UI版本
	UINT			uCommand;							// 指令
	DWORD			dwRequestSize;						// 请求的长度
	DWORD			dwCount;							// 记录条数
	wchar_t			wszPassword[16];					// 联机密码
	//DWORD			dwCRC;								// 数据校验值

	_BT_SOCKET_HEAD_REQUEST()
	{
		memset(this,0,sizeof(_BT_SOCKET_HEAD_REQUEST));
		cbSize = sizeof(_BT_SOCKET_HEAD_REQUEST);
		dwFlags = BTS_FLAGS_32[6];
	}
}BT_SOCKET_HEAD_REQUEST;
//SOCKET返回请求包头结构
typedef struct _BT_SOCKET_HEAD_REPLY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	WORD			wHead;								// 1978
	WORD			wServiceVer;						// BT服务版本
	UINT			uCommand;							// 指令
	DWORD			dwReplySize;						// 答复请求的长度
	DWORD			dwCount;							// 记录条数
	int				iErrorCode;							// 错误代码(10000:表示成功,其它表示失败，错误信息可通过COMM_GetUIErrorInfoString获取)
	//DWORD			dwCRC;								// 数据校验值

	_BT_SOCKET_HEAD_REPLY()
	{
		memset(this,0,sizeof(_BT_SOCKET_HEAD_REPLY));
		cbSize = sizeof(_BT_SOCKET_HEAD_REPLY);
		dwFlags = BTS_FLAGS_32[6];
	}
}BT_SOCKET_HEAD_REPLY;
//SOCKET接收缓存结构
typedef struct _SOCKET_BUFF
{
	int				iSize;								// 实际有效的缓冲区数据大小
	char			szBuff[1024*4];						// 缓冲区(4KB)
}SOCKET_BUFF;

//命令参数结构
typedef struct _COMMAND_PARAM
{
	DWORD			cbSize;
	DWORD			dwFlags;

	ParamGetGames	pgg;								// 获取资源信息命令参数
	QueryType		qt;									// 查询资源类型
	QuerySubClass	qsc;								// 查询资源分类
	int				iSortItem;							// 要排序的项目索引(<0无项目，默认）
	int				iSortFlag;							// 排序方式（0:升序1:降序)		
	wchar_t			wszGroupName[18];					// getMenuClassGame与getMenuClassWeb:菜单类名 getGroupGame:分组名称
	wchar_t			wszQueryString[32];					// 查询字符(为空就不查) (2013-08-08新加)
	int				nPage;					//页码
	int				nCount;					//页面条数

	_COMMAND_PARAM()
	{
		memset(this,0,sizeof(_COMMAND_PARAM));
		cbSize = sizeof(_COMMAND_PARAM);
		dwFlags = BTS_FLAGS_32[9];
	}
}COMMAND_PARAM;

//UI界面需要的登录返回信息
typedef struct _UI_LOGIN_REPLY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszNetbarName[32];					// 网吧名称
	wchar_t			wszAgentName[64];					// 代理商名称
	wchar_t			wszAgentID[16];						// 代理商编号
	WORD			wDay;								// 还有多少天到期
	//
	DWORD			dwLoginStatus;						// (0x00:无登录操作;0x01:正在登录验证中;0x02:登录失败需要重复登录)
	WORD			wUserStatus;						// 用户状态(0:未知用户,1:免费用户,2:vip)USER_STATUS_UNKNOWN,USER_STATUS_FREE,USER_STATUS_VIP
	DWORD			dwError;							// 错误值(0:无错误)
	wchar_t			wszError[128];						// 错误信息
	wchar_t			wszUserName[64];					// 用户名
	int				iSoftMode;							// 软件模式(0:主服模式,1:从服模式,2:有盘内网模式)

	_UI_LOGIN_REPLY()
	{
		memset(this,0,sizeof(_UI_LOGIN_REPLY));
		cbSize = sizeof(_UI_LOGIN_REPLY);
		dwFlags = BTS_FLAGS_32[10];
	}
}UI_LOGIN_REPLY;

//非核心任务信息结构
typedef struct _WAIT_TASK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Size;						//× 游戏资源大小
	DWORD			dwStatus;							//× 非核心任务当前操作(NONCORE_TASK_STATUS_NONE,NONCORE_TASK_STATUS_DOWNLOAD_FILE,NONCORE_TASK_STATUS_CREATE_IDX)
	DWORD			dwTotalBtye;						//× 总的字节数
	DWORD			dwCompletedBtye;					//× 已完成的字节数
	BOOL			bStop;								//× 是否停止等待
	wchar_t			wszHashNew[41];						//× 新的HASH值
	wchar_t			wszHashOld[41];						//× 老的HASH值

	_WAIT_TASK_INFO()
	{
		memset(this,0,sizeof(_WAIT_TASK_INFO));
		cbSize = sizeof(_WAIT_TASK_INFO);
		dwFlags = BTS_FLAGS_32[7];
	}
}WAIT_TASK_INFO;

// 任务基本信息
typedef struct _BASIC_TASK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								//√编号
	DWORD			dwIndex;							//√索引值(队列),默认情况下下载活动任务排前，等待任务排中，上传任务排最后
	//_taskType		tsType;								//√任务类型(TASK_TYPE_NONCORE:非核心任务，TASK_TYPE_CORE:核心任务)
	_taskAutoState	tsAutoState;						//√当前任务操作状态(TASK_STATUS_WAITING:等待、TASK_STATUS_ACTIVE:正常活动、TASK_STATUS_MANUAL_STOP:手动停止)
	//DWORD			dwCommand;							//×当前任务指令 (修改:2013-05-07) ***可以作废***
	_taskUseDirectoryType	tsUseDirType;				//  使用目录的类型(暂时使用dwCommand的空间）
	_taskTrigger	tsTrigger;							//√下载触发器(0:TSWS_TRIGGER_NONE)
	SYSTEMTIME		tmAdd;								//√载入时间
	SYSTEMTIME		tmStart;							//√开始活动时间
	SYSTEMTIME		tmFinished;							//√下载完成时间
	//
	HANDLE			hDownloader;						//√活动任务句柄**
	wchar_t			wszGame_Name[64];					// 任务名称**
	wchar_t			wszDirectoryName[64];				// 目录名称(数据库中执行文件目录名，此目录名作为实际下载的目录名)**
	wchar_t			wszIdxPath[360];					// Idx文件路径
	wchar_t			wszDirectory[360];					// 下载目录
	wchar_t			wszCacheDirectory[360];				// 缓存目录
	wchar_t			wszHash[41];						// 特征码值 （2013-8-3 新加）
	char			szErrorInfo[128];					// 错误信息(此处定义为多字节，是因为内核处理核心任务是多字节的)
	//_taskCacheDirectoryState tsCacheDirState;			// 缓存目录的状态
	_taskDirectoryState	tsDirState;						// 目录的状态

	DWORD			dwWorkImage;						// 任务状态图标
	wchar_t			wszWorkStatus[360];					// 任务状态信息文本

	int				iChangePieces;						// 需要更新的块的个数
	int*			pChangePiecesArray;					// 需要更新的，有变化的piece的信息

	_BASIC_TASK_INFO()
	{
		memset(this,0,sizeof(_BASIC_TASK_INFO));
		cbSize = sizeof(_BASIC_TASK_INFO);
		dwFlags = BTS_FLAGS_32[21];
	}
}BASIC_TASK_INFO;
//任务结构
typedef struct _TASK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 0x01 wti, 0x02 di,0x04 bti,

	PACK_DOWNLOADER_INFO	pdi;						// 核心任务
	//WAIT_TASK_INFO	wti;								// 非核心任务	
	BASIC_TASK_INFO	bti;								// 任务基本信息   

	_TASK_INFO()
	{
		////memset(this,0,sizeof(_TASK_INFO));			// 坚决不能清空
		cbSize = sizeof(_TASK_INFO);
		dwFlags = BTS_FLAGS_32[3];
	}
}TASK_INFO;

//表T_GamesInfo的数据结构 
typedef struct	_T_GamesInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;
	DWORD			dwFlags1;

	wchar_t			wszGame_Id[8];						//  编号
	wchar_t			wszGame_Text[32];					//--名称
	wchar_t			wszGame_Path[128];					//--文件及路径(游戏执行文件相对路径,格式"游戏目录\\..\\xx.exe")
	wchar_t			wszGame_Reg[128];					//--服务端下载路径(游戏下载目录,格式"盘符:\\..\\游戏目录")
	wchar_t			wszGame_Exe_Param[128];				//  运行参数
	wchar_t			wszGame_URL[32];					//  客户端路径
	DWORD			dwGame_Click_Rate;					//  总点击
	int				nGame_Flag;							//  操作标记(参见"资源状态值常量",-4:未知状态,-3:无效数据(未启用) ,-2:已删除(手动),-1:已删除(自动),0:未下载,1:有更新,2:已经更新（完成）,3:正在更新)
	wchar_t			wszGame_Abc[16];					//--拼音缩写
	wchar_t			wszGame_Only[128];					//--关键文件
	DWORD			dwGame_Show;						//  显示/会员
	DWORD			dwGame_Sort;						//  排序
	DWORD			dwGame_Type;						//--类型(所属分组,0:未分组,支持0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80... 32个组)
	wchar_t			wszGame_Save[128];					//--网络存档
	DWORD			dwNet_Sort;							//--网络排行
	wchar_t			wszGame_BM[32];						//  别名								-		
	SYSTEMTIME		InstTime;							//  创建日期
	SYSTEMTIME		UpdateTime;							//  更新日期
	DWORD			dwUpdate_Click_Rate;				//  更新后的点击率[本地月点击率]
	DWORD			dwGameSize;							//--资源大小(精确到MB)
	wchar_t			wszClass[32];						//--资源所属分类
	wchar_t			wszHashOld[41];						//  本地的HASH							-
	wchar_t			wszHashNew[41];						//--网络最新的HASH						-
	SYSTEMTIME		NetInstTime;						//--网络安装时间
	SYSTEMTIME		NetUpdateTime;						//--网络更新时间
	BOOL			bIsPlan;							//  计划任务(更新方式,TRUE:自动更新 FALSE:手动更新)
	BOOL			bClearFile;							//  禁止自动清除多余文件
	BOOL			bIsBT;								//--是否是有效的BT资源					-
	DWORD			dwTopGrade;							//  项目等级
	BOOL			bRestoreTime;						//--是否还原文件时间
	wchar_t			wszMonthDetail[121];				//  本地点击率的月详细					-
	DWORD			dwDeleteGrade;						//  删除等级
	double			fMonthClick;						//  平均月点击
	wchar_t			wszFuzzyIndex[32];					//--模糊目录
	int				nUpdateRange;						//--更新范围(0:非全区更新,1:全区更新)	-
	DWORD			dwOSType;							//--支持的操作系统(0x00:XP,0x01:WIN7）
	DWORD			dwGame3D;							//--3D游戏等级							-
	wchar_t			wszReadme3D[128];					//--3D设置说明							-
	SYSTEMTIME		DelayUpdateTime;					//--更新延时时间(*新加)					-
	DWORD			dwRunMode;							//--游戏运行模式(*新加)
	DWORD			dwShortcut;							//--创建桌面快捷方式(0不创建,1创建) 新加:2013-06-07

	_T_GamesInfo()
	{
		memset(this,0,sizeof(_T_GamesInfo));
		cbSize = sizeof(_T_GamesInfo);
		dwFlags = BTS_FLAGS_32[32];
		dwFlags1 = BTS_FLAGS_32[9];
	}
}T_GamesInfo;

//扩展信息
typedef struct	_T_GamesInfoEx
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Id;							// 编号的整数型
	wchar_t			wszDirectoryName[32];				// 默认的目录名xx (从strGame_Path中获取\xx\...\yy.zz 的xx)			-
	wchar_t			wszSubDirectory[64];				// 执行子目录名...(从strGame_Path中获取\xx\...\yy.zz 的... )		-
	wchar_t			wszFileName[32];					// 执行文件名yy.zz (从strGame_Path中获取\xx\...\yy.zz 的 yy.zz)		-
	DWORD			dwMonthDetail[30];					// 本地点击率的月详细值(分30份对应一个月的30天)						-
	float			fNetInstalledDay;					// 网络已安装的天数(与本地时间对比)									-
	float			fInstalledDay;						// 本地已经安装的天数
	int				nServerGameStatus;					// 服务器上的游戏状态

	DWORD			dwWorkImage;						// 工作图标()
	DWORD			dwWorkColor;						// 工作颜色
	DWORD			dwWorkStatus;						//×工作状态默认(RSWS_NONE:没有工作状态;RSWS_ACTIVING:活动中;RSWS_ACTIVE_SUPPLY_SEED:活动中(补种中);RSWS_MOVE_DIRECTORY:正在移动目录中;RSWS_DELETE_DIRECTORY:正在删除目录中;RSWS_RESTORE_CACHE_DIRECTORY:缓存目录数据还原中)
	wchar_t			wszWorkStatus[32];					// 工作状态文本信息

	//修改:2013-05-02	新加
	DWORD			dwExType;							// 资源扩展类型(0x00:无扩展类型 0x01:已停止支持更新的资源 0x02:强制推广的资源 0x04:强制修改的资源 0x08:强制删除的资源)

	_T_GamesInfoEx()
	{
		memset(this,0,sizeof(_T_GamesInfoEx));
		cbSize = sizeof(_T_GamesInfoEx);
		dwFlags = BTS_FLAGS_32[13];
	}
}T_GamesInfoEx;
//资源信息结构 
typedef struct _RESOURCE_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 0x01 gi,0x02 giex;

	T_GamesInfo		gi;									// 表T_GameInfo所有字段信息
	T_GamesInfoEx   giex;								// 扩展信息

	_RESOURCE_INFO()
	{
		////memset(this,0,sizeof(_RESOURCE_INFO));		//坚决不能清空
		cbSize = sizeof(_RESOURCE_INFO);
		dwFlags = BTS_FLAGS_32[2];
	}
}RESOURCE_INFO;

//资源属性
typedef	struct _RESOURCE_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 0x01 gi,0x02 wszAllGroupName;

	T_GamesInfo		gi;
	wchar_t			wszAllGroupName[32*18];				// 有效的分组名称和是否勾选,格式:[是否勾选][分组名称]|[是否勾选][分组名称]...|,例如(0网游|1单机|1高清|0综艺|)(支持32个分组，每个分组信息占wchar_t[18])

	_RESOURCE_PROPERTY()
	{
		//memset(this,0,sizeof(_RESOURCE_PROPERTY));   //不能把gi再清空一次了
		memset(wszAllGroupName,0,sizeof(wszAllGroupName));
		cbSize = sizeof(_RESOURCE_PROPERTY);
		dwFlags = BTS_FLAGS_32[2];
	}
}RESOURCE_PROPERTY;

//表T_WgsInfo结构
typedef struct 	_T_WgsInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszWg_Text[64];						// 名称			0x01
	wchar_t			wszWg_FTP_Path[128];				// 路径			0x02
	wchar_t			wszWg_URL[128];						// 客户端路径	0x04
	wchar_t			wszWg_Ver[128];						// 服务端路径	0x08
	wchar_t			wszGame_Id[48];						// 对应游戏编号	0x10
	DWORD			dwWg_Flag;							// 操作标记		0x20
	DWORD			dwWg_Show;							// 显示/会员	0x40

	_T_WgsInfo()
	{
		memset(this,0,sizeof(_T_WgsInfo));
		cbSize = sizeof(_T_WgsInfo);
		dwFlags = BTS_FLAGS_32[7];
	}
}T_WgsInfo;

//表T_SubClass和T_ParentClass结构 
typedef struct	 _T_ClassInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszID[3];							// 菜单类编号
	wchar_t 		wszName[32];						// 菜单类名称
	DWORD			dwShowIndex;						// 显示顺序
	DWORD			dwShow;								// 是否显示
	wchar_t			wszTypeId[2];						// 分类类型(NULL,0:混合 1:本地 2:网络)

	_T_ClassInfo()
	{
		memset(this,0,sizeof(_T_ClassInfo));
		cbSize = sizeof(_T_ClassInfo);
		dwFlags = BTS_FLAGS_32[5];
	}
}T_ClassInfo;

//表T_Manager结构
typedef struct _T_Manager
{
	DWORD			cbSize;
	DWORD			dwFlags;
	DWORD			dwFlags1;
	DWORD			dwFlags2;

	wchar_t			wszNetwork_Disk[128];				// 网游主路径		***
	int				nNetwork_Level;						// 搜索深度			***
	wchar_t			wszTools_Disk[128];					// 辅助工具磁盘		***
	wchar_t			wszQQ_Exe[64];						// QQ文件			***
	wchar_t			wszMusic_Exe[128];					// 千千静听文件		***
	BYTE			BaseInfo[1024];
	int				nInfoSize;
	int				nDbVer;								// 数据库版本
	wchar_t			wszServerIP[16];					// 游戏点击率IP		***
	wchar_t			wszLoginServerIp[16];				// 登录IP
	wchar_t			wszUsbServerIp[16];					// 网络U盘IP
	wchar_t			wszFtpServerIp[16];					// 存档IP
	wchar_t			wszCall1ServerIp[16];				// 呼叫IP
	wchar_t			wszCall2ServerIp[16];
	wchar_t			wszCall3ServerIp[16];
	wchar_t			wszCall4ServerIp[16];
	wchar_t			wszCall5ServerIp[16];
	int				nEnterInfo;							// 是否提示
	int				nAutoReadSave;						// 自动存档
	int				nShowSaveWin;						// 显示存档窗口
	int				nShowAsIcon;						// 显示方式：图片图标	***
	int				nPicSpacing;						// 图片间距				***
	int				nNormalIconSpacing;					// 标准图标间距			***
	int				nSmallIconSpacing;					// 经典图标间距			***
	int				nBigIconSpacing;					// 超大图标间距			***
	wchar_t			wszSkinFileName[128];				// 皮肤文件				***
	wchar_t			wszBgFileName[128];					// 背景文件				***
	int				nHideGameTools;						// 隐藏辅助工具			***
	int				nHideCallBoard;						// 隐藏公告板           ***(注释：隐藏菜单右边的游戏排行榜)
	int				nNetConnection;						// 连接：电信网通
	int				nUserRegIp;							// 用户注册IP
	wchar_t			wszUserRegName[64];					// 通行证
	int				nIsFixedDisk;						// 有盘无盘
	wchar_t			wszWallpaperFileName[128];			// 墙纸文件
	int				nAutoWallpaper;						// 自动选择墙纸
	int				nTimerWallpaper;					// 定时切换墙纸
	wchar_t			wszUpdate1ServerIP[16];				// 自动更新IP
	wchar_t			wszUpdate2ServerIP[16]; 
	wchar_t			wszUpdate3ServerIP[16];
	wchar_t			wszUpdate4ServerIP[16];
	wchar_t			wszUpdate5ServerIP[16];
	int				nNoExistRun;						// 游戏不存在时运行方式
	wchar_t			wszUpdatePwd[64];					// 自动更新密码
	int				nUpdateMode;						// 自动更新方式
	wchar_t			wszGroupType[80];					// 分组名称
	int				nUserCallTimer;						// 呼叫网管间隔时间
	wchar_t			wszShowBoardText[256];				// 公告板文本
	int				nShowBoardTime;						// 是否弹出公告板(注释：if(ShowBoardTime&0x02):启动时显示公告板, if(ShowBoardTime&0x01):默认显示公告板文本 else 显示nbboard.htm文件内容)
	int				nRunIsMode;							// 运行游戏后最小化或隐藏 ***
	int				nIsUpdate;							// 自动更新分类
	int				IsNetUsb;							// 网络U盘
	wchar_t			wszCustomExe1[128];					// 自定义文件
	wchar_t			wszCustomExe2[128];
	wchar_t			wszCustomExe3[128];
	wchar_t			wszCustomExe4[128];
	int				nVerType;							// 版本类型
	int				nShowClass;							// 是否显示子分类
	int				nWmConfig;							// 自动调用游戏环境配置程序(*)
	int				nToolsPrompt;						// 运行辅助工具时是否警告提示(*)
	wchar_t			wszAgentID[32];						// 代理商编号(*)
	wchar_t			wszAgentMZP[64];					// 代理商通行证(*)
	wchar_t			wszCustomName1[128];
	wchar_t			wszCustomName2[128];
	wchar_t			wszCustomName3[128];
	wchar_t			wszCustomName4[128];
	int				nSwitchWndSave;						// 1 表示切换窗口自动保存，0 表示不保存
	int				nIeNewWin;
	SYSTEMTIME		Clicktime;
	int				nClickDay;
	int				nAlphaIcon;							//0:256色 1:透明通道颜色
	BOOL			bExitPopAd;							// 退出时是否弹出广告
	int				nLanguageId;						// 语言地区编号(支持多语言用)
	wchar_t			wszCityName[20];					// 城市名称

	_T_Manager()
	{
		memset(this,0,sizeof(_T_Manager));
		cbSize = sizeof(_T_Manager);
		dwFlags = BTS_FLAGS_32[32];
		dwFlags1 = BTS_FLAGS_32[32];
		dwFlags2 = BTS_FLAGS_32[9];
	}
}T_Manager;

//游戏菜单扩展设置
typedef struct _MENU_CONFIG_EX
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwMenuStyle;						// 游戏菜单风格(0:经典版,1:卡通版,2:传统版,3:Win7版,4:时尚版)
	DWORD			dwClassTemplate;					// 游戏大类模板(0:无模板,1~3默认模板一二三,4自定义模板)

	_MENU_CONFIG_EX()
	{
		memset(this,0,sizeof(_MENU_CONFIG_EX));
		cbSize = sizeof(_MENU_CONFIG_EX);
		dwFlags = BTS_FLAGS_32[2];
	}
}MENU_CONFIG_EX;

//游戏菜单设置
typedef struct _MENU_CONFIG
{
	DWORD			cbSize;								
	DWORD			dwFlags;							// 0x01 manager, 0x02 mcex

	T_Manager		manager;
	MENU_CONFIG_EX	mcex;

	_MENU_CONFIG()
	{
		//memset(this,0,sizeof(_MENU_CONFIG));			//坚决不能清空(否则manager,mcex初始值也被清空了)
		cbSize = sizeof(_MENU_CONFIG);
		dwFlags = BTS_FLAGS_32[2];
	}
}MENU_CONFIG;

//表T_Promotion结构(Today.mdb)
typedef struct	_T_Promotion
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwAutoID;							// 自动编号
	wchar_t			wszFileName[8];						// 6位资源项目编号
	wchar_t			wszArea[10];						// 地区(Area和MZP相互排斥，只取一个，先取Area,如果为空，再取MZP)
	wchar_t			wszMZP[32];							// 完美通行证
	DWORD			dwFlag;								// (操作类型(0:强删1:强推广2:强更新))
	wchar_t			wszVerType[6];						// 用户版本类型(WMP -分别对应- WMB|MZD|PXD)

	_T_Promotion()
	{
		memset(this,0,sizeof(_T_Promotion));
		cbSize = sizeof(_T_Promotion);
		dwFlags = BTS_FLAGS_32[6];
	}
}T_Promotion;

//表T_GroupList结构 
typedef struct	_T_GroupList
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwComputerID;						// 计算机编号
	wchar_t			wszComputerName[32];				// 计算机名
	DWORD			dwComputerGroup;					// 所属分组
	wchar_t			wszIP[16];							// IP地址
	wchar_t			wszMAC[18];							// MAC网卡地址
	wchar_t			wszGateway[16];						// 网关
	wchar_t			wszDNS1[16];						// DNS1
	wchar_t			wszDNS2[16];						// DNS2		
	wchar_t			wszSubnetMask[16];					// 子网掩码
	wchar_t			wszResolution[10];					// 分辨率

	_T_GroupList()
	{
		memset(this,0,sizeof(_T_GroupList));
		cbSize = sizeof(_T_GroupList);
		dwFlags = BTS_FLAGS_32[10];
	}
}T_GroupList;

//表T_WorkstationInfo  工作站信息
typedef struct _T_WorkstationInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// 工作站编号
	DWORD			dwGroup;							// 所属分组
	wchar_t			wszName[32];						// 工作站名称
	wchar_t			wszIP[16];							// 工作站IP
	wchar_t			wszMAC[32];							// 网卡MAC地址

	_T_WorkstationInfo()
	{
		memset(this,0,sizeof(_T_WorkstationInfo));
		cbSize = sizeof(_T_WorkstationInfo);
		dwFlags = BTS_FLAGS_32[5];
	}
}T_WorkstationInfo;

//表T_ServerInfo		服务器信息
typedef	struct _T_ServerInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszName[32];						// 服务器名称
	DWORD			dwGroup;							// 所属分组
	wchar_t			wszIP[4][16];						// IP地址(支持4个)

	_T_ServerInfo()
	{
		memset(this,0,sizeof(_T_ServerInfo));
		cbSize = sizeof(_T_ServerInfo);
		dwFlags = BTS_FLAGS_32[3];
	}
}T_ServerInfo;

//表T_Movie
typedef struct _T_Movie
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwMovie_Index;						// 排序
	wchar_t			wszMovie_Path[255];					// 路径
	wchar_t			wszMovie_Disk[2];					// 盘符
	wchar_t			wszLogin_Name[30];					// 登录帐号
	wchar_t			wszLogin_Pass[30];					// 登录密码
	wchar_t			wszMovie_Name[50];					// 名称
	DWORD			dwMovie_Show;						// 显示或会员
	DWORD			dwIsDefault;						// 首页

	_T_Movie()
	{
		memset(this,0,sizeof(_T_Movie));
		cbSize = sizeof(_T_Movie);
		dwFlags = BTS_FLAGS_32[8];
	}
}T_Movie;

//表T_Online
typedef struct _T_Online
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwIdx;								// 排序
	wchar_t			wszLink[255];						// 路径
	wchar_t			wszCaption[20];						// 标题
	DWORD			dwShow;								// 显示或会员
	DWORD			dwIsDefault;						// 首页

	_T_Online()
	{
		memset(this,0,sizeof(_T_Online));
		cbSize = sizeof(_T_Online);
		dwFlags = BTS_FLAGS_32[5];
	}
}T_Online;

//表T_PlayerList
typedef struct _T_PlayerList
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszPlayerFile[255];					// 播放器文件
	wchar_t			wszPlayerExt[255];					// 扩展名列表
	DWORD			dwPlayerType;						// 所属影视/音乐

	_T_PlayerList()
	{
		memset(this,0,sizeof(_T_PlayerList));
		cbSize = sizeof(_T_PlayerList);
		dwFlags = BTS_FLAGS_32[3];
	}
}T_PlayerList;

//BT系统概况信息
typedef struct _BT_SYSTEM_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwDownloads;						// 正在下载任务数
	DWORD			dwLimitDownloads;					// 同时最大下载任务数
	DWORD			dwWaitDownloads;					// 等待任务
	DWORD			dwTimePeriodLimitSpeed;				// 分时段限速
	BOOL			bTimePeriodLimitSpeed;				// 是否开启了分时段限速
	BOOL			bPortUPNP;							// 是否开启了端口映射
	int				iLine;								// 选择线路
	DWORD			dwDownloadSpeed;					// 下载速度(KB)
	DWORD			dwTotalGames;						// 中心游戏总数
	__int64			ulTotalGameSize;					// 中心游戏总量(Byte)
	DWORD			dwLocalGames;						// 本地已下载的游戏
	__int64			ulLocalGameSize;					// 本地游戏总量(Byte)
	DWORD			dwLocalHaveUpdateGames;				// 本地未更新的游戏数

	_BT_SYSTEM_INFO()
	{
		memset(this,0,sizeof(_BT_SYSTEM_INFO));
		cbSize = sizeof(_BT_SYSTEM_INFO);
		dwFlags = BTS_FLAGS_32[13];
	}
}BT_SYSTEM_INFO;

//资源导航栏数据
typedef struct  _BT_RESOURCE_NUMBER
{
	DWORD			cbSize;
	DWORD			dwFlags;

	int				nNetResource;						// 全部资源
	int				nTodayUpdate;						// 今日更新
	int				nHaveUpdate;						// 有更新游戏
	int				nUndownload;						// 未下载游戏
	int				nNew;								// 新增加游戏
	int				nStopUpdate;						// 已停运游戏
	//	int				nLocal;								// 本地资源(2013-06-04作废)

	int				nLocalBtGame;						// 本地BT游戏(2013-06-04新加)
	int				nLocalBtWeb;						// 本地BTWeb(2013-06-04新加)
	int				nLocalUserGame;						// 本地用户游戏(2013-06-04新加)
	int				nLocalUserWeb;						// 本地用户Web(2013-06-04新加)

	int				nNetGame;							// 网络游戏
	int				nDiskGame;							// 单机游戏
	__int64			ulNetGameSize;						// 网络游戏大小
	__int64			ulDiskGameSize;						// 单机游戏大小
	__int64			ulResourceSize;						// 资源大小

	_BT_RESOURCE_NUMBER()
	{
		memset(this,0,sizeof(_BT_RESOURCE_NUMBER));
		cbSize = sizeof(_BT_RESOURCE_NUMBER);
		dwFlags = BTS_FLAGS_32[15];
	}
}BT_RESOURCE_NUMBER;


//移动资源目录信息
typedef struct _GAME_MOVE_DIRECTORY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// 要移动的资源编号
	wchar_t			wszOrgDirectory[360];				// 原始目录 
	wchar_t			wszDestDirectory[360];				// 要移动到的目的目录
	BOOL			bForceMove;							// 是否允许强制移动

	_GAME_MOVE_DIRECTORY()
	{
		memset(this,0,sizeof(_GAME_MOVE_DIRECTORY));
		cbSize = sizeof(_GAME_MOVE_DIRECTORY);
		dwFlags = BTS_FLAGS_32[4];
	}
}GAME_MOVE_DIRECTORY;

//移动资源目录进度信息
typedef struct _GAME_MOVE_DIRECTORY_PROPERSS
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// 资源编号
	DWORD			dwMax;								// 最大进度值
	DWORD			dwCurPos;							// 当前进度位置

	_GAME_MOVE_DIRECTORY_PROPERSS()
	{
		memset(this,0,sizeof(_GAME_MOVE_DIRECTORY_PROPERSS));
		cbSize = sizeof(_GAME_MOVE_DIRECTORY_PROPERSS);
		dwFlags = BTS_FLAGS_32[3];
	}
}GAME_MOVE_DIRECTORY_PROPERSS;

//直接做种上传结构
typedef struct _TASK_SEED_DATA
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// 资源编号
	BOOL			bQuickSeed;							// 是否快速上传做种
	wchar_t			wszIdxPath[256];					// idx文件路径
	wchar_t			wszDirectory[256];					// 资源目录

	_TASK_SEED_DATA()
	{
		memset(this,0,sizeof(_TASK_SEED_DATA));
		cbSize = sizeof(_TASK_SEED_DATA);
		dwFlags = BTS_FLAGS_32[4];
	}
}TASK_SEED_DATA;

//添加种源结构
typedef struct _ADD_SEED_SOURCE
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// 资源编号
	wchar_t			wszIP[64];							// 种源IP地址
	WORD			wPort;								// 种源BT端口号
	ADD_SEED_SOURCE_MODE	addMode;					// 添加模式

	_ADD_SEED_SOURCE()
	{
		memset(this,0,sizeof(_ADD_SEED_SOURCE));
		cbSize = sizeof(_ADD_SEED_SOURCE);
		dwFlags = BTS_FLAGS_32[4];
	}
}ADD_SEED_SOURCE;

//文件目录信息
typedef struct _FILE_DIRECTORY_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	BOOL			bIsFile;							// 是否是文件
	wchar_t			wszName[128];						// 文件目录名

	_FILE_DIRECTORY_INFO()
	{
		memset(this,0,sizeof(_FILE_DIRECTORY_INFO));
		cbSize = sizeof(_FILE_DIRECTORY_INFO);
		dwFlags = BTS_FLAGS_32[2];
	}
}FILE_DIRECTORY_INFO;

//文件目录属性
typedef struct _FILE_DIRECTORY_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	BOOL			bDirectory;							// 是否是目录
	DWORD			dwFile;								// 子文件个数
	DWORD			dwDirectory;						// 子目录个数
	__int64			ulTotalSize;						// 总的大小

	_FILE_DIRECTORY_PROPERTY()
	{
		memset(this,0,sizeof(_FILE_DIRECTORY_PROPERTY));
		cbSize = sizeof(_FILE_DIRECTORY_PROPERTY);
		dwFlags = BTS_FLAGS_32[4];
	}
}FILE_DIRECTORY_PROPERTY;

//磁盘信息
typedef struct _DISK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszDisk[4];							// 磁盘盘符
	wchar_t			wszVolumnInfo[64];					// 卷标信息
	UINT			uDiskType;							// 磁盘类型
	__int64			ulTotal;							// 总共大小
	__int64			ulRemaining;						// 剩余大小

	_DISK_INFO()
	{
		memset(this,0,sizeof(_DISK_INFO));
		cbSize = sizeof(_DISK_INFO);
		dwFlags = BTS_FLAGS_32[5];
	}
}DISK_INFO;
//分组信息管理
typedef struct _GroupInfo
{
	wchar_t			wszGroupName[32][18];				// 所有支持的32个分组名称
}GroupInfo;
//分组名称
typedef struct _BT_GROUP_NAME
{
	wchar_t			wszGroupName[18];					// 单个分组名称,为空表示全部
}BT_GROUP_NAME;
//修改分组信息
typedef struct _MODIFY_GROUP_NAME
{
	BT_GROUP_NAME		oldGroupName;					// 老的分组名称
	BT_GROUP_NAME		newGroupName;					// 待修改的新分组名称
}MODIFY_GROUP_NAME;
//所有分组信息
typedef struct _GROUP_INFO
{
	BT_GROUP_NAME		gn[32];
}GROUP_INFO;

//UI界面登录输入
typedef struct _UI_LOGING_USERPSW
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszUserName[64];
	wchar_t			wszPassword[32];

	_UI_LOGING_USERPSW()
	{
		memset(this,0,sizeof(_UI_LOGING_USERPSW));
		cbSize = sizeof(_UI_LOGING_USERPSW);
		dwFlags = BTS_FLAGS_32[2];
	}
}UI_LOGING_USERPSW;

//同步数据进度结构
typedef struct _SYNC_DATA_PROGRESS
{
	DWORD			cbSize;
	DWORD			dwFlags;

	BOOL			bSyncing;							// 是否处于同步中
	DWORD			dwStatus;							// 同步状态(0:无同步或同步已完成,1:正在同步下载)
	DWORD			dwFileSize;							// 正在同步的文件大小
	DWORD			dwDownload;							// 正在同步的文件的完成大小
	wchar_t			wszFileName[64];					// 正在同步的文件名
	wchar_t			wszInfo[128];						// 信息

	_SYNC_DATA_PROGRESS()
	{
		memset(this,0,sizeof(_SYNC_DATA_PROGRESS));
		cbSize = sizeof(_SYNC_DATA_PROGRESS);
		dwFlags = BTS_FLAGS_32[6];
	}
}SYNC_DATA_PROGRESS;

//BT用户环境设置窗口
typedef	struct _BT_CONFIG_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;
	DWORD			dwFlags1;

	//端口映射
	BOOL			bMapPort;							// 是否映射BT端口
	BOOL			bMapRouterPort;						// 是否映射补种端口
	//登录设置
	wchar_t			wszUserName[32];					// BT用户账号
	wchar_t			wszPassword[32];					// BT用户密码
	wchar_t			wszOldPID[128];						// 上次成功登录的PID
	//环境设置
	BOOL			bDisablePublishGames;				// 禁止内网铺送游戏
	BOOL			bUPNP;								// 是否开启UPNP自动端口映射
	BOOL			bLimitLocalBandwidth;				// 是否限制本地带宽(内网下载、上传速度)
	BOOL			bAutoDeleteStopUpdate;				// 是否自动删除已停止更新的游戏
	BOOL			bAutoClearSpace;					// 是否自动清理空间(在磁盘空间不够时)
	BOOL			bNoManualToAuto;					// 手动下载时不改变更新方式为"自动更新"
	DWORD			dwUserNetLineType;					// 用户上网线路类型及性能(0:电信(ADSL),1:电信(10M光纤),2:电信(100M光纤),3:联通(ADSL),4:联通(10M光纤),5:联通(100M光纤),6:其它(ADSL),7:其它(10M光纤),8:其它(100M光纤))
	DWORD			dwSyncIntervalTime;					// 与服务器同步数据间隔时间(分钟)
	DWORD			dwHoldDiskSpace;					// 需要预留的磁盘空间大小
	wchar_t			wszServerIP[16];					// 服务器IP地址(内网连接外网用)
	int				iSoftMode;							// 程序模式(0:主服模式,1:从服模式,2:工作站模式
	//下载任务与速度
	DWORD			dwMaxActiveTask;					// 最大活动任务数
	DWORD			dwMaxDownloadTask;					// 最大下载任务数
	DWORD			dwMaxDownloadSpeed;					// 全局最大下载速度
	DWORD			dwMaxUploadSpeed;					// 全局最大上传速度

	DWORD			dwLANMaxDownloadSpeed;				// 内网最大下载速度(2013-07-24 新加)

	//下载端口
	DWORD			dwPort;								// BT端口
	DWORD			dwRouterPort;						// 补种端口
	//自动移除完成任务
	BOOL			bAutoRemoveCompletedTask;			// 是否自动移除已完成的活动任务
	BOOL			bAutoRemoveTime;					// 是否设置移除时间(上传时间达到此值时允许移除)
	BOOL			bAutoRemoveSpeed;					// 是否设置移除速度(下载速度小于此值时允许移除)
	DWORD			dwAutoRemoveTime;					// 自动移除需要上传时间超过此值
	DWORD			dwAutoRemoveSpeed;					// 自动移除需要下载速度小于此值
	//自动接受新游戏
	BOOL			bAutoAcceptNew;						// 是否自动接受新增加资源
	BOOL			bAutoAcceptNetGame;					// 是否自动接受新的网络游戏
	BOOL			bAutoAcceptHDGame;					// 是否自动接受新的单机游戏
	BOOL			bAutoAcceptToolSoft;				// 是否自动接受新的工具软件
	BOOL			bAutoAcceptFZTool;					// 是否自动接受新的辅助工具
	BOOL			bAutoAcceptSize;					// 是否限制自动接收的新资源的大小
	BOOL			bAutoAcceptRank;					// 是否限制自动接收的新资源的排行
	DWORD			dwAutoAcceptSize;					// 自动接受新游戏时游戏大小不得大于此值
	DWORD			dwAutoAcceptRank;					// 自动接受新游戏时游戏网络排行不得大于此值(默认不小于20)
	//下载目录
	wchar_t			wszCacheDirectory[128];				// 下载缓存目录盘(T:\temp)
	wchar_t			wszDefaultDirectory[8][64];			// 固定8大类的默认下载目录
	wchar_t			wszSSD[32];							// SSD盘符(H:\)									
	//时间段控制
	wchar_t			wszLimitSpeedTimePeriod[169];		// 速度限制时间段(0:无限制 1:限制 2:禁止）
	DWORD			dwLimitUploadRate;					// 当前自动限制的上传速度 
	DWORD			dwLimitDownloadRate;				// 当前自动限制的下载速度  
	//启动退出调用
	BOOL			bStartupRun_1;
	BOOL			bStartupRun_2;
	BOOL			bStartupRun_3;
	BOOL			bExitRun_1;
	BOOL			bExitRun_2;
	BOOL			bExitRun_3;
	wchar_t			wszStartupExe_1[64];
	wchar_t			wszStartupExe_2[64];
	wchar_t			wszStartupExe_3[64];
	wchar_t			wszStartupParam_1[64];
	wchar_t			wszStartupParam_2[64];
	wchar_t			wszStartupParam_3[64];
	wchar_t			wszExitExe_1[64];
	wchar_t			wszExitExe_2[64];
	wchar_t			wszExitExe_3[64];
	wchar_t			wszExitParam_1[64];
	wchar_t			wszExitParam_2[64];
	wchar_t			wszExitParam_3[64];	

	_BT_CONFIG_INFO()
	{
		memset(this,0,sizeof(_BT_CONFIG_INFO));
		cbSize = sizeof(_BT_CONFIG_INFO);
		dwFlags = BTS_FLAGS_32[32];
		dwFlags1 = BTS_FLAGS_32[29];
	}
}BT_CONFIG_INFO;

//设置游戏资源的简单属性
typedef struct _SET_GAME_SIMPLE_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Id;							// 编号(*必须填写)
	DWORD			dwIsPlan;							// 更新方式(0:不改变 1:手动 2:自动)
	DWORD			dwClearFile;						// 清除多余文件(0:不改变 1:手动 2:自动
	DWORD			dwTopGrade;							// 游戏等级(0:不改变 12345)
	DWORD			dwGroupMode;						// 分组方式(0:不改变 1:取消分组 2:设置分组)
	wchar_t			wszDirectory[360];					// 下载目录
	wchar_t			wszGroupName[32*18];				// 格式[勾选了的分组名称]|[勾选了的分组名称]...

	_SET_GAME_SIMPLE_PROPERTY()
	{
		memset(this,0,sizeof(_SET_GAME_SIMPLE_PROPERTY));
		cbSize = sizeof(_SET_GAME_SIMPLE_PROPERTY);
		dwFlags = BTS_FLAGS_32[7];
	}
}SET_GAME_SIMPLE_PROPERTY;

//获取游戏资源的简单属性
typedef struct _GET_GAME_SIMPLE_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Id;							// 编号(*必须填写)
	int				nGame_Flag;							// 状态
	DWORD			dwIsPlan;							// 更新方式(0:不改变 1:手动 2:自动)
	DWORD			dwClearFile;						// 清除多余文件(0:不改变 1:手动 2:自动
	DWORD			dwTopGrade;							// 游戏等级(0:不改变 12345)
	DWORD			dwGroupMode;						// 分组方式(0:不改变 1:取消分组 2:设置分组)
	wchar_t			wszDirectoryName[64];				// 游戏目录名
	wchar_t			wszDirectory[360];					// 下载目录
	wchar_t			wszAllGroupName[32*18];				// 有效的分组名称和是否勾选,格式:[是否勾选][分组名称]|[是否勾选][分组名称]...|,例如(0网游|1单机|1高清|0综艺|)(支持32个分组，每个分组信息占wchar_t[18])

	_GET_GAME_SIMPLE_PROPERTY()
	{
		memset(this,0,sizeof(_GET_GAME_SIMPLE_PROPERTY));
		cbSize = sizeof(_GET_GAME_SIMPLE_PROPERTY);
		dwFlags = BTS_FLAGS_32[9];
	}
}GET_GAME_SIMPLE_PROPERTY;

//游戏自动删除顺序结构
typedef struct _GAME_AUTO_DELETE_SORT
{
	DWORD		cbSize;
	DWORD		dwFlags;

	DWORD		dwGame_Id;								//编号
	wchar_t		wszGame_Text[32];						//名称
	wchar_t		wszGame_Reg[128];						//路径
	DWORD		dwGame_Click_Rate;						//总点击率
	DWORD		dwNet_Sort;								//网络排行
	DWORD		dwTopGrade;								//项目等级
	float		fInstDay;								//本地已经安装的天数

	_GAME_AUTO_DELETE_SORT()
	{
		memset(this,0,sizeof(_GAME_AUTO_DELETE_SORT));
		cbSize = sizeof(_GAME_AUTO_DELETE_SORT);
		dwFlags = BTS_FLAGS_32[7];
	}
}GAME_AUTO_DELETE_SORT;

//删除游戏顺序结构
typedef struct _GAME_DELETE_SORT
{
	DWORD		cbSize;
	DWORD		dwFlags;

	wchar_t		wszGame_Id[8];							//编号
	wchar_t		wszGame_Text[32];						//名称
	wchar_t		wszGame_Reg[128];						//路径
	int			nGame_Flag;								//操作标记(-3:未知状态,-2:无效数据(未启用),-1:已删除,0:未下载,1:有更新,2:已经更新（完成）,3:正在更新) //20121012修改加
	DWORD		dwNet_Sort;								//网络排行
	SYSTEMTIME	InstTime;								//本地安装时间
	DWORD		dwGameSize;								//大小(精确到MB)
	DWORD		dwTopGrade;								//项目等级
	DWORD		dwDeleteSort;							//暂时改为点击率（删除顺序(删除等级)）
	wchar_t		wszMonthDetail[121];					//
	float		fMonthClick;							//平均月点击
	//
	DWORD		dwMonthDetail[30];						//本地点击率的月详细值
	int			iInstalledDay;							//本地已经安装的天数

	_GAME_DELETE_SORT()
	{
		memset(this,0,sizeof(_GAME_DELETE_SORT));
		cbSize = sizeof(_GAME_DELETE_SORT);
		dwFlags = BTS_FLAGS_32[13];
	}
}GAME_DELETE_SORT;
//工作站属性
typedef struct _WORKSTATION_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwOldComputerID;					// 老的计算机编号(*必须填写)		****(原名:dwComputerID,修改:2013-03-25 13:51)
	DWORD			dwNewComputerID;					// 新的计算机编号(修改计算机编号用,如果与dwOldComputerID不同，表示计算机编号要修改) ****(新加:2013-03-25 13:51)
	wchar_t			wszComputerName[32];				// 计算机名
	wchar_t			wszIP[16];							// IP地址
	wchar_t			wszMAC[20];							// MAC地址
	wchar_t			wszAllGroupName[32*18];				// 有效的分组名称和是否勾选,格式:[是否勾选][分组名称]|[是否勾选][分组名称]...|,例如(0网游|1单机|1高清|0综艺|)(支持32个分组，每个分组信息占wchar_t[18])

	_WORKSTATION_PROPERTY()
	{
		memset(this,0,sizeof(_WORKSTATION_PROPERTY));
		cbSize = sizeof(_WORKSTATION_PROPERTY);
		dwFlags = BTS_FLAGS_32[6];
	}
}WORKSTATION_PROPERTY;
//服务器属性
typedef struct _SERVER_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszOldComputerName[32];				// 老的计算机名(*必须填写)			****(原名:wszComputerName[32],修改:2013-03-25 13:51)
	wchar_t			wszNewComputerName[32];				// 新的计算机名(修改计算机名用,如果与wszOldComputerName不同，表示计算机名要修改)		****(新加:2013-03-25 13:51
	wchar_t			wszIP[4][16];						// IP地址
	wchar_t			wszAllGroupName[32*18];				// 有效的分组名称和是否勾选,格式:[是否勾选][分组名称]|[是否勾选][分组名称]...|,例如(0网游|1单机|1高清|0综艺|)(支持32个分组，每个分组信息占wchar_t[18])

	_SERVER_PROPERTY()
	{
		memset(this,0,sizeof(_SERVER_PROPERTY));
		cbSize = sizeof(_SERVER_PROPERTY);
		dwFlags = BTS_FLAGS_32[4];
	}
}SERVER_PROPERTY;
//计算机编号
typedef struct _COMPUTER_ID
{
	DWORD			dwComputerID;						// 计算机编号
}COMPUTER_ID;
//计算机名称
typedef struct _COMPUTER_NAME
{
	wchar_t			wszComputerName[32];				// 计算机名
}COMPUTER_NAME;
//限制时段信息
typedef struct _LIMIT_TIME_PERIOD_INFO
{
	int			iMode;									//0:正常 1:限制 2:禁止
	DWORD		dwDownloadSpeed;						//下载速度(单位KB/s)
	DWORD		dwUploadSpeed;							//上传速度(单位KB/s)
}LIMIT_TIME_PERIOD_INFO;
/////////////////////////////////////////////////////////////////////////////////////////////
//检索本地游戏资源所用数据结构

//获取游戏定位信息
typedef struct _GET_GAME_LOCATE_INFO
{
	BOOL			bSuccess;
	DWORD			dwID;
	wchar_t			wszGameName[32];
}GET_GAME_LOCATE_INFO;

//获取游戏的更新状态请求结构
typedef struct _GET_GAME_LOCATE_STATUS_REQUEST
{
	int				iMode;								// (0:自动 1:强制有更新 2:强制已更新)
	DWORD			dwID;
	wchar_t			 wszDirectory[128];
}GET_GAME_LOCATE_STATUS_REQUEST;
//获取游戏的更新状态答复结构
typedef struct _GET_GAME_LOCATE_STATUS_REPLY
{
	int				 iFlag;
}GET_GAME_LOCATE_STATUS_REPLY;
//设置游戏定位信息
typedef struct _SET_GAME_LOCATE_INFO
{
	DWORD			dwID;								// 编号
	int				iFlag;								// (1:有更新 2:已更新)
	wchar_t			wszDirectory[128];
}SET_GAME_LOCATE_INFO;

//获取游戏搜索信息
typedef struct _SEARCH_INFO
{
	DWORD		cbSize;
	DWORD		dwFlags;

	DWORD		dwGameId;								// 游戏编号(0:未定位)
	DWORD		dwMode;									// 模式(0x01:wmblive.idx匹配,0x02:目录名与目录名匹配 0x04:目录名与游戏名匹配 0x08:关键字匹配 0x10:执行文件匹配 0x20:空目录
	wchar_t		wszLocalDirectory[128];					// 本地目录路径
	wchar_t		wszGameText[32];						// 游戏名称
	wchar_t		wszDirectoryName[32];					// 本地目录名

	_SEARCH_INFO()
	{
		memset(this,0,sizeof(_SEARCH_INFO));
		cbSize = sizeof(_SEARCH_INFO);
		dwFlags = BTS_FLAGS_32[5];
	}

}SEARCH_INFO;

#pragma pack(pop)

//----------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------函数-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

#include "MZD_INI.h"

typedef BOOL	(WINAPI* _btcInitConnect)(wchar_t* pwszIP,wchar_t* pwszPassword);	//初始化设置连接IP和密码
typedef DWORD   (WINAPI* _btcSendCommand)(const UINT iCommand,const char* pszInIni,const int iInIniSize,char** pszOutIni,int* pOutCount, int* pOutSize);		

typedef DWORD	(WINAPI* _btcGetFlags)(int iCount);
typedef BOOL	(WINAPI* _btcSockInitial)();
typedef int		(WINAPI* _btcSockRelease)();
//typedef BOOL	(WINAPI* _btcInitConnect)(wchar_t* pwszIP,wchar_t* pwszPassword);										//初始化连接
typedef void	(WINAPI* _btcReleaseEx)(char* pByte);																	//统一接口释放内存
//--------------
typedef int		(WINAPI* _btcConnectServ)();																			//联机BT服务
typedef int		(WINAPI* _btcUILogin)(UI_LOGING_USERPSW* pUilup,UI_LOGIN_REPLY* pUilr);									//UI登录
typedef int		(WINAPI* _btcGetLoginInfo)(UI_LOGIN_REPLY* pUilr);														//获取UI登录信息
typedef int		(WINAPI* _btcSetConnectPassword)(wchar_t* pwszNewPassword);												//设置联机密码
typedef int		(WINAPI* _btcSyncData)();																				//同步数据
typedef int		(WINAPI* _btcGetSyncProgress)(SYNC_DATA_PROGRESS* pSyncProgress);										//获取同步进度
typedef int		(WINAPI* _btcGetServerWorkStatus)(DWORD* pdwSrvWorkStatus);												//获取BT服务工作状态
typedef int		(WINAPI* _btcGetBtConfig)(BT_CONFIG_INFO* pBtConfig);													//获取BT配置环境
typedef int		(WINAPI* _btcSetBtConfig)(BT_CONFIG_INFO* pBtConfig);													//设置BT配置环境
typedef int		(WINAPI* _btcGetMenuConfig)(MENU_CONFIG* pMenuConfig);													//获取菜单配置环境
typedef int		(WINAPI* _btcSetMenuConfig)(MENU_CONFIG* pMenuConfig);													//设置菜单配置环境
typedef int     (WINAPI* _btcGetLimitTimePeriodInfo)(LIMIT_TIME_PERIOD_INFO* pLimitTPI);								//获取限制时段信息
typedef int		(WINAPI* _btcClearBtRegInfo)();																			//清除BT注册信息
//--------------
typedef int		(WINAPI* _btcGetGamesInfo)(RESOURCE_INFO** pRi,COMMAND_PARAM* pCp,int* piCount);						//获取游戏信息		
typedef int		(WINAPI* _btcGetGamesInfo_1)(char** pResultBuff,COMMAND_PARAM* pCp,int* piResultCount);

typedef void    (WINAPI* _btcReleaseGamesInfo)(RESOURCE_INFO** pRi);													//释放辅游戏信息
typedef int		(WINAPI* _btcGetWgsInfo)(T_WgsInfo** pWi,int* piCount);													//获取辅助工具信息
typedef void    (WINAPI* _btcReleaseWgsInfo)(T_WgsInfo** pWi);															//释放辅助工具信息
typedef int		(WINAPI* _btcGetParentClassInfo)(T_ClassInfo** pPci,int* piCount);										//获取菜单大类信息
typedef void    (WINAPI* _btcReleaseParentClassInfo)(T_ClassInfo** pPci);												//释放菜单大类信息
typedef int		(WINAPI* _btcGetSubClassInfo)(T_ClassInfo** pSci,int* piCount);											//获取菜单小类信息
typedef void    (WINAPI* _btcReleaseSubClassInfo)(T_ClassInfo** pPci);													//释放菜单小类信息
typedef int		(WINAPI* _btcGetMovieInfo)(T_Movie** pMi,int* piCount);													//获取T_MovieInfo数据
typedef void    (WINAPI* _btcReleaseMovieInfo)(T_Movie** pMi);															//释放T_MovieInfo数据
typedef int		(WINAPI* _btcGetOnlineInfo)(T_Online** pOi,int* piCount);												//获取T_Online数据	
typedef void    (WINAPI* _btcReleaseOnlineInfo)(T_Online** pOi);														//释放T_Online数据
typedef int		(WINAPI* _btcGetPlayerListInfo)(T_PlayerList** pPli,int* piCount);										//获取T_Player数据		
typedef void    (WINAPI* _btcReleasePlayerListInfo)(T_PlayerList** pPli);												//释放T_Player数据
typedef int     (WINAPI* _btcGetSingleGameInfo)(RESOURCE_INFO* pRi);													//获取单个游戏资源信息
//
typedef int		(WINAPI* _btcSetParentClassInfo)(T_ClassInfo** pCi,int* piCount);										//设置T_ParentClass大类数据
typedef int		(WINAPI* _btcSetSubClassInfo)(T_ClassInfo** pCi,int* piCount);											//设置T_SubClass小类数据
typedef int		(WINAPI* _btcSetMovieInfo)(T_Movie** pMi,int* piCount);													//设置T_MovieInfo数据
typedef int		(WINAPI* _btcSetOnlineInfo)(T_Online** pOi,int* piCount);												//设置T_Online数据
typedef int		(WINAPI* _btcSetPlayerListInfo)(T_PlayerList** pPli,int* piCount);										//设置T_Player数据
//--------------公共游戏资源设置、操作指令
typedef int		(WINAPI* _btcGameGetSuperfluousInfo)(RESOURCE_INFO** pRi,int* piCount);									//获取多余的已停止更新的资源数据
typedef void	(WINAPI* _btcReleaseGameSuperfluousInfo)(RESOURCE_INFO** pRi);											//释放多余的已停止更新的资源数据
typedef int		(WINAPI* _btcGameGetDeleteSort)(GAME_DELETE_SORT** pGds,int* piCount);									//获取游戏删除顺序数据
typedef void	(WINAPI* _btcReleaseGameDeleteSort)(GAME_DELETE_SORT** pGds);											//释放游戏删除顺序数据
typedef int		(WINAPI* _btcGetSimpleProperty)(GET_GAME_SIMPLE_PROPERTY* pgetGsp);										//获取指定资源的简单属性
typedef int		(WINAPI* _btcSetSimpleProperty)(SET_GAME_SIMPLE_PROPERTY* psetGsp);										//设置指定资源的简单属性
typedef int		(WINAPI* _btcGetBtSystemInfo)(BT_SYSTEM_INFO* pBtSi);													//获取BT系统概况信息
typedef int		(WINAPI* _btcGetResourceNumber)(BT_RESOURCE_NUMBER* pBtRn);												//获取资源数
typedef int		(WINAPI* _btcGameDelete)(DWORD dwGameId);																//删除资源
typedef int		(WINAPI* _btcGameClearFileDir)(DWORD dwGameId);															//清除多余文件目录	
typedef int		(WINAPI* _btcGameMoveDirectory)(GAME_MOVE_DIRECTORY* pGmd);												//移动游戏目录
typedef int		(WINAPI* _btcGameRepair)(DWORD dwGameId);																//游戏修复
typedef int		(WINAPI* _btcGameSetAutoUpdate)(DWORD dwGameId);														//资源设置自动更新方式
typedef int		(WINAPI* _btcGameSetManualUpdate)(DWORD dwGameId);														//资源设置手动更新方式
//--------------自定义游戏资源操作指令
typedef int		(WINAPI* _btcAddCustomGame)(RESOURCE_PROPERTY* pRp);													//添加自定义游戏资源
typedef int		(WINAPI* _btcAddCustomWeb)(RESOURCE_PROPERTY* pRp);														//添加自定义WEB资源
typedef int		(WINAPI* _btcGetCustomGameMaxId)(DWORD* pdwMaxID);														//自动获取最大自定义游戏编号
typedef int		(WINAPI* _btcGetCustomGameProperty)(DWORD dwGameId,RESOURCE_PROPERTY* pRp);								//获取自定义游戏属性
typedef int		(WINAPI* _btcModifyCustomGameProperty)(RESOURCE_PROPERTY* pRp);											//修改自定义游戏属性
typedef int		(WINAPI* _btcDeleteCustomGame)(DWORD dwGameId);															//删除自定义游戏
//--------------Task操作指令
typedef int		(WINAPI* _btcGetTaskInfo)(TASK_INFO** pTask,int* piCount);												//获取所有活动任务信息
typedef void	(WINAPI* _btcReleaseTaskInfo)(TASK_INFO** pTask);														//释放所有活动任务信息
typedef int		(WINAPI* _btcTaskGetTrackerInfo)(DWORD dwID,PACK_TRACKER_INFO_ENTRY* pTie);								//获取指定任务的Tracker信息
typedef int		(WINAPI* _btcTaskGetPeerInfo)(DWORD dwID,PACK_PEER_INFO_ENTRY** pPie,int* piCount);						//获取指定任务的节点信息
typedef void	(WINAPI* _btcReleaseTaskPeerInfo)(TASK_INFO** pPie);													//释放指定任务的节点信息
typedef int		(WINAPI* _btcTaskAddDownload)(DWORD dwID);																//添加一个下载任务
typedef int		(WINAPI* _btcTaskSSDDownload)(DWORD dwID);																//SSD磁盘方式下载
typedef	int		(WINAPI* _btcTaskPropertyDownload)(SET_GAME_SIMPLE_PROPERTY* psetGsp);									//属性方式添加下载
typedef	int		(WINAPI* _btcTaskAddSeed)(TASK_SEED_DATA* pTsd);														//添加一个做种任务
typedef int		(WINAPI* _btcTaskAddSeedSource)(ADD_SEED_SOURCE* pAss);													//给指定任务添加一个种源
typedef int		(WINAPI* _btcTaskStart)(DWORD dwID);																	//开始任务
typedef int		(WINAPI* _btcTaskStop)(DWORD dwID);																		//停止任务
typedef int		(WINAPI* _btcTaskCheck)(DWORD dwID);																	//检查任务
typedef int		(WINAPI* _btcTaskRemove)(DWORD dwID);																	//移除任务
typedef int		(WINAPI* _btcTaskTop)(DWORD dwID);																		//任务置顶
typedef int		(WINAPI* _btcTaskUp)(DWORD dwID);																		//任务上移
typedef int		(WINAPI* _btcTaskDown)(DWORD dwID);																		//任务下移
typedef int		(WINAPI* _btcTaskLimitSpeed)(DWORD dwID);																//任务限制速度
typedef int		(WINAPI* _btcTaskSort)(DWORD dwID);																		//任务排序
typedef int		(WINAPI* _btcTaskRefreshTracker)(DWORD dwID);															//任务强制重连一次
//--------------分组、工作站、服务器
typedef int		(WINAPI* _btcInsertGroup)(BT_GROUP_NAME* pInstGroup);													//添加一个分组信息
typedef int		(WINAPI* _btcModifyGroup)(MODIFY_GROUP_NAME* pModGroup);												//修改一个分组信息
typedef int		(WINAPI* _btcDeleteGroup)(BT_GROUP_NAME* pDelGroup);													//删除一个分组信息
typedef int		(WINAPI* _btcGetGroupInfo)(GroupInfo* pAllGi);															//获取所有分组信息
typedef int		(WINAPI* _btcGetWorkstationInfo)(T_WorkstationInfo** pWk,BT_GROUP_NAME gn,int* piCount);				//获取指定分组中的工作站信息	
typedef void    (WINAPI* _btcReleaseWorkstationInfo)(T_WorkstationInfo** pWk);											//释放指定分组中的工作站信息
typedef int		(WINAPI* _btcGetServerInfo)(T_ServerInfo** pSrv,BT_GROUP_NAME gn,int* piCount);							//获取指定分组中的服务器信息
typedef void    (WINAPI* _btcReleaseServerInfo)(T_ServerInfo** pSrv);													//释放指定分组中的服务器信息
typedef int		(WINAPI* _btcDeleteWorkstation)(COMPUTER_ID ci);														//删除一台工作站
typedef int		(WINAPI* _btcDeleteServer)(COMPUTER_NAME cn);															//删除一台服务器
typedef int		(WINAPI* _btcGetWorkstationProperty)(WORKSTATION_PROPERTY* pWkp);										//获取一台工作站属性
typedef int		(WINAPI* _btcSetWorkstationProperty)(WORKSTATION_PROPERTY* pWkp);										//设置一台工作站属性(如果没有找到对应的工作站，就新加)
typedef int		(WINAPI* _btcGetServerProperty)(SERVER_PROPERTY* pSrvp);												//获取一台服务器属性
typedef int		(WINAPI* _btcSetServerProperty)(SERVER_PROPERTY* pSrvp);												//设置一台服务器属性(如果没有找到对应的服务器，就新加)
typedef int		(WINAPI* _btcSyncMzdWorkstation)();																		//同步MZD工作站信息
typedef int		(WINAPI* _btcSyncMzdServer)();																			//同步MZD服务器信息
//--------------磁盘目录操作指令
typedef int		(WINAPI* _btcGetDiskInfo)(DISK_INFO** pDi,int* piCount);												//获取磁盘信息
typedef	void	(WINAPI* _btcReleaseDiskInfo)(DISK_INFO** pDi);															//释放磁盘信息
typedef int		(WINAPI* _btcGetFileDirectoryInfo)(wchar_t* pwszPath,FILE_DIRECTORY_INFO** pFdi,int* piCount);			//获取文件目录信息
typedef void	(WINAPI* _btcReleaseDirectoryInfo)(FILE_DIRECTORY_INFO** pFdi);											//释放文件目录信息
typedef int		(WINAPI* _btcGetFileDirectoryProperty)(wchar_t* pwszPath,FILE_DIRECTORY_PROPERTY* pFdp);				//获取文件目录属性
typedef int		(WINAPI* _btcGetDirectorySize)(wchar_t* pwszDisk,__int64* pDiskSize);									//获取目录大小(单位Byte）

//----------资源搜索定位操作指令
typedef int		(WINAPI* _btcStartSearch)(wchar_t* pSearchParentDirectory);												//开始游戏定位搜索	
typedef int		(WINAPI* _btcStopSearch)();																				//结束游戏定位搜索
typedef int		(WINAPI* _btcCoverLocate)();																			//覆盖方式定位				
//pli:			返回定位的具体信息SEARCH_INFO
typedef int		(WINAPI* _btcGetLocate)(SEARCH_INFO** pSearchInfo,int* piCount);												//获取游戏定位信息
typedef int		(WINAPI* _btcGetLocateStatus)(GET_GAME_LOCATE_STATUS_REQUEST* pRequest,GET_GAME_LOCATE_STATUS_REPLY* pReply);	//获取游戏定位状态
typedef int		(WINAPI* _btcSetLocate)(SET_GAME_LOCATE_INFO* pSet);													//设置游戏定位信息
#endif