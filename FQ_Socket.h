#pragma once

class CFQ_Socket
{
public:
	CFQ_Socket(void);
	~CFQ_Socket(void);
	BOOL		InitSocket(int Type);
	BOOL		Connect(CString		IpAddress, UINT	iServerProt);
	int			Send(void*	pData,	DWORD	DataLen);
	int			Receive(void*	pData,DWORD	Len);
	int			Close();
public:
	SOCKET			m_Socket;
};
