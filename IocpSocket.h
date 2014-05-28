#pragma once
#include <WinSock2.h>
#include <map>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define		BufferSizoeof	1024 * 1000

typedef	struct _tagIocp_HandleData
{
	SOCKET				Socket;
	sockaddr_in			SocketAddr;	
}Iocp_HandleData, *pIocp_HandleData;

typedef	struct	_tagIocp_Io_Data
{
	OVERLAPPED		Overlapped;
	WSABUF			DataBuf;
	char			pDataBuffer[BufferSizoeof];
	int				nRecvBytes;
	int				nSendBytes;
	int				OperationType;
}Iocp_Io_Data, *pIocp_Io_Data;

typedef	std::map<SOCKET,pIocp_HandleData>		Map_Iocp_Handle;
typedef	Map_Iocp_Handle::iterator				Iter_Iocp_Handle;

typedef	std::map<SOCKET,pIocp_Io_Data>			Map_Iocp_Io;
typedef	Map_Iocp_Io::iterator					Iter_Iocp_Io;

class CIocpSocket
{
public:
	CIocpSocket(void);
	~CIocpSocket(void);
	BOOL			Init();
	BOOL			InitNotice();
	int 			Create(UINT	nPort);
	int				AsynSendMsg(SOCKET	Socket,LPVOID lpData,int nlen);	//没用???
	int				SendMsg(SOCKET	Socket,LPVOID lpData,int nlen);;

	int				Quest404(SOCKET	Socket);
	int 			Quest200(SOCKET Socket, DWORD dwFile);
	int				QuestError(SOCKET	Socket, char*	pErrorMessage);
	int				CookieOutLimit(SOCKET	Socket);
public:
	static	UINT	WINAPI	ServerWorkerThread(LPVOID	lpvoid);
	static	DWORD	WINAPI	AcceptWorkerThread(LPVOID	lpvoid);

	static	DWORD	WINAPI	NoticeWorkerThread(LPVOID	lpvoid);
private:
	SOCKET				m_ServerSocket;
	HANDLE				m_hCompletionPort;	//I/O句柄
	Map_Iocp_Handle		m_Iocp_Handle;
	Map_Iocp_Io			m_Iocp_Io;
	BOOL				m_bIsStart;	//socket已绑定
};
