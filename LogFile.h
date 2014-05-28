#pragma once

class CLogFile
{
public:
	CLogFile(void);
	~CLogFile(void);
	void		InitLog(LPCTSTR	lpwzsFilePath);
	BOOL		WriteLog(const char* fmt, ...);
private:
	LPCTSTR		m_pFilePath;
};
