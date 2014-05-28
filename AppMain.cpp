#include "FQ_Std.h"
#include "AppMain.h"
#include "mylog.h"

//////////////////////////////////////////////////////////////////////////
//��д�ߣ�������
//////////////////////////////////////////////////////////////////////////
//ʱ�䣺2014��2��17��14:05:44

//��̬����
CAppMain*	CAppMain::m_pAppMain = NULL;
BOOL		CAppMain::m_AppFlag = TRUE;
int			CAppMain::m_Ver = 1;

CAppMain::CAppMain(void)
{
	m_IsLog = FALSE;
	m_AppHandle = NULL;

	WRITE_LOG(LOG_LEVEL_DEBUG,"%s\r\n","�����ʼ����ʼ��");
	//m_BT_IpAddress = _T("127.0.0.1");
	//m_MZD_IpAddress = _T("127.0.0.1");
}

CAppMain::~CAppMain(void)
{
}



//************************************
// ������:	GetAppMain
// ȫ����:	CAppMain::GetAppMain
// ���ʼ�:	public static 
// ����ֵ:	CAppMain*
// �޶���:	
// ��  ע:	��������,�൱��ȫ�ֱ���
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
// ������:	GetAppPath
// ȫ����:	CAppMain::GetAppPath
// ���ʼ�:	public static 
// ����ֵ:	CString
// �޶���:	
// ��  ע:	��ȡ����·��
//************************************
CString		CAppMain::GetAppPath()
{
	TCHAR	wsBuffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,wsBuffer,MAX_PATH);
	CString	StrPath(wsBuffer);
	int nPos = StrPath.ReverseFind('\\');
	return StrPath.Left(nPos + 1);
}

//��ʼ�����з���
BOOL	CAppMain::InitInstance()
{
	WRITE_LOG(LOG_LEVEL_DEBUG,"��ʼ�����з���");
	//if (!CHttp::InitSocket())
	//{
	//	return FALSE;
	//}
	m_HtmlFile.InitHtmlFile();	//��ʼ��Web�ļ�
	m_Crc.InitCrc();	//��ʼ��CRC
	CString	AppPath = GetAppPath();	//����·��
	CString	IniPath = AppPath + _T("httpsvc.ini");	//�����ĵ�·��
	if (!m_IniFile.SetPath(IniPath))
	{
		//��������ĵ��������򴴽�
		WRITE_LOGLINE(LOG_LEVEL_DEBUG,_T("���������ļ� ��%s\r\n"),IniPath.GetBuffer());
		CFile	hFile;
		CFileException e;
		BOOL bRet = hFile.Open(IniPath,CFile::modeCreate, &e);
		if (!bRet)
		{
			CString strError;
			e.GetErrorMessage(strError.GetBuffer(), 1024);
			WRITE_LOGLINE(LOG_LEVEL_FATAL, _T("�޷����������ļ� : %s\r\nErrorMessage : %s\r\n"), IniPath.GetBuffer(), strError);
			return FALSE;
		}
		hFile.Close();
	}
	if (!InitIniFile())	//��ȡ�����ļ������ļ��ж�Ϊ��ʱ�򴴽�
	{
		return FALSE;
	}
	//if (!m_ThreadPool.InitThreadPool(10))
	//{
	//	//m_LogFile.WriteLog("InitThreadPool ʧ�ܣ�");
	//	WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","�̳߳س�ʼ��ʧ�ܣ�");
	//	return FALSE;
	//}

	//��ʼ��bt
	m_Bt.Init();
	m_FQ.Web_Init();
	m_Mzd.Init();

	m_Bm.Init();	//��ʼ��BM
  	if (!m_Http.StartHttpServer(m_Port))
  	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","Http������ʧ�ܣ�");
  		return FALSE;
  	}
	if (!m_NoticeHttp.StartNoticeHttp(11411))
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,"%s\r\n","NoticeHttp������ʧ�ܣ�");
		return FALSE;
	}
	return TRUE;
}

//��ʼ����ȡ�����ļ�

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
// ������:	SetupAPI
// ȫ����:	CAppMain::SetupAPI
// ���ʼ�:	public 
// ����ֵ:	VOID
// �޶���:	
// ��  ��:	char * lpstrPassWord
// ��  ע:	��ʼ��INI�ļ�,����ͨ������
//************************************
BOOL		CAppMain::SetupAPI(char*	lpstrPassWord)
{
	CString	AppPath = GetAppPath();	//��ȡ����·��
	CString	IniPath = AppPath + _T("httpsvc.ini");	//�����ļ�
	if (!m_IniFile.SetPath(IniPath))
	{
		CFile	hFile;
		CFileException ex;
		if(hFile.Open(IniPath,CFile::modeCreate, &ex) == FALSE)
		{
			TCHAR strErrMsg[MAXBYTE];
			ex.GetErrorMessage(strErrMsg, MAXBYTE);
			WRITE_LOGLINE(LOG_LEVEL_FATAL, "�������ļ� : %s\r\nErrorMsg : %s\r\n", m_IniFile, strErrMsg);
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
	DWORD	ulPassWord = m_Crc.GetCrc(lpstrPassWord,strlen(lpstrPassWord));	//�����ݼ���
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