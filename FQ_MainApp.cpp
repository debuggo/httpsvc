#include "FQ_Std.h"
#include "AppMain.h"
#include <WinSvc.h>
#include <Tlhelp32.h>
#include <DbgHelp.h>
#include "SplAutoUpdate.h"
#include "LogFile.h"
#include "ControlService.h"
#include "FQ_Crc.h"
#include "ServiceWindow.h"
#include "mylog.h"
#include "MzdTypedef.h"
#include <rpcsal.h> // MSDN的代码中这里没有包含这个头文件，导致编译不过
#include <crtdbg.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>
#include <netfw.h>
#include <Userenv.h>
#include <WtsApi32.h>
#include "WinFireWall.h"
#include "MainDialog.h"

#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "oleaut32.lib")
#pragma comment( lib, "Userenv.lib")
#pragma comment( lib, "WtsApi32.lib")

DWORD					lpOldHandler = NULL;
SERVICE_STATUS_HANDLE	m_hServiceStatus = NULL;
DWORD					m_MainThreadId = NULL;
BOOL					m_EixtFlags = TRUE;

HINSTANCE				m_hInstance = NULL;
HWND					m_hWnd = NULL;

HANDLE					m_SubProcess = NULL;
ULONG					m_ProcessId = 0;

typedef	BOOL (WINAPI *IMFJW_CreateEnvironmentBlock)(LPVOID *lpEnvironment, HANDLE hToken, BOOL bInherit);




void	WindowsFirewallCleanup(IN INetFwProfile *fwProfile)
{
	if (fwProfile != NULL)
	{
		fwProfile->Release();
	}
}

HRESULT WindowsFirewallIsOn(IN INetFwProfile *fwProfile, OUT BOOL *fwOn)
{
	HRESULT hr = S_OK;
	VARIANT_BOOL fwEnabled;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwOn != NULL);

	*fwOn = FALSE;

	hr = fwProfile->get_FirewallEnabled(&fwEnabled);
	if (FAILED(hr))
	{
		goto error;
	}

	if (fwEnabled != VARIANT_FALSE)
	{
		*fwOn = TRUE;
	}
error:
	return hr;
}

HRESULT WindowsFirewallTurnOn(IN INetFwProfile *fwProfile)
{
	HRESULT hr = S_OK;
	BOOL fwOn;

	_ASSERT(fwProfile != NULL);

	hr = WindowsFirewallIsOn(fwProfile, &fwOn);
	if (FAILED(hr))
	{
		goto error;
	}

	if (!fwOn)
	{
		hr = fwProfile->put_FirewallEnabled(VARIANT_TRUE);
		if (FAILED(hr))
		{
			goto error;
		}
	}
error:
	return hr;
}

HRESULT WindowsFirewallTurnOff(IN INetFwProfile *fwProfile)
{
	HRESULT hr = S_OK;
	BOOL fwOn;

	_ASSERT(fwProfile != NULL);

	hr = WindowsFirewallIsOn(fwProfile, &fwOn);
	if (FAILED(hr))
	{
		goto error;
	}

	if (fwOn)
	{
		hr = fwProfile->put_FirewallEnabled(VARIANT_FALSE);
		if (FAILED(hr))
		{
			goto error;
		}
	}
error:
	return hr;
}

HRESULT WindowsFirewallAppIsEnabled(IN INetFwProfile * fwProfile, IN const wchar_t *fwProcessImageFileName, OUT BOOL *fwAppEnabled)
{
	HRESULT hr = S_OK;
	BSTR fwBstrProcessImageFileName = NULL;
	VARIANT_BOOL fwEnabled;
	INetFwAuthorizedApplication *fwApp = NULL;
	INetFwAuthorizedApplications *fwApps = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwProcessImageFileName != NULL);
	_ASSERT(fwAppEnabled != NULL);

	*fwAppEnabled = FALSE;

	// 获取授权的程序集
	hr = fwProfile->get_AuthorizedApplications(&fwApps);
	if (FAILED(hr))
	{
		goto error;
	}

	fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
	if (fwBstrProcessImageFileName == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto error;
	}

	hr = fwApps->Item(fwBstrProcessImageFileName, &fwApp);
	if (SUCCEEDED(hr))
	{
		hr = fwApp->get_Enabled(&fwEnabled);
		if (FAILED(hr))
		{
			goto error;
		}

		if (fwEnabled != VARIANT_FALSE)
		{
			*fwAppEnabled = TRUE;
		}
		else
		{
		}
	}
	else
	{
		hr = S_OK;
	}

