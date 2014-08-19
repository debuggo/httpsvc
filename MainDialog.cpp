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

#define  WM_NOTIFYMESSAGE  WM_USER + 301	//ϵͳ������Ϣ
#define  WM_SOCKET_IN  WM_USER + 302	//ϵͳ������Ϣ
#define  NOTIFYID  1	//����ID
#define WM_NOTIFY_OPENPATH WM_USER+106 //,_T("��Ŀ¼(&D)"));
#define WM_NOTIFY_CONTACT_US WM_USER+102//,_T("��ϵ����(&C)"));
#define WM_NOTIFY_SERVICE_CONTROL WM_USER+103//,_T("�������(&S)"));
#define WM_NOTIFY_PROCESS_CONTROL WM_USER+105//,_T("�������(&A)"));
#define WM_NOTIFY_INTERFACE_CONTROL WM_USER+101//,_T("�������(&W)"));
#define WM_NOTIFY_EXIT WM_USER+104 //,_T("�˳�(&E)"));

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
			case IDC_BTN_EXIT:	//���ش���
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
	case WM_NOTIFYMESSAGE:	//������Ϣ
		{
			if (wParam == NOTIFYID)	//�����ע�����̵���Ϣ
			{
				switch(lParam)
				{
				case WM_RBUTTONUP:	//����_�Ҽ�̧��
					{

						POINT *lpoint = new tagPOINT;
						::GetCursorPos(lpoint);//�õ����λ��
						pMainDlg->m_hMenu = CreatePopupMenu();
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_OPENPATH,_T("��Ŀ¼(&D)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_CONTACT_US,_T("��ϵ����(&C)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_SERVICE_CONTROL,_T("�������(&S)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_PROCESS_CONTROL,_T("�������(&A)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_INTERFACE_CONTROL,_T("�������(&W)"));
						AppendMenu(pMainDlg->m_hMenu,MF_STRING,WM_NOTIFY_EXIT,_T("�˳�(&E)"));
						::SetForegroundWindow(pMainDlg->m_hWnd);
						TrackPopupMenu(pMainDlg->m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, lpoint->x, lpoint->y, 0, hWnd, NULL);
						delete	lpoint;

					}
					break;
				case WM_LBUTTONDBLCLK:	//����_���˫��,����Ϣʱ����URL
					{
						if (pMainDlg->m_bIsHasMsg)
						{
							KillTimer(hWnd, ID_NOTIFYMSG_IN);
							pMainDlg->m_bIsHasMsg = FALSE;
							//��ʾ��Ϣ����
							if (pMainDlg->m_bMsgWindowsIsShow == FALSE)
							{
								ShowWindow(pMainDlg->m_hMsgWnd, SW_SHOW);
								pMainDlg->m_bMsgWindowsIsShow = TRUE;
							}
							//������Ϣ
							pMainDlg->AddMsgToMsgWnd(hWnd);
							pMainDlg->m_nid.hIcon =  LoadIcon(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon));	//����ͼ��
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
					return 0;	//��ϵͳ����
					break;
				}
			}
		}
		break;
	case WM_COMMAND:	//�˵���Ϣ
		{
			WORD wmMenuID = LOWORD(wParam);
			WORD wmEvent = HIWORD(wParam);
			switch(wmMenuID)
			{
			case WM_NOTIFY_INTERFACE_CONTROL:	//����_�������
				{
					CString strUrl = URL_CONTROL + pMainDlg->m_strPort;
					pMainDlg->OpenUrl(strUrl);
				}
				break;
			case WM_NOTIFY_CONTACT_US:	//����_��ϵ����
				{
					CString strUrl = URL_HOMEPAGE;
					pMainDlg->OpenUrl(strUrl);
				}
				break;
			case WM_NOTIFY_SERVICE_CONTROL:	//����_�������
				{
					ShowWindow(hWnd, SW_SHOW);
					SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
					pMainDlg->m_bWindowIsShow = TRUE;
				}
				break;
			case WM_NOTIFY_EXIT:	//����_�˳�
				{
					if(pMainDlg->ExitMainDialog()) ExitProcess(0);
				}
				break;
			case WM_NOTIFY_PROCESS_CONTROL:	//����_�������
				{
					CString strPath = pMainDlg->m_strAppPath + URL_PROCESS_CONTROL;
					if(pMainDlg->OpenUrl(strPath))
						WRITE_LOG(LOG_LEVEL_ERROR, _T("�򿪳���%sʧ��!"), strPath);
				}
				break;
			case WM_NOTIFY_OPENPATH:	//����_��Ŀ¼
				{
					pMainDlg->OpenUrl(pMainDlg->m_strAppPath);
				}
				break;
			case IDC_BTN_STARTSERVICE:	//������������
				{
					pMainDlg->BtnStartService(hWnd);
				}
				break;
			case IDC_BTN_STOPSERVICE:	//ֹͣ��������
				{
					pMainDlg->BtnStopService(hWnd);
				}
				break;
			case IDC_BTN_RESTSTART:	//��������
				{
					pMainDlg->BtnRestStatrService(hWnd);
				}
				break;
			case IDC_BTN_REFRESH://ˢ�·���״̬
				{
					pMainDlg->BtnRefreshService(hWnd);
				}
				break;
			case IDC_BTN_STARTALLSRTVICE:	//�������з���
				{
					pMainDlg->BtnStartAllService(hWnd);
				}
				break;
			case IDC_BTN_STOPALLSERVICE:	//ֹͣ���з���
				{
					pMainDlg->BtnStopAllService(hWnd);
				}
				break;
			case IDC_BTN_HIDEWINDOW://���ش���
				{
					pMainDlg->BtnHideWindow(hWnd);
				}
				break;
			default:
				return 0;	//��ϵͳ����
				break;
			}
		}
		break;
	case WM_CLOSE:	//���ڹر�
		{
			ShowWindow(hWnd, SW_HIDE);
			pMainDlg->m_bWindowIsShow = FALSE;
		}
		break;
	case WM_INITDIALOG:	//���ڴ���
		{
			HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon)));   
			pMainDlg->InitServiceList(hWnd);
			GdiplusStartup(&pMainDlg->m_gdiPlusToken, &pMainDlg->m_gdiPlusInPut, NULL);
			pMainDlg->WriteMessage(hWnd, _T("��ʼ�����"));
		}
		break;
	case WM_PAINT:	//�����ػ�
		{
			PAINTSTRUCT ps;
			HWND hTextName = GetDlgItem(hWnd,IDC_SERVICE_NAME); //��ͷ-����
			HWND hTextDescription = GetDlgItem(hWnd,IDC_SERVICE_DESCRIPTION);//��ͷ-����
			HWND hTextStatus = GetDlgItem(hWnd,IDC_SERVICE_STATUS);//��ͷ-״̬
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
			HRSRC hRsrc = ::FindResource(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDJ_Title), L"JPG");	//��ȡͼƬ��Դ
			if (hRsrc == NULL)
			{
				break;
			}
			DWORD dwSize = ::SizeofResource(pMainDlg->m_hInstance, hRsrc); //��ȡ��Դ��С
			if (dwSize == NULL)
			{
				break;
			}
			HGLOBAL hGlobal = ::LoadResource(pMainDlg->m_hInstance, hRsrc); //������Դ
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
			pMainDlg->RefreshServiceStaus(hWnd);
		}
		break;
	case WM_SOCKET_IN:	//���յ�BT��MZD����Ϣ
		{
			if (WSAGETSELECTERROR(lParam))	//����Ǵ�����Ϣ
			{
				closesocket(wParam);
				break;
			}
			switch(WSAGETSELECTEVENT(lParam))	//��ȡ��Ϣ
			{
			case FD_READ:
				{
					char RecvBuffer[RECVMAXBUFFER] = { 0 };//��Ϣ
					int nRecv = recvfrom(pMainDlg->m_Socket, RecvBuffer, RECVMAXBUFFER, 0, NULL, NULL);
					if (nRecv == SOCKET_ERROR)//��ȡ��Ϣʧ��
					{
						break;
					}
					BUBBLEDATA *pBubble = (BUBBLEDATA *)RecvBuffer;
					switch(pBubble->nFlags)
					{
					case 1://��Ϣ����
						{
							//����Ϣ����������
							PSOCKETINMSG inMsg = new SOCKETINMSG;
							CTime time = CTime::GetCurrentTime();
							CString strBuf = time.Format(_T("%Y��%m��%d�� %H:%M:%S"));
							//TCHAR strBuf[MAXBYTE] = time.Format(_T("%Y��%m��%D�� %H:%M:%S"));
							_tcscpy(inMsg->szTime, strBuf.GetBuffer());
							strBuf.ReleaseBuffer();
							_tcscpy(inMsg->szMsgText, pBubble->wszMessage);
							_tcscpy(inMsg->szTitle, pBubble->wszTitle);
							pMainDlg->m_vctMsg.push_back(inMsg);
							//�����Ϣ��¼���ڱ���
							if (pMainDlg->m_bMsgWindowsIsShow == TRUE)
							{
								//����ʾ����_ֱ�Ӹ�������Ϣ��¼����
								pMainDlg->AddMsgToMsgWnd(hWnd);
							}
							else
							{
								//��ʾ��Ϣ����_����ͼ������
								SetTimer(hWnd, ID_NOTIFYMSG_IN, 400, TimeShellNotifyIcon);
								pMainDlg->m_bIsHasMsg = TRUE;
							}
						}
						break;
					case 10:	//ɾ�����̲��˳�
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
		return 0;	//��ϵͳ����
		break;
	}
	return 1;	//���������
}

BOOL CMainDialog::CreateMainDialog( HINSTANCE hInstance, int bIsShow )
{
	m_hInstance = hInstance;

	TCHAR szDlgName[MAXBYTE] = { 0 };
	LoadString(NULL, IDS_BrandsName, szDlgName, MAXBYTE);//��ȡ���ڱ���
	//�������Ƿ�������
	m_hMutex = CreateMutex(NULL, FALSE, _T("FQ_MainDlg"));
	if (ERROR_ALREADY_EXISTS == GetLastError())	//����������Ѵ���
	{
		m_hWnd = FindWindowEx(NULL, NULL, NULL, szDlgName);
		if (NULL == m_hWnd)
		{
			WRITE_LOG(LOG_LEVEL_FATAL, _T("���ֻ�����,��δ�ҵ����ھ��! ErrorCode : 0x%08X"), GetLastError());
			ExitProcess(0);
		}
		if(bIsShow == 1)
			ShowWindow(m_hWnd, SW_SHOW);
		ExitProcess(0);
	}
	//��������
	m_hWnd = CreateDialog(hInstance, MAKEINTRESOURCEW(IDD_DLG_MAIN), NULL, WindowProc);
	if (m_hWnd == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("��������ʧ��! ErrorCode : 0x%08X"), GetLastError());
		CloseHandle(m_hMutex);
		ExitProcess(0);
	}
	//������Ϣ����
	m_hMsgWnd = CreateDialog(hInstance, MAKEINTRESOURCEW(IDD_DLG_MSG), NULL, MsgWndProc);
	if (m_hMsgWnd == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("��������ʧ��! ErrorCode : 0x%08X"), GetLastError());
		CloseHandle(m_hMutex);
		ExitProcess(0);
	}
	m_bMsgWindowsIsShow = FALSE;
	//��ʾ����
	if (bIsShow == 1)
	{
		ShowWindow(m_hWnd, SW_SHOW);
		m_bWindowIsShow = TRUE;
	}
	
	

	//���������ļ�
	m_strAppPath = CAppMain::GetAppPath();
	CString strIniPath = m_strAppPath + _T("httpsvc.ini");
	m_IniFile.SetPath(strIniPath);

	//����socket
	WSADATA wsaData;
	if(int nErr = WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("WSAStartup failed! ErrorCode : 0x%08X"), GetLastError());
		MessageBox(m_hWnd, _T("Socket ʧ��!"), NULL, MB_OK);
		ExitProcess(0);
	}
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == SOCKET_ERROR)
	{
		WRITE_LOG(LOG_LEVEL_FATAL, _T("Socket ʧ��! ErrorCode : 0x%08X"), GetLastError());
		WSACleanup();
		MessageBox(m_hWnd, _T("Socket ʧ��!"), NULL, MB_OK);
		ExitProcess(0);
	}

	m_strPort = m_IniFile.GetKeyValue(_T("FQ"), _T("Port"));
	int nPort = _ttoi(m_strPort);//��ȡ�˿�
	TCHAR szPortOccupationProcessName[MAXBYTE] = { 0 };	//ռ�ö˿ڵĳ�����
	BOOL bRet = FALSE;
	do 
	{
		if(GetProcessNameFromPort(1, nPort, szPortOccupationProcessName, MAXBYTE) != 0)//���˿��Ƿ�ռ��
		{
			CString strBuf;
			strBuf.Format(_T("���ǽ���������ʹ�õ�UDP�˿�:%d�ѱ�����:\"%s\"ռ��!\r\n��رոó��������!"), nPort, szPortOccupationProcessName);
			if(MessageBox(m_hWnd, strBuf, _T("����"), MB_YESNO) == IDYES)
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
		WRITE_LOG(LOG_LEVEL_FATAL, _T("��Sokcetʧ��! ErrorCode : 0x%08X"), GetLastError());
		MessageBox(m_hWnd, _T("���ǽ����������ڰ󶨶˿�ʱ���ִ���!"), _T("����"), MB_OK);
		closesocket(m_Socket);
		CloseHandle(m_hMutex);
		WSACleanup();
		ExitProcess(0);
	}
	WSAAsyncSelect(m_Socket, m_hWnd, WM_SOCKET_IN, FD_READ);	//����Ϣ
	//�������ͼ��

	if (!CreateTrayNotify(szDlgName))
	{
		WRITE_LOG(LOG_LEVEL_ERROR, _T("�������ͼ��ʧ��! ErrorCode :0x%08X"), GetLastError());
	}

	
	MSG msg;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) 
	{ 
		if (bRet == -1)
		{
			// Handle the error and possibly exit
			WRITE_LOG(LOG_LEVEL_ERROR, _T("GetMessage���ִ���! ErrorCode : 0x%08X"), GetLastError());
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
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;//ͼ��|�ص���Ϣ|����|��Ϣ����
	m_nid.dwInfoFlags = NIIF_INFO;	
	m_nid.uCallbackMessage = WM_NOTIFYMESSAGE;	//�ص���Ϣ
	m_nid.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon));	//����ͼ��
	m_nid.uVersion = NOTIFYICON_VERSION_4;	//���ð汾
	//m_nid.dwState = NIS_SHAREDICON;	//ͼ�깲��
	lstrcpy(m_nid.szTip, szTip);
	//�������ͼ��
	return Shell_NotifyIcon(NIM_ADD, &m_nid);
}
//��ȡ������
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


