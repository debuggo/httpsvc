#pragma once

class CCriticalSectionLock
{
public:
	CCriticalSectionLock(void);
	~CCriticalSectionLock(void);
public:
	virtual void	Lock();
	virtual	void	UnLock();
	BOOL			IsLock(){ return m_bLocked; }
private:
	CRITICAL_SECTION	m_CriticalSection;
	BOOL				m_bLocked;
};