error:
	SysFreeString(fwBstrProcessImageFileName);
	if (fwApp != NULL)
	{
		fwApp->Release();
	}

	if (fwApps != NULL)
	{
		fwApps->Release();
	}
	return hr;
}

//************************************
// 方法名:	WindowsFirewallAddApp
// 全名称:	WindowsFirewallAddApp
// 访问级:	public 
// 返回值:	HRESULT
// 限定符:	
// 参  数:	IN INetFwProfile * fwProfile
// 参  数:	IN const wchar_t * fwProcessImageFileName
// 参  数:	IN const wchar_t * fwName
// 备  注:	往防火墙中添加程序
//************************************
//HRESULT WindowsFirewallAddApp(IN INetFwProfile *fwProfile, IN const wchar_t *fwProcessImageFileName, IN const wchar_t *fwName)
//{
//	HRESULT hr = S_OK;
//	BOOL fwAppEnabled;
//	BSTR fwBstrName = NULL;
//	BSTR fwBstrProcessImageFileName = NULL;
//	INetFwAuthorizedApplication *fwApp = NULL;
//	INetFwAuthorizedApplications *fwApps = NULL;
//
//	_ASSERT(fwProfile != NULL);
//	_ASSERT(fwProcessImageFileName != NULL);
//	_ASSERT(fwName != NULL);
//
//	hr = WindowsFirewallAppIsEnabled(fwProfile, fwProcessImageFileName, &fwAppEnabled);
//	if (FAILED(hr))
//	{
//		goto error;
//	}
//
//	if (!fwAppEnabled)
//	{
//		hr = fwProfile->get_AuthorizedApplications(&fwApps);
//		if (FAILED(hr))
//		{
//			goto error;
//		}
//
//		hr = CoCreateInstance(__uuidof(NetFwAuthorizedApplication), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwAuthorizedApplication), (void**)&fwApp);
//		if (FAILED(hr))
//		{
//			goto error;
//		}
//
//		fwBstrProcessImageFileName = SysAllocString(fwProcessImageFileName);
//		if (fwBstrProcessImageFileName == NULL)
//		{
//			hr = E_OUTOFMEMORY;
//			goto error;
//		}
//		hr = fwApp->put_ProcessImageFileName(fwBstrProcessImageFileName);
//		if (FAILED(hr))
//		{
//			goto error;
//		}
//
//		fwBstrName = SysAllocString(fwName);
//		if (SysStringLen(fwBstrName) == 0)
//		{
//			hr = E_OUTOFMEMORY;
//			goto error;
//		}
//
//		hr = fwApp->put_Name(fwBstrName);
//		if (FAILED(hr))
//		{
//			goto error;
//		}
//
//		hr = fwApps->Add(fwApp);
//		if (FAILED(hr))
//		{
//			goto error;
//		}
//	}
//
//error:
//	SysFreeString(fwBstrName);
//	SysFreeString(fwBstrProcessImageFileName);
//	if (fwApp != NULL)
//	{
//		fwApp->Release();
//	}
//	if (fwApps != NULL)
//	{
//		fwApps->Release();
//	}
//	return hr;
//}

HRESULT WindowsFirewallPortIsEnabled(IN INetFwProfile *fwProfile, IN LONG portNumber, IN NET_FW_IP_PROTOCOL ipProtocol, OUT BOOL *fwPortEnabled)
{
	HRESULT hr = S_OK;
	VARIANT_BOOL fwEnabled;
	INetFwOpenPort *fwOpenPort = NULL;
	INetFwOpenPorts *fwOpenPorts = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(fwPortEnabled != NULL);

	*fwPortEnabled = FALSE;

	hr = fwProfile->get_GloballyOpenPorts(&fwOpenPorts);
	if (FAILED(hr))
	{
		goto error;
	}

	// 获取端口的设备上下文
	hr = fwOpenPorts->Item(portNumber, ipProtocol, &fwOpenPort);
	if (SUCCEEDED(hr))
	{
		hr = fwOpenPort->get_Enabled(&fwEnabled);
		if (FAILED(hr))
		{
			goto error;
		}

		if (fwEnabled != VARIANT_FALSE)
		{
			*fwPortEnabled = TRUE;
		}
		else
		{
		}
	}
	else
	{
		hr = S_OK;
	}

error:
	if (fwOpenPort != NULL)
	{
		fwOpenPort->Release();
	}
	if (fwOpenPorts != NULL)
	{
		fwOpenPorts->Release();
	}
	return hr;
}


