#pragma once
#include "MZD_INI.h"

#pragma pack(push)//保存对齐状态
#pragma pack(1)//保存对齐状态

#define MZD_MAX_WKS_NUMBER_LENGTH 4   //工作站数字编号长度
#define MZD_DISPLAYNAME_LENGTH 32 //显示名称长度
#define MZD_BACKUP_ADAPT_NAME_LENGTH (32*2) //备用服务器网卡名称
#define MZD_UNDODIR_LENGTH 64 //undo路径长度
#define MZD_SERVER_NAME_LENGTH 32 //服务器名称,长度
#define MZD_DISKSET_NAME_LENGTH 32
#define MZD_WORKDIR_LENGTH 32
#define MZD_COMPOSE_NAME_LENGTH (3*MZD_SERVER_NAME_LENGTH) //组合名称长度
#define MZD_SRCRES_LENGTH 20 //分辨率长度
#define MZD_PRE_AFX_NAME_LENGTH 20 //前后缀长度
#define MZD_GROUP_NAME_LENGTH 32 //分组长度

#define MZD_GET_WKS_MSG 1//获取所有工作站
#define MZD_ADD_WKS_MSG 2//添加工作站
#define MZD_MODIFY_WKS_MSG 3//修改工作站
#define MZD_DEL_WKS_MSG 4//删除工作站
#define MZD_WKS_CMD_MSG 5// 工作站命令
#define MZD_ADD_DISK_MSG 6//添加磁盘设置
#define MZD_MODIFY_DISK_MSG 7//修改磁盘设置
#define MZD_DEL_DISK_MSG 8//删除磁盘设置
#define MZD_GET_MENU_MSG 9//获取菜单设置
#define MZD_GET_GLOBAL_SET_MSG 13//获取全局设置
#define MZD_SET_GLOBAL_SET_MSG 14//修改全局设置
#define MZD_GET_INI_MSG 15//获取INI//返回数据内容为INI数据，不需要结构
#define MZD_GET_LOG_MSG 16//获取日志//	返回数据内容为日志内容，不需要结构
#define MZD_GET_FIX_LIST_MSG 18//获取FIX列表
#define MZD_GET_UPLOAD_FIX_LISG_MSG 19//获取可上传FIX列表
#define MZD_GET_UDO_LISG_MSG 20//获取UDO列表
#define MZD_DISK_FORMAT_CHANGE_MSG 23//IMG包格式转换
#define MZD_DISK_FORMAT_CHANGE_CHECK_MSG 24//IMG包格式转换验证
#define MZD_GET_MZD_LIST_MSG 25//获取MZD文件列表
#define MZD_GET_DISK_NAMELIST_MSG 26//获取磁盘列表名称
#define MZD_GET_PHYSICALDISKID_MSG 27//获取硬盘序列号
#define MZD_REGISTER_MSG 28 //注册请求 
#define MZD_DISK_MAITAIN_MSG 31 //磁盘维护命令
#define MZD_GET_UPDATE_FILE_MSG 32 //获取主服更新版本//SOCKET接收请求包头
#define MZD_ADD_SERVER_MSG 33 //添加服务器设置(新版消息)
#define MZD_MODIFY_SERVER_MSG 34 //修改服务器设置(新版消息)
#define MZD_DEL_SERVER_MSG 35  //删除服务器设置(新版消息)
#define MZD_GET_SERVER_LIST_MSG 36//获取所有服务器设置(新版消息)
#define MZD_GET_IMG_DISK_SIZE_MSG 37 //获取IMG包磁盘大小
#define MZD_GET_DISKSET_BYSERVERNAME_MSG 38//获取指定服务器名磁盘设置
#define MZD_GET_ALL_SERVER_ADAPT_MSG 39 //获取所有服务器的所有可用网卡名
#define MZD_GET_SERVER_TASK_LIST_MSG 40 //根据服务器名获取该服务器任务列表
#define MZD_GET_IMG_PARTITION_PHYSICAL_MSG 41 //获取IMG包,分区,物理盘
#define MZD_MODIFY_WKS_LIST_MSG 42//批量修改工作站
#define MZD_GET_SERVICE_STATUS_MSG 43 //获取服务状态
#define MZD_GET_SERVER_WORKDIR_MSG 44 //获取服务器工作目录状态
#define MZD_SERVER_CMD_MSG 45 //服务器命令操作
#define MZD_GET_GET_SERVER_INFO_MSG 46 //获取服务器信息命令
#define MZD_GET_MZ_REG_MSG 47 //获取该服务器注册信息
#define MZD_GET_DISKSET_BYSERVERNAME_MSG_EX 48//获取指定服务器名磁盘设置
#define MZD_GET_CACHE_INFO_MSG 49  //获取缓存信息
#define MZD_MODIFY_WKS_MAC_MSG 50//修改工作站MAC地址
#define MZD_GET_CACHE_REG_INFO_MSG 51//获取缓存和注册信息
#define MZD_SET_CACHE_MSG 52 //设置缓存
#define MZD_REMOVE_CACHE_MSG 53 //取消缓存
#define MZD_REMOVE_CACHE_EX_MSG 54 //取消缓存,但是不删除配置,下次启动时仍有效
#define MZD_CHANGE_WKS_NUMBER_MSG 55 //互换工作站编号
#define MZD_GET_WKS_BY_WKSNUM_MSG 56 //获取指定工作站的信息

