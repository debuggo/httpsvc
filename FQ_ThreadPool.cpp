#include "FQ_Std.h"
#include "FQ_ThreadPool.h"
#include "AppMain.h"


CFQ_ThreadPool::CFQ_ThreadPool()
{
	m_ThreadPoolFlag = TRUE;
	InitializeCriticalSection(&m_CriticalSection);
}

CFQ_ThreadPool::~CFQ_ThreadPool()
{
	DeleteCriticalSection(&m_CriticalSection);
	ExitThreadPool();
}

BOOL	CFQ_ThreadPool::InitThreadPool(u_short iNumber)
{
	if (iNumber < 1)
		return FALSE;
	m_ThreadPoolFlag = TRUE;
	int iErrorCount = 0;
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	
	EnterCriticalSection(&m_CriticalSection);

	for (int i = 0; i < iNumber; i++)
	{
		DWORD	ThreadId;
		HANDLE	ThreadHandle = CreateThread(NULL,0,WorkProc,this,CREATE_SUSPENDED,&ThreadId);
		if (ThreadHandle == NULL)
		{
			iErrorCount++;
			if (iErrorCount > 30)
			{
				break;
			}
			continue;
		}
		pThreadInfo	p = new ThreadInfo;
		p->ThreadHandle = ThreadHandle;
		//p->ThreadId = GetThreadId(ThreadHandle);
		p->ThreadId = ThreadId;
		p->bFlag = TRUE;
		m_MapThreadInfo.insert(Map_ThreadInfo::value_type(p->ThreadId,p));
		ResumeThread(ThreadHandle);
		p = NULL;
	}

	LeaveCriticalSection(&m_CriticalSection);

	return TRUE;
}

DWORD	WINAPI	CFQ_ThreadPool::WorkProc(LPVOID pData)
{
	CFQ_ThreadPool*	pFQ_ThreadPool = (CFQ_ThreadPool*)pData;
	
	Iter_ThreadInfo	Iter = pFQ_ThreadPool->m_MapThreadInfo.find(GetCurrentThreadId());
	if (Iter == pFQ_ThreadPool->m_MapThreadInfo.end())
	{
		//不晓得哪里冒出的线程
		return 0;
	}
	while (pFQ_ThreadPool->m_ThreadPoolFlag)
	{
		if (Iter->second->bFlag)
		{
			Sleep(100);
			continue;
		}

		pTaskInfo p = pFQ_ThreadPool->m_StackTaskInfo.top();
		pFQ_ThreadPool->m_StackTaskInfo.pop();

		if (p == NULL)
		{
			Iter->second->bFlag = TRUE;
			continue;
		}
		DWORD	pParameter = (DWORD)p->pData;
		DWORD	pFun = (DWORD)p->iFunction;
		__asm
		{
			push	pParameter
			call	pFun
		}
		Iter->second->bFlag = TRUE;
		delete	p;
	}
	return 0;
}

void	CFQ_ThreadPool::ExitThreadPool()
{
	m_ThreadPoolFlag = FALSE;
	Iter_ThreadInfo Iter = m_MapThreadInfo.begin();
	for (; Iter != m_MapThreadInfo.end(); Iter++)
	{
		CloseHandle(Iter->second->ThreadHandle);
		pThreadInfo p = NULL;
		p = Iter->second;
		delete p;
	}
	int iCount = m_StackTaskInfo.size();
	for (int i = 0; i < iCount; i++)
	{
		pTaskInfo p = NULL;
		p = m_StackTaskInfo.top();
		m_StackTaskInfo.pop();
		delete p;
	}
}

void	CFQ_ThreadPool::AddTask(FARPROC iFunction, LPVOID pData)
{
	if (!m_ThreadPoolFlag)
	{
		return;
	}
	EnterCriticalSection(&m_CriticalSection);

	pTaskInfo p = new TaskInfo;
	p->iFunction = iFunction;
	p->pData = pData;
	m_StackTaskInfo.push(p);

	Iter_ThreadInfo Iter = m_MapThreadInfo.begin();
	for (; Iter != m_MapThreadInfo.end(); Iter++)
	{
		if (Iter->second->bFlag == TRUE)
		{
			Iter->second->bFlag = FALSE;
			break;
		}
	}
	Sleep(100);
	LeaveCriticalSection(&m_CriticalSection);
}