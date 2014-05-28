#include "FQ_Std.h"
#include "Http.h"
#include "AppMain.h"
#include "Managers.h"
#include "mylog.h"

MyStartListen			Http_Create;
MySendMsg				Http_Send;
MySendMsgAsyn			Http_AsynSend;

//IOCP回调函数
int		WINAPI	IocpCallBack(SOCKET sClient, char * pData, unsigned long DataLength, LPVOID lpParam)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	//char*	pszHttpData = (char*)GlobalAlloc(GPTR,409600);
	char *pszHttpData = new char[409600];
	if (pszHttpData == NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"%s","IocpCallBack接收数据缓存申请失败！");
		return 0;
	}
	CString	strFile;

	int		nLen = 0;
	int nRet = pAppMain->m_Http.PacketMessage(sClient,pData,strFile,pszHttpData,nLen);

	switch (nRet)
	{
	case	-1:
		{
			//closesocket(sClient);
			break;
		}
	case	1:
		{
			CManagers::Get_Request(sClient,strFile);
			break;
		}
	case	2:
		{
			CManagers::Post_Request(sClient,pszHttpData,nLen);
			break;
		}
	case	0:
		{
			break;
		}
	}
	//GlobalFree(pszHttpData);
	delete []pszHttpData;
	return 0;
}


CHttp::CHttp(void)
{
}

CHttp::~CHttp(void)
{
}


BOOL	WINAPI	CHttp::InitSocket()
{
	//CAppMain*	pAppMain = CAppMain::GetAppMain();
	//WSADATA	wsaData;
	//if (NULL != WSAStartup(MAKEWORD(2, 2), &wsaData))
	//{
	//	//pAppMain->m_LogFile.WriteLog("初始化 Socket 失败！");
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","初始化SOCKET失败！");
	//	//return	FALSE;
	//}
	//HMODULE	hLib = LoadLibrary(_T("SplIocp.dll"));
	//if (hLib == NULL)
	//{
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","加载SplIocp.dll失败");
	//	//return	FALSE;
	//}
	//Http_Create = (MyStartListen)GetProcAddress(hLib,"StartListen");
	//if (Http_Create == NULL)
	//{
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","加载StartListen失败");
	//	//return	FALSE;
	//}
	//Http_Send = (MySendMsg)GetProcAddress(hLib,"SendMsg");
	//if (Http_Send == NULL)
	//{
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","加载SendMsg失败");
	//	//return	FALSE;
	//}
	//Http_AsynSend = (MySendMsgAsyn)GetProcAddress(hLib,"SendMsgAsyn");
	//if (Http_AsynSend == NULL)
	//{
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","加载SendMsgAsyn失败");
	//	//return	FALSE;
	//}
	return TRUE;
}

//CClientSocket*	CHttp::GetSocketInfo(SOCKET Socket)
//{
//	CClientSocket* p = NULL;
//	//m_CriticalSectionLock.Lock();
//	Iter_Http	Iter = m_MapHttp.find(Socket);
//	if (Iter != m_MapHttp.end())
//	{
//		p =  Iter->second;
//	}
//	//m_CriticalSectionLock.UnLock();
//	return p;
//}
//
//void	CHttp::Close_Socket(SOCKET Socket)
//{
//	//m_CriticalSectionLock.Lock();
//	//Iter_Http	Iter = m_MapHttp.find(Socket);
//	//if (Iter != m_MapHttp.end())
//	//{
//	//	CClientSocket*	p = Iter->second;
//	//	closesocket(Socket);
//	//	m_MapHttp.erase(Iter);
//	//	FD_CLR(Socket,&m_fdSocket);
//	//	delete	p;
//	//}
//	//m_CriticalSectionLock.UnLock();
//}


