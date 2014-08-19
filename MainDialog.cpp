//#include "MainDialog.h"
//#include "mylog.h"
//#include "AppMain.h"
#include <WindowsX.h>
#include "FQ_Std.h"
#include "MainDialog.h"
#include "AppMain.h"
#include "mylog.h"
#include "ControlService.h"
#include <process.h>

#define  WM_NOTIFYMESSAGE  WM_USER + 301	//系统托盘消息
#define  WM_SOCKET_IN  WM_USER + 302	//系统托盘消息
#define  NOTIFYID  1	//托盘ID
#define WM_NOTIFY_OPENPATH WM_USER+106 //,_T("打开目录(&D)"));
#define WM_NOTIFY_CONTACT_US WM_USER+102//,_T("联系我们(&C)"));
#define WM_NOTIFY_SERVICE_CONTROL WM_USER+103//,_T("服务管理(&S)"));
#define WM_NOTIFY_PROCESS_CONTROL WM_USER+105//,_T("程序管理(&A)"));
#define WM_NOTIFY_INTERFACE_CONTROL WM_USER+101//,_T("界面管理(&W)"));
#define WM_NOTIFY_EXIT WM_USER+104 //,_T("退出(&E)"));

#define URL_HOMEPAGE	L"http://www.mzdchina.com"
#define URL_CONTROL	L"http://127.0.0.1:"
#define URL_PROCESS_CONTROL L"MZMgrConsole.exe"

#define SVC_NAME_SPLHTTPSVC L"SPL_HTTPSVC"
#define SVC_NAME_SPLMZDIO L"SPL_MZDIO"
#define SVC_NAME_SPLTOOLSVC L"SPL_TOOLSVC"
#define SVC_NAME_SPLBTSVC L"SPL_BTSVC"

#define RECVMAXBUFFER 1024

#define ID_NOTIFYMSG_IN 1
CMainDialog* CMainDialog::m_pTheSinleton = new CMainDialog();


CMainDialog::CMainDialog(void)
{
	m_bWindowIsShow = FALSE;
}

