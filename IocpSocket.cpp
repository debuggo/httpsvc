#include "FQ_Std.h"
#include "IocpSocket.h"
#include "AppMain.h"
#include "Managers.h"
#include "FQ_ThreadPool.h"
#include "mylog.h"
#include <process.h>

CIocpSocket::CIocpSocket(void)
{
	m_bIsStart = 0;
}

CIocpSocket::~CIocpSocket(void)
{
	WSACleanup();
}

//IOCP工作线程
DWORD	WINAPI	CIocpSocket::AcceptWorkerThread(LPVOID lpvoid)
{
	CIocpSocket*	pIocpSocket = (CIocpSocket*)lpvoid;

	while (pIocpSocket->m_bIsStart)
	{
		pIocp_HandleData	pClient_Iocp_Handle = new Iocp_HandleData;	//关联完成端口用
		if (pClient_Iocp_Handle == NULL)
		{
			continue;
		}
		ZeroMemory(pClient_Iocp_Handle, sizeof(Iocp_HandleData));

		//接收数据
		int RemoteLen = sizeof(sockaddr_in);
		SOCKET	AcceptSocket = accept(pIocpSocket->m_ServerSocket,(sockaddr*)&pClient_Iocp_Handle->SocketAddr,&RemoteLen);
		if (AcceptSocket == SOCKET_ERROR)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"accept接收错误线程返回。错误代码：%d",GetLastError());
			delete pClient_Iocp_Handle;
			continue;
		}
		pClient_Iocp_Handle->Socket = AcceptSocket;
		
		HANDLE	Create_Io = CreateIoCompletionPort((HANDLE)AcceptSocket,pIocpSocket->m_hCompletionPort,(ULONG)pClient_Iocp_Handle,0);	//关联完成端口
		if (Create_Io == NULL)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"CreateIoCompletionPort绑定SOCKET失败，错误代码：%d",GetLastError());
			closesocket(AcceptSocket);
			delete(pClient_Iocp_Handle);
			continue;
		}


		pIocp_Io_Data	pClient_Iocp_Data = new Iocp_Io_Data;
		if (pClient_Iocp_Data == NULL)
		{
			closesocket(AcceptSocket);
			delete(pClient_Iocp_Handle);
			continue;
		}
		memset(pClient_Iocp_Data,0,sizeof(Iocp_Io_Data));


		pClient_Iocp_Data->DataBuf.buf = pClient_Iocp_Data->pDataBuffer;
		pClient_Iocp_Data->DataBuf.len = BufferSizoeof;
		pClient_Iocp_Data->OperationType = 0;
		DWORD Flags = 0;
		int nRecvCode = WSARecv(AcceptSocket,&pClient_Iocp_Data->DataBuf,1,(LPDWORD)&pClient_Iocp_Data->nRecvBytes,&Flags,&pClient_Iocp_Data->Overlapped,NULL);
		if (nRecvCode == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				WRITE_LOG(LOG_LEVEL_ERROR,"WSARecv设置SOCKET失败，错误代码：%d",GetLastError());
				closesocket(AcceptSocket);
				delete pClient_Iocp_Handle;
				delete pClient_Iocp_Data;
				continue;
			}
		}
		//pIocpSocket->m_Iocp_Handle.insert(Map_Iocp_Handle::value_type(AcceptSocket,pClient_Iocp_Handle));
		//pIocpSocket->m_Iocp_Io.insert(Map_Iocp_Io::value_type(AcceptSocket,pClient_Iocp_Data));
	}
	return 0;
}