HRESULT WindowsFirewallPortAdd(IN INetFwProfile* fwProfile, IN LONG portNumber, IN NET_FW_IP_PROTOCOL ipProtocol, IN const wchar_t *name)
{
	HRESULT hr = S_OK;
	BOOL fwPortEnabled;
	BSTR fwBstrName = NULL;
	INetFwOpenPort *fwOpenPort = NULL;
	INetFwOpenPorts *fwOpenPorts = NULL;

	_ASSERT(fwProfile != NULL);
	_ASSERT(name != NULL);

	hr = WindowsFirewallPortIsEnabled(fwProfile,portNumber,ipProtocol,&fwPortEnabled);
	if (FAILED(hr))
	{
		goto error;
	}
	if (!fwPortEnabled)
	{
		hr = fwProfile->get_GloballyOpenPorts(&fwOpenPorts);
		if (FAILED(hr))
		{
			goto error;
		}

		hr = CoCreateInstance(__uuidof(NetFwOpenPort), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwOpenPort), (void**)&fwOpenPort);
		if (FAILED(hr))
		{
			goto error;
		}
		hr = fwOpenPort->put_Port(portNumber);
		if (FAILED(hr))
		{
			goto error;
		}
		hr = fwOpenPort->put_Protocol(ipProtocol);
		if (FAILED(hr))
		{
			goto error;
		}
		fwBstrName = SysAllocString(name);
		if (SysStringLen(fwBstrName) == 0)
		{
			hr = E_OUTOFMEMORY;
			goto error;
		}
		hr = fwOpenPort->put_Name(fwBstrName);
		if (FAILED(hr))
		{
			goto error;
		}
		hr = fwOpenPorts->Add(fwOpenPort);
		if (FAILED(hr))
		{
			goto error;
		}
	}
error:
	SysFreeString(fwBstrName);
	if (fwOpenPort != NULL)
	{
		fwOpenPort->Release();
	}
	if (fwOpenPorts != NULL)
	{
		fwOpenPorts->Release();
	}
	return hr;
}



BOOL EnableDebugPriv()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken( GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ))
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("OpenProcessToken失败错误码：%d"),GetLastError());
		return FALSE;
	}

	if ( ! LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("LookupPrivilegeValue失败错误码：%d"),GetLastError());
		CloseHandle( hToken );
		return FALSE;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if ( ! AdjustTokenPrivileges( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL ) )
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("AdjustTokenPrivileges失败错误码：%d"),GetLastError());
		CloseHandle( hToken );
		return FALSE;
	}
	return TRUE;
}

DWORD	WINAPI	CreateMiniIconProcess(PVOID	lpvoid)
{
	if(!EnableDebugPriv())
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,"调试权限失败");
	}

	DWORD	ExplorerPid = NULL;
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	Sleep(5000);

