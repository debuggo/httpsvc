/********************************************************************
	created:	2014/03/19
	created:	19:3:2014   10:54
	filename: 	..\Common\WinFireWall\WinFireWall.h
	file path:	..\Common\WinFireWall
	file base:	WinFireWall
	file ext:	h
	author:		杨波
	
	purpose:   用于操作防火墙	
*********************************************************************/
#pragma once

#include <netfw.h>

//错误代码
enum FW_ERROR_CODE
{
	//成功
	FW_NOERROR = 0,						
	// 初始化失败或未初始化
	FW_ERR_INITIALIZED,					
	// 创建组件失败
	FW_ERR_CREATE_SETTING_MANAGER,		
	//获取firewall策略失败
	FW_ERR_LOCAL_POLICY,				
	//获取firewall配置失败
	FW_ERR_PROFILE,						
	//无效的参数
	FW_ERR_INVALID_ARG,					
	//获取软件列表失败
	FW_ERR_AUTH_APPLICATIONS,			
	//程序已获取授权
	FW_ERR_APP_ENABLED,					
	//初始化BSTR失败
	FW_ERR_SYS_ALLOC_STRING,			
	//添加PROCESS_IMAGE失败
	FW_ERR_PUT_PROCESS_IMAGE_NAME,		
	//添加REGISTER_NAME失败
	FW_ERR_PUT_REGISTER_NAME,			
	//加入防火墙失败
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
	//			  初始化防火墙管理组件
	//************************************
	FW_ERROR_CODE InitializeFireWall();
	//************************************
	// 方法名:    UninitializeFireWall
	// 方法全名:  CWinFireWall::UninitializeFireWall
	// 访问权限:    public 
	// 返回值:   FW_ERROR_CODE
	// 限定符:
	// 说明:	
	//************************************
	FW_ERROR_CODE UninitializeFireWall();
	//************************************
	// 方法名:    AddApplication
	// 方法全名:  CWinFireWall::AddApplication
	// 访问权限:    public 
	// 返回值:   FW_ERROR_CODE
	// 限定符:
	// 参数: IN const THAR * process_image_file_name
	// 参数: IN const THAR * server_name
	// 说明: 添加程序至防火墙
	//**********************************
	FW_ERROR_CODE AddApplication( const TCHAR *process_image_file_name,  const TCHAR *tsz_service_name);
private:
	//************************************
	// 方法名:    IsAppEnabled
	// 方法全名:  CWinFireWall::IsAppEnabled
	// 访问权限:    public 
	// 返回值:   FW_ERROR_CODE
	// 限定符:
	// 参数: IN const THAR * process_image_file_name
	// 参数: OUT BOOL & enabled 
	//				    FALSE:未授权 
	//				    TRUE:已授权
	// 说明: 检查程序是否已经授权 
	//************************************
	FW_ERROR_CODE IsAppEnabled(IN const TCHAR *process_image_file_name, OUT BOOL &enabled);
protected:
	INetFwProfile *m_p_firewall;
};