//#include "stdafx.h"

#include "mylog.h"

//��־�����ַ���
#define LOG_LEVEL_DEBUG_STR  ("[����]") 
#define LOG_LEVEL_INFO_STR	 ("[��Ϣ]")
#define LOG_LEVEL_WARN_STR	 ("[����]")
#define LOG_LEVEL_ERROR_STR	 ("[����]")
#define LOG_LEVEL_FATAL_STR	 ("[����]")

#define LOG_DIR _T("\\LOG\\")   //��־�ļ����Ŀ¼

CTextLog g_logger;

#include "string"
using namespace std;

HMODULE GetSelfModuleHandle()
{
    MEMORY_BASIC_INFORMATION mbi;
    return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0)  ? (HMODULE) mbi.AllocationBase : NULL);
}
 
CTextLog::CTextLog(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode, LPCTSTR lpLogName)
{
    //#ifdef _DEBUG 
    //#else	
    InitializeCriticalSection(&m_cs);//��ʼ���ṹCRITICAL_SECTION
    //ȡ��ִ���ļ���
    GetModuleFileName(GetSelfModuleHandle(),  m_szCurPath, MAX_PATH);
    //ȡ��ִ���ļ�·��
    TCHAR* pFileName = _tcsrchr(m_szCurPath, _T('\\'));
    *pFileName++ = _T('\0');

    lstrcpy(m_szFileName, pFileName);

    m_file = INVALID_HANDLE_VALUE;

    //������־Ŀ¼
    lstrcat(m_szCurPath, LOG_DIR);
    CreateDirectory(m_szCurPath, NULL);
    if (lpLogName == NULL)
    {//ȡִ���ļ���
        //ȡִ���ļ��ļ���
        TCHAR* pFileNameDot = _tcsrchr(m_szFileName, _T('.'));
        if (pFileNameDot != NULL)
        {
            *pFileNameDot++ = _T('\0');

            if (lstrcmpi(m_szFileName, _T("svchost")) == 0)
            {//�Ǹ�DLL����������⴦���£�ȡ����������
                lstrcpy(m_szFileName, GetCommandLine());
                TCHAR* pFileNameDot = _tcsrchr(m_szFileName, _T(' '));
                if (pFileNameDot)
                {     
                    pFileNameDot++;
                    lstrcpy(m_szFileName, pFileNameDot);
                }
                else
                {
                    lstrcpy(m_szFileName, _T("svchost"));
                }
            }
        }
    }
    else
    {
        lstrcpy(m_szFileName, lpLogName);

    }
    CreateNewLogFile();

    m_buffer[0] = '\0';
    m_level = level;
    m_mode = writemode;

    //lstrcpy(szFileName, GetCommandLine());
    //AddTLog(true, LOG_LEVEL_DEBUG, _T("%s"), szFileName);
    //#endif
}

CTextLog::~CTextLog()
{
    Close();
}