//IOCP服务线程
 UINT WINAPI	CIocpSocket::ServerWorkerThread(LPVOID lpvoid)
 {
 	CIocpSocket*	pIocpSocket = (CIocpSocket*)lpvoid;
 	CAppMain*		pAppMain = CAppMain::GetAppMain();
 	DWORD				BytesTransferred; //接收到的大小
 	LPOVERLAPPED		lpOverlapped;	//overlapped结构
 	pIocp_HandleData	PerHandleData = NULL;	//密钥
 	pIocp_Io_Data		PerIoData = NULL; 
 	DWORD				SendBytes; 
 	DWORD				RecvBytes; 
 	DWORD				Flags; 
 	BOOL				bRet = FALSE;
	const int MAXDATABUF = 409600;
 	while (TRUE)
 	{
 		bRet = GetQueuedCompletionStatus(pIocpSocket->m_hCompletionPort, //端口
																&BytesTransferred,	//获取的大小
																(PULONG_PTR)&PerHandleData, //密钥
																(LPOVERLAPPED*)&lpOverlapped,//IOCP结构
																INFINITE//超时
																);
 		PerIoData = CONTAINING_RECORD(lpOverlapped,Iocp_Io_Data,Overlapped);	//获得结构基址
 		if(!bRet)
 		{ 
			WRITE_LOG(LOG_LEVEL_ERROR,"GetQueuedCompletionStatus失败，错误代码：%d",GetLastError());
 			closesocket(PerHandleData->Socket);
 			delete(PerHandleData);
 			delete(PerIoData);
 			continue;
 		}
 		if (BytesTransferred == 0)
 		{
			WRITE_LOG(LOG_LEVEL_ERROR,"GetQueuedCompletionStatus数据长度等于0，错误代码：%d",GetLastError());
 			closesocket(PerHandleData->Socket);
 			delete(PerHandleData);
 			delete(PerIoData);
 			continue;
 		}
 		switch(PerIoData->OperationType)
 		{
 		case	0://接收
 			{
				CString	strFileName;
				char*	pData = new char[MAXDATABUF];
				ZeroMemory(pData, MAXDATABUF);
				int		nLen = 0;
				int nErrorRet = pAppMain->m_Http.PacketMessage(PerHandleData->Socket,PerIoData->pDataBuffer,strFileName,pData,nLen);
				if (nErrorRet == -1)
				{
					WRITE_LOG(LOG_LEVEL_ERROR,"PacketMessage数据不对");
					closesocket(PerHandleData->Socket);
					delete []pData;
					delete(PerHandleData);
					delete(PerIoData);
					break;
				}
				if (nErrorRet == 1)
				{
					CManagers::Get_Request(PerHandleData->Socket,strFileName);
					closesocket(PerHandleData->Socket);
					delete []pData;
					delete(PerHandleData);
					delete(PerIoData);
					break;
				}
				if (nErrorRet == 2)	//获取到post请求
				{
					CManagers::Post_Request(PerHandleData->Socket,pData,nLen);
					closesocket(PerHandleData->Socket);
					delete []pData;
					delete(PerHandleData);
					delete(PerIoData);
					break;
				}
				if (nErrorRet == 3)
				{
					CManagers::NoticeInterface(PerHandleData->Socket,strFileName);
					closesocket(PerHandleData->Socket);
					delete []pData;
					delete(PerHandleData);
					delete(PerIoData);
					break;
				}
 				DWORD Flags = 0;
 				memset(PerIoData,0,sizeof(Iocp_Io_Data));
 				PerIoData->DataBuf.buf = PerIoData->pDataBuffer;
 				PerIoData->DataBuf.len = BufferSizoeof;
 				PerIoData->OperationType = 0;
 
 				int nRecvCode = WSARecv(PerHandleData->Socket,&PerIoData->DataBuf,1,(LPDWORD)&PerIoData->nRecvBytes,&Flags,&PerIoData->Overlapped,NULL);
 				if (nRecvCode == SOCKET_ERROR)
 				{
 					if (WSAGetLastError() != WSA_IO_PENDING)
 					{
 						closesocket(PerHandleData->Socket);
 					}
 				}
				delete []pData;
				break;
 			}
 		case	1://发送
 			{
				closesocket(PerHandleData->Socket);
 				delete(PerHandleData);
 				delete(PerIoData);
 				break;
 			}
 		}
 	}
 	return 0;
 }

