#include "FQ_Std.h"
#include "FQ_Socket.h"
#include "AppMain.h"
#include "LogFile.h"
#include <afxsock.h>

CFQ_Socket::CFQ_Socket(void)
{
	m_Socket = INVALID_SOCKET;
}

CFQ_Socket::~CFQ_Socket(void)
{
}


BOOL	CFQ_Socket::InitSocket(int Type)
{
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	m_Socket = socket(AF_INET,Type,0);
	if (m_Socket == INVALID_SOCKET)
	{
		//pAppMain->m_LogFile.WriteLog("客户端SOCKET创建失败！");
		return FALSE;
	}

	unsigned long ul1 = 1;  
	if (ioctlsocket(m_Socket,FIONBIO,(unsigned long*)&ul1) == SOCKET_ERROR)
	{
		//pAppMain->m_LogFile.WriteLog("设置SOCKET为非阻塞失败！");
		return FALSE;
	}

	struct timeval tv_out;
	tv_out.tv_sec = 3000;
	tv_out.tv_usec = 0;
	setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));
	
	return TRUE;
}

BOOL	CFQ_Socket::Connect(CString IpAddress, UINT iServerProt)
{
	SOCKADDR_IN	sockAddr = { 0 };
	char	lpszAscii[32] = { 0 };
	int		nErorr = 0;
	WideCharToMultiByte(CP_ACP,0,IpAddress,IpAddress.GetLength(),lpszAscii,32,NULL,NULL);
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(lpszAscii);
	if (sockAddr.sin_addr.s_addr == INADDR_NONE)
	{
		LPHOSTENT lphost;
		lphost = gethostbyname(lpszAscii);
		if (lphost != NULL)
			sockAddr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
			return FALSE;
	}
	sockAddr.sin_port = htons((u_short)iServerProt);
	nErorr = connect(m_Socket,(const sockaddr*)&sockAddr,sizeof(SOCKADDR_IN));

	struct timeval timeout ;  
	fd_set r;
	FD_ZERO(&r);  
	FD_SET(m_Socket,&r);
	timeout.tv_sec = 1;   //连接超时3秒  
	timeout.tv_usec = 0;  
	nErorr = select(NULL,NULL,&r,NULL,&timeout);  
	if(nErorr <= 0)  
	{
		::closesocket(m_Socket);  
		return FALSE; 
	}

	unsigned long ul2= 0;  
	nErorr = ioctlsocket(m_Socket,FIONBIO,(unsigned long*)&ul2);  
	if(nErorr == SOCKET_ERROR)
	{
		::closesocket(m_Socket);  
		return FALSE; 
	}
	return TRUE;
}

int		CFQ_Socket::Send(void *pData, DWORD DataLen)
{
	return send(m_Socket,(const char*)pData,DataLen,0);
}

int		CFQ_Socket::Receive(void *pData, DWORD Len)
{
	return recv(m_Socket,(char*)pData,Len,0);
}

int		CFQ_Socket::Close()
{
	closesocket(m_Socket);
	m_Socket = INVALID_SOCKET;
	return 1;
}

