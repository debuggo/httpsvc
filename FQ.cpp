#include "FQ_Std.h"
#include "FQ.h"
#include "AppMain.h"
#include "INet.h"
#include "ChineseCode.h"
#include "FQ_Crc.h"
#include "ControlService.h"
#include "VMProtectSDK.h"

extern "C" int WINAPI uncompress(BYTE * pDest, ULONG * pDestLen, BYTE * pSource, ULONG SourceLen);

CFQ::CFQ(void)
{
	BT_Timer = 0;
	Mzd_Timer = 0;
}

CFQ::~CFQ(void)
{
}


//初始化WEB
BOOL	CFQ::Web_Init()
{
	if (!m_JsonEx.InitStWeb())
	{
		return FALSE;
	}
	return TRUE;
}

int		CFQ::Web_OpenDir(CString strJson, CString& strResult)
{
	ShellExecute(NULL,_T("open"),strJson.GetBuffer(),_T(""),_T(""),SW_SHOW);
	strResult.Format(_T("0"));
	return 1;
}

int		CFQ::Web_LoginFlags(CString strJson, CString& strResult)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("LoginFlags"),strJson);

	strResult.Format(_T("0"));
	return 1;
}

int		CFQ::Web_GetLoginFlags(CString& strResult)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	CString	strVal = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("LoginFlags"));

	strResult.Format(_T("%s"),strVal.GetBuffer());
	return 1;
}

