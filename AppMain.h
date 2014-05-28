#pragma once
#include "Http.h"
#include "IniFile.h"
#include "FQ_Socket.h"
#include "FQ_ThreadPool.h"
#include "Bt.h"
#include "FQ.h"
#include "Mzd.h"
#include "Bm.h"
#include "IocpSocket.h"
#include "FQ_Crc.h"
#include "HtmlFile.h"
#include "LogFile.h"
#include "StorageStruct.h"

class CAppMain
{
public:
	CAppMain(void);
	~CAppMain(void);
	BOOL			InitInstance();
	void			ExitInstance();
	BOOL			InitIniFile();
	BOOL			SetupAPI(char*	lpstrPassWord);
	int				isRegistration();
public:
	static	CAppMain*		GetAppMain();
	static	CString			GetAppPath();
	static	CAppMain*		m_pAppMain;
	static	BOOL			m_AppFlag;
	static	int				m_Ver;
public:
	int						m_IsSubServer;	//�Ƿ����ӷ���
	CString					m_CommunicationPassWord;	//ͨ������
	//CString					m_HardwarePath;
	//CString					m_StatusPath;
	CString					m_BT_IpAddress;
	UINT					m_BT_Port;			//BT�˿�
	UINT					m_Port;		//FQ�˿�
	HANDLE					m_AppHandle;
	CHttp					m_Http;
	CHttp					m_NoticeHttp;
	//CLogFile				m_LogFile;
	CIniFile				m_IniFile;	//�����ļ�����
	CFQ_ThreadPool			m_ThreadPool;
	BOOL					m_IsLog;	//�Ƿ�д����
	//CIocpSocket				m_IocpSocket;
	CFQ_Crc					m_Crc;
	CHtmlFile				m_HtmlFile;	//Web�ļ�
	CStorageStruct			m_StorageStrct;
	CBt						m_Bt;
	CFQ						m_FQ;
	CMzd					m_Mzd;
	CBm						m_Bm;
};