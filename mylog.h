#pragma once

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

//日志记录级别  //写日志函数的参数
enum ENUM_LOG_LINE_LEVEL
{
    LOG_LEVEL_DEBUG = 1,       //调试级别, 仅在调试时输出
    LOG_LEVEL_INFO = 2,        //一般信息输出
    LOG_LEVEL_WARN = 3,        //警告
    LOG_LEVEL_ERROR = 4,       //一般错误
    LOG_LEVEL_FATAL = 5,       //严重错误,  这个级别的错误表示程序一般无法正常进行
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

//以下表示日志类内部会自动追加换行符
#define WRITE_LOG(level,format,...) g_logger.AddTLog(true,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
//以下表示日志类不用自动追加换行符
#define WRITE_LOGLINE(level,format,...) g_logger.AddTLog(false,level, __TFILE__, __TFUNCTION__, __LINE__, format,__VA_ARGS__)
#endif

//每条日志最大长度
#define LINE_BUFFER_SIZE (10240)

class CTextLog
{
public:
    //日志输出模式  //作构造函数参数
    enum ENUM_LOG_MODE
    {
        LOG_MODE_DIRECT = 0,  //直接输出日志
        LOG_MODE_DELAY        //延迟输出日志
    };

    //日志输出级别 //作构造函数参数
    enum ENUM_LOG_LEVEL
    {
        LOG_WRITE_NONE = 0,     //关闭日志
        LOG_WRITE_ERROR = 1,    //输出警告级别以上的日志 (日志量极小)
        LOG_WRITE_INFO = 2,     //输出信息级别以上的日志 (不包括调试日志,一般是这个级别)
        LOG_WRITE_ALL = 3,      //输出调试级别以上的日志 (所有日志,包括调试日志)
    };

public: //构造析构
    CTextLog(ENUM_LOG_LEVEL level = LOG_WRITE_ALL, ENUM_LOG_MODE writemode = LOG_MODE_DIRECT, LPCTSTR lpLogName = NULL);
    virtual ~CTextLog();

public: //外部调用接口
    // 改变日志记录模式
    void SetMode(ENUM_LOG_LEVEL level, ENUM_LOG_MODE writemode)
    {	
        m_level = level;
        m_mode = writemode;
    }
    //添加日志
    void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const WCHAR* format, ...);
    void AddTLog(bool bAddLine, ENUM_LOG_LINE_LEVEL level, LPCTSTR szSrc, LPCTSTR szFunc, ULONG uLine, const CHAR* format, ...);

private:  //私有函数
    void Close();
    void CreateNewLogFile();
private:  //私有变量
    TCHAR m_strFileName[MAX_PATH];           //日志文件完整路径 
    TCHAR m_szCurPath[MAX_PATH];             //日志文件存放路径
    TCHAR m_szFileName[MAX_PATH];            //日志文件名
    HANDLE m_file;                           //日志文件句柄
    SYSTEMTIME m_createtime;                 //日志创建时间

    ENUM_LOG_LEVEL m_level;                  //日志输出级别, 默认为3,  输出所有日志
    ENUM_LOG_MODE m_mode;                    //日志输出模式: 直接,延迟, 默认为直接,  延迟模式为每大于9*LINE_BUFFER_SIZE输出一次
    CHAR m_buffer[10*LINE_BUFFER_SIZE];      //日志缓存
    CRITICAL_SECTION m_cs;
};

extern CTextLog g_logger;
