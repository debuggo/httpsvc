#include "FQ_Std.h"
#include "ControlService.h"
#include "mylog.h"

BOOL IsSystem64()
{
	SYSTEM_INFO info;
	GetNativeSystemInfo(&info);
	return (info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64);
}

CControlServiceEx::CControlServiceEx()
{
	//m_bIsSystem64 = FALSE;
	m_bIsSystem64 = IsSystem64();
}

CControlServiceEx::~CControlServiceEx()
{

}

//void COMM_WriteLogFile(LPCTSTR)
//{
//
//}
// 获取服务状态 
int   CControlServiceEx::GetServiceStatus(const TCHAR* pszServiceName)                         
{ 
	int iResult = 0; 
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_QUERY_LOCK_STATUS); 
	if (hScm != 0) 
	{ 
		SC_HANDLE hService = OpenService(hScm,pszServiceName,SERVICE_QUERY_STATUS); 
		if (hService != 0) 
		{ 
			SERVICE_STATUS stStatus; 
			memset(&stStatus, 0, sizeof(stStatus)); 
			QueryServiceStatus(hService, &stStatus); 
			//switch(stStatus.dwCurrentState) 
			//{ 
			//case SERVICE_CONTINUE_PENDING:   //0x00000005   服务继续等待。 
			//	break; 
			//case SERVICE_PAUSE_PENDING:      //0x00000006   的服务暂停正在等待。 
			//	break; 
			//case SERVICE_PAUSED:         //0x00000007   该服务已暂停。 
			//	break; 
			//case SERVICE_RUNNING:         //0x00000004   该服务正在运行。 
			//	break; 
			//case SERVICE_START_PENDING:      //0x00000002   服务正在启动。 
			//	break; 
			//case SERVICE_STOP_PENDING:      //0x00000003   该服务被停止。 
			//	break; 
			//case SERVICE_STOPPED:         //0x00000001   服务没有运行。 
			//	break; 
			//} 
			iResult = stStatus.dwCurrentState; 
			CloseServiceHandle(hService); 
		} 
		else iResult = 0; 
		CloseServiceHandle(hScm); 
	} 
	else iResult = -1; 
	return iResult; 
}
void	CControlServiceEx::SetSystemServiceInfo(TCHAR *pszServiceName,TCHAR*	pszDisplayName, TCHAR *pszDescription,TCHAR *pszFilePath)
{
	lstrcpy(m_szServiceName,pszServiceName);
	lstrcpy(m_szDescription,pszDescription);
	lstrcpy(m_szFilePath,pszFilePath);
	lstrcpy(m_szDisplayName,pszDisplayName);
}

int CControlServiceEx::SetSystemServiceFile()
{
	int nCmdVal = 0;
	HKEY hKey = 0;
	TCHAR tsFile[MAX_PATH];
	TCHAR tsBuff[MAX_PATH];
	//BOOL nSystem64 = IsSystem64();
	lstrcpy(tsBuff, _T("SYSTEM\\CurrentControlSet\\Services\\"));
	lstrcat(tsBuff, m_szServiceName);
	if ((RegOpenKeyEx(HKEY_LOCAL_MACHINE, tsBuff, 0, KEY_READ | KEY_WRITE | (m_bIsSystem64 == 0 ? 0 : KEY_WOW64_64KEY), &hKey)) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_EXPAND_SZ;
		DWORD dwLen = sizeof(tsBuff);
		*tsBuff = 0;
		RegQueryValueEx(hKey, _T("ImagePath"), 0, &dwType, (LPBYTE)tsBuff, &dwLen);
		//GetModuleFileName(0, tsFile, sizeof(tsFile)/sizeof(TCHAR));
		lstrcpy(tsFile, m_szFilePath);
		//_wcslwr_s(tsBuff,lstrlen(tsBuff));
		if (_tcsnicmp(tsBuff, _T("\\??\\"), 4) == 0)
			nCmdVal = (int)wcsstr(tsBuff + 4,tsFile);
		else
			nCmdVal = (int)wcsstr(tsBuff,tsFile);
		if (nCmdVal == 0)
			RegSetValueEx(hKey, _T("ImagePath"), 0, REG_EXPAND_SZ, (byte *)tsFile, (lstrlen(tsFile) + 1) * sizeof(TCHAR));
		RegCloseKey(hKey);
	}
	return nCmdVal;
}

