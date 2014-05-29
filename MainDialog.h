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
	int		nFlags;// 控制位：10:（删除托盘并退出程序）1（气泡提示）
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
	/* 方法                                                                 */
	/************************************************************************/


	//************************************
	// 方法:	Instance
	// 权限:	public static 
	// 返回:	CMainDialog*
	// 说明:	获取CMainDialog类指针
	//************************************
	static CMainDialog* Instance()		//构建单体类
	{
		return m_pTheSinleton;
	}


	//************************************
	// 方法:	CreateMainDialog
	// 权限:	public 
	// 返回:	BOOL
	// 参数:	HINSTANCE hInstance
	// 参数:	BOOL bIsShow
	// 说明:	创建窗体
	//************************************
	BOOL CreateMainDialog(HINSTANCE hInstance, BOOL bIsShow);

	//************************************
	// 方法:	OpenUrl
	// 权限:	public 
	// 返回:	BOOL
	// 参数:	const CString & strUrl
	// 说明:	打开指定网址
	//************************************
	BOOL OpenUrl( const CString& strUrl );

	//************************************
	// 方法:	ExitMainDialog
	// 权限:	public 
	// 返回:	BOOL
	// 说明:	关闭窗口
	//************************************
	BOOL ExitMainDialog();
	
	BOOL InitServiceList(HWND hWnd);//初始化列表
	BOOL RefreshServiceStaus(HWND hWnd);//刷新消息
	BOOL WriteMessage(HWND hWnd, CString strMsg);//写入消息
	BOOL BtnStartService(HWND hWnd);//启动按钮被按下
	BOOL BtnStartAllService(HWND hWnd);//启动全部服务按钮被按下
	BOOL BtnStopService(HWND hWnd);//停止按钮被按下
	BOOL BtnStopAllService(HWND hWnd);//停止全部按钮被按下
	BOOL BtnRestStatrService(HWND hWnd);//重启服务按钮被按下
	BOOL BtnRefreshService(HWND hWnd);	//刷新服务状态按钮被按下
	BOOL BtnHideWindow(HWND hWnd);	//隐藏窗口
	BOOL AddMsgToMsgWnd(HWND hMsgWnd);	//向消息窗口添加消息
	/************************************************************************/
	/* 变量                                                                 */
	/************************************************************************/
	BOOL m_bWindowIsShow;	//窗口是否显示
	BOOL m_bMsgWindowsIsShow;	//消息窗口是否显示
	HMENU m_hMenu;	//托盘菜单
	HWND m_hWnd;	//主窗口句柄
	HWND m_hMsgWnd;	//消息窗口句柄
	CString m_strPort;//端口
	CString m_strAppPath;	//程序路径
	GdiplusStartupInput		m_gdiPlusInPut;
	ULONG_PTR				m_gdiPlusToken;
	HINSTANCE m_hInstance;	//程序实例句柄
	SOCKET m_Socket;	//Socket对象
	BOOL m_bIsFirstIcon;//控制托盘图标闪动
	BOOL m_bIsHasMsg;	//消息到达
	NOTIFYICONDATA m_nid;	//托盘结构
	vector<PSOCKETINMSG> m_vctMsg;	//消息容器
private:
	CMainDialog(void);
	CMainDialog(CMainDialog const&);
	CMainDialog& operator = (CMainDialog const&);
	~CMainDialog(void);
	//************************************
	// 方法:	CreateTrayNotify
	// 权限:	private 
	// 返回:	BOOL
	// 参数:	TCHAR * szTip
	// 说明:	创建托盘图标
	//************************************
	BOOL CreateTrayNotify( TCHAR *szTip); //创建托盘图标
	int GetProcessNameFromPort(DWORD dwType, u_short wdPort, TCHAR * ptsFile, DWORD dwFileSize);	//查询指定端口是否被占用
	int GetProcessNameFromId(DWORD dwProcessId, TCHAR * ptsName, DWORD dwNameLen);//获取进程名
	int GetSeleteItemText(HWND hList, TCHAR *szText);
	static DWORD WINAPI ThreadStartService( LPVOID p );//启动服务线程
	static DWORD WINAPI ThreadStartAllService( LPVOID p );//启动服务线程
	static DWORD WINAPI ThreadStopService( LPVOID p );//启动服务线程
	static DWORD WINAPI ThreadStopAllService( LPVOID p );//启动服务线程
	static DWORD WINAPI ThreadRestartService( LPVOID p );//启动服务线程
	static DWORD WINAPI ThreadRefreshServiceStatus( LPVOID p );//启动服务线程
	BOOL InstallService(TCHAR *szServiceName);//安装服务
	BOOL ServiceStart(TCHAR *szServiceName);//启动服务
	BOOL ServiceStop(TCHAR *szServiceName);//暂停服务
	BOOL ServiceStopByName(HWND hWnd, int nItemIndex, TCHAR *szText);//根据名字停止服务
	BOOL ServiceStartByName(HWND hWnd, int nItemIndex, TCHAR *szText);//根据名字启动
	inline TCHAR* GetServicePathForName(TCHAR *szServiceName, TCHAR *szServicePath);//根据服务名获取服务路径
	BOOL SetListItemText(HWND hWnd, int nItemIndex, TCHAR *szText, int nSubItem = 2);//设置列表文本
	
	static CMainDialog* m_pTheSinleton;
	HANDLE m_hMutex;	//互斥体句柄
	CIniFile m_IniFile;	//Ini对象
};
