#pragma once
#include <map>
#include "ClientSocket.h"
#include "CriticalSectionLock.h"
#include "IocpSocket.h"
#include "spliocp.h"

using namespace std;

typedef	struct	_tagHttpPacket
{
	char		szBufferData[4096];
	int			nLen;
}HttpPacket,*pHttpPacket;



typedef	std::map<SOCKET,	pHttpPacket>				Map_Http;
typedef	Map_Http::iterator								Iter_Http;

class CHttp
{
public:
	CHttp(void);
	~CHttp(void);
	static	BOOL	WINAPI	InitSocket();
	static	DWORD	WINAPI	AcceptThreadProc(LPVOID	pData);
	BOOL			StartHttpServer(UINT	nPort);
	BOOL			StartNoticeHttp(UINT	nPort);

	void			Close_Socket(SOCKET	Socket);
	CClientSocket*	GetSocketInfo(SOCKET	Socket);


	int				PacketMessage(SOCKET	sSocket, char*	pData, CString&	strFileName, char* pResultData, int& nLen);
	int				PacketMessageByNotice(SOCKET	sSocket, char*	pData, CString&	strFileName, char* pResultData, int& nLen);

	int				Http_Quest404(SOCKET	sSocket);
	int				Http_Quest200(SOCKET	sSocket,	int nLen);

	int				Http_SendMsg(SOCKET	sSocket,	LPVOID	lpData,	int nLen);
public:
	HANDLE			m_hCompletion;
	SOCKET			m_ServerSocket;
	Map_Http		m_MapHttp;
	CCriticalSectionLock	m_CriticalSectionLock;
	CIocpSocket		m_IocpSocket;
	tagIocpData		m_HttpIocp;
};