// ȡ��ռ����ָ���˿ڵĽ����ļ���------���󶨶˿�ʧ��ʱʹ�ã���ʾ�û��˿��ѱ��ĸ�����ռ��
// dwType     = 0ΪTCP,1ΪUDP
// wdPort     = �˿�
// pszFile    = ����Ľ����ļ���
// dwFileSize = pszFile��С
// ����ֵ0=ʧ�ܣ���0=�ɹ�
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
	//��ȡ�ؼ�
	HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);	//�б�
	HWND hTextName = GetDlgItem(hWnd,IDC_SERVICE_NAME);	//������
	HWND hTextDescription = GetDlgItem(hWnd,IDC_SERVICE_DESCRIPTION);	//��������
	HWND hTextStatus = GetDlgItem(hWnd,IDC_SERVICE_STATUS);//����״̬
	SendMessage(hList,LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//�����б��ѡ��
	
	//��ȡ�ؼ�λ��
	CRect rcTextName, rcTextDescription, rcTextStatus;
	GetWindowRect(hTextName, rcTextName);
	GetWindowRect(hTextDescription, rcTextDescription);
	GetWindowRect(hTextStatus, rcTextStatus);
	
	//����listλ��
	LV_COLUMN lvc = { 0 };
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;//�����ı������Ч
	lvc.cx = rcTextName.Width();
	SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&lvc);
	lvc.cx = rcTextDescription.Width() - 22;
	SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&lvc);
	lvc.cx = rcTextStatus.Width();
	SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&lvc);
	
	//����ͼ��
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
	
	
	//���÷���״̬
	LV_ITEM lvItem = { 0 };
	int nItemIndex = 0;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	
	CString strSvcStatus;
	//HTTPSVC
	lvItem.iSubItem = 0;	//���õ�һ��	
	lvItem.pszText = SVC_NAME_SPLHTTPSVC;
	nItemIndex = SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iSubItem = 1;
	lvItem.iItem = nItemIndex;
	lvItem.iImage = 1;
	lvItem.pszText = _T("˹�������ǽ���������");
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);

	//MZD
	lvItem.iItem = ++nItemIndex;
	lvItem.iSubItem = 0; 
	lvItem.pszText = SVC_NAME_SPLMZDIO;
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = 1;
	lvItem.iImage = 2;
	lvItem.pszText = (_T("˹�������Ǵ��̷���"));
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);
	
	//TOOL
	lvItem.iItem = ++nItemIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = SVC_NAME_SPLTOOLSVC;
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = 1;
	lvItem.iImage = 3;
	lvItem.pszText = (_T("˹�������Ǹ������߷���"));
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);

	//BT
	lvItem.iItem = ++nItemIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = SVC_NAME_SPLBTSVC;
	SendMessage(hList, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	lvItem.iItem = nItemIndex;
	lvItem.iSubItem = 1;
	lvItem.iImage = 4;
	lvItem.pszText = (_T("˹�����������ط���"));
	SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lvItem);

	RefreshServiceStaus(hWnd);
	return TRUE;
}

