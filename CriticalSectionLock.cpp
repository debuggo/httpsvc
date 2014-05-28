#include "FQ_Std.h"
#include "CriticalSectionLock.h"

CCriticalSectionLock::CCriticalSectionLock(void)
{
	InitializeCriticalSection(&m_CriticalSection);
}

CCriticalSectionLock::~CCriticalSectionLock(void)
{
	UnLock();
	DeleteCriticalSection(&m_CriticalSection);
}

void	CCriticalSectionLock::Lock()
{
	EnterCriticalSection(&m_CriticalSection);
	m_bLocked = TRUE;
}

void	CCriticalSectionLock::UnLock()
{
	if (m_bLocked)
	{
		LeaveCriticalSection(&m_CriticalSection);
		m_bLocked = FALSE;
	}
}