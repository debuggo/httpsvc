#pragma once

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

//��־��¼����  //д��־�����Ĳ���
enum ENUM_LOG_LINE_LEVEL
{
    LOG_LEVEL_DEBUG = 1,       //���Լ���, ���ڵ���ʱ���
    LOG_LEVEL_INFO = 2,        //һ����Ϣ���
    LOG_LEVEL_WARN = 3,        //����
    LOG_LEVEL_ERROR = 4,       //һ�����
    LOG_LEVEL_FATAL = 5,       //���ش���,  �������Ĵ����ʾ����һ���޷���������
};

//#define FAST_RELEASE

#ifdef FAST_RELEASE 
#define WRITE_LOG(...) 
#define WRITE_LOGLINE(...) 
#else

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)

#define __WFILE__ WIDEN(__FILE__)
#ifdef _UNICODE
#define __TFILE__ __WFILE__
#else
#define __TFILE__ __FILE__
#endif

#if (_MSC_VER && _MSC_VER<=1200) || (__BORLANDC__) 
#define __FUNCTION__ NULL
#define __WFUNCTION__ NULL
#else //_MSC_VER>1200 __GNUC__ __INTEL_COMPILER
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#endif

#ifdef _UNICODE
#ifdef __GNUC__
#define __TFUNCTION__ NULL
#else
#define __TFUNCTION__ __WFUNCTION__
#endif
#else
#define __TFUNCTION__ __FUNCTION__
#endif

//���±�ʾ��־���ڲ����Զ�׷�ӻ��з�
#define WRITE_LOG(level,format,...) g_logger.AddTLog(true,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
//���±�ʾ��־�಻���Զ�׷�ӻ��з�
#define WRITE_LOGLINE(level,format,...) g_logger.AddTLog(false,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
#endif

//ÿ����־��󳤶�
#define LINE_BUFFER_SIZE (10240)

class CTextLog
{
public:
    //��־���ģʽ  //�����캯������
    enum ENUM_LOG_MODE
    {
        LOG_MODE_DIRECT = 0,  //ֱ�������־
        LOG_MODE_DELAY        //�ӳ������־
    };

    //��־������� //�����캯������
    enum ENUM_LOG_LEVEL
    {
        LOG_WRITE_NONE = 0,     //�ر���־
        LOG_WRITE_ERROR = 1,    //������漶�����ϵ���־ (��־����С)
        LOG_WRITE_INFO = 2,     //�����Ϣ�������ϵ���־ (������������־,һ�����������)
        LOG_WRITE_ALL = 3,      //������Լ������ϵ���־ (������־,����������־)
    };

public: //��������
    CTextLog(ENUM_LOG_LEVEL level = LOG_WRITE_ALL, ENUM_LOG_MODE writemode = LOG_MODE_DIRECT, LPCTSTR lpLogName = NULL);
    virtual ~CTextLog();

public: //�ⲿ���ýӿ�
    // �ı���־��¼ģʽ
    void SetMode(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode)
    {	
        m_level = level;
        m_mode = writemode;
    }
    //�����־
    void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const WCHAR* format, ...);
    void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const CHAR* format, ...);

private:  //˽�к���
    void Close();
    void CreateNewLogFile();
private:  //˽�б���
    TCHAR m_strFileName[MAX_PATH];           //��־�ļ�����·�� 
    TCHAR m_szCurPath[MAX_PATH];             //��־�ļ����·��
    TCHAR m_szFileName[MAX_PATH];            //��־�ļ���
    HANDLE m_file;                           //��־�ļ����
    SYSTEMTIME m_createtime;                 //��־����ʱ��

    ENUM_LOG_LEVEL m_level;                  //��־�������, Ĭ��Ϊ3,  ���������־
    ENUM_LOG_MODE m_mode;                    //��־���ģʽ: ֱ��,�ӳ�, Ĭ��Ϊֱ��,  �ӳ�ģʽΪÿ����9*LINE_BUFFER_SIZE���һ��
    CHAR m_buffer[10*LINE_BUFFER_SIZE];      //��־����
    CRITICAL_SECTION m_cs;
};

extern CTextLog g_logger;
