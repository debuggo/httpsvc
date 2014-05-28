#pragma once
#include <map>
#include <stack>

using namespace std;

typedef struct	_FQ_ThreadInfo
{
	DWORD		ThreadId;
	HANDLE		ThreadHandle;
	BOOL		bFlag;
}ThreadInfo, *pThreadInfo;

typedef	struct	_FQ_TaskInfo
{
	FARPROC		iFunction;
	LPVOID		pData;
}TaskInfo, *pTaskInfo;

typedef	std::map<DWORD,	pThreadInfo>	Map_ThreadInfo;
typedef	Map_ThreadInfo::iterator		Iter_ThreadInfo;

typedef	std::stack<pTaskInfo>			Stack_TaskInfo;


class	CFQ_ThreadPool
{
public:
	CFQ_ThreadPool();
	~CFQ_ThreadPool();
private:
	static	DWORD	WINAPI	WorkProc(LPVOID		pData);
public:
	BOOL			InitThreadPool(u_short	iNumber);
	void			AddTask(FARPROC	iFunction, LPVOID	pData);
	void			ExitThreadPool();
private:
	CRITICAL_SECTION	m_CriticalSection;
	Map_ThreadInfo		m_MapThreadInfo;
	Stack_TaskInfo		m_StackTaskInfo;
	BOOL				m_ThreadPoolFlag;
};