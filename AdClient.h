#pragma once

//#include "global.h"
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")

#include <tchar.h>
#include <wininet.h>

#include <vector>
#include <string>
using namespace std;

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif
// 从文件路径中取得文件名
TCHAR * GetFileTitleName(TCHAR * ptsFile);

//#define CHANGE_PAPER_TIMER 2  //修改壁纸
//#define SHOW_DESKTOP_UP_TIMER 3   //显示桌面升窗
//#define CHECK_DESKTOP_UP_TIMER 4   //检查桌面升窗
//#define GAME_EXIT_TIMER 5 //游戏退出检查定时器
//#define IE_CHECK_TIMER 6  //IE使用定时器

#pragma pack(push)//保存对齐状态
#pragma pack(1)  //设置为1字节对齐


typedef struct _GGMEMBB      //广告平台共享内存块
{
	DWORD	zipFileSize;      //广告压缩包大小
	//DWORD   dwIniFileSize;    //广告配置文件大小
	DWORD   ggADEnable;
	TCHAR	ggTypeFlag[6];			
	TCHAR	ggszMZP[32];		
	//TCHAR	ggszIEHome[128];
} GGMEMBB;

struct tagAdSwitch
{
	BOOL b[31];
	void Init(DWORD dwValue)
	{
		unsigned long p=1;
		for (int i = 1; i <= 31; i++)
		{
			if ((dwValue %(p*2)) < p)
			{
				b[i-1] = FALSE;
			}
			else
			{
				b[i-1] = TRUE;
			}
			p=p*2;
		}
	}
};

struct gamename{
	tstring name;//游戏进程名
	DWORD time;	//开启时间
	DWORD first_check_time;//初次检查到的时间
	DWORD pid;	
};

//配置文件
typedef struct _ClientIniData
{
	TCHAR szSysName[8];//网吧系统产品产品名称（MZD、PXD、WMB）
	TCHAR szAgentName[64];//代理商名称
	TCHAR szNetBarName[64];	//网吧名称
	TCHAR szIEHome[1024];//IE首页设定地址
	TCHAR strIeSafePath[MAX_PATH];  //IESAFE完整路径  //add by skylly
	TCHAR szADCbl[128];//侧边栏广告图片点击跳转地址
	DWORD dwADEnable;//广告是否启用标志（1：启用； 0：不启用）
	TCHAR szBrowser[8];//浏览器类型（缺省值：IE）
	DWORD dwLSEnable;//硬件，状态信息开关
}ClientIniData,*pClientIniData;

typedef struct _DownLoadFileData
{
	DWORD dwCRC;
	TCHAR szURL[256];
	TCHAR szFileName[128];
}DownLoadFileData,*pDownLoadFileData;
#pragma pack(pop)//保存对齐状态

// Windows 头文件:
class CAdClient
{
public:  //构造析构
	CAdClient(HINSTANCE);
	~CAdClient(void);

public:  //公有方法
	static CAdClient*  Instance();
	int start(wstring ip, int port);
	void UnInit();

private:  //私有变量
	bool m_bRun;
	HANDLE m_hMutex;

	//char* m_pDeskDataBuffer;
	DWORD m_dwDeskDataBufferLength;

	GGMEMBB POPO;
	DWORD m_AdEnable;
	HWND m_hWnd;
	TCHAR m_MZP[32];
	TCHAR m_AgentId[32];
	//TCHAR m_IeHome[128];

	tagAdSwitch m_AdSwitch;
	gamename mygame;

	bool m_bCheckDesktopUp;
	bool m_bCheckIeUp;
	bool m_bCheckGameExit;
	bool m_bCheckWallPaper;

	int m_iDesktopUpTime;
	char m_ClientInfo[1024];
	string m_ServerIp;
	short  m_ServerPort;
	bool m_bUseActiveDesktop;
	tstring m_strIniFileName;  //ini文件路径

private:  //私有方法
	BOOL GetParameterAndParse(void);
	int Init(string ,int);

	int ActiveDesktopUsed(void);
	int GetParameter(void);
	int ParseParameter(void);
	int ParseAdEnable(void);

	int SetWallPaper(tstring picPath);
	int OnGetProcess(LPCTSTR lpFileName, LPCTSTR lpFileName2);
	int CheckGameExitShowAd(void);
	int UpdateWallPater(void);
	int CreateInterShortcut(CHAR* pszURL, TCHAR* pszURLfilename,CHAR* szDescription,CHAR* szIconFile = NULL,int nIndex = -1);
	int GetOneGame(void);
	int CheckGameExist(DWORD pid);
	int ProcessIeEvent(void);
	int getLocalMac(char* hash);
	int CheckAndShowIeAd(void);
	int CheckUpAdWindow();
	//广告程序作为库的话，自身不用关心升级了
	//int UpdateThread(int iLocalVersion, tstring strNetBarServer, int iListenPort);

	static void WorkThreadProc(void*);
	int WorkThread(void);
	static void UpAdWindowThreadProc(void* pParam);
	int UpAdThread(void);
	static void UpIeAdThreadProc(void* pParam);
	int UpIeAdThread(void);
	//int UncompressAndRegisterIesafeDLL(void);
	int AddCClientInfo(tstring url, tstring name);
	//char* GetClientInfo(void);
	string GetHashokA(tstring GGID);
	tstring GetHashok(tstring GGID);
};
