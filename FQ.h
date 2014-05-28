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
	int			Web_UserLogin(CString	strIp, CString	strJson,	CString&	strResult);				//WEB��½	30001
	int			Web_GetSubServer(CString&	strResult);									//��ȡ�Ƿ��Ǵӷ�
	int			Web_SetSubServer(CString&	strResult);				//���÷���������
	int			Web_SetServer();//����Ϊ����
	int			Web_SaveRegInfo(CString	strJson,	CString&	strResult);				//����ע����Ϣ
	int			Web_StratBtServer(CString&	strResult);									//����BT����
	int			Web_StratMzdServer(CString&	strResult);									//����MZD����
	int			Web_LoginFlags(CString	strJson,	CString&	strResult);				//�����Ƿ񱾻���½
	int			Web_GetLoginFlags(CString&	strResult);
	int			Web_OpenDir(CString	strJson,	CString&	strResult);
	//************************************
	// ������:    Web_GetBtCurrentStatus
	// ����ȫ��:  CFQ::Web_GetBtCurrentStatus
	// ����Ȩ��:    public 
	// ����ֵ:   int
	// �޶���:
	// ����: CString & strResult
	// ˵��:	����1Ϊ���� strResultΪ"0"
	//			����0Ϊ�ر� strResultΪ"1"
	//************************************
	int			Web_GetBtCurrentStatus(CString&	strResult);								//��ȡBT�ĵ�ǰ״̬	
	//************************************
	// ������:    Web_GetMZDCurrentStatus
	// ����ȫ��:  CFQ::Web_GetMZDCurrentStatus
	// ����Ȩ��:    public 
	// ����ֵ:   int
	// �޶���:
	// ����: CString & strResult
	// ˵��:	����1Ϊ���� strResultΪ"0"
	//			����0Ϊ�ر� strResultΪ"1"
	//************************************
	int			Web_GetMZDCurrentStatus(CString&	strResult);							//��ȡMZD�ĵ�ǰ״̬

	CJsonEx		m_JsonEx;
private:
	int			BT_Timer;
	int			Mzd_Timer;
};