DWORD	WINAPI	CIocpSocket::NoticeWorkerThread(LPVOID lpvoid)
{
	CIocpSocket*	pIocpSocket = (CIocpSocket*)lpvoid;
	CAppMain*		pAppMain = CAppMain::GetAppMain();

	DWORD				BytesTransferred; 
	LPOVERLAPPED		lpOverlapped; 
	pIocp_HandleData	PerHandleData = NULL; 
	pIocp_Io_Data		PerIoData = NULL; 
	DWORD				SendBytes; 
	DWORD				RecvBytes; 
	DWORD				Flags; 
	BOOL				bRet = FALSE;
	const int MAXDATABUF = 409600;

	while (TRUE)
	{
		bRet = GetQueuedCompletionStatus(pIocpSocket->m_hCompletionPort, &BytesTransferred,(PULONG_PTR)&PerHandleData,(LPOVERLAPPED*)&lpOverlapped, INFINITE);
		PerIoData = CONTAINING_RECORD(lpOverlapped,Iocp_Io_Data,Overlapped);
		if(!bRet)
		{ 
			WRITE_LOG(LOG_LEVEL_ERROR,"GetQueuedCompletionStatus失败，错误代码：%d",GetLastError());
			closesocket(PerHandleData->Socket);
			delete(PerHandleData);
			delete(PerIoData);
			continue;
		}
		if (BytesTransferred == 0)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"GetQueuedCompletionStatus数据长度等于0，错误代码：%d",GetLastError());
			closesocket(PerHandleData->Socket);
			delete(PerHandleData);
			delete(PerIoData);
			continue;
		}
		switch(PerIoData->OperationType)
		{
		case	0://接收
			{
				CString	strFileName;
				char*	pData = new char[MAXDATABUF];
				ZeroMemory(pData, MAXDATABUF);
				int		nLen = 0;
				int nErrorRet = pAppMain->m_Http.PacketMessageByNotice(PerHandleData->Socket,PerIoData->pDataBuffer,strFileName,pData,nLen);
				if (nErrorRet == -1)
				{
					WRITE_LOG(LOG_LEVEL_ERROR,"PacketMessageByNotice数据不对");
					closesocket(PerHandleData->Socket);
					delete []pData;
					delete(PerHandleData);
					delete(PerIoData);
					break;
				}
				if (nErrorRet == 1)
				{
					CManagers::NoticeInterface(PerHandleData->Socket,strFileName);
					closesocket(PerHandleData->Socket);
					delete []pData;
					delete(PerHandleData);
					delete(PerIoData);
					break;
				}
				DWORD Flags = 0;
				memset(PerIoData,0,sizeof(Iocp_Io_Data));
				PerIoData->DataBuf.buf = PerIoData->pDataBuffer;
				PerIoData->DataBuf.len = BufferSizoeof;
				PerIoData->OperationType = 0;

				int nRecvCode = WSARecv(PerHandleData->Socket,&PerIoData->DataBuf,1,(LPDWORD)&PerIoData->nRecvBytes,&Flags,&PerIoData->Overlapped,NULL);
				if (nRecvCode == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSA_IO_PENDING)
					{
						closesocket(PerHandleData->Socket);
					}
				}
				delete []pData;
				break;
			}
		case	1://发送
			{
				closesocket(PerHandleData->Socket);
				delete(PerHandleData);
				delete(PerIoData);
				break;
			}
		}
	}
	return 0;
}

//初始化IOCP
BOOL	CIocpSocket::Init()
{
	WRITE_LOG(LOG_LEVEL_INFO, "IocpSocket Init 开始");
	WSAData wsaData = { 0 };
	int nErr = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(nErr != 0)
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL, "启动Windows套接字失败.\r\nErroeCode : %X", nErr);
		return FALSE;
	}
	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL, "无法找到Winsock.dll.");
		WSACleanup();
		return FALSE;
	}
	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);	//创建IO完成端口
	if (m_hCompletionPort == NULL)
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL, "创建I/O完成端口失败.\r\nErroeCode : %X", GetLastError());
		WSACleanup();
		return FALSE;
	}
	//获取CPU数目
	SYSTEM_INFO siSys;
	GetSystemInfo(&siSys);
	//创建一定数目的工作者线程，本例中以一个处理器一个线程搭配
 	for(int i = 0;i < (int)siSys.dwNumberOfProcessors * 2; i++)//NumberOfProcessors
 	{
 		HANDLE hThread = NULL;
 		//hThread = CreateThread(NULL,0,ServerWorkerThread,this,0,NULL);
 		hThread = (HANDLE)_beginthreadex(NULL,0,ServerWorkerThread,this,0,NULL);
		if (!hThread)
		{
			WRITE_LOGLINE(LOG_LEVEL_FATAL, "创建线程失败 ! \r\nErrorCode : %X", GetLastError());
			return FALSE;
		}
 		CloseHandle(hThread);
 	}
	WRITE_LOG(LOG_LEVEL_INFO, "IocpSocket Init 结束");
	return TRUE;
}

//初始化公告板
BOOL	CIocpSocket::InitNotice()
{
	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);
	if (m_hCompletionPort == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	//获取CPU数目
	SYSTEM_INFO siSys;
	GetSystemInfo(&siSys);
	//创建一定数目的工作者线程，本例中以一个处理器一个线程搭配
	for(int i = 0;i < (int)siSys.dwNumberOfProcessors * 2; i++)//NumberOfProcessors
	{
		HANDLE hThread = NULL;
		hThread = CreateThread(NULL,0,NoticeWorkerThread,this,0,NULL);
		CloseHandle(hThread);
	}

	return 0;
}