int	CControlServiceEx::SetSystemServiceFileDll()
{
	int nCmdVal = 0;
	HKEY hKey = 0;
	DWORD dwValue = 0;
	DWORD dwLen = 0;
	TCHAR tsBuff[MAX_PATH];
	_stprintf(tsBuff, _T("SYSTEM\\CurrentControlSet\\Services\\%s\\Parameters"), m_szServiceName);
	if ((RegCreateKeyEx(HKEY_LOCAL_MACHINE, tsBuff, 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE | (m_bIsSystem64 == 0 ? 0 : KEY_WOW64_64KEY), 0, &hKey, 0)) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		dwLen = sizeof(tsBuff);
		*tsBuff = 0;
		RegQueryValueEx(hKey, _T("ServiceDll"), 0, &dwType, (LPBYTE)tsBuff, &dwLen);
		//GetModuleFileName(g_hInstance, tsFile, sizeof(tsFile)/sizeof(TCHAR));
		if (_tcsnicmp(tsBuff, _T("\\??\\"), 4) == 0)
			nCmdVal = lstrcmpi(tsBuff + 4, m_szFilePath);
		else
			nCmdVal = lstrcmpi(tsBuff, m_szFilePath);
		if (nCmdVal != 0)
			RegSetValueEx(hKey, _T("ServiceDll"), 0, REG_EXPAND_SZ, (byte *)m_szFilePath, (lstrlen(m_szFilePath) + 1) * sizeof(TCHAR));
		dwValue = 1;
		RegSetValueEx(hKey, _T("ServiceDllUnloadOnStop"), 0, REG_DWORD, (byte *)&dwValue, sizeof(dwValue));
		RegCloseKey(hKey);
	}
	if ((RegCreateKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Svchost"), 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE /*| (m_bIsSystem64 == 0 ? 0 : KEY_WOW64_64KEY)*/, 0, &hKey, 0)) == ERROR_SUCCESS)
	{
		lstrcpy(tsBuff, m_szServiceName);
		dwLen = lstrlen(tsBuff);
		tsBuff[dwLen + 1] = 0;
		RegSetValueEx(hKey, m_szServiceName, 0, REG_MULTI_SZ, (byte *)tsBuff, (dwLen + 2) * sizeof(TCHAR));
		RegCloseKey(hKey);
	}
	lstrcpy(tsBuff, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Svchost\\"));
	lstrcat(tsBuff, m_szServiceName);
	if ((RegCreateKeyEx(HKEY_LOCAL_MACHINE, tsBuff, 0, 0, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE /*| (m_bIsSystem64 == 0 ? 0 : KEY_WOW64_64KEY)*/, 0, &hKey, 0)) == ERROR_SUCCESS)
	{
		dwValue = 0;
		RegSetValueEx(hKey, _T("CoInitializeSecurityParam"), 0, REG_DWORD, (byte *)&dwValue, sizeof(dwValue));
		RegCloseKey(hKey);
	}
	return nCmdVal;
}

// 连接文件目录和文件名

// 创建服务
INT_PTR CControlServiceEx::CreateSystemService(SC_HANDLE hScm, bool bStart, bool bDll)
{
	//COMM_WriteLogFile(_T("CreateSystemService()"));
	INT_PTR nRet = 0;
	TCHAR szFile[MAX_PATH];
	if (bDll)
	{
		GetSystemDirectory(szFile, sizeof(szFile)/sizeof(TCHAR));
		lstrcat(szFile, m_szServiceName);
	}
	else
	{
		lstrcpy(szFile, m_szFilePath);
	}

	SC_HANDLE hService = CreateService(hScm, m_szServiceName, m_szDisplayName, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
		SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, szFile, 0, 0, 0, 0, 0);
	if (hService != 0)
	{
		if (m_szDescription != 0)
		{
			SERVICE_DESCRIPTION stDesc;
			stDesc.lpDescription = m_szDescription;
			ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &stDesc);
		}
		if (bDll)
			SetSystemServiceFileDll();
		else
			SetSystemServiceFile();

		if (bStart)
			nRet = StartService(hService, 0, 0);
		CloseServiceHandle(hService);
	}
	return nRet;
}

// 启动服务
INT_PTR CControlServiceEx::StartSystemService(bool bStart, bool bDll)
{
	INT_PTR nRet = 0;
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm != 0)
	{
		SC_HANDLE hService = OpenService(hScm, m_szServiceName, SERVICE_ALL_ACCESS);
		if (hService != 0)
		{
			//COMM_WriteLogFile(_T("OpenService success."));
			// 保证服务启动类型是自动
			GuaranteeServiceAtuoStart(hService);
			// 修改服务路径
			int nCmpVal = -1;
			if (bDll)
			{
				nCmpVal = SetSystemServiceFileDll();
			}
			else
			{
				nCmpVal = SetSystemServiceFile();
			}
			SERVICE_STATUS stStatus;
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState == SERVICE_STOPPED)// 如果服务已停止，启动
			{	
				if (bStart)
				{
					nRet = StartService(hService, 0, 0);
					//ATLASSERT(nRet);
				}
			}

			else if (stStatus.dwCurrentState == SERVICE_RUNNING)
			{	// 服务启动过程中（服务路径变化）
				ControlService(hService, SERVICE_CONTROL_STOP, &stStatus);
				// 停止服务
				for (int nLoop = 0; nLoop < 1000; nLoop++)
				{
					if (QueryServiceStatus(hService, &stStatus) != 0 && stStatus.dwCurrentState == SERVICE_STOPPED)
						break;
					Sleep(30);
				}
				// 重启服务
				if (stStatus.dwCurrentState == SERVICE_STOPPED)
				{
					if (bStart)
					{
						nRet = StartService(hService, 0, 0);
						//ATLASSERT(nRet);
					}
				}
				else
				{
					//ATLASSERT(FALSE);
				}
			}
			else
			{
				//ATLASSERT(FALSE);
			}
			CloseServiceHandle(hService);
		}
		else
		{
			// 服务不存在，创建新的服务
			nRet = CreateSystemService(hScm, bStart, bDll);
		}
		CloseServiceHandle(hScm);
	}
	else	
		//COMM_WriteLogFile(_T("OpenSCManager() failed."));
	return nRet;
}

