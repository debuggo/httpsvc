#include "FQ_Std.h"
#include "ClientSocket.h"
#include "AppMain.h"
#include "mylog.h"

CClientSocket::CClientSocket(void)
{
	m_pzsData = new char[FQ_BufferSizeof];
	m_pszBuffer = new char[FQ_BufferSizeof];
	memset(m_pszBuffer,0,FQ_BufferSizeof);
	memset(m_pzsData,0,FQ_BufferSizeof);
	m_dwData = 0;
}

CClientSocket::~CClientSocket(void)
{
	delete	[]m_pzsData;
	delete	[]m_pszBuffer;
}

int		CClientSocket::Quest404()
{
	char	SendBuffer[1024] = { 0 };

	_snprintf((char*)SendBuffer,1024,"HTTP/1.1 404 OK\r\nServer:%s\r\nCache-Control:private\r\nContent-Type:%s\r\nContent-Length:%d\r\nConnection:Close\r\nContent-Type:text/html\r\n\r\n","FQServer","Bytes",0);

	return send(m_Socket,SendBuffer,strlen(SendBuffer),0);
}

int 	CClientSocket::Quest200(DWORD dwFile)
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
	return send(m_Socket,SendBuffer,iSendLen,0);
}

int		CClientSocket::CookieOutLimit()
{
	char	SendBuffer[1024] = { 0 };
	_snprintf(SendBuffer,1024,"Cookie&nbspCookie过期，请重新登录！");
	int nBufferLen = strlen(SendBuffer);

	Quest200(nBufferLen);
	return	send(m_Socket,SendBuffer,nBufferLen,0);
}

int		CClientSocket::QuestError(char*	pErrorMessage)
{
	char	szSendBuffer[1024] = { 0 };
	_snprintf(szSendBuffer,1024,"0&nbsp%s",pErrorMessage);
	int DataLen = strlen(szSendBuffer);

	Quest200(DataLen);

	return send(m_Socket,szSendBuffer,DataLen,NULL);
}

CClientSocket*	CClientSocket::FromHandle(SOCKET Socket)
{
	CClientSocket*	p = new	CClientSocket;
	if (p)
	{
		p->m_Socket = Socket;
	}
	return p;
}

int		CClientSocket::Receive()
{
	char*	pRecvBuffer = m_pszBuffer;
	pRecvBuffer += m_dwData;
	DWORD nRecv = recv(m_Socket,pRecvBuffer,FQ_BufferSizeof,0);
	if (nRecv == 0 || nRecv == SOCKET_ERROR)
	{
		return -1;
	}


	//WRITE_LOG(LOG_LEVEL_DEBUG,"%s",pRecvBuffer);

	char*	pEndPos = strstr(m_pszBuffer,"\r\n\r\n");
	if (pEndPos)
	{
		pEndPos += strlen("\r\n\r\n");
		char* pPos = strstr(m_pszBuffer," ");
		if(pPos)
		{
			char	strMethod[MAX_PATH] = { 0 };
			memcpy(strMethod,m_pszBuffer,pPos - m_pszBuffer);
			if (strcmp(strMethod,"GET") == 0)
			{
				pPos++;
				char*	sznPos = strstr(pPos," ");
				if (sznPos)
				{
					char	szBuffer[128] = { 0 };
					memcpy(szBuffer,pPos,sznPos - pPos);
					if (strcmp(szBuffer,"/") == NULL)
					{
						m_FileName = _T("Login.html");
						return 1;
					}
					else
					{
						m_FileName = szBuffer;
					}
					return 1;
				}
				return 0;
			}
			if (strcmp(strMethod,"POST") == 0)
			{
				char*	pzsLength = strstr(m_pszBuffer,"Content-Length:");
				if (pzsLength)
				{
					pzsLength += strlen("Content-Length:");
					m_dwData = atoi(pzsLength);
					int nDataLen = strlen(pEndPos);
					if (nDataLen == m_dwData)
					{
						memcpy(m_pzsData,pEndPos,nDataLen);
						return 2;
					}
					else
					{
						nRecv = recv(m_Socket,pEndPos,m_dwData,NULL);
						if (nRecv == m_dwData)
						{
							memcpy(m_pzsData,pEndPos,m_dwData);
							return 2;
						}
					}
				}
			}
		}
	}
	return -1;
}

int		CClientSocket::Send(LPVOID pData, DWORD	dwData)
{
	//DWORD	SendLen = send(m_Socket,(const char*)pData,dwData,0);
	//return SendLen;

	int nNullCount = 0;
	int nSend = 0;
	while (1)
	{
		int nSendLen = send(m_Socket,(const char*)pData,dwData,0);
		if (nSendLen  == -1)
		{
			//WRITE_LOG(LOG_LEVEL_DEBUG,"应发送数据长度：%d,错误码：%d",dwData,GetLastError());
			return -1;
		}
		if (nSendLen == NULL)
		{
			nNullCount++;
			if (nNullCount == 5)
			{
				return -1;
			}
		}
		nSend += nSendLen;
		if (nSend != dwData)
		{
			continue;
		}
		break;
	}
	return nSend;
}

int		CClientSocket::IsReg()
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();

	if (!pAppMain->m_IsSubServer)
	{
		CString	StrRegUserName = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserName"));
		CString	StrRegUserPassWord = pAppMain->m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserPassWord"));
		if (StrRegUserName.IsEmpty() && StrRegUserPassWord.IsEmpty())
		{
			return 0;
		}
		return 1;
	}
	return 1;
}