enum MzdTaskType
{
	Mzd_New_Img_Type = 0,
	Mzd_Acc_Img_Type,
	Mzd_Direct_Update_Type,
	Mzd_Backup_Update_Type,
	Mzd_Restore_Disk_Type,
	Mzd_Sync_Disk_Type,
	Mzd_Generate_New_Disk_Type,
	Mzd_Sync_Disk_Remote_Img_Type,
	Mzd_Change_format_Type,
	Mzd_Img_Check_Type
};

enum WKS_CMD_TYPE
{
	WKS_SHUTDOWN_TYPE = 0,//关闭工作站
	WKS_RESTART_TYPE,//重启工作站
	WKS_WAKEUP_TYPE,//唤醒工作站
	WKS_FORBIDDEN_TYPE,//禁用工作站
	WKS_REUSE_TYPE,//启用工作站
};

enum tagMzdResult
{
	MZD_SUCCESS = 0,//成功
	MZD_MODIFY_NAME_FAILED =1,//修改成功，但名称修改失败
	MZD_ADD_FAILED_REASON_EXIST = 2,//添加失败，存在该设置,编号存在或MAC存在
	MZD_CFG_NOT_EXIST_ERROR = 3,//不存在该设置
	MZD_SERVER_NOT_EXIST_ERROR = 4,//服务器设置不存在
	MZD_DISKNAME_IMGPATH_ERROR = 5,//磁盘名或IMG包路径错误
	MZD_DISKSET_IS_IN_USE_ERROR = 6,//磁盘设置,服务器设置正在使用中，不能删除
	MZD_GET_REMOTE_IMG_SECTOR_ERROR = 7,//获取远端扇区数失败
	MZD_NETWORK_ERROR = 8,//网络错误
	MZD_FORBIDDEN_ERROR = 9,//禁止操作
	MZD_WKS_CFG_EXIST_ERROR = 10,//工作站存在,提示是否删除
	MZD_MODIFY_NAME_EXIST_ERROR = 11,//修改名称存在,不能将其修改为该名称
	MZD_PASSWORD_ERROR = 12,//通讯密码错误
	MZD_ILLEGAL_CONNECT_ERROR = 13,//非法链接
	MZD_MODIFY_GLOBAL_SUPERWKS_ERROR = 14,//修改全局设置中修改超管失败，原超管工作站在线，需要重启该超管工作站
	MZD_IP_CLASH_ERROR = 15,//IP地址与其他设置的IP冲突
	MZD_MAC_CLASH_ERROR = 16,//操作失败,MAC地址冲突
	MZD_NUMBER_CLASH_ERROR = 17,//操作失败,编号冲突
	MZD_SERVERNAME_ERROR = 18,//操作失败,服务器名称冲突
	MZD_GATEWAY_ERROR = 19,//操作失败,服务器名称冲突
	MZD_Res_Msg_Succeed = 40,//操作成功
	MZD_Res_Msg_Succeed_Login = 41,//
	MZD_Res_Msg_Succeed_Login_KEYFILE = 42,//取码生成KEY文件成功
	MZD_Res_Msg_Succeed_Verify = 43,//校验成功
	MZD_Res_Msg_Succeed_ChangePCCount = 45,//更改机器台数成功
	MZD_Res_Msg_fail_Interval = 51,//= '(51)取码间隔太短';
	MZD_Res_Msg_fail_HD_UnReg = 52,//= '硬盘号未注册';
	MZD_Res_Msg_fail_IPError = 53,//= '(53)注册IP错误';
	MZD_Res_Msg_fail_PassErr = 54,//= '(54)用户密码错误';
	MZD_Res_Msg_fail_TimeOut = 55,//= '(55)使用期限已过';         
	MZD_Res_Msg_fail_Active = 56,//= '(56)用户被限制使用';
	MZD_Res_Msg_fail_VerOld = 57,//= '(57)需更新版本';
	MZD_Res_Msg_fail_VerDisable = 58,//= '(58)此版本已限制使用';
	MZD_Res_Msg_fail_BindClinet = 59,//    = '(59)绑定客户端需要更高版本';
	MZD_Res_Msg_fail_DEMO = 60,//= 'DEMO版';
	MZD_Res_Msg_fail_NetErr = 61,//= '(61)网络错误';
	MZD_Res_Msg_fail_AgentNOFail = 62,//= '请用新代理商编码'; 
	MZD_Res_Msg_fail_Verify = 63,//= '校验失败,时间错误';
	MZD_Res_Msg_fail_Unknown = 64,// = '未知错误';
	MZD_Res_Msg_fail_SmsCode = 65,//短信码验证错误
	Res_Msg_fail_MobileInvalid = 66,//无效的手机号码网吧业主手机号码错误
	Res_Msg_fail_MobileBlack = 67,//手机号码是黑名单
	Res_Msg_fail_MobileProtect = 68,//目标手机号码在保护名单内
	Res_Msg_fail_MobileFail = 69,//发送短信失败
	Res_Msg_fail_Login = 70,//登录失败
	Res_Msg_fail_HDExpired = 71,//硬盘已过期
	Res_Msg_fail_Save = 72,//保存数据失败
	MZD_UNKOWN_MSG_ERROR = 73,//未知消息
	MZD_SERVICE_NOT_START = 74,//服务未运行
};