CMainDialog::~CMainDialog(void)
{
	if (m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Socket);
	}
	WSACleanup();
}
VOID CALLBACK TimeShellNotifyIcon(HWND hWnd, UINT uMsg, UINT uTimerID, DWORD dwTime);
INT_PTR CALLBACK MsgWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMainDialog *pMainDlg = CMainDialog::Instance();
	switch(msg)
	{
	case WM_COMMAND:
		{
			WORD wmMenuID = LOWORD(wParam);
			WORD wmEvent = HIWORD(wParam);
			switch(wmMenuID)
			{
			case IDC_BTN_EXIT:	//隐藏窗口
				{
					ShowWindow(hWnd, SW_HIDE);
					pMainDlg->m_bMsgWindowsIsShow = FALSE;
				}	
				break;
			default:
				return 0;
			}
		}
		break;
	case WM_CLOSE:
		{
			ShowWindow(hWnd, SW_HIDE);
			pMainDlg->m_bMsgWindowsIsShow = FALSE;
		}
		break;
	default:
		return 0;
	}
	return 1;
}
INT_PTR CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CMainDialog* pMainDlg = CMainDialog::Instance();
	switch(message)
	{
	case WM_NOTIFYMESSAGE:	//托盘消息
		{
			if (wParam == NOTIFYID)	//如果是注册托盘的消息
			{
				switch(lParam)
				{
				case WM_RBUTTONUP:	//托盘_右键抬起
					{

						POINT *lpoint = new tagPOINT;
						::GetCursorPos(lpoint);//得到鼠标位置
						pMainDlg->m_hMenu = CreatePopupMenu();
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_OPENPATH,_T("打开目录(&D)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_CONTACT_US,_T("联系我们(&C)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_SERVICE_CONTROL,_T("服务管理(&S)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_PROCESS_CONTROL,_T("程序管理(&A)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_INTERFACE_CONTROL,_T("界面管理(&W)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_EXIT,_T("退出(&E)"));
						::SetForegroundWindow(pMainDlg->m_hWnd);
						TrackPopupMenu(pMainDlg->m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y, 0, hWnd, NULL);
						delete	lpoint;

					}
					break;
				case WM_LBUTTONDBLCLK:	//托盘_左键双击,无消息时启动URL
					{
						if (pMainDlg->m_bIsHasMsg)
						{
							KillTimer(hWnd, ID_NOTIFYMSG_IN);
							pMainDlg->m_bIsHasMsg = FALSE;
							//显示消息窗口
							if (pMainDlg->m_bMsgWindowsIsShow == FALSE)
							{
								ShowWindow(pMainDlg->m_hMsgWnd, SW_SHOW);
								pMainDlg->m_bMsgWindowsIsShow = TRUE;
							}
							//更新消息
							pMainDlg->AddMsgToMsgWnd(hWnd);
							pMainDlg->m_nid.hIcon =  LoadIcon(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon));	//加载图标
							Shell_NotifyIcon(NIM_MODIFY, &(pMainDlg->m_nid));
						}
						else
						{
							CString strUrl = URL_CONTROL + pMainDlg->m_strPort;
							pMainDlg->OpenUrl(strUrl);
						}
					}
					break;
				default:
					return 0;	//由系统处理
					break;
				}
			}
		}
		break;
	case WM_COMMAND:	//菜单消息
		{
			WORD wmMenuID = LOWORD(wParam);
			WORD wmEvent = HIWORD(wParam);
			switch(wmMenuID)
			{
			case WM_NOTIFY_INTERFACE_CONTROL:	//托盘_界面管理
				{
					CString strUrl = URL_CONTROL + pMainDlg->m_strPort;
					pMainDlg->OpenUrl(strUrl);
				}
				break;
			case WM_NOTIFY_CONTACT_US:	//托盘_联系我们
				{
					CString strUrl = URL_HOMEPAGE;
					pMainDlg->OpenUrl(strUrl);
				}
				break;
			case WM_NOTIFY_SERVICE_CONTROL:	//托盘_服务管理
				{
					ShowWindow(hWnd, SW_SHOW);
					SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
					pMainDlg->m_bWindowIsShow = TRUE;
				}
				break;
			case WM_NOTIFY_EXIT:	//托盘_退出
				{
					if(pMainDlg->ExitMainDialog()) ExitProcess(0);
				}
				break;
			case WM_NOTIFY_PROCESS_CONTROL:	//托盘_程序管理
				{
					CString strPath = pMainDlg->m_strAppPath + URL_PROCESS_CONTROL;
					if(pMainDlg->OpenUrl(strPath))
						WRITE_LOG(LOG_LEVEL_ERROR, _T("打开程序%s失败!"), strPath);
				}
				break;
			case WM_NOTIFY_OPENPATH:	//托盘_打开目录
				{
					pMainDlg->OpenUrl(pMainDlg->m_strAppPath);
				}
				break;
			case IDC_BTN_STARTSERVICE:	//启动单个服务
				{
					pMainDlg->BtnStartService(hWnd);
				}
				break;
			case IDC_BTN_STOPSERVICE:	//停止单个服务
				{
					pMainDlg->BtnStopService(hWnd);
				}
				break;
			case IDC_BTN_RESTSTART:	//重启服务
				{
					pMainDlg->BtnRestStatrService(hWnd);
				}
				break;
			case IDC_BTN_REFRESH://刷新服务状态
				{
					pMainDlg->BtnRefreshService(hWnd);
				}
				break;
			case IDC_BTN_STARTALLSRTVICE:	//启动所有服务
				{
					pMainDlg->BtnStartAllService(hWnd);
				}
				break;
			case IDC_BTN_STOPALLSERVICE:	//停止所有服务
				{
					pMainDlg->BtnStopAllService(hWnd);
				}
				break;
			case IDC_BTN_HIDEWINDOW://隐藏窗口
				{
					pMainDlg->BtnHideWindow(hWnd);
				}
				break;
			default:
				return 0;	//由系统处理
				break;
			}
		}
		break;
	case WM_CLOSE:	//窗口关闭
		{
			ShowWindow(hWnd, SW_HIDE);
			pMainDlg->m_bWindowIsShow = FALSE;
		}
		break;
	case WM_INITDIALOG:	//窗口创建
		{
			HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon)));   
			pMainDlg->InitServiceList(hWnd);
			GdiplusStartup(&pMainDlg->m_gdiPlusToken, &pMainDlg->m_gdiPlusInPut, NULL);
			pMainDlg->WriteMessage(hWnd, _T("初始化完成"));
		}
		break;
	case WM_PAINT:	//窗口重画
		{
			PAINTSTRUCT ps;
			HWND hTextName = GetDlgItem(hWnd,IDC_SERVICE_NAME); //表头-名字
			HWND hTextDescription = GetDlgItem(hWnd,IDC_SERVICE_DESCRIPTION);//表头-描述
			HWND hTextStatus = GetDlgItem(hWnd,IDC_SERVICE_STATUS);//表头-状态
			HWND hTextTitle = GetDlgItem(hWnd,IDC_Title);//表头-图标

			//隐藏窗体
			ShowWindow(hTextName,SW_HIDE);
			ShowWindow(hTextDescription,SW_HIDE);
			ShowWindow(hTextStatus,SW_HIDE);
			ShowWindow(hTextTitle,SW_HIDE);

			//获取设备
			HDC	 hParentDc = BeginPaint(hWnd,&ps);

			//获取颜色
			HBRUSH	hBrush = CreateSolidBrush(RGB(17,113,223));


			//获取位置
			RECT	rcName, rcDescription, rcStatus;
			CRect rcTitle;

			GetWindowRect(hTextName,&rcName);
			GetWindowRect(hTextDescription,&rcDescription);
			GetWindowRect(hTextStatus,&rcStatus);
			GetWindowRect(hTextTitle,&rcTitle);

			//坐标转换
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcName,2);
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcDescription,2);
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcStatus,2);
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcTitle,2);

			Graphics mGraphics(hParentDc);
			HRSRC hRsrc = ::FindResource(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDJ_Title), L"JPG");	//获取图片资源
			if (hRsrc == NULL)
			{
				break;
			}
			DWORD dwSize = ::SizeofResource(pMainDlg->m_hInstance, hRsrc); //获取资源大小
			if (dwSize == NULL)
			{
				break;
			}
			HGLOBAL hGlobal = ::LoadResource(pMainDlg->m_hInstance, hRsrc); //加载资源
			if (hGlobal == NULL)
			{
				break;
			}
			LPVOID pBuffer = ::LockResource(hGlobal); //获取资源的内存地址
			if (pBuffer == NULL)
			{
				break;
			}

			HGLOBAL hMem = (HGLOBAL)GlobalAlloc(GMEM_FIXED, dwSize);
			//HGLOBAL hMem = (HGLOBAL)new HGLOBAL[dwSize];
			if (hMem == NULL)
			{
				break;
			}
			memcpy((LPVOID)hMem,pBuffer,dwSize);

			IStream* pStm = NULL;
			::CreateStreamOnHGlobal(hMem, TRUE, &pStm); 
			Image* pImage = Gdiplus::Image::FromStream(pStm);
			pStm->Release();

			RectF	rcTitleF(rcTitle.left,rcTitle.top, rcTitle.Width(),rcTitle.Height());
			mGraphics.DrawImage(pImage,rcTitleF);

			::FreeResource(hGlobal);
			GlobalFree(hMem);
			//delete []hMem;

			FillRect(hParentDc,&rcName,hBrush);
			FillRect(hParentDc,&rcDescription,hBrush);
			FillRect(hParentDc,&rcStatus,hBrush);

			DeleteObject(hBrush);

			HFONT hFont = CreateFont(-14,0,0,0,0,0,0,0,0,0,0,0,0,_T("宋体"));
			HGDIOBJ hGDIFont = SelectObject(hParentDc,hFont);
			SetTextColor(hParentDc,RGB(255,255,255));
			SetBkMode(hParentDc,TRANSPARENT);

			DrawText(hParentDc,_T("   名称"),-1,&rcName,DT_VCENTER | DT_SINGLELINE);
			DrawText(hParentDc,_T("   描述"),-1,&rcDescription,DT_VCENTER | DT_SINGLELINE);
			DrawText(hParentDc,_T("   状态"),-1,&rcStatus,DT_VCENTER | DT_SINGLELINE);

			SelectObject(hParentDc,hGDIFont);
			DeleteObject(hFont);
			EndPaint(hWnd,&ps);
			pMainDlg->RefreshServiceStaus(hWnd);
		}
		break;
	case WM_SOCKET_IN:	//接收到BT或MZD的消息
		{
			if (WSAGETSELECTERROR(lParam))	//如果是错误消息
			{
				closesocket(wParam);
				break;
			}
			switch(WSAGETSELECTEVENT(lParam))	//获取消息
			{
			case FD_READ:
				{
					char RecvBuffer[RECVMAXBUFFER] = { 0 };//消息
					int nRecv = recvfrom(pMainDlg->m_Socket, RecvBuffer, RECVMAXBUFFER, 0, NULL, NULL);
					if (nRecv == SOCKET_ERROR)//获取消息失败
					{
						break;
					}
					BUBBLEDATA *pBubble = (BUBBLEDATA *)RecvBuffer;
					switch(pBubble->nFlags)
					{
					case 1://消息到达
						{
							//将消息更新至容器
							PSOCKETINMSG inMsg = new SOCKETINMSG;
							CTime time = CTime::GetCurrentTime();
							CString strBuf = time.Format(_T("%Y年%m月%d日 %H:%M:%S"));
							//TCHAR strBuf[MAXBYTE] = time.Format(_T("%Y年%m月%D日 %H:%M:%S"));
							_tcscpy(inMsg->szTime, strBuf.GetBuffer());
							strBuf.ReleaseBuffer();
							_tcscpy(inMsg->szMsgText, pBubble->wszMessage);
							_tcscpy(inMsg->szTitle, pBubble->wszTitle);
							pMainDlg->m_vctMsg.push_back(inMsg);
							//如果消息记录窗口被打开
							if (pMainDlg->m_bMsgWindowsIsShow == TRUE)
							{
								//不提示闪动_直接更新至消息记录窗口
								pMainDlg->AddMsgToMsgWnd(hWnd);
							}
							else
							{
								//提示消息到达_托盘图标闪动
								SetTimer(hWnd, ID_NOTIFYMSG_IN, 400, TimeShellNotifyIcon);
								pMainDlg->m_bIsHasMsg = TRUE;
							}
						}
						break;
					case 10:	//删除托盘并退出
						{
							Shell_NotifyIcon(NIM_DELETE, &pMainDlg->m_nid);
							ExitProcess(0);
						}
						break;
					default:
						break;
					}
				}
				break;
			}
		}
		break;
	default:
		return 0;	//由系统处理
		break;
	}
	return 1;	//处理已完成
}

