/*************************************************************************
【文件名】                	ControlService.h,ControlService.cpp
【功能模块和目的】     		服务的控制类，实现服务的安装、删除、启动和停止操作，修改启动方式手动、自动或禁用。
【开发者及日期】          	张华(2011-10-20)
【版本】                 	v1.0
【版权信息】                Hunan Spring Copyright(2001-2011)
【更改记录】             	
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
	INT_PTR		CreateSystemService(SC_HANDLE hScm, bool bStart, bool bDll);			// 创建服务(安装服务)
	INT_PTR		StartSystemService(bool bStart, bool bDll);							// 启动服务
	BOOL		StopSystemService();							// 停止服务
	BOOL		DeleteSystemService();							// 删除服务
	BOOL		GuaranteeServiceAtuoStart(SC_HANDLE hService);	// 保证服务自动启动
	int   GetServiceStatus(const TCHAR* pszServiceName);	//查询服务状态
	inline CString ServiceStatusToCString(IN const int servicestatus)	//服务状态转文字
	{
		CString ret = _T("未知状态");

		switch(servicestatus) 
			{ 
			case SERVICE_CONTINUE_PENDING:   //0x00000005   服务继续等待。 
				ret = _T("挂起");
				break; 
			case SERVICE_PAUSE_PENDING:      //0x00000006   的服务暂停正在等待。 
				ret = _T("暂停中");
				break; 
			case SERVICE_PAUSED:      //0x00000007   该服务已暂停。 
				ret = _T("已暂停");
				break; 
			case SERVICE_RUNNING:         //0x00000004   该服务正在运行。 
				ret = _T("正在运行");
				break; 
			case SERVICE_START_PENDING:      //0x00000002   服务正在启动。 
				ret = _T("正在启动");
				break; 
			case SERVICE_STOP_PENDING:      //0x00000003   该服务被停止。 
				ret = _T("正在停止");
				break; 
			case SERVICE_STOPPED:         //0x00000001   服务没有运行。 
				ret = _T("已停止");
				break; 
			case -1:
				ret = _T("未安装");
				break;
			} 
		return ret;
	}
protected:
	TCHAR		m_szServiceName[_MAX_PATH];						// 服务名
	TCHAR		m_szDescription[_MAX_PATH];						// 服务描述
	TCHAR		m_szFilePath[_MAX_PATH];						// 服务文件路径
	TCHAR		m_szDisplayName[_MAX_PATH];						// 显示名称
	BOOL		m_bIsSystem64;
};

#endif