// 停止服务
BOOL CControlServiceEx::StopSystemService()
{
	BOOL dbRet = 0;
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm != 0)
	{
		SC_HANDLE hService = OpenService(hScm, m_szServiceName, SERVICE_ALL_ACCESS);
		if (hService != 0)
		{
			SERVICE_STATUS stStatus;
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState != SERVICE_STOPPED)
				dbRet = ControlService(hService, SERVICE_CONTROL_STOP, &stStatus);
			CloseServiceHandle(hService);
		}
		CloseServiceHandle(hScm);
	}
	return dbRet;
}

// 删除服务
BOOL CControlServiceEx::DeleteSystemService()
{
	BOOL dbRet = 0;
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm != 0)
	{
		SC_HANDLE hService = OpenService(hScm, m_szServiceName, SERVICE_ALL_ACCESS);
		if (hService != 0)
		{
			SERVICE_STATUS stStatus;
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState != SERVICE_STOPPED)
				ControlService(hService, SERVICE_CONTROL_STOP, &stStatus);
			dbRet = DeleteService(hService);
			CloseServiceHandle(hService);
		}
		CloseServiceHandle(hScm);
	}
	return dbRet;
}

BOOL CControlServiceEx::GuaranteeServiceAtuoStart(SC_HANDLE hService)
{
	BOOL bRelust = FALSE;
	DWORD dwError = 0;
	DWORD dwBytesNeeded = 0;
	TCHAR szError[256];
	LPQUERY_SERVICE_CONFIG	lpqscBuf = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR,8*1024);
	if(NULL != lpqscBuf)
	{
		if (QueryServiceConfig(hService,lpqscBuf,8*1024,&dwBytesNeeded))//获取服务配置信息
		{
			switch(lpqscBuf->dwStartType)						//服务启动方式
			{
			case SERVICE_BOOT_START://0x00000000
				//COMM_WriteLogFile(_T("Service boot start."));	
				break;
			case SERVICE_SYSTEM_START://0x00000001
				//COMM_WriteLogFile(_T("Service system start."));	
				break;
			case SERVICE_AUTO_START://0x00000002				
				//COMM_WriteLogFile(_T("Servic auto start."));
				break;
			case SERVICE_DEMAND_START://0x00000003
				//COMM_WriteLogFile(_T("Service demand start."));
				break;
			case SERVICE_DISABLED://0x00000004
				//COMM_WriteLogFile(_T("Service disable."));
				break;
			default:
				//COMM_WriteLogFile(_T("Unknown Service type."));;
				break;
			}
			if(lpqscBuf->dwStartType == SERVICE_AUTO_START)
			{
				bRelust = TRUE;
			}
			else	//如果服务器当前不是自动启动方式
			{	
				if(ChangeServiceConfig(hService,SERVICE_NO_CHANGE,SERVICE_AUTO_START,SERVICE_NO_CHANGE,NULL,NULL,NULL,NULL,NULL,NULL,NULL))
				{
					bRelust = TRUE;
					//COMM_WriteLogFile(_T("Change service start type success!")); 
				}
				else
				{
					dwError = GetLastError();
					switch(dwError)
					{
					case ERROR_ACCESS_DENIED:
						//COMM_WriteLogFile(_T("Err:The handle does not have the SERVICE_CHANGE_CONFIG access right."));
						break;
					case ERROR_CIRCULAR_DEPENDENCY:
						//COMM_WriteLogFile(_T("Err:A circular service dependency was specified."));
						break;
					case ERROR_DUPLICATE_SERVICE_NAME:
						//COMM_WriteLogFile(_T("Err:The display name already exists in the service controller manager database, either as a service name or as another display name."));
						break;
					case ERROR_INVALID_HANDLE:
						//COMM_WriteLogFile(_T("Err:The specified handle is invalid."));
						break;
					case ERROR_INVALID_PARAMETER:
						//COMM_WriteLogFile(_T("Err:A parameter that was specified is invalid."));
						break;
					case ERROR_INVALID_SERVICE_ACCOUNT:
						//COMM_WriteLogFile(_T("Err:The account name does not exist, or a service is specified to share the same binary file as an already installed service but with an account name that is not the same as the installed service."));
						break;
					case ERROR_SERVICE_MARKED_FOR_DELETE:
						//COMM_WriteLogFile(_T("Err:The service has been marked for deletion."));
						break;
					default:
						{
							_stprintf(szError,_T("Err:[%d] Unknown Error A!"),dwError);
							//COMM_WriteLogFile(szError);
							break;
						}
					}
				}
			}
		}
		else
		{
			dwError = GetLastError();
			switch(dwError)
			{
			case ERROR_ACCESS_DENIED:
				//COMM_WriteLogFile(_T("Err:The handle does not have the SERVICE_QUERY_CONFIG access right."));
				break;
			case ERROR_INSUFFICIENT_BUFFER:
				//COMM_WriteLogFile(_T("Err:There is more service configuration information than would fit into the lpServiceConfig buffer. The number of bytes required to get all the information is returned in the pcbBytesNeeded parameter. Nothing is written to lpServiceConfig."));
				break;
			case ERROR_INVALID_HANDLE:
				//COMM_WriteLogFile(_T("Err:The specified handle is invalid."));
				break;
			default:
				{
					_stprintf(szError, _T("Err:[%d] Unknown Error B!"),dwError);
					//COMM_WriteLogFile(szError);
					break;
				}
			}
		}
		LocalFree(lpqscBuf);
	}
	return bRelust;
}


