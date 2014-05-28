// ServiceWindow.cpp : 实现文件
//

#include "FQ_Std.h"
#include "ServiceWindow.h"
#include "AppMain.h"
#include "mylog.h"
#include "ControlService.h"

#pragma comment(lib, "ws2_32.lib")

#define		Hide_Flags		WM_USER + 301
#define		PopupMenu		WM_USER + 302

#define		WM_SOCKET_IN		WM_USER + 401
#define		WM_INITWINODW	WM_USER + 402
#define WM_NOTIFY_OPENPATH WM_USER+106 //,_T("打开目录(&D)"));
#define WM_NOTIFY_CONTACT_US WM_USER+102//,_T("联系我们(&C)"));
#define WM_NOTIFY_SERVICE_CONTROL WM_USER+103//,_T("服务管理(&S)"));
#define WM_NOTIFY_PROCESS_CONTROL WM_USER+105//,_T("程序管理(&A)"));
#define WM_NOTIFY_INTERFACE_CONTROL WM_USER+101//,_T("界面管理(&W)"));
#define WM_NOTIFY_EXIT WM_USER+104 //,_T("退出(&E)"));


CServiceWindow*	pServiceWindow = NULL;
int				g_CloseFlags = 0;	//关闭标识
int				g_MsgTaskbarRestart = 0;

int GetProcessNameFromId(DWORD dwProcessId, TCHAR * ptsName, DWORD dwNameLen)
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
int GetProcessNameFromPort(DWORD dwType, u_short wdPort, TCHAR * ptsFile, DWORD dwFileSize)
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





DWORD	WINAPI	CloseThread(LPVOID	lpvoid)
{
	HWND	MainhWnd = (HWND)lpvoid;
	g_CloseFlags = 1;

	CServiceWindow*	pServiceWindow = CServiceWindow::GetServiceWindow();
	CloseHandle(pServiceWindow->FQ_ShangGuanXWHandle);
	pServiceWindow->m_nid.cbSize = sizeof(NOTIFYICONDATA);
	pServiceWindow->m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_REALTIME;
	pServiceWindow->m_nid.uTimeout = 5000;
	pServiceWindow->m_nid.dwInfoFlags = NIIF_INFO;
	lstrcpy(pServiceWindow->m_nid.szInfo,_T("程序正在关闭中,请稍后..."));
	lstrcpy(pServiceWindow->m_nid.szInfoTitle,_T("名智2013"));
	Shell_NotifyIcon(NIM_MODIFY, &pServiceWindow->m_nid);

	//ThreadStopAll((LPVOID)MainhWnd);

	pServiceWindow->m_nid.cbSize = sizeof(NOTIFYICONDATA);
	pServiceWindow->m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_REALTIME;
	Shell_NotifyIcon(NIM_DELETE, &pServiceWindow->m_nid);

	ExitProcess(0);

	return 0;
}