//WEB登陆
int		CFQ::Web_UserLogin(CString	strIp, CString strJson, CString& strResult)
{
	VMProtectBegin("Web_UserLogin");

	CAppMain*	pAppMain = CAppMain::GetAppMain();

	PVOID	lpStData = NULL;
	if (!m_JsonEx.ToStruct(strJson,_T("WebUserInfo"),&lpStData))
	{
		strResult.Format(_T("5000"));
		return -1;
	}
	WebUserInfo*	pUser = (WebUserInfo*)lpStData;

	int LoginFlags = _ttoi(pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("LoginFlags")));
	if (LoginFlags == 1)
	{
		int		nSuccess = 0;
		char hostname[128]; 
		gethostname(hostname,128);
		struct hostent *pHost = gethostbyname(hostname); 
		for (int i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++) 
		{
			CString	strCurrentIp(inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]));
			if (strCurrentIp == strIp)
			{
				nSuccess = 1;
				break;
			}
		}
		if (strIp == _T("127.0.0.1"))
		{
			nSuccess = 1;
		}
		if (nSuccess == 0)
		{
			strResult.Format(_T("90001"));
			return 0;
		}
	}


	CString	ManagementName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ManagementName"));
	CString	ManagementPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ManagementPassWord"));
	if (pUser->wzsUserName == ManagementName && pUser->wzsPassWord == ManagementPassWord)
	{
		strResult.Format(_T("1"));
		m_JsonEx.ToStructRelease(lpStData);
		return 1;
	}

	CString	BtUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("BtUserName"));
	CString	BtUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("BtUserPassWord"));
	if (pUser->wzsUserName == BtUserName && pUser->wzsPassWord == BtUserPassWord)
	{
		strResult.Format(_T("2"));
		m_JsonEx.ToStructRelease(lpStData);
		return 1;
	}

	CString	MzdUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("MzdUserName"));
	CString	MzdUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("MzdUserPassWord"));
	if (pUser->wzsUserName == MzdUserName && pUser->wzsPassWord == MzdUserPassWord)
	{
		strResult.Format(_T("3"));
		m_JsonEx.ToStructRelease(lpStData);
		return 1;
	}

	CString	ReadUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ReadUserName"));
	CString	ReadUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ReadUserPassWord"));
	if (pUser->wzsUserName == ReadUserName && pUser->wzsPassWord == ReadUserPassWord)
	{
		strResult.Format(_T("3"));
		m_JsonEx.ToStructRelease(lpStData);
		return 1;
	}
	strResult.Format(_T("0"));
	m_JsonEx.ToStructRelease(lpStData);

	VMProtectEnd();
	return 1;
}
//获取是不是从服
int		CFQ::Web_GetSubServer(CString& strResult)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	CString	strVal = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("IsSubServer"));

	strResult.Format(_T("%s"),strVal);
	return 1;
}
//设置为主服
int		CFQ::Web_SetSubServer(CString& strResult)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("IsSubServer"),_T("0"));

	strResult.Format(_T("0"));
	return 1;
}
//设置为从服
int		CFQ::Web_SetServer()
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("IsSubServer"),_T("1"));

	return 1;
}
//保存注册信息
int		CFQ::Web_SaveRegInfo(CString strJson, CString& strResult)
{
	VMProtectBegin("Web_SaveRegInfo");

	PVOID	lpStData = NULL;
	if (!m_JsonEx.ToStruct(strJson,_T("RegInfo"),&lpStData))
	{
		strResult.Format(_T("5000"));
		return -1;
	}
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	pRegInfo	pReg = (RegInfo*)lpStData;

	TCHAR	wzsNameBuffer[128];
	memset(wzsNameBuffer,0,128 * sizeof(TCHAR));
	int i = 0;
	int nName = lstrlen(pReg->wzsUserName);
	while (i < nName)
	{
		int nCode = pReg->wzsUserName[i];
		nCode = (nCode ^ 255) + 11;
		CString	strCode;
		strCode.Format(_T("%2X"),nCode);
		lstrcat(wzsNameBuffer,strCode.GetBuffer());
		i++;
	}
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegUserName"),wzsNameBuffer);

	TCHAR	wzsPassWordBuffer[128];
	memset(wzsPassWordBuffer,0,128 * sizeof(TCHAR));
	int ii = 0;
	int nPassWord = lstrlen(pReg->wzsUserPassWord);
	while (ii < nPassWord)
	{
		int nCode = pReg->wzsUserPassWord[ii];
		nCode = (nCode ^ 255) + 11;
		CString	strCode;
		strCode.Format(_T("%2X"),nCode);
		lstrcat(wzsPassWordBuffer,strCode.GetBuffer());
		ii++;
	}
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegUserPassWord"),wzsPassWordBuffer);

	TCHAR	wzsAgentIdBuffer[128];
	memset(wzsAgentIdBuffer,0,128 * sizeof(TCHAR));
	int iii = 0;
	int nAgentId = lstrlen(pReg->wzsAgentId);
	while (iii < nAgentId)
	{
		int nCode = pReg->wzsAgentId[iii];
		nCode = (nCode ^ 255) + 11;
		CString	strCode;
		strCode.Format(_T("%2X"),nCode);
		lstrcat(wzsAgentIdBuffer,strCode.GetBuffer());
		iii++;
	}
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegAgentName"),wzsPassWordBuffer);

	m_JsonEx.ToStructRelease(lpStData);
	strResult.Format(_T("0"));

	VMProtectEnd();
	return 1;
}
//重新启动BT服务
int		CFQ::Web_StratBtServer(CString &strResult)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	strRunDirectory = pAppMain->GetAppPath();

	TCHAR	wszBtPath[MAX_PATH] = { 0 };

	swprintf(wszBtPath,MAX_PATH,_T("%sbtsvc.exe"),strRunDirectory.GetBuffer());

	CControlServiceEx		ControlService;
	ControlService.SetSystemServiceInfo(_T("SPL_BTSVC"),_T("斯普林完美下载服务"),_T("斯普林完美下载服务为全自动更新游戏管理平台"),wszBtPath);
	ControlService.StartSystemService(true,true);
	strResult.Format(_T("0"));
	return 1;
}
//重启MZD服务
int		CFQ::Web_StratMzdServer(CString& strResult)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	strRunDirectory = pAppMain->GetAppPath();

	TCHAR	wszBtPath[MAX_PATH] = { 0 };

	swprintf(wszBtPath,MAX_PATH,_T("%smzdio.exe -S"),strRunDirectory.GetBuffer());

	CControlServiceEx		ControlService;
	ControlService.SetSystemServiceInfo(_T("SPL_MZDIO"),_T("斯普林名智磁盘服务"),_T("斯普林名智磁盘服务"),wszBtPath);
	ControlService.StartSystemService(true,false);
	strResult.Format(_T("0"));
	return 1;
}
//获取BT的状态
int		CFQ::Web_GetBtCurrentStatus(CString& strResult)
{
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm != NULL)
	{
		SC_HANDLE hService = OpenService(hScm, _T("SPL_BTSVC"), SERVICE_ALL_ACCESS);
		if (hService != NULL)
		{
			SERVICE_STATUS stStatus;
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState == SERVICE_RUNNING)
			{
				strResult.Format(_T("0"));
				return 1;
			}
		}
	}
	strResult.Format(_T("1"));
	return 0;
}
//获取MZD的状态
int		CFQ::Web_GetMZDCurrentStatus(CString& strResult)
{
	SC_HANDLE hScm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hScm != NULL)
	{
		SC_HANDLE hService = OpenService(hScm, _T("SPL_MZDIO"), SERVICE_ALL_ACCESS);
		if (hService != NULL)
		{
			SERVICE_STATUS stStatus;
			memset(&stStatus, 0, sizeof(stStatus));
			QueryServiceStatus(hService, &stStatus);
			if (stStatus.dwCurrentState == SERVICE_RUNNING)
			{
				strResult.Format(_T("0"));
				return 1;
			}
		}
	}
	strResult.Format(_T("1"));
	return 0;
}