BOOL CMainDialog::CreateMainDialog( HINSTANCE hInstance, int bIsShow )
{
	m_hInstance = hInstance;

	TCHAR szDlgName[MAXBYTE] = { 0 };
	LoadString(NULL, IDS_BrandsName, szDlgName, MAXBYTE);//读取窗口标题
	//检查程序是否已运行
	m_hMutex = CreateMutex(NULL, FALSE, _T("FQ_MainDlg"));
	if (ERROR_ALREADY_EXISTS == GetLastError())	//如果互斥体已存在
	{
		m_hWnd = FindWindowEx(NULL, NULL, NULL, szDlgName);
		if (NULL == m_hWnd)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, _T("发现互斥体,但未找到窗口句柄! ErrorCode : 0x%08X"), GetLastError());
			ExitProcess(0);
		}
		if(bIsShow == 1)
			ShowWindow(m_hWnd, SW_SHOW);
		ExitProcess(0);
	}
	//创建窗口
	m_hWnd = CreateDialog(hInstance, MAKEINTRESOURCEW(IDD_DLG_MAIN), NULL, WindowProc);
	if (m_hWnd == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("创建窗体失败! ErrorCode : 0x%08X"), GetLastError());
		CloseHandle(m_hMutex);
		ExitProcess(0);
	}
	//创建消息窗口
	m_hMsgWnd = CreateDialog(hInstance, MAKEINTRESOURCEW(IDD_DLG_MSG), NULL, MsgWndProc);
	if (m_hMsgWnd == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("创建窗体失败! ErrorCode : 0x%08X"), GetLastError());
		CloseHandle(m_hMutex);
		ExitProcess(0);
	}
	m_bMsgWindowsIsShow = FALSE;
	//显示窗口
	if (bIsShow == 1)
	{
		ShowWindow(m_hWnd, SW_SHOW);
		m_bWindowIsShow = TRUE;
	}
	
	

	//设置配置文件
	m_strAppPath = CAppMain::GetAppPath();
	CString strIniPath = m_strAppPath + _T("httpsvc.ini");
	m_IniFile.SetPath(strIniPath);

	//启动socket
	WSADATA wsaData;
	if(int nErr = WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("WSAStartup failed! ErrorCode : 0x%08X"), GetLastError());
		MessageBox(m_hWnd, _T("Socket 失败!"), NULL, MB_OK);
		ExitProcess(0);
	}
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == SOCKET_ERROR)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("Socket 失败! ErrorCode : 0x%08X"), GetLastError());
		WSACleanup();
		MessageBox(m_hWnd, _T("Socket 失败!"), NULL, MB_OK);
		ExitProcess(0);
	}

	m_strPort = m_IniFile.GetKeyValue(_T("FQ"), _T("Port"));
	int nPort = _ttoi(m_strPort);//获取端口
	TCHAR szPortOccupationProcessName[MAXBYTE] = { 0 };	//占用端口的程序名
	BOOL bRet = FALSE;
	do 
	{
		if(GetProcessNameFromPort(1, nPort, szPortOccupationProcessName, MAXBYTE) != 0)//检查端口是否被占用
		{
			CString strBuf;
			strBuf.Format(_T("名智界面管理服务使用的UDP端口:%d已被程序:\"%s\"占用!\r\n请关闭该程序后重试!"), nPort, szPortOccupationProcessName);
			if(MessageBox(m_hWnd, strBuf, _T("错误"), MB_YESNO) == IDYES)
			{
				bRet = TRUE;
			}
			else
			{
				closesocket(m_Socket);
				CloseHandle(m_hMutex);
				WSACleanup();
				ExitProcess(0);
			}
		}
	} while (bRet);
	
	SOCKADDR_IN local;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(nPort);
	bRet = FALSE;
	if (bind(m_Socket, (sockaddr*)&local, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("绑定Sokcet失败! ErrorCode : 0x%08X"), GetLastError());
		MessageBox(m_hWnd, _T("名智界面管理服务在绑定端口时出现错误!"), _T("错误"), MB_OK);
		closesocket(m_Socket);
		CloseHandle(m_hMutex);
		WSACleanup();
		ExitProcess(0);
	}
	WSAAsyncSelect(m_Socket, m_hWnd, WM_SOCKET_IN, FD_READ);	//绑定消息
	//添加托盘图标

	if (!CreateTrayNotify(szDlgName))
	{
		WRITE_LOG(LOG_LEVEL_ERROR, _T("添加托盘图标失败! ErrorCode :0x%08X"), GetLastError());
	}

	
	MSG msg;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) 
	{ 
		if (bRet == -1)
		{
			// Handle the error and possibly exit
			WRITE_LOG(LOG_LEVEL_ERROR, _T("GetMessage出现错误! ErrorCode : 0x%08X"), GetLastError());
		}
		else if (!IsWindow(m_hWnd) || !IsDialogMessage(m_hWnd, &msg)) 
		{ 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		} 
	} 
	return (int)msg.wParam;
}
BOOL CMainDialog::CreateTrayNotify( TCHAR* szTip )
{
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;
	m_nid.uID = NOTIFYID;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;//图标|回调消息|标题|消息队列
	m_nid.dwInfoFlags = NIIF_INFO;	
	m_nid.uCallbackMessage = WM_NOTIFYMESSAGE;	//回调消息
	m_nid.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon));	//加载图标
	m_nid.uVersion = NOTIFYICON_VERSION_4;	//设置版本
	//m_nid.dwState = NIS_SHAREDICON;	//图标共享
	lstrcpy(m_nid.szTip, szTip);
	//添加托盘图标
	return Shell_NotifyIcon(NIM_ADD, &m_nid);
}
//获取进程名
int CMainDialog::GetProcessNameFromId(DWORD dwProcessId, TCHAR * ptsName, DWORD dwNameLen)
{
	int nRet = 0;
	TCHAR tsFile[MAX_PATH];
	GetSystemDirectory(tsFile, sizeof(tsFile)/sizeof(TCHAR));
	lstrcat(tsFile, _T("PSAPI.DLL"));
	HMODULE hLib = LoadLibrary(tsFile);
	if (hLib != 0)
	{
#ifdef UNICODE
		DWORD (WINAPI * fnGetModuleFileNameEx) (HANDLE, HMODULE, LPWSTR, DWORD);
		*(FARPROC *)&fnGetModuleFileNameEx = GetProcAddress(hLib, "GetModuleFileNameExW");
#else
		DWORD (WINAPI * fnGetModuleFileNameEx) (HANDLE, HMODULE, LPTSTR, DWORD);
		*(FARPROC *)&fnGetModuleFileNameEx = GetProcAddress(hLib, "GetModuleFileNameExA");
#endif
		if (fnGetModuleFileNameEx != 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,dwProcessId);
			if (hProcess != 0)
			{
				nRet = fnGetModuleFileNameEx(hProcess, 0, ptsName, dwNameLen);
				CloseHandle(hProcess);
			}
		}
		FreeLibrary(hLib);
	}
	return nRet;
}