FindProcess:
	PROCESSENTRY32 pe = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL	report = Process32First(hSnapshot, &pe);
	while(report)
	{
		//WRITE_LOG(LOG_LEVEL_DEBUG,_T("%s"),pe.szExeFile);
		if (lstrcmpi(pe.szExeFile,_T("explorer.exe")) == NULL)
		{
			ExplorerPid = pe.th32ProcessID;
			break;
		}
		report = Process32Next(hSnapshot, &pe);
	}
	CloseHandle(hSnapshot); 
	if (ExplorerPid == NULL)
	{
		//WRITE_LOG(LOG_LEVEL_DEBUG,_T("没有找到"));
		BubbleData	bubble = { 0 };
		SOCKADDR_IN   local = { 0 };

		CAppMain*	pAppMain = CAppMain::GetAppMain();

		CString	strPort = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));
		int nPort = _ttoi(strPort);

		SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
		if (s == SOCKET_ERROR)
		{
			Sleep(1000);
			goto FindProcess;
		}
		local.sin_addr.s_addr = inet_addr("127.0.0.1");;   
		local.sin_family = AF_INET;  
		local.sin_port = htons(nPort);
		sendto(s,(char*)&bubble,sizeof(BubbleData),0,(SOCKADDR*)&local,sizeof(SOCKADDR_IN));
		Sleep(1000);
		goto FindProcess;
	}
	//WRITE_LOG(LOG_LEVEL_DEBUG,_T("explorer 找到 Pid : %d"),ExplorerPid);
	if (ExplorerPid == m_ProcessId)
	{
		Sleep(1000);
		goto FindProcess;
	}

	Sleep(3000);

	m_ProcessId = ExplorerPid;

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_PROCESS, FALSE, m_ProcessId);
	if (hProcess == NULL)
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("OpenProcess失败 : %d"),GetLastError());
		return 0;
	}

	HANDLE hToken = 0;
	OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY | TOKEN_EXECUTE | TOKEN_DUPLICATE, &hToken);
	if (hToken == NULL)
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("OpenProcessToken失败 : %d"),GetLastError());
		return 0;
	}

	//DWORD dwSessionID = WTSGetActiveConsoleSessionId();
	//HANDLE hToken = NULL; 
	//if (WTSQueryUserToken(dwSessionID, &hToken) == FALSE) 
	//{ 
	//	WRITE_LOG(LOG_LEVEL_DEBUG,_T("WTSQueryUserToken失败 : %d"),GetLastError());
	//	return 0;
	//} 
	HANDLE hDuplicatedToken = NULL; 
	if (DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hDuplicatedToken) == FALSE) 
	{ 
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("DuplicateTokenEx失败1 : %d"),GetLastError());
		return 0;
	} 
	DWORD dwSessionId = 0;
	ProcessIdToSessionId(m_ProcessId, &dwSessionId);

	DWORD dwCreationFlag = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
	LPVOID lpEnvironment = NULL; 
	if (CreateEnvironmentBlock(&lpEnvironment, hDuplicatedToken, FALSE) == NULL) 
	{ 
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("CreateEnvironmentBlock失败 : %d"),GetLastError());
		return 0;
	} 
	HANDLE hCurToken = 0;
	OpenProcessToken((HANDLE)-1, TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY | TOKEN_EXECUTE | TOKEN_DUPLICATE, &hCurToken);
	HANDLE hNewCurToken = 0;
	DuplicateTokenEx(hCurToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hNewCurToken);
	if (hNewCurToken == NULL)
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("DuplicateTokenEx失败2 : %d"),GetLastError());
		return 0;
	}
	SetTokenInformation(hNewCurToken, TokenSessionId, &dwSessionId, sizeof(dwSessionId));

	TCHAR	lpwzsBuffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,lpwzsBuffer,MAX_PATH);

	lstrcat(lpwzsBuffer,_T(" /MiniIcon 0"));

	STARTUPINFO sInfo;
	PROCESS_INFORMATION pInfo;
	ZeroMemory(&sInfo,sizeof(sInfo));
	sInfo.cb = sizeof(sInfo);
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_SHOWNORMAL;
	//sInfo.lpDesktop = L"Winsta0\\Default";


	if (CreateProcessAsUser(hNewCurToken,  NULL, lpwzsBuffer, NULL, NULL, FALSE, dwCreationFlag, lpEnvironment, NULL, &sInfo, &pInfo) == FALSE) 
	{ 
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("CreateProcessAsUser失败 : %d"),GetLastError());
		return 0;
	} 

	//HANDLE	ExplorerHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE,ExplorerPid);
	//if (ExplorerHandle == NULL)
	//{
	//	WRITE_LOG(LOG_LEVEL_DEBUG,_T("OpenProcess失败 : %d"),GetLastError());
	//	return 0;
	//}
	//HANDLE	ExplorerToken;
	//if (!OpenProcessToken(ExplorerHandle,TOKEN_ALL_ACCESS,&ExplorerToken))
	//{
	//	WRITE_LOG(LOG_LEVEL_DEBUG,_T("OpenProcessToken失败 : %d"),GetLastError());
	//	return 0;
	//}

	//TCHAR	lpwzsBuffer[MAX_PATH] = { 0 };
	//GetModuleFileName(NULL,lpwzsBuffer,MAX_PATH);

	//lstrcat(lpwzsBuffer,_T(" /MiniIcon"));

	////STARTUPINFO sInfo;
	//PROCESS_INFORMATION pInfo;
	////ZeroMemory(&sInfo,sizeof(sInfo));
	////sInfo.cb = sizeof(sInfo);
	////sInfo.dwFlags = STARTF_USESHOWWINDOW;
	////sInfo.wShowWindow = SW_SHOWNORMAL;

	//ZeroMemory(&pInfo,sizeof(pInfo));

	//STARTUPINFOW StartupInfo;

	//LoadUserProfile(ExplorerToken,0);
	//ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	//StartupInfo.cb = sizeof(StartupInfo);
	//StartupInfo.lpDesktop = L"winsta0\\default"; 
	//StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	//StartupInfo.wShowWindow = SW_SHOW;

	//LPVOID  pEnv = NULL;
	//DWORD dwCreationFlag = NORMAL_PRIORITY_CLASS;//NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;//
	//HMODULE hModule = LoadLibrary(L"Userenv.dll");
	//if(hModule )
	//{
	//	IMFJW_CreateEnvironmentBlock lpfnCreateEnvironmentBlock = (IMFJW_CreateEnvironmentBlock)GetProcAddress( hModule, "CreateEnvironmentBlock" );
	//	if (lpfnCreateEnvironmentBlock != NULL )
	//	{
	//		if(lpfnCreateEnvironmentBlock(&pEnv, ExplorerToken, FALSE))
	//		{
	//			dwCreationFlag |= CREATE_UNICODE_ENVIRONMENT;
	//		}
	//		else
	//		{
	//			pEnv = NULL;
	//		}
	//	}
	//	FreeLibrary(hModule);
	//}

	//if (!CreateProcessAsUser(ExplorerToken,NULL,lpwzsBuffer,NULL,NULL,FALSE,dwCreationFlag,pEnv,NULL,&StartupInfo,&pInfo))
	//{
	//	WRITE_LOG(LOG_LEVEL_DEBUG,_T("CreateProcessAsUser失败 : %d"),GetLastError());
	//	return 0;
	//}
	////CloseHandle(pInfo.hProcess);

	m_SubProcess = pInfo.hProcess;

	goto	FindProcess;

	return 0;
}

