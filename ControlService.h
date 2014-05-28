/*************************************************************************
���ļ�����                	ControlService.h,ControlService.cpp
������ģ���Ŀ�ġ�     		����Ŀ����࣬ʵ�ַ���İ�װ��ɾ����������ֹͣ�������޸�������ʽ�ֶ����Զ�����á�
�������߼����ڡ�          	�Ż�(2011-10-20)
���汾��                 	v1.0
����Ȩ��Ϣ��                Hunan Spring Copyright(2001-2011)
�����ļ�¼��             	
*************************************************************************/

#if !defined CONTROL_SERVICE_H
#define CONTROL_SERVICE_H
#include <Winsvc.h>

class CControlServiceEx
{
public:
	CControlServiceEx();
	virtual		~CControlServiceEx();
public:
	void		SetSystemServiceInfo(TCHAR *pszServiceName, TCHAR*	pszDisplayName, TCHAR *pszDescription, TCHAR *pszFilePath);
	int         SetSystemServiceFile();
	int			SetSystemServiceFileDll();
	INT_PTR		CreateSystemService(SC_HANDLE hScm, bool bStart, bool bDll);			// ��������(��װ����)
	INT_PTR		StartSystemService(bool bStart, bool bDll);							// ��������
	BOOL		StopSystemService();							// ֹͣ����
	BOOL		DeleteSystemService();							// ɾ������
	BOOL		GuaranteeServiceAtuoStart(SC_HANDLE hService);	// ��֤�����Զ�����
	int   GetServiceStatus(const TCHAR* pszServiceName);	//��ѯ����״̬
	inline CString ServiceStatusToCString(IN const int servicestatus)	//����״̬ת����
	{
		CString ret = _T("δ֪״̬");

		switch(servicestatus) 
			{ 
			case SERVICE_CONTINUE_PENDING:   //0x00000005   ��������ȴ��� 
				ret = _T("����");
				break; 
			case SERVICE_PAUSE_PENDING:      //0x00000006   �ķ�����ͣ���ڵȴ��� 
				ret = _T("��ͣ��");
				break; 
			case SERVICE_PAUSED:      //0x00000007   �÷�������ͣ�� 
				ret = _T("����ͣ");
				break; 
			case SERVICE_RUNNING:         //0x00000004   �÷����������С� 
				ret = _T("��������");
				break; 
			case SERVICE_START_PENDING:      //0x00000002   �������������� 
				ret = _T("��������");
				break; 
			case SERVICE_STOP_PENDING:      //0x00000003   �÷���ֹͣ�� 
				ret = _T("����ֹͣ");
				break; 
			case SERVICE_STOPPED:         //0x00000001   ����û�����С� 
				ret = _T("��ֹͣ");
				break; 
			case -1:
				ret = _T("δ��װ");
				break;
			} 
		return ret;
	}
protected:
	TCHAR		m_szServiceName[_MAX_PATH];						// ������
	TCHAR		m_szDescription[_MAX_PATH];						// ��������
	TCHAR		m_szFilePath[_MAX_PATH];						// �����ļ�·��
	TCHAR		m_szDisplayName[_MAX_PATH];						// ��ʾ����
	BOOL		m_bIsSystem64;
};

#endif