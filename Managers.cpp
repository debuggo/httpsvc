#include "FQ_Std.h"
#include "Managers.h"
#include "AppMain.h"
#include "Http.h"
#include "ChineseCode.h"
#include "mylog.h"
#include "Bt.h"
#include "Mzd.h"
#include "JsonEx.h"

CCriticalSectionLock		m_CriticalSectionLock;


int 	WINAPI		HttpFlagsSend(SOCKET	nSocket, DWORD	ulLen, CString	strType)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	char	SendBuffer[1024] = { 0 };
	__int64 ltime;
	struct tm *newtime;

	char	strTime[128] = { 0 };
	time((time_t*)&ltime);
	newtime = gmtime((time_t*)&ltime);
	strftime(strTime, 128,"%a, %d %b %Y %H:%M:%S GMT", newtime);

	if (strType == _T("html"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"text/html");
	}
	else if (strType == _T("htm"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"text/html");
	}
	else if (strType == _T("css"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"text/css");
	}
	else if (strType == _T("gif"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"image/gif");
	}
	else if (strType == _T("js"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"text/javascript");
	}
	else if (strType = _T("jpg"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"image/jpeg");
	}
	else if (strType = _T("xml"))
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"text/xml");
	}
	else
	{
		_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:FQServer\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:close\r\nContent-Type:%s\r\n\r\n",strTime,ulLen,"text/html");
	}

	int		nSend = 0;

	int iSendLen = strlen(SendBuffer);
	return pAppMain->m_Http.Http_SendMsg(nSocket,SendBuffer,iSendLen);
}


CManagers::CManagers(void)
{
}

CManagers::~CManagers(void)
{
}
//�����ӿ�
ULONG	WINAPI	CManagers::NoticeInterface(SOCKET sSocket, CString strPathFile)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	CString		strType, strFilePath;

	int nPos = strPathFile.ReverseFind('?');
	if (nPos == -1)
	{
		nPos = strPathFile.GetLength();
	}
	strFilePath = strPathFile.Left(nPos);
	nPos = strFilePath.ReverseFind('.');
	strType = strFilePath.Mid(nPos + 1);

	CString	strAppPath = CAppMain::GetAppPath() + _T("Notice\\");
	strAppPath += strFilePath;

	HANDLE	hFile = CreateFile(strAppPath.GetBuffer(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == (HANDLE)-1)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,_T("NoticeInterfaceû�ҵ��ļ���%s   �����룺%d"),strAppPath.GetBuffer(),GetLastError());
		pAppMain->m_Http.Http_Quest404(sSocket);
		return 0;
	}
	ULONG	ulFileLen = GetFileSize(hFile,NULL);
	//char*	lpszData = (char*)GlobalAlloc(GPTR,ulFileLen);
	char *lpszData = new char[ulFileLen];
	if (lpszData == NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,_T("NoticeInterface�޷������ڴ�	�����룺%d"),strAppPath.GetBuffer(),GetLastError());
		pAppMain->m_Http.Http_Quest404(sSocket);
		return 0;
	}
	HttpFlagsSend(sSocket,ulFileLen,strType);

	ULONG	ulRead;
	ReadFile(hFile,lpszData,ulFileLen,&ulRead,NULL);

	CloseHandle(hFile);

	pAppMain->m_Http.Http_SendMsg(sSocket,lpszData,ulFileLen);
	//GlobalFree(lpszData);
	delete []lpszData;
	return 0;
}
//����GET����
DWORD	WINAPI	CManagers::Get_Request(SOCKET	ClientSocket, CString	strFile)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	int nPos = strFile.ReverseFind('.');
	CString	StrFileType = strFile.Mid(nPos + 1);

	for (int i = 0; i < strFile.GetLength(); i++)
	{
		int nPos = strFile.Find('/');
		if (nPos == -1)
		{
			break;
		}
		strFile.SetAt(nPos,'\\');
	}
	HANDLE	hFile;
	DWORD	dwFile;
	pHtmlInfo	pHtmlFile = NULL;
	if (pAppMain->m_HtmlFile.m_Module)
	{
		pHtmlFile = pAppMain->m_HtmlFile.GetHtmlFile(strFile);
		if (pHtmlFile == NULL)
		{
			pAppMain->m_Http.Http_Quest404(ClientSocket);
			//closesocket(ClientSocket);
			return 0;
		}
		dwFile = pHtmlFile->ulFileLength;
	}
	else
	{
		CString		StrFileName = CAppMain::GetAppPath() + _T("Web\\");
		StrFileName += strFile;
		//BOOL	IsOpen = hFile.Open(StrFileName,CFile::shareDenyRead);
		hFile = CreateFile(StrFileName.GetBuffer(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (hFile == (HANDLE)-1)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,_T("�ļ���%s   �����룺%d"),StrFileName.GetBuffer(),GetLastError());
			pAppMain->m_Http.Http_Quest404(ClientSocket);
			//closesocket(ClientSocket);
			return 0;
		}
		//dwFile = hFile.GetLength();
		dwFile = GetFileSize(hFile,NULL);
	}

	HttpFlagsSend(ClientSocket,dwFile,StrFileType);

	int		nSend = 0;
	if (pHtmlFile != NULL)
	{
		nSend = pAppMain->m_Http.Http_SendMsg(ClientSocket,pHtmlFile->lpData,dwFile);
	}
	else
	{
		//char*	lpszData = (char*)GlobalAlloc(GPTR,dwFile);
		char *lpszData = new char[dwFile];
		//hFile.Read(lpszData,dwFile);
		//hFile.Close();
		DWORD	dwRead = 0;
		ReadFile(hFile,lpszData,dwFile,&dwRead,NULL);
		CloseHandle(hFile);
		nSend = pAppMain->m_Http.Http_SendMsg(ClientSocket,lpszData,dwFile);
		//GlobalFree(lpszData);
		delete []lpszData;
	}
	//closesocket(ClientSocket);
	return 0;
}

//WEB���ӿڴ���POST��Ϣ
DWORD	WINAPI	CManagers::Post_Request(SOCKET	sSocket,	char*	pHttpData,	int nLen)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	if (pAppMain->m_IsLog)
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,"����POST���� ��%s",pHttpData);
	}
	//WRITE_LOG(LOG_LEVEL_DEBUG,"����POST���� ��%s",pHttpData);
	char	szBuffer[12] = { 0 };
	char*	pData = pHttpData;
	memcpy(szBuffer,pData,5);
	pData += 5;
	int nCommand = atoi(szBuffer);
	int		nRet = 0;
	CString	strResult;
	int nJsonlen = ::MultiByteToWideChar(CP_UTF8,0,pData,nLen - 5,NULL,0);
	wchar_t*	pwzsBuffer = new wchar_t[nJsonlen + 1];
	//memset(pwzsBuffer,0,nJsonlen + 1);
	MultiByteToWideChar(CP_UTF8,0,pData,nLen - 5,pwzsBuffer,nJsonlen + 1);
	pwzsBuffer[nJsonlen] = 0;
	switch (nCommand)
	{
	case	30001:	//��½�ɹ�
		{
			sockaddr_in	sAddr = { 0 };
			int nAddr = sizeof(sockaddr_in);
			getpeername(sSocket,(SOCKADDR*)&sAddr,&nAddr);
			CString	strClientIp(inet_ntoa(sAddr.sin_addr));
			nRet = pAppMain->m_FQ.Web_UserLogin(strClientIp,pwzsBuffer,strResult);//WebUserInfo
			break;
		}
	case	30002:
		{
			nRet = pAppMain->m_FQ.Web_GetSubServer(strResult);	//����Ƿ��Ǵӷ�
			break;
		}
	case	30003:
		{
			nRet = pAppMain->m_FQ.Web_SaveRegInfo(pwzsBuffer,strResult);//RegInfoa	����ע����Ϣ
			break;
		}
	case	30004:
		{
			nRet = pAppMain->m_FQ.Web_StratBtServer(strResult);	 //����bt����
			break;
		}
	case	30005:
		{
			nRet = pAppMain->m_FQ.Web_StratMzdServer(strResult);	//����mzd
			break;
		}
	case	30006:		//����Ϊ�ӷ�
		{
			nRet = pAppMain->m_FQ.Web_SetSubServer(strResult);
			break;
		}
	case	30007:		//����Ϊ�ѵ�½
		{
			nRet = pAppMain->m_FQ.Web_LoginFlags(pwzsBuffer,strResult);
			break;
		}
	case	30008:	//��ȡ��½״̬
		{
			nRet = pAppMain->m_FQ.Web_GetLoginFlags(strResult);
			break;
		}
	case	30009:		//���ļ���
		{
			nRet = pAppMain->m_FQ.Web_OpenDir(pwzsBuffer,strResult);
			break;
		}
	case	30010:
		{
			nRet = pAppMain->m_FQ.Web_GetBtCurrentStatus(strResult);	//��ȡbt����״̬
			break;
		}
	case	30011:
		{
			nRet = pAppMain->m_FQ.Web_GetMZDCurrentStatus(strResult);		//��ȡmzd����״̬
			break;
		}
	case	40001://��ȡ������ȫ������
		{
			nRet = pAppMain->m_Mzd.Mzd_GetGlobal(strResult);//tagGetGlobalSetEx
			break;
		}
	case	40002://�޸�ȫ������
		{
			nRet = pAppMain->m_Mzd.Mzd_SetGlobal(pwzsBuffer,strResult);	//tagGetGlobalSetEx
			break;
		}
	case	40003://��ȡ���з�������Ϣ
		{
			nRet = pAppMain->m_Mzd.Mzd_GetSvrCfg(strResult);//tagServerCfg	
			break;
		}
	case	40004://�޸ķ���������(�°���Ϣ)
		{
			nRet = pAppMain->m_Mzd.Mzd_ModSvrCfg(pwzsBuffer,strResult);	//tagServerCfg
			break;
		}
	case	40005://��ӷ���������(�°���Ϣ)
		{
			nRet = pAppMain->m_Mzd.Mzd_AddSvrCfg(pwzsBuffer,strResult);	//tagServerCfg
			break;
		}
	case	40006: //ɾ������������(�°���Ϣ)
		{
			nRet = pAppMain->m_Mzd.Mzd_DelSvrCfg(pwzsBuffer,strResult);	//tagServerCfg
			break;
		}
	case	40007://��ȡָ������������������
		{
			nRet = pAppMain->m_Mzd.Mzd_GetDiskList(pwzsBuffer,strResult);	//IN tagServerName			OUT tagDiskSet
			break;
		}
	case	40008://��ȡ�����б�����
		{
			nRet = pAppMain->m_Mzd.Mzd_GetDiskNameList(strResult);//tagGetDisksetNameList
			break;
		}
	case	40009://�޸Ĵ�������
		{
			nRet = pAppMain->m_Mzd.Mzd_ModifyDiskCfg(pwzsBuffer,strResult);	//tagDiskSet
			break;
		}
	case	40010://ɾ����������
		{
			nRet = pAppMain->m_Mzd.Mzd_DelDiskCfg(pwzsBuffer,strResult);	//tagDiskSet
			break;
		}
	case	40011://��Ӵ�������
		{
			nRet = pAppMain->m_Mzd.Mzd_AddDiskCfg(pwzsBuffer,strResult);	//tagDiskSet
			break;
		}
	case	40012://��ȡ���й���վ
		{
			nRet = pAppMain->m_Mzd.Mzd_GetWksCfg(strResult);	//tagWkstationEx
			break;
		}
	case	40013://�޸Ĺ���վ
		{
			nRet = pAppMain->m_Mzd.Mzd_ModWksCfg(pwzsBuffer,strResult);	//tagWkstationEx	//�޸Ĺ���վ
			break;
		}
	case	40014://ɾ������վ
		{
			nRet = pAppMain->m_Mzd.Mzd_DelWksCfg(pwzsBuffer,strResult);	//tagWkstationEx
			break;
		}
	case	40015://��ӹ���վ
		{
			nRet = pAppMain->m_Mzd.Mzd_AddWksCfg(pwzsBuffer,strResult);	//tagAddWksInfo
			break;
		}
	case	40016: //ע������ 
		{
			nRet = pAppMain->m_Mzd.Mzd_Register(pwzsBuffer,strResult);	//tagMZDRegister	ע��mzd
			break;
		}
	case	40017://��ȡ�˵�����
		{
			nRet = pAppMain->m_Mzd.Mzd_GetAdaptMenu(strResult);//tagAdaptMenuSet
			break;
		}
	case	40018://��ȡӲ�����к�
		{
			nRet = pAppMain->m_Mzd.Mzd_GetPhysicalDiskId(strResult);//tagPhysicalDiskId
			break;
		}
	case	40019: //��ȡIMG��,����,������
		{
			nRet = pAppMain->m_Mzd.Mzd_GetImgPartitionPhysical(pwzsBuffer,strResult);	//IN tagServerIp	OUT tagImgResponse
			break;
		}
	case	40020://��ȡFIX�б�
		{
			nRet = pAppMain->m_Mzd.Mzd_GetFix(pwzsBuffer,strResult);	//IN tagGetFixListRequest	OUT tagFixResponse
			break;
		}
	case	40021://��ȡUDO�б�
		{
			nRet = pAppMain->m_Mzd.Mzd_GetUdo(pwzsBuffer,strResult);	//IN tagGetUdoListRequest	OUT tagUdoResponse
			break;
		}
	case	40022: //����ά������
		{
			nRet = pAppMain->m_Mzd.Mzd_DoDiskMaitainTask(pwzsBuffer,strResult);	//tagTask
			break;
		}
	case	40023://���ݷ���������ȡ�÷����������б�
		{
			nRet = pAppMain->m_Mzd.Mzd_GetDiskMaitainTaskList(pwzsBuffer,strResult);	//IN tagServerIp  OUT tagTask
			break;
		}
	case	40024:// ����վ����
		{
			nRet = pAppMain->m_Mzd.Mzd_WksCmd(pwzsBuffer,strResult);	//tagWksCmd
			break;
		}
	case	40025://��ȡ���з����������п���������
		{
			nRet = pAppMain->m_Mzd.Mzd_GetSrvAdpName(strResult);//tagServerAdaptName
			break;
		}
	case	40026: //��ȡ����״̬
		{
			nRet = pAppMain->m_Mzd.Mzd_GetServiceStatus(strResult);	//��ȡmzd����״̬
			break;
		}
	case	40027:	//������
		{
			nRet = pAppMain->m_Mzd.Mzd_ModWksCount(pwzsBuffer,strResult);//tagAddWksInfo
			break;
		}
	case	40028://��ȡ����������Ŀ¼״̬
		{
			nRet = pAppMain->m_Mzd.Mzd_CheckWorkDir(pwzsBuffer,strResult);//tagCheckServerWorkDir
			break;
		}
	case	40029://�������������
		{
			nRet = pAppMain->m_Mzd.Mzd_ServerCmd(pwzsBuffer,strResult);//tagServerCmd
			break;
		}
	case	40030: //��ȡ�÷�����ע����Ϣ
		{
			nRet = pAppMain->m_Mzd.Mzd_GetMZRegInfo(strResult);
			//�ж����ӷ�,�޸������ļ�
			if (strResult.Find(_T("serverType\":\"0\"")) == -1)
			{
				//Ϊ�ӷ�
				pAppMain->m_FQ.Web_SetServer();
			}
			else
			{
				CString strBuffer;
				pAppMain->m_FQ.Web_SetSubServer(strBuffer);
			}
			break;
		}
	case	40031://�������������
		{
			nRet = pAppMain->m_Mzd.Mzd_GetCacheInfo(pwzsBuffer,strResult);
			break;
		}
	case	40032:	//������
		{
			nRet = pAppMain->m_Mzd.Mzd_ModifyWksMac(pwzsBuffer,strResult);
			break;
		}
	case	50001://��ȡT_GamesInfo��Ϸ��Դ����		//
		{
			nRet = pAppMain->m_Bt.GetGameListInfo(pwzsBuffer,strResult);	//tagWksCmd
			break;
		}
	case	50002://��ȡT_WgsInf������������			//
		{
			nRet = pAppMain->m_Bt.GetWgsInfo(strResult);//T_WgsInfo
			break;
		}
	case	50003://��ȡT_ParentClass��������			//
		{
			nRet = pAppMain->m_Bt.GetParentClassInfo(pwzsBuffer, strResult);//T_ClassInfo
			break;
		}
	case	50004://��ȡT_SubClassС������			//
		{
			nRet = pAppMain->m_Bt.GetSubClassInfo(pwzsBuffer, strResult);//T_ClassInfo
			break;
		}
	case	50005://��ȡT_MovieInfo����				//
		{
			nRet = pAppMain->m_Bt.GetMovieInfo(strResult);//T_Movie
			break;
		}
	case	50006://��ȡT_Online����					//
		{
			nRet = pAppMain->m_Bt.GetOnlineInfo(strResult);//T_Online
			break;
		}
	case	50007://��ȡT_Player����					//
		{
			nRet = pAppMain->m_Bt.GetPlayerListInfo(strResult);//T_PlayerList
			break;
		}
	case	50008://����BT����						//
		{
			nRet = pAppMain->m_Bt.ConnectServ(strResult);
			break;
		}
	case	50009:
		{
			CString	strJson(pData);		//ע����֤
			nRet = pAppMain->m_Bt.UILogin(strJson,strResult);//UI_LOGING_USERPSW
			break;
		}
	case	50010:	//��ȡUI��¼��Ϣ					//
		{
			nRet = pAppMain->m_Bt.GetLoginInfo(strResult);//UI_LOGIN_REPLY
			break;
		}
	case	50011:	//����ͨ������ �ѷ���
		{
			CString	strJson;
			nRet = pAppMain->m_Bt.SetConnectPassword(strJson,strResult);
			break;
		}
	case	50012://ͬ������							//
		{
			nRet = pAppMain->m_Bt.SyncData(strResult);
			break;
		}
	case	50013://��ȡͬ������
		{
			nRet = pAppMain->m_Bt.GetSyncProgress(strResult);	//SYNC_DATA_PROGRESS
			break;
		}
	case	50014:	//��ȡbt����״̬
		{
			nRet = pAppMain->m_Bt.GetServerWorkStatus(strResult);	//��ȡbt����״̬
			break;
		}
	case	50015://��ȡBT������Ϣ					//
		{
			nRet = pAppMain->m_Bt.GetBtConfig(strResult);//BT_CONFIG_INFO
			break;
		}
	case	50016://����BT������Ϣ					//
		{
			nRet = pAppMain->m_Bt.SetBtConfig(pwzsBuffer,strResult);//BT_CONFIG_INFO
			break;
		}
	case	50017://��ȡ��Ϸ�˵�������Ϣ				//
		{
			nRet = pAppMain->m_Bt.GetMenuConfig(strResult);//MENU_CONFIG
			break;
		}
	case	50018:
		{
			nRet = pAppMain->m_Bt.SetMenuConfig(pwzsBuffer,strResult);//������Ϸ�˵�������Ϣ
			break;
		}
	case	50019://��ȡ�������ֹͣ���µ���Դ����	//
		{
			nRet = pAppMain->m_Bt.GameGetSuperfluousInfo(strResult);//RESOURCE_INFO
			break;
		}
	case	50020://��ȡ��Ϸɾ��˳������				//
		{
			nRet = pAppMain->m_Bt.GameGetDeleteSort(strResult);//GAME_DELETE_SORT
			break;
		}
	case	50021://��ȡBT��Դ������				//
		{
			nRet = pAppMain->m_Bt.GetSimpleProperty(pwzsBuffer,strResult);//GET_GAME_SIMPLE_PROPERTY
			break;
		}
	case	50022://����BT��Դ������				//
		{
			nRet = pAppMain->m_Bt.SetSimpleProperty(pwzsBuffer,strResult);//SET_GAME_SIMPLE_PROPERTY
			break;
		}
	case	50023://��ȡBTϵͳ�ſ���Ϣ				//
		{
			nRet = pAppMain->m_Bt.GetBtSystemInfo(strResult);	//BT_SYSTEM_INFO
			break;
		}
	case	50024://��ȡ��Դ��						//
		{
			nRet = pAppMain->m_Bt.GetResourceNumber(strResult);	//BT_RESOURCE_NUMBER
			break;
		}
	case	50025://ɾ����Դ							//
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.GameDelete(strJson,strResult);//int
			break;
		}
	case	50026:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.GameClearFileDir(strJson,strResult);//int
			break;
		}
	case	50027:
		{
			nRet = pAppMain->m_Bt.GameMoveDirectory(pwzsBuffer,strResult);//GAME_MOVE_DIRECTORY
			break;
		}
	case	50028:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.GameRepair(strJson,strResult);//int
			break;
		}
	case	50029:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.GameSetAutoUpdate(strJson,strResult);//int
			break;
		}
	case	50030:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.GameSetManualUpdate(strJson,strResult);	//int
			break;
		}
	case	50031:
		{
			nRet = pAppMain->m_Bt.AddCustomGame(pwzsBuffer,strResult);	//RESOURCE_PROPERTY
			break;
		}
	case	50032:
		{
			nRet = pAppMain->m_Bt.GetCustomGameMaxId(strResult);	//int
			break;
		}
	case	50033:
		{
			nRet = pAppMain->m_Bt.GetCustomGameProperty(pwzsBuffer,strResult);//IN int OUT RESOURCE_PROPERTY
			break;
		}
	case	50034:
		{
			nRet = pAppMain->m_Bt.ModifyCustomGameProperty(pwzsBuffer,strResult);	//RESOURCE_PROPERTY
			break;
		}
	case	50035:
		{
			nRet = pAppMain->m_Bt.DeleteCustomGame(pwzsBuffer,strResult);	//int
			break;
		}
	case	50036:
		{
			nRet = pAppMain->m_Bt.GetTaskInfo(strResult);		//TASK_INFO
			break;
		}
	case	50037:
		{
			nRet = pAppMain->m_Bt.TaskGetTrackerInfo(pwzsBuffer,strResult);	//TASK_INFO
			break;
		}
	case	50038:
		{
			nRet = pAppMain->m_Bt.TaskGetPeerInfo(pwzsBuffer,strResult);	//PACK_PEER_INFO_ENTRY
			break;
		}
	case	50039:
		{
			nRet = pAppMain->m_Bt.TaskAddDownload(pwzsBuffer,strResult);	//int
			break;
		}
	case	50040:
		{
			nRet = pAppMain->m_Bt.TaskSSDDownload(pwzsBuffer,strResult); //int
			break;
		}
	case	50041:
		{
			nRet = pAppMain->m_Bt.TaskPropertyDownload(pwzsBuffer,strResult);	//SET_GAME_SIMPLE_PROPERTY
			break;
		}
	case	50042:
		{
			nRet = pAppMain->m_Bt.TaskAddSeed(pwzsBuffer,strResult);	//TASK_SEED_DATA
			break;
		}
	case	50043:
		{
			nRet = pAppMain->m_Bt.TaskAddSeedSource(pwzsBuffer,strResult);	//ADD_SEED_SOURCE
			break;
		}
	case	50044:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskStart(strJson,strResult);//int
			break;
		}
	case	50045:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskStop(strJson,strResult);//int
			break;
		}
	case	50046:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskCheck(strJson,strResult);//int
			break;
		}
	case	50047:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskRemove(strJson,strResult);//int
			break;
		}
	case	50048:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskTop(strJson,strResult);//int
			break;
		}
	case	50049:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskUp(strJson,strResult);//int
			break;
		}
	case	50050:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskDown(strJson,strResult);//int
			break;
		}
	case	50051:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskLimitSpeed(strJson,strResult);//int
			break;
		}
	case	50052:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskSort(strJson,strResult);//int
			break;
		}
	case	50053:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.TaskRefreshTracker(strJson,strResult);//int
			break;
		}
	case	50054:
		{
			nRet = pAppMain->m_Bt.InsertGroup(pwzsBuffer,strResult);// IN GROUP_NAME
			break;
		}
	case	50055:
		{
			nRet = pAppMain->m_Bt.ModifyGroup(pwzsBuffer,strResult);//MODIFY_GROUP_NAME
			break;
		}
	case	50056:
		{
			nRet = pAppMain->m_Bt.DeleteGroup(pwzsBuffer,strResult);// IN GROUP_NAME
			break;
		}
	case	50057:
		{
			nRet = pAppMain->m_Bt.GetGroupInfo(strResult);//GroupInfo	//��ȡ����վ��Ϣ
			break;
		}
	case	50058:
		{
			nRet = pAppMain->m_Bt.GetWorkstationInfo(pwzsBuffer,strResult);//IN	GROUP_NAME			OUT		T_WorkstationInfo
			break;
		}
	case	50059:
		{
			nRet = pAppMain->m_Bt.GetServerInfo(pwzsBuffer,strResult);//IN	GROUP_NAME			OUT		T_ServerInfo
			break;
		}
	case	50060:
		{
			CString	strJson(pData);
			nRet = pAppMain->m_Bt.DeleteWorkstation(strJson,strResult);//COMPUTER_ID
			break;
		}
	case	50061:
		{
			nRet = pAppMain->m_Bt.DeleteServer(pwzsBuffer,strResult);//COMPUTER_NAME
			break;
		}
	case	50062:
		{
			nRet = pAppMain->m_Bt.GetWorkstationProperty(pwzsBuffer,strResult);//WORKSTATION_PROPERTY
			break;
		}
	case	50063:
		{
			nRet = pAppMain->m_Bt.SetWorkstationProperty(pwzsBuffer,strResult);//WORKSTATION_PROPERTY
			break;
		}
	case	50064:
		{
			nRet = pAppMain->m_Bt.GetServerProperty(pwzsBuffer,strResult);//SERVER_PROPERTY
			break;
		}
	case	50065:
		{
			nRet = pAppMain->m_Bt.SetServerProperty(pwzsBuffer,strResult);//SERVER_PROPERTY
			break;
		}
	case	50066:
		{
			nRet = pAppMain->m_Bt.GetDiskInfo(strResult);//DISK_INFO
			break;
		}
	case	50067:
		{
			nRet = pAppMain->m_Bt.GetFileDirectoryInfo(pwzsBuffer,strResult);// IN wchar_t			OUT FILE_DIRECTORY_INFO
			break;
		}
	case	50068:
		{
			nRet = pAppMain->m_Bt.GetFileDirectoryProperty(pwzsBuffer,strResult);// IN wchar_t			OUT FILE_DIRECTORY_PROPERTY
			break;
		}
	case	50069:
		{
			nRet = pAppMain->m_Bt.GetDirectorySize(pwzsBuffer,strResult);//IN	wchar_t			OUT DWORD
			break;
		}
	case	50070:
		{
			nRet = pAppMain->m_Bt.SetParentClassInfo(pwzsBuffer,strResult);//T_ClassInfo
			break;
		}
	case	50071:
		{
			nRet = pAppMain->m_Bt.SetSubClassInfo(pwzsBuffer,strResult);//T_ClassInfo
			break;
		}
	case	50072:
		{
			nRet = pAppMain->m_Bt.SetMovieInfo(pwzsBuffer,strResult);//T_Movie
			break;
		}
	case	50073:
		{
			nRet = pAppMain->m_Bt.SetOnlineInfo(pwzsBuffer,strResult);//T_Online
			break;
		}
	case	50074:
		{
			nRet = pAppMain->m_Bt.SetPlayerListInfo(pwzsBuffer,strResult);//T_PlayerList
			break;
		}
	case	50075:
		{
			nRet = pAppMain->m_Bt.StartSearch(pwzsBuffer,strResult);
			break;
		}
	case	50076:
		{
			nRet = pAppMain->m_Bt.StopSearch(strResult);
			break;
		}
	case	50077:
		{
			nRet = pAppMain->m_Bt.GetLocate(pwzsBuffer,strResult);//wchar_t
			break;
		}
	case	50078:
		{
			nRet = pAppMain->m_Bt.GetLocateStatus(pwzsBuffer,strResult);//GET_GAME_LOCATE_STATUS_REQUEST //GET_GAME_LOCATE_STATUS_REPLY
			break;
		}
	case	50079:
		{
			nRet = pAppMain->m_Bt.SetLocate(pwzsBuffer,strResult);//SET_GAME_LOCATE_INFO
			break;
		}
	case	50080:
		{
			nRet = pAppMain->m_Bt.GetSingleGameInfo(pwzsBuffer,strResult);
			break;
		}
	case	50081:
		{
			nRet = pAppMain->m_Bt.GetLimitTimePeriodInfo(strResult);
			break;
		}
	case	50082:
		{
			nRet = pAppMain->m_Bt.ClearBtRegInfo(strResult);
			break;
		}
	case	50083:
		{
			nRet = pAppMain->m_Bt.CoverLocate(strResult);
			break;
		}
	case	50084:
		{
			nRet = pAppMain->m_Bt.AddCustomWeb(pwzsBuffer,strResult);
			break;
		}
	case	50085:
		{
			nRet = pAppMain->m_Bt.SyncMzdWorkstation(strResult);
			break;
		}
	case	50086:
		{
			nRet = pAppMain->m_Bt.SyncMzdServer(strResult);
			break;
		}
	case	50087:
		{
			nRet = pAppMain->m_Bt.GetSingleParentClassName(pwzsBuffer,strResult);
			break;
		}
	case	50088:
		{
			nRet = pAppMain->m_Bt.GetSingleSubClassName(pwzsBuffer,strResult);
			break;
		}
	case	60001:	//��ȡ������Ӳ������
		{
			nRet = pAppMain->m_Bm.GetHardware(strResult);
			break;
		}
	case	60002:		//��ȡ����վ�¶���Ϣ
		{
			nRet = pAppMain->m_Bm.GetStatus(strResult);
			break;
		}
	case 60003:	//���Ӽ����Ϊ
		{
			/****************************************************************************************************
			����
			60003
			����
			{addlist:[addaction:{action_type:type,param1:param1,param2:param2,action_name:name},other:{...}]}
			����
			{listfortype:[action1:{...},action2:{...}]}                                                                     
			*****************************************************************************************************/
			pAppMain->m_Bm.AddMonitorAction(pwzsBuffer, strResult);
			break;
		}
	case 60004:	//ɾ�������Ϊ
		{
			/****************************************************************************************************
			����
			60004
			����
			{dellist:[addaction:{action_type:type,param1:param1,param2:param2,action_name:name},other:{...}]}
			����
			{listfortype:[action1:{...},action2:{...}]}
			*****************************************************************************************************/
			pAppMain->m_Bm.DelMonitorAction(pwzsBuffer, strResult);
			break;
		}
	case 60005:	//�޸ļ����Ϊ
		{
			/****************************************************************************************************
			����
			60005
			����
			{old:{action_type:tyep,param1:param1,param2:param2,action_name=name},new:{action_type:type,param1:param1,param2:param2,action_name:name}}
			����
			{listfortype:[action1:{...},action2:{...}]}
			*****************************************************************************************************/
			pAppMain->m_Bm.ChageMonitorAction(pwzsBuffer, strResult);
			break;
		}
	case 60006:	//��ѯ�����Ϊ
		{
			/****************************************************************************************************
			����
			60006
			����
			{action_type:type}
			����
			{listfortype:[action1:{...},action2:{...}]}
			*****************************************************************************************************/
			//������Ҫ���ַ�����ת��Ϊutf-8
			pAppMain->m_Bm.QueryMonitorAction(pwzsBuffer, strResult);
			break;
		}
	}
	delete []pwzsBuffer;
	if (pAppMain->m_IsLog)
	{
		WRITE_LOG(LOG_LEVEL_DEBUG,_T("������������ ��%s"),strResult.GetBuffer());
	}

	//WRITE_LOG(LOG_LEVEL_DEBUG,_T("������������ ��%s"),strResult.GetBuffer());
	DWORD	strLength = ::WideCharToMultiByte(CP_UTF8,0,strResult.GetBuffer(),strResult.GetLength(),NULL,0,NULL,NULL);
	//char*	szPostBuffer = (char*)GlobalAlloc(GPTR,strLength);
	char * szPostBuffer = new char[strLength];
	WideCharToMultiByte(CP_UTF8,0,strResult.GetBuffer(),strResult.GetLength(),szPostBuffer,strLength,NULL,NULL);
	//pClientSocket->Quest200(strLength);
	pAppMain->m_Http.Http_Quest200(sSocket,strLength);
		//pClientSocket->Send(szPostBuffer,strLength);
	pAppMain->m_Http.Http_SendMsg(sSocket,szPostBuffer,strLength);
	//GlobalFree(szPostBuffer);
	delete []szPostBuffer;
	//closesocket(sSocket);
	return 0;
}