LONG WINAPI TopLevelExceptionFilter(EXCEPTION_POINTERS * pstEpt)
{	// 取得SYSTEM32完整路径并加载DLL（动态加载DLL必须使用完整路径，以免被病毒木马等钻漏洞）
	TCHAR tsFile[MAX_PATH];
	GetSystemDirectory(tsFile, sizeof(tsFile) / sizeof(TCHAR));
	lstrcat(tsFile, _T("\\DBGHELP.DLL"));
	HMODULE hLib = LoadLibrary(tsFile);
	if (hLib != 0)
	{
		BOOL (WINAPI * fnMiniDumpWriteDump) (HANDLE, DWORD, HANDLE, MINIDUMP_TYPE, PMINIDUMP_EXCEPTION_INFORMATION, PMINIDUMP_USER_STREAM_INFORMATION, PMINIDUMP_CALLBACK_INFORMATION);
		*(FARPROC *)&fnMiniDumpWriteDump = GetProcAddress(hLib, "MiniDumpWriteDump");
		if (fnMiniDumpWriteDump != 0)
		{	// 创建调试信息文件
			GetModuleFileName(NULL, tsFile, sizeof(tsFile)/sizeof(TCHAR));
			lstrcat(tsFile, _T(".dmp"));
			HANDLE hFile = CreateFile(tsFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, 0);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				MINIDUMP_EXCEPTION_INFORMATION stMdei;
				memset(&stMdei, 0, sizeof(stMdei));
				stMdei.ThreadId = GetCurrentThreadId();
				stMdei.ExceptionPointers = pstEpt;
				stMdei.ClientPointers = FALSE;
				// 生成最小的调试信息文件
				fnMiniDumpWriteDump((HANDLE)-1, GetCurrentProcessId(), hFile, (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory), &stMdei, 0, 0);
				// 生成完整的调试信息文件（会有几百兆）
				//fnMiniDumpWriteDump((HANDLE)-1, GetCurrentProcessId(), hFile, (MINIDUMP_TYPE)(MiniDumpWithFullMemory | MiniDumpWithFullMemoryInfo), &stMdei, 0, 0);
				CloseHandle(hFile);
			}
		}
		FreeLibrary(hLib);
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

VOID	WINAPI	ServiceStrl(DWORD dwOpcode)
{
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_STOP:
		{
//			BubbleData	bubble = { 0 };
//			SOCKADDR_IN   local = { 0 };
//
//			CAppMain*	pAppMain = CAppMain::GetAppMain();
//
//			CString	strPort = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("Port"));
//			int nPort = _ttoi(strPort);
//
//			SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);
//			if (s == SOCKET_ERROR)
//			{
//				WRITE_LOG(LOG_LEVEL_ERROR,L"创建SOCKET失败！");
//				goto	Jieshu;
//			}
//
//			local.sin_addr.s_addr = inet_addr("127.0.0.1");;   
//			local.sin_family = AF_INET;  
//			local.sin_port = htons(nPort);
//			sendto(s,(char*)&bubble,sizeof(BubbleData),0,(SOCKADDR*)&local,sizeof(SOCKADDR_IN));
//Jieshu:
			m_EixtFlags = FALSE;
			break;
		}
	case SERVICE_CONTROL_PAUSE:
		break;
	case SERVICE_CONTROL_CONTINUE:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		break;
	default:
		break;
	}
}

