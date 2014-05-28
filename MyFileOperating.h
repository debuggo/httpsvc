#pragma once
#include <afx.h>
#include <io.h>
#include "mylog.h"
class CMyFileOperating
{
public:
	CMyFileOperating(void);
	~CMyFileOperating(void);
	BOOL MyDeleteFile(const CString strFilePath);
	BOOL ChangeFileReadOnlyStatus(const CString& strFilePath, BOOL bReadOnly);

private:
	BOOL IsBadFilePath(const CString& strFilePath);
};
