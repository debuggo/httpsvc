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
// ���ļ�·����ȡ���ļ���
TCHAR * GetFileTitleName(TCHAR * ptsFile);

//#define CHANGE_PAPER_TIMER 2  //�޸ı�ֽ
//#define SHOW_DESKTOP_UP_TIMER 3   //��ʾ��������
//#define CHECK_DESKTOP_UP_TIMER 4   //�����������
//#define GAME_EXIT_TIMER 5 //��Ϸ�˳���鶨ʱ��
//#define IE_CHECK_TIMER 6  //IEʹ�ö�ʱ��

#pragma pack(push)//�������״̬
#pragma pack(1)  //����Ϊ1�ֽڶ���


typedef struct _GGMEMBB      //���ƽ̨�����ڴ��
{
	DWORD	zipFileSize;      //���ѹ������С
	//DWORD   dwIniFileSize;    //��������ļ���С
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
	tstring name;//��Ϸ������
	DWORD time;	//����ʱ��
	DWORD first_check_time;//���μ�鵽��ʱ��
	DWORD pid;	
};

//�����ļ�
typedef struct _ClientIniData
{
	TCHAR szSysName[8];//����ϵͳ��Ʒ��Ʒ���ƣ�MZD��PXD��WMB��
	TCHAR szAgentName[64];//����������
	TCHAR szNetBarName[64];	//��������
	TCHAR szIEHome[1024];//IE��ҳ�趨��ַ
	TCHAR strIeSafePath[MAX_PATH];  //IESAFE����·��  //add by skylly
	TCHAR szADCbl[128];//��������ͼƬ�����ת��ַ
	DWORD dwADEnable;//����Ƿ����ñ�־��1�����ã� 0�������ã�
	TCHAR szBrowser[8];//��������ͣ�ȱʡֵ��IE��
	DWORD dwLSEnable;//Ӳ����״̬��Ϣ����
}ClientIniData,*pClientIniData;

typedef struct _DownLoadFileData
{
	DWORD dwCRC;
	TCHAR szURL[256];
	TCHAR szFileName[128];
}DownLoadFileData,*pDownLoadFileData;
#pragma pack(pop)//�������״̬

// Windows ͷ�ļ�:
class CAdClient
{
public:  //��������
	CAdClient(HINSTANCE);
	~CAdClient(void);

public:  //���з���
	static CAdClient*  Instance();
	int start(wstring ip, int port);
	void UnInit();

private:  //˽�б���
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
	tstring m_strIniFileName;  //ini�ļ�·��

private:  //˽�з���
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
	//��������Ϊ��Ļ��������ù���������
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
