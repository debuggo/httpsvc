#include "MyFileOperating.h"

CMyFileOperating::CMyFileOperating(void)
{
}
CMyFileOperating::~CMyFileOperating(void)
{
}
BOOL CMyFileOperating::MyDeleteFile( const CString strFilePath )
{
	if (IsBadFilePath(strFilePath))
	{
		return FALSE;
	}
	if (!DeleteFile(strFilePath))
	{
		DWORD dwErr = GetLastError();
		if (ERROR_FILE_NOT_FOUND == dwErr)
		{
			return TRUE;
		}
		else if (ERROR_FILE_READ_ONLY == dwErr)
		{
			ChangeFileReadOnlyStatus(strFilePath, FALSE);
			return MyDeleteFile(strFilePath);
		}
		WRITE_LOG(LOG_LEVEL_WARN, _T("删除文件时发生错误!! ErrorCode: %08X"), dwErr);
		return FALSE;
	}
	return TRUE;
}

BOOL CMyFileOperating::ChangeFileReadOnlyStatus( const CString &strFilePath, BOOL bReadOnly )
{
	if (IsBadFilePath(strFilePath))
	{
		return FALSE;
	}
	CFileStatus status;
	CFile::GetStatus(strFilePath, status);

	if (bReadOnly)
	{
		status.m_attribute |= FILE_ATTRIBUTE_READONLY;
	}
	else
	{
		status.m_attribute &= ~FILE_ATTRIBUTE_READONLY;
	}
	
	CFile::SetStatus(strFilePath, status);
	return TRUE;
}

BOOL CMyFileOperating::IsBadFilePath( const CString &strFilePath )
{
	BOOL bRet = FALSE;
	if ( strFilePath == _T(" "))
	{
		WRITE_LOG(LOG_LEVEL_WARN, _T("无效路径."));
		bRet = TRUE;
	}
	return bRet;
}