//************************************
// 方法名:	WndProc
// 全名称:	WndProc
// 访问级:	public 
// 返回值:	INT_PTR CALLBACK
// 限定符:	
// 参  数:	HWND hWnd
// 参  数:	UINT message
// 参  数:	WPARAM wParam
// 参  数:	LPARAM lParam
// 备  注:	窗口过程
//************************************
INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CServiceWindow*	pServiceWindow = CServiceWindow::GetServiceWindow();
	//防止程序被第三方程序激活显示
	if ( message == WM_WINDOWPOSCHANGING && InSendMessage() )
	{
		WINDOWPOS * pWps = (WINDOWPOS *)lParam; 
		if (pWps->flags & SWP_SHOWWINDOW) 
		{
			pWps->flags = pWps->flags & ~SWP_SHOWWINDOW;
		}
	}
	if (message == g_MsgTaskbarRestart)	//如果消息是自己注册的TaskbarCreated
	{
		TCHAR	wszBrandsName[MAXBYTE] = { 0 };
		LoadString(NULL,IDS_BrandsName,wszBrandsName,MAXBYTE);
		memset(&pServiceWindow->m_nid,0,sizeof(NOTIFYICONDATA));
		pServiceWindow->m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
		pServiceWindow->m_nid.hWnd = hWnd;
		pServiceWindow->m_nid.uID = 1;
		pServiceWindow->m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_REALTIME;
		pServiceWindow->m_nid.dwInfoFlags = NIIF_INFO;
		pServiceWindow->m_nid.uCallbackMessage = PopupMenu;//自定义的消息名称
		pServiceWindow->m_nid.hIcon = LoadIcon(pServiceWindow->m_hInstance,MAKEINTRESOURCE(IDI_MiniIcon));
		lstrcpy(pServiceWindow->m_nid.szTip,wszBrandsName);//信息提示条为“计划任务提醒”
		//在托盘区添加图标
		if (!Shell_NotifyIcon(NIM_ADD,&pServiceWindow->m_nid))
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"Shell_NotifyIcon失败！错误代码 %d",GetLastError());
		}
		return 0;
	}

	switch (message)
	{
	case	PopupMenu:		//自定义消息过程	1326
		{
			if (wParam == 1)
			{
				switch (lParam)
				{
				case	WM_RBUTTONUP:
					{
						if (!g_CloseFlags)	//检查窗口是否被关闭
						{
							LPPOINT lpoint = new tagPOINT;
							::GetCursorPos(lpoint);//得到鼠标位置
							pServiceWindow->m_hMenu = CreatePopupMenu();
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_OPENPATH,_T("打开目录(&D)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_CONTACT_US,_T("联系我们(&C)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_SERVICE_CONTROL,_T("服务管理(&S)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_PROCESS_CONTROL,_T("程序管理(&A)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_INTERFACE_CONTROL,_T("界面管理(&W)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_EXIT,_T("退出(&E)"));
							::SetForegroundWindow(pServiceWindow->m_hWnd);
							TrackPopupMenu(pServiceWindow->m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y, 0, hWnd, NULL);
							delete	lpoint;
						}
					}
					break;
				case	WM_LBUTTONDBLCLK://双击左键的处理
					{
						CString strPort = pServiceWindow->m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));
						CString		strUrl;
						strUrl.Format(_T("http://127.0.0.1:%s/"),strPort);
						ShellExecute(hWnd,_T("open"),strUrl.GetBuffer(),_T(""),_T(""),SW_SHOW);
					}
					break;
				}
			}
		}
		break;
	case	WM_COMMAND:
		{
			int		wmId    = LOWORD(wParam);
			int		wmEvent = HIWORD(wParam);
			// 分析菜单选择:
			switch (wmId)
			{
			case	WM_NOTIFY_INTERFACE_CONTROL:	//"界面管理(&W)")
				{
					CString strPort = pServiceWindow->m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));
					CString		strUrl;
					strUrl.Format(_T("http://127.0.0.1:%s"),strPort);
					ShellExecute(hWnd,_T("open"),strUrl.GetBuffer(),_T(""),_T(""),SW_SHOW);
				}
				break;
			case	WM_NOTIFY_CONTACT_US:	//"联系我们(&C)"
				{
					ShellExecute(hWnd,_T("open"),_T("http://www.mzdchina.com/"),_T(""),_T(""),SW_SHOW);
					break;
				}
			case	WM_NOTIFY_SERVICE_CONTROL:	//"服务管理(&S)"
				{
					//ThreadRefresh((PVOID)hWnd);
					WRITE_LOG(LOG_LEVEL_ERROR, _T("窗口被激活"));
					ShowWindow(pServiceWindow->m_hWnd,SW_SHOW);
					SetWindowPos(pServiceWindow->m_hWnd,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);//让这个窗口显示在最前面
					break;
				}
			case	WM_NOTIFY_EXIT:	//"退出(&E)"
				{
					HANDLE hCloseThread = CreateThread(NULL,0,CloseThread,hWnd,0,NULL);
					CloseHandle(hCloseThread);
					break;
				}
			case	WM_NOTIFY_PROCESS_CONTROL:	//"程序管理(&A)"
				{
					CString	strAppPath = CAppMain::GetAppPath();
					strAppPath += _T("MZMgrConsole.exe");
					STARTUPINFO si = { sizeof(si) };   
					PROCESS_INFORMATION pi;   
					si.dwFlags = STARTF_USESHOWWINDOW;   
					si.wShowWindow = SW_SHOW; //TRUE表示显示创建的进程的窗口  
					CreateProcess(NULL,strAppPath.GetBuffer(),NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					break;
				}
			case	WM_NOTIFY_OPENPATH:	//"打开目录(&D)"
				{
					CString	strAppPath = CAppMain::GetAppPath();
					ShellExecute(hWnd,_T("open"),strAppPath.GetBuffer(),_T(""),_T(""),SW_SHOW);
					break;
				}
			case	IDC_BUTTON1:	//启动单个服务
				{
					pServiceWindow->ButtonStart();
					break;
				}
			case	IDC_BUTTON2:	//停止单个服务
				{
					pServiceWindow->ButtonStop();
					break;
				}
			case	IDC_BUTTON3:	//重新启动服务
				{
					pServiceWindow->ButtonRestart();
					break;
				}
			case	IDC_BUTTON4:	//刷新
				{
					pServiceWindow->ButtonRefresh();
					break;
				}
			case	IDC_BUTTON5:	//全部启动
				{
					pServiceWindow->ButtonStartAll();
					break;
				}
			case	IDC_BUTTON6:	//全部停止
				{
					pServiceWindow->ButtonStopAll();
					break;
				}
			case	IDC_BUTTON7:	//关闭窗口
				{
					ShowWindow(pServiceWindow->m_hWnd,SW_HIDE);
					break;
				}
			}
		}
		break;
	case	WM_SOCKET_IN:	//socket消息到达
		{
			if (WSAGETSELECTERROR(lParam))
			{       
				closesocket(wParam);       
				break;     
			}
			switch (WSAGETSELECTEVENT(lParam))
			{
			case	FD_READ:	//读取
				{
					byte	RecvBuffer[1024] = { 0 };
					int nRecv = recvfrom(pServiceWindow->m_Socket,(char*)RecvBuffer,1024,0,NULL,NULL);//读取数据至RecvBuffer
					if (nRecv == SOCKET_ERROR)
					{
						break;
					}
					int	nFlags = *(int*)RecvBuffer;
					if (nFlags == 10)	//删除托盘并退出程序
					{
						BubbleData*	pBubble = (BubbleData*)RecvBuffer;
						pServiceWindow->m_nid.cbSize = sizeof(NOTIFYICONDATA);
						pServiceWindow->m_nid.uFlags = NIF_TIP | NIF_INFO | NIF_REALTIME;
						pServiceWindow->m_nid.dwInfoFlags = NIIF_INFO;
						lstrcpy(pServiceWindow->m_nid.szInfo,pBubble->wszMessage);
						lstrcpy(pServiceWindow->m_nid.szInfoTitle,pBubble->wszTitle);
						Shell_NotifyIcon(NIM_DELETE, &pServiceWindow->m_nid);
						ExitProcess(0);
						break;
					}
					if (nFlags == 1)	//提示气泡
					{
						BubbleData*	pBubble = (BubbleData*)RecvBuffer;
						pServiceWindow->m_nid.cbSize = sizeof(NOTIFYICONDATA);
						pServiceWindow->m_nid.uFlags = NIF_INFO;
						pServiceWindow->m_nid.uTimeout = 10 * 1000;
						pServiceWindow->m_nid.dwInfoFlags = NIIF_INFO;
						lstrcpy(pServiceWindow->m_nid.szInfo,pBubble->wszMessage);
						lstrcpy(pServiceWindow->m_nid.szInfoTitle,pBubble->wszTitle);
						Shell_NotifyIcon(NIM_MODIFY, &pServiceWindow->m_nid);
					}
				break;
				}
				break;
			}
			break;
		}
	case	WM_CLOSE:	//关闭窗口
		{
			ShowWindow(pServiceWindow->m_hWnd,SW_HIDE);
		}
		break;
	case	WM_INITDIALOG:	//初始化窗口
		{
			HWND hList = GetDlgItem(hWnd,IDC_LIST1);
			SendMessage(hList,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置选中
			pServiceWindow->InitServiceList(hWnd);	//初始化List列表

			GdiplusStartup(&pServiceWindow->m_gdiPlusToken, &pServiceWindow->m_gdiPlusInPut, NULL);
			//pServiceWindow->ButtonRefresh();
		}
		break;
	//case	WM_ERASEBKGND:
	//	{
	//		HWND hTextName = GetDlgItem(hWnd,IDC_Name);
	//		HWND hTextDescription = GetDlgItem(hWnd,IDC_Description);
	//		HWND hTextStatus = GetDlgItem(hWnd,IDC_Status);
	//		HWND hTextTitle = GetDlgItem(hWnd,IDC_Title);

	//		ShowWindow(hTextName,SW_HIDE);
	//		ShowWindow(hTextDescription,SW_HIDE);
	//		ShowWindow(hTextStatus,SW_HIDE);
	//		ShowWindow(hTextTitle,SW_HIDE);

	//		HDC	 hParentDc = (HDC)wParam;

	//		HBRUSH	hBrush = CreateSolidBrush(RGB(17,113,223));
	//		RECT	rcName, rcDescription, rcStatus;
	//		CRect rcTitle;

	//		GetWindowRect(hTextName,&rcName);
	//		GetWindowRect(hTextDescription,&rcDescription);
	//		GetWindowRect(hTextStatus,&rcStatus);
	//		GetWindowRect(hTextTitle,&rcTitle);

	//		MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcName,2);
	//		MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcDescription,2);
	//		MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcStatus,2);
	//		MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcTitle,2);

	//		Graphics mGraphics(hParentDc);
	//		HRSRC hRsrc = ::FindResource(pServiceWindow->m_hInstance, MAKEINTRESOURCE(IDJ_Title), L"JPG");
	//		if (hRsrc == NULL)
	//		{
	//			break;
	//		}
	//		DWORD dwSize = ::SizeofResource(pServiceWindow->m_hInstance, hRsrc); 
	//		if (dwSize == NULL)
	//		{
	//			break;
	//		}
	//		HGLOBAL hGlobal = ::LoadResource(pServiceWindow->m_hInstance, hRsrc); 
	//		if (hGlobal == NULL)
	//		{
	//			break;
	//		}
	//		LPVOID pBuffer = ::LockResource(hGlobal); 
	//		if (pBuffer == NULL)
	//		{
	//			break;
	//		}

	//		HGLOBAL hMem = (HGLOBAL)GlobalAlloc(GMEM_FIXED, dwSize);
	//		if (hMem == NULL)
	//		{
	//			break;
	//		}
	//		memcpy((LPVOID)hMem,pBuffer,dwSize);

	//		IStream* pStm = NULL;
	//		::CreateStreamOnHGlobal(hMem, TRUE, &pStm); 
	//		Image* pImage = Gdiplus::Image::FromStream(pStm);
	//		pStm->Release();

	//		RectF	rcTitleF(rcTitle.left,rcTitle.top, rcTitle.Width(),rcTitle.Height());
	//		mGraphics.DrawImage(pImage,rcTitleF);

	//		::FreeResource(hGlobal);
	//		GlobalFree(hMem);

	//		FillRect(hParentDc,&rcName,hBrush);
	//		FillRect(hParentDc,&rcDescription,hBrush);
	//		FillRect(hParentDc,&rcStatus,hBrush);

	//		DeleteObject(hBrush);

	//		HFONT hFont = CreateFont(-14,0,0,0,0,0,0,0,0,0,0,0,0,_T("宋体"));
	//		HGDIOBJ hGDIFont = SelectObject(hParentDc,hFont);
	//		SetTextColor(hParentDc,RGB(255,255,255));
	//		SetBkMode(hParentDc,TRANSPARENT);

	//		DrawText(hParentDc,_T("   名称"),-1,&rcName,DT_VCENTER | DT_SINGLELINE);
	//		DrawText(hParentDc,_T("   描述"),-1,&rcDescription,DT_VCENTER | DT_SINGLELINE);
	//		DrawText(hParentDc,_T("   状态"),-1,&rcStatus,DT_VCENTER | DT_SINGLELINE);

	//		SelectObject(hParentDc,hGDIFont);
	//		DeleteObject(hFont);
	//		//ReleaseDC(hWnd,hParentDc);
	//		return 1;
	//	}
	case	WM_PAINT:	//画表头
		{
			PAINTSTRUCT ps;
			HWND hTextName = GetDlgItem(hWnd,IDC_Name); //表头-名字
			HWND hTextDescription = GetDlgItem(hWnd,IDC_Description);//表头-描述
			HWND hTextStatus = GetDlgItem(hWnd,IDC_Status);//表头-状态
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
			 HRSRC hRsrc = ::FindResource(pServiceWindow->m_hInstance, MAKEINTRESOURCE(IDJ_Title), L"JPG");	//获取图片资源
			 if (hRsrc == NULL)
			 {
				 break;
			 }
			 DWORD dwSize = ::SizeofResource(pServiceWindow->m_hInstance, hRsrc); //获取资源大小
			 if (dwSize == NULL)
			 {
				 break;
			 }
			 HGLOBAL hGlobal = ::LoadResource(pServiceWindow->m_hInstance, hRsrc); //加载资源
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
			return 0;
			break;
		}
	default:
		return 0;
	}
	return 1;
}