//DWORD	WINAPI	CHttp::AcceptThreadProc(PVOID pData)
//{
//	CHttp*	pHttp = (CHttp*)pData;
//	CAppMain*	pAppMain = CAppMain::GetAppMain();
//	// 1）初始化一个套节字集合fdSocket，添加监听套节字句柄到这个集合
//	struct timeval Tv;
//	fd_set fdSocket;
//	Tv.tv_sec = 30;
//	Tv.tv_usec = 0;
//
//	FD_ZERO(&pHttp->m_fdSocket);
//
//	while(TRUE)
//	{       
//		FD_ZERO(&fdSocket);
//		FD_SET(pHttp->m_ServerSocket, &fdSocket);
//		for (int iCount = 0; iCount < pHttp->m_fdSocket.fd_count; iCount++)
//		{
//			if (pHttp->m_fdSocket.fd_array[iCount] != 0)
//			{
//				FD_SET(pHttp->m_fdSocket.fd_array[iCount],&fdSocket);
//			}
//		}
//
//		int nRet = ::select(0, &fdSocket, NULL, NULL, &Tv);
//		if(nRet > 0)
//		{
//			for(int i = 0; i < (int)fdSocket.fd_count; i++)
//			{
//				if(fdSocket.fd_array[i] == pHttp->m_ServerSocket)        // （1）监听套节字接收到新连接
//				{
//					if(fdSocket.fd_count < FD_SETSIZE)
//					{
//						sockaddr_in addrRemote;
//						int nAddrLen = sizeof(addrRemote);
//						SOCKET sNew = ::accept(pHttp->m_ServerSocket, (SOCKADDR*)&addrRemote, &nAddrLen);
//						CClientSocket*	pClient = CClientSocket::FromHandle(sNew);
//						if (pClient == NULL)
//						{
//							closesocket(sNew);
//							break;
//						}
//						FD_SET(sNew,&fdSocket);
//						FD_SET(sNew, &pHttp->m_fdSocket);
//						pHttp->m_MapHttp.insert(Map_Http::value_type(sNew,pClient));
//					}
//					continue;
//				}
//				else
//				{
//					for (int iS = 0; iS < pHttp->m_fdSocket.fd_count; iS++)
//					{
//						if (FD_ISSET(pHttp->m_fdSocket.fd_array[iS],&fdSocket))
//						{
//							CClientSocket*	pClient = pHttp->GetSocketInfo(pHttp->m_fdSocket.fd_array[iS]);
//							if (pClient == NULL)
//							{
//								continue;
//							}
//							int iResult = pClient->Receive();
//							if (iResult == -1)
//							{
//								pHttp->Close_Socket(pHttp->m_fdSocket.fd_array[iS]);
//								continue;
//							}
//							if (iResult == 1)
//							{
//								//pAppMain->m_ThreadPool.AddTask((FARPROC)&CManagers::Get_Request,pClient);
//								CManagers::Get_Request(pClient);
//								continue;
//							}
//							if (iResult == 2)
//							{
//								pAppMain->m_ThreadPool.AddTask((FARPROC)&CManagers::Post_Request,pClient);
//								//CManagers::Post_Request(pClient);
//								continue;
//							}
//							continue;
//						}
//					}
//				}
//			}
//		}
//	}
//	return 0;
//}