// 取得占用了指定端口的进程文件名------当绑定端口失败时使用，提示用户端口已被哪个程序占用
// dwType     = 0为TCP,1为UDP
// wdPort     = 端口
// pszFile    = 输出的进程文件名
// dwFileSize = pszFile大小
// 返回值0=失败，非0=成功
int CMainDialog::GetProcessNameFromPort(DWORD dwType, u_short wdPort, TCHAR * ptsFile, DWORD dwFileSize)
{
	int nRet = 0;
	HMODULE hLib = LoadLibrary(L"iphlpapi.dll");
	if (hLib != 0)
	{
		HANDLE hHeap = HeapCreate(0, 0, 0);
		if (hHeap != 0)
		{
			wdPort = htons(wdPort);
			if (dwType == 0)
			{	// TCP
				DWORD (WINAPI * fnAllocateAndGetTcpExTableFromStack) (PMIB_TCPTABLE_OWNER_PID *, BOOL, HANDLE, DWORD, DWORD);
				*(FARPROC *)&fnAllocateAndGetTcpExTableFromStack = GetProcAddress(hLib, "AllocateAndGetTcpExTableFromStack");
				if (fnAllocateAndGetTcpExTableFromStack != 0)
				{	// WinXP
					PMIB_TCPTABLE_OWNER_PID pTcpTable = 0;
					fnAllocateAndGetTcpExTableFromStack(&pTcpTable, TRUE, hHeap, 0, AF_INET);
					if (pTcpTable != 0)
					{
						for (DWORD i = 0; i < pTcpTable->dwNumEntries; i++)
						{
							if ((pTcpTable->table[i].dwState != MIB_TCP_STATE_CLOSED) && ((pTcpTable->table[i].dwLocalPort & 0xFFFF) == wdPort))
							{
								if ((nRet = GetProcessNameFromId(pTcpTable->table[i].dwOwningPid, ptsFile, dwFileSize)) != 0)
									break;
							}
						}
						HeapFree(hHeap, 0, pTcpTable);
					}
					if (nRet == 0)
					{
						PMIB_TCP6TABLE_OWNER_PID pTcpTable6 = 0;
						fnAllocateAndGetTcpExTableFromStack((PMIB_TCPTABLE_OWNER_PID *)&pTcpTable6, TRUE, hHeap, 0, AF_INET6);
						if (pTcpTable6 != 0)
						{
							for (DWORD i = 0; i < pTcpTable6->dwNumEntries; i++)
							{
								if ((pTcpTable6->table[i].dwState != MIB_TCP_STATE_CLOSED) && ((pTcpTable6->table[i].dwLocalPort & 0xFFFF) == wdPort))
								{
									if ((nRet = GetProcessNameFromId(pTcpTable6->table[i].dwOwningPid, ptsFile, dwFileSize)) != 0)
										break;
								}
							}
							HeapFree(hHeap, 0, pTcpTable6);
						}
					}
				}
				else
				{	// WinVista
					DWORD (WINAPI * fnInternalGetTcpTable2) (PMIB_TCPTABLE2 *, HANDLE, DWORD);
					*(FARPROC *)&fnInternalGetTcpTable2 = GetProcAddress(hLib, "InternalGetTcpTable2");
					if (fnInternalGetTcpTable2 != 0)
					{
						PMIB_TCPTABLE2 pTcpExTable = 0;
						fnInternalGetTcpTable2(&pTcpExTable, hHeap, 0);
						if (pTcpExTable != 0)
						{
							for (DWORD i = 0; i < pTcpExTable->dwNumEntries; i++)
							{
								if ((pTcpExTable->table[i].dwState != MIB_TCP_STATE_CLOSED) && ((pTcpExTable->table[i].dwLocalPort & 0xFFFF) == wdPort))
								{
									if ((nRet = GetProcessNameFromId(pTcpExTable->table[i].dwOwningPid, ptsFile, dwFileSize)) != 0)
										break;
								}
							}
							HeapFree(hHeap, 0, pTcpExTable);
						}
					}
				}
			}
			else
			{	// UDP
				DWORD (WINAPI * fnAllocateAndGetUdpExTableFromStack) (PMIB_UDPTABLE_OWNER_PID *, BOOL, HANDLE, DWORD, DWORD);
				*(FARPROC *)&fnAllocateAndGetUdpExTableFromStack = GetProcAddress(hLib, "AllocateAndGetUdpExTableFromStack");
				if (fnAllocateAndGetUdpExTableFromStack != 0)
				{	// WinXP
					PMIB_UDPTABLE_OWNER_PID pUdpTable = 0;
					fnAllocateAndGetUdpExTableFromStack(&pUdpTable, TRUE, hHeap, 0, AF_INET);
					if (pUdpTable != 0)
					{
						for (DWORD i = 0; i < pUdpTable->dwNumEntries; i++)
						{
							if ((pUdpTable->table[i].dwLocalPort & 0xFFFF) == wdPort)
							{
								if ((nRet = GetProcessNameFromId(pUdpTable->table[i].dwOwningPid, ptsFile, dwFileSize)) != 0)
									break;
							}
						}
						HeapFree(hHeap, 0, pUdpTable);
					}
					if (nRet == 0)
					{
						PMIB_UDP6TABLE_OWNER_PID pUdpTable6 = 0;
						fnAllocateAndGetUdpExTableFromStack((PMIB_UDPTABLE_OWNER_PID *)&pUdpTable6, TRUE, hHeap, 0, AF_INET);
						if (pUdpTable6 != 0)
						{
							for (DWORD i = 0; i < pUdpTable6->dwNumEntries; i++)
							{
								if ((pUdpTable6->table[i].dwLocalPort & 0xFFFF) == wdPort)
								{
									if ((nRet = GetProcessNameFromId(pUdpTable6->table[i].dwOwningPid, ptsFile, dwFileSize)) != 0)
										break;
								}
							}
							HeapFree(hHeap, 0, pUdpTable6);
						}
					}
				}
				else
				{	// WinVista
					DWORD (WINAPI * fnInternalGetUdpTableWithOwnerPid) (PMIB_UDPTABLE_OWNER_PID *, HANDLE, DWORD);
					*(FARPROC *)&fnInternalGetUdpTableWithOwnerPid = GetProcAddress(hLib, "InternalGetUdpTableWithOwnerPid");
					if (fnInternalGetUdpTableWithOwnerPid != 0)
					{
						PMIB_UDPTABLE_OWNER_PID pUdpTable = 0;
						fnInternalGetUdpTableWithOwnerPid(&pUdpTable, hHeap, 0);
						if (pUdpTable != 0)
						{
							for (DWORD i = 0; i < pUdpTable->dwNumEntries; i++)
							{
								if ((pUdpTable->table[i].dwLocalPort & 0xFFFF) == wdPort)
								{
									if ((nRet = GetProcessNameFromId(pUdpTable->table[i].dwOwningPid, ptsFile, dwFileSize)) != 0)
										break;
								}
							}
							HeapFree(hHeap, 0, pUdpTable);
						}
					}
				}
			}
			HeapDestroy(hHeap);
		}
		FreeLibrary(hLib);
	}
	return nRet;
}

BOOL CMainDialog::OpenUrl( const CString& strUrl )
{
	if (strUrl == _T(""))
	{
		return FALSE;
	}

	return (int)ShellExecute(m_hWnd, _T("open"), strUrl, _T(""), _T(""), SW_SHOW)>32?TRUE:FALSE;
}

BOOL CMainDialog::ExitMainDialog()
{
	if (m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Socket);
	}
	WSACleanup();
	CloseHandle(m_hMutex);
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	return TRUE;
}