BOOL CMainDialog::RefreshServiceStaus(HWND hWnd)
{
	HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);	//�б�
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
	return SetWindowText(hMsg, _T("��ʾ:") + strMsg);
}


BOOL CMainDialog::BtnStartService( HWND hWnd )
{
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTSERVICE);
	EnableWindow(hBtn, FALSE);	//���ð�ť
	
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
			pMainDlg->WriteMessage(hWnd, _T("��ѡ�����!"));
			break;
		}
		//int dwServiceStatus = serviceCon.GetServiceStatus(szText);
		//if (dwServiceStatus == SERVICE_RUNNING && nAgainNum == 0)	//�����������˳�
		//{
		//	CString strBuf;
		//	strBuf.Format(_T("%s������������,�����ٴ�����!"), szText);
		//	pMainDlg->WriteMessage(hWnd, strBuf);
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_RUNNING).GetBuffer());
		//	break;
		//}
		//else
		//{
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, _T("��������"));
		//	//��������
		//	switch(dwServiceStatus)
		//	{
		//	case -1:	//����δ��װ
		//		{
		//			if(FALSE == pMainDlg->InstallService(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("��װ����ʱ���ִ���!"));
		//				CString strBuf;
		//				strBuf.Format(_T("��װ����%sʱ���ִ���!�����ļ��Ƿ�����!�������°�װ������!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����δ��װ"));
		//				bAgain = FALSE;//������ѭ��
		//			}
		//		}
		//		break;
		//	case SERVICE_RUNNING:	//��������
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("%s���������ɹ�!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_RUNNING).GetBuffer());
		//			bAgain = FALSE;//������ѭ��
		//		}
		//		break;
		//	case SERVICE_STOPPED:	//��ֹͣ
		//	case SERVICE_CONTINUE_PENDING://����
		//	case SERVICE_PAUSED:	//��ͣ
		//		{
		//			if (FALSE == pMainDlg->ServiceStart(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("��������ʱ��������!"));
		//				CString strBuf;
		//				strBuf.Format(_T("��������%sʱ���ִ���!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("��������ʧ��"));
		//				bAgain = FALSE;//������ѭ��
		//			}
		//		}
		//		break;
		//	default:
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("������������%s!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			if (nAgainNum % 4 == 0)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����������"));
		//			}
		//			else if(nAgainNum %4 == 1)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����������."));
		//			}
		//			else if(nAgainNum %4 == 2)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����������.."));
		//			}
		//			else if(nAgainNum %4 == 3)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����������..."));
		//			}
		//		}
		//		break;
		//	}
		//}
		//nAgainNum ++;
		//Sleep(500);
		//if (nAgainNum == 20)
		//{
		//	WRITE_LOG(LOG_LEVEL_ERROR, _T("��������ʱ��������!"));
		//	CString strBuf;
		//	strBuf.Format(_T("��������%s��ʱ!������"), szText);
		//	pMainDlg->WriteMessage(hWnd, strBuf);
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����������ʱ"));
		//	bAgain = FALSE;//������ѭ��
		//}

		pMainDlg->ServiceStartByName(hWnd, nItemIndex, szText);
	} while (FALSE);
	
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTSERVICE);
	EnableWindow(hBtn, TRUE);	//���ð�ť
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
	HWND hList = GetDlgItem(hWnd,IDC_LIST_SERVICE);	//�б�
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
	WriteMessage(hWnd, _T("��ʼ��ͣ����"));
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPSERVICE);
	EnableWindow(hBtn, FALSE);	//���ð�ť

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
			pMainDlg->WriteMessage(hWnd, _T("��ѡ�����!"));
			break;
		}
		pMainDlg->ServiceStopByName(hWnd, nItemIndex, szText);
		//int dwServiceStatus = serviceCon.GetServiceStatus(szText);
		//if (dwServiceStatus == SERVICE_STOPPED && nAgainNum == 0)	//��������ͣ�˳�
		//{
		//	CString strBuf;
		//	strBuf.Format(_T("%s��������ͣ,�����ٴ���ͣ!"), szText);
		//	pMainDlg->WriteMessage(hWnd, strBuf);
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_STOPPED).GetBuffer());
		//	break;
		//}
		//else
		//{
		//	pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ"));
		//	//��ͣ����
		//	switch(dwServiceStatus)
		//	{
		//	case -1:	//����δ��װ
		//		{
		//			if(FALSE == pMainDlg->InstallService(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ���ִ���!"));
		//				CString strBuf;
		//				strBuf.Format(_T("��ͣ����%sʱ���ִ���!�����ļ��Ƿ�����!�������°�װ������!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("����δ��װ"));
		//				bAgain = FALSE;//������ѭ��
		//			}
		//		}
		//		break;
		//	case SERVICE_STOPPED:	//��ֹͣ
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("%s������ͣ�ɹ�!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			pMainDlg->SetListItemText(hWnd, nItemIndex, serviceCon.ServiceStatusToCString(SERVICE_STOPPED).GetBuffer());
		//			bAgain = FALSE;//������ѭ��
		//		}
		//		break;
		//	case SERVICE_RUNNING:	//������
		//		{
		//			if (FALSE == pMainDlg->ServiceStop(szText))
		//			{
		//				WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ��������!"));
		//				CString strBuf;
		//				strBuf.Format(_T("��ͣ����%sʱ���ִ���!"), szText);
		//				pMainDlg->WriteMessage(hWnd, strBuf);
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣʧ��"));
		//				bAgain = FALSE;//������ѭ��
		//			}
		//		}
		//		break;
		//	default:
		//		{
		//			CString strBuf;
		//			strBuf.Format(_T("������ͣ����%s!"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			if (nAgainNum % 4 == 0)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ��"));
		//			}
		//			else if(nAgainNum %4 == 1)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ��."));
		//			}
		//			else if(nAgainNum %4 == 2)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ��.."));
		//			}else if(nAgainNum %4 == 3)
		//			{
		//				pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ��..."));
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
		//		if (nAgainNum == 60) //һ����
		//		{
		//			WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ������ʱ!"));
		//			strBuf.Format(_T("��ͣ����%s��ʱ!������"), szText);
		//			pMainDlg->WriteMessage(hWnd, strBuf);
		//			pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ��ʱ"));
		//			bAgain = FALSE;//������ѭ��
		//		}
		//	}
		//	else
		//	{
		//		WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ������ʱ!"));
		//		strBuf.Format(_T("��ͣ����%s��ʱ!������"), szText);
		//		pMainDlg->WriteMessage(hWnd, strBuf);
		//		pMainDlg->SetListItemText(hWnd, nItemIndex, _T("������ͣ��ʱ"));
		//		bAgain = FALSE;//������ѭ��
		//	}
		//	
		//}


	} while (FALSE);

	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPSERVICE);
	EnableWindow(hBtn, TRUE);	//���ð�ť
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
	WriteMessage(hWnd, _T("��ʼ��������"));
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_RESTSTARTSERVICE);
	EnableWindow(hBtn, FALSE);	//���ð�ť

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
			pMainDlg->WriteMessage(hWnd, _T("��ѡ�����!"));
			break;
		}
		CString strBuf;
		int dwServiceStatus = serviceCon.GetServiceStatus(szText);
		if (dwServiceStatus != SERVICE_STOPPED)	//�������Ϊֹͣ
		{
			//ֹͣ����
			if(pMainDlg->ServiceStopByName(hWnd, nItemIndex, szText) == FALSE)
			{
				strBuf.Format(_T("��������%s���޷�ֹͣ����ʧ��!"), szText);
				pMainDlg->WriteMessage(hWnd, strBuf);
				break;
			}
		}
		//��������
		if(pMainDlg->ServiceStartByName(hWnd, nItemIndex, szText) == FALSE)
		{
			strBuf.Format(_T("��������%s���޷���������ʧ��!"), szText);
			pMainDlg->WriteMessage(hWnd, strBuf);
			break;
		}
		strBuf.Format(_T("��������%s�ɹ�!"), szText);
		pMainDlg->WriteMessage(hWnd, strBuf);
	} while (FALSE);

	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_RESTSTARTSERVICE);
	EnableWindow(hBtn, TRUE);	//���ð�ť
	return 1;
}



