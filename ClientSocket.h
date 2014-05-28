#pragma once


#define		FQ_BufferSizeof		1024 * 1024

class CClientSocket
{
public:
	CClientSocket(void);
	~CClientSocket(void);

	static	CClientSocket*	FromHandle(SOCKET	Socket);
	int		Quest404();
	int 	Quest200(DWORD dwFile);
	int		QuestError(char*	pErrorMessage);
	int		CookieOutLimit();
	int		IsReg();
	int		Receive();
	int		Send(LPVOID	pData,	DWORD	dwData);
public:
	SOCKET			m_Socket;
	CString			m_FileName;
	CString			m_CookiesTime;
	DWORD			m_dwData;
	char*			m_pzsData;
	char*			m_pszBuffer;
};
