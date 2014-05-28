#include "FQ_Std.h"
#include "AppMain.h"
#include "mylog.h"

//////////////////////////////////////////////////////////////////////////
//编写者：曾谅亮
//////////////////////////////////////////////////////////////////////////
//时间：2014年2月17日14:05:44

//静态常量
CAppMain*	CAppMain::m_pAppMain = NULL;
BOOL		CAppMain::m_AppFlag = TRUE;
int			CAppMain::m_Ver = 1;

CAppMain::CAppMain(void)
{
	m_IsLog = FALSE;
	m_AppHandle = NULL;

	WRITE_LOG(LOG_LEVEL_DEBUG,"%s\r\n","程序初始化开始！");
	//m_BT_IpAddress = _T("127.0.0.1");
	//m_MZD_IpAddress = _T("127.0.0.1");
}

CAppMain::~CAppMain(void)
{
}



//************************************
// 方法名:	GetAppMain
// 全名称:	CAppMain::GetAppMain
// 访问级:	public static 
// 返回值:	CAppMain*
// 限定符:	
// 备  注:	返回自身,相当于全局变量
//************************************
CAppMain*	CAppMain::GetAppMain()
{
	if (m_pAppMain)
	{
		return m_pAppMain;
	}
	m_pAppMain = new CAppMain;
	return m_pAppMain;
}

//************************************
// 方法名:	GetAppPath
// 全名称:	CAppMain::GetAppPath
// 访问级:	public static 
// 返回值:	CString
// 限定符:	
// 备  注:	获取程序路径
//************************************
CString		CAppMain::GetAppPath()
{
	TCHAR	wsBuffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,wsBuffer,MAX_PATH);
	CString	StrPath(wsBuffer);
	int nPos = StrPath.ReverseFind('\\');
	return StrPath.Left(nPos + 1);
}

//初始化运行服务
BOOL	CAppMain::InitInstance()
{
	WRITE_LOG(LOG_LEVEL_DEBUG,"初始化运行服务");
	//if (!CHttp::InitSocket())
	//{
	//	return FALSE;
	//}
	m_HtmlFile.InitHtmlFile();	//初始化Web文件
	m_Crc.InitCrc();	//初始化CRC
	CString	AppPath = GetAppPath();	//程序路径
	CString	IniPath = AppPath + _T("httpsvc.ini");	//配置文档路径
	if (!m_IniFile.SetPath(IniPath))
	{
		//如果配置文档不存在则创建
		WRITE_LOGLINE(LOG_LEVEL_DEBUG,_T("创建配置文件 ：%s\r\n"),IniPath.GetBuffer());
		CFile	hFile;
		CFileException e;
		BOOL bRet = hFile.Open(IniPath,CFile::modeCreate, &e);
		if (!bRet)
		{
			CString strError;
			e.GetErrorMessage(strError.GetBuffer(), 1024);
			WRITE_LOGLINE(LOG_LEVEL_FATAL, _T("无法创建配置文件 : %s\r\nErrorMessage : %s\r\n"), IniPath.GetBuffer(), strError);
			return FALSE;
		}
		hFile.Close();
	}
	if (!InitIniFile())	//读取配置文件配置文件中段为空时则创建
	{
		return FALSE;
	}
	//if (!m_ThreadPool.InitThreadPool(10))
	//{
	//	//m_LogFile.WriteLog("InitThreadPool 失败！");
	//	WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","线程池初始化失败！");
	//	return FALSE;
	//}

	//初始化bt
	m_Bt.Init();
	m_FQ.Web_Init();
	m_Mzd.Init();

	m_Bm.Init();	//初始化BM
  	if (!m_Http.StartHttpServer(m_Port))
  	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","Http服务开启失败！");
  		return FALSE;
  	}
	if (!m_NoticeHttp.StartNoticeHttp(11411))
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","NoticeHttp服务开启失败！");
		return FALSE;
	}
	return TRUE;
}

//初始化读取配置文件