//服务入口点
VOID	WINAPI	ServiceMain(DWORD dwArgc,LPTSTR* lpszArgv)
{
	WRITE_LOG(LOG_LEVEL_INFO,"Entry ServiceMain");

	SERVICE_STATUS status;
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;	//可执行文件只有一个单独的服务
	status.dwCurrentState = SERVICE_START_PENDING;		//通知SCM服务正在初始化
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;	//服务只接受SERVICE_ACCEPT_STOP通知

	m_hServiceStatus = RegisterServiceCtrlHandler(_T("SPL_HTTPSVC"), ServiceStrl);	//注册回调
	if (m_hServiceStatus == NULL)
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","RegisterServiceCtrlHandler错误！");
		return;
	}
	WRITE_LOG(LOG_LEVEL_DEBUG,"注册服务监控成功");
	SetServiceStatus(m_hServiceStatus, &status);	//设置服务状态

	lpOldHandler = (DWORD)SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)TopLevelExceptionFilter);	//设置崩溃DUMP

	if (!pAppMain->InitInstance())	//初始化
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","InitInstance错误！");
		return;
	}
	//CreateMiniIconProcess();

	HANDLE	hThread = CreateThread(NULL,0,CreateMiniIconProcess,NULL,0,NULL);
	CloseHandle(hThread);
	Sleep(1000);

	status.dwWin32ExitCode = S_OK;
	status.dwCheckPoint = 0;
	status.dwWaitHint = 0;
	status.dwServiceSpecificExitCode = 0;
	status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(m_hServiceStatus, &status);

	while (m_EixtFlags)
	{
		Sleep(1000);
	}
	status.dwCurrentState = SERVICE_STOPPED;
	SetServiceStatus(m_hServiceStatus, &status);
	ExitProcess(0);
}


//************************************
// 方法名:	GetFileVersion
// 全名称:	GetFileVersion
// 访问级:	public 
// 返回值:	BOOL
// 限定符:	
// 参  数:	IN LPCTSTR strFile	需要检查的文件
// 参  数:	OUT CString & strVersion	版本信息
// 备  注:	获取文件版本
//************************************
BOOL GetFileVersion(LPCTSTR strFile, CString& strVersion)    
{       
	DWORD dwVerSize;    
	DWORD dwHandle;    
	BOOL bRes = FALSE;

	//获取版本大小
	dwVerSize = GetFileVersionInfoSize(strFile, &dwHandle);
	if (dwVerSize == 0)    
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"获取文件版本错误!");
		return FALSE;
	}
	//获取版本信息
	TCHAR* szVersionBuffer = new TCHAR[dwVerSize];
	if (GetFileVersionInfo(strFile, NULL, dwVerSize, szVersionBuffer) != NULL)
	{
		//解析版本信息
		VS_FIXEDFILEINFO * pInfo;    
		unsigned int nInfoLen;
		if (VerQueryValue(szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen)) 
		{ 
			TCHAR chVer[MAX_PATH];
			_stprintf(chVer, _T("%04d%04d%04d%04d"),    
				HIWORD(pInfo->dwFileVersionMS),
				LOWORD(pInfo->dwFileVersionMS),    
				HIWORD(pInfo->dwFileVersionLS),
				LOWORD(pInfo->dwFileVersionLS));
			strVersion = chVer;
			delete [] szVersionBuffer;
			return TRUE;
		}
	}
	
	WRITE_LOGLINE(LOG_LEVEL_FATAL,"获取文件版本信息错误!");
	delete [] szVersionBuffer;
	return FALSE;

}

