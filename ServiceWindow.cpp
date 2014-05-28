// ServiceWindow.cpp : ʵ���ļ�
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
#define WM_NOTIFY_OPENPATH WM_USER+106 //,_T("��Ŀ¼(&D)"));
#define WM_NOTIFY_CONTACT_US WM_USER+102//,_T("��ϵ����(&C)"));
#define WM_NOTIFY_SERVICE_CONTROL WM_USER+103//,_T("�������(&S)"));
#define WM_NOTIFY_PROCESS_CONTROL WM_USER+105//,_T("�������(&A)"));
#define WM_NOTIFY_INTERFACE_CONTROL WM_USER+101//,_T("�������(&W)"));
#define WM_NOTIFY_EXIT WM_USER+104 //,_T("�˳�(&E)"));


CServiceWindow*	pServiceWindow = NULL;
int				g_CloseFlags = 0;	//�رձ�ʶ
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


// ȡ��ռ����ָ���˿ڵĽ����ļ���------���󶨶˿�ʧ��ʱʹ�ã���ʾ�û��˿��ѱ��ĸ�����ռ��
// dwType     = 0ΪTCP,1ΪUDP
// wdPort     = �˿�
// pszFile    = ����Ľ����ļ���
// dwFileSize = pszFile��С
// ����ֵ0=ʧ�ܣ���0=�ɹ�
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
	lstrcpy(pServiceWindow->m_nid.szInfo,_T("�������ڹر���,���Ժ�..."));
	lstrcpy(pServiceWindow->m_nid.szInfoTitle,_T("����2013"));
	Shell_NotifyIcon(NIM_MODIFY, &pServiceWindow->m_nid);

	//ThreadStopAll((LPVOID)MainhWnd);

	pServiceWindow->m_nid.cbSize = sizeof(NOTIFYICONDATA);
	pServiceWindow->m_nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_REALTIME;
	Shell_NotifyIcon(NIM_DELETE, &pServiceWindow->m_nid);

	ExitProcess(0);

	return 0;
}