CString	CFQ::FQ_UserLogin(CString	StrUser, CString	StrPassWord)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	StrResult;

	CTime	nCurrentTime = CTime::GetCurrentTime();
	INT64 KeyTime = nCurrentTime.GetTime() + 3600;

	CString	ManagementName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ManagementName"));
	CString	ManagementPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ManagementPassWord"));
	if (StrUser == ManagementName && StrPassWord == ManagementPassWord)
	{
		StrResult.Format(_T("1&nbsp%I64d&nbsp"),KeyTime);
		return StrResult;
	}

	CString	BtUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("BtUserName"));
	CString	BtUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("BtUserPassWord"));
	if (StrUser == BtUserName && StrPassWord == BtUserPassWord)
	{
		StrResult.Format(_T("2&nbsp%I64d&nbsp"),KeyTime);
		return StrResult;
	}

	CString	MzdUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("MzdUserName"));
	CString	MzdUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("MzdUserPassWord"));
	if (StrUser == MzdUserName && StrPassWord == MzdUserPassWord)
	{
		StrResult.Format(_T("3&nbsp%I64d&nbsp"),KeyTime);
		return StrResult;
	}

	CString	ReadUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ReadUserName"));
	CString	ReadUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("ReadUserPassWord"));
	if (StrUser == ReadUserName && StrPassWord == ReadUserPassWord)
	{
		StrResult.Format(_T("4&nbsp%I64d&nbsp"),KeyTime);
		return StrResult;
	}
	StrResult.Format(_T("0&nbsp账号或者密码错误！&nbsp"));
	return StrResult;
}

CString	CFQ::FQ_GetRegStatus()
{
	CString	StrResult;
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	StrRegUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserName"));
	CString	StrRegUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserPassWord"));
	if (StrRegUserName.IsEmpty() | StrRegUserPassWord.IsEmpty())
	{
		StrResult.Format(_T("1&nbsp0&nbsp"));
		return StrResult;
	}
	CString	StrHttpPost;
	StrHttpPost.Format(_T("mzp=%s&pwd=%s&debug=0"),StrRegUserName,StrRegUserPassWord);

	CStringA StrRetA = PostData(_T("ls.w918.com"), _T("LoadUserInfo.ashx"), StrHttpPost);

	char	DataBuffer[1024] = { 0 };
	ULONG	UlRetLen = StrRetA.GetLength();
	ULONG	BufferLen = sizeof(DataBuffer);
	int iRet = uncompress((BYTE*)DataBuffer,&BufferLen,(BYTE*)StrRetA.GetBuffer(),UlRetLen);
	TCHAR	WzsBuffer[1024] = { 0 };
	CChineseCode::Utf8ToUniCode(DataBuffer,WzsBuffer);
	CString	StrRegRetData(WzsBuffer);
	int FindnPos = StrRegRetData.Find(_T("value="));
	CString	StrTemp = StrRegRetData.Mid(FindnPos + strlen("value=") + 1);
	FindnPos = StrTemp.Find(_T(" message"));
	CString	StrFlag = StrTemp.Left(FindnPos - 1);
	if(StrFlag == _T("false"))
	{
		StrResult.Format(_T("1&nbsp0&nbsp"));
	}
	if (StrFlag == _T("true"))
	{
		int IdnPos = StrRegRetData.Find(_T("AgentNo="));
		CString	StrTempToo = StrRegRetData.Mid(IdnPos + strlen("AgentNo=") + 1);
		IdnPos = StrTempToo.Find(_T(" "));
		CString	StrAgentNo = StrTempToo.Left(IdnPos - 1);
		pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegAgentName"),StrAgentNo);
		StrResult.Format(_T("1&nbsp%s&nbsp"),StrAgentNo);
	}
	return StrResult;
}