BOOL CMainDialog::ServiceStopByName( HWND hWnd, int nItemIndex, TCHAR *szText)
{
	SetListItemText(hWnd, nItemIndex, _T("������ͣ"));
	//��ͣ����
	CControlServiceEx serviceCon;
	int dwServiceStatus;
	BOOL bAgain = TRUE;
	int nAgainNum = 0;
	CString strBuf;
	strBuf.Format(_T("��ʼ��ͣ����%s"), szText);
	do 
	{
		dwServiceStatus = serviceCon.GetServiceStatus(szText);
		if (dwServiceStatus == SERVICE_STOPPED && nAgainNum == 0)	//��������ͣ�˳�
		{
			strBuf.Format(_T("%s��������ͣ,�����ٴ���ͣ!"), szText);
			WriteMessage(hWnd, strBuf);
			strBuf = serviceCon.ServiceStatusToCString(SERVICE_STOPPED);
			SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());
			strBuf.ReleaseBuffer();
			break;
		}
		switch(dwServiceStatus)
		{
		case -1:	//����δ��װ
			{
				if(FALSE == InstallService(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ���ִ���!"));
					strBuf.Format(_T("��ͣ����%sʱ���ִ���!�����ļ��Ƿ�����!�������°�װ������!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("����δ��װ"));
					return FALSE;
				}
			}
			break;
		case SERVICE_STOPPED:	//��ֹͣ
			{
				strBuf.Format(_T("%s������ͣ�ɹ�!"), szText);
				WriteMessage(hWnd, strBuf);
				strBuf = serviceCon.ServiceStatusToCString(SERVICE_STOPPED);
				SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());
				strBuf.ReleaseBuffer();
				bAgain = FALSE;//������ѭ��
			}
			break;
		case SERVICE_RUNNING:	//������
			{
				if (FALSE == ServiceStop(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ��������!"));
					strBuf.Format(_T("��ͣ����%sʱ���ִ���!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("������ͣʧ��"));
					return FALSE;
				}
			}
			break;
		default:
			{
				strBuf.Format(_T("������ͣ����%s!"), szText);
				WriteMessage(hWnd, strBuf);
				if (nAgainNum % 4 == 0)
				{
					SetListItemText(hWnd, nItemIndex, _T("������ͣ��"));
				}
				else if(nAgainNum %4 == 1)
				{
					SetListItemText(hWnd, nItemIndex, _T("������ͣ��."));
				}
				else if(nAgainNum %4 == 2)
				{
					SetListItemText(hWnd, nItemIndex, _T("������ͣ��.."));
				}else if(nAgainNum %4 == 3)
				{
					SetListItemText(hWnd, nItemIndex, _T("������ͣ��..."));
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
				if (nAgainNum == 60) //һ����
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ������ʱ!"));
					strBuf.Format(_T("��ͣ����%s��ʱ!������"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("������ͣ��ʱ"));
					return FALSE;
				}
			}
			else
			{
				WRITE_LOG(LOG_LEVEL_ERROR, _T("��ͣ����ʱ������ʱ!"));
				strBuf.Format(_T("��ͣ����%s��ʱ!������"), szText);
				WriteMessage(hWnd, strBuf);
				SetListItemText(hWnd, nItemIndex, _T("������ͣ��ʱ"));
				return FALSE;
			}
		}
	} while (bAgain);
	return TRUE;
}

BOOL CMainDialog::ServiceStartByName( HWND hWnd, int nItemIndex, TCHAR *szText )
{
	SetListItemText(hWnd, nItemIndex, _T("��������"));
	//��������
	CControlServiceEx serviceCon;
	int dwServiceStatus;//����״̬
	BOOL bAgain = TRUE;	//�Ƿ��ٴ�ѭ�� 
	int nAgainNum = 0;	//ѭ������
	CString strBuf;
	strBuf.Format(_T("��ʼ��������%s"), szText);
	WriteMessage(hWnd, strBuf);
	do 
	{
		dwServiceStatus = serviceCon.GetServiceStatus(szText);
		if (dwServiceStatus == SERVICE_RUNNING && nAgainNum == 0)	//������������
		{
			strBuf.Format(_T("%s����������,�����ٴ�����!"), szText);
			WriteMessage(hWnd, strBuf);
			strBuf = serviceCon.ServiceStatusToCString(SERVICE_RUNNING);
			SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());//�����ı�Ϊ������������
			strBuf.ReleaseBuffer();
			break;//�˳�ѭ��
		}
		switch(dwServiceStatus)
		{
		case -1:	//����δ��װ
			{
				if(FALSE == InstallService(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("��װ����ʱ���ִ���!"));
					strBuf.Format(_T("��װ����%sʱ���ִ���!�����ļ��Ƿ�����!�������°�װ������!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("����δ��װ"));
					return FALSE;
				}
			}
			break;
		case SERVICE_RUNNING:	//��������
			{
				strBuf.Format(_T("%s���������ɹ�!"), szText);
				WriteMessage(hWnd, strBuf);
				strBuf = serviceCon.ServiceStatusToCString(SERVICE_RUNNING);
				SetListItemText(hWnd, nItemIndex, strBuf.GetBuffer());
				strBuf.ReleaseBuffer();
				bAgain = FALSE;//������ѭ��
			}
			break;
		case SERVICE_STOPPED:	//��ֹͣ
		case SERVICE_CONTINUE_PENDING://����
		case SERVICE_PAUSED:	//��ͣ
			{
				if (FALSE == ServiceStart(szText))
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("��������ʱ��������!"));
					strBuf.Format(_T("��������%sʱ���ִ���!"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("��������ʧ��"));
					return FALSE;
				}
			}
			break;
		default:
			{
				strBuf.Format(_T("������������%s!"), szText);
				WriteMessage(hWnd, strBuf);
				if (nAgainNum % 4 == 0)
				{
					SetListItemText(hWnd, nItemIndex, _T("����������"));
				}
				else if(nAgainNum %4 == 1)
				{
					SetListItemText(hWnd, nItemIndex, _T("����������."));
				}
				else if(nAgainNum %4 == 2)
				{
					SetListItemText(hWnd, nItemIndex, _T("����������.."));
				}
				else if(nAgainNum %4 == 3)
				{
					SetListItemText(hWnd, nItemIndex, _T("����������..."));
				}
			}
			break;
		}
		nAgainNum ++;
		Sleep(1000);
		if (nAgainNum == 20)
		{

			if (dwServiceStatus == SERVICE_START_PENDING)//������������
			{
				if (nAgainNum == 60) //һ����
				{
					WRITE_LOG(LOG_LEVEL_ERROR, _T("��������ʱ������ʱ!"));
					strBuf.Format(_T("��������%s��ʱ!������"), szText);
					WriteMessage(hWnd, strBuf);
					SetListItemText(hWnd, nItemIndex, _T("����������ʱ"));
					return FALSE;
				}
			}
			else
			{
				WRITE_LOG(LOG_LEVEL_ERROR, _T("��������ʱ������ʱ!"));
				strBuf.Format(_T("��������%s��ʱ!������"), szText);
				WriteMessage(hWnd, strBuf);
				SetListItemText(hWnd, nItemIndex, _T("����������ʱ"));
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
	EnableWindow(hBtn, FALSE);	//���ð�ť

	HANDLE hThread = CreateThread(NULL, 0, ThreadRefreshServiceStatus, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadRefreshServiceStatus( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	pMainDlg->WriteMessage(hWnd, _T("��ʼˢ�·���״̬!"));
	pMainDlg->RefreshServiceStaus(hWnd);
	
	pMainDlg->WriteMessage(hWnd, _T("����״̬ˢ�����!"));
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_REFRESH);
	EnableWindow(hBtn, TRUE);	//���ð�ť
	return 1;
}

BOOL CMainDialog::BtnStartAllService( HWND hWnd )
{
	WriteMessage(hWnd, _T("��ʼ�������з���"));
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTALLSRTVICE);
	EnableWindow(hBtn, FALSE);	//���ð�ť

	HANDLE hThread = CreateThread(NULL, 0, ThreadStartAllService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadStartAllService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	//��ȡ�б�
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
				strBuf.Format(_T("��������%sʧ��,������������һ������!"), szText);
				pMainDlg->WriteMessage(hWnd, strBuf);
				Sleep(1000);
			}
		}
	} while (FALSE);
	pMainDlg->WriteMessage(hWnd, _T("�������з���������!"));
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STARTALLSRTVICE);
	EnableWindow(hBtn, TRUE);	//���ð�ť
	return 1;
}

BOOL CMainDialog::BtnStopAllService( HWND hWnd )
{
	BOOL bRet = TRUE;
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPALLSERVICE);
	EnableWindow(hBtn, FALSE);	//���ð�ť

	HANDLE hThread = CreateThread(NULL, 0, ThreadStopAllService, hWnd, 0, NULL);
	CloseHandle(hThread);
	return bRet;
}

DWORD WINAPI CMainDialog::ThreadStopAllService( LPVOID p )
{
	HWND hWnd = (HWND)p;
	CMainDialog *pMainDlg = CMainDialog::Instance();
	//��ȡ�б�
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
				strBuf.Format(_T("��ͣ����%sʧ��,��������ͣ��һ������!"), szText);
				pMainDlg->WriteMessage(hWnd, strBuf);
				Sleep(1000);
			}
		}
	} while (FALSE);
	pMainDlg->WriteMessage(hWnd, _T("��ͣ���з���������!"));
	HWND hBtn = GetDlgItem(hWnd, IDC_BTN_STOPALLSERVICE);
	EnableWindow(hBtn, TRUE);	//���ð�ť
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
		pMainDlg->m_nid.hIcon =  LoadIcon(pMainDlg->m_hInstance, MAKEINTRESOURCE(IDI_MiniIcon));	//����ͼ��
		Shell_NotifyIcon(NIM_MODIFY, &(pMainDlg->m_nid));
		pMainDlg->m_bIsFirstIcon = TRUE;
	}
}