#define MZD_CMD_PORT 10700



typedef struct _tagGlobalSet
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效

	DWORD	undoNums;	//最大还原次数
	TCHAR	wksDefPassword[20];	//13303  13187069098 
	DWORD	passwordCrc;
	TCHAR	undoDir[64];	//还原文件目录
	bool	isDisableTelnet;	//远程界面开关
	bool	isDisableDebug;	//调式模式开关
	bool	isShowRegFMFlag;      // for IO Server Not Show Reg FM 用作IO服务器不显示注册窗口
	WORD	dhcpFastMode;			//dhcp快速模式，就是一次性多发25个OFFER包
	BYTE	fixFormat;
	bool	isWanTonFlag;				//记录注册线路是不是网通
	bool	isEnableStrap;		//MHD外挂开关
	bool	isAutoNumber;				//自动编号
	bool	isAutoAdd;					//自动添加工作站
	bool	isCompulsoryNumber;			////自动覆盖编号
	bool	isDisableDhcp;				//关闭MS DHCP 开关
	TCHAR	regDomainAddress[64];	//注册服务器域名
	TCHAR	removeIp[255];   //分配DHCP时，要排除的IP列表，
	DWORD	loginServerIP; //主服IP
	WORD	superWks;				//超级工作站编号
	bool	isEnableSysDiskForSuperWks;  //超级工作站能改动的磁盘开关
	bool 	isEnableDataDisk1ForSuperWks;
	bool 	isEnableDataDisk2ForSuperWks;
	bool 	isEnableDataDisk3ForSuperWks;
	bool	isDhcpQuickResponse;
	bool	isAutoSyncUpdateForSuperWks;//超级工作站关机后，自动同步开关。
	DWORD	arDataSourceIP[64];		//IMG包同步数据源IP列表
	TCHAR	runExternal[255];		//运行外部程序。	
	bool	isWaitCompleted;	//等待运行外部程序运行完成。
	TCHAR	LanguagePack[255];	//语言包
	DWORD   m_MemType;//内存模式,0:普通内存，1：AWE内存
	TCHAR m_WksWorkDir[255];//工作站工作目录
	TCHAR m_SsdPartition[2];//ssd盘符
	DWORD dwFlags1; // 控制后面哪个字段生效

	bool bRestartRestore;//重启自动恢复
	DWORD m_LastUpdateTime;//最后修改的时间
	DWORD m_LogLevel;//日志等级
	DWORD	spareServerIP; //备用注册服IP
}tagGlobalSet;

typedef struct _tagGetGlobalSetEx
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	_tagGlobalSet globalset;
	TCHAR RegisterHdid[16];
	TCHAR spareRegisterHdid[16];
}tagGetGlobalSetEx;


typedef struct _tagServerCfg
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效

	TCHAR serverName[32];//服务器名称
	DWORD adaptIp[4];//服务器网卡IP
	TCHAR backupAdaptName[4][96];//备用服务器网卡名称
	DWORD writeCacheSize;//写缓存大小
	DWORD systemCacheSize;//系统盘缓存大小
	DWORD dataCacheSize;//数据盘缓存大小
	DWORD ssdCacheSize;//SSD缓存大小
	TCHAR ssdDisk[2];//SSD盘符
	TCHAR workDir[4][32];//工作路径
	TCHAR networkGameGroup[32];//游戏服务器分组
	bool bServerUseHotBackup;//是否启用热备
	int serverConnectStatus;//服务器连接状态
	int serverType;//服务器类型
}tagServerCfg;

typedef	struct _tagServerName
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR servername[32];
}tagServerName;

typedef	struct _tagServerIp
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	DWORD serverIp[4];
}tagServerIp;