BOOL CMainDialog::InitServiceList(HWND hWnd)
{
	//获取控件
	HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);	//列表
	HWND hTextName = GetDlgItem(hWnd,IDC_SERVICE_NAME);	//服务名
	HWND hTextDescription = GetDlgItem(hWnd,IDC_SERVICE_DESCRIPTION);	//服务描述
	HWND hTextStatus = GetDlgItem(hWnd,IDC_SERVICE_STATUS);//服务状态
	SendMessage(hList,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置列表框选中
	
	//获取控件位置
	CRect rcTextName, rcTextDescription, rcTextStatus;
	GetWindowRect(hTextName, rcTextName);
	GetWindowRect(hTextDescription, rcTextDescription);
	GetWindowRect(hTextStatus, rcTextStatus);
	
	//设置list位置
	LV_COLUMN lvc = { 0 };
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;//设置文本宽度有效
	lvc.cx = rcTextName.Width();
	SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&lvc);
	lvc.cx = rcTextDescription.Width() - 22;
	SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&lvc);
	lvc.cx = rcTextStatus.Width();
	SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&lvc);
	
	//设置图标
	HIMAGELIST  hImageList = ImageList_Create(32, 32, ILC_COLOR16 | ILC_MASK, 0, 0);
	ListView_SetImageList(hList,hImageList,LVSIL_SMALL);
	HICON  hIcon = NULL;



	hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON));
	ImageList_AddIcon(hImageList,hIcon);
	DestroyIcon(hIcon);

	hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON_MZD));
	ImageList_AddIcon(hImageList,hIcon); 
	DestroyIcon(hIcon);

	hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON_TOOL));
	ImageList_AddIcon(hImageList,hIcon);
	DestroyIcon(hIcon);

	hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON_BT));
	ImageList_AddIcon(hImageList,hIcon);
	DestroyIcon(hIcon);
	
	
	//设置服务状态
	LV_ITEM lvItem = { 0 };
	int nItemIndex = 0;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	
	CString strSvcStatus;
	//HTTPSVC
	lvItem.iSubItem = 0;	//设置第一列	
	lvItem.pszText = SVC_NAME_SPLHTTPSVC;
	nItemIndex = SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iSubItem = 1;
	lvItem.iItem = nItemIndex;
	lvItem.iImage = 1;
	lvItem.pszText = _T("斯普林名智界面管理服务");
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);

	//MZD
	lvItem.iItem = ++nItemIndex;
	lvItem.iSubItem = 0; 
	lvItem.pszText = SVC_NAME_SPLMZDIO;
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = 1;
	lvItem.iImage = 2;
	lvItem.pszText = (_T("斯普林名智磁盘服务"));
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);
	
	//TOOL
	lvItem.iItem = ++nItemIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = SVC_NAME_SPLTOOLSVC;
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = 1;
	lvItem.iImage = 3;
	lvItem.pszText = (_T("斯普林名智辅助工具服务"));
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);

	//BT
	lvItem.iItem = ++nItemIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = SVC_NAME_SPLBTSVC;
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = 1;
	lvItem.iImage = 4;
	lvItem.pszText = (_T("斯普林完美下载服务"));
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);

	RefreshServiceStaus(hWnd);
	return TRUE;
}

BOOL CMainDialog::RefreshServiceStaus(HWND hWnd)
{
	HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);	//列表
	CControlServiceEx serviceInfo;	
	
	LV_ITEM lvItem = { 0 };
	int nItemIndex = 0;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;

	CString strSvcStatus;
	//HTTP
	strSvcStatus = serviceInfo.ServiceStatusToCString(serviceInfo.GetServiceStatus(SVC_NAME_SPLHTTPSVC));
	SetListItemText(hWnd, nItemIndex++, strSvcStatus.GetBuffer());
	strSvcStatus.ReleaseBuffer();
	//MZD
	strSvcStatus = serviceInfo.ServiceStatusToCString(serviceInfo.GetServiceStatus(SVC_NAME_SPLMZDIO));
	SetListItemText(hWnd, nItemIndex++, strSvcStatus.GetBuffer());
	strSvcStatus.ReleaseBuffer();
	//TOOL
	strSvcStatus = serviceInfo.ServiceStatusToCString(serviceInfo.GetServiceStatus(SVC_NAME_SPLTOOLSVC));
	SetListItemText(hWnd, nItemIndex++, strSvcStatus.GetBuffer());
	strSvcStatus.ReleaseBuffer();
	//BT	
	strSvcStatus = serviceInfo.ServiceStatusToCString(serviceInfo.GetServiceStatus(SVC_NAME_SPLBTSVC));
	SetListItemText(hWnd, nItemIndex++, strSvcStatus.GetBuffer());
	strSvcStatus.ReleaseBuffer();
	return TRUE;
}

BOOL CMainDialog::WriteMessage( HWND hWnd, CString strMsg )
{
	HWND hMsg = GetDlgItem(hWnd, IDC_MESSAGE);
	return SetWindowText(hMsg, _T("提示:") + strMsg);
}


BOOL CMainDialog::BtnStartService( HWND hWnd )
{
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTSERVICE);
	EnableWindow(hBtn, FALSE);	//禁用按钮
	
	HANDLE hThread = CreateThread(NULL, 0, ThreadStartService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadStartService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	CControlServiceEx serviceCon;
	TCHAR szText[MAXBYTE];
	int nItemIndex = pMainDlg->GetSeleteItemText(hWnd, szText);
	int nAgainNum = 0;
	do 
	{
		if (_tcscmp(szText, _T("")) == 0)
		{
			pMainDlg->WriteMessage(hWnd, _T("请选择服务!"));
			break;
		}
		//int dwServiceStatus = serviceCon.GetServiceStatus(szText);
		//if (dwServiceStatus == SERVICE_RUNNING && nAgainNum == 0)	//服务已启动退出
		//{
		//	CString strBuf;
		//	strBuf.Format(_T("%s服务正在运行,无需再次启动!"), szText);
		//	pMainDlg->WriteMessage(hWnd, strBuf);
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_RUNNING).GetBuffer());
		//	break;
		//}
		//else
		//{
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, _T("正在启动"));
		//	//启动服务
		//	switch(dwServiceStatus)
		//	{
		//	case -1:	//服务未安装
		//		{
		//			if(FALSE == pMainDlg->InstallService(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("安装服务时出现错误!"));
		//				CString strBuf;
		//				strBuf.Format(_T("安装服务%s时出现错误!请检查文件是否完整!建议重新安装本程序!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务未安装"));
		//				bAgain = FALSE;//不继续循环
		//			}
		//		}
		//		break;
		//	case SERVICE_RUNNING:	//正在运行
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("%s服务启动成功!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_RUNNING).GetBuffer());
		//			bAgain = FALSE;//不继续循环
		//		}
		//		break;
		//	case SERVICE_STOPPED:	//已停止
		//	case SERVICE_CONTINUE_PENDING://挂起
		//	case SERVICE_PAUSED:	//暂停
		//		{
		//			if (FALSE == pMainDlg->ServiceStart(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("启动服务时发生错误!"));
		//				CString strBuf;
		//				strBuf.Format(_T("启动服务%s时出现错误!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务启动失败"));
		//				bAgain = FALSE;//不继续循环
		//			}
		//		}
		//		break;
		//	default:
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("正在启动服务%s!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			if (nAgainNum % 4 == 0)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务启动中"));
		//			}
		//			else if(nAgainNum %4 == 1)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务启动中."));
		//			}
		//			else if(nAgainNum %4 == 2)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务启动中.."));
		//			}
		//			else if(nAgainNum %4 == 3)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务启动中..."));
		//			}
		//		}
		//		break;
		//	}
		//}
		//nAgainNum ++;
		//Sleep(500);
		//if (nAgainNum == 20)
		//{
		//	WRITE_LOG(LOG_LEVEL_ERROR, _T("启动服务时发生错误!"));
		//	CString strBuf;
		//	strBuf.Format(_T("启动服务%s超时!请重试"), szText);
		//	pMainDlg->WriteMessage(hWnd, strBuf);
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务启动超时"));
		//	bAgain = FALSE;//不继续循环
		//}

		pMainDlg->ServiceStartByName(hWnd, nItemIndex, szText);
	} while (FALSE);
	
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTSERVICE);
	EnableWindow(hBtn, TRUE);	//禁用按钮
	return 1;
}