DWORD	WINAPI	ToInternetProtocolW(wchar_t*	lpwszIp)
{
	DWORD	dwRet = 0;

	int		nAddress[4] = { 0 };
	swscanf(lpwszIp,_T("%d.%d.%d.%d"),&nAddress[0],&nAddress[1],&nAddress[2],&nAddress[3]);

	byte	bArray[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		bArray[i] = nAddress[i];
	}
	memcpy(&dwRet,bArray,sizeof(DWORD));
	return dwRet;
}

DWORD	WINAPI	ToInternetProtocolA(char*	lpszIp)
{
	DWORD	dwRet = 0;

	int		nAddress[4] = { 0 };
	sscanf(lpszIp,"%d.%d.%d.%d",&nAddress[0],&nAddress[1],&nAddress[2],&nAddress[3]);

	byte	bArray[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		bArray[i] = nAddress[i];
	}
	memcpy(&dwRet,bArray,sizeof(DWORD));
	return dwRet;
}

int		WINAPI	ToDwordByInternetProtocolW(DWORD	dwInDword, wchar_t*	lpwszOut)
{
	byte	bAddress[4] = { 0 };

	bAddress[0] = dwInDword;
	bAddress[1] = dwInDword >> 8;
	bAddress[2] = dwInDword >> 16;
	bAddress[3] = dwInDword >> 24;

	wsprintfW(lpwszOut,_T("%d.%d.%d.%d"),bAddress[0],bAddress[1],bAddress[2],bAddress[3]);
	return 1;
}