typedef	struct _tagDiskSet
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	bool	isAutoUpload;  //上传还原开关
	bool	isAllowUpload;
	bool	isAllowRevert;
	bool	isAllowClear;
	bool	isAutoRevert;
	bool	isAutoClear;
	DWORD	readCacheSize;     // Per Disk Read Cache Size//读缓存大小
	DWORD	writeCacheSize;    // MZD Server Write Cache Size
	BYTE	abreastSum;			//并发数
	int		retryTimeOut;      //和服务端失去连接时，重试时间  ：-1 永不超时
	BYTE	dosReadSize,dosWriteSize; // Win 4-7 bits ,dos 0-3 bits    // -1
	BYTE	winReadSize,winWriteSize; // win 4-7 bits ,dos 0-3 bits    // -1
	short	localCacheSize;				//本地缓存总开关
	bool	isDelayLoad;				 //延时加载
	bool	isIScsiBoot;				//iSCSI引导开关
	TCHAR	clientWriteDir[32];		//客户端回写目录
	DWORD	diskQuota;		//磁盘配额
	DWORD	dirIp;					// Disk Img Host address
	DWORD	mirrIp;					 //磁盘镜像IP
	DWORD	hotBakIP;
	DWORD	ssdCacheSize;				 //SSD 缓存
	TCHAR	ssdVolum[8];
	TCHAR	destinationFile[64];			//磁盘目标设备
	TCHAR	arWorkDir[4][32];		//磁盘工作路径
	TCHAR	diskName[96];		//磁盘设置名称
	DWORD readCacheType;//0:普通内存，1：AWE内存
	DWORD writeCacheType;//0:普通内存，1：AWE内存
	TCHAR    diskDisplayName[32];//磁盘设置显示名称
	DWORD diskType;//磁盘类型（0：虚拟系统盘，1：虚拟数据盘）
	DWORD disksize;//磁盘大小（MB）

	DWORD dwFlags1; // 控制后面哪个字段生效
	TCHAR serverName[32];
	DWORD serverIp[4];//服务器IP
}tagDiskSet;

typedef	struct _tagGetDisksetNameList
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR disksetname[96];
}tagGetDisksetNameList;

typedef struct _tagMenuSetEx
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR displayname[MZD_DISPLAYNAME_LENGTH];
	TCHAR diskName[4][MZD_COMPOSE_NAME_LENGTH];
	DWORD start_mode;//启动模式
}tagMenuSetEx;

typedef struct _tagWkstationEx
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	DWORD wksNumber;
	TCHAR  wksName[32];
	DWORD wksIp;
	TCHAR wksMac[32];
	DWORD subMask;
	DWORD gateway;
	TCHAR scrRes[20];//分辨率
	TCHAR groupId[32];//归属分组
	DWORD numberLength;//编号长度
	tagMenuSetEx menuGroup[4];
	DWORD startMode;
	DWORD LocalMemoryCache;//工作站本地缓存
	bool bStartHotBack;//是否启用热备
	bool bAutoRestore;//工作站是否自动还原
	TCHAR comPre[20];//计算机前缀
	TCHAR comAfx[20];//计算机后缀
	DWORD dns1;
	DWORD dns2;
	DWORD startServerIp;//启动服务器IP
	bool bSuperMode;
	bool bOnlineStatus;
	bool bForbidStatus;
	bool bSuperOnline;//超管在线检测
}tagWkstationEx;

enum MzdErrorCmd
{
	REPORT_ERROR,//报告错误
	IGNORE_ONE_ERROR,//操作，但忽略一次错误
	IGNORE_ALL_ERROR,//操作，并忽略所有错误
	JUMP_ONE_ERROR,//跳过一次错误操作
	JUMP_ALL_ERROR//跳过所有错误操作
};


//添加修改工作站使用同一个结构体
typedef struct _tagModifyWksInfo
{
	DWORD startIp;//起始IP(添加使用)
	DWORD oldWksNumber;//原工作站编号(修改使用)(获取工作站信息时必须输入该编号)
	MzdErrorCmd bIgnoreError;//错误处理逻辑
	bool bAloneWks;//是否单台工作站(单台添加时工作站IP为用户指定,批量添加工作站是IP是根据起始IP和编号确定)
	DWORD startNumber;//起始编号
	DWORD endNumber;//结束编号
	_tagWkstationEx wks;//工作站信息
	_tagModifyWksInfo()
	{
		memset(this,0,sizeof(_tagModifyWksInfo));
	}

	/*void SetValue(MZD_INI& ini,DWORD secNum = 0)
	{
		MZD_CHAR classname[MAX_PATH];
		GETCLASSNAME(classname,MAX_PATH);
		ini.ReadIpFromINI(classname,secNum,STR(startIp),startIp,MZD_T("0.0.0.0"));
		ini.ReadFromINI(classname,secNum,STR(oldWksNumber),oldWksNumber,0);
		ini.ReadFromINI(classname,secNum,STR(bIgnoreError),(int&)bIgnoreError,0);
		ini.ReadFromINI(classname,secNum,STR(bAloneWks),bAloneWks,false);
		ini.ReadFromINI(classname,secNum,STR(startNumber),startNumber,0);
		ini.ReadFromINI(classname,secNum,STR(endNumber),endNumber,0);
		MZD_CHAR temp_sec_name[MAX_PATH];
		int temp_sec_num;
		ini.ReadFromINI(classname,secNum,STR(wks),temp_sec_name,MAX_PATH,MZD_T(""));
		MZD_INI::SpliteSecName(temp_sec_name,temp_sec_num);
		wks.SetValue(ini,temp_sec_num);
	}

	DWORD Write2INI(MZD_INI& ini,MZD_CHAR* pOutClassName = NULL,DWORD max_length = 0)
	{
		MZD_CHAR classname[MAX_PATH];
		GETCLASSNAME(classname,MAX_PATH);
		DWORD sec_num = ini.CreateSecNumber(classname);
		ini.WriteIp2INI(classname,sec_num,STR(startIp),startIp);
		ini.Write2INI(classname,sec_num,STR(oldWksNumber),oldWksNumber);
		ini.Write2INI(classname,sec_num,STR(bIgnoreError),bIgnoreError);
		ini.Write2INI(classname,sec_num,STR(bAloneWks),bAloneWks);
		ini.Write2INI(classname,sec_num,STR(startNumber),startNumber);
		ini.Write2INI(classname,sec_num,STR(endNumber),endNumber);
		MZD_CHAR temp_sec_name[MAX_PATH];
		int temp_sec_num = wks.Write2INI(ini,temp_sec_name,MAX_PATH);
		ini.Write2INI(classname,sec_num,STR(wks),temp_sec_name);
		if (pOutClassName)
		{
			MZD_INI::GetSectionName(classname,sec_num,pOutClassName,max_length);
		}
		return sec_num;
	}*/
}tagModifyWksInfo,tagAddWksInfo,tagAddWksInfoUI,_tagAddWksInfoUI,tagModifyWksInfoUI,_tagModifyWksInfoUI,tagGetWksInfo,tagGetWksInfoUI;