int CMainDialog::GetSeleteItemText(HWND hWnd, TCHAR *szText)
{
	if (szText == NULL)
	{
		szText = new TCHAR[MAXBYTE];
	}
	HWND hList = GetDlgItem(hWnd, IDC_LIST_SERVICE);
	int nItemIndex = SendMessage(hList, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
	if (nItemIndex == -1)
	{
		_tcscpy(szText, _T(""));
		return nItemIndex;
	}
	LV_ITEM lvItem = {0};
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItemIndex;
	lvItem.cchTextMax = MAXBYTE;
	lvItem.pszText = szText;
	SendMessage(hList, LVM_GETITEM, 0, (LPARAM)&lvItem);
	return nItemIndex;
}

TCHAR* CMainDialog::GetServicePathForName( TCHAR *szServiceName, TCHAR *szServicePath )
{
	if (szServicePath == NULL)
	{
		szServicePath = new TCHAR[MAX_PATH];
	}
	if (_tcscmp(szServiceName, SVC_NAME_SPLBTSVC) == 0)
	{
		_tcscpy(szServicePath, m_strAppPath + _T("btsvc.exe"));
	}
	else if (_tcscmp(szServiceName, SVC_NAME_SPLHTTPSVC) == 0)
	{
		_tcscpy(szServicePath, m_strAppPath + _T("httpsvc.exe /Start"));
	}
	else if (_tcscmp(szServiceName, SVC_NAME_SPLMZDIO) == 0)
	{
		_tcscpy(szServicePath, m_strAppPath + _T("MZDIO.exe"));
	}
	else if (_tcscmp(szServiceName, SVC_NAME_SPLTOOLSVC) == 0)
	{
		_tcscpy(szServicePath, m_strAppPath + _T("toolsvc.exe"));
	}
	else
	{
		_tcscpy(szServicePath, _T(""));
	}
	return szServicePath;
}

BOOL CMainDialog::InstallService( TCHAR *szServiceName )
{
	BOOL bRet = FALSE;
	TCHAR szServicePath[MAX_PATH];
	GetServicePathForName(szServiceName, szServicePath);
	if (_tcscmp(szServicePath, _T("")) != 0)
	{
		bRet = OpenUrl(szServicePath);
	}
	return bRet;
}

BOOL CMainDialog::SetListItemText( HWND hWnd, int nItemIndex, TCHAR *szText, int nSubItem)
{
	HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);	//列表
	LV_ITEM lvItem = { 0 };
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = szText;
	return SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);
}

BOOL CMainDialog::ServiceStart( TCHAR *szServiceName )
{
	BOOL bRet = FALSE;
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService;
	do 
	{
		if (hScm == NULL)
		{
			break;
		}
		hService = OpenService(hScm, szServiceName, SERVICE_ALL_ACCESS);
		if (hService == NULL)
		{
			break;
		}
		if (StartService(hService, 0, 0) == TRUE)
		{
			bRet = TRUE;
		}
	} while (FALSE);
	if(hScm != NULL)
		CloseServiceHandle(hScm);
	if(hService != NULL)
		CloseServiceHandle(hService);
	return bRet;
}

BOOL CMainDialog::BtnStopService( HWND hWnd )
{
	WriteMessage(hWnd, _T("开始暂停服务"));
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPSERVICE);
	EnableWindow(hBtn, FALSE);	//禁用按钮

	HANDLE hThread = CreateThread(NULL, 0, ThreadStopService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadStopService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	
	TCHAR szText[MAXBYTE];
	int nItemIndex = pMainDlg->GetSeleteItemText(hWnd, szText);
	BOOL bAgain = TRUE;
	int nAgainNum = 0;
	do 
	{
		if (_tcscmp(szText, _T("")) == 0)
		{
			pMainDlg->WriteMessage(hWnd, _T("请选择服务!"));
			break;
		}
		pMainDlg->ServiceStopByName(hWnd, nItemIndex, szText);
		//int dwServiceStatus = serviceCon.GetServiceStatus(szText);
		//if (dwServiceStatus == SERVICE_STOPPED && nAgainNum == 0)	//服务已暂停退出
		//{
		//	CString strBuf;
		//	strBuf.Format(_T("%s服务已暂停,无需再次暂停!"), szText);
		//	pMainDlg->WriteMessage(hWnd, strBuf);
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_STOPPED).GetBuffer());
		//	break;
		//}
		//else
		//{
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, _T("正在暂停"));
		//	//暂停服务
		//	switch(dwServiceStatus)
		//	{
		//	case -1:	//服务未安装
		//		{
		//			if(FALSE == pMainDlg->InstallService(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时出现错误!"));
		//				CString strBuf;
		//				strBuf.Format(_T("暂停服务%s时出现错误!请检查文件是否完整!建议重新安装本程序!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务未安装"));
		//				bAgain = FALSE;//不继续循环
		//			}
		//		}
		//		break;
		//	case SERVICE_STOPPED:	//已停止
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("%s服务暂停成功!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_STOPPED).GetBuffer());
		//			bAgain = FALSE;//不继续循环
		//		}
		//		break;
		//	case SERVICE_RUNNING:	//已启动
		//		{
		//			if (FALSE == pMainDlg->ServiceStop(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时发生错误!"));
		//				CString strBuf;
		//				strBuf.Format(_T("暂停服务%s时出现错误!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停失败"));
		//				bAgain = FALSE;//不继续循环
		//			}
		//		}
		//		break;
		//	default:
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("正在暂停服务%s!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			if (nAgainNum % 4 == 0)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停中"));
		//			}
		//			else if(nAgainNum %4 == 1)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停中."));
		//			}
		//			else if(nAgainNum %4 == 2)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停中.."));
		//			}else if(nAgainNum %4 == 3)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停中..."));
		//			}
		//		}
		//		break;
		//	}
		//}
		//nAgainNum ++;
		//Sleep(1000);
		//if (nAgainNum == 20)
		//{
		//	
		//	CString strBuf;
		//	if (dwServiceStatus == SERVICE_STOP_PENDING)
		//	{
		//		if (nAgainNum == 60) //一分钟
		//		{
		//			WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时发生超时!"));
		//			strBuf.Format(_T("暂停服务%s超时!请重试"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停超时"));
		//			bAgain = FALSE;//不继续循环
		//		}
		//	}
		//	else
		//	{
		//		WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时发生超时!"));
		//		strBuf.Format(_T("暂停服务%s超时!请重试"), szText);
		//		pMainDlg->WriteMessage(hWnd, strBuf);
		//		pMainDlg->SetListItemText(hWnd, nItemIndex, _T("服务暂停超时"));
		//		bAgain = FALSE;//不继续循环
		//	}
		//	
		//}


	} while (FALSE);

	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPSERVICE);
	EnableWindow(hBtn, TRUE);	//禁用按钮
	return 1;
}