void CTextLog::Close()
{
    if (m_file != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_file);
        m_file = INVALID_HANDLE_VALUE;
    }
}
void CTextLog::CreateNewLogFile()
{
    if (m_file != INVALID_HANDLE_VALUE)
    {
        if (m_mode == LOG_MODE_DELAY)
        {//������ӳ���������֮ǰ���ڴ��е���־���
            DWORD dwByteWrite = 0;
            WriteFile(m_file, m_buffer, lstrlenA(m_buffer)*sizeof(CHAR), &dwByteWrite, NULL);  
            m_buffer[0] = 0;
        }
        CloseHandle(m_file);

    }   
    //ȡϵͳʱ��
    GetLocalTime(&m_createtime); 
    wsprintf(m_strFileName, _T("%s%s_%02d%02d%02d.log"), m_szCurPath, m_szFileName, m_createtime.wYear, m_createtime.wMonth, m_createtime.wDay);

    m_file = CreateFile(m_strFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
    if (m_file == INVALID_HANDLE_VALUE)
    {
        OutputDebugString(_T("���ش�����־�ļ��޷�������"));
        return;
    }
    //#ifdef _UNICODE  ��ʱֻдANSI��ʽ��־
    //    DWORD dwSize = ::GetFileSize(m_file, NULL);
    //    if (dwSize == 0)
    //    {//д��UNICODEǰ׺
    //        WORD wBf = 0xFEFF;
    //        DWORD dwWrite = 0;
    //        WriteFile(m_file, &wBf, 2, &dwWrite, NULL);
    //    }
    //#endif
    SetFilePointer(m_file, 0, NULL, FILE_END);
}

wstring MToWChar(string str)
{
    //��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ַ������
    int len=MultiByteToWideChar(CP_ACP,0,str.c_str(),str.size(),NULL,0);
    WCHAR *buffer = new WCHAR[len+1];
    //���ֽڱ���ת���ɿ��ֽڱ���
    MultiByteToWideChar(CP_ACP,0,str.c_str(),str.size(),buffer,len);
    buffer[len]='\0';//����ַ�����β
    //ɾ��������������ֵ
    wstring return_value;
    return_value.append(buffer);
    delete []buffer;
    return return_value;
}

string WToMChar(wstring str)
{
    string return_value;
    //��ȡ�������Ĵ�С��������ռ䣬��������С�ǰ��ֽڼ����
    int len=WideCharToMultiByte(CP_ACP,0,str.c_str(),str.size(),NULL,0,NULL,NULL);
    char *buffer=new char[len+1];
    WideCharToMultiByte(CP_ACP,0,str.c_str(),str.size(),buffer,len,NULL,NULL);
    buffer[len]='\0';
    //ɾ��������������ֵ
    return_value.append(buffer);
    delete []buffer;
    return return_value;
}

//�����־
void CTextLog::AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine,  const WCHAR* format, ...)
{
    if (m_level == LOG_WRITE_NONE)
    {//�ر���־
        return;
    }
    else if ((m_level+level) < 4)
    {//δ������Ҫ��¼��־�ļ���
        return;
    }

    va_list ap;
    va_start(ap, format);

    WCHAR line[LINE_BUFFER_SIZE] = {0};

    EnterCriticalSection(&m_cs);

    SYSTEMTIME systime; 
    GetLocalTime(&systime); 
    if ((systime.wYear != m_createtime.wYear) || (systime.wMonth != m_createtime.wMonth) || (systime.wDay != m_createtime.wDay))
    {//�����ղ��Ǻϣ����´�����־�ļ�
        CreateNewLogFile();
    }
#ifdef _UNICODE
    switch (level)
    {
    case LOG_LEVEL_DEBUG: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_DEBUG_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_INFO:  //��Ϣ
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_INFO_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_WARN: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_WARN_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_ERROR: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_ERROR_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_FATAL: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_FATAL_STR, szSrc, szFunc, uLine);
        break;
    }