//typedef struct _tagModifyWksInfo
//{
//	//DWORD cbSize; // 结构总的大小
//	//DWORD dwFlags; // 控制后面哪个字段生效
//	DWORD startIp;//起始IP(添加使用)
//	DWORD oldWksNumber;//原工作站编号(修改使用)
//	int	  nIgnoreError;//错误标志位
//	bool bAloneWks;//是否单台工作站(单台添加时工作站IP为用户指定,批量添加工作站是IP是根据起始IP和编号确定)
//	DWORD startNumber;//起始编号
//	DWORD endNumber;//结束编号
//	_tagWkstationEx wks;//工作站信息
//	_tagModifyWksInfo()
//	{
//		memset(this,0,sizeof(_tagModifyWksInfo));
//		cbSize = sizeof(_tagModifyWksInfo);
//		dwFlags = 0x0F;
//	}
//}tagModifyWksInfo,tagAddWksInfo;
//

typedef struct _tagModifyServer
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR oldservername[32];//原服务器配置名称(修改时使用)
	int   bIgnoreError;//直接操作,忽略错误
	tagServerCfg servercfg;//修改后的服务器配置
}tagModifyServer,tagAddServer;

typedef	struct _tagImgResponse
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR imgpath[260];
	DWORD imgsectornums;
	DWORD freeimgsectornums;//剩余扇区数(只有在分区和物理磁盘时值才有效)
}tagImgResponse;

typedef	struct _tagGetFixListRequest
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR servername[32];
	TCHAR imgpath[260];
}tagGetFixListRequest;

typedef	struct _tagFixResponse
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR fixpath[260];
}tagFixResponse;

typedef	struct _tagGetUdoListRequest
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR servername[32];
	TCHAR imgpath[260];
}tagGetUdoListRequest;

typedef	struct _tagUdoResponse
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR fixpath[260];
}tagUdoResponse;

typedef struct _tagTask
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	DWORD taskId;
	DWORD taskPercent;
	int	 taskType;
	TCHAR servername[32];
	TCHAR syncservername[32];
	TCHAR imgPath[64];
	DWORD imgSize;
	TCHAR fixudoPath[64];
	TCHAR newimgPath[64];
}tagTask;

typedef	struct _tagMZDRegister
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR diskId[256];
	TCHAR agentId[64];//代理商编号
	TCHAR password[256];//密码
	DWORD lineType;//线路，0：网通，1：电信
	TCHAR smscode[8];//短信验证码
	TCHAR mzdusername[20];
	TCHAR mzdpassword[32];
}tagMZDRegister;

typedef	struct _tagMenuSet
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	int		waitTime;	//工作站启动界面等待时间
	bool	isShowHostIP;	//显示Login服务器IP开关
	bool	isVipLogon;
	TCHAR	adapterSet[20];	//包含的网卡设置名
	TCHAR	wksArea[255];        //255 MAX STRING 工作站编号列表
	DWORD	gateway;
	int		numberLength;	//编号长度
	BYTE	bootOrd;	//启动顺序
	BYTE	bootOrd1;
	BYTE	bootOrd2;
	DWORD	dns1;			//DNS
	DWORD	dns2;			//DNS
	TCHAR	arDiskItems[4][32];	//当前设置的磁盘
	TCHAR	comPre[20];	//计算机名前缀
	TCHAR	comAfx[20];	//计算机名后缀
	int		startNumber;				//计算机名启始编号
	TCHAR	workGroup[20];	//工作组
	TCHAR	scrRes[20];	//工作站的屏幕分辩率
	TCHAR	gatewayMAC[20];		//网关MAC
	DWORD	coverDirIp;               // Disk Img Host address
	DWORD	coverMirrIp;              //磁盘镜像IP
	DWORD	coverHotBakIP;
	DWORD m_WksMemory;//工作站内存缓冲
	BYTE  m_WksAutoClear;//工作自动清空
	BYTE  m_UseHotBackup;//启用热备
	TCHAR	displayName[20]; //这个一定要放在最后  菜单名称
	TCHAR	menuName[20]; //这个一定要放在最后  菜单名称
}tagMenuSet;