CString	CFQ::FQ_UserReg(CString	UserName, CString	PassWord)
{
	CString	StrResult;
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	CString	StrHttpPost;
	StrHttpPost.Format(_T("mzp=%s&pwd=%s&debug=0"),UserName,PassWord);

	CStringA StrRetA = PostData(_T("ls.w918.com"), _T("LoadUserInfo.ashx"), StrHttpPost);

	char	DataBuffer[1024] = { 0 };
	ULONG	UlRetLen = StrRetA.GetLength();
	ULONG	BufferLen = sizeof(DataBuffer);
	int iRet = uncompress((BYTE*)DataBuffer,&BufferLen,(BYTE*)StrRetA.GetBuffer(),UlRetLen);
	TCHAR	WzsBuffer[1024] = { 0 };
	CChineseCode::Utf8ToUniCode(DataBuffer,WzsBuffer);
	CString	StrRegRetData(WzsBuffer);
	int FindnPos = StrRegRetData.Find(_T("value="));
	CString	StrTemp = StrRegRetData.Mid(FindnPos + strlen("value=") + 1);
	FindnPos = StrTemp.Find(_T(" message"));
	CString	StrFlag = StrTemp.Left(FindnPos - 1);
	if(StrFlag == _T("false"))
	{
		StrResult.Format(_T("1&nbsp0&nbsp"));
	}
	if (StrFlag == _T("true"))
	{
		int IdnPos = StrRegRetData.Find(_T("AgentNo="));
		CString	StrTempToo = StrRegRetData.Mid(IdnPos + strlen("AgentNo=") + 1);
		IdnPos = StrTempToo.Find(_T(" "));
		CString	StrAgentNo = StrTempToo.Left(IdnPos - 1);
		StrResult.Format(_T("1&nbsp%s&nbsp"),StrAgentNo);
	}
	return StrResult;
}

CString	CFQ::FQ_GetUserRegInfo(CString	StrServerName)
{
	CString	StrResult;
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString	StrRegUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserName"));
	CString	StrRegUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserPassWord"));
	CString	StrRegAgentName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegAgentName"));
	if (StrRegUserName.IsEmpty() | StrRegUserPassWord.IsEmpty() | StrRegAgentName.IsEmpty())
	{
		StrResult.Format(_T("0&nbsp"));
		return StrResult;
	}
	if (lstrcmpi(StrServerName,_T("BT")) == NULL)
	{
		if (BT_Timer == NULL)
		{
			StrResult.Format(_T("1&nbsp%s&nbsp%s&nbsp"),StrRegUserName,StrRegUserPassWord);
			return StrResult;
		}
	}

	if (lstrcmpi(StrServerName,_T("MZD")) == NULL)
	{
		if (Mzd_Timer == NULL)
		{
			StrResult.Format(_T("1&nbsp%s&nbsp%s&nbsp"),StrRegAgentName,StrRegUserPassWord);
			return StrResult;
		}
	}
}

int		CFQ::FQ_SetCommunicationPassWord(CString PassWord)
{
	if (PassWord.IsEmpty())
	{
		return 0;
	}
	CAppMain*	pAppMain  = CAppMain::GetAppMain();
	int nLength = PassWord.GetLength();

	char	szWordCode[32] = { 0 };
	int nlen = CChineseCode::UniCodeToAscii(szWordCode,PassWord.GetBuffer());

	ULONG	ulCode = pAppMain->m_Crc.GetCrc(szWordCode,nlen);
	CString	strForma;
	strForma.Format(_T("%X"),ulCode);
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("CommunicationPassWord"),strForma);

	pAppMain->m_CommunicationPassWord = strForma;
	return 1;
}

CString	CFQ::FQ_SaveReg(CString UserName, CString PassWord, CString RegAgentName)
{
	CString	strResult;
	if (UserName.IsEmpty())
	{
		strResult.Format(_T("0&nbsp0&nbsp"));
		return strResult;
	}
	if (PassWord.IsEmpty())
	{
		strResult.Format(_T("0&nbsp0&nbsp"));
		return strResult;
	}
	if (RegAgentName.IsEmpty())
	{
		strResult.Format(_T("0&nbsp0&nbsp"));
		return strResult;
	}
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegUserName"),UserName);
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegUserPassWord"),PassWord);
	pAppMain->m_IniFile.SetKeyValue(_T("FQ"),_T("RegAgentName"),RegAgentName);
	strResult.Format(_T("1&nbsp1&nbsp"));
	return	strResult;
}

int			CFQ::FQ_RegMessageInfo()
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	CString	strValue = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegInfo"));

	int	nResult = _ttoi(strValue);

	return nResult;
}


