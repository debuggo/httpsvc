#pragma once
//#include <windows.h>
//#include <afx.h>
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//#include <Windows.h>
//#include "resource.h"
//#include "IniFile.h"
#include <winsock.h>
#include "IniFile.h"
#include <Winsvc.h>
#include <Gdiplus.h> 
#include <vector>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;


typedef	struct	_tagBubbleData
{
	int		nFlags;// ����λ��10:��ɾ�����̲��˳�����1��������ʾ��
	TCHAR	wszMessage[128];
	TCHAR	wszTitle[64];
}BUBBLEDATA;
typedef struct _tagSocketInMsg
{
	TCHAR szTime[MAXBYTE];
	TCHAR szMsgText[MAXBYTE];
	TCHAR szTitle[MAXBYTE];
}SOCKETINMSG, *PSOCKETINMSG;
class CMainDialog
{
enum MAINDLGERR
{
	SUCCESS,
	NOTSELETEITEM
};

public:
	/************************************************************************/
	/* ����                                                                 */
	/************************************************************************/


	//************************************
	// ����:	Instance
	// Ȩ��:	public static 
	// ����:	CMainDialog*
	// ˵��:	��ȡCMainDialog��ָ��
	//************************************
	static CMainDialog* Instance()		//����������
	{
		return m_pTheSinleton;
	}


	//************************************
	// ����:	CreateMainDialog
	// Ȩ��:	public 
	// ����:	BOOL
	// ����:	HINSTANCE hInstance
	// ����:	BOOL bIsShow
	// ˵��:	��������
	//************************************
	BOOL CreateMainDialog(HINSTANCE hInstance, BOOL bIsShow);

	//************************************
	// ����:	OpenUrl
	// Ȩ��:	public 
	// ����:	BOOL
	// ����:	const CString & strUrl
	// ˵��:	��ָ����ַ
	//************************************
	BOOL OpenUrl( const CString& strUrl );

	//************************************
	// ����:	ExitMainDialog
	// Ȩ��:	public 
	// ����:	BOOL
	// ˵��:	�رմ���
	//************************************
	BOOL ExitMainDialog();
	
	BOOL InitServiceList(HWND hWnd);//��ʼ���б�
	BOOL RefreshServiceStaus(HWND hWnd);//ˢ����Ϣ
	BOOL WriteMessage(HWND hWnd, CString strMsg);//д����Ϣ
	BOOL BtnStartService(HWND hWnd);//������ť������
	BOOL BtnStartAllService(HWND hWnd);//����ȫ������ť������
	BOOL BtnStopService(HWND hWnd);//ֹͣ��ť������
	BOOL BtnStopAllService(HWND hWnd);//ֹͣȫ����ť������
	BOOL BtnRestStatrService(HWND hWnd);//��������ť������
	BOOL BtnRefreshService(HWND hWnd);	//ˢ�·���״̬��ť������
	BOOL BtnHideWindow(HWND hWnd);	//���ش���
	BOOL AddMsgToMsgWnd(HWND hMsgWnd);	//����Ϣ���������Ϣ
	/************************************************************************/
	/* ����                                                                 */
	/************************************************************************/
	BOOL m_bWindowIsShow;	//�����Ƿ���ʾ
	BOOL m_bMsgWindowsIsShow;	//��Ϣ�����Ƿ���ʾ
	HMENU m_hMenu;	//���̲˵�
	HWND m_hWnd;	//�����ھ��
	HWND m_hMsgWnd;	//��Ϣ���ھ��
	CString m_strPort;//�˿�
	CString m_strAppPath;	//����·��
	GdiplusStartupInput		m_gdiPlusInPut;
	ULONG_PTR				m_gdiPlusToken;
	HINSTANCE m_hInstance;	//����ʵ�����
	SOCKET m_Socket;	//Socket����
	BOOL m_bIsFirstIcon;//��������ͼ������
	BOOL m_bIsHasMsg;	//��Ϣ����
	NOTIFYICONDATA m_nid;	//���̽ṹ
	vector<PSOCKETINMSG> m_vctMsg;	//��Ϣ����
private:
	CMainDialog(void);
	CMainDialog(CMainDialog const&);
	CMainDialog& operator = (CMainDialog const&);
	~CMainDialog(void);
	//************************************
	// ����:	CreateTrayNotify
	// Ȩ��:	private 
	// ����:	BOOL
	// ����:	TCHAR * szTip
	// ˵��:	��������ͼ��
	//************************************
	BOOL CreateTrayNotify( TCHAR *szTip); //��������ͼ��
	int GetProcessNameFromPort(DWORD dwType, u_short wdPort, TCHAR * ptsFile, DWORD dwFileSize);	//��ѯָ���˿��Ƿ�ռ��
	int GetProcessNameFromId(DWORD dwProcessId, TCHAR * ptsName, DWORD dwNameLen);//��ȡ������
	int GetSeleteItemText(HWND hList, TCHAR *szText);
	static DWORD WINAPI ThreadStartService( LPVOID p );//���������߳�
	static DWORD WINAPI ThreadStartAllService( LPVOID p );//���������߳�
	static DWORD WINAPI ThreadStopService( LPVOID p );//���������߳�
	static DWORD WINAPI ThreadStopAllService( LPVOID p );//���������߳�
	static DWORD WINAPI ThreadRestartService( LPVOID p );//���������߳�
	static DWORD WINAPI ThreadRefreshServiceStatus( LPVOID p );//���������߳�
	BOOL InstallService(TCHAR *szServiceName);//��װ����
	BOOL ServiceStart(TCHAR *szServiceName);//��������
	BOOL ServiceStop(TCHAR *szServiceName);//��ͣ����
	BOOL ServiceStopByName(HWND hWnd, int nItemIndex, TCHAR *szText);//��������ֹͣ����
	BOOL ServiceStartByName(HWND hWnd, int nItemIndex, TCHAR *szText);//������������
	inline TCHAR* GetServicePathForName(TCHAR *szServiceName, TCHAR *szServicePath);//���ݷ�������ȡ����·��
	BOOL SetListItemText(HWND hWnd, int nItemIndex, TCHAR *szText, int nSubItem = 2);//�����б��ı�
	
	static CMainDialog* m_pTheSinleton;
	HANDLE m_hMutex;	//��������
	CIniFile m_IniFile;	//Ini����
};