typedef	struct _tagAdapt
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效

	TCHAR	adapterName[20];//网卡设置名称
	DWORD	loginIP;		//主服登录IP	
	DWORD	spareLoginIp;	//从服登录IP
	DWORD	wksStartIp;		//起始DHCP IP
	DWORD	wksSubMask;		//DHCP 子网
	BYTE	subsectionIp;	//IP分段点	
	int		dhcpCount;		//范围计数
	DWORD gateway;//网关
	DWORD dns1;
	DWORD dns2;
}tagAdapt;

typedef	struct _tagAdaptMenuSet
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	_tagMenuSet menuset;
	_tagAdapt adaptset;
}tagAdaptMenuSet;

typedef	struct _tagPhysicalDiskId
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR diskId[256];
}tagPhysicalDiskId;

typedef	struct _tagServerAdaptName
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR ServerAdapt[96];
}tagServerAdaptName;

typedef struct _tagWksCmd
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	DWORD startWksId;
	DWORD endWksId;
	int   wksCmd;
}tagWksCmd;

typedef struct _tagCheckServerWorkDir
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	DWORD serverIp[4];
	bool bWorkDirExist[4];//U,V,W,X是否存在
	bool bSSDExist;//S盘
}tagCheckServerWorkDir;

typedef struct _tagServerCmd
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	DWORD serverIp[4];
	int		cmdType;
}tagServerCmd;

typedef	struct _tagMZRegInfo
{
	DWORD cbSize; // 结构总的大小
	DWORD dwFlags; // 控制后面哪个字段生效
	TCHAR netbarname[64];//网吧名
	TCHAR hdid[16];//注册硬盘序列号
	TCHAR sparehdid[16];//备用注册硬盘序列号
	TCHAR proxyname[64];//代理商
	SYSTEMTIME expiretime;//到期时间
	int   serverType;//服务器类型
	TCHAR passport[32];//通行证
}tagMZRegInfo;

typedef struct _tagAddWksInfoError
{
	DWORD wksNumberInError;//添加该编号时发生错误
	bool bIpClash;//与其他工作站IP冲突
	bool bMacClash;//与其他工作站MAC冲突
	bool bNumberClash;//与其他工作站编号冲突
	bool bServerNameClash;//与其他服务器名冲突
	bool bServerIpClash;//与其他服务器IP冲突
	bool bGateWayClash;//与网关冲突
	DWORD wksIpInError;//添加该工作站IP时发送错误(作为新的起始IP)
	int	 ErorrCode;  //接口错误值
	_tagAddWksInfoError()
	{
		memset(this,0,sizeof(_tagAddWksInfoError));
	}
	_tagAddWksInfoError(_tagAddWksInfoError& A)
	{
		wksNumberInError = A.wksNumberInError;
		bIpClash = A.bIpClash;
		bMacClash = A.bMacClash;
		bNumberClash = A.bNumberClash;
		bServerNameClash = A.bServerNameClash;
		bGateWayClash = A.bGateWayClash;
	}
}tagAddWksInfoError;

typedef struct _tagAddServerError
{
	bool bIpClash;//与其他工作站IP冲突
	bool bServerIpClash;//与其他服务器IP冲突
	bool bServerNameClash;//与其他服务器名冲突
	bool bGateWayClash;//与网关冲突
	int	 ErorrCode;  //接口错误值
	_tagAddServerError()
	{
		bIpClash = false;
		bServerIpClash = false;
		bServerNameClash = false;
		bGateWayClash = false;
	}
}tagAddServerError;

typedef struct _tagHookCache
{
	DWORD cache_size;//缓存大小
	DWORD rw_type;//缓存类型(1 = 写缓存 其他是读)
	TCHAR owner[128];//使用者
	INT64 total_rw_secs;//总读/写数据量
	INT64 hit_rw_secs;//命中数据量
	INT64 hit_percent;//命中率
	INT64 rw_nums;//读写总次数
	INT64 IOPS;//每秒进行读写（I/O）操作的次数
	INT64 rw_speed;//读写速率
	DWORD current_time;//当前检测时间
}tagHookCache;