//开启HTTP服务
BOOL	CHttp::StartHttpServer(UINT nPort)
{
	//CAppMain*	pAppMain = CAppMain::GetAppMain();

	//m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	//if (m_ServerSocket == INVALID_SOCKET)
	//{
	//	WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","HTTP SOCKET创建失败！");
	//	return FALSE;
	//}

	//sockaddr_in	SocketAddr;
	//int Socketlen = sizeof(sockaddr_in);
	//memset(&SocketAddr,0,Socketlen);
	//SocketAddr.sin_family = AF_INET;
	//SocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//SocketAddr.sin_port = htons((u_short)nPort);

	//int iResult = 0;
	//iResult= bind(m_ServerSocket,(const sockaddr*)&SocketAddr,Socketlen);
	//if (iResult == SOCKET_ERROR)
	//{
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","HTTP SOCKET绑定失败！");
	//	closesocket(m_ServerSocket);
	//	return FALSE;
	//}
	//iResult = listen(m_ServerSocket,5);
	//if (iResult == SOCKET_ERROR)
	//{
	//	WRITE_LOG(LOG_LEVEL_FATAL,"%s","HTTP SOCKET监听失败！");
	//	closesocket(m_ServerSocket);
	//	return FALSE;
	//}
	//pAppMain->m_ThreadPool.AddTask((FARPROC)&AcceptThreadProc,this);

	//SYSTEM_INFO siSys;
	//GetSystemInfo(&siSys);

	//m_HttpIocp.iSvrPort1 = nPort;
	//m_HttpIocp.iSvrPort2 = nPort + 1;
	//m_HttpIocp.wThreadNum = siSys.dwNumberOfProcessors * 2;
	//m_HttpIocp.m_pProcessRecvData = IocpCallBack;
	////HttpIocp.m_lpVoid = (LPVOID)12345678;

	//int nErrorRet = Http_Create(&m_HttpIocp);
	//if (nErrorRet != NULL)
	//{
	//	return FALSE;
	//}
	WRITE_LOG(LOG_LEVEL_INFO,"开始SOCKET初始化");
	if (m_IocpSocket.Init() == -1)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"IOCP Init失败！");
		return FALSE;
	}
	if (m_IocpSocket.Create(nPort) == -1)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"IOCP Create失败！");
		return FALSE;
	}

	return	TRUE;
}

//开启公告板
BOOL	CHttp::StartNoticeHttp(UINT nPort)
{
	if (m_IocpSocket.InitNotice() == -1)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"InitNotice失败");
		return FALSE;
	}
	if (m_IocpSocket.Create(nPort) == -1)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"Create失败");
		return FALSE;
	}
	return TRUE;
}

int		CHttp::Http_Quest404(SOCKET	sSocket)
{
	char	SendBuffer[1024] = { 0 };

	int nLen = _snprintf((char*)SendBuffer,1024,"HTTP/1.1 404 OK\r\nServer:%s\r\nCache-Control:private\r\nContent-Type:%s\r\nContent-Length:%d\r\nConnection:Close\r\nContent-Type:text/html\r\n\r\n","FQServer","Bytes",0);

	int nErrorRet = m_IocpSocket.SendMsg(sSocket,SendBuffer,nLen);

	return nErrorRet;
}

int		CHttp::Http_Quest200(SOCKET sSocket, int nLen)
{
	char	SendBuffer[1024] = { 0 };
	__int64 ltime;
	struct tm *newtime;

	char	strTime[128] = { 0 };
	time((time_t*)&ltime);
	newtime = gmtime((time_t*)&ltime);
	strftime(strTime, 128,"%a, %d %b %Y %H:%M:%S GMT", newtime);

	int nDataLen = _snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:%s\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:%s\r\nContent-Type:text/html\r\n\r\n",strTime,"FQServer",nLen,"close");

	int nErrorRet = m_IocpSocket.SendMsg(sSocket,SendBuffer,nDataLen);

	return nErrorRet;
}

int		CHttp::Http_SendMsg(SOCKET sSocket, LPVOID lpData, int nLen)
{
	int nErrorRet = m_IocpSocket.SendMsg(sSocket,(char*)lpData,nLen);
	return nErrorRet;
}