BOOL CMainDialog::ServiceStop( TCHAR *szServiceName )
{
	BOOL bRet = FALSE;
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	SC_HANDLE hService;
	do 
	{
		if (hScm == NULL)
		{
			break;
		}
		hService = OpenService(hScm, szServiceName, SERVICE_ALL_ACCESS);
		if (hService == NULL)
		{
			break;
		}
		SERVICE_STATUS svcStatus;
		if (QueryServiceStatus(hService, &svcStatus) == FALSE)
		{
			break;
		}
		if (ControlService(hService, SERVICE_CONTROL_STOP, &svcStatus) == FALSE)
		{
			break;
		}
		bRet = TRUE;
	} while (FALSE);
	if(hScm != NULL)
		CloseServiceHandle(hScm);
	if(hService != NULL)
		CloseServiceHandle(hService);
	return bRet;
}

BOOL CMainDialog::BtnRestStatrService( HWND hWnd )
{
	WriteMessage(hWnd, _T("开始重启服务"));
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_RESTSTARTSERVICE);
	EnableWindow(hBtn, FALSE);	//禁用按钮

	HANDLE hThread = CreateThread(NULL, 0, ThreadRestartService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadRestartService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	CControlServiceEx serviceCon;
	TCHAR szText[MAXBYTE];
	int nItemIndex = pMainDlg->GetSeleteItemText(hWnd, szText);
	int nAgainNum = 0;
	do 
	{
		if (_tcscmp(szText, _T("")) == 0)
		{
			pMainDlg->WriteMessage(hWnd, _T("请选择服务!"));
			break;
		}
		CString strBuf;
		int dwServiceStatus = serviceCon.GetServiceStatus(szText);
		if (dwServiceStatus != SERVICE_STOPPED)	//如果服务不为停止
		{
			//停止服务
			if(pMainDlg->ServiceStopByName(hWnd, nItemIndex, szText) == FALSE)
			{
				strBuf.Format(_T("重启服务%s因无法停止导致失败!"), szText);
				pMainDlg->WriteMessage(hWnd, strBuf);
				break;
			}
		}
		//启动服务
		if(pMainDlg->ServiceStartByName(hWnd, nItemIndex, szText) == FALSE)
		{
			strBuf.Format(_T("重启服务%s因无法启动导致失败!"), szText);
			pMainDlg->WriteMessage(hWnd, strBuf);
			break;
		}
		strBuf.Format(_T("重启服务%s成功!"), szText);
		pMainDlg->WriteMessage(hWnd, strBuf);
	} while (FALSE);

	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_RESTSTARTSERVICE);
	EnableWindow(hBtn, TRUE);	//禁用按钮
	return 1;
}



BOOL CMainDialog::ServiceStopByName( HWND hWnd, int nItemIndex, TCHAR *szText)
{
	SetListItemText(hWnd, nItemIndex, _T("正在暂停"));
	//暂停服务
	CControlServiceEx serviceCon;
	int dwServiceStatus;
	BOOL bAgain = TRUE;
	int nAgainNum = 0;
	CString strBuf;
	strBuf.Format(_T("开始暂停服务%s"), szText);
	do 
	{
		dwServiceStatus = serviceCon.GetServiceStatus(szText);
		if (dwServiceStatus == SERVICE_STOPPED && nAgainNum == 0)	//服务已暂停退出
		{
			strBuf.Format(_T("%s服务已暂停,无需再次暂停!"), szText);
			WriteMessage(hWnd, strBuf);
			strBuf = serviceCon.ServiceStatusToCString(SERVICE_STOPPED);
			SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());
			strBuf.ReleaseBuffer();
			break;
		}
		switch(dwServiceStatus)
		{
		case -1:	//服务未安装
			{
				if(FALSE == InstallService(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时出现错误!"));
					strBuf.Format(_T("暂停服务%s时出现错误!请检查文件是否完整!建议重新安装本程序!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("服务未安装"));
					return FALSE;
				}
			}
			break;
		case SERVICE_STOPPED:	//已停止
			{
				strBuf.Format(_T("%s服务暂停成功!"), szText);
				WriteMessage(hWnd, strBuf);
				strBuf = serviceCon.ServiceStatusToCString(SERVICE_STOPPED);
				SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());
				strBuf.ReleaseBuffer();
				bAgain = FALSE;//不继续循环
			}
			break;
		case SERVICE_RUNNING:	//已启动
			{
				if (FALSE == ServiceStop(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时发生错误!"));
					strBuf.Format(_T("暂停服务%s时出现错误!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("服务暂停失败"));
					return FALSE;
				}
			}
			break;
		default:
			{
				strBuf.Format(_T("正在暂停服务%s!"), szText);
				WriteMessage(hWnd, strBuf);
				if (nAgainNum % 4 == 0)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务暂停中"));
				}
				else if(nAgainNum %4 == 1)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务暂停中."));
				}
				else if(nAgainNum %4 == 2)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务暂停中.."));
				}else if(nAgainNum %4 == 3)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务暂停中..."));
				}
			}
			break;
		}
		nAgainNum ++;
		Sleep(1000);
		if (nAgainNum == 20)
		{

			if (dwServiceStatus == SERVICE_STOP_PENDING)
			{
				if (nAgainNum == 60) //一分钟
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时发生超时!"));
					strBuf.Format(_T("暂停服务%s超时!请重试"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("服务暂停超时"));
					return FALSE;
				}
			}
			else
			{
				WRITE_LOG(LOG_LEVEL_ERROR, _T("暂停服务时发生超时!"));
				strBuf.Format(_T("暂停服务%s超时!请重试"), szText);
				WriteMessage(hWnd, strBuf);
				SetListItemText(hWnd, nItemIndex, _T("服务暂停超时"));
				return FALSE;
			}
		}
	} while (bAgain);
	return TRUE;
}

BOOL CMainDialog::ServiceStartByName( HWND hWnd, int nItemIndex, TCHAR *szText )
{
	SetListItemText(hWnd, nItemIndex, _T("正在启动"));
	//启动服务
	CControlServiceEx serviceCon;
	int dwServiceStatus;//服务状态
	BOOL bAgain = TRUE;	//是否再次循环 
	int nAgainNum = 0;	//循环次数
	CString strBuf;
	strBuf.Format(_T("开始启动服务%s"), szText);
	WriteMessage(hWnd, strBuf);
	do 
	{
		dwServiceStatus = serviceCon.GetServiceStatus(szText);
		if (dwServiceStatus == SERVICE_RUNNING && nAgainNum == 0)	//服务正在运行
		{
			strBuf.Format(_T("%s服务已运行,无需再次运行!"), szText);
			WriteMessage(hWnd, strBuf);
			strBuf = serviceCon.ServiceStatusToCString(SERVICE_RUNNING);
			SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());//设置文本为服务正在运行
			strBuf.ReleaseBuffer();
			break;//退出循环
		}
		switch(dwServiceStatus)
		{
		case -1:	//服务未安装
			{
				if(FALSE == InstallService(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("安装服务时出现错误!"));
					strBuf.Format(_T("安装服务%s时出现错误!请检查文件是否完整!建议重新安装本程序!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("服务未安装"));
					return FALSE;
				}
			}
			break;
		case SERVICE_RUNNING:	//正在运行
			{
				strBuf.Format(_T("%s服务启动成功!"), szText);
				WriteMessage(hWnd, strBuf);
				strBuf = serviceCon.ServiceStatusToCString(SERVICE_RUNNING);
				SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());
				strBuf.ReleaseBuffer();
				bAgain = FALSE;//不继续循环
			}
			break;
		case SERVICE_STOPPED:	//已停止
		case SERVICE_CONTINUE_PENDING://挂起
		case SERVICE_PAUSED:	//暂停
			{
				if (FALSE == ServiceStart(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("启动服务时发生错误!"));
					strBuf.Format(_T("启动服务%s时出现错误!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("服务启动失败"));
					return FALSE;
				}
			}
			break;
		default:
			{
				strBuf.Format(_T("正在启动服务%s!"), szText);
				WriteMessage(hWnd, strBuf);
				if (nAgainNum % 4 == 0)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务启动中"));
				}
				else if(nAgainNum %4 == 1)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务启动中."));
				}
				else if(nAgainNum %4 == 2)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务启动中.."));
				}
				else if(nAgainNum %4 == 3)
				{
					SetListItemText(hWnd, nItemIndex, _T("服务启动中..."));
				}
			}
			break;
		}
		nAgainNum ++;
		Sleep(1000);
		if (nAgainNum == 20)
		{

			if (dwServiceStatus == SERVICE_START_PENDING)//服务正在运行
			{
				if (nAgainNum == 60) //一分钟
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("启动服务时发生超时!"));
					strBuf.Format(_T("启动服务%s超时!请重试"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("服务启动超时"));
					return FALSE;
				}
			}
			else
			{
				WRITE_LOG(LOG_LEVEL_ERROR, _T("启动服务时发生超时!"));
				strBuf.Format(_T("启动服务%s超时!请重试"), szText);
				WriteMessage(hWnd, strBuf);
				SetListItemText(hWnd, nItemIndex, _T("服务启动超时"));
				return FALSE;
			}
		}
	} while (bAgain);
	return TRUE;
}