typedef struct _tagCache
{
	tagHookCache	stHookCache;
	int		bSsd;	//SSD标志位
}tagCache;
enum EWKSMODE
{
	eNormalMode, eDbgMode,    eDiagMode, eSuperMode, eGhostMode
};
#define MZD_LENGTH_4 4
#define MZD_LENGTH_8 8
#define MZD_LENGTH_16 16
#define MZD_LENGTH_20 20
#define MZD_LENGTH_32 32
#define MZD_LENGTH_64 64
#define MZD_LENGTH_96 96
#define MZD_LENGTH_128 128
#define MZD_LENGTH_255 255
#define MZD_LENGTH_256 256
//工作站
struct _tagWkstation
{
	WORD	wksNumber;  //编号
	WORD	loginID;		//登陆号
	DWORD	wksCmdCfg;	//发过来的登陆命令
	EWKSMODE	wksMode;
	BYTE	userType; //0:Normal 1:VIP 工作站类型

	bool	isDisable;	//禁止工作站
	DWORD	wksIp;	//工作站IP
	WORD	randKey;	//随机KEY
	WORD	loginIPLow;	//登陆的服务器IP后两位
	DWORD	userSelectCmd;//用户选择命令

	MZD_CHAR	strMac[MZD_LENGTH_20];	//工作站的MAC
	MZD_CHAR	comName[MZD_LENGTH_20];	//工作站的计算机名
	MZD_CHAR	currSetCfg[MZD_LENGTH_20];	//当前工作站使用的系统设置名称
	MZD_CHAR	menuName[MZD_LENGTH_20];	//当前工作站使用的菜单设置名称
	MZD_CHAR	userName[MZD_LENGTH_20];	//登陆用的用户名，工作站使用的是MAC，VIP使用的是VIP用户名 

	MZD_CHAR	password[MZD_LENGTH_20];	//登陆密码
	MZD_CHAR	inputName[MZD_LENGTH_20];	//工作站登陆时输入的用户名
	MZD_CHAR	inputPass[MZD_LENGTH_20];	//工作站登陆时输入的密码
	MZD_CHAR	adaptname[MZD_LENGTH_20];//当前网络设置
	DWORD	serverIp;		//工作站连接的主机IP

	DWORD	dhcpGateway;	//DHCP 的网关
	DWORD	subMask;
	WORD	clientPort;	//控制这台工作站重启，关机的端口
	int		wksMemory;

	//防止人为改动磁盘设置后，工作站续接找不到磁盘信息
	MZD_CHAR	arDiskSetName[4][MZD_LENGTH_96];	// 保存当次进入系统的磁盘设置信息
	MZD_CHAR	arDestinationFile[4][MZD_LENGTH_64];      //
	MZD_CHAR	arDiskWorkDir[4][MZD_LENGTH_32];
	BYTE     RestartAutoClear;//重启自动清空
	MZD_CHAR group[MZD_GROUP_NAME_LENGTH];//所属分组
	bool bSuperMode;
	DWORD m_LiveSendTime;//心跳包发送时间
	DWORD m_LiveRecvTime;//心跳包返回时间
	DWORD m_WksPhysicalMemory;//工作站上报的物理内存(MB)
	bool bSuperOnline;//超管在线状态

	MZD_CHAR menu_set[4][MZD_LENGTH_32];//菜单内部名

	//_tagWkstation()
	//{
	//	memset(this,0,sizeof _tagWkstation);
	//}
	//void m_SetLoginId(WORD ID)
	//{
	//	if (ID < MAX_WORKSTATION_NUMBERS) 
	//		loginID = ID;
	//}

	////当前是否被VIP用户使用
	//bool m_IsVipUsing(int cDiskIndex) const
	//{
	//	return  (cDiskIndex < 0 && inputName != strMac);  //inputName == strMac 工作站调试模式，忽略还原清空等设置
	//}

	////设置工作站类型，VIP 工作站
	//bool m_IsVipUser() const
	//{
	//	return  (userType > 0);  
	//}

	//bool m_IsSuperWks(const MZD_CHAR* pszDiskName, byte byIndex)
	//{
	//	return false;
	//}

	//void CreateComName(DWORD wksLength,MZD_CHAR* comPre,MZD_CHAR* comAfx)
	//{
	//	//计算机名的长度最大为16字节
	//	if (MZD_STRCMP(comPre,MZD_INVALIDE_PRE) == 0)
	//	{
	//		//无效的前缀,只需要取后缀的名称
	//		if (MZD_STRLEN(comAfx) > 16 - 1)
	//		{
	//			MZD_MEMCPY(comName,comAfx,16 - 1);
	//			comName[16 - 1] = '\0';
	//		}else
	//		{
	//			MZD_STRCPY(comName,comAfx);
	//		}
	//	}else
	//	{
	//		MZD_CHAR strComName[64];
	//		MZD_CHAR strNumber[32];
	//		MZD_CHAR strComPre[20];
	//		MZD_CHAR strComAfx[20];
	//		if (wksLength > 4)
	//		{
	//			wksLength = 4;
	//		}