BOOL	CAppMain::InitIniFile()
{
	BOOL	IsIniFlag;
	IsIniFlag = m_IniFile.SectionExist(_T("FQ"));
	if (!IsIniFlag)
	{
		m_IniFile.SetKeyValue(_T("FQ"),_T("Port"),_T("10000"));
		m_IniFile.SetKeyValue(_T("FQ"),_T("ManagementName"),_T("admin"));
		m_IniFile.SetKeyValue(_T("FQ"),_T("ManagementPassWord"),_T("admin"));
		m_IniFile.SetKeyValue(_T("FQ"),_T("IsLog"),_T("0"));
		m_IniFile.SetKeyValue(_T("FQ"),_T("LoginFlags"),_T("0"));
		DWORD	ulPassWord = m_Crc.GetCrc("123456",6);
		CString	strFomat;
		strFomat.Format(_T("%X"),ulPassWord);
		m_IniFile.SetKeyValue(_T("FQ"),_T("CommunicationPassWord"),strFomat);
	}
	IsIniFlag = m_IniFile.SectionExist(_T("BT"));
	if (!IsIniFlag)
	{
		m_IniFile.SetKeyValue(_T("BT"),_T("Port"),_T("17002"));
	}
	IsIniFlag = m_IniFile.SectionExist(_T("MZD"));
	if (!IsIniFlag)
	{
		m_IniFile.SetKeyValue(_T("MZD"),_T("Port"),_T("9001"));
	}
	//IsIniFlag = m_IniFile.SectionExist(_T("BM"));
	//if (!IsIniFlag)
	//{
	//	CString	strPath = GetAppPath();
	//	m_IniFile.SetKeyValue(_T("BM"),_T("MachinePath"),strPath + _T("Hardware\\"));
	//	m_IniFile.SetKeyValue(_T("BM"),_T("StatusPath"),strPath + _T("Status\\"));
	//	m_IniFile.SetKeyValue(_T("BM"),_T("SetIniPath"),strPath + _T("ClientCfg.Ini"));
	//}
	//m_WebPath = m_IniFile.GetKeyValue(_T("FQ"),_T("Path"));
	m_Port = _ttoi(m_IniFile.GetKeyValue(_T("FQ"),_T("Port")));
	m_CommunicationPassWord = m_IniFile.GetKeyValue(_T("FQ"),_T("CommunicationPassWord"));

	m_BT_Port = _ttoi(m_IniFile.GetKeyValue(_T("BT"),_T("Port")));

	//m_MZD_Port = _ttoi(m_IniFile.GetKeyValue(_T("MZD"),_T("Port")));

	//m_HardwarePath = m_IniFile.GetKeyValue(_T("BM"),_T("MachinePath"));

	//m_StatusPath = m_IniFile.GetKeyValue(_T("BM"),_T("StatusPath"));

	//m_Bm.BmInit(m_IniFile.GetKeyValue(_T("BM"),_T("SetIniPath")));

	m_IsLog = _ttoi(m_IniFile.GetKeyValue(_T("FQ"),_T("IsLog")));

	m_IsSubServer = _ttoi(m_IniFile.GetKeyValue(_T("FQ"),_T("IsSubServer")));
	
	return TRUE;
}

int				CAppMain::isRegistration()
{
	CString	StrRegUserName = m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserName"));
	CString	StrRegUserPassWord = m_IniFile.GetKeyValue(_T("FQ"),_T("RegUserPassWord"));
	if (StrRegUserName.IsEmpty() | StrRegUserPassWord.IsEmpty())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

//************************************
// 方法名:	SetupAPI
// 全名称:	CAppMain::SetupAPI
// 访问级:	public 
// 返回值:	VOID
// 限定符:	
// 参  数:	char * lpstrPassWord
// 备  注:	初始化INI文件,设置通信密码
//************************************
BOOL		CAppMain::SetupAPI(char*	lpstrPassWord)
{
	CString	AppPath = GetAppPath();	//获取自身路径
	CString	IniPath = AppPath + _T("httpsvc.ini");	//配置文件
	if (!m_IniFile.SetPath(IniPath))
	{
		CFile	hFile;
		CFileException ex;
		if(hFile.Open(IniPath,CFile::modeCreate, &ex) == FALSE)
		{
			TCHAR strErrMsg[MAXBYTE];
			ex.GetErrorMessage(strErrMsg, MAXBYTE);
			WRITE_LOGLINE(LOG_LEVEL_FATAL, "打开配置文件 : %s\r\nErrorMsg : %s\r\n", m_IniFile, strErrMsg);
			return FALSE;
		}
		hFile.Close();
	}
	m_IniFile.SetKeyValue(_T("FQ"),_T("Port"),_T("10000"));
	m_IniFile.SetKeyValue(_T("FQ"),_T("ManagementName"),_T("admin"));
	m_IniFile.SetKeyValue(_T("FQ"),_T("ManagementPassWord"),_T("admin"));
	m_IniFile.SetKeyValue(_T("FQ"),_T("IsLog"),_T("0"));
	m_IniFile.SetKeyValue(_T("FQ"),_T("LoginFlags"),_T("0"));
	m_Crc.InitCrc();
	DWORD	ulPassWord = m_Crc.GetCrc(lpstrPassWord,strlen(lpstrPassWord));	//对数据加密
	CString	strFomat;
	strFomat.Format(_T("%X"),ulPassWord);
	m_IniFile.SetKeyValue(_T("FQ"),_T("CommunicationPassWord"),strFomat);

	//m_IniFile.SetKeyValue(_T("FQ"),_T("IsSubServer"),_T("0"));

	m_IniFile.SetKeyValue(_T("BT"),_T("Port"),_T("17002"));

	m_IniFile.SetKeyValue(_T("MZD"),_T("Port"),_T("9001"));

	//CString	strPath = GetAppPath();
	//m_IniFile.SetKeyValue(_T("BM"),_T("MachinePath"),strPath + _T("Hardware\\"));
	//m_IniFile.SetKeyValue(_T("BM"),_T("SetIniPath"),strPath + _T("Updata\\ClientCfg.Ini"));
}