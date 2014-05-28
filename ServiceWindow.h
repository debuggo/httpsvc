#pragma once


// CServiceWindow �Ի���
#include <winsock.h>
#include "IniFile.h"
#include <Winsvc.h>
#include <Gdiplus.h> 

using namespace Gdiplus;

#pragma comment(lib,"Gdiplus.lib")

#pragma pack(push)//�������״̬
#pragma pack(1)//�������״̬

typedef	struct	_BubbleData
{
	int		nFlags;// ����λ��10:��ɾ�����̲��˳�����1��������ʾ��
	TCHAR	wszMessage[128];
	TCHAR	wszTitle[64];
}BubbleData;

#pragma pack(pop)

DWORD	WINAPI	ThreadStopAll(LPVOID	lpvoid);
DWORD	WINAPI	ThreadRefresh(LPVOID	lpvoid);

class CServiceWindow
{
public:
	CServiceWindow();
	virtual ~CServiceWindow();

	static	CServiceWindow*		GetServiceWindow();
	int			CreateServiceWindow(HINSTANCE hInstance, int nShow);
	int			InitServiceList(HWND	hWndParent);

	VOID		ButtonStart();
	VOID		ButtonStop();
	VOID		ButtonRestart();
	VOID		ButtonRefresh();
	VOID		ButtonStartAll();
	VOID		ButtonStopAll();

public:
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	CIniFile	m_IniFile;
	HMENU		m_hMenu;
	NOTIFYICONDATA	m_nid;
	SOCKET		m_Socket;	//servicewindows
	//HWND		m_hServiceWindow;
	GdiplusStartupInput		m_gdiPlusInPut;
	ULONG_PTR				m_gdiPlusToken;
	HANDLE	FQ_ShangGuanXWHandle;	
	BOOL m_bIsInit;
};
