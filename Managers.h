#pragma once
#include "ClientSocket.h"
#include "CriticalSectionLock.h"

class CManagers
{
public:
	CManagers(void);
	~CManagers(void);
	static	DWORD	WINAPI	Get_Request(SOCKET	ClientSocket, CString	strFile);
	static	DWORD	WINAPI	Post_Request(SOCKET	sSocket,	char*	pHttpData,	int nLen);

	static	ULONG	WINAPI	NoticeInterface(SOCKET	sSocket,	CString	strPathFile);
	
// 	static	DWORD	WINAPI	Get_Quest_Iocp(CPacket*		pPacket);
// 	static	DWORD	WINAPI	Post_Quest_Iocp(CPacket*	pPacket);
};
