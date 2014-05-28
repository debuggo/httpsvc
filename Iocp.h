#pragma once

class CFQ_Iocp
{
public:
	CIocp(void);
	~CIocp(void);
	BOOL			InitIocp();
private:
	static	DWORD	WINAPI	ServerWorkerThread(LPVOID	lpvoid);
private:
	HANDLE			m_hCompletionPort;
};
