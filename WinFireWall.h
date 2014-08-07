/********************************************************************
	created:	2014/03/19
	created:	19:3:2014   10:54
	filename: 	..\Common\WinFireWall\WinFireWall.h
	file path:	..\Common\WinFireWall
	file base:	WinFireWall
	file ext:	h
	author:		�
	
	purpose:   ���ڲ�������ǽ	
*********************************************************************/
#pragma once

#include <netfw.h>

//�������
enum FW_ERROR_CODE
{
	//�ɹ�
	FW_NOERROR = 0,						
	// ��ʼ��ʧ�ܻ�δ��ʼ��
	FW_ERR_INITIALIZED,					
	// �������ʧ��
	FW_ERR_CREATE_SETTING_MANAGER,		
	//��ȡfirewall����ʧ��
	FW_ERR_LOCAL_POLICY,				
	//��ȡfirewall����ʧ��
	FW_ERR_PROFILE,						
	//��Ч�Ĳ���
	FW_ERR_INVALID_ARG,					
	//��ȡ����б�ʧ��
	FW_ERR_AUTH_APPLICATIONS,			
	//�����ѻ�ȡ��Ȩ
	FW_ERR_APP_ENABLED,					
	//��ʼ��BSTRʧ��
	FW_ERR_SYS_ALLOC_STRING,			
	//���PROCESS_IMAGEʧ��
	FW_ERR_PUT_PROCESS_IMAGE_NAME,		
	//���REGISTER_NAMEʧ��
	FW_ERR_PUT_REGISTER_NAME,			
	//�������ǽʧ��
	FW_ERR_ADD_TO_COLLECTION,	

};
class CWinFireWall
{
public:
	CWinFireWall();
	~CWinFireWall();
	//************************************
	// Method:    InitializeFireWall
	// FullName:  CWinFireWall::InitializeFireWall
	// Access:    public 
	// Returns:   FW_ERROR_CODE
	// Qualifier: 
	//			  ��ʼ������ǽ�������
	//************************************
	FW_ERROR_CODE InitializeFireWall();
	//************************************
	// ������:    UninitializeFireWall
	// ����ȫ��:  CWinFireWall::UninitializeFireWall
	// ����Ȩ��:    public 
	// ����ֵ:   FW_ERROR_CODE
	// �޶���:
	// ˵��:	
	//************************************
	FW_ERROR_CODE UninitializeFireWall();
	//************************************
	// ������:    AddApplication
	// ����ȫ��:  CWinFireWall::AddApplication
	// ����Ȩ��:    public 
	// ����ֵ:   FW_ERROR_CODE
	// �޶���:
	// ����: IN const THAR * process_image_file_name
	// ����: IN const THAR * server_name
	// ˵��: ��ӳ���������ǽ
	//**********************************
	FW_ERROR_CODE AddApplication( const TCHAR *process_image_file_name,  const TCHAR *tsz_service_name);
private:
	//************************************
	// ������:    IsAppEnabled
	// ����ȫ��:  CWinFireWall::IsAppEnabled
	// ����Ȩ��:    public 
	// ����ֵ:   FW_ERROR_CODE
	// �޶���:
	// ����: IN const THAR * process_image_file_name
	// ����: OUT BOOL & enabled 
	//				    FALSE:δ��Ȩ 
	//				    TRUE:����Ȩ
	// ˵��: �������Ƿ��Ѿ���Ȩ 
	//************************************
	FW_ERROR_CODE IsAppEnabled(IN const TCHAR *process_image_file_name, OUT BOOL &enabled);
protected:
	INetFwProfile *m_p_firewall;
};