int		CFQ::FQ_Meesage(int iRequestFlag, char * pDataBuffer, CString &StrResult)
{
	int iResult = 0;

	switch (iRequestFlag)
	{
	case	FQ_Login:
		{
			int iSeparate = strlen("&nbsp");
			char	lpBuffer[64] = { 0 };
			char*	nPos = strstr(pDataBuffer,"&nbsp");
			if (nPos)
			{
				memcpy(lpBuffer,pDataBuffer,nPos - pDataBuffer);
				CString	strUser(lpBuffer);
				pDataBuffer += strlen(lpBuffer);
				pDataBuffer += iSeparate;
				memset(lpBuffer,0,64);
				char*	nPos = strstr(pDataBuffer,"&nbsp");
				if (nPos)
				{
					memcpy(lpBuffer,pDataBuffer,nPos - pDataBuffer);
					CString	StrPassWord(lpBuffer);
					pDataBuffer += strlen(lpBuffer);
					pDataBuffer += iSeparate;
					memset(lpBuffer,0,64);
					StrResult = FQ_UserLogin(strUser,StrPassWord);
					iResult = 1;
				}
			}
			break;
		}
	case	FQ_RegStatus:
		{
			StrResult = FQ_GetRegStatus();
			iResult = 1;
			break;
		}
	case	FQ_UserRegQuest:
		{
			int iSeparate = strlen("&nbsp");
			char*	pPos = NULL;
			char	szBuffer[128] = { 0 };
			pPos = strstr(pDataBuffer,"&nbsp");
			if (pPos)
			{
				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
				CString	StrUserName(szBuffer);
				pDataBuffer += strlen(szBuffer);
				pDataBuffer += iSeparate;
				memset(szBuffer,0,128);
				pPos = strstr(pDataBuffer,"&nbsp");
				if (pPos)
				{
					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
					CString	StrUserPassWord(szBuffer);
					pDataBuffer += strlen(szBuffer);
					pDataBuffer += iSeparate;
					memset(szBuffer,0,128);
					StrResult = FQ_UserReg(StrUserName,StrUserPassWord);
					iResult = 1;
					break;
				}
			}
			break;
		}
	case	FQ_RegUserInfo:
		{
			int iSeparate = strlen("&nbsp");
			char*	pPos = NULL;
			char	szBuffer[128] = { 0 };
			pPos = strstr(pDataBuffer,"&nbsp");
			if (pPos)
			{
				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
				CString	StrServerName(szBuffer);
				StrResult = FQ_GetUserRegInfo(StrServerName);
				iResult = 1;
				break;
			}
			break;
		}
	case	FQ_CommunicationPassWord:
		{
			int iSeparate = strlen("&nbsp");
			char*	pPos = NULL;
			char	szBuffer[128] = { 0 };
			pPos = strstr(pDataBuffer,"&nbsp");
			if (pPos)
			{
				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
				CString	StrPassWord(szBuffer);
				iResult = FQ_SetCommunicationPassWord(StrPassWord);
				StrResult.Format(_T("1&nbsp"));
			}
			break;
		}
	case	FQ_SaveRegInfo:
		{
			int iSeparate = strlen("&nbsp");
			char	lpBuffer[64] = { 0 };
			char*	nPos = strstr(pDataBuffer,"&nbsp");
			if (nPos)
			{
				memcpy(lpBuffer,pDataBuffer,nPos - pDataBuffer);
				CString	strUser(lpBuffer);
				pDataBuffer += strlen(lpBuffer);
				pDataBuffer += iSeparate;
				memset(lpBuffer,0,64);
				nPos = strstr(pDataBuffer,"&nbsp");
				if (nPos)
				{
					memcpy(lpBuffer,pDataBuffer,nPos - pDataBuffer);
					CString	StrPassWord(lpBuffer);
					pDataBuffer += strlen(lpBuffer);
					pDataBuffer += iSeparate;
					memset(lpBuffer,0,64);
					nPos = strstr(pDataBuffer,"&nbsp");
					if (nPos)
					{
						memcpy(lpBuffer,pDataBuffer,nPos - pDataBuffer);
						CString	strAgentId(lpBuffer);
						pDataBuffer += strlen(lpBuffer);
						pDataBuffer += iSeparate;
						memset(lpBuffer,0,64);

						StrResult = FQ_SaveReg(strUser,StrPassWord,strAgentId);
						iResult = 1;
						break;
					}
				}
			}
			break;
		}
	case	FQ_RegInfo:
		{
			int		nRet = FQ_RegMessageInfo();
			StrResult.Format(_T("1&nbsp%d&nbsp"),nRet);
			iResult = 1;
			break;
		}
	}
	return iResult;
}