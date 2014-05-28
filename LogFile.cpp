#include "FQ_Std.h"
#include "LogFile.h"

CLogFile::CLogFile(void)
{
	m_pFilePath = new TCHAR[MAX_PATH];
	memset((void*)m_pFilePath,0,MAX_PATH * sizeof(TCHAR));
}

CLogFile::~CLogFile(void)
{
	delete	[]m_pFilePath;
}


void	CLogFile::InitLog(LPCTSTR lpwzsFilePath)
{
	lstrcpy((wchar_t*)m_pFilePath,lpwzsFilePath);
}

BOOL	CLogFile::WriteLog(const char* fmt, ...)
{
	char	lpzsBuffer[1024] = { 0 };
	char	lpzsWriteBuffer[2048] = { 0 };
	BOOL	bRet;
	int		nLen;

	va_list argptr;          //分析字符串的格式
	va_start(argptr, fmt);
	//_vsnprintf(lpzsBuffer, 2048, fmt, argptr);
	wvsprintfA(lpzsBuffer,fmt,argptr);
	va_end(argptr);

	HANDLE	hFile = NULL;
	hFile = CreateFile(m_pFilePath,GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	SetFilePointer(hFile,0,0,FILE_END);

	DWORD	dwWrite;

	char	lpszTimeBuffer[64] = { 0 };
	int		nTimeLen;
	SYSTEMTIME   sysTime;                          //加入当前时间
	GetLocalTime(&sysTime);
	nTimeLen = wsprintfA(lpszTimeBuffer,"%d-%d-%d %d:%d:%d\r\n",sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour,sysTime.wMinute,sysTime.wSecond);

	bRet = WriteFile(hFile,lpszTimeBuffer,nTimeLen,&dwWrite,NULL);
	if (!bRet)
	{
		CloseHandle(hFile);
		return	bRet;
	}

	nLen = wsprintfA(lpzsWriteBuffer,"%s\r\n",lpzsBuffer);

	bRet = WriteFile(hFile,lpzsWriteBuffer,nLen,&dwWrite,NULL);
	if (!bRet)
	{
		CloseHandle(hFile);
		return	bRet;
	}
	CloseHandle(hFile);
	return TRUE;
}