int		WINAPI	ToDwordByInternetProtocolA(DWORD	dwInDword, char*	lpszOut)
{
	byte	bAddress[4] = { 0 };

	bAddress[0] = dwInDword;
	bAddress[1] = dwInDword >> 8;
	bAddress[2] = dwInDword >> 16;
	bAddress[3] = dwInDword >> 24;

	wsprintfA(lpszOut,"%d.%d.%d.%d",bAddress[0],bAddress[1],bAddress[2],bAddress[3]);
	return 1;
}
//程序入口点
extern "C" int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;

	m_MainThreadId = GetCurrentThreadId();	//获取主线程ID	 该变量无用

	CString	StrVer;
	TCHAR	PathBuffer[MAX_PATH] = { 0 };			//运行路径 
	GetModuleFileName(NULL,PathBuffer,MAX_PATH);

	
	/////////////////////////////////设置防火墙-S/////////////////////////////////////////
	//HRESULT hr = S_OK;
	//HRESULT comInit = E_FAIL;
	//INetFwProfile *fwProfile = NULL;	//Windows防火墙接口
	//comInit = CoInitializeEx(0, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);	//初始化COM组件
	//if (comInit != RPC_E_CHANGED_MODE)
	//{
	//	hr = comInit;
	//	if (FAILED(hr))		//S_FALSE
	//	{
	//		WRITE_LOGLINE(LOG_LEVEL_FATAL, "初始化COM组件失败");
	//		return 0;
	//	}
	//}
	//TCHAR	wszSerivceName[MAXBYTE] = { 0 };
	//LoadString(NULL,IDS_ServiceName,wszSerivceName,MAXBYTE);
	//hr = WindowsFirewallInitialize(&fwProfile);	//初始化防火墙
	//if (!FAILED(hr))
	//{
	//	WindowsFirewallAddApp(fwProfile, PathBuffer,wszSerivceName);	//将程序加到防火墙中

	//}
	TCHAR	wszSerivceName[MAXBYTE] = { 0 };	//服务名
	LoadString(NULL,IDS_ServiceName,wszSerivceName,MAXBYTE);
	//全局初始化COM组件
	HRESULT comInit = E_FAIL;
	comInit = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (comInit != RPC_E_CHANGED_MODE)
	{
		if (FAILED(comInit))
		{
			WRITE_LOG(LOG_LEVEL_FATAL, "初始化COM组件失败");
			return 0;
		}
	}
	CWinFireWall firewall;
	FW_ERROR_CODE fw_err;	//初始化防火墙
	do 
	{
		if ((fw_err = firewall.InitializeFireWall()) != FW_NOERROR)
		{
			break;
		}

		if ((fw_err = firewall.AddApplication(PathBuffer, wszSerivceName)) != FW_NOERROR)
		{
			break;
		}
	
	} while (FALSE);
	if (fw_err != FW_NOERROR)
	{
		WRITE_LOG(LOG_LEVEL_WARN, "防火墙操作失败! ErrorCode :", fw_err);
	}
	/////////////////////////////////设置防火墙-E/////////////////////////////////////////

	timeBeginPeriod(1);	//设置定时器精确度

	/////////////////////自动更新-S/////////////////////////////////////////////////////
	UPDATEPARAMCLIENT	UpdateInfo;
	UpdateInfo.hInst = NULL;
	UpdateInfo.bProxy = false;
	UpdateInfo.bNotify = false;
	UpdateInfo.bWait = false;
	UpdateInfo.bLibray = true;

	if (!GetFileVersion(PathBuffer,StrVer))	//获取版本号	
	{
		return 0;
	}
	lstrcpy(UpdateInfo.pName,_T("httpsvc"));
	lstrcpy(UpdateInfo.pVer,StrVer.GetBuffer());
	lstrcpy(UpdateInfo.pType,_T("Web"));

	CAtuoUpdate* pUpdata = CAtuoUpdate::Instance();	//自动更新类
	pUpdata->StartUpdateClient(UpdateInfo);	//自动更新
	/////////////////////自动更新-E/////////////////////////////////////////////////////


	/////////////////////////////////读取命令行参数-S/////////////////////////////////////////
	if (strstr(lpCmdLine, "/InitSetPassWord") != NULL)	//设置通信密码
	{
		char*	szPsw = lpCmdLine + strlen("/InitSetPassWord") + 1;	//读取密码
		CAppMain*	pAppMain = CAppMain::GetAppMain();
		pAppMain->SetupAPI(szPsw);	//设置通信密码
		ExitProcess(0);
	}

	if (strstr(lpCmdLine,"/MiniIcon") != NULL)	//托盘显示
	{
		WRITE_LOG(LOG_LEVEL_FATAL, "开始进入托盘显示");
		lpCmdLine += strlen("/MiniIcon") + 1;
		int nShow = atoi(lpCmdLine);
		//CServiceWindow*	pServiceWindow = CServiceWindow::GetServiceWindow();
		//WRITE_LOG(LOG_LEVEL_FATAL, "开始创建窗口");
		//pServiceWindow->CreateServiceWindow(hInstance,nShow);	//服务管理界面
		CMainDialog *pMainDlg = CMainDialog::Instance();
		pMainDlg->CreateMainDialog(hInstance, nShow);
		WRITE_LOG(LOG_LEVEL_FATAL, "创建完成,退出程序!");
		ExitProcess(0);
	}

	if (strstr(lpCmdLine,"/Start") != NULL)	
	{
		CAppMain*	pAppMain = CAppMain::GetAppMain();
		SERVICE_TABLE_ENTRY st[] ={ _T("SPL_HTTPSVC"), (LPSERVICE_MAIN_FUNCTION)ServiceMain };	//服务入口
		if (!StartServiceCtrlDispatcher(st))	//启动服务
		{
			return 0;
		}
		return 0;
	}
	/////////////////////////////////读取命令行参数-E/////////////////////////////////////////

	/////////////////////////////////调试模式不启动服务-S/////////////////////////////////////////
#ifdef _DEBUG
	lpOldHandler = (DWORD)SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)TopLevelExceptionFilter);	//设置报错的dump
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	if (pAppMain->InitInstance())
	{
		Sleep(-1);
	}
	ExitProcess(0);
	/////////////////////////////////调试模式不启动服务-E/////////////////////////////////////////
#endif //
	TCHAR	lpwzsAppBuffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,lpwzsAppBuffer,MAX_PATH);
	CString	strServicePath(lpwzsAppBuffer);
	strServicePath += _T(" /Start");
	CControlServiceEx		m_ControlService;
	m_ControlService.SetSystemServiceInfo(_T("SPL_HTTPSVC"),wszSerivceName,wszSerivceName,strServicePath.GetBuffer());
	m_ControlService.StartSystemService(true,false);

	//HANDLE	FQ_ShangGuanXWHandle = NULL;
	//FQ_ShangGuanXWHandle = CreateMutex(NULL,FALSE,_T("FQ_ShangGuanXW"));
	//if (FQ_ShangGuanXWHandle)
	//{
	//	if (ERROR_ALREADY_EXISTS == GetLastError())
	//	{
	//		ExitProcess(0);
	//	}
	//}
	ExitProcess(0);
	return 0;
}