#else
    switch (level)
    {
    case LOG_LEVEL_DEBUG: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_DEBUG_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_INFO:  //��Ϣ
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_INFO_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_WARN: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_WARN_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_ERROR: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_ERROR_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_FATAL: //����
        wsprintfW(line, (L"[%02d:%02d:%02d.%03d] %S %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_FATAL_STR, szSrc, szFunc, uLine);
        break;
    }
#endif

	int FormatLen = 0;
    int len = (int)lstrlenW(line);
    if (bAddLine)
    {//���Ҫ׷�ӻ��з�����Ҫ���Ǳ�����λ�洢���з�
        FormatLen = _vsnwprintf_s(line + len, LINE_BUFFER_SIZE - len, LINE_BUFFER_SIZE - len - 3, format, ap);

        //vswprintf(line + len, LINE_BUFFER_SIZE - len - 4 , format, ap);
    }
    else
    {   
        FormatLen = _vsnwprintf_s(line + len, LINE_BUFFER_SIZE - len, LINE_BUFFER_SIZE - len - 1, format, ap);
        //vswprintf(line + len, LINE_BUFFER_SIZE - len - 1 , format, ap);
    }
  
    va_end(ap);

    if (bAddLine)
    {//��Ҫ׷�ӻ��з�
        len = (int)lstrlenW(line);
        if (len < LINE_BUFFER_SIZE - 2)
        {
            line[len] = L'\r';
            line[len + 1] = L'\n';
            line[len + 2] = L'\0';
        }
    }
    lstrcatA(m_buffer, WToMChar(line).c_str());

    DWORD dwByteWrite = 0;
    if (m_mode == LOG_MODE_DIRECT)
    {
        WriteFile(m_file, m_buffer, lstrlenA(m_buffer)*sizeof(CHAR), &dwByteWrite, NULL);  
        m_buffer[0] = 0;
    }
    else
    {
        if (lstrlenA(m_buffer) > 9*LINE_BUFFER_SIZE)
        {
            BOOL bOk = WriteFile(m_file, m_buffer, lstrlenA(m_buffer)*sizeof(CHAR), &dwByteWrite, NULL);  
            m_buffer[0] = 0;
        }
    }
    LeaveCriticalSection(&m_cs);
}

//�����־
void CTextLog::AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const CHAR* format, ...)
{
    if (m_level == LOG_WRITE_NONE)
    {//�ر���־
        return;
    }
    else if ((m_level+level) < 4)
    {//δ������Ҫ��¼��־�ļ���
        return;
    }

    va_list ap;
    va_start(ap, format);

    CHAR line[LINE_BUFFER_SIZE] = {0}; 
    
    EnterCriticalSection(&m_cs);

    SYSTEMTIME systime; 
    GetLocalTime(&systime); 

    if ((systime.wYear != m_createtime.wYear) || (systime.wMonth != m_createtime.wMonth) || (systime.wDay != m_createtime.wDay))
    {//�����ղ��Ǻϣ����´�����־�ļ�
        CreateNewLogFile();
    }
#ifdef _UNICODE
    switch (level)
    {
    case LOG_LEVEL_DEBUG: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_DEBUG_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_INFO:  //��Ϣ
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_INFO_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_WARN: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_WARN_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_ERROR: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_ERROR_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_FATAL: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %S %S %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_FATAL_STR, szSrc, szFunc, uLine);
        break;
    }
#else
    switch (level)
    {
    case LOG_LEVEL_DEBUG: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_DEBUG_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_INFO:  //��Ϣ
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_INFO_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_WARN: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_WARN_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_ERROR: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_ERROR_STR, szSrc, szFunc, uLine);
        break;
    case LOG_LEVEL_FATAL: //����
        wsprintfA(line, ("[%02d:%02d:%02d.%03d] %s %s %s %d "), systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, LOG_LEVEL_FATAL_STR, szSrc, szFunc, uLine);
        break;
    }
#endif
    int len = (int)lstrlenA(line);
	if (bAddLine)
	{//���Ҫ׷�ӻ��з�����Ҫ���Ǳ�����λ�洢���з�
		vsnprintf_s(line + len, LINE_BUFFER_SIZE - len, LINE_BUFFER_SIZE - len - 3, format, ap);
	}
	else
	{
		vsnprintf_s(line + len, LINE_BUFFER_SIZE - len, LINE_BUFFER_SIZE - len - 1, format, ap);
	}


    va_end(ap);

    if (bAddLine)
    {//��Ҫ׷�ӻ��з�
        len = (int)lstrlenA(line);
        if (len < LINE_BUFFER_SIZE - 2)
        {
            line[len] = '\r';
            line[len + 1] = '\n';
            line[len + 2] = '\0';
        }
    }

	
    //lstrcat(m_buffer, line);
	strncat_s(m_buffer,_countof(m_buffer),line,_TRUNCATE);
    //wsprintfA(m_buffer + lstrlenA(m_buffer), "%s", line);

    DWORD dwByteWrite = 0;
    if (m_mode == LOG_MODE_DIRECT)
    {
        BOOL bOk = WriteFile(m_file, m_buffer, lstrlenA(m_buffer)*sizeof(CHAR), &dwByteWrite, NULL); 
        m_buffer[0] = 0;
    }else
    {
        if (lstrlenA(m_buffer) > 9*LINE_BUFFER_SIZE)
        {
            BOOL bOk = WriteFile(m_file, m_buffer, lstrlenA(m_buffer)*sizeof(CHAR), &dwByteWrite, NULL);  
            m_buffer[0] = 0;
        }
    }
    LeaveCriticalSection(&m_cs);
}
