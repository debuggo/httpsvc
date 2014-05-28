#pragma once
#include "MzdTypedef.h"
#include "JsonEx.h"

#define		FQ_Login			300
#define		FQ_SetPassWord		301
#define		FQ_ErrorMessage		302
#define		FQ_RegStatus		303
#define		FQ_UserRegQuest		304
#define		FQ_SaveRegInfo		305
#define		FQ_RegUserInfo		808
#define		FQ_CommunicationPassWord		901
#define		FQ_SetServerIpName				902
#define		FQ_RegInfo						903

typedef	struct	_WebUserInfo
{
	wchar_t		wzsUserName[64];
	wchar_t		wzsPassWord[128];
}WebUserInfo;

typedef	struct	_tagRegInfo
{
	TCHAR		wzsUserName[64];
	TCHAR		wzsUserPassWord[128];
	TCHAR		wzsAgentId[128];
}RegInfo,	*pRegInfo;

class CFQ
{
public:
	CFQ(void);
	~CFQ(void);
	int			FQ_Meesage(int iRequestFlag, char*	pDataBuffer,CString&	StrResult);
	CString		FQ_UserLogin(CString	StrUser, CString	StrPassWord);
	CString		FQ_SetUserPassWord(CString	StrPassWord);
	CString		FQ_GetRegStatus();
	CString		FQ_UserReg(CString	UserName, CString	PassWord);
	CString		FQ_GetUserRegInfo(CString	StrServerName);
	CString		FQ_SaveReg(CString	UserName, CString	PassWord, CString	RegAgentName);
	int			FQ_SetCommunicationPassWord(CString	PassWord);
	int			FQ_RegMessageInfo();

	BOOL		Web_Init();
	int			Web_UserLogin(CString	strIp, CString	strJson,	CString&	strResult);				//WEB登陆	30001
	int			Web_GetSubServer(CString&	strResult);									//获取是否是从服
	int			Web_SetSubServer(CString&	strResult);				//设置服务器类型
	int			Web_SetServer();//设置为主服
	int			Web_SaveRegInfo(CString	strJson,	CString&	strResult);				//保存注册信息
	int			Web_StratBtServer(CString&	strResult);									//启动BT服务
	int			Web_StratMzdServer(CString&	strResult);									//启动MZD服务
	int			Web_LoginFlags(CString	strJson,	CString&	strResult);				//开关是否本机登陆
	int			Web_GetLoginFlags(CString&	strResult);
	int			Web_OpenDir(CString	strJson,	CString&	strResult);
	//************************************
	// 方法名:    Web_GetBtCurrentStatus
	// 方法全名:  CFQ::Web_GetBtCurrentStatus
	// 访问权限:    public 
	// 返回值:   int
	// 限定符:
	// 参数: CString & strResult
	// 说明:	返回1为开启 strResult为"0"
	//			返回0为关闭 strResult为"1"
	//************************************
	int			Web_GetBtCurrentStatus(CString&	strResult);								//获取BT的当前状态	
	//************************************
	// 方法名:    Web_GetMZDCurrentStatus
	// 方法全名:  CFQ::Web_GetMZDCurrentStatus
	// 访问权限:    public 
	// 返回值:   int
	// 限定符:
	// 参数: CString & strResult
	// 说明:	返回1为开启 strResult为"0"
	//			返回0为关闭 strResult为"1"
	//************************************
	int			Web_GetMZDCurrentStatus(CString&	strResult);							//获取MZD的当前状态

	CJsonEx		m_JsonEx;
private:
	int			BT_Timer;
	int			Mzd_Timer;
};