CServiceWindow*	CServiceWindow::GetServiceWindow()
{
	if (pServiceWindow == NULL)
	{
		pServiceWindow = new CServiceWindow;
	}
	return pServiceWindow;
}

CServiceWindow::CServiceWindow()
{
	m_bIsInit = FALSE;
}

CServiceWindow::~CServiceWindow()
{
}


//创建服务管理界面
//************************************
// 方法名:	CreateServiceWindow
// 全名称:	CServiceWindow::CreateServiceWindow
// 访问级:	public 
// 返回值:	int
// 限定符:	
// 参  数:	HINSTANCE hInstance	实例句柄
// 参  数:	int nShow			是否需要显示
// 备  注:	创建管理窗口
//************************************
int		CServiceWindow::CreateServiceWindow(HINSTANCE hInstance, int nShow)
{
	m_hInstance = hInstance; 

	FQ_ShangGuanXWHandle = CreateMutex(NULL,FALSE,_T("FQ_Mz"));	//创建互斥句柄
	//if (FQ_ShangGuanXWHandle)
	//{
		if (ERROR_ALREADY_EXISTS == GetLastError())	//如果发现互斥体
		{
			WRITE_LOG(LOG_LEVEL_INFO, "程序已启动");
		
			//HWND	hFindWind = FindWindowEx(_T(""),_T("名智2013"));	//显示原程序
			HWND hFindWind = FindWindowEx(NULL, NULL, NULL, _T("名智2013"));
			if (hFindWind == NULL)
			{
				WRITE_LOG(LOG_LEVEL_FATAL,"发现互斥体,但未找到窗口句柄.程序退出!");
				ExitProcess(0);
			}
			ShowWindow(hFindWind,SW_SHOW);

			WRITE_LOG(LOG_LEVEL_ERROR, _T("窗口被再次激活"));
			ExitProcess(0);
		}
	//}

	//WNDCLASSEX wcex;

	//wcex.cbSize = sizeof(WNDCLASSEX);

	//wcex.style			= CS_HREDRAW | CS_VREDRAW;
	//wcex.lpfnWndProc	= WndProc;
	//wcex.cbClsExtra		= 0;
	//wcex.cbWndExtra		= 0;
	//wcex.hInstance		= hInstance;
	//wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	//wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	//wcex.lpszMenuName	= NULL;
	//wcex.lpszClassName	= _T("明智2013");
	//wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	//if (!RegisterClassEx(&wcex))
	//{
	//	return 0;
	//}

	//HWND   hwnd   = ::FindWindow(_T("Shell_TrayWnd"),NULL);
	//if (hwnd == NULL)
	//{
	//	return 0;
	//}
	//CRect	rc;
	//GetWindowRect(hwnd,&rc);
	//int nW = rc.right / 2 - 300;
	//int nH = rc.bottom / 2 - 250;
	//m_hWnd = CreateWindow(wcex.lpszClassName,_T("明智2013"), WS_OVERLAPPEDWINDOW, nW, nH, 800, 600, NULL, NULL, hInstance, NULL);
	//m_hWnd = CreateWindow(wcex.lpszClassName,_T("明智2013"), WS_OVERLAPPED | WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_ICONIC | WS_SYSMENU, nW, nH, 600, 500, NULL, NULL, hInstance, NULL);

	//SendMessage(m_hWnd,WM_INITWINODW,NULL,NULL);
	//CServiceWindow*	pServiceWindow = CServiceWindow::GetServiceWindow();

	m_hWnd = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),NULL,WndProc);	//创建窗体
	if (NULL == m_hWnd)
	{
		//TODO: 是否通知用户
		WRITE_LOG(LOG_LEVEL_FATAL, "The function CreateDialog is faild , ErrorCode : %x\r\n", GetLastError());
		ExitProcess(0);
	}
	//SendMessage(m_hWnd,WM_INITWINODW,NULL,NULL);
	if (nShow)	//如果需要显示
	{
		WRITE_LOG(LOG_LEVEL_ERROR, _T("窗口第一次被激活"));
		ShowWindow(m_hWnd,SW_SHOW);
	}
	//UpdateWindow (m_hWnd);

	TCHAR	wszBrandsName[MAXBYTE] = { 0 };
	LoadString(NULL,IDS_BrandsName,wszBrandsName,MAXBYTE);
	memset(&m_nid,0,sizeof(NOTIFYICONDATA));	//托盘图标结构
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_REALTIME;
	m_nid.dwInfoFlags = NIIF_INFO;
	m_nid.uCallbackMessage = PopupMenu;//自定义的消息名称
	m_nid.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_MiniIcon));
	lstrcpy(m_nid.szTip,wszBrandsName);//信息提示条为“名智2013”
	//在托盘区添加图标
	if (!Shell_NotifyIcon(NIM_ADD,&m_nid))	//添加托盘图标
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Shell_NotifyIcon失败！错误代码 %d",GetLastError());
	}

	

	TCHAR	lpwzsBuffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,lpwzsBuffer,MAX_PATH);
	CString	strPath(lpwzsBuffer);
	int nPos = strPath.ReverseFind('\\');
	CString	strIniPath;
	strIniPath = strPath.Left(nPos + 1);
	strIniPath += _T("httpsvc.Ini");
	m_IniFile.SetPath(strIniPath);

	WSADATA       wsd;
	SOCKADDR_IN   local = { 0 };
	WSAStartup(MAKEWORD(2, 2), &wsd);
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == SOCKET_ERROR)
	{
		MessageBox(m_hWnd,_T("socket 失败"),NULL,0);
		ExitProcess(0);
	}

	CString	strPort = m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));//管理界面的UDP端口
	int nPort = _ttoi(strPort);

	TCHAR	wszPortBuffer[512] = { 0 };
	int nErrorUdp = GetProcessNameFromPort(1,nPort,wszPortBuffer,sizeof(wszPortBuffer)/sizeof(TCHAR));	//检查端口是否被占用
	if (nErrorUdp != NULL)
	{
		TCHAR	wszErrorMessage[256] = { 0 };
		wsprintf(wszErrorMessage, _T("名智界面管理服务使用的UDP端口 %u 已被“%s”占用！\r\n\r\n请暂时关闭该程序。"), nPort, wszPortBuffer);
		MessageBox(m_hWnd,wszErrorMessage, _T("温馨提示"), MB_OK);
		ExitProcess(0);
	}


	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   
	local.sin_family = AF_INET;  
	local.sin_port = htons(nPort);   
	if (bind(m_Socket, (struct sockaddr*)&local,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		ExitProcess(0);
	}

	WSAAsyncSelect(m_Socket,m_hWnd,WM_SOCKET_IN,FD_READ);	//异步模式

	g_MsgTaskbarRestart = RegisterWindowMessage(_T("TaskbarCreated"));	//注册新消息TaskbarCreated
	if (!g_MsgTaskbarRestart)
	{	
		//注册新消息失败
		WRITE_LOG(LOG_LEVEL_ERROR,"RegisterWindowMessage 失败！");
		ExitProcess(0);
	}

	WRITE_LOG(LOG_LEVEL_FATAL, "初始化完成进入消息循环!");
	MSG	msg;
	while (GetMessage (&msg, NULL, 0, 0)) 
	{  
		//WRITE_LOG(LOG_LEVEL_INFO, "接收到消息:%d", msg.message);
		TranslateMessage (&msg); 
		DispatchMessage (&msg);    
		//WRITE_LOG(LOG_LEVEL_INFO, "消息:%d处理完成", msg.message);
	} 
	return msg.wParam;
}
//初始化列表
int		CServiceWindow::InitServiceList(HWND	hWndParent)
{
	if (m_bIsInit)
	{
		return 0;
	}

	LV_COLUMN lvc = { 0 };
	LV_ITEM lvi = { 0 }; 
	HWND hList = GetDlgItem(hWndParent,IDC_LIST1);

	HWND hTextName = GetDlgItem(hWndParent,IDC_Name);
	HWND hTextDescription = GetDlgItem(hWndParent,IDC_Description);
	HWND hTextStatus = GetDlgItem(hWndParent,IDC_Status);

	CRect	rcName, rcDescription, rcStatus;

	GetWindowRect(hTextName,&rcName);
	GetWindowRect(hTextDescription,&rcDescription);
	GetWindowRect(hTextStatus,&rcStatus);

	lvc.mask = LVIF_TEXT | LVCF_WIDTH;    
	lvc.cx = rcName.Width();
	SendMessage(hList, LVM_INSERTCOLUMN, 0, (long)&lvc); 
	lvc.cx = rcDescription.Width() - 22;
	SendMessage(hList, LVM_INSERTCOLUMN, 1, (long)&lvc);
	lvc.cx = rcStatus.Width();
	SendMessage(hList, LVM_INSERTCOLUMN, 2, (long)&lvc);

	TCHAR	wszAppPath[MAX_PATH] = { 0 };
	int nApplen = GetModuleFileName(NULL,wszAppPath,MAX_PATH);
	for (int i = nApplen; i >= 0; i--)
	{
		if (wszAppPath[i] == '\\')
		{
			break;
		}
		else
		{
			wszAppPath[i] = 0;
		}
	}
	TCHAR	wszBuffer[MAX_PATH] = { 0 };
	lstrcpy(wszBuffer,wszAppPath);

	HIMAGELIST  hImageList = ImageList_Create(32, 32, ILC_COLOR16 | ILC_MASK, 0, 0);
	ListView_SetImageList(hList,hImageList,LVSIL_SMALL);
	HICON  hIcon = NULL;
	hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_ICON));
	ImageList_AddIcon(hImageList,hIcon);
	DeleteObject(hIcon);

	SHFILEINFO	hFileInfo;

	lstrcat(wszBuffer,_T("MZDIO.exe"));
	SHGetFileInfo(wszBuffer,0,&hFileInfo,sizeof(SHFILEINFO),SHGFI_ICON);
	ImageList_AddIcon(hImageList,hFileInfo.hIcon);
	DestroyIcon(hFileInfo.hIcon);

	memset(wszBuffer,0,sizeof(TCHAR) * MAX_PATH);
	lstrcpy(wszBuffer,wszAppPath);
	lstrcat(wszBuffer,_T("toolsvc.exe"));
	SHGetFileInfo(wszBuffer,0,&hFileInfo,sizeof(SHFILEINFO),SHGFI_ICON);
	ImageList_AddIcon(hImageList,hFileInfo.hIcon);
	DestroyIcon(hFileInfo.hIcon);

	memset(wszBuffer,0,sizeof(TCHAR) * MAX_PATH);
	lstrcpy(wszBuffer,wszAppPath);
	lstrcat(wszBuffer,_T("btsvc.exe"));
	SHGetFileInfo(wszBuffer,0,&hFileInfo,sizeof(SHFILEINFO),SHGFI_ICON);
	ImageList_AddIcon(hImageList,hFileInfo.hIcon);
	DestroyIcon(hFileInfo.hIcon);

	int	nItem = 0;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;

	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_HTTPSVC");
	nItem = SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 1;
	lvi.pszText = _T("斯普林名智界面管理服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);


	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_MZDIO");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 2;
	lvi.pszText = _T("斯普林名智磁盘服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_TOOLSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 3;
	lvi.pszText = _T("斯普林名智辅助工具服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_BTSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 4;
	lvi.pszText = _T("斯普林完美下载服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm == NULL)
	{
		return -1;
	}
	SC_HANDLE hService = NULL;
	SERVICE_STATUS stStatus;

	hService = OpenService(hScm, _T("SPL_HTTPSVC"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 0;
		lvi.pszText = _T("没有安装");
		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	}
	else
	{
		memset(&stStatus, 0, sizeof(stStatus));
		QueryServiceStatus(hService, &stStatus);
		if(stStatus.dwCurrentState == SERVICE_STOPPED)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 0;
			lvi.pszText = _T("已停止");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 0;
			lvi.pszText = _T("正在运行");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);

	hService = OpenService(hScm, _T("SPL_TOOLSVC"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 2;
		lvi.pszText = _T("没有安装");
		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	}
	else
	{
		memset(&stStatus, 0, sizeof(stStatus));
		QueryServiceStatus(hService, &stStatus);
		if(stStatus.dwCurrentState == SERVICE_STOPPED)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 2;
			lvi.pszText = _T("已停止");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 2;
			lvi.pszText = _T("正在运行");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);

	hService = OpenService(hScm, _T("SPL_BTSVC"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 3;
		lvi.pszText = _T("没有安装");
		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	}
	else
	{
		memset(&stStatus, 0, sizeof(stStatus));
		QueryServiceStatus(hService, &stStatus);
		if(stStatus.dwCurrentState == SERVICE_STOPPED)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 3;
			lvi.pszText = _T("已停止");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 3;
			lvi.pszText = _T("正在运行");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);

	hService = OpenService(hScm, _T("SPL_MZDIO"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 1;
		lvi.pszText = _T("没有安装");
		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	}
	else
	{
		memset(&stStatus, 0, sizeof(stStatus));
		QueryServiceStatus(hService, &stStatus);
		if(stStatus.dwCurrentState == SERVICE_STOPPED)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 1;
			lvi.pszText = _T("已停止");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 1;
			lvi.pszText = _T("正在运行");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);
	CloseServiceHandle(hScm);
	m_bIsInit = TRUE;
	//ButtonRefresh();
	return 0;
}
//启动服务
DWORD	WINAPI	ThreadStart(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	LV_ITEM lvi = { 0 };
	int nItem = SendMessage(hList,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(hWnd,_T("请选择服务！"),_T("名智2013"),0);
		goto End;
	}
	TCHAR	lpwzsItemData[64] = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.cchTextMax = 64;
	lvi.pszText = lpwzsItemData;
	SendMessage(hList,LVM_GETITEM,0,(long)&lvi);

	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm == NULL)
	{
		goto End;
	}
	SC_HANDLE hService = NULL;
	SERVICE_STATUS stStatus;

	hService = OpenService(hScm, lpwzsItemData, SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 没有安装，请重新安装。"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hScm);
		goto End;
	}
	memset(&stStatus, 0, sizeof(stStatus));
	QueryServiceStatus(hService, &stStatus);
	if (stStatus.dwCurrentState == SERVICE_RUNNING)
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 正在运行"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else if (stStatus.dwCurrentState == SERVICE_STOPPED)
	{
		int nRet = StartService(hService, 0, 0);
		if (nRet == 1)
		{
			lvi.pszText = _T("正在运行");
			lvi.iSubItem = 2;
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		else
		{
			TCHAR	wszMessageBuffer[128] = { 0 };
			wsprintf(wszMessageBuffer,_T("%s 启动失败"),lpwzsItemData);
			MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		}
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 状态无法识别"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
	}
End:
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON1);
	EnableWindow(hButton,TRUE);
	return 0;
}

VOID	CServiceWindow::ButtonStart()
{
	HWND hButton = GetDlgItem(m_hWnd,IDC_BUTTON1);
	EnableWindow(hButton,FALSE);

	HANDLE	hThread = CreateThread(NULL,0,ThreadStart,(LPVOID)m_hWnd,0,NULL);
	if (hThread != NULL)
	{
		CloseHandle(hThread);
	}
}
//单个安装
DWORD	WINAPI	ThreadStop(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	LV_ITEM lvi = { 0 };
	int nItem = SendMessage(hList,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(hWnd,_T("请选择服务！"),_T("名智2013"),0);
		goto End;
	}
	TCHAR	lpwzsItemData[64] = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.cchTextMax = 64;
	lvi.pszText = lpwzsItemData;
	SendMessage(hList,LVM_GETITEM,0,(long)&lvi);

	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm == NULL)
	{
		goto End;
	}
	SC_HANDLE hService = NULL;
	SERVICE_STATUS stStatus;

	hService = OpenService(hScm, lpwzsItemData, SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 没有安装，请重新安装。"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hScm);
		goto End;
	}
	memset(&stStatus, 0, sizeof(stStatus));
	QueryServiceStatus(hService, &stStatus);
	if (stStatus.dwCurrentState == SERVICE_RUNNING)
	{
		ControlService(hService, SERVICE_CONTROL_STOP, &stStatus);

		for (int i = 0; i < 1000; i++)
		{
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState == SERVICE_STOPPED)
			{
				lvi.pszText = _T("已停止");
				lvi.iSubItem = 2;
				SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
				break;
			}
			Sleep(50);
		}
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else if (stStatus.dwCurrentState == SERVICE_STOPPED)
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 已经停止"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 状态无法识别"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
	}
End:
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON2);
	EnableWindow(hButton,TRUE);
	return 0;
}

VOID	CServiceWindow::ButtonStop()
{
	HWND hButton = GetDlgItem(m_hWnd,IDC_BUTTON2);
	EnableWindow(hButton,FALSE);

	HANDLE	hThread = CreateThread(NULL,0,ThreadStop,(LPVOID)m_hWnd,0,NULL);
	if (hThread != NULL)
	{
		CloseHandle(hThread);
	}
}
//单个开启
DWORD	WINAPI	ThreadRestart(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	LV_ITEM lvi = { 0 };
	int nItem = SendMessage(hList,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(hWnd,_T("请选择服务！"),_T("名智2013"),0);
		goto End;
	}
	TCHAR	lpwzsItemData[64] = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.iItem = nItem;
	lvi.cchTextMax = 64;
	lvi.pszText = lpwzsItemData;
	SendMessage(hList,LVM_GETITEM,0,(long)&lvi);

	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm == NULL)
	{
		goto End;
	}
	SC_HANDLE hService = NULL;
	SERVICE_STATUS stStatus;

	hService = OpenService(hScm, lpwzsItemData, SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 没有安装，请重新安装。"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hScm);
		goto End;
	}
	memset(&stStatus, 0, sizeof(stStatus));
	QueryServiceStatus(hService, &stStatus);
	if (stStatus.dwCurrentState == SERVICE_RUNNING)
	{
		ControlService(hService, SERVICE_CONTROL_STOP, &stStatus);

		for (int i = 0; i < 1000; i++)
		{
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState == SERVICE_STOPPED)
			{
				int nRet = StartService(hService, 0, 0);
				if (nRet == 1)
				{
					lvi.pszText = _T("正在运行");
					lvi.iSubItem = 2;
					SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
				}
				else
				{
					TCHAR	wszMessageBuffer[128] = { 0 };
					wsprintf(wszMessageBuffer,_T("%s 启动失败"),lpwzsItemData);
					MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
				}
				break;
			}
			Sleep(60);
		}
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else if (stStatus.dwCurrentState == SERVICE_STOPPED)
	{
		memset(&stStatus, 0, sizeof(stStatus));
		QueryServiceStatus(hService, &stStatus);
		if (stStatus.dwCurrentState == SERVICE_STOPPED)
		{
			int nRet = StartService(hService, 0, 0);
			if (nRet == 1)
			{
				lvi.pszText = _T("正在运行");
				lvi.iSubItem = 2;
				SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
			}
			else
			{
				TCHAR	wszMessageBuffer[128] = { 0 };
				wsprintf(wszMessageBuffer,_T("%s 启动失败"),lpwzsItemData);
				MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
			}
		}
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s 状态无法识别"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("名智2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
	}
End:
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON3);
	EnableWindow(hButton,TRUE);

	return 0;
}

VOID	CServiceWindow::ButtonRestart()
{
	HWND hButton = GetDlgItem(m_hWnd,IDC_BUTTON3);
	EnableWindow(hButton,FALSE);

	HANDLE	hThread = CreateThread(NULL,0,ThreadRestart,(LPVOID)m_hWnd,0,NULL);
	CloseHandle(hThread);
}
//刷新服务状态
DWORD	WINAPI	ThreadRefresh(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	SendMessage(hList,LVM_DELETEALLITEMS,0,0);

	LV_ITEM lvi = { 0 }; 

	int	nItem = 0;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE;

	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_HTTPSVC");
	nItem = SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 1;
	lvi.pszText = _T("斯普林名智界面管理服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_MZDIO");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 2;
	lvi.pszText = _T("斯普林名智磁盘服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_TOOLSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 3;
	lvi.pszText = _T("斯普林名智辅助工具服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_BTSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 4;
	lvi.pszText = _T("斯普林完美下载服务");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	//SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);	//打开SCM管理器
	//if (hScm == NULL)
	//{
	//	goto End;
	//}
	//SC_HANDLE hService = NULL;
	//SERVICE_STATUS stStatus;

	//hService = OpenService(hScm, _T("SPL_HTTPSVC"), SERVICE_ALL_ACCESS);
	//if (hService == NULL)
	//{
	//	lvi.iSubItem = 2;
	//	lvi.iItem = 0;
	//	lvi.iImage = 1;
	//	lvi.pszText = _T("没有安装");
	//	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//}
	//else
	//{
	//	memset(&stStatus, 0, sizeof(stStatus));
	//	QueryServiceStatus(hService, &stStatus);
	//	if(stStatus.dwCurrentState == SERVICE_STOPPED)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 0;
	//		lvi.iImage = 1;
	//		lvi.pszText = _T("已停止");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 0;
	//		lvi.iImage = 1;
	//		lvi.pszText = _T("正在运行");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//}
	//CloseServiceHandle(hService);
	
	CControlServiceEx se;
	lvi.iSubItem = 2;
	lvi.iItem = 0;
	lvi.iImage = 1;
	//lvi.pszText =(LPWSTR)(LPCTSTR) se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_HTTPSVC")));
	CString temp = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_HTTPSVC")));
	lvi.pszText = temp.GetBuffer();
	temp.ReleaseBuffer();
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	//hService = OpenService(hScm, _T("SPL_MZDIO"), SERVICE_ALL_ACCESS);
	//if (hService == NULL)
	//{
	//	lvi.iSubItem = 2;
	//	lvi.iItem = 1;
	//	lvi.iImage = 2;
	//	lvi.pszText = _T("没有安装");
	//	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//}
	//else
	//{
	//	memset(&stStatus, 0, sizeof(stStatus));
	//	QueryServiceStatus(hService, &stStatus);
	//	if(stStatus.dwCurrentState == SERVICE_STOPPED)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 1;
	//		lvi.iImage = 2;
	//		lvi.pszText = _T("已停止");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 1;
	//		lvi.iImage = 2;
	//		lvi.pszText = _T("正在运行");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//}
	//CloseServiceHandle(hService);
	lvi.iSubItem = 2;
	lvi.iItem = 1;
	lvi.iImage = 2;
	temp = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_MZDIO")));
	lvi.pszText = temp.GetBuffer();
	temp.ReleaseBuffer();
	//lvi.pszText = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_MZDIO"))).GetBuffer();
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	//hService = OpenService(hScm, _T("SPL_TOOLSVC"), SERVICE_ALL_ACCESS);
	//if (hService == NULL)
	//{
	//	lvi.iSubItem = 2;
	//	lvi.iItem = 2;
	//	lvi.iImage = 3;
	//	lvi.pszText = _T("没有安装");
	//	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//}
	//else
	//{
	//	memset(&stStatus, 0, sizeof(stStatus));
	//	QueryServiceStatus(hService, &stStatus);
	//	if(stStatus.dwCurrentState == SERVICE_STOPPED)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 2;
	//		lvi.iImage = 3;
	//		lvi.pszText = _T("已停止");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 2;
	//		lvi.iImage = 3;
	//		lvi.pszText = _T("正在运行");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//}
	//CloseServiceHandle(hService);
	lvi.iSubItem = 2;
	lvi.iItem = 2;
	lvi.iImage = 3;
	temp = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_TOOLSVC")));
	lvi.pszText = temp.GetBuffer();
	temp.ReleaseBuffer();
	//lvi.pszText = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_TOOLSVC"))).GetBuffer();
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	
	lvi.iSubItem = 2;
	lvi.iItem = 3;
	lvi.iImage = 4;
	temp = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_BTSVC")));
	lvi.pszText = temp.GetBuffer();
	temp.ReleaseBuffer();
	//lvi.pszText = se.ServiceStatusToCString(se.GetServiceStatus( _T("SPL_BTSVC"))).GetBuffer();
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);



	//hService = OpenService(hScm, _T("SPL_TOOLSVC"), SERVICE_ALL_ACCESS);
	//if (hService == NULL)
	//{
	//	lvi.iSubItem = 2;
	//	lvi.iItem = 2;
	//	lvi.iImage = 3;
	//	lvi.pszText = _T("没有安装");
	//	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//}
	//else
	//{
	//	memset(&stStatus, 0, sizeof(stStatus));
	//	QueryServiceStatus(hService, &stStatus);
	//	if(stStatus.dwCurrentState == SERVICE_STOPPED)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 2;
	//		lvi.iImage = 3;
	//		lvi.pszText = _T("已停止");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 2;
	//		lvi.iImage = 3;
	//		lvi.pszText = _T("正在运行");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//}
	//CloseServiceHandle(hService);

	//hService = OpenService(hScm, _T("SPL_BTSVC"), SERVICE_ALL_ACCESS);
	//if (hService == NULL)
	//{
	//	lvi.iSubItem = 2;
	//	lvi.iItem = 3;
	//	lvi.iImage = 4;
	//	lvi.pszText = _T("没有安装");
	//	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//}
	//else
	//{
	//	memset(&stStatus, 0, sizeof(stStatus));
	//	QueryServiceStatus(hService, &stStatus);
	//	if(stStatus.dwCurrentState == SERVICE_STOPPED)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 3;
	//		lvi.iImage = 4;
	//		lvi.pszText = _T("已停止");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 3;
	//		lvi.iImage = 4;
	//		lvi.pszText = _T("正在运行");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//}
	//CloseServiceHandle(hService);
	//CloseServiceHandle(hScm);
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON4);	
	EnableWindow(hButton,TRUE);	//启用使用刷新按钮
	return 0;
}
//刷新按钮
VOID	CServiceWindow::ButtonRefresh()
{
	HWND hButton = GetDlgItem(m_hWnd,IDC_BUTTON4);
	EnableWindow(hButton,FALSE);

	HANDLE	hThread = CreateThread(NULL,0,ThreadRefresh,(LPVOID)m_hWnd,0,NULL);
	if (hThread != NULL)
	{
		CloseHandle(hThread);
	}
}
//启动所有服务
DWORD	WINAPI	ThreadStartAll(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);
	LV_ITEM	lvi = { 0 };

	int nItemCount = SendMessage(hList,LVM_GETITEMCOUNT,0,0);
	if (nItemCount <= 0)
	{
		goto End;
	}

	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm == NULL)
	{
		goto End;
	}

	TCHAR	lpwzsItemData[64] = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 64;
	lvi.pszText = lpwzsItemData;

	for (int i = 0; i < nItemCount; i++)
	{
		lvi.iItem = i;
		memset(lpwzsItemData,0,sizeof(TCHAR) * 64);
		SendMessage(hList,LVM_GETITEM,0,(long)&lvi);

		SC_HANDLE	hService = OpenService(hScm,lpwzsItemData,SERVICE_ALL_ACCESS);
		if (hService == NULL)
		{
			TCHAR	wszMessage[64] = { 0 };
			wsprintf(wszMessage,_T("%s 服务没有安装或者错误。"),lpwzsItemData);
			MessageBox(hWnd,wszMessage,_T("名智2013"),0);
			continue;
		}
		SERVICE_STATUS stStatus = { 0 };
		QueryServiceStatus(hService,&stStatus);
		if (stStatus.dwCurrentState == SERVICE_STOPPED)
		{
			int nRet = StartService(hService,0,0);
			if (nRet)
			{
				LV_ITEM	LvSub = { 0 };
				LvSub.mask = LVIF_TEXT;
				LvSub.iItem = i;
				LvSub.iSubItem = 2;
				LvSub.pszText = _T("正在运行");
				SendMessage(hList,LVM_SETITEM,0,(long)&LvSub);
			}
		}
		CloseServiceHandle(hService);
	}
	CloseServiceHandle(hScm);
