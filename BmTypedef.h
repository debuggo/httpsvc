#pragma once
#include <windows.h>

#define CONFIG_SYSTEMDEF L"System default"

enum enuBmConfigType
{
	BmConfigTypeTransfer,     //传送文件
	BmConfigTypeStartup,      //开机运行
	BmConfigTypeMapDrv,       //映射盘符
	BmConfigTypeIpMac,        //IPMAC绑定

	BmSafeTypeWindows,     //禁用窗口
	BmSafeTypeProgram,     //禁用程序
	BmSafeTypeWebSite,     //禁用网址
};

//关联配置信息
struct tagRefConfig
{    
	TCHAR macname[50];  //mac地址
	TCHAR pcname[50];    //计算机名
	TCHAR cfgname[50];   //关联配置名
};

//硬件信息类型
enum enuHWType
{
	enuHwNone = -1,     //未知
	enuHwCpu = 0,       //cpu
	enuHwBoard,         //主板
	enuHwBios,          //bios
	enuHwDisplay,       //显卡
	enuHwAudio,         //声卡
	enuHwNetCard,       //网卡
	enuHwMem,           //内存
	enuHwHard,          //硬盘
	enuHwUsb,           //USB
	enuHwMonitor,       //显示器
	enuHwChipset,       //芯片组
};

struct HWNAME
{
	enuHWType	dwType;			// 硬件类型
	wchar_t  	pwsName[200];	// 硬件名称
	DWORD dwPower;              // 硬件功耗

public:
	void clear()
	{
		dwType = enuHwNone;
		memset(pwsName, 0, sizeof(pwsName));
		dwPower = 0;
	}
	HWNAME()
	{
		clear();
	}
};

//硬件状态类型
enum enuHSType
{
	enuHsNone = -1,       //未知
	enuHsCpuUse = 0,      //CPU使用率
	enuHsCpuDUse = 1,     //CPU%d使用率(1个以上cpu核心时)
	enuHsHardUse = 2,     //磁盘占用率(整个磁盘的占用率)
	enuHsNetcard = 3,     //网卡占用率
	enuHsMemUse = 4,      //内存占用率
	enuHsDriverUse = 5,   //分区占用率(每个分区的占用率,数据存储在stVal中，其它的项数据都在pwsValue)
	enuHsCpuFan = 6,      //CPU风扇转速
	enuHsBoard = 7,       //主板温度
	enuHsCpuTemp = 8,     //CPU温度
	enuHsHardTemp = 9,    //磁盘温度
	enuHsDisplay = 10,    //显卡温度
	enuHsMemTemp = 11,    //内存温度
	enuHsNetWidth = 12,   //网卡带宽
};

struct HWSTATUS
{
	enuHSType	nType;			// 状态类型
	DWORD_PTR	dwNum;			// 序号
	LARGE_INTEGER	stVal;		// 大小
	wchar_t	pwsValue[20];		// 状态数值
public:
	void clear()
	{
		nType = enuHsNone;
		memset(pwsValue, 0, sizeof(pwsValue));
		dwNum = -1;
		stVal.HighPart = 0;  //当前值
		stVal.LowPart = 0;   //最大值 MaxValue
	}
	HWSTATUS()
	{
		clear();
	}
};

struct HWDATA
{
	DWORD_PTR	dwIsServer;		// 是否服务器
	DWORD		dwStatus;		// 状态0=未知，1=在线，2=离线，4=警告，8=异常   硬件更新时间或状态更新时间在120秒以内是在线的

	SYSTEMTIME  stStartup;      // 上线时间(开机时间)
	LONG  lOnlineTime;          // 在线时间(从上线时间算起,add at 2013.1.23)

	DWORD		dwTime;			// 检测时间
	DWORD		dwWarTime[30];	// 警告时间
	DWORD		dwWarning;		// 是否不再警告，1=CPU,2=单核CPU,4=磁盘,8=网卡,0x10=内存,0x20=主板温度,0x40=CPU温度,0x80=磁盘温度,0x100=磁盘空间
	HWND		hWarningWnd;	// 警告窗口
	wchar_t  	pwsComputer[24];// 计算机名
	wchar_t     pwsMac[80];		// 网卡地址
	wchar_t  	pwsIp[100];		// IP
	wchar_t 	pwsHTime[30];	// 硬件更新时间
	wchar_t 	pwsSTime[30];	// 状态更新时间
	wchar_t 	pwsSVer[300];	// 客户端软件版本信息  (add by jl 2012.3.10)
	DWORD       dwWCount;       // 状态信息条数
	DWORD       dwHCount;       // 硬件信息条数
	HWSTATUS	ppStatus[100];	// 状态信息
	HWNAME		stDev[100];		// 硬件信息

public:
	HWDATA()
	{
		clear();
	}

	void clear()
	{
		dwIsServer = -1;
		dwStatus = 0;
		memset(&stStartup, 0, sizeof(SYSTEMTIME));
		lOnlineTime = 0;
		dwTime = 0;
		memset(&dwWarTime, 0, sizeof(dwWarTime));
		dwWarning = 0;
		hWarningWnd = NULL;
		memset(&pwsComputer, 0, sizeof(pwsComputer));
		memset(&pwsMac, 0, sizeof(pwsMac));
		memset(&pwsIp, 0, sizeof(pwsIp));
		memset(&pwsHTime, 0, sizeof(pwsHTime));
		memset(&pwsSTime, 0, sizeof(pwsSTime));
		memset(&pwsSVer, 0, sizeof(pwsSVer));
		dwWCount = 0;
		dwHCount = 0;
		memset(ppStatus, 0, sizeof(ppStatus));
		memset(stDev, 0, sizeof(stDev));
	}        
};