//创建SOCKET
int		CIocpSocket::Create(UINT nPort)
{
	WRITE_LOG(LOG_LEVEL_INFO, "IocpSocket Create 开始");

	m_ServerSocket = socket(AF_INET,SOCK_STREAM,0);
	if (m_ServerSocket == SOCKET_ERROR)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"socket 创建失败");
		return -1;
	}

	int nReuseAddr = 1;
	if(setsockopt(m_ServerSocket,SOL_SOCKET,SO_REUSEADDR,(const char *)&nReuseAddr,sizeof(int)) != 0)
	{
		closesocket(m_ServerSocket);
		return -1;
	}

	sockaddr_in	Addr = { 0 };
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(nPort);
	Addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(m_ServerSocket,(struct sockaddr *)&Addr,sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"socket 绑定失败");
		closesocket(m_ServerSocket);
		return -1;
	}

	if (listen(m_ServerSocket,5) == SOCKET_ERROR)
	{
		closesocket(m_ServerSocket);
		return -1;
	}
	m_bIsStart = TRUE;

	HANDLE	AcceptThread = CreateThread(NULL,0,AcceptWorkerThread,this,0,NULL);
	CloseHandle(AcceptThread);

	WRITE_LOG(LOG_LEVEL_INFO, "IocpSocket Create 结束");
	return 1;
}

int	CIocpSocket::AsynSendMsg(SOCKET	Socket,LPVOID lpData,int nlen)
{
	//pIocp_Io_Data	pSend_Iocp_Data = (pIocp_Io_Data)GlobalAlloc(GPTR,sizeof(Iocp_Io_Data));
	pIocp_Io_Data pSend_Iocp_Data = new Iocp_Io_Data;
	if (pSend_Iocp_Data == NULL)
	{
		return -1;
	}

	memcpy(pSend_Iocp_Data->pDataBuffer,lpData,nlen);

	pSend_Iocp_Data->DataBuf.buf = pSend_Iocp_Data->pDataBuffer;
	pSend_Iocp_Data->DataBuf.len = nlen;
	pSend_Iocp_Data->OperationType = 1;

	int nCode = WSASend(Socket,&pSend_Iocp_Data->DataBuf,1,(LPDWORD)&pSend_Iocp_Data->nSendBytes,0,&pSend_Iocp_Data->Overlapped,NULL);
	if (nCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			delete pSend_Iocp_Data;
			closesocket(Socket);
			return -1;
		}
	}
	delete pSend_Iocp_Data;
	return nlen;
}

int		CIocpSocket::SendMsg(SOCKET Socket,LPVOID lpData,int nlen)
{
	return send(Socket,(char*)lpData,nlen,0);
}

int	CIocpSocket::Quest404(SOCKET	Socket)
{
	char	SendBuffer[1024] = { 0 };
	
	_snprintf((char*)SendBuffer,1024,"HTTP/1.1 404 OK\r\nServer:%s\r\nCache-Control:private\r\nContent-Type:%s\r\nContent-Length:%d\r\nConnection:Close\r\nContent-Type:text/html\r\n\r\n","FQServer","Bytes",0);

	return SendMsg(Socket,SendBuffer,strlen(SendBuffer));
}

int CIocpSocket::Quest200(SOCKET Socket, DWORD dwFile)
{
	char	SendBuffer[1024] = { 0 };
	__int64 ltime;
	struct tm *newtime;

	char	strTime[128] = { 0 };
	time((time_t*)&ltime);
	newtime = gmtime((time_t*)&ltime);
	strftime(strTime, 128,"%a, %d %b %Y %H:%M:%S GMT", newtime);

	_snprintf((char*)SendBuffer,1024,"HTTP/1.1 200 OK\r\nDate:%s\r\nServer:%s\r\nAccept-Ranges:bytes\r\nContent-Length:%ld\r\nConnection:%s\r\nContent-Type:text/html\r\n\r\n",strTime,"FQServer",dwFile,"close");
	int iSendLen = strlen(SendBuffer);
	return SendMsg(Socket,SendBuffer,iSendLen);
}

int	CIocpSocket::QuestError(SOCKET	Socket, char*	pErrorMessage)
{
	char	szSendBuffer[1024] = { 0 };
	_snprintf(szSendBuffer,1024,"0&nbsp%s",pErrorMessage);
	int DataLen = strlen(szSendBuffer);

	Quest200(Socket,DataLen);

	return SendMsg(Socket,szSendBuffer,DataLen);
}

int	CIocpSocket::CookieOutLimit(SOCKET	Socket)
{
	return QuestError(Socket,"Cookie");
}