End:
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON5);
	EnableWindow(hButton,TRUE);
	return 0;
}

VOID	CServiceWindow::ButtonStartAll()
{
	HWND hButton = GetDlgItem(m_hWnd,IDC_BUTTON5);
	EnableWindow(hButton,FALSE);

	HANDLE	hThread = CreateThread(NULL,0,ThreadStartAll,(LPVOID)m_hWnd,0,NULL);
	if (hThread != NULL)
	{
		CloseHandle(hThread);
	}
}
//关闭所有
DWORD	WINAPI	ThreadStopAll(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);
	LV_ITEM	lvi = { 0 };

	int nItemCount = SendMessage(hList,LVM_GETITEMCOUNT,0,0);
	if (nItemCount <= 0)
	{
		goto End;
	}

	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm == NULL)
	{
		goto End;
	}

	TCHAR	lpwzsItemData[64] = { 0 };
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = 64;
	lvi.pszText = lpwzsItemData;

	for (int i = 0; i < nItemCount; i++)
	{
		lvi.iItem = i;
		memset(lpwzsItemData,0,sizeof(TCHAR) * 64);
		SendMessage(hList,LVM_GETITEM,0,(long)&lvi);

		WRITE_LOG(LOG_LEVEL_FATAL, _T("开始停止服务: %s"), lpwzsItemData);
		SC_HANDLE	hService = OpenService(hScm,lpwzsItemData,SERVICE_ALL_ACCESS);
		if (hService == NULL)
		{
			DWORD err = GetLastError();
			TCHAR	wszMessage[64] = { 0 };
			switch(err)
			{
			case ERROR_INVALID_NAME:
				wsprintf(wszMessage,_T("%s 服务名错误。"),lpwzsItemData);
				MessageBox(hWnd,wszMessage,_T("名智2013"),0);
				break;
			case ERROR_SERVICE_DOES_NOT_EXIST:
				wsprintf(wszMessage,_T("%s 服务未安装"),lpwzsItemData);
				MessageBox(hWnd,wszMessage,_T("名智2013"),0);
				break;
			default:
				i--;
				break;
			}
			continue;
		}
		SERVICE_STATUS stStatus = { 0 };
		QueryServiceStatus(hService,&stStatus);
		if (stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			ControlService(hService, SERVICE_CONTROL_STOP, &stStatus);
			for (int ii = 0; ii < 1000; ii++)
			{
				memset(&stStatus, 0, sizeof(stStatus));
				QueryServiceStatus(hService, &stStatus);
				if (stStatus.dwCurrentState == SERVICE_STOPPED)
				{
					LV_ITEM	LvSub = { 0 };
					LvSub.mask = LVIF_TEXT;
					LvSub.iItem = i;
					LvSub.iSubItem = 2;
					LvSub.pszText = _T("已停止");
					SendMessage(hList,LVM_SETITEM,0,(long)&LvSub);
					break;
				}
				Sleep(60);
			}
		}
		else
		{
			WRITE_LOG(LOG_LEVEL_FATAL, _T("停止服务: %s 时发现服务未运行"), lpwzsItemData);
		}
		CloseServiceHandle(hService);
	}
	CloseServiceHandle(hScm);

End:
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON6);
	EnableWindow(hButton,TRUE);
	return 0;
}

VOID	CServiceWindow::ButtonStopAll()
{
	HWND hButton = GetDlgItem(m_hWnd,IDC_BUTTON6);
	EnableWindow(hButton,FALSE);

	HANDLE	hThread = CreateThread(NULL,0,ThreadStopAll,(LPVOID)m_hWnd,0,NULL);
	if (hThread != NULL)
	{
		CloseHandle(hThread);
	}
}