	//		MZD_MEMCPY(strComPre,comPre,20);
	//		MZD_MEMCPY(strComAfx,comAfx,20);
	//		MZD_SPRINTF_S(strNumber,MZD_T("%d"),wksNumber);
	//		while(MZD_STRLEN(strNumber) < wksLength)
	//		{
	//			MZD_SPRINTF(strComName,MZD_T("0%s"),strNumber);
	//			MZD_STRCPY(strNumber,strComName);
	//		}

	//		//动态计算计算机名长度,(长度=前缀+wkslength+ 后缀) < 16 - 1
	//		DWORD prelength = MZD_STRLEN(strComPre);
	//		DWORD afxlength = MZD_STRLEN(strComAfx);

	//		if (prelength > 16  - wksLength - 1)
	//		{
	//			prelength = 16 - wksLength - 1;
	//			strComPre[prelength] = '\0';
	//		}

	//		if (prelength + wksLength + 1 < 16)
	//		{
	//			afxlength = 16 - 1 - wksLength - prelength;
	//		}else
	//		{
	//			afxlength = 0;
	//		}
	//		strComAfx[afxlength] = '\0';

	//		MZD_SPRINTF_S(strComName,MZD_T("%s%s%s"),strComPre,strNumber,strComAfx);
	//		MZD_STRCPY(comName,strComName);
	//	}
	//}
};


#pragma pack(pop)



typedef int (*MzdAgentInit)(TCHAR* pIp,short port,TCHAR* pPassword);
typedef void (*MzdAgentFree)(void*);
typedef int (*GetGlobal)(tagGetGlobalSetEx* pCfg);
typedef int (*ModifyGlobal)(_tagGlobalSet* pCfg);
typedef int (*GetServerCfg)(DWORD& nums,_tagServerCfg** pServerList);
typedef int (*ModifyServerCfg)(tagModifyServer* pCfg, tagAddServerError& error);
typedef int (*AddServerCfg)(tagAddServer* pCfg, tagAddServerError& error);
typedef int (*DelServerCfg)(_tagServerCfg* pCfg);
typedef int (*GetDiskSetCfg)(_tagServerName* pServerName,DWORD&,_tagDiskSet**);
typedef int (*GetDiskSetNameList)(DWORD&,_tagGetDisksetNameList**);
typedef int (*ModifyDiskSetCfg)(_tagDiskSet* pCfg);
typedef int (*DelDiskSetCfg)(_tagDiskSet* pCfg);
typedef int (*AddDiskSetCfg)(_tagDiskSet* pCfg);
typedef int (*GetWksCfg)(DWORD&,_tagWkstationEx**);
typedef int (*ModifyWksCfg)(tagModifyWksInfo* pCfg, tagAddWksInfoError& error);
typedef int (*AddWksCfg)(tagAddWksInfo* pCfg, tagAddWksInfoError& error);
typedef int (*ModifyWksCfgList)(tagAddWksInfo*);
typedef int (*DelWksCfg)(DWORD delNums,DWORD* wksList);
typedef int (*GetImgPartitionPhysical)(tagServerIp* pServerIp,DWORD&,_tagImgResponse**);
typedef int (*GetFix)(_tagGetFixListRequest* pServerName,DWORD&,_tagFixResponse**);
typedef int (*GetUdo)(_tagGetUdoListRequest* pServerName,DWORD&,_tagUdoResponse**);
typedef int (*DoDiskMaitainTask)(tagTask*);
typedef int (*GetDiskMaitainTaskList)(tagServerIp* pServerIp,DWORD&,tagTask**);
typedef int (*StartRegister)(_tagMZDRegister*);
typedef int (*GetAdaptMenuCfg)(DWORD&,_tagAdaptMenuSet**);
typedef int (*GetPhysicalDiskId)(DWORD&,_tagPhysicalDiskId**);
typedef int (*GetServerAdaptName)(DWORD& nums,_tagServerAdaptName** pList);
typedef	int (*WksCmd)(tagWksCmd*);
typedef	int (*GetServiceStatus)(int*);
typedef	int	(*CheckServerWorkDir)(tagCheckServerWorkDir*);
typedef	int (*ServerCmd)(tagServerCmd* pCmd);
typedef	int (*GetMZRegInfo)(_tagMZRegInfo* pReg);
typedef int (*GetDiskSetCfgEx)(TCHAR* pServerName,bool bGetImgSize,DWORD& nums,_tagDiskSet** pList);
typedef	int (*GetCacheInfo)(_tagServerIp* pIp,DWORD& mem_nums,tagHookCache** p_mem_list,DWORD& ssd_nums,tagHookCache** p_ssd_list);
typedef int (*ModifyWksMac)(tagModifyWksInfo*);



typedef void (*FreeMZD_INI)(char* pINIBuf);
typedef int (*DoCmd2MZDIO)(DWORD cmd,const char* pINI,char** ppOutBuf);

#define MZD_INVALIDE_PRE MZD_T("_MZD_INVALID_MZD_")