//解析WEB消息和分析
int		CHttp::PacketMessage(SOCKET	sSocket, char*	pData, CString&	strFileName, char* pResultData, int& nLen)
{
	//WRITE_LOG(LOG_LEVEL_DEBUG,"%s",pData);

	char*	pEndPos = strstr(pData,"\r\n\r\n");
	pEndPos += strlen("\r\n\r\n");
	char* pPos = strstr(pData," ");
	if(pPos)
	{
		char	strMethod[MAX_PATH] = { 0 };
		memcpy(strMethod,pData,pPos - pData);
		if (strcmp(strMethod,"GET") == 0)
		{
			pPos++;
			char*	sznPos = strstr(pPos," ");
			if (sznPos)
			{
				char	szBuffer[128] = { 0 };
				memcpy(szBuffer,pPos,sznPos - pPos);
				if (strcmp(szBuffer,"/") == NULL)		//登陆
				{
					strFileName = _T("login.html");
					return 1;
				}
				else
				{
					char*	pPoint = strstr(szBuffer,"?");
					if (pPoint)
					{
						CString	strName(&szBuffer[1]);
						strFileName = strName;
						return 3;
					}
					else
					{
						CString	strName(&szBuffer[1]);
						strFileName = strName;
						return 1;
					}
				}
			}
			WRITE_LOG(LOG_LEVEL_ERROR,"GET请求无法找到文件。数据为：%s",pData);
			return -1;
		}
		if (strcmp(strMethod,"POST") == 0)
		{
			char*	pzsLength = strstr(pData,"Content-Length:");
			if (pzsLength)
			{
				pzsLength += strlen("Content-Length:");
				nLen = atoi(pzsLength);
				int nDataLen = strlen(pEndPos);
				if (nDataLen == NULL)
				{
					char*	pBuffer = new char[nLen];
					memset(pBuffer,0,nLen);
					char*	pTemp = pBuffer;
					int nRecvLen = 0;
					while (1)
					{
						if (nRecvLen != nLen)
						{
							int nRecv = recv(sSocket,pTemp,nLen,0);
							if (nRecv <= 0)
							{
								WRITE_LOG(LOG_LEVEL_ERROR,"recv数据错误。错误代码：%d",GetLastError());
								delete []pBuffer;
								return -1;
							}
							nRecvLen += nRecv;
							pTemp += nRecv;
							continue;
						}
						break;
					}
					memcpy(pResultData,pBuffer,nLen);
					delete []pBuffer;
				}
				else if (nDataLen < nLen)
				{
					char*	pBuffer = new char[nLen];
					memset(pBuffer,0,nLen);
					char*	pTemp = pBuffer;
					strcpy(pTemp,pEndPos);
					int nRecvLen = nDataLen;
					pTemp += nDataLen;
					while (1)
					{
						if (nRecvLen != nLen)
						{
							int nRecv = recv(sSocket,pTemp,nLen,0);
							if (nRecv <= 0)
							{
								WRITE_LOG(LOG_LEVEL_ERROR,"recv数据错误。错误代码：%d",GetLastError());
								delete []pBuffer;
								return -1;
							}
							nRecvLen += nRecv;
							pTemp += nRecv;
							continue;
						}
						break;
					}
					memcpy(pResultData,pBuffer,nLen);
					delete []pBuffer;
				}
				else
				{
					memcpy(pResultData,pEndPos,nLen);
				}
				return 2;
			}
		}
	}
	return -1;
}

//公告板的WEB消息解析
int		CHttp::PacketMessageByNotice(SOCKET sSocket, char *pData, CString &strFileName, char *pResultData, int &nLen)
{
	char*	pEndPos = strstr(pData,"\r\n\r\n");
	pEndPos += strlen("\r\n\r\n");
	char* pPos = strstr(pData," ");
	if(pPos)
	{
		char	strMethod[MAX_PATH] = { 0 };
		memcpy(strMethod,pData,pPos - pData);
		if (strcmp(strMethod,"GET") == 0)
		{
			pPos++;
			char*	sznPos = strstr(pPos," ");
			if (sznPos)
			{
				char	szBuffer[128] = { 0 };
				memcpy(szBuffer,pPos,sznPos - pPos);
				CString	strName(&szBuffer[1]);
				strFileName = strName;
				return 1;
			}
			WRITE_LOG(LOG_LEVEL_ERROR,"GET请求无法找到文件。数据为：%s",pData);
			return -1;
		}
	}
	return -1;
}