BOOL CMainDialog::BtnRefreshService( HWND hWnd )
{
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_REFRESH);
	EnableWindow(hBtn, FALSE);	//禁用按钮

	HANDLE hThread = CreateThread(NULL, 0, ThreadRefreshServiceStatus, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadRefreshServiceStatus( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	pMainDlg->WriteMessage(hWnd, _T("开始刷新服务状态!"));
	pMainDlg->RefreshServiceStaus(hWnd);
	
	pMainDlg->WriteMessage(hWnd, _T("服务状态刷新完成!"));
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_REFRESH);
	EnableWindow(hBtn, TRUE);	//禁用按钮
	return 1;
}

BOOL CMainDialog::BtnStartAllService( HWND hWnd )
{
	WriteMessage(hWnd, _T("开始启动所有服务"));
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTALLSRTVICE);
	EnableWindow(hBtn, FALSE);	//禁用按钮

	HANDLE hThread = CreateThread(NULL, 0, ThreadStartAllService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadStartAllService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	//获取列表
	HWND hList = GetDlgItem(hWnd, IDC_LIST_SERVICE);
	LV_ITEM lvItem = { 0 };
	TCHAR szText[MAXBYTE] = { 0 };
	lvItem.mask = LVIF_TEXT;
	lvItem.cchTextMax = MAXBYTE;
	lvItem.pszText = szText;
	do 
	{
		for (int i = 0; i < 4; i++)
		{
			lvItem.iItem = i;
			ZeroMemory(szText, MAXBYTE);
			SendMessage(hList, LVM_GETITEM, 0, (LPARAM)&lvItem);
			if(pMainDlg->ServiceStartByName(hWnd, i, szText) == FALSE)
			{
				CString strBuf;
				strBuf.Format(_T("启动服务%s失败,将继续启动下一个服务!"), szText);
				pMainDlg->WriteMessage(hWnd, strBuf);
				Sleep(1000);
			}
		}
	} while (FALSE);
	pMainDlg->WriteMessage(hWnd, _T("启动所有服务操作完成!"));
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTALLSRTVICE);
	EnableWindow(hBtn, TRUE);	//启用按钮
	return 1;
}

BOOL CMainDialog::BtnStopAllService( HWND hWnd )
{
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPALLSERVICE);
	EnableWindow(hBtn, FALSE);	//禁用按钮

	HANDLE hThread = CreateThread(NULL, 0, ThreadStopAllService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadStopAllService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	//获取列表
	HWND hList = GetDlgItem(hWnd, IDC_LIST_SERVICE);
	LV_ITEM lvItem = { 0 };
	TCHAR szText[MAXBYTE] = { 0 };
	lvItem.mask = LVIF_TEXT;
	lvItem.cchTextMax = MAXBYTE;
	lvItem.pszText = szText;
	do 
	{
		for (int i = 0; i < 4; i++)
		{
			lvItem.iItem = i;
			ZeroMemory(szText, MAXBYTE);
			SendMessage(hList, LVM_GETITEM, 0, (LPARAM)&lvItem);
			if(pMainDlg->ServiceStopByName(hWnd, i, szText) == FALSE)
			{
				CString strBuf;
				strBuf.Format(_T("暂停服务%s失败,将继续暂停下一个服务!"), szText);
				pMainDlg->WriteMessage(hWnd, strBuf);
				Sleep(1000);
			}
		}
	} while (FALSE);
	pMainDlg->WriteMessage(hWnd, _T("暂停所有服务操作完成!"));
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPALLSERVICE);
	EnableWindow(hBtn, TRUE);	//启用按钮
	return 1;
}

BOOL CMainDialog::BtnHideWindow( HWND hWnd )
{
	ShowWindow(hWnd, FALSE);
	m_bWindowIsShow = FALSE;
	return TRUE;
}

BOOL CMainDialog::AddMsgToMsgWnd( HWND hMsgWnd )
{
	HWND hEdit = GetDlgItem(m_hMsgWnd, IDC_EDIT_MSGTEXT);
	TCHAR szEditText[1024] = { 0 };
	TCHAR szBufText[1024] = { 0 };
	int nLen;
	Edit_GetText(hEdit, szEditText, 1024);
	//strText.ReleaseBuffer();
	for (vector<PSOCKETINMSG>::iterator iter = m_vctMsg.begin();
		iter != m_vctMsg.end(); ++iter)
	{
		swprintf(szBufText, _T("%s\t%s\r\n%s\r\n"), (*iter)->szTime,(*iter)->szTitle, (*iter)->szMsgText);
		//strBuf.Format(_T("%s\r%s\r\n%s\r\n"), (*iter)->szTime, (*iter)->szTitle, (*iter)->szMsgText);
		nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		SendMessage(hEdit, EM_SETSEL, 0, (LPARAM)nLen);
		_tcscat(szEditText,szBufText);
		//strText += strBuf;
		//SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)strText.GetBuffer());
		SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)szEditText);
		//strText.ReleaseBuffer();
		delete *iter;
	}
	m_vctMsg.clear();
	return TRUE;
}

VOID CALLBACK TimeShellNotifyIcon( HWND hWnd, UINT uMsg, UINT uTimerID, DWORD dwTime )
{
	CMainDialog *pMainDlg = CMainDialog::Instance();
	if (pMainDlg->m_bIsFirstIcon)
	{
		pMainDlg->m_nid.hIcon = NULL;
		Shell_NotifyIcon(NIM_MODIFY, &(pMainDlg->m_nid));
		pMainDlg->m_bIsFirstIcon = FALSE;
	}
	else
	{
		pMainDlg->m_nid.hIcon =  LoadIcon(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon));	//加载图标
		Shell_NotifyIcon(NIM_MODIFY, &(pMainDlg->m_nid));
		pMainDlg->m_bIsFirstIcon = TRUE;
	}
}

