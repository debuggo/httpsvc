#pragma once
#include <windows.h>

#define CONFIG_SYSTEMDEF L"System default"

enum enuBmConfigType
{
	BmConfigTypeTransfer,     //�����ļ�
	BmConfigTypeStartup,      //��������
	BmConfigTypeMapDrv,       //ӳ���̷�
	BmConfigTypeIpMac,        //IPMAC��

	BmSafeTypeWindows,     //���ô���
	BmSafeTypeProgram,     //���ó���
	BmSafeTypeWebSite,     //������ַ
};

//����������Ϣ
struct tagRefConfig
{    
	TCHAR macname[50];  //mac��ַ
	TCHAR pcname[50];    //�������
	TCHAR cfgname[50];   //����������
};

//Ӳ����Ϣ����
enum enuHWType
{
	enuHwNone = -1,     //δ֪
	enuHwCpu = 0,       //cpu
	enuHwBoard,         //����
	enuHwBios,          //bios
	enuHwDisplay,       //�Կ�
	enuHwAudio,         //����
	enuHwNetCard,       //����
	enuHwMem,           //�ڴ�
	enuHwHard,          //Ӳ��
	enuHwUsb,           //USB
	enuHwMonitor,       //��ʾ��
	enuHwChipset,       //оƬ��
};

struct HWNAME
{
	enuHWType	dwType;			// Ӳ������
	wchar_t  	pwsName[200];	// Ӳ������
	DWORD dwPower;              // Ӳ������

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

//Ӳ��״̬����
enum enuHSType
{
	enuHsNone = -1,       //δ֪
	enuHsCpuUse = 0,      //CPUʹ����
	enuHsCpuDUse = 1,     //CPU%dʹ����(1������cpu����ʱ)
	enuHsHardUse = 2,     //����ռ����(�������̵�ռ����)
	enuHsNetcard = 3,     //����ռ����
	enuHsMemUse = 4,      //�ڴ�ռ����
	enuHsDriverUse = 5,   //����ռ����(ÿ��������ռ����,���ݴ洢��stVal�У������������ݶ���pwsValue)
	enuHsCpuFan = 6,      //CPU����ת��
	enuHsBoard = 7,       //�����¶�
	enuHsCpuTemp = 8,     //CPU�¶�
	enuHsHardTemp = 9,    //�����¶�
	enuHsDisplay = 10,    //�Կ��¶�
	enuHsMemTemp = 11,    //�ڴ��¶�
	enuHsNetWidth = 12,   //��������
};

struct HWSTATUS
{
	enuHSType	nType;			// ״̬����
	DWORD_PTR	dwNum;			// ���
	LARGE_INTEGER	stVal;		// ��С
	wchar_t	pwsValue[20];		// ״̬��ֵ
public:
	void clear()
	{
		nType = enuHsNone;
		memset(pwsValue, 0, sizeof(pwsValue));
		dwNum = -1;
		stVal.HighPart = 0;  //��ǰֵ
		stVal.LowPart = 0;   //���ֵ MaxValue
	}
	HWSTATUS()
	{
		clear();
	}
};

struct HWDATA
{
	DWORD_PTR	dwIsServer;		// �Ƿ������
	DWORD		dwStatus;		// ״̬0=δ֪��1=���ߣ�2=���ߣ�4=���棬8=�쳣   Ӳ������ʱ���״̬����ʱ����120�����������ߵ�

	SYSTEMTIME  stStartup;      // ����ʱ��(����ʱ��)
	LONG  lOnlineTime;          // ����ʱ��(������ʱ������,add at 2013.1.23)

	DWORD		dwTime;			// ���ʱ��
	DWORD		dwWarTime[30];	// ����ʱ��
	DWORD		dwWarning;		// �Ƿ��پ��棬1=CPU,2=����CPU,4=����,8=����,0x10=�ڴ�,0x20=�����¶�,0x40=CPU�¶�,0x80=�����¶�,0x100=���̿ռ�
	HWND		hWarningWnd;	// ���洰��
	wchar_t  	pwsComputer[24];// �������
	wchar_t     pwsMac[80];		// ������ַ
	wchar_t  	pwsIp[100];		// IP
	wchar_t 	pwsHTime[30];	// Ӳ������ʱ��
	wchar_t 	pwsSTime[30];	// ״̬����ʱ��
	wchar_t 	pwsSVer[300];	// �ͻ�������汾��Ϣ  (add by jl 2012.3.10)
	DWORD       dwWCount;       // ״̬��Ϣ����
	DWORD       dwHCount;       // Ӳ����Ϣ����
	HWSTATUS	ppStatus[100];	// ״̬��Ϣ
	HWNAME		stDev[100];		// Ӳ����Ϣ

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