//************************************
// ������:	WndProc
// ȫ����:	WndProc
// ���ʼ�:	public 
// ����ֵ:	INT_PTR CALLBACK
// �޶���:	
// ��  ��:	HWND hWnd
// ��  ��:	UINT message
// ��  ��:	WPARAM wParam
// ��  ��:	LPARAM lParam
// ��  ע:	���ڹ���
//************************************
INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CServiceWindow*	pServiceWindow = CServiceWindow::GetServiceWindow();
	//��ֹ���򱻵��������򼤻���ʾ
	if ( message == WM_WINDOWPOSCHANGING && InSendMessage() )
	{
		WINDOWPOS * pWps = (WINDOWPOS *)lParam; 
		if (pWps->flags & SWP_SHOWWINDOW) 
		{
			pWps->flags = pWps->flags & ~SWP_SHOWWINDOW;
		}
	}
	if (message == g_MsgTaskbarRestart)	//�����Ϣ���Լ�ע���TaskbarCreated
	{
		TCHAR	wszBrandsName[MAXBYTE] = { 0 };
		LoadString(NULL,IDS_BrandsName,wszBrandsName,MAXBYTE);
		memset(&pServiceWindow->m_nid,0,sizeof(NOTIFYICONDATA));
		pServiceWindow->m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
		pServiceWindow->m_nid.hWnd = hWnd;
		pServiceWindow->m_nid.uID = 1;
		pServiceWindow->m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_REALTIME;
		pServiceWindow->m_nid.dwInfoFlags = NIIF_INFO;
		pServiceWindow->m_nid.uCallbackMessage = PopupMenu;//�Զ������Ϣ����
		pServiceWindow->m_nid.hIcon = LoadIcon(pServiceWindow->m_hInstance,MAKEINTRESOURCE(IDI_MiniIcon));
		lstrcpy(pServiceWindow->m_nid.szTip,wszBrandsName);//��Ϣ��ʾ��Ϊ���ƻ��������ѡ�
		//�����������ͼ��
		if (!Shell_NotifyIcon(NIM_ADD,&pServiceWindow->m_nid))
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"Shell_NotifyIconʧ�ܣ�������� %d",GetLastError());
		}
		return 0;
	}

	switch (message)
	{
	case	PopupMenu:		//�Զ�����Ϣ����	1326
		{
			if (wParam == 1)
			{
				switch (lParam)
				{
				case	WM_RBUTTONUP:
					{
						if (!g_CloseFlags)	//��鴰���Ƿ񱻹ر�
						{
							LPPOINT lpoint = new tagPOINT;
							::GetCursorPos(lpoint);//�õ����λ��
							pServiceWindow->m_hMenu = CreatePopupMenu();
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_OPENPATH,_T("��Ŀ¼(&D)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_CONTACT_US,_T("��ϵ����(&C)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_SERVICE_CONTROL,_T("�������(&S)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_PROCESS_CONTROL,_T("�������(&A)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_INTERFACE_CONTROL,_T("�������(&W)"));
							AppendMenu(pServiceWindow->m_hMenu,MF_STRING,WM_NOTIFY_EXIT,_T("�˳�(&E)"));
							::SetForegroundWindow(pServiceWindow->m_hWnd);
							TrackPopupMenu(pServiceWindow->m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y, 0, hWnd, NULL);
							delete	lpoint;
						}
					}
					break;
				case	WM_LBUTTONDBLCLK://˫������Ĵ���
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
			// �����˵�ѡ��:
			switch (wmId)
			{
			case	WM_NOTIFY_INTERFACE_CONTROL:	//"�������(&W)")
				{
					CString strPort = pServiceWindow->m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));
					CString		strUrl;
					strUrl.Format(_T("http://127.0.0.1:%s"),strPort);
					ShellExecute(hWnd,_T("open"),strUrl.GetBuffer(),_T(""),_T(""),SW_SHOW);
				}
				break;
			case	WM_NOTIFY_CONTACT_US:	//"��ϵ����(&C)"
				{
					ShellExecute(hWnd,_T("open"),_T("http://www.mzdchina.com/"),_T(""),_T(""),SW_SHOW);
					break;
				}
			case	WM_NOTIFY_SERVICE_CONTROL:	//"�������(&S)"
				{
					//ThreadRefresh((PVOID)hWnd);
					WRITE_LOG(LOG_LEVEL_ERROR, _T("���ڱ�����"));
					ShowWindow(pServiceWindow->m_hWnd,SW_SHOW);
					SetWindowPos(pServiceWindow->m_hWnd,HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);//�����������ʾ����ǰ��
					break;
				}
			case	WM_NOTIFY_EXIT:	//"�˳�(&E)"
				{
					HANDLE hCloseThread = CreateThread(NULL,0,CloseThread,hWnd,0,NULL);
					CloseHandle(hCloseThread);
					break;
				}
			case	WM_NOTIFY_PROCESS_CONTROL:	//"�������(&A)"
				{
					CString	strAppPath = CAppMain::GetAppPath();
					strAppPath += _T("MZMgrConsole.exe");
					STARTUPINFO si = { sizeof(si) };   
					PROCESS_INFORMATION pi;   
					si.dwFlags = STARTF_USESHOWWINDOW;   
					si.wShowWindow = SW_SHOW; //TRUE��ʾ��ʾ�����Ľ��̵Ĵ���  
					CreateProcess(NULL,strAppPath.GetBuffer(),NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					break;
				}
			case	WM_NOTIFY_OPENPATH:	//"��Ŀ¼(&D)"
				{
					CString	strAppPath = CAppMain::GetAppPath();
					ShellExecute(hWnd,_T("open"),strAppPath.GetBuffer(),_T(""),_T(""),SW_SHOW);
					break;
				}
			case	IDC_BUTTON1:	//������������
				{
					pServiceWindow->ButtonStart();
					break;
				}
			case	IDC_BUTTON2:	//ֹͣ��������
				{
					pServiceWindow->ButtonStop();
					break;
				}
			case	IDC_BUTTON3:	//������������
				{
					pServiceWindow->ButtonRestart();
					break;
				}
			case	IDC_BUTTON4:	//ˢ��
				{
					pServiceWindow->ButtonRefresh();
					break;
				}
			case	IDC_BUTTON5:	//ȫ������
				{
					pServiceWindow->ButtonStartAll();
					break;
				}
			case	IDC_BUTTON6:	//ȫ��ֹͣ
				{
					pServiceWindow->ButtonStopAll();
					break;
				}
			case	IDC_BUTTON7:	//�رմ���
				{
					ShowWindow(pServiceWindow->m_hWnd,SW_HIDE);
					break;
				}
			}
		}
		break;
	case	WM_SOCKET_IN:	//socket��Ϣ����
		{
			if (WSAGETSELECTERROR(lParam))
			{       
				closesocket(wParam);       
				break;     
			}
			switch (WSAGETSELECTEVENT(lParam))
			{
			case	FD_READ:	//��ȡ
				{
					byte	RecvBuffer[1024] = { 0 };
					int nRecv = recvfrom(pServiceWindow->m_Socket,(char*)RecvBuffer,1024,0,NULL,NULL);//��ȡ������RecvBuffer
					if (nRecv == SOCKET_ERROR)
					{
						break;
					}
					int	nFlags = *(int*)RecvBuffer;
					if (nFlags == 10)	//ɾ�����̲��˳�����
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
					if (nFlags == 1)	//��ʾ����
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
	case	WM_CLOSE:	//�رմ���
		{
			ShowWindow(pServiceWindow->m_hWnd,SW_HIDE);
		}
		break;
	case	WM_INITDIALOG:	//��ʼ������
		{
			HWND hList = GetDlgItem(hWnd,IDC_LIST1);
			SendMessage(hList,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//����ѡ��
			pServiceWindow->InitServiceList(hWnd);	//��ʼ��List�б�

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

	//		HFONT hFont = CreateFont(-14,0,0,0,0,0,0,0,0,0,0,0,0,_T("����"));
	//		HGDIOBJ hGDIFont = SelectObject(hParentDc,hFont);
	//		SetTextColor(hParentDc,RGB(255,255,255));
	//		SetBkMode(hParentDc,TRANSPARENT);

	//		DrawText(hParentDc,_T("   ����"),-1,&rcName,DT_VCENTER | DT_SINGLELINE);
	//		DrawText(hParentDc,_T("   ����"),-1,&rcDescription,DT_VCENTER | DT_SINGLELINE);
	//		DrawText(hParentDc,_T("   ״̬"),-1,&rcStatus,DT_VCENTER | DT_SINGLELINE);

	//		SelectObject(hParentDc,hGDIFont);
	//		DeleteObject(hFont);
	//		//ReleaseDC(hWnd,hParentDc);
	//		return 1;
	//	}
	case	WM_PAINT:	//����ͷ
		{
			PAINTSTRUCT ps;
			HWND hTextName = GetDlgItem(hWnd,IDC_Name); //��ͷ-����
			HWND hTextDescription = GetDlgItem(hWnd,IDC_Description);//��ͷ-����
			HWND hTextStatus = GetDlgItem(hWnd,IDC_Status);//��ͷ-״̬
			HWND hTextTitle = GetDlgItem(hWnd,IDC_Title);//��ͷ-ͼ��

			//���ش���
			ShowWindow(hTextName,SW_HIDE);
			ShowWindow(hTextDescription,SW_HIDE);
			ShowWindow(hTextStatus,SW_HIDE);
			ShowWindow(hTextTitle,SW_HIDE);
			
			//��ȡ�豸
			HDC	 hParentDc = BeginPaint(hWnd,&ps);

			//��ȡ��ɫ
			HBRUSH	hBrush = CreateSolidBrush(RGB(17,113,223));


			//��ȡλ��
			RECT	rcName, rcDescription, rcStatus;
			CRect rcTitle;

			GetWindowRect(hTextName,&rcName);
			GetWindowRect(hTextDescription,&rcDescription);
			GetWindowRect(hTextStatus,&rcStatus);
			GetWindowRect(hTextTitle,&rcTitle);

			//����ת��
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcName,2);
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcDescription,2);
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcStatus,2);
			MapWindowPoints(HWND_DESKTOP,hWnd,(LPPOINT)&rcTitle,2);

			Graphics mGraphics(hParentDc);
			 HRSRC hRsrc = ::FindResource(pServiceWindow->m_hInstance, MAKEINTRESOURCE(IDJ_Title), L"JPG");	//��ȡͼƬ��Դ
			 if (hRsrc == NULL)
			 {
				 break;
			 }
			 DWORD dwSize = ::SizeofResource(pServiceWindow->m_hInstance, hRsrc); //��ȡ��Դ��С
			 if (dwSize == NULL)
			 {
				 break;
			 }
			 HGLOBAL hGlobal = ::LoadResource(pServiceWindow->m_hInstance, hRsrc); //������Դ
			 if (hGlobal == NULL)
			 {
				 break;
			 }
			 LPVOID pBuffer = ::LockResource(hGlobal); //��ȡ��Դ���ڴ��ַ
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

			HFONT hFont = CreateFont(-14,0,0,0,0,0,0,0,0,0,0,0,0,_T("����"));
			HGDIOBJ hGDIFont = SelectObject(hParentDc,hFont);
			SetTextColor(hParentDc,RGB(255,255,255));
			SetBkMode(hParentDc,TRANSPARENT);

			DrawText(hParentDc,_T("   ����"),-1,&rcName,DT_VCENTER | DT_SINGLELINE);
			DrawText(hParentDc,_T("   ����"),-1,&rcDescription,DT_VCENTER | DT_SINGLELINE);
			DrawText(hParentDc,_T("   ״̬"),-1,&rcStatus,DT_VCENTER | DT_SINGLELINE);

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


//��������������
//************************************
// ������:	CreateServiceWindow
// ȫ����:	CServiceWindow::CreateServiceWindow
// ���ʼ�:	public 
// ����ֵ:	int
// �޶���:	
// ��  ��:	HINSTANCE hInstance	ʵ�����
// ��  ��:	int nShow			�Ƿ���Ҫ��ʾ
// ��  ע:	����������
//************************************
int		CServiceWindow::CreateServiceWindow(HINSTANCE hInstance, int nShow)
{
	m_hInstance = hInstance; 

	FQ_ShangGuanXWHandle = CreateMutex(NULL,FALSE,_T("FQ_Mz"));	//����������
	//if (FQ_ShangGuanXWHandle)
	//{
		if (ERROR_ALREADY_EXISTS == GetLastError())	//������ֻ�����
		{
			WRITE_LOG(LOG_LEVEL_INFO, "����������");
		
			//HWND	hFindWind = FindWindowEx(_T(""),_T("����2013"));	//��ʾԭ����
			HWND hFindWind = FindWindowEx(NULL, NULL, NULL, _T("����2013"));
			if (hFindWind == NULL)
			{
				WRITE_LOG(LOG_LEVEL_FATAL,"���ֻ�����,��δ�ҵ����ھ��.�����˳�!");
				ExitProcess(0);
			}
			ShowWindow(hFindWind,SW_SHOW);

			WRITE_LOG(LOG_LEVEL_ERROR, _T("���ڱ��ٴμ���"));
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
	//wcex.lpszClassName	= _T("����2013");
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
	//m_hWnd = CreateWindow(wcex.lpszClassName,_T("����2013"), WS_OVERLAPPEDWINDOW, nW, nH, 800, 600, NULL, NULL, hInstance, NULL);
	//m_hWnd = CreateWindow(wcex.lpszClassName,_T("����2013"), WS_OVERLAPPED | WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_ICONIC | WS_SYSMENU, nW, nH, 600, 500, NULL, NULL, hInstance, NULL);

	//SendMessage(m_hWnd,WM_INITWINODW,NULL,NULL);
	//CServiceWindow*	pServiceWindow = CServiceWindow::GetServiceWindow();

	m_hWnd = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),NULL,WndProc);	//��������
	if (NULL == m_hWnd)
	{
		//TODO: �Ƿ�֪ͨ�û�
		WRITE_LOG(LOG_LEVEL_FATAL, "The function CreateDialog is faild , ErrorCode : %x\r\n", GetLastError());
		ExitProcess(0);
	}
	//SendMessage(m_hWnd,WM_INITWINODW,NULL,NULL);
	if (nShow)	//�����Ҫ��ʾ
	{
		WRITE_LOG(LOG_LEVEL_ERROR, _T("���ڵ�һ�α�����"));
		ShowWindow(m_hWnd,SW_SHOW);
	}
	//UpdateWindow (m_hWnd);

	TCHAR	wszBrandsName[MAXBYTE] = { 0 };
	LoadString(NULL,IDS_BrandsName,wszBrandsName,MAXBYTE);
	memset(&m_nid,0,sizeof(NOTIFYICONDATA));	//����ͼ��ṹ
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;
	m_nid.uID = 1;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_REALTIME;
	m_nid.dwInfoFlags = NIIF_INFO;
	m_nid.uCallbackMessage = PopupMenu;//�Զ������Ϣ����
	m_nid.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_MiniIcon));
	lstrcpy(m_nid.szTip,wszBrandsName);//��Ϣ��ʾ��Ϊ������2013��
	//�����������ͼ��
	if (!Shell_NotifyIcon(NIM_ADD,&m_nid))	//�������ͼ��
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Shell_NotifyIconʧ�ܣ�������� %d",GetLastError());
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
		MessageBox(m_hWnd,_T("socket ʧ��"),NULL,0);
		ExitProcess(0);
	}

	CString	strPort = m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));//��������UDP�˿�
	int nPort = _ttoi(strPort);

	TCHAR	wszPortBuffer[512] = { 0 };
	int nErrorUdp = GetProcessNameFromPort(1,nPort,wszPortBuffer,sizeof(wszPortBuffer)/sizeof(TCHAR));	//���˿��Ƿ�ռ��
	if (nErrorUdp != NULL)
	{
		TCHAR	wszErrorMessage[256] = { 0 };
		wsprintf(wszErrorMessage, _T("���ǽ���������ʹ�õ�UDP�˿� %u �ѱ���%s��ռ�ã�\r\n\r\n����ʱ�رոó���"), nPort, wszPortBuffer);
		MessageBox(m_hWnd,wszErrorMessage, _T("��ܰ��ʾ"), MB_OK);
		ExitProcess(0);
	}


	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   
	local.sin_family = AF_INET;  
	local.sin_port = htons(nPort);   
	if (bind(m_Socket, (struct sockaddr*)&local,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		ExitProcess(0);
	}

	WSAAsyncSelect(m_Socket,m_hWnd,WM_SOCKET_IN,FD_READ);	//�첽ģʽ

	g_MsgTaskbarRestart = RegisterWindowMessage(_T("TaskbarCreated"));	//ע������ϢTaskbarCreated
	if (!g_MsgTaskbarRestart)
	{	
		//ע������Ϣʧ��
		WRITE_LOG(LOG_LEVEL_ERROR,"RegisterWindowMessage ʧ�ܣ�");
		ExitProcess(0);
	}

	WRITE_LOG(LOG_LEVEL_FATAL, "��ʼ����ɽ�����Ϣѭ��!");
	MSG	msg;
	while (GetMessage (&msg, NULL, 0, 0)) 
	{  
		//WRITE_LOG(LOG_LEVEL_INFO, "���յ���Ϣ:%d", msg.message);
		TranslateMessage (&msg); 
		DispatchMessage (&msg);    
		//WRITE_LOG(LOG_LEVEL_INFO, "��Ϣ:%d�������", msg.message);
	} 
	return msg.wParam;
}
//��ʼ���б�
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
	lvi.pszText = _T("˹�������ǽ���������");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);


	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_MZDIO");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 2;
	lvi.pszText = _T("˹�������Ǵ��̷���");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_TOOLSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 3;
	lvi.pszText = _T("˹�������Ǹ������߷���");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_BTSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 4;
	lvi.pszText = _T("˹�����������ط���");
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
		lvi.pszText = _T("û�а�װ");
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
			lvi.pszText = _T("��ֹͣ");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 0;
			lvi.pszText = _T("��������");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);

	hService = OpenService(hScm, _T("SPL_TOOLSVC"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 2;
		lvi.pszText = _T("û�а�װ");
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
			lvi.pszText = _T("��ֹͣ");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 2;
			lvi.pszText = _T("��������");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);

	hService = OpenService(hScm, _T("SPL_BTSVC"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 3;
		lvi.pszText = _T("û�а�װ");
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
			lvi.pszText = _T("��ֹͣ");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 3;
			lvi.pszText = _T("��������");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);

	hService = OpenService(hScm, _T("SPL_MZDIO"), SERVICE_ALL_ACCESS);
	if (hService == NULL)
	{
		lvi.iSubItem = 2;
		lvi.iItem = 1;
		lvi.pszText = _T("û�а�װ");
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
			lvi.pszText = _T("��ֹͣ");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		if(stStatus.dwCurrentState == SERVICE_RUNNING)
		{
			lvi.iSubItem = 2;
			lvi.iItem = 1;
			lvi.pszText = _T("��������");
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
	}
	CloseServiceHandle(hService);
	CloseServiceHandle(hScm);
	m_bIsInit = TRUE;
	//ButtonRefresh();
	return 0;
}
//��������
DWORD	WINAPI	ThreadStart(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	LV_ITEM lvi = { 0 };
	int nItem = SendMessage(hList,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(hWnd,_T("��ѡ�����"),_T("����2013"),0);
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
		wsprintf(wszMessageBuffer,_T("%s û�а�װ�������°�װ��"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
		CloseServiceHandle(hScm);
		goto End;
	}
	memset(&stStatus, 0, sizeof(stStatus));
	QueryServiceStatus(hService, &stStatus);
	if (stStatus.dwCurrentState == SERVICE_RUNNING)
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s ��������"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else if (stStatus.dwCurrentState == SERVICE_STOPPED)
	{
		int nRet = StartService(hService, 0, 0);
		if (nRet == 1)
		{
			lvi.pszText = _T("��������");
			lvi.iSubItem = 2;
			SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
		}
		else
		{
			TCHAR	wszMessageBuffer[128] = { 0 };
			wsprintf(wszMessageBuffer,_T("%s ����ʧ��"),lpwzsItemData);
			MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
		}
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s ״̬�޷�ʶ��"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
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
//������װ
DWORD	WINAPI	ThreadStop(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	LV_ITEM lvi = { 0 };
	int nItem = SendMessage(hList,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(hWnd,_T("��ѡ�����"),_T("����2013"),0);
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
		wsprintf(wszMessageBuffer,_T("%s û�а�װ�������°�װ��"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
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
				lvi.pszText = _T("��ֹͣ");
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
		wsprintf(wszMessageBuffer,_T("%s �Ѿ�ֹͣ"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s ״̬�޷�ʶ��"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
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
//��������
DWORD	WINAPI	ThreadRestart(LPVOID	lpvoid)
{
	HWND	hWnd = (HWND)lpvoid;

	HWND hList = GetDlgItem(hWnd,IDC_LIST1);

	LV_ITEM lvi = { 0 };
	int nItem = SendMessage(hList,LVM_GETNEXTITEM,-1,LVNI_SELECTED);
	if (nItem == -1)
	{
		MessageBox(hWnd,_T("��ѡ�����"),_T("����2013"),0);
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
		wsprintf(wszMessageBuffer,_T("%s û�а�װ�������°�װ��"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
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
					lvi.pszText = _T("��������");
					lvi.iSubItem = 2;
					SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
				}
				else
				{
					TCHAR	wszMessageBuffer[128] = { 0 };
					wsprintf(wszMessageBuffer,_T("%s ����ʧ��"),lpwzsItemData);
					MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
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
				lvi.pszText = _T("��������");
				lvi.iSubItem = 2;
				SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
			}
			else
			{
				TCHAR	wszMessageBuffer[128] = { 0 };
				wsprintf(wszMessageBuffer,_T("%s ����ʧ��"),lpwzsItemData);
				MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
			}
		}
		CloseServiceHandle(hService);
		CloseServiceHandle(hScm);
		goto End;
	}
	else
	{
		TCHAR	wszMessageBuffer[128] = { 0 };
		wsprintf(wszMessageBuffer,_T("%s ״̬�޷�ʶ��"),lpwzsItemData);
		MessageBox(hWnd,wszMessageBuffer,_T("����2013"),0);
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
//ˢ�·���״̬
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
	lvi.pszText = _T("˹�������ǽ���������");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_MZDIO");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 2;
	lvi.pszText = _T("˹�������Ǵ��̷���");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_TOOLSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 3;
	lvi.pszText = _T("˹�������Ǹ������߷���");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	lvi.iItem = ++nItem;
	lvi.iSubItem = 0;
	lvi.pszText = _T("SPL_BTSVC");
	SendMessage(hList,LVM_INSERTITEM,0,(long)&lvi);
	lvi.iSubItem = 1;
	lvi.iItem = nItem;
	lvi.iImage = 4;
	lvi.pszText = _T("˹�����������ط���");
	SendMessage(hList,LVM_SETITEM,0,(long)&lvi);

	//SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);	//��SCM������
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
	//	lvi.pszText = _T("û�а�װ");
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
	//		lvi.pszText = _T("��ֹͣ");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 0;
	//		lvi.iImage = 1;
	//		lvi.pszText = _T("��������");
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
	//	lvi.pszText = _T("û�а�װ");
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
	//		lvi.pszText = _T("��ֹͣ");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 1;
	//		lvi.iImage = 2;
	//		lvi.pszText = _T("��������");
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
	//	lvi.pszText = _T("û�а�װ");
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
	//		lvi.pszText = _T("��ֹͣ");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 2;
	//		lvi.iImage = 3;
	//		lvi.pszText = _T("��������");
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
	//	lvi.pszText = _T("û�а�װ");
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
	//		lvi.pszText = _T("��ֹͣ");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 2;
	//		lvi.iImage = 3;
	//		lvi.pszText = _T("��������");
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
	//	lvi.pszText = _T("û�а�װ");
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
	//		lvi.pszText = _T("��ֹͣ");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//	if(stStatus.dwCurrentState == SERVICE_RUNNING)
	//	{
	//		lvi.iSubItem = 2;
	//		lvi.iItem = 3;
	//		lvi.iImage = 4;
	//		lvi.pszText = _T("��������");
	//		SendMessage(hList,LVM_SETITEM,0,(long)&lvi);
	//	}
	//}
	//CloseServiceHandle(hService);
	//CloseServiceHandle(hScm);
	HWND hButton = GetDlgItem(hWnd,IDC_BUTTON4);	
	EnableWindow(hButton,TRUE);	//����ʹ��ˢ�°�ť
	return 0;
}
//ˢ�°�ť
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
//�������з���
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
			wsprintf(wszMessage,_T("%s ����û�а�װ���ߴ���"),lpwzsItemData);
			MessageBox(hWnd,wszMessage,_T("����2013"),0);
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
				LvSub.pszText = _T("��������");
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
//�ر�����
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

		WRITE_LOG(LOG_LEVEL_FATAL, _T("��ʼֹͣ����: %s"), lpwzsItemData);
		SC_HANDLE	hService = OpenService(hScm,lpwzsItemData,SERVICE_ALL_ACCESS);
		if (hService == NULL)
		{
			DWORD err = GetLastError();
			TCHAR	wszMessage[64] = { 0 };
			switch(err)
			{
			case ERROR_INVALID_NAME:
				wsprintf(wszMessage,_T("%s ����������"),lpwzsItemData);
				MessageBox(hWnd,wszMessage,_T("����2013"),0);
				break;
			case ERROR_SERVICE_DOES_NOT_EXIST:
				wsprintf(wszMessage,_T("%s ����δ��װ"),lpwzsItemData);
				MessageBox(hWnd,wszMessage,_T("����2013"),0);
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
					LvSub.pszText = _T("��ֹͣ");
					SendMessage(hList,LVM_SETITEM,0,(long)&LvSub);
					break;
				}
				Sleep(60);
			}
		}
		else
		{
			WRITE_LOG(LOG_LEVEL_FATAL, _T("ֹͣ����: %s ʱ���ַ���δ����"), lpwzsItemData);
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