#include "FQ_Std.h"
#include "Mzd.h"
#include "AppMain.h"
#include "MzdTypedef.h"
#include "ChineseCode.h"
#include "mylog.h"
#include "MZD_INI.h"
#include "BaseFunc.h"
MzdAgentInit				m_fnMzdAgtInit;
MzdAgentFree				m_fnMzdAgtFree;
GetGlobal					m_fnMzdGetGlb;
ModifyGlobal				m_fnMzdMdyGlb;
GetServerCfg				m_fnMzdGetSrvCfg;
ModifyServerCfg				m_fnMzdMdySrvCfg;
AddServerCfg				m_fnMzdAddSrvCfg;
DelServerCfg				m_fnMzdDelSrvCfg;
GetDiskSetCfg				m_fnMzdGetDiskCfg;
GetDiskSetNameList			m_fnMzdGetDiskNameList;
ModifyDiskSetCfg			m_fnMzdMdyDiskCfg;
DelDiskSetCfg				m_fnMzdDelDiskCfg;
AddDiskSetCfg				m_fnMzdAddDiskCfg;
GetWksCfg					m_fnMzdGetWksCfg;
ModifyWksCfg				m_fnMzdMdyWksCfg;
AddWksCfg					m_fnMzdAddWksCfg;
DelWksCfg					m_fnMzdDelWksCfg;
//ModifyWksCfgList			m_fnMzdModWksCount;
GetImgPartitionPhysical		m_fnMzdGetImgPrtPhi;
GetFix						m_fnMzdGetFix;
GetUdo						m_fnMzdGetUdo;
DoDiskMaitainTask			m_fnMzdDiskMtnTList;
GetDiskMaitainTaskList		m_fnMzdGetDiskMtnTList;
StartRegister				m_fnMzdStartRegst;
GetAdaptMenuCfg				m_fnMzdGetAdpMenuCfg;
GetPhysicalDiskId			m_fnMzdGetPhyDiskId;
GetServerAdaptName			m_fnMzdGetSrvAdpName;
WksCmd						m_fnMzdWksCmd;
GetServiceStatus			m_fnMzdGetServiceStatus;
CheckServerWorkDir			m_fnMzdCeckWorkDir;
ServerCmd					m_fnMzdServerCmd;
GetMZRegInfo				m_fnMzdGetMZRegInfo;
GetDiskSetCfgEx				m_fnMzdGetDiskSetCfgEx;
GetCacheInfo				m_fnMzdGetCacheInfo;
ModifyWksMac				m_fnMzdModifyWksMac;

FreeMZD_INI					m_fnMzdFreeIni;
DoCmd2MZDIO					m_fnMzdCallIni;


CMzd::CMzd(void)
{
}

CMzd::~CMzd(void)
{
}

int		CMzd::GetMzdApiCallAddress()
{
	return (int)m_fnMzdCallIni;
}

int		CMzd::GetMzdFreeAddress()
{
	return (int)m_fnMzdFreeIni;
}


//初始化MZD
BOOL	CMzd::Init()
{
	HMODULE	hMzsLib = LoadLibrary(_T("MZDAGENTLIB.dll"));
	if (hMzsLib == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"%s","无法加载MZD核心动态库文件");
		return FALSE;
	}
	m_fnMzdAgtInit = (MzdAgentInit)GetProcAddress(hMzsLib, "MzdAgentInit");
	if(NULL == m_fnMzdAgtInit) 
	{ 
		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","MzdAgentInit");
		//return FALSE; 
	}

	m_fnMzdAgtFree = (MzdAgentFree)GetProcAddress(hMzsLib, "MzdAgentRelease");
	if(NULL == m_fnMzdAgtFree) 
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","MzdAgentRelease");
		//return FALSE; 
	}

//	m_fnMzdGetGlb = (GetGlobal)GetProcAddress(hMzsLib, "GetGlobal");
//	if(NULL == m_fnMzdGetGlb) 
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetGlobal");
//		return FALSE; 
//	}
//
//	m_fnMzdMdyGlb = (ModifyGlobal)GetProcAddress(hMzsLib, "ModifyGlobal");
//	if(NULL == m_fnMzdMdyGlb) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ModifyGlobal");
//		return FALSE; 
//	}
//
//	m_fnMzdGetSrvCfg = (GetServerCfg)GetProcAddress(hMzsLib, "GetServerCfg");
//	if(NULL == m_fnMzdGetSrvCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetServerCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdMdySrvCfg = (ModifyServerCfg)GetProcAddress(hMzsLib, "ModifyServerCfg");
//	if(NULL == m_fnMzdMdySrvCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ModifyServerCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdAddSrvCfg = (AddServerCfg)GetProcAddress(hMzsLib, "AddServerCfg");
//	if(NULL == m_fnMzdAddSrvCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","AddServerCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdDelSrvCfg = (DelServerCfg)GetProcAddress(hMzsLib, "DelServerCfg");
//	if(NULL == m_fnMzdDelSrvCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","DelServerCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdGetDiskCfg = (GetDiskSetCfg)GetProcAddress(hMzsLib, "GetDiskSetCfg");
//	if(NULL == m_fnMzdGetDiskCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetDiskSetCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdGetDiskNameList = (GetDiskSetNameList)GetProcAddress(hMzsLib, "GetDiskSetNameList");
//	if(NULL == m_fnMzdGetDiskNameList) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetDiskSetNameList");
//		return FALSE; 
//	}
//
//	m_fnMzdMdyDiskCfg = (ModifyDiskSetCfg)GetProcAddress(hMzsLib, "ModifyDiskSetCfg");
//	if(NULL == m_fnMzdMdyDiskCfg) 
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ModifyDiskSetCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdDelDiskCfg = (DelDiskSetCfg)GetProcAddress(hMzsLib, "DelDiskSetCfg");
//	if(NULL == m_fnMzdDelDiskCfg) 
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","DelDiskSetCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdAddDiskCfg = (AddDiskSetCfg)GetProcAddress(hMzsLib, "AddDiskSetCfg");
//	if(NULL == m_fnMzdAddDiskCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","AddDiskSetCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdGetWksCfg = (GetWksCfg)GetProcAddress(hMzsLib, "GetWksCfg");
//	if(NULL == m_fnMzdGetWksCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetWksCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdMdyWksCfg = (ModifyWksCfg)GetProcAddress(hMzsLib, "ModifyWksCfg");
//	if(NULL == m_fnMzdMdyWksCfg) 
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ModifyWksCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdAddWksCfg = (AddWksCfg)GetProcAddress(hMzsLib, "AddWksCfg");
//	if(NULL == m_fnMzdAddWksCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","AddWksCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdDelWksCfg = (DelWksCfg)GetProcAddress(hMzsLib, "DelWksCfg");
//	if(NULL == m_fnMzdDelWksCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","DelWksCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdGetImgPrtPhi = (GetImgPartitionPhysical)GetProcAddress(hMzsLib, "GetImgPartitionPhysical");
//	if(NULL == m_fnMzdGetImgPrtPhi) 
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetImgPartitionPhysical");
//		return FALSE; 
//	}
//
//	m_fnMzdGetFix = (GetFix)GetProcAddress(hMzsLib, "GetFix");
//	if(NULL == m_fnMzdGetFix) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetFix");
//		return FALSE; 
//	}
//
//	m_fnMzdGetUdo = (GetUdo)GetProcAddress(hMzsLib, "GetUdo");
//	if(NULL == m_fnMzdGetUdo) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetUdo");
//		return FALSE; 
//	}
//
//	m_fnMzdDiskMtnTList = (DoDiskMaitainTask)GetProcAddress(hMzsLib, "DoDiskMaitainTask");
//	if(NULL == m_fnMzdDiskMtnTList) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","DoDiskMaitainTask");
//		return FALSE; 
//	}
//
//	m_fnMzdGetDiskMtnTList = (GetDiskMaitainTaskList)GetProcAddress(hMzsLib, "GetDiskMaitainTaskList");
//	if(NULL == m_fnMzdGetDiskMtnTList) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetDiskMaitainTaskList");
//		return FALSE; 
//	}
//
//	m_fnMzdStartRegst = (StartRegister)GetProcAddress(hMzsLib, "StartRegister");
//	if(NULL == m_fnMzdStartRegst) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","StartRegister");
//		return FALSE; 
//	}
//
//	m_fnMzdGetAdpMenuCfg = (GetAdaptMenuCfg)GetProcAddress(hMzsLib, "GetAdaptMenuCfg");
//	if(NULL == m_fnMzdGetAdpMenuCfg) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetAdaptMenuCfg");
//		return FALSE; 
//	}
//
//	m_fnMzdGetPhyDiskId = (GetPhysicalDiskId)GetProcAddress(hMzsLib, "GetPhysicalDiskId");
//	if(NULL == m_fnMzdGetPhyDiskId) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetPhysicalDiskId");
//		return FALSE; 
//	}
//
//	m_fnMzdGetSrvAdpName = (GetServerAdaptName)GetProcAddress(hMzsLib, "GetServerAdaptName");
//	if(NULL == m_fnMzdGetSrvAdpName) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetServerAdaptName");
//		return FALSE; 
//	}
//
//	m_fnMzdWksCmd = (WksCmd)GetProcAddress(hMzsLib,"WksCmd");
//	if(NULL == m_fnMzdWksCmd) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","WksCmd");
//		return FALSE; 
//	}
//	m_fnMzdGetServiceStatus = (GetServiceStatus)GetProcAddress(hMzsLib,"GetServiceStatus");
//	if(NULL == m_fnMzdGetServiceStatus) 
//	{ 
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetServiceStatus");
//		return FALSE; 
//	}
//// 	m_fnMzdModWksCount = (ModifyWksCfgList)GetProcAddress(hMzsLib,"ModifyWksCfgList");
//// 	if(NULL == m_fnMzdModWksCount) 
//// 	{ 
//// 		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ModifyWksCfgList");
//// 		return FALSE; 
//// 	}
//	m_fnMzdCeckWorkDir = (CheckServerWorkDir)GetProcAddress(hMzsLib,"CheckServerWorkDir");
//	if (NULL == m_fnMzdCeckWorkDir)
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","CheckServerWorkDir");
//		return FALSE; 
//	}
//	m_fnMzdServerCmd = (ServerCmd)GetProcAddress(hMzsLib,"ServerCmd");
//	if (m_fnMzdServerCmd == NULL)
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ServerCmd");
//		return FALSE; 
//	}
//	m_fnMzdGetMZRegInfo = (GetMZRegInfo)GetProcAddress(hMzsLib,"GetMZRegInfo");
//	if (m_fnMzdGetMZRegInfo == NULL)
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetMZRegInfo");
//		return FALSE; 
//	}
//	m_fnMzdGetDiskSetCfgEx = (GetDiskSetCfgEx)GetProcAddress(hMzsLib,"GetDiskSetCfgEx");
//	if (m_fnMzdGetDiskSetCfgEx == NULL)
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetDiskSetCfgEx");
//		return FALSE; 
//	}
//	m_fnMzdGetCacheInfo = (GetCacheInfo)GetProcAddress(hMzsLib,"GetCacheInfo");
//	if (m_fnMzdGetCacheInfo == NULL)
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","GetCacheInfo");
//		return FALSE; 
//	}
//	m_fnMzdModifyWksMac = (ModifyWksMac)GetProcAddress(hMzsLib,"ModifyWksMac");
//	if (m_fnMzdModifyWksMac == NULL)
//	{
//		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","ModifyWksMac");
//		return FALSE; 
//	}
	m_fnMzdFreeIni = (FreeMZD_INI)GetProcAddress(hMzsLib,"FreeMZD_INI");
	if (m_fnMzdFreeIni == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","FreeMZD_INI");
	}
	m_fnMzdCallIni = (DoCmd2MZDIO)GetProcAddress(hMzsLib,"DoCmd2MZDIO");
	if (m_fnMzdFreeIni == NULL)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"无法获取函数地址 : %s","DoCmd2MZDIO");
	}
	
	CAppMain*	pAppMain = CAppMain::GetAppMain();
	int nErrorRet = m_fnMzdAgtInit(_T("127.0.0.1"),MZD_CMD_PORT,pAppMain->m_CommunicationPassWord.GetBuffer());
	if (nErrorRet)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"MzdAgtInit错误 : %d",nErrorRet);
		return FALSE; 
	}
	if (!m_JsonEx.InitStMzd())
	{
		WRITE_LOG(LOG_LEVEL_FATAL,"Mzd Json初始化错误");
		return FALSE; 
	}
	return TRUE;
}

int		CMzd::Mzd_GetGlobal(CString &strResult)
{
	//tagGetGlobalSetEx MzdGlobalSet = { 0 };

	//MzdGlobalSet.cbSize = sizeof(tagGetGlobalSetEx);
	//MzdGlobalSet.dwFlags = 0x4;

	//int nErrorRet = m_fnMzdGetGlb(&MzdGlobalSet);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40001错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (MzdGlobalSet.cbSize != sizeof(tagGetGlobalSetEx))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40001命令需要更新！");
	//}
	//m_JsonEx.ToJsonEx(_T("tagGetGlobalSetEx"),&MzdGlobalSet,strResult);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_GLOBAL_SET_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40001错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagGetGlobalSetEx"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40001命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_SetGlobal(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagGlobalSet"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagGlobalSet*	pGlobal = (tagGlobalSet*)lpStData;
	//pGlobal->cbSize = sizeof(tagGlobalSet);
	//pGlobal->dwFlags = 0xFFFFFFFF;
	//pGlobal->dwFlags1 = 0x7;
	//
	//int nErrorRet = m_fnMzdMdyGlb(pGlobal);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40002错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	stIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagGlobalSet"),&stIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40002命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	stIni.Format2Str(strMessageFormat);

	int nErrorRet = m_fnMzdCallIni(MZD_SET_GLOBAL_SET_MSG,strMessageFormat.c_str(),NULL);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40002错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("%d"),0);
	return 1;
}

int		CMzd::Mzd_GetSvrCfg(CString &strResult)
{
	//tagServerCfg*	pSerCfg = NULL;
	//DWORD nCount;

	//int nErrorRet = m_fnMzdGetSrvCfg(nCount,&pSerCfg);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40003错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pSerCfg->cbSize != sizeof(tagServerCfg))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40003命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagServerCfg"),&pSerCfg[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pSerCfg);
	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_SERVER_LIST_MSG,NULL,&pRetData);	//获取所有服务器消息
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40003错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagServerCfg"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagServerCfg"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_ModSvrCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagModifyServer"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagModifyServer*	pSerCfg = (tagModifyServer*)lpStData;
	//pSerCfg->servercfg.cbSize = sizeof(tagModifyServer);
	//pSerCfg->servercfg.dwFlags = 0x7FF;
	//tagAddServerError	ServerErorr;

	//int nErrorRet = m_fnMzdMdySrvCfg(pSerCfg, ServerErorr);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40004错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//}
	//ServerErorr.ErorrCode = nErrorRet;
	//m_JsonEx.ToStructRelease(lpStData);
	//m_JsonEx.ToJsonEx(_T("tagAddServerError"),&ServerErorr,strResult);
	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagModifyServer"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40004命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_MODIFY_SERVER_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40004错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		//return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	OutIni.Write2INI(_T("_tagAddServerError"),0,_T("ErorrCode"),nErrorRet);
	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagAddServerError"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40004命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_AddSvrCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagAddServer"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagAddServer*	pSerCfg = (tagAddServer*)lpStData;
	//pSerCfg->cbSize = sizeof(tagAddServer);
	//pSerCfg->dwFlags = 0x7FF;

	//tagAddServerError	ServerErorr;

	//int nErrorRet = m_fnMzdAddSrvCfg(pSerCfg, ServerErorr);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40005错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//}
	//ServerErorr.ErorrCode = nErrorRet;
	//m_JsonEx.ToStructRelease(lpStData);
	//m_JsonEx.ToJsonEx(_T("tagAddServerError"),&ServerErorr,strResult);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagModifyServer"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40004命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_ADD_SERVER_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40005错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		//return -1;
	}

	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	OutIni.Write2INI(_T("_tagAddServerError"),0,_T("ErorrCode"),nErrorRet);
	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagAddServerError"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40005命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_DelSvrCfg(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagServerCfg"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagServerCfg*	pSerCfg = (tagServerCfg*)lpStData;
	//pSerCfg->cbSize = sizeof(tagServerCfg);
	//pSerCfg->dwFlags = 0x7FF;

	//int nErrorRet = m_fnMzdDelSrvCfg(pSerCfg);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40006错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagServerCfg"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40004命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	int nErrorRet = m_fnMzdCallIni(MZD_DEL_SERVER_MSG,strMessageFormat.c_str(),NULL);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40006错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("%d"),0);
	return 1;
}

int		CMzd::Mzd_GetDiskList(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagServerName"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagServerName*	pSerName = (tagServerName*)lpStData;
	//pSerName->cbSize = sizeof(tagServerName);
	//pSerName->dwFlags = 0x1;

	//DWORD nCount;
	//tagDiskSet*	pDisk = NULL;

	//int nErrorRet = m_fnMzdGetDiskCfg(pSerName,nCount,&pDisk);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40007错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pDisk->cbSize != sizeof(tagDiskSet))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40007命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagDiskSet"),&pDisk[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_JsonEx.ToStructRelease(lpStData);
	//m_fnMzdAgtFree(pDisk);
	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagServerName"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40007号命令转INI失败");
		strResult.Format(_T("5006"));
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_DISKSET_BYSERVERNAME_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40007错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagDiskSet"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagDiskSet"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetDiskNameList(CString &strResult)
{
	//tagGetDisksetNameList*	pDiskNameList = NULL;
	//DWORD nCount;

	//int nErrorRet = m_fnMzdGetDiskNameList(nCount,&pDiskNameList);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40008错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (nCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pDiskNameList->cbSize != sizeof(tagGetDisksetNameList))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40008命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < nCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagGetDisksetNameList"),&pDiskNameList[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pDiskNameList);
	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_DISK_NAMELIST_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40008错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagGetDisksetNameList"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagGetDisksetNameList"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_ModifyDiskCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagDiskSet"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagDiskSet*	pDiskSet = (tagDiskSet*)lpStData;
	//pDiskSet->cbSize = sizeof(tagDiskSet);
	//pDiskSet->dwFlags = 0xFFFFFFFF;
	//pDiskSet->dwFlags1 = 0x03;

	//int nErrorRet = m_fnMzdMdyDiskCfg(pDiskSet);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40009错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagDiskSet"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40009号命令转INI失败");
		strResult.Format(_T("5006"));
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_MODIFY_DISK_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40009错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_DelDiskCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagDiskSet"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagDiskSet*	pDiskSet = (tagDiskSet*)lpStData;
	//pDiskSet->cbSize = sizeof(tagDiskSet);
	//pDiskSet->dwFlags = 0xFFFFFFFF;
	//pDiskSet->dwFlags1 = 0x03;

	//int nErrorRet = m_fnMzdDelDiskCfg(pDiskSet);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40010错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagDiskSet"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40010号命令转INI失败");
		strResult.Format(_T("5006"));
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_DEL_DISK_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40010错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_AddDiskCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagDiskSet"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagDiskSet*	pDiskSet = (tagDiskSet*)lpStData;
	//pDiskSet->cbSize = sizeof(tagDiskSet);
	//pDiskSet->dwFlags = 0xFFFFFFFF;
	//pDiskSet->dwFlags1 = 0x03;

	//int nErrorRet = m_fnMzdAddDiskCfg(pDiskSet);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40011错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagDiskSet"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40011号命令转INI失败");
		strResult.Format(_T("5006"));
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_ADD_DISK_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40011错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_GetWksCfg(CString& strResult)
{
	//tagWkstationEx*	pWks = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetWksCfg(dwCount,&pWks);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40012错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//int		nSize = sizeof(tagWkstationEx);
	//if (pWks->cbSize != sizeof(tagWkstationEx))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40012命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagWkstationEx"),&pWks[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pWks);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_WKS_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40012错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagWkstationEx"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagWkstationEx"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_ModWksCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagModifyWksInfo"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagModifyWksInfo*	pWks = (tagModifyWksInfo*)lpStData;
	//pWks->cbSize = sizeof(tagModifyWksInfo);
	//pWks->dwFlags = 0x0F;

	//tagAddWksInfoError	ErorrWks;

	//int nErrorRet = m_fnMzdMdyWksCfg(pWks,ErorrWks);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40013错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	//return -1;
	//}
	//ErorrWks.ErorrCode = nErrorRet;
	//m_JsonEx.ToJsonEx(_T("tagAddWksInfoError"),&ErorrWks,strResult);
	//m_JsonEx.ToStructRelease(lpStData);
	////strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagModifyWksInfo"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40013命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_MODIFY_WKS_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40013错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		//return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	OutIni.Write2INI(_T("_tagAddWksInfoError"),0,_T("ErorrCode"),nErrorRet);
	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagAddWksInfoError"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40013命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_DelWksCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//int		nCount =m_JsonEx.ToStructCount(strJson,_T("tagWkstationDel"),&lpStData);
	//if (!nCount)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//DWORD*	pWksId = (DWORD*)lpStData;

	//int nErrorRet = m_fnMzdDelWksCfg(nCount,pWksId);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40014错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagDelWksStruct"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40014命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL, *pDeleteWksInfo;
	string strWksNumber = strMessageFormat.substr(strMessageFormat.find_last_of("=")+1);
	//取得工作站详细信息
	string strQueryWksInfo = GetQueryString(strWksNumber);
	int nErrorRet = m_fnMzdCallIni(MZD_GET_WKS_BY_WKSNUM_MSG, strQueryWksInfo.c_str(), &pDeleteWksInfo);

	//执行删除操作
	nErrorRet = m_fnMzdCallIni(MZD_DEL_WKS_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40014错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	else
	{
		CBm bm;
		bm.DeleteWksInfo(pDeleteWksInfo);
	}
	m_fnMzdFreeIni(pDeleteWksInfo);
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_AddWksCfg(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagAddWksInfo"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("Json转结构失败。%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagAddWksInfo*	pWks = (tagAddWksInfo*)lpStData;
	//pWks->cbSize = sizeof(tagAddWksInfo);
	//pWks->dwFlags = 0x0F;

	//tagAddWksInfoError	ErorrWks;

	//int nErrorRet = m_fnMzdAddWksCfg(pWks,ErorrWks);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40015错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	//return -1;
	//}
	//ErorrWks.ErorrCode = nErrorRet;
	//m_JsonEx.ToJsonEx(_T("tagAddWksInfoError"),&ErorrWks,strResult);
	////strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagModifyWksInfo"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40015命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_ADD_WKS_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40015错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		//return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	OutIni.Write2INI(_T("_tagAddWksInfoError"),0,_T("ErorrCode"),nErrorRet);
	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagAddWksInfoError"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40015命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_Register(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagMZDRegister"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagMZDRegister*	pRegInfo = (tagMZDRegister*)lpStData;
	//pRegInfo->cbSize = sizeof(tagMZDRegister);
	//pRegInfo->dwFlags = 0x7F;

	//int nErrorRet = m_fnMzdStartRegst(pRegInfo);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40016错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagMZDRegister"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40016命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_REGISTER_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		//1.检测是否为网络错误	nErrorRet == 8 网络错误
		if (nErrorRet == MZD_NETWORK_ERROR)
		{
			if (CAppMain::GetAppMain()->m_FQ.Web_GetMZDCurrentStatus(strResult) == 0)
			{
				nErrorRet = MZD_SERVICE_NOT_START;
			}
		}
		//2.检测是否因为服务未开启导致网络错误
		WRITE_LOG(LOG_LEVEL_ERROR,"40016错误，错误码：%d",nErrorRet);
	}
	CAppMain *pAppMain = CAppMain::GetAppMain();
	if (pAppMain->m_IniFile.GetKeyValue(_T("FQ"), _T("RegUserType")) == _T("WMB"))
	{
		strResult = _T("0");
		pAppMain->m_FQ.Web_SetServer();
	}
	else
		strResult.Format(_T("%d"),nErrorRet);
	return 1;
}

int		CMzd::Mzd_GetAdaptMenu(CString& strResult)
{
	//tagAdaptMenuSet*	pAdapMenu = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetAdpMenuCfg(dwCount,&pAdapMenu);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40017错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pAdapMenu->cbSize != sizeof(tagAdaptMenuSet))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40017命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagAdaptMenuSet"),&pAdapMenu[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pAdapMenu);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_MENU_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40017错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagAdaptMenuSet"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagAdaptMenuSet"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetPhysicalDiskId(CString& strResult)
{
	//tagPhysicalDiskId*	pPhyDisk = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetPhyDiskId(dwCount,&pPhyDisk);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40018错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pPhyDisk->cbSize != sizeof(tagPhysicalDiskId))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40018命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagPhysicalDiskId"),&pPhyDisk[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pPhyDisk);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_PHYSICALDISKID_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40018错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagPhysicalDiskId"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagPhysicalDiskId"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetImgPartitionPhysical(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagServerIp"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagServerIp*	pSerIp = (tagServerIp*)lpStData;
	//pSerIp->cbSize = sizeof(tagServerIp);
	//pSerIp->dwFlags = 0x4;

	//tagImgResponse*	pImg = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetImgPrtPhi(pSerIp,dwCount,&pImg);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40019错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pImg->cbSize != sizeof(tagImgResponse))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40019命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagImgResponse"),&pImg[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pImg);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagServerIp"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40019命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_IMG_PARTITION_PHYSICAL_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40019错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagImgResponse"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagImgResponse"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetFix(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagGetFixListRequest"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagGetFixListRequest*	pSerName = (tagGetFixListRequest*)lpStData;
	//pSerName->cbSize = sizeof(tagGetFixListRequest);
	//pSerName->dwFlags = 0x2;

	//tagFixResponse*	pFix = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetFix(pSerName,dwCount,&pFix);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40020错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pFix->cbSize != sizeof(tagFixResponse))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40020命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagFixResponse"),&pFix[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pFix);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagGetFixListRequest"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40020命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_FIX_LIST_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40020错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagFixResponse"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagFixResponse"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetUdo(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagGetUdoListRequest"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagGetUdoListRequest*	pUdo = (tagGetUdoListRequest*)lpStData;
	//pUdo->cbSize = sizeof(tagGetUdoListRequest);
	//pUdo->dwFlags = 0x2;

	//tagUdoResponse*	pUdoRet = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetUdo(pUdo,dwCount,&pUdoRet);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40021错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pUdo->cbSize != sizeof(tagUdoResponse))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40021命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagUdoResponse"),&pUdoRet[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pUdoRet);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagGetFixListRequest"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40021命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_UDO_LISG_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40021错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagFixResponse"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagFixResponse"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_DoDiskMaitainTask(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagTask"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagTask*	pTask = (tagTask*)lpStData;
	//pTask->cbSize = sizeof(tagTask);
	//pTask->dwFlags = 0x1FF;

	//int nErrorRet = m_fnMzdDiskMtnTList(pTask);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40022错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagTask"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40022命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	char*	pRetData = NULL;

	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);
	
	int nErrorRet = m_fnMzdCallIni(MZD_DISK_MAITAIN_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40022错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_GetDiskMaitainTaskList(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagServerIp"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagServerIp*	pSerName = (tagServerIp*)lpStData;
	//pSerName->cbSize = sizeof(tagServerIp);
	//pSerName->dwFlags = 0x4;

	//tagTask*	pTask = NULL;
	//DWORD	dwCount;
	//int nErrorRet = m_fnMzdGetDiskMtnTList(pSerName,dwCount,&pTask);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40023错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pTask->cbSize != sizeof(tagTask))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40023命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagTask"),&pTask[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pTask);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagServerIp"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40023命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_SERVER_TASK_LIST_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40023错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagTask"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagTask"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_WksCmd(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagWksCmd"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败！ : %s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagWksCmd*	pWksCmd = (tagWksCmd*)lpStData;
	//pWksCmd->cbSize = sizeof(tagWksCmd);
	//pWksCmd->dwFlags = 0x4;

	//int nErrorRet = m_fnMzdWksCmd(pWksCmd);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40024错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("0"));

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagWksCmd"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40024命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_WKS_CMD_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40024错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_GetSrvAdpName(CString& strResult)
{
	//tagServerAdaptName*	pSerAdaptName = NULL;
	//DWORD	dwCount;

	//int nErrorRet = m_fnMzdGetSrvAdpName(dwCount,&pSerAdaptName);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40025错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//if (dwCount == 0)
	//{
	//	strResult.Format(_T("0"));
	//	return 0;
	//}
	//if (pSerAdaptName->cbSize != sizeof(tagServerAdaptName))
	//{
	//	WRITE_LOG(LOG_LEVEL_WARN,"40025命令需要更新！");
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int i = 0; i < dwCount; i++)
	//{
	//	CString	strJson;
	//	m_JsonEx.ToJsonEx(_T("tagServerAdaptName"),&pSerAdaptName[i],strJson);
	//	strData += strJson;
	//	strData +=_T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_fnMzdAgtFree(pSerAdaptName);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_ALL_SERVER_ADAPT_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40025错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagServerAdaptName"));
	if (nCount == NULL)
	{
		strResult.Format(_T("%d"),5007);
		return -1;
	}
	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagServerAdaptName"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetServiceStatus(CString& strResult)
{
	//int		nStatus;
	//int nErrorRet = m_fnMzdGetServiceStatus(&nStatus);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40026错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("%d"),nStatus);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_SERVICE_STATUS_MSG,NULL,&pRetData);	//获取mzd服务状态
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40026错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagServiceStatus"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40026命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

//目前已经废掉了

int		CMzd::Mzd_ModWksCount(CString strJson, CString &strResult)
{
//	PVOID	lpStData = NULL;
//	if (!m_JsonEx.ToStruct(strJson,_T("tagAddWksInfo"),&lpStData))
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败.%s"),strJson.GetBuffer());
//		strResult.Format(_T("5000"));
//		return -1;
//	}
//	tagAddWksInfo*	pWks = (tagAddWksInfo*)lpStData;
//	pWks->cbSize = sizeof(tagAddWksInfo);
//	pWks->dwFlags = 0x0F;
//	int nErrorRet = 90001;//m_fnMzdModWksCount(pWks);
//	if (nErrorRet)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR,"40027错误，错误码：%d",nErrorRet);
//		strResult.Format(_T("%d"),nErrorRet);
//		return -1;
//	}
//	m_JsonEx.ToStructRelease(lpStData);
//	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_CheckWorkDir(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagCheckServerWorkDir"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败.%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagCheckServerWorkDir*	pWorkDir = (tagCheckServerWorkDir*)lpStData;
	//int nErrorRet = m_fnMzdCeckWorkDir(pWorkDir);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40028错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("tagCheckServerWorkDir"),pWorkDir,strResult);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagCheckServerWorkDir"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40028命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_SERVER_WORKDIR_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40028错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagCheckServerWorkDir"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40028命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}
	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_ServerCmd(CString strJson, CString &strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagServerCmd"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败.%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagServerCmd*	pSvcCmd = (tagServerCmd*)lpStData;
	//pSvcCmd->cbSize = sizeof(tagServerCmd);

	//int nErrorRet = m_fnMzdServerCmd(pSvcCmd);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40029错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//strResult.Format(_T("%d"),nErrorRet);
	//m_JsonEx.ToStructRelease(lpStData);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagServerCmd"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40029命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_SERVER_CMD_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40029错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	strResult.Format(_T("0"));
	return 1;
}

int		CMzd::Mzd_GetMZRegInfo(CString& strResult)
{
	//_tagMZRegInfo	MzdRegInfo = { 0 };
	//MzdRegInfo.cbSize = sizeof(tagMZRegInfo);
	//MzdRegInfo.dwFlags = 0x3F;

	//int nErrorRet = m_fnMzdGetMZRegInfo(&MzdRegInfo);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40030错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToJsonEx(_T("tagMZRegInfo"),&MzdRegInfo,strResult);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_GET_MZ_REG_MSG,NULL,&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40030错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	if (!m_JsonEx.ToJsonByIni(&OutIni,_T("_tagMZRegInfo"),0,strResult))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40030命令 转JSON失败！");
		strResult.Format(_T("%d"),5005);
		return -1;
	}

	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_GetDiskSetCfgEx(CString strJson, CString& strResult)
{
	return 1;
}

int		CMzd::Mzd_GetCacheInfo(CString strJson, CString& strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagServerIp"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败.%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//DWORD	dwMen, dwSsd;
	//tagHookCache*	pMenCache = NULL;
	//tagHookCache*	pSsdCache = NULL;
	//_tagServerIp* pSevIp = (_tagServerIp*)lpStData;
	//int nErrorRet = m_fnMzdGetCacheInfo(pSevIp,dwMen,&pMenCache,dwSsd,&pSsdCache);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40031错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//CString	strData;
	//strData += _T("{\"Array\":[");
	//for (int z = 0; z < dwMen; z++)
	//{
	//	CString	strJsonData;
	//	tagCache	stCache = { 0 };
	//	memcpy(&stCache.stHookCache,&pMenCache[z],sizeof(tagHookCache));
	//	stCache.bSsd = 0;
	//	m_JsonEx.ToJsonEx(_T("tagCache"),&stCache,strJsonData);
	//	strData += strJsonData;
	//	strData += _T(",");
	//}
	//for (int x = 0; x < dwSsd; x++)
	//{
	//	CString	strJsonData;
	//	tagCache	stCache = { 0 };
	//	memcpy(&stCache.stHookCache,&pMenCache[x],sizeof(tagHookCache));
	//	stCache.bSsd = 1;
	//	m_JsonEx.ToJsonEx(_T("tagCache"),&stCache,strJsonData);
	//	strData += strJsonData;
	//	strData += _T(",");
	//}
	//strResult = strData.Left(strData.GetLength() - 1);
	//strResult += _T("]}");
	//m_JsonEx.ToStructRelease(lpStData);
	//m_fnMzdAgtFree(pMenCache);
	//m_fnMzdAgtFree(pSsdCache);

	MZD_INI	InIni;
	if (!m_JsonEx.ToIniByJson(strJson,_T("_tagServerCmd"),&InIni))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40031命令 转Ini失败！");
		strResult.Format(_T("%d"),5006);
		return -1;
	}
	std::string	strMessageFormat;
	InIni.Format2Str(strMessageFormat);

	char*	pRetData = NULL;
	int nErrorRet = m_fnMzdCallIni(MZD_SERVER_CMD_MSG,strMessageFormat.c_str(),&pRetData);
	if (nErrorRet != NULL)
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"40031错误，错误码：%d",nErrorRet);
		strResult.Format(_T("%d"),nErrorRet);
		return -1;
	}
	MZD_INI	OutIni;
	OutIni.Load(pRetData);

	int nCount = OutIni.GetSectionNums(_T("_tagHookCache"));

	CString	strData;
	strData += _T("{\"Array\":[");
	for(int i = 0; i < nCount; i++)
	{
		CString	strJson;
		m_JsonEx.ToJsonByIni(&OutIni,_T("_tagHookCache"),i,strJson);
		strData += strJson;
		strData +=_T(",");
	}
	strResult = strData.Left(strData.GetLength() - 1);
	strResult += _T("]}");

	m_fnMzdFreeIni(pRetData);
	return 1;
}

int		CMzd::Mzd_ModifyWksMac(CString	strJson,	CString&	strResult)
{
	//PVOID	lpStData = NULL;
	//if (!m_JsonEx.ToStruct(strJson,_T("tagModifyWksInfo"),&lpStData))
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,_T("JSON转结构失败.%s"),strJson.GetBuffer());
	//	strResult.Format(_T("5000"));
	//	return -1;
	//}
	//tagModifyWksInfo*	pWksInfo = (tagModifyWksInfo*)lpStData;
	//int nErrorRet = m_fnMzdModifyWksMac(pWksInfo);
	//if (nErrorRet)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR,"40032错误，错误码：%d",nErrorRet);
	//	strResult.Format(_T("%d"),nErrorRet);
	//	return -1;
	//}
	//m_JsonEx.ToStructRelease(lpStData);
	//strResult.Format(_T("%d"),nErrorRet);
	return 1;
}

string CMzd::GetQueryString( string wksNumber )
{
	string strBuf="[_tagModifyWksInfo00000000]\r\nstartIp=\r\noldWksNumber="+wksNumber +"bIgnoreError=\r\nbAloneWks=\r\nstartNumber=\r\nendNumber=\r\nwks=_tagWkstationEx00000000\r\n[_tagWkstationEx00000000]\r\nwksNumber=\r\nwksName=\r\nwksIp=\r\nwksMac=\r\nsubMask=\r\ngateway=\r\nscrRes=\r\ngroupId=\r\nnumberLength=\r\nmenuGroup0=_tagMenuSetEx00000000\r\nmenuGroup1=_tagMenuSetEx00000001\r\nmenuGroup2=_tagMenuSetEx00000002\r\nmenuGroup3=_tagMenuSetEx00000003\r\nstartMode=0\r\nLocalMemoryCache=\r\nbStartHotBack=\r\nbAutoRestore=\r\ncomPre=\r\ncomAfx=\r\ndns1=\r\ndns2=\r\nstartServerIp=\r\nbSuperMode=\r\nbOnlineStatus=\r\nbForbidStatus=\r\nbSuperOnline=\r\n[_tagMenuSetEx00000000]\r\ndisplayname=XP\r\ndiskName0=\r\ndiskName1=\r\ndiskName2=\r\ndiskName3=\r\n[_tagMenuSetEx00000001]\r\ndisplayname=\r\ndiskName0=\r\ndiskName1=\r\ndiskName2=\r\ndiskName3=\r\n[_tagMenuSetEx00000002]\r\ndisplayname=\r\ndiskName0=\r\ndiskName1=\r\ndiskName2=\r\ndiskName3=\r\n[_tagMenuSetEx00000003]\r\ndisplayname=\r\ndiskName0=\r\ndiskName1=\r\ndiskName2=\r\ndiskName3=";
	return strBuf;
}

bool CMzd::TheWksIsExist( string wks_number )
{
	bool ret = false;
	do 
	{
		if (wks_number.length() <= 0)
		{
			WRITE_LOG(LOG_LEVEL_WARN, "\"wks_numbet\"不能为空");
			break;
		}
		char *outdata = NULL;
		if (int err = m_fnMzdCallIni(MZD_GET_WKS_MSG, NULL, &outdata) != 0)
		{
			WRITE_LOG(LOG_LEVEL_ERROR, "获取全部工作站信息时发生错误,错误原因:%s", FormatMzdErrorCode(err));
			break;
		}
		wks_number = "wksName=" + wks_number + "\r\nwksIp=";
		if (strstr(outdata, wks_number.c_str()) == NULL)
		{
			break;
		}
		ret = true;
	} while (false);
	return ret;
}

std::string CMzd::FormatMzdErrorCode( int err )
{
	string ret = "";
	switch(err)
	{
	case MZD_SUCCESS						:	ret = "成功";	break;
	case MZD_MODIFY_NAME_FAILED 			:	ret = "修改成功，但名称修改失败";	break;
	case MZD_ADD_FAILED_REASON_EXIST 		:	ret = "添加失败，存在该设置,编号存在或MAC存在";	break;
	case MZD_CFG_NOT_EXIST_ERROR 			:	ret = "不存在该设置";	break;
	case MZD_SERVER_NOT_EXIST_ERROR 		:	ret = "服务器设置不存在";	break;
	case MZD_DISKNAME_IMGPATH_ERROR 		:	ret = "磁盘名或IMG包路径错误";	break;
	case MZD_DISKSET_IS_IN_USE_ERROR 		:	ret = "磁盘设置,服务器设置正在使用中，不能删除";	break;
	case MZD_GET_REMOTE_IMG_SECTOR_ERROR 	:	ret = "获取远端扇区数失败";	break;
	case MZD_NETWORK_ERROR 					:	ret = "网络错误";	break;
	case MZD_FORBIDDEN_ERROR 				:	ret = "禁止操作";	break;
	case MZD_WKS_CFG_EXIST_ERROR 			:	ret = "工作站存在,提示是否删除";	break;
	case MZD_MODIFY_NAME_EXIST_ERROR 		:	ret = "修改名称存在,不能将其修改为该名称";	break;
	case MZD_PASSWORD_ERROR 				:	ret = "通讯密码错误";	break;
	case MZD_ILLEGAL_CONNECT_ERROR 			:	ret = "非法链接";	break;
	case MZD_MODIFY_GLOBAL_SUPERWKS_ERROR 	:	ret = "修改全局设置中修改超管失败，原超管工作站在线，需要重启该超管工作站";	break;
	case MZD_ADD_MODIFY_WKS_ERROR 			:	ret = "添加，修改失败，错误见详细描述";	break;
	case MZD_ADD_MODIFY_SERVER_ERROR 		:	ret = "添加，修改服务器失败，错误见详细描述";	break;
	case MZD_Res_Msg_Succeed 				:	ret = "操作成功";	break;
	case MZD_Res_Msg_Succeed_Login 			:	ret = "";	break;
	case MZD_Res_Msg_Succeed_Login_KEYFILE 	:	ret = "取码生成KEY文件成功";	break;
	case MZD_Res_Msg_Succeed_Verify 		:	ret = "校验成功";	break;
	case MZD_Res_Msg_Succeed_ChangePCCount 	:	ret = "更改机器台数成功";	break;
	case MZD_Res_Msg_fail_Interval 			:	ret = "取码间隔太短";	break;
	case MZD_Res_Msg_fail_HD_UnReg 			:	ret = "硬盘号未注册";	break;
	case MZD_Res_Msg_fail_IPError 			:	ret = "注册IP错误";	break;
	case MZD_Res_Msg_fail_PassErr 			:	ret = "用户密码错误";	break;
	case MZD_Res_Msg_fail_TimeOut 			:	ret = "使用期限已过         ";	break;
	case MZD_Res_Msg_fail_Active 			:	ret = "用户被限制使用";	break;
	case MZD_Res_Msg_fail_VerOld 			:	ret = "需更新版本";	break;
	case MZD_Res_Msg_fail_VerDisable 		:	ret = "此版本已限制使用";	break;
	case MZD_Res_Msg_fail_BindClinet 		:	ret = "绑定客户端需要更高版本";	break;
	case MZD_Res_Msg_fail_DEMO 				:	ret = "DEMO版";	break;
	case MZD_Res_Msg_fail_NetErr 			:	ret = "网络错误";	break;
	case MZD_Res_Msg_fail_AgentNOFail 		:	ret = "请用新代理商编码 ";	break;
	case MZD_Res_Msg_fail_Verify 			:	ret = "校验失败,时间错误";	break;
	case MZD_Res_Msg_fail_Unknown 			:	ret = "未知错误";	break;
	case MZD_Res_Msg_fail_SmsCode 			:	ret = "短信码验证错误";	break;
	case Res_Msg_fail_MobileInvalid 		:	ret = "无效的手机号码网吧业主手机号码错误";	break;
	case Res_Msg_fail_MobileBlack 			:	ret = "手机号码是黑名单";	break;
	case Res_Msg_fail_MobileProtect 		:	ret = "目标手机号码在保护名单内";	break;
	case Res_Msg_fail_MobileFail 			:	ret = "发送短信失败";	break;
	case Res_Msg_fail_Login 				:	ret = "登录失败";	break;
	case Res_Msg_fail_HDExpired 			:	ret = "硬盘已过期";	break;
	case Res_Msg_fail_Save 					:	ret = "保存数据失败";	break;
	case MZD_UNKOWN_MSG_ERROR 				:	ret = "未知消息";	break;
	case MZD_SERVICE_NOT_START 				:	ret = "服务未运行";	break;
	default:
		ret = "未知错误";
		break;
	}
	return ret;
}

// void	CMzd::Init(CString MzdServerIpAddress, UINT MzdServerPort)
// {
// 	m_MzdServerIpAddress = MzdServerIpAddress;
// 	m_MzdServerPort = MzdServerPort;
// }
// 
// BOOL	CMzd::ConnectServer()
// {
// 	CAppMain*	pAppMain = CAppMain::GetAppMain();
// 	BOOL	bResult;
// 	bResult = InitSocket(SOCK_STREAM);
// 	if (!bResult)
// 	{
// 		pAppMain->m_LogFile.WriteLog("Mzd Init InitSocket 错误");
// 		return bResult;
// 	}
// 	pAppMain->m_LogFile.WriteLog("IpAddress : %ws  --- Prot : %d",m_MzdServerIpAddress.GetBuffer(),m_MzdServerPort);
// 	bResult = Connect(m_MzdServerIpAddress,m_MzdServerPort);
// 	if (!bResult)
// 	{
// 		pAppMain->m_LogFile.WriteLog("Mzd Init Connect 错误");
// 		CAppMain::m_MzdIsOpen = FALSE;
// 		return bResult;
// 	}
// 	CAppMain::m_MzdIsOpen = TRUE;
// 	return bResult;
// }
// 
// int		CMzd::GetColumnList(CStringArray& ColumnList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_DEFAULT_COLUMN_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	CString		StrResult;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	ColumnCheckStatus	Mzd_Column;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		iSocketRet = Receive(&Mzd_Column,sizeof(ColumnCheckStatus));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			return -1;
// 		}
// 		CString	StrColumn(Mzd_Column.columnName);
// 		CString	StrWks;
// 		StrWks.Format(_T("['%s','%ld',],"),StrColumn,Mzd_Column.bShow);
// 		ColumnList.Add(StrWks);
// 	}
// 	return 1;
// }
// 
// int 	CMzd::GetWkstation(CStringArray		&WksArray)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_WKS_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	CString		StrResult;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(Wkstation));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += sizeof(Wkstation);
// 	}
// 	Wkstation*	pWkstation = (Wkstation*)pbBuffer;
// 	for (int iCount = 0; iCount < Mzd_Reply_Head.dwCount; iCount++)
// 	{
// 		CString	StrWksData;
// 		int		iWksIsDisable;
// 		if (pWkstation->isDisable)
// 		{
// 			iWksIsDisable = 1;
// 		}
// 		else
// 		{
// 			iWksIsDisable = 0;
// 		}
// 		sockaddr_in stAddr = { 0 };
// 		stAddr.sin_addr.S_un.S_addr = pWkstation->wksIp;
// 		CString	StrWksIp(inet_ntoa(stAddr.sin_addr));
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 
// 		CString	StrWksMac(pWkstation->strMac);
// 		CString	StrWksName(pWkstation->comName);
// 		CString	StrWksUserName(pWkstation->userName);
// 		CString	StrWksUserPassWord(pWkstation->password);
// 		CString	StrConfigSet(pWkstation->currSetCfg);
// 		CString	StrMenuName(pWkstation->menuName);
// 		CString StrInputName(pWkstation->inputName);
// 		CString	StrInputPass(pWkstation->inputPass);
// 		CString	Stradaptname(pWkstation->adaptname);
// 
// 		stAddr.sin_addr.S_un.S_addr = pWkstation->serverIp;
// 		CString StrServerIp(inet_ntoa(stAddr.sin_addr));
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 
// 		stAddr.sin_addr.S_un.S_addr = pWkstation->dhcpGateway;
// 		CString StrdhcpGateway(inet_ntoa(stAddr.sin_addr));
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 
// 		stAddr.sin_addr.S_un.S_addr = pWkstation->subMask;
// 		CString StrsubMask(inet_ntoa(stAddr.sin_addr));
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 
// 		wchar_t	lpwzsDiskSetName0[64] = { 0 };
// 		CString	StrarDiskSetName0(pWkstation->arDiskSetName[0]);
// 		AddChar(StrarDiskSetName0.GetBuffer(),lpwzsDiskSetName0,64);
// 
// 		wchar_t	lpwzsDiskSetName1[64] = { 0 };
// 		CString	StrarDiskSetName1(pWkstation->arDiskSetName[1]);
// 		AddChar(StrarDiskSetName1.GetBuffer(),lpwzsDiskSetName1,64);
// 
// 		wchar_t	lpwzsDiskSetName2[64] = { 0 };
// 		CString	StrarDiskSetName2(pWkstation->arDiskSetName[2]);
// 		AddChar(StrarDiskSetName2.GetBuffer(),lpwzsDiskSetName2,64);
// 
// 		wchar_t	lpwzsDiskSetName3[64] = { 0 };
// 		CString	StrarDiskSetName3(pWkstation->arDiskSetName[3]);
// 		AddChar(StrarDiskSetName3.GetBuffer(),lpwzsDiskSetName3,64);
// 
// 		wchar_t lpwzsDestinationFile0[64] = { 0 };
// 		CString	StrarDestinationFile0(pWkstation->arDestinationFile[0]);
// 		AddChar(StrarDestinationFile0.GetBuffer(),lpwzsDestinationFile0,64);
// 
// 		wchar_t	lpwzsDestinationFile1[64] = { 0 };
// 		CString	StrarDestinationFile1(pWkstation->arDestinationFile[1]);
// 		AddChar(StrarDestinationFile1.GetBuffer(),lpwzsDestinationFile1,64);
// 
// 		wchar_t	lpwzsDestinationFile2[64] = { 0 };
// 		CString	StrarDestinationFile2(pWkstation->arDestinationFile[2]);
// 		AddChar(StrarDestinationFile2.GetBuffer(),lpwzsDestinationFile2,64);
// 
// 		wchar_t	lpwzsDestinationFile3[64] = { 0 };
// 		CString	StrarDestinationFile3(pWkstation->arDestinationFile[3]);
// 		AddChar(StrarDestinationFile3.GetBuffer(),lpwzsDestinationFile3,64);
// 
// 		wchar_t	lpwzsDiskWorkDir0[64] = { 0 };
// 		CString	StrarDiskWorkDir0(pWkstation->arDiskWorkDir[0]);
// 		AddChar(StrarDiskWorkDir0.GetBuffer(),lpwzsDiskWorkDir0,64);
// 
// 		wchar_t	lpwzsDiskWorkDir1[64] = { 0 };
// 		CString	StrarDiskWorkDir1(pWkstation->arDiskWorkDir[1]);
// 		AddChar(StrarDiskWorkDir1.GetBuffer(),lpwzsDiskWorkDir1,64);
// 
// 		wchar_t	lpwzsDiskWorkDir2[64] = { 0 };
// 		CString	StrarDiskWorkDir2(pWkstation->arDiskWorkDir[2]);
// 		AddChar(StrarDiskWorkDir2.GetBuffer(),lpwzsDiskWorkDir2,64);
// 
// 		wchar_t	lpwzsDiskWorkDir3[64] = { 0 };
// 		CString	StrarDiskWorkDir3(pWkstation->arDiskWorkDir[3]);
// 		AddChar(StrarDiskWorkDir3.GetBuffer(),lpwzsDiskWorkDir3,64);
// 		StrWksData.Format(_T("['%d','%d','%ld','%d','%x','%d','%s','%d','%d','%ld','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%ld','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d'],"),
// 			pWkstation->wksNumber,
// 			pWkstation->loginID,
// 			pWkstation->wksCmdCfg,
// 			pWkstation->wksMode,
// 			pWkstation->userType,
// 			iWksIsDisable,
// 			StrWksIp,
// 			pWkstation->randKey,
// 			pWkstation->loginIPLow,
// 			pWkstation->userSelectCmd,
// 			StrWksMac,
// 			StrWksName,
// 			StrConfigSet,
// 			StrMenuName,
// 			StrWksUserName,
// 			StrWksUserPassWord,
// 			StrInputName,
// 			StrInputPass,
// 			Stradaptname,
// 			StrServerIp,
// 			StrdhcpGateway,
// 			StrsubMask,
// 			pWkstation->clientPort,
// 			pWkstation->wksMemory,
// 			lpwzsDiskSetName0,
// 			lpwzsDiskSetName1,
// 			lpwzsDiskSetName2,
// 			lpwzsDiskSetName3,
// 			lpwzsDestinationFile0,
// 			lpwzsDestinationFile1,
// 			lpwzsDestinationFile2,
// 			lpwzsDestinationFile3,
// 			lpwzsDiskWorkDir0,
// 			lpwzsDiskWorkDir1,
// 			lpwzsDiskWorkDir2,
// 			lpwzsDiskWorkDir3,
// 			pWkstation->RestartAutoClear);
// 		WksArray.Add(StrWksData);
// 		pWkstation++;
// 	}
// 	delete []pbBuffer;
// 	return 1;
// }
// 
// int		CMzd::LoadWkstation(Wkstation* pWkstation, char* pDataBuffer)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[64] = { 0 };
// 	pPos = strstr(pDataBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 		pWkstation->wksNumber = atoi(szBuffer);
// 		pDataBuffer += strlen(szBuffer);
// 		pDataBuffer += iSeparate;
// 		memset(szBuffer,0,64);
// 		pPos = strstr(pDataBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 			pWkstation->loginID = atoi(szBuffer);
// 			pDataBuffer += strlen(szBuffer);
// 			pDataBuffer += iSeparate;
// 			memset(szBuffer,0,64);
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				pWkstation->wksCmdCfg = atol(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					pWkstation->wksMode = atoi(szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						pWkstation->userType = atoi(szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							pWkstation->isDisable = atoi(szBuffer);
// 							pDataBuffer += strlen(szBuffer);
// 							pDataBuffer += iSeparate;
// 							memset(szBuffer,0,64);
// 							pPos = strstr(pDataBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 								pWkstation->wksIp = inet_addr(szBuffer);
// 								pDataBuffer += strlen(szBuffer);
// 								pDataBuffer += iSeparate;
// 								memset(szBuffer,0,64);
// 								pPos = strstr(pDataBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 									pWkstation->randKey = atoi(szBuffer);
// 									pDataBuffer += strlen(szBuffer);
// 									pDataBuffer += iSeparate;
// 									memset(szBuffer,0,64);
// 									pPos = strstr(pDataBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 										pWkstation->loginIPLow = atoi(szBuffer);
// 										pDataBuffer += strlen(szBuffer);
// 										pDataBuffer += iSeparate;
// 										memset(szBuffer,0,64);
// 										pPos = strstr(pDataBuffer,"&nbsp");
// 										if (pPos)
// 										{
// 											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 											pWkstation->userSelectCmd = atol(szBuffer);
// 											pDataBuffer += strlen(szBuffer);
// 											pDataBuffer += iSeparate;
// 											memset(szBuffer,0,64);
// 											pPos = strstr(pDataBuffer,"&nbsp");
// 											if (pPos)
// 											{
// 												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 												strcpy(pWkstation->strMac,szBuffer);
// 												pDataBuffer += strlen(szBuffer);
// 												pDataBuffer += iSeparate;
// 												memset(szBuffer,0,64);
// 												pPos = strstr(pDataBuffer,"&nbsp");
// 												if (pPos)
// 												{
// 													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 													//strcpy(pWkstation->comName,szBuffer);
// 													CChineseCode::Utf8ToAscii(szBuffer,pWkstation->comName);
// 													pDataBuffer += strlen(szBuffer);
// 													pDataBuffer += iSeparate;
// 													memset(szBuffer,0,64);
// 													pPos = strstr(pDataBuffer,"&nbsp");
// 													if (pPos)
// 													{
// 														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 														//strcpy(pWkstation->currSetCfg,szBuffer);
// 														CChineseCode::Utf8ToAscii(szBuffer,pWkstation->currSetCfg);
// 														pDataBuffer += strlen(szBuffer);
// 														pDataBuffer += iSeparate;
// 														memset(szBuffer,0,64);
// 														pPos = strstr(pDataBuffer,"&nbsp");
// 														if (pPos)
// 														{
// 															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 															//strcpy(pWkstation->menuName,szBuffer);
// 															CChineseCode::Utf8ToAscii(szBuffer,pWkstation->menuName);
// 															pDataBuffer += strlen(szBuffer);
// 															pDataBuffer += iSeparate;
// 															memset(szBuffer,0,64);
// 															pPos = strstr(pDataBuffer,"&nbsp");
// 															if (pPos)
// 															{
// 																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																//strcpy(pWkstation->userName,szBuffer);
// 																CChineseCode::Utf8ToAscii(szBuffer,pWkstation->userName);
// 																pDataBuffer += strlen(szBuffer);
// 																pDataBuffer += iSeparate;
// 																memset(szBuffer,0,64);
// 																pPos = strstr(pDataBuffer,"&nbsp");
// 																if (pPos)
// 																{
// 																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																	//strcpy(pWkstation->password,szBuffer);
// 																	CChineseCode::Utf8ToAscii(szBuffer,pWkstation->password);
// 																	pDataBuffer += strlen(szBuffer);
// 																	pDataBuffer += iSeparate;
// 																	memset(szBuffer,0,64);
// 																	pPos = strstr(pDataBuffer,"&nbsp");
// 																	if (pPos)
// 																	{
// 																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																		//strcpy(pWkstation->inputName,szBuffer);
// 																		CChineseCode::Utf8ToAscii(szBuffer,pWkstation->inputName);
// 																		pDataBuffer += strlen(szBuffer);
// 																		pDataBuffer += iSeparate;
// 																		memset(szBuffer,0,64);
// 																		pPos = strstr(pDataBuffer,"&nbsp");
// 																		if (pPos)
// 																		{
// 																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																			//strcpy(pWkstation->inputPass,szBuffer);
// 																			CChineseCode::Utf8ToAscii(szBuffer,pWkstation->inputPass);
// 																			pDataBuffer += strlen(szBuffer);
// 																			pDataBuffer += iSeparate;
// 																			memset(szBuffer,0,64);
// 																			pPos = strstr(pDataBuffer,"&nbsp");
// 																			if (pPos)
// 																			{
// 																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																				//strcpy(pWkstation->adaptname,szBuffer);
// 																				CChineseCode::Utf8ToAscii(szBuffer,pWkstation->adaptname);
// 																				pDataBuffer += strlen(szBuffer);
// 																				pDataBuffer += iSeparate;
// 																				memset(szBuffer,0,64);
// 																				pPos = strstr(pDataBuffer,"&nbsp");
// 																				if (pPos)
// 																				{
// 																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																					pWkstation->serverIp = inet_addr(szBuffer);
// 																					pDataBuffer += strlen(szBuffer);
// 																					pDataBuffer += iSeparate;
// 																					memset(szBuffer,0,64);
// 																					pPos = strstr(pDataBuffer,"&nbsp");
// 																					if (pPos)
// 																					{
// 																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																						pWkstation->dhcpGateway = inet_addr(szBuffer);
// 																						pDataBuffer += strlen(szBuffer);
// 																						pDataBuffer += iSeparate;
// 																						memset(szBuffer,0,64);
// 																						pPos = strstr(pDataBuffer,"&nbsp");
// 																						if (pPos)
// 																						{
// 																							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																							pWkstation->subMask = inet_addr(szBuffer);
// 																							pDataBuffer += strlen(szBuffer);
// 																							pDataBuffer += iSeparate;
// 																							memset(szBuffer,0,64);
// 																							pPos = strstr(pDataBuffer,"&nbsp");
// 																							if (pPos)
// 																							{
// 																								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																								pWkstation->clientPort = atoi(szBuffer);
// 																								pDataBuffer += strlen(szBuffer);
// 																								pDataBuffer += iSeparate;
// 																								memset(szBuffer,0,64);
// 																								pPos = strstr(pDataBuffer,"&nbsp");
// 																								if (pPos)
// 																								{
// 																									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																									pWkstation->wksMemory = atoi(szBuffer);
// 																									pDataBuffer += strlen(szBuffer);
// 																									pDataBuffer += iSeparate;
// 																									memset(szBuffer,0,64);
// 																									pPos = strstr(pDataBuffer,"&nbsp");
// 																									if (pPos)
// 																									{
// 																										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																										//strcpy(pWkstation->arDiskSetName[0],szBuffer);
// 																										CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskSetName[0]);
// 																										pDataBuffer += strlen(szBuffer);
// 																										pDataBuffer += iSeparate;
// 																										memset(szBuffer,0,64);
// 																										pPos = strstr(pDataBuffer,"&nbsp");
// 																										if (pPos)
// 																										{
// 																											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																											//strcpy(pWkstation->arDiskSetName[1],szBuffer);
// 																											CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskSetName[1]);
// 																											pDataBuffer += strlen(szBuffer);
// 																											pDataBuffer += iSeparate;
// 																											memset(szBuffer,0,64);
// 																											pPos = strstr(pDataBuffer,"&nbsp");
// 																											if (pPos)
// 																											{
// 																												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																												//strcpy(pWkstation->arDiskSetName[2],szBuffer);
// 																												CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskSetName[2]);
// 																												pDataBuffer += strlen(szBuffer);
// 																												pDataBuffer += iSeparate;
// 																												memset(szBuffer,0,64);
// 																												pPos = strstr(pDataBuffer,"&nbsp");
// 																												if (pPos)
// 																												{
// 																													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																													//strcpy(pWkstation->arDiskSetName[3],szBuffer);
// 																													CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskSetName[3]);
// 																													pDataBuffer += strlen(szBuffer);
// 																													pDataBuffer += iSeparate;
// 																													memset(szBuffer,0,64);
// 																													pPos = strstr(pDataBuffer,"&nbsp");
// 																													if (pPos)
// 																													{
// 																														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																														//strcpy(pWkstation->arDestinationFile[0],szBuffer);
// 																														CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDestinationFile[0]);
// 																														pDataBuffer += strlen(szBuffer);
// 																														pDataBuffer += iSeparate;
// 																														memset(szBuffer,0,64);
// 																														pPos = strstr(pDataBuffer,"&nbsp");
// 																														if (pPos)
// 																														{
// 																															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																															//strcpy(pWkstation->arDestinationFile[1],szBuffer);
// 																															CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDestinationFile[1]);
// 																															pDataBuffer += strlen(szBuffer);
// 																															pDataBuffer += iSeparate;
// 																															memset(szBuffer,0,64);
// 																															pPos = strstr(pDataBuffer,"&nbsp");
// 																															if (pPos)
// 																															{
// 																																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																//strcpy(pWkstation->arDestinationFile[2],szBuffer);
// 																																CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDestinationFile[2]);
// 																																pDataBuffer += strlen(szBuffer);
// 																																pDataBuffer += iSeparate;
// 																																memset(szBuffer,0,64);
// 																																pPos = strstr(pDataBuffer,"&nbsp");
// 																																if (pPos)
// 																																{
// 																																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																	//strcpy(pWkstation->arDestinationFile[3],szBuffer);
// 																																	CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDestinationFile[3]);
// 																																	pDataBuffer += strlen(szBuffer);
// 																																	pDataBuffer += iSeparate;
// 																																	memset(szBuffer,0,64);
// 																																	pPos = strstr(pDataBuffer,"&nbsp");
// 																																	if (pPos)
// 																																	{
// 																																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																		//strcpy(pWkstation->arDiskWorkDir[0],szBuffer);
// 																																		CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskWorkDir[0]);
// 																																		pDataBuffer += strlen(szBuffer);
// 																																		pDataBuffer += iSeparate;
// 																																		memset(szBuffer,0,64);
// 																																		pPos = strstr(pDataBuffer,"&nbsp");
// 																																		if (pPos)
// 																																		{
// 																																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																			//strcpy(pWkstation->arDiskWorkDir[1],szBuffer);
// 																																			CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskWorkDir[1]);
// 																																			pDataBuffer += strlen(szBuffer);
// 																																			pDataBuffer += iSeparate;
// 																																			memset(szBuffer,0,64);
// 																																			pPos = strstr(pDataBuffer,"&nbsp");
// 																																			if (pPos)
// 																																			{
// 																																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																				//strcpy(pWkstation->arDiskWorkDir[2],szBuffer);
// 																																				CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskWorkDir[2]);
// 																																				pDataBuffer += strlen(szBuffer);
// 																																				pDataBuffer += iSeparate;
// 																																				memset(szBuffer,0,64);
// 																																				pPos = strstr(pDataBuffer,"&nbsp");
// 																																				if (pPos)
// 																																				{
// 																																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																					//strcpy(pWkstation->arDiskWorkDir[3],szBuffer);
// 																																					CChineseCode::Utf8ToAscii(szBuffer,pWkstation->arDiskWorkDir[3]);
// 																																					pDataBuffer += strlen(szBuffer);
// 																																					pDataBuffer += iSeparate;
// 																																					memset(szBuffer,0,64);
// 																																					pPos = strstr(pDataBuffer,"&nbsp");
// 																																					if (pPos)
// 																																					{
// 																																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																						pWkstation->RestartAutoClear = atoi(szBuffer);
// 																																						pDataBuffer += strlen(szBuffer);
// 																																						pDataBuffer += iSeparate;
// 																																						memset(szBuffer,0,64);
// 																																						return 1;
// 																																					}
// 																																				}
// 																																			}
// 																																		}
// 																																	}
// 																																}
// 																															}
// 																														}
// 																													}
// 																												}
// 																											}
// 																										}
// 																									}
// 																								}
// 																							}
// 																						}
// 																					}
// 																				}
// 																			}
// 																		}
// 																	}
// 																}
// 															}
// 														}
// 													}
// 												}
// 											}
// 										}
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// CString	CMzd::GetGlobalInfo()
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_GLOBAL_SET_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	CString		StrResult;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	GlobalSetEx	Mzd_Global;
// 	iSocketRet = Receive(&Mzd_Global,sizeof(GlobalSetEx));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	TCHAR	wszwksDefPassword[64] = { 0 };
// 	TCHAR	wzsundoDir[64] = { 0 };
// 	TCHAR	wzsWksWorkDir[64] = { 0 };
// 	TCHAR	wzsrunExternal[256] = { 0 };
// 	TCHAR	wzsLanguagePack[255] = { 0 };
// 	CChineseCode::Utf8ToUniCode(Mzd_Global.globalset.wksDefPassword,wszwksDefPassword);
// 
// 	sockaddr_in stAddr = { 0 };
// 	stAddr.sin_addr.S_un.S_addr = Mzd_Global.globalset.loginServerIP;
// 	CString	StrLoginServerIP(inet_ntoa(stAddr.sin_addr));
// 
// 
// 	CString	StrregDomainAddress(Mzd_Global.globalset.regDomainAddress);
// 	CString	StrSsdPartition(Mzd_Global.globalset.m_SsdPartition);
// 
// 	CString	StrWksWorkDir(Mzd_Global.globalset.m_WksWorkDir);
// 	CString	StrundoDir(Mzd_Global.globalset.undoDir);
// 	CString	StrremoveIp(Mzd_Global.globalset.removeIp);
// 	CString	StrwzsrunExternal(Mzd_Global.globalset.runExternal);
// 	CString	StrLanguagePack(Mzd_Global.globalset.LanguagePack);
// 
// 	AddChar(StrundoDir.GetBuffer(),(wchar_t*)wzsundoDir,64);
// 	AddChar(StrWksWorkDir.GetBuffer(),(wchar_t*)wzsWksWorkDir,64);
// 	AddChar(StrwzsrunExternal.GetBuffer(),wzsrunExternal,256);
// 	AddChar(StrLanguagePack.GetBuffer(),wzsLanguagePack,255);
// 
// 	CString	strDiskKey(Mzd_Global.RegisterHdid);
// 	CString	strDiskKey2(Mzd_Global.spareRegisterHdid);
// 
// 	StrResult.Format(_T("1&nbsp['%d','%s','%ld','%s','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s','%s','%s','%d','%d','%d','%d','%d','%d','%d','%s','%d','%s','%ld','%s','%s','%ld','%ld','%ld','%s','%s']"),
// 		Mzd_Global.globalset.undoNums,
// 		wszwksDefPassword,
// 		Mzd_Global.globalset.passwordCrc,
// 		wzsundoDir,
// 		Mzd_Global.globalset.isDisableTelnet,
// 		Mzd_Global.globalset.isDisableDebug,
// 		Mzd_Global.globalset.isShowRegFMFlag,
// 		Mzd_Global.globalset.dhcpFastMode,
// 		Mzd_Global.globalset.fixFormat,
// 		Mzd_Global.globalset.isWanTonFlag,
// 		Mzd_Global.globalset.isEnableStrap,
// 		Mzd_Global.globalset.isAutoNumber,
// 		Mzd_Global.globalset.isAutoAdd,
// 		Mzd_Global.globalset.isCompulsoryNumber,
// 		Mzd_Global.globalset.isDisableDhcp,
// 		StrregDomainAddress,
// 		StrremoveIp,
// 		StrLoginServerIP,
// 		Mzd_Global.globalset.superWks,
// 		Mzd_Global.globalset.isEnableSysDiskForSuperWks,
// 		Mzd_Global.globalset.isEnableDataDisk1ForSuperWks,
// 		Mzd_Global.globalset.isEnableDataDisk2ForSuperWks,
// 		Mzd_Global.globalset.isEnableDataDisk3ForSuperWks,
// 		Mzd_Global.globalset.isDhcpQuickResponse,
// 		Mzd_Global.globalset.isAutoSyncUpdateForSuperWks,
// 		wzsrunExternal,
// 		Mzd_Global.globalset.isWaitCompleted,
// 		wzsLanguagePack,
// 		Mzd_Global.globalset.m_MemType,
// 		wzsWksWorkDir,
// 		StrSsdPartition,
// 		Mzd_Global.globalset.bRestartRestore,
// 		Mzd_Global.globalset.m_LastUpdateTime,
// 		Mzd_Global.globalset.m_Loglevel,
// 		strDiskKey,
// 		strDiskKey2);
// 	return StrResult;
// }
// 
// int		CMzd::LoadGlobalSet(GlobalSet* pGlobalSet, char* pDataBuffer)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[255] = { 0 };
// 	pPos = strstr(pDataBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 		pGlobalSet->undoNums = atoi(szBuffer);
// 		pDataBuffer += iSeparate;
// 		pDataBuffer += strlen(szBuffer);
// 		memset(szBuffer,0,255);
// 		pPos = strstr(pDataBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 			strcpy(pGlobalSet->wksDefPassword,szBuffer);
// 			pDataBuffer += iSeparate;
// 			pDataBuffer += strlen(szBuffer);
// 			memset(szBuffer,0,255);
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				pGlobalSet->passwordCrc = atoi(szBuffer);
// 				pDataBuffer += iSeparate;
// 				pDataBuffer += strlen(szBuffer);
// 				memset(szBuffer,0,255);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(pGlobalSet->undoDir,szBuffer);
// 					pDataBuffer += iSeparate;
// 					pDataBuffer += strlen(szBuffer);
// 					memset(szBuffer,0,255);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						pGlobalSet->isDisableTelnet = atoi(szBuffer);
// 						pDataBuffer += iSeparate;
// 						pDataBuffer += strlen(szBuffer);
// 						memset(szBuffer,0,255);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							pGlobalSet->isDisableDebug = atoi(szBuffer);
// 							pDataBuffer += iSeparate;
// 							pDataBuffer += strlen(szBuffer);
// 							memset(szBuffer,0,255);
// 							pPos = strstr(pDataBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 								pGlobalSet->isShowRegFMFlag = atoi(szBuffer);
// 								pDataBuffer += iSeparate;
// 								pDataBuffer += strlen(szBuffer);
// 								memset(szBuffer,0,255);
// 								pPos = strstr(pDataBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 									pGlobalSet->dhcpFastMode = atoi(szBuffer);
// 									pDataBuffer += iSeparate;
// 									pDataBuffer += strlen(szBuffer);
// 									memset(szBuffer,0,255);
// 									pPos = strstr(pDataBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 										pGlobalSet->fixFormat = atoi(szBuffer);
// 										pDataBuffer += iSeparate;
// 										pDataBuffer += strlen(szBuffer);
// 										memset(szBuffer,0,255);
// 										pPos = strstr(pDataBuffer,"&nbsp");
// 										if (pPos)
// 										{
// 											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 											pGlobalSet->isWanTonFlag = atoi(szBuffer);
// 											pDataBuffer += iSeparate;
// 											pDataBuffer += strlen(szBuffer);
// 											memset(szBuffer,0,255);
// 											pPos = strstr(pDataBuffer,"&nbsp");
// 											if (pPos)
// 											{
// 												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 												pGlobalSet->isEnableStrap = atoi(szBuffer);
// 												pDataBuffer += iSeparate;
// 												pDataBuffer += strlen(szBuffer);
// 												memset(szBuffer,0,255);
// 												pPos = strstr(pDataBuffer,"&nbsp");
// 												if (pPos)
// 												{
// 													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 													pGlobalSet->isAutoNumber = atoi(szBuffer);
// 													pDataBuffer += iSeparate;
// 													pDataBuffer += strlen(szBuffer);
// 													memset(szBuffer,0,255);
// 													pPos = strstr(pDataBuffer,"&nbsp");
// 													if (pPos)
// 													{
// 														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 														pGlobalSet->isAutoAdd = atoi(szBuffer);
// 														pDataBuffer += iSeparate;
// 														pDataBuffer += strlen(szBuffer);
// 														memset(szBuffer,0,255);
// 														pPos = strstr(pDataBuffer,"&nbsp");
// 														if (pPos)
// 														{
// 															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 															pGlobalSet->isCompulsoryNumber = atoi(szBuffer);
// 															pDataBuffer += iSeparate;
// 															pDataBuffer += strlen(szBuffer);
// 															memset(szBuffer,0,255);
// 															pPos = strstr(pDataBuffer,"&nbsp");
// 															if (pPos)
// 															{
// 																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																pGlobalSet->isDisableDhcp = atoi(szBuffer);
// 																pDataBuffer += iSeparate;
// 																pDataBuffer += strlen(szBuffer);
// 																memset(szBuffer,0,255);
// 																pPos = strstr(pDataBuffer,"&nbsp");
// 																if (pPos)
// 																{
// 																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																	strcpy(pGlobalSet->regDomainAddress,szBuffer);
// 																	pDataBuffer += iSeparate;
// 																	pDataBuffer += strlen(szBuffer);
// 																	memset(szBuffer,0,255);
// 																	pPos = strstr(pDataBuffer,"&nbsp");
// 																	if (pPos)
// 																	{
// 																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																		strcpy(pGlobalSet->removeIp,szBuffer);
// 																		pDataBuffer += iSeparate;
// 																		pDataBuffer += strlen(szBuffer);
// 																		memset(szBuffer,0,255);
// 																		pPos = strstr(pDataBuffer,"&nbsp");
// 																		if (pPos)
// 																		{
// 																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																			pGlobalSet->loginServerIP = inet_addr(szBuffer);
// 																			pDataBuffer += iSeparate;
// 																			pDataBuffer += strlen(szBuffer);
// 																			memset(szBuffer,0,255);
// 																			pPos = strstr(pDataBuffer,"&nbsp");
// 																			if (pPos)
// 																			{
// 																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																				pGlobalSet->superWks = atoi(szBuffer);
// 																				pDataBuffer += iSeparate;
// 																				pDataBuffer += strlen(szBuffer);
// 																				memset(szBuffer,0,255);
// 																				pPos = strstr(pDataBuffer,"&nbsp");
// 																				if (pPos)
// 																				{
// 																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																					pGlobalSet->isEnableSysDiskForSuperWks = atoi(szBuffer);
// 																					pDataBuffer += iSeparate;
// 																					pDataBuffer += strlen(szBuffer);
// 																					memset(szBuffer,0,255);
// 																					pPos = strstr(pDataBuffer,"&nbsp");
// 																					if (pPos)
// 																					{
// 																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																						pGlobalSet->isEnableDataDisk1ForSuperWks = atoi(szBuffer);
// 																						pDataBuffer += iSeparate;
// 																						pDataBuffer += strlen(szBuffer);
// 																						memset(szBuffer,0,255);
// 																						pPos = strstr(pDataBuffer,"&nbsp");
// 																						if (pPos)
// 																						{
// 																							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																							pGlobalSet->isEnableDataDisk2ForSuperWks = atoi(szBuffer);
// 																							pDataBuffer += iSeparate;
// 																							pDataBuffer += strlen(szBuffer);
// 																							memset(szBuffer,0,255);
// 																							pPos = strstr(pDataBuffer,"&nbsp");
// 																							if (pPos)
// 																							{
// 																								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																								pGlobalSet->isEnableDataDisk3ForSuperWks = atoi(szBuffer);
// 																								pDataBuffer += iSeparate;
// 																								pDataBuffer += strlen(szBuffer);
// 																								memset(szBuffer,0,255);
// 																								pPos = strstr(pDataBuffer,"&nbsp");
// 																								if (pPos)
// 																								{
// 																									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																									pGlobalSet->isDhcpQuickResponse = atoi(szBuffer);
// 																									pDataBuffer += iSeparate;
// 																									pDataBuffer += strlen(szBuffer);
// 																									memset(szBuffer,0,255);
// 																									pPos = strstr(pDataBuffer,"&nbsp");
// 																									if (pPos)
// 																									{
// 																										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																										pGlobalSet->isAutoSyncUpdateForSuperWks = atoi(szBuffer);
// 																										pDataBuffer += iSeparate;
// 																										pDataBuffer += strlen(szBuffer);
// 																										memset(szBuffer,0,255);
// 																										pPos = strstr(pDataBuffer,"&nbsp");
// 																										if (pPos)
// 																										{
// 																											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																											strcpy(pGlobalSet->runExternal,szBuffer);
// 																											pDataBuffer += iSeparate;
// 																											pDataBuffer += strlen(szBuffer);
// 																											memset(szBuffer,0,255);
// 																											pPos = strstr(pDataBuffer,"&nbsp");
// 																											if (pPos)
// 																											{
// 																												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																												pGlobalSet->isWaitCompleted = atoi(szBuffer);
// 																												pDataBuffer += iSeparate;
// 																												pDataBuffer += strlen(szBuffer);
// 																												memset(szBuffer,0,255);
// 																												pPos = strstr(pDataBuffer,"&nbsp");
// 																												if (pPos)
// 																												{
// 																													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																													strcpy(pGlobalSet->LanguagePack,szBuffer);
// 																													pDataBuffer += iSeparate;
// 																													pDataBuffer += strlen(szBuffer);
// 																													memset(szBuffer,0,255);
// 																													pPos = strstr(pDataBuffer,"&nbsp");
// 																													if (pPos)
// 																													{
// 																														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																														pGlobalSet->m_MemType = atol(szBuffer);
// 																														pDataBuffer += iSeparate;
// 																														pDataBuffer += strlen(szBuffer);
// 																														memset(szBuffer,0,255);
// 																														pPos = strstr(pDataBuffer,"&nbsp");
// 																														if (pPos)
// 																														{
// 																															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																															strcpy(pGlobalSet->m_WksWorkDir,szBuffer);
// 																															pDataBuffer += iSeparate;
// 																															pDataBuffer += strlen(szBuffer);
// 																															memset(szBuffer,0,255);
// 																															pPos = strstr(pDataBuffer,"&nbsp");
// 																															if (pPos)
// 																															{
// 																																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																strcpy(pGlobalSet->m_SsdPartition,szBuffer);
// 																																pDataBuffer += iSeparate;
// 																																pDataBuffer += strlen(szBuffer);
// 																																memset(szBuffer,0,255);
// 																																pPos = strstr(pDataBuffer,"&nbsp");
// 																																if (pPos)
// 																																{
// 																																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																	pGlobalSet->bRestartRestore = atoi(szBuffer);
// 																																	pDataBuffer += iSeparate;
// 																																	pDataBuffer += strlen(szBuffer);
// 																																	memset(szBuffer,0,255);
// 																																	pPos = strstr(pDataBuffer,"&nbsp");
// 																																	if (pPos)
// 																																	{
// 																																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																		pGlobalSet->m_LastUpdateTime = atoi(szBuffer);
// 																																		pDataBuffer += iSeparate;
// 																																		pDataBuffer += strlen(szBuffer);
// 																																		memset(szBuffer,0,255);
// 																																		pPos = strstr(pDataBuffer,"&nbsp");
// 																																		if (pPos)
// 																																		{
// 																																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																			pGlobalSet->m_Loglevel = atoi(szBuffer);
// 																																			pDataBuffer += iSeparate;
// 																																			pDataBuffer += strlen(szBuffer);
// 																																			memset(szBuffer,0,255);
// 																																			return 1;
// 																																		}
// 																																	}
// 																																}
// 																															}
// 																														}
// 																													}
// 																												}
// 																											}
// 																										}
// 																									}
// 																								}
// 																							}
// 																						}
// 																					}
// 																				}
// 																			}
// 																		}
// 																	}
// 																}
// 															}
// 														}
// 													}
// 												}
// 											}
// 										}
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// int		CMzd::Remote_GetPhysicsDiskList(CStringArray&	PhysicsDiskList, ServerDiskListIp*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	CString	StrIpAddress(pServerIp->ServerIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	
// 	if (pMzd->ConnectServer())
// 	{
// 		byte*	pRecvBuffer = NULL;
// 		byte*	pSendBuffer = new byte[dwMemory];
// 		byte*	pTemp = NULL;
// 		int			iSocketRet;
// 		DWORD	dwDataSizeof = 0;
// 		DWORD	dwCumulative = 0;
// 
// 		memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = dwMemory;
// 		Mzd_Quest_Head.uCommand = MZD_GET_PHYSICAL_DISK_MSG;
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 		pTemp = pSendBuffer;
// 		memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 		memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 		iSocketRet = pMzd->Send(pSendBuffer,dwMemory);
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete	[]pSendBuffer;
// 			goto End;
// 		}
// 		delete	[]pSendBuffer;
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			goto End;
// 		}
// 
// 		dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 		dwCumulative = 0;
// 		pRecvBuffer = new	byte[dwDataSizeof];
// 		pTemp = pRecvBuffer;
// 		while (dwDataSizeof != dwCumulative)
// 		{
// 			iSocketRet = pMzd->Receive(pTemp,sizeof(physicalDisk));
// 			if (iSocketRet == SOCKET_ERROR)
// 			{
// 				delete []pRecvBuffer;
// 				goto End;
// 			}
// 			pTemp += iSocketRet;
// 			dwCumulative += iSocketRet;
// 		}
// 		physicalDisk*	pPhysicalDisk = (physicalDisk*)pRecvBuffer;
// 		for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 		{
// 			TCHAR	wzsBuffer[32] = { 0 };
// 			CString		StrData;
// 			CString		StrBuffer(pPhysicalDisk->diskname);
// 			AddChar(StrBuffer.GetBuffer(),wzsBuffer,32);
// 			CString	StrRetData;
// 			StrRetData.Format(_T("'%s',"),wzsBuffer);
// 			PhysicsDiskList.Add(StrRetData);
// 			pPhysicalDisk++;
// 		}
// 		delete []pRecvBuffer;
// 	}
// End:
// 	pMzd->Close();
// 	delete	pMzd;
// 	return PhysicsDiskList.GetCount();
// }
// 
// int		CMzd::GetPhysicsDiskList(CStringArray&	PhysicsDiskList, physicalDiskRequest*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(physicalDiskRequest);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	byte*	pRecvBuffer = NULL;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTemp = NULL;
// 	int			iSocketRet;
// 	DWORD	dwDataSizeof = 0;
// 	DWORD	dwCumulative = 0;
// 
// 	memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_PHYSICAL_DISK_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	pTemp = pSendBuffer;
// 	memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTemp,pServerIp,sizeof(physicalDiskRequest));
// 
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		delete	[]pSendBuffer;
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	dwCumulative = 0;
// 	pRecvBuffer = new	byte[dwDataSizeof];
// 	pTemp = pRecvBuffer;
// 	while (dwDataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(physicalDisk));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete []pRecvBuffer;
// 			return -1;
// 		}
// 		pTemp += iSocketRet;
// 		dwCumulative += iSocketRet;
// 	}
// 	physicalDisk*	pPhysicalDisk = (physicalDisk*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzsBuffer[32] = { 0 };
// 		CString		StrData;
// 		CString		StrBuffer(pPhysicalDisk->diskname);
// 		AddChar(StrBuffer.GetBuffer(),wzsBuffer,32);
// 		CString	StrRetData;
// 		StrRetData.Format(_T("'%s',"),wzsBuffer);
// 		PhysicsDiskList.Add(StrRetData);
// 		pPhysicalDisk++;
// 	}
// 	delete []pRecvBuffer;
// 	return PhysicsDiskList.GetCount();
// }
// 
// int		CMzd::Remote_GetPartitionDiskList(CStringArray& PartitionDiskList, ServerDiskListIp*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	CString	StrIpAddress(pServerIp->ServerIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	if (pMzd->ConnectServer())
// 	{
// 		byte*	pRecvBuffer = NULL;
// 		byte*	pSendBuffer = new byte[dwMemory];
// 		byte*	pTemp = NULL;
// 		int			iSocketRet;
// 		DWORD	dwDataSizeof = 0;
// 		DWORD	dwCumulative = 0;
// 
// 		memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = dwMemory;
// 		Mzd_Quest_Head.uCommand = MZD_GET_DISK_PARTITION_MSG;
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 		pTemp = pSendBuffer;
// 		memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 		memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 		iSocketRet = pMzd->Send(pSendBuffer,dwMemory);
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete	[]pSendBuffer;
// 			goto End;
// 		}
// 		delete	[]pSendBuffer;
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			goto End;
// 		}
// 
// 		dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 		dwCumulative = 0;
// 		pRecvBuffer = new	byte[dwDataSizeof];
// 		pTemp = pRecvBuffer;
// 		while (dwDataSizeof != dwCumulative)
// 		{
// 			iSocketRet = pMzd->Receive(pTemp,sizeof(physicalDisk));
// 			if (iSocketRet == SOCKET_ERROR)
// 			{
// 				delete []pRecvBuffer;
// 				goto	End;
// 			}
// 			pTemp += iSocketRet;
// 			dwCumulative += iSocketRet;
// 		}
// 		partition*	pPhysicalDisk = (partition*)pRecvBuffer;
// 		for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 		{
// 			TCHAR	wzsBuffer[32] = { 0 };
// 			CString		StrData;
// 			CString		StrBuffer(pPhysicalDisk->partitionname);
// 			AddChar(StrBuffer.GetBuffer(),wzsBuffer,32);
// 			CString	StrRetData;
// 			StrRetData.Format(_T("'%s',"),wzsBuffer);
// 			PartitionDiskList.Add(StrRetData);
// 			pPhysicalDisk++;
// 		}
// 		delete []pRecvBuffer;
// 	}
// End:
// 	pMzd->Close();
// 	delete	pMzd;
// 	return PartitionDiskList.GetCount();
// }
// 
// int		CMzd::GetPartitionDiskList(CStringArray& PartitionDiskList, partitionRequest*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(partitionRequest);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	byte*	pRecvBuffer = NULL;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTemp = NULL;
// 	int			iSocketRet;
// 	DWORD	dwDataSizeof = 0;
// 	DWORD	dwCumulative = 0;
// 
// 	memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_DISK_PARTITION_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	pTemp = pSendBuffer;
// 	memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTemp,pServerIp,sizeof(partitionRequest));
// 
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		delete	[]pSendBuffer;
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	dwCumulative = 0;
// 	pRecvBuffer = new	byte[dwDataSizeof];
// 	pTemp = pRecvBuffer;
// 	while (dwDataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(physicalDisk));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete []pRecvBuffer;
// 			return -1;
// 		}
// 		pTemp += iSocketRet;
// 		dwCumulative += iSocketRet;
// 	}
// 	partition*	pPhysicalDisk = (partition*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzsBuffer[32] = { 0 };
// 		CString		StrData;
// 		CString		StrBuffer(pPhysicalDisk->partitionname);
// 		AddChar(StrBuffer.GetBuffer(),wzsBuffer,32);
// 		CString	StrRetData;
// 		StrRetData.Format(_T("'%s',"),wzsBuffer);
// 		PartitionDiskList.Add(StrRetData);
// 		pPhysicalDisk++;
// 	}
// 	delete []pRecvBuffer;
// 	return PartitionDiskList.GetCount();
// }
// 
// int		CMzd::Remote_GetImgDiskList(CStringArray& ImgDiskList, ServerDiskListIp*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	CString	StrIpAddress(pServerIp->ServerIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	if (pMzd->ConnectServer())
// 	{
// 		byte*	pRecvBuffer = NULL;
// 		byte*	pSendBuffer = new byte[dwMemory];
// 		byte*	pTemp = NULL;
// 		int			iSocketRet;
// 		DWORD	dwDataSizeof = 0;
// 		DWORD	dwCumulative = 0;
// 
// 		memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = dwMemory;
// 		Mzd_Quest_Head.uCommand = MZD_GET_IMG_LIST_MSG;
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 		pTemp = pSendBuffer;
// 		memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 		memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 		iSocketRet = pMzd->Send(pSendBuffer,dwMemory);
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete	[]pSendBuffer;
// 			goto	End;
// 		}
// 		delete	[]pSendBuffer;
// 		Sleep(100);
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			goto End;
// 		}
// 
// 		dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 		dwCumulative = 0;
// 		pRecvBuffer = new	byte[dwDataSizeof];
// 		pTemp = pRecvBuffer;
// 		while (dwDataSizeof != dwCumulative)
// 		{
// 			iSocketRet = pMzd->Receive(pTemp,sizeof(physicalDisk));
// 			if (iSocketRet == SOCKET_ERROR)
// 			{
// 				delete []pRecvBuffer;
// 				goto End;
// 			}
// 			pTemp += iSocketRet;
// 			dwCumulative += iSocketRet;
// 		}
// 		ImgResponse*	pPhysicalDisk = (ImgResponse*)pRecvBuffer;
// 		for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 		{
// 			TCHAR	wzsBuffer[260] = { 0 };
// 			CString		StrData;
// 			CString		StrBuffer(pPhysicalDisk->imgpath);
// 			AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 			CString	StrRetData;
// 			StrRetData.Format(_T("'%s',"),wzsBuffer);
// 			ImgDiskList.Add(StrRetData);
// 			pPhysicalDisk++;
// 		}
// 		delete []pRecvBuffer;
// 	}
// 	else
// 	{
// 		delete	pMzd;
// 		return -1;
// 	}
// End:
// 	pMzd->Close();
// 	delete	pMzd;
// 	return ImgDiskList.GetCount();
// }
// 
// int		CMzd::GetImgDiskList(CStringArray& ImgDiskList, Img*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(Img);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	byte*	pRecvBuffer = NULL;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTemp = NULL;
// 	int			iSocketRet;
// 	DWORD	dwDataSizeof = 0;
// 	DWORD	dwCumulative = 0;
// 
// 	memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_IMG_LIST_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	pTemp = pSendBuffer;
// 	memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTemp,pServerIp,sizeof(Img));
// 
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		delete	[]pSendBuffer;
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	Sleep(100);
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	dwCumulative = 0;
// 	pRecvBuffer = new	byte[dwDataSizeof];
// 	pTemp = pRecvBuffer;
// 	while (dwDataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(ImgResponse));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete []pRecvBuffer;
// 			return -1;
// 		}
// 		pTemp += iSocketRet;
// 		dwCumulative += iSocketRet;
// 	}
// 	ImgResponse*	pImgList = (ImgResponse*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzsBuffer[260] = { 0 };
// 		CString		StrData;
// 		CString		StrBuffer(pImgList->imgpath);
// 		AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 		CString	StrRetData;
// 		StrRetData.Format(_T("['%s','%d'],"),wzsBuffer,pImgList->imgsectornums);
// 		ImgDiskList.Add(StrRetData);
// 		pImgList++;
// 	}
// 	delete []pRecvBuffer;
// 	return ImgDiskList.GetCount();
// }
// 
// int		CMzd::Remote_GetFixDiskList(CStringArray& FixDiskList, ServerDiskListIp*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	CString	StrIpAddress(pServerIp->ServerIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	if (pMzd->ConnectServer())
// 	{
// 		byte*	pRecvBuffer = NULL;
// 		byte*	pSendBuffer = new byte[dwMemory];
// 		byte*	pTemp = NULL;
// 		int			iSocketRet;
// 		DWORD	dwDataSizeof = 0;
// 		DWORD	dwCumulative = 0;
// 
// 		memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = dwMemory;
// 		Mzd_Quest_Head.uCommand = MZD_GET_FIX_LIST_MSG;
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 		pTemp = pSendBuffer;
// 		memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 		memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 		iSocketRet = pMzd->Send(pSendBuffer,dwMemory);
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete	[]pSendBuffer;
// 			goto End;
// 		}
// 		delete	[]pSendBuffer;
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			goto End;
// 		}
// 
// 		dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 		dwCumulative = 0;
// 		pRecvBuffer = new	byte[dwDataSizeof];
// 		pTemp = pRecvBuffer;
// 		while (dwDataSizeof != dwCumulative)
// 		{
// 			iSocketRet = pMzd->Receive(pTemp,sizeof(physicalDisk));
// 			if (iSocketRet == SOCKET_ERROR)
// 			{
// 				delete []pRecvBuffer;
// 				goto End;
// 			}
// 			pTemp += iSocketRet;
// 			dwCumulative += iSocketRet;
// 		}
// 		Fix*	pPhysicalDisk = (Fix*)pRecvBuffer;
// 		for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 		{
// 			TCHAR	wzsBuffer[260] = { 0 };
// 			CString		StrData;
// 			CString		StrBuffer(pPhysicalDisk->fixpath);
// 			AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 			CString	StrRetData;
// 			StrRetData.Format(_T("'%s',"),wzsBuffer);
// 			FixDiskList.Add(StrRetData);
// 			pPhysicalDisk++;
// 		}
// 		delete []pRecvBuffer;
// 	}
// End:
// 	pMzd->Close();
// 	delete pMzd;
// 	return FixDiskList.GetCount();
// }
// 
// int		CMzd::GetFixDiskList(CStringArray& FixDiskList, FixParameter*	pParameter)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(FixParameter);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	byte*	pRecvBuffer = NULL;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTemp = NULL;
// 	int			iSocketRet;
// 	DWORD	dwDataSizeof = 0;
// 	DWORD	dwCumulative = 0;
// 
// 	memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_FIX_LIST_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	pTemp = pSendBuffer;
// 	memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTemp,pParameter,sizeof(FixParameter));
// 
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		delete	[]pSendBuffer;
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	dwCumulative = 0;
// 	pRecvBuffer = new	byte[dwDataSizeof];
// 	pTemp = pRecvBuffer;
// 	while (dwDataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(Fix));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete []pRecvBuffer;
// 			return -1;
// 		}
// 		pTemp += iSocketRet;
// 		dwCumulative += iSocketRet;
// 	}
// 	Fix*	pFixList = (Fix*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzsBuffer[260] = { 0 };
// 		CString		StrData;
// 		CString		StrBuffer(pFixList->fixpath);
// 		AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 		CString	StrRetData;
// 		StrRetData.Format(_T("'%s',"),wzsBuffer);
// 		FixDiskList.Add(StrRetData);
// 		pFixList++;
// 	}
// 	delete []pRecvBuffer;
// 	return FixDiskList.GetCount();
// }
// 
// int		CMzd::Remote_GetUploadFixDiskList(CStringArray& UploadFixDiskList, ServerDiskListIp*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	CString	StrIpAddress(pServerIp->ServerIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	if (pMzd->ConnectServer())
// 	{
// 		byte*	pRecvBuffer = NULL;
// 		byte*	pSendBuffer = new byte[dwMemory];
// 		byte*	pTemp = NULL;
// 		int			iSocketRet;
// 		DWORD	dwDataSizeof = 0;
// 		DWORD	dwCumulative = 0;
// 
// 		memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = dwMemory;
// 		Mzd_Quest_Head.uCommand = MZD_GET_UPLOAD_FIX_LISG_MSG;
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 		pTemp = pSendBuffer;
// 		memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 		memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 		iSocketRet = pMzd->Send(pSendBuffer,dwMemory);
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete	[]pSendBuffer;
// 			goto End;
// 		}
// 		delete	[]pSendBuffer;
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			goto End;
// 		}
// 
// 		dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 		dwCumulative = 0;
// 		pRecvBuffer = new	byte[dwDataSizeof];
// 		pTemp = pRecvBuffer;
// 		while (dwDataSizeof != dwCumulative)
// 		{
// 			iSocketRet = pMzd->Receive(pTemp,sizeof(physicalDisk));
// 			if (iSocketRet == SOCKET_ERROR)
// 			{
// 				delete []pRecvBuffer;
// 				goto End;
// 			}
// 			pTemp += iSocketRet;
// 			dwCumulative += iSocketRet;
// 		}
// 		UploadFix*	pPhysicalDisk = (UploadFix*)pRecvBuffer;
// 		for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 		{
// 			TCHAR	wzsBuffer[260] = { 0 };
// 			CString		StrData;
// 			CString		StrBuffer(pPhysicalDisk->fixpath);
// 			AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 			CString	StrRetData;
// 			StrRetData.Format(_T("'%s',"),wzsBuffer);
// 			UploadFixDiskList.Add(StrRetData);
// 			pPhysicalDisk++;
// 		}
// 		delete []pRecvBuffer;
// 	}
// End:
// 	pMzd->Close();
// 	delete pMzd;
// 	return UploadFixDiskList.GetCount();
// }
// 
// int		CMzd::GetUploadFixDiskList(CStringArray& UploadFixDiskList, ServerDiskListIp*	pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	byte*	pRecvBuffer = NULL;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTemp = NULL;
// 	int			iSocketRet;
// 	DWORD	dwDataSizeof = 0;
// 	DWORD	dwCumulative = 0;
// 
// 	memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_UPLOAD_FIX_LISG_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	pTemp = pSendBuffer;
// 	memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		delete	[]pSendBuffer;
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	dwCumulative = 0;
// 	pRecvBuffer = new	byte[dwDataSizeof];
// 	pTemp = pRecvBuffer;
// 	while (dwDataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(UploadFix));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete []pRecvBuffer;
// 			return -1;
// 		}
// 		pTemp += iSocketRet;
// 		dwCumulative += iSocketRet;
// 	}
// 	UploadFix*	pPhysicalDisk = (UploadFix*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzsBuffer[260] = { 0 };
// 		CString		StrData;
// 		CString		StrBuffer(pPhysicalDisk->fixpath);
// 		AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 		CString	StrRetData;
// 		StrRetData.Format(_T("'%s',"),wzsBuffer);
// 		UploadFixDiskList.Add(StrRetData);
// 		pPhysicalDisk++;
// 	}
// 	delete []pRecvBuffer;
// 	return UploadFixDiskList.GetCount();
// }
// 
// int		CMzd::Remote_GetUdoResponseList(CStringArray& UdoResponseList,ServerDiskListIp* pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	CString	StrIpAddress(pServerIp->ServerIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	if (pMzd->ConnectServer())
// 	{
// 		byte*	pRecvBuffer = NULL;
// 		byte*	pSendBuffer = new byte[dwMemory];
// 		byte*	pTemp = NULL;
// 		int			iSocketRet;
// 		DWORD	dwDataSizeof = 0;
// 		DWORD	dwCumulative = 0;
// 
// 		memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = dwMemory;
// 		Mzd_Quest_Head.uCommand = MZD_GET_UDO_LISG_MSG;
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 		pTemp = pSendBuffer;
// 		memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 		memcpy(pTemp,pServerIp,sizeof(ServerDiskListIp));
// 
// 		iSocketRet = pMzd->Send(pSendBuffer,dwMemory);
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete	[]pSendBuffer;
// 			goto End;
// 		}
// 		delete	[]pSendBuffer;
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			goto End;
// 		}
// 
// 		dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 		dwCumulative = 0;
// 		pRecvBuffer = new	byte[dwDataSizeof];
// 		pTemp = pRecvBuffer;
// 		while (dwDataSizeof != dwCumulative)
// 		{
// 			iSocketRet = pMzd->Receive(pTemp,sizeof(Udo));
// 			if (iSocketRet == SOCKET_ERROR)
// 			{
// 				delete []pRecvBuffer;
// 				goto End;
// 			}
// 			pTemp += iSocketRet;
// 			dwCumulative += iSocketRet;
// 		}
// 		Udo*	pUdoResponse = (Udo*)pRecvBuffer;
// 		for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 		{
// 			TCHAR	wzsBuffer[260] = { 0 };
// 			CString		StrData;
// 			CString		StrBuffer(pUdoResponse->fixpath);
// 			AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 			CString	StrRetData;
// 			StrRetData.Format(_T("'%s',"),wzsBuffer);
// 			UdoResponseList.Add(StrRetData);
// 			pUdoResponse++;
// 		}
// 		delete []pRecvBuffer;
// 	}
// End:
// 	pMzd->Close();
// 	delete pMzd;
// 	return UdoResponseList.GetCount();
// }
// 
// int		CMzd::GetUdoResponseList(CStringArray& UdoResponseList,UdoParameter*	pParameter)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(UdoParameter);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head;
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 
// 	byte*	pRecvBuffer = NULL;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTemp = NULL;
// 	int			iSocketRet;
// 	DWORD	dwDataSizeof = 0;
// 	DWORD	dwCumulative = 0;
// 
// 	memset(&Mzd_Quest_Head,0,sizeof(SOCKET_HEAD_REQUEST));
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_UDO_LISG_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	pTemp = pSendBuffer;
// 	memcpy(pTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTemp,pParameter,sizeof(UdoParameter));
// 
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		delete	[]pSendBuffer;
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	dwDataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	dwCumulative = 0;
// 	pRecvBuffer = new	byte[dwDataSizeof];
// 	pTemp = pRecvBuffer;
// 	while (dwDataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(Udo));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			delete []pRecvBuffer;
// 			return -1;
// 		}
// 		pTemp += iSocketRet;
// 		dwCumulative += iSocketRet;
// 	}
// 	Udo*	pUdoResponse = (Udo*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzsBuffer[260] = { 0 };
// 		CString		StrData;
// 		CString		StrBuffer(pUdoResponse->fixpath);
// 		AddChar(StrBuffer.GetBuffer(),wzsBuffer,260);
// 		CString	StrRetData;
// 		StrRetData.Format(_T("'%s',"),wzsBuffer);
// 		UdoResponseList.Add(StrRetData);
// 		pUdoResponse++;
// 	}
// 	delete []pRecvBuffer;
// 	return UdoResponseList.GetCount();
// }
// 
// int		CMzd::LoadDiskSet(char* pDataBuffer,DiskSetEx* pDiskSet)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[64] = { 0 };
// 	pPos = strstr(pDataBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 		pDiskSet->isAutoUpload = atoi(szBuffer);
// 		pDataBuffer += strlen(szBuffer);
// 		pDataBuffer += iSeparate;
// 		memset(szBuffer,0,64);
// 		pPos = strstr(pDataBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 			pDiskSet->isAllowUpload = atoi(szBuffer);
// 			pDataBuffer += strlen(szBuffer);
// 			pDataBuffer += iSeparate;
// 			memset(szBuffer,0,64);
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				pDiskSet->isAllowRevert = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					pDiskSet->isAllowClear = atoi(szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						pDiskSet->isAutoRevert = atoi(szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							pDiskSet->isAutoClear = atoi(szBuffer);
// 							pDataBuffer += strlen(szBuffer);
// 							pDataBuffer += iSeparate;
// 							memset(szBuffer,0,64);
// 							pPos = strstr(pDataBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 								pDiskSet->readCacheSize = atol(szBuffer);
// 								pDataBuffer += strlen(szBuffer);
// 								pDataBuffer += iSeparate;
// 								memset(szBuffer,0,64);
// 								pPos = strstr(pDataBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 									pDiskSet->writeCacheSize = atol(szBuffer);
// 									pDataBuffer += strlen(szBuffer);
// 									pDataBuffer += iSeparate;
// 									memset(szBuffer,0,64);
// 									pPos = strstr(pDataBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 										pDiskSet->abreastSum = atoi(szBuffer);
// 										pDataBuffer += strlen(szBuffer);
// 										pDataBuffer += iSeparate;
// 										memset(szBuffer,0,64);
// 										pPos = strstr(pDataBuffer,"&nbsp");
// 										if (pPos)
// 										{
// 											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 											pDiskSet->retryTimeOut = atoi(szBuffer);
// 											pDataBuffer += strlen(szBuffer);
// 											pDataBuffer += iSeparate;
// 											memset(szBuffer,0,64);
// 											pPos = strstr(pDataBuffer,"&nbsp");
// 											if (pPos)
// 											{
// 												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 												pDiskSet->dosReadSize = atoi(szBuffer);
// 												pDataBuffer += strlen(szBuffer);
// 												pDataBuffer += iSeparate;
// 												memset(szBuffer,0,64);
// 												pPos = strstr(pDataBuffer,"&nbsp");
// 												if (pPos)
// 												{
// 													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 													pDiskSet->dosWriteSize = atoi(szBuffer);
// 													pDataBuffer += strlen(szBuffer);
// 													pDataBuffer += iSeparate;
// 													memset(szBuffer,0,64);
// 													pPos = strstr(pDataBuffer,"&nbsp");
// 													if (pPos)
// 													{
// 														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 														pDiskSet->winReadSize = atoi(szBuffer);
// 														pDataBuffer += strlen(szBuffer);
// 														pDataBuffer += iSeparate;
// 														memset(szBuffer,0,64);
// 														pPos = strstr(pDataBuffer,"&nbsp");
// 														if (pPos)
// 														{
// 															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 															pDiskSet->winWriteSize = atoi(szBuffer);
// 															pDataBuffer += strlen(szBuffer);
// 															pDataBuffer += iSeparate;
// 															memset(szBuffer,0,64);
// 															pPos = strstr(pDataBuffer,"&nbsp");
// 															if (pPos)
// 															{
// 																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																pDiskSet->localCacheSize = atoi(szBuffer);
// 																pDataBuffer += strlen(szBuffer);
// 																pDataBuffer += iSeparate;
// 																memset(szBuffer,0,64);
// 																pPos = strstr(pDataBuffer,"&nbsp");
// 																if (pPos)
// 																{
// 																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																	pDiskSet->isDelayLoad = atoi(szBuffer);
// 																	pDataBuffer += strlen(szBuffer);
// 																	pDataBuffer += iSeparate;
// 																	memset(szBuffer,0,64);
// 																	pPos = strstr(pDataBuffer,"&nbsp");
// 																	if (pPos)
// 																	{
// 																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																		pDiskSet->isIScsiBoot = atoi(szBuffer);
// 																		pDataBuffer += strlen(szBuffer);
// 																		pDataBuffer += iSeparate;
// 																		memset(szBuffer,0,64);
// 																		pPos = strstr(pDataBuffer,"&nbsp");
// 																		if (pPos)
// 																		{
// 																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																			strcpy(pDiskSet->clientWriteDir,szBuffer);
// 																			pDataBuffer += strlen(szBuffer);
// 																			pDataBuffer += iSeparate;
// 																			memset(szBuffer,0,64);
// 																			pPos = strstr(pDataBuffer,"&nbsp");
// 																			if (pPos)
// 																			{
// 																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																				pDiskSet->diskQuota = atol(szBuffer);
// 																				pDataBuffer += strlen(szBuffer);
// 																				pDataBuffer += iSeparate;
// 																				memset(szBuffer,0,64);
// 																				pPos = strstr(pDataBuffer,"&nbsp");
// 																				if (pPos)
// 																				{
// 																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																					pDiskSet->dirIp = inet_addr(szBuffer);
// 																					pDataBuffer += strlen(szBuffer);
// 																					pDataBuffer += iSeparate;
// 																					memset(szBuffer,0,64);
// 																					pPos = strstr(pDataBuffer,"&nbsp");
// 																					if (pPos)
// 																					{
// 																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																						pDiskSet->mirrIp = inet_addr(szBuffer);
// 																						pDataBuffer += strlen(szBuffer);
// 																						pDataBuffer += iSeparate;
// 																						memset(szBuffer,0,64);
// 																						pPos = strstr(pDataBuffer,"&nbsp");
// 																						if (pPos)
// 																						{
// 																							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																							pDiskSet->hotBakIP = inet_addr(szBuffer);
// 																							pDataBuffer += strlen(szBuffer);
// 																							pDataBuffer += iSeparate;
// 																							memset(szBuffer,0,64);
// 																							pPos = strstr(pDataBuffer,"&nbsp");
// 																							if (pPos)
// 																							{
// 																								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																								pDiskSet->ssdCacheSize = atol(szBuffer);
// 																								pDataBuffer += strlen(szBuffer);
// 																								pDataBuffer += iSeparate;
// 																								memset(szBuffer,0,64);
// 																								pPos = strstr(pDataBuffer,"&nbsp");
// 																								if (pPos)
// 																								{
// 																									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																									strcpy(pDiskSet->ssdVolum,szBuffer);
// 																									pDataBuffer += strlen(szBuffer);
// 																									pDataBuffer += iSeparate;
// 																									memset(szBuffer,0,64);
// 																									pPos = strstr(pDataBuffer,"&nbsp");
// 																									if (pPos)
// 																									{
// 																										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																										char	FileBuffer[128] = { 0 };
// 																										CChineseCode::Utf8ToAscii(szBuffer,FileBuffer);
// 																										strcpy(pDiskSet->destinationFile,FileBuffer);
// 																										pDataBuffer += strlen(szBuffer);
// 																										pDataBuffer += iSeparate;
// 																										memset(szBuffer,0,64);
// 																										pPos = strstr(pDataBuffer,"&nbsp");
// 																										if (pPos)
// 																										{
// 																											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																											strcpy(pDiskSet->arWorkDir[0],szBuffer);
// 																											pDataBuffer += strlen(szBuffer);
// 																											pDataBuffer += iSeparate;
// 																											memset(szBuffer,0,64);
// 																											pPos = strstr(pDataBuffer,"&nbsp");
// 																											if (pPos)
// 																											{
// 																												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																												strcpy(pDiskSet->arWorkDir[1],szBuffer);
// 																												pDataBuffer += strlen(szBuffer);
// 																												pDataBuffer += iSeparate;
// 																												memset(szBuffer,0,64);
// 																												pPos = strstr(pDataBuffer,"&nbsp");
// 																												if (pPos)
// 																												{
// 																													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																													strcpy(pDiskSet->arWorkDir[2],szBuffer);
// 																													pDataBuffer += strlen(szBuffer);
// 																													pDataBuffer += iSeparate;
// 																													memset(szBuffer,0,64);
// 																													pPos = strstr(pDataBuffer,"&nbsp");
// 																													if (pPos)
// 																													{
// 																														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																														strcpy(pDiskSet->arWorkDir[3],szBuffer);
// 																														pDataBuffer += strlen(szBuffer);
// 																														pDataBuffer += iSeparate;
// 																														memset(szBuffer,0,64);
// 																														pPos = strstr(pDataBuffer,"&nbsp");
// 																														if (pPos)
// 																														{
// 																															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																															CChineseCode::Utf8ToAscii(szBuffer,pDiskSet->diskName);
// 																															//strcpy(pDiskSet->diskName,szBuffer);
// 																															pDataBuffer += strlen(szBuffer);
// 																															pDataBuffer += iSeparate;
// 																															memset(szBuffer,0,64);
// 																															pPos = strstr(pDataBuffer,"&nbsp");
// 																															if (pPos)
// 																															{
// 																																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																pDiskSet->readCacheType = atol(szBuffer);
// 																																pDataBuffer += strlen(szBuffer);
// 																																pDataBuffer += iSeparate;
// 																																memset(szBuffer,0,64);
// 																																pPos = strstr(pDataBuffer,"&nbsp");
// 																																if (pPos)
// 																																{
// 																																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																	pDiskSet->writeCacheType = atol(szBuffer);
// 																																	pDataBuffer += strlen(szBuffer);
// 																																	pDataBuffer += iSeparate;
// 																																	memset(szBuffer,0,64);
// 																																	pPos = strstr(pDataBuffer,"&nbsp");
// 																																	if (pPos)
// 																																	{
// 																																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																		CChineseCode::Utf8ToAscii(szBuffer,pDiskSet->diskDisplayName);
// 																																		pDataBuffer += strlen(szBuffer);
// 																																		pDataBuffer += iSeparate;
// 																																		memset(szBuffer,0,64);
// 																																		pPos = strstr(pDataBuffer,"&nbsp");
// 																																		if (pPos)
// 																																		{
// 																																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																			pDiskSet->diskType = atoi(szBuffer);
// 																																			pDataBuffer += strlen(szBuffer);
// 																																			pDataBuffer += iSeparate;
// 																																			memset(szBuffer,0,64);
// 																																			pPos = strstr(pDataBuffer,"&nbsp");
// 																																			if (pPos)
// 																																			{
// 																																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																				pDiskSet->disksize = atoi(szBuffer);
// 																																				pDataBuffer += strlen(szBuffer);
// 																																				pDataBuffer += iSeparate;
// 																																				memset(szBuffer,0,64);
// 																																				pPos = strstr(pDataBuffer,"&nbsp");
// 																																				if (pPos)
// 																																				{
// 																																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																					CChineseCode::Utf8ToAscii(szBuffer,pDiskSet->serverName);
// 																																					pDataBuffer += strlen(szBuffer);
// 																																					pDataBuffer += iSeparate;
// 																																					memset(szBuffer,0,64);
// 																																					pPos = strstr(pDataBuffer,"&nbsp");
// 																																					if (pPos)
// 																																					{
// 																																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																						pDiskSet->serverIp[0] = inet_addr(szBuffer);
// 																																						pDataBuffer += strlen(szBuffer);
// 																																						pDataBuffer += iSeparate;
// 																																						memset(szBuffer,0,64);
// 																																						pPos = strstr(pDataBuffer,"&nbsp");
// 																																						if (pPos)
// 																																						{
// 																																							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																							pDiskSet->serverIp[1] = inet_addr(szBuffer);
// 																																							pDataBuffer += strlen(szBuffer);
// 																																							pDataBuffer += iSeparate;
// 																																							memset(szBuffer,0,64);
// 																																							pPos = strstr(pDataBuffer,"&nbsp");
// 																																							if (pPos)
// 																																							{
// 																																								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																								pDiskSet->serverIp[2] = inet_addr(szBuffer);
// 																																								pDataBuffer += strlen(szBuffer);
// 																																								pDataBuffer += iSeparate;
// 																																								memset(szBuffer,0,64);
// 																																								pPos = strstr(pDataBuffer,"&nbsp");
// 																																								if (pPos)
// 																																								{
// 																																									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																									pDiskSet->serverIp[3] = inet_addr(szBuffer);
// 																																									pDataBuffer += strlen(szBuffer);
// 																																									pDataBuffer += iSeparate;
// 																																									memset(szBuffer,0,64);
// 																																									return 1;
// 																																								}
// 																																							}
// 																																						}
// 																																					}
// 																																				}
// 																																			}
// 																																		}
// 																																	}
// 																																}
// 																															}
// 																														}
// 																													}
// 																												}
// 																											}
// 																										}
// 																									}
// 																								}
// 																							}
// 																						}
// 																					}
// 																				}
// 																			}
// 																		}
// 																	}
// 																}
// 															}
// 														}
// 													}
// 												}
// 											}
// 										}
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// CString	CMzd::DiskSet_Operation(int nFlag,DiskSetEx* pDiskSet)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(DiskSetEx);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 	switch (nFlag)
// 	{
// 	case	0:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_ADD_DISK_MSG;
// 			break;
// 		}
// 	case	1:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_MODIFY_DISK_MSG;
// 			break;
// 		}
// 	case	2:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_DEL_DISK_MSG;
// 			break;
// 		}
// 	}
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pDiskSet,sizeof(DiskSetEx));
// 	CString		StrResult;
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// int		CMzd::GetAdaptMenuSet(CStringArray& AdaptMenuSetList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_MENU_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pRecvBuffer = new byte[DataSizeof];
// 	byte*	pbTemp = pRecvBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (DataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pbTemp,sizeof(AdaptMenuSet));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pbTemp += iSocketRet;
// 	}
// 	AdaptMenuSet*	pAdaptMenuSet = (AdaptMenuSet*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		CString	StrData;
// 		sockaddr_in stAddr;
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.wksSubMask;
// 		CString	StrwksSubMask(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.gateway;
// 		CString	Strgateway(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.dns1;
// 		CString	Strdns1(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.wksStartIp;
// 		CString	StrwksStartIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.dns2;
// 		CString	Strdns2(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->menuset.gateway;
// 		CString	StrMenuGatway(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->menuset.dns1;
// 		CString	StrMenudns1(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->menuset.dns2;
// 		CString	StrMenudns2(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->menuset.coverDirIp;
// 		CString	StrcoverDirIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->menuset.coverMirrIp;
// 		CString	StrcoverMirrIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->menuset.coverHotBakIP;
// 		CString	StrcoverHotBakIP(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.loginIP;
// 		CString	StrloginIP(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pAdaptMenuSet->adaptset.spareLoginIp;
// 		CString	StrspareLoginIp(inet_ntoa(stAddr.sin_addr));
// 
// 		CString	StrcomPre(pAdaptMenuSet->menuset.comPre);
// 		CString	StrcomAfx(pAdaptMenuSet->menuset.comAfx);
// 		CString	MenuName(pAdaptMenuSet->menuset.menuName);
// 		CString	StrscrRes(pAdaptMenuSet->menuset.scrRes);
// 		CString	StradapterSet(pAdaptMenuSet->menuset.adapterSet);
// 		CString	StrwksArea(pAdaptMenuSet->menuset.wksArea);
// 		CString	StrworkGroup(pAdaptMenuSet->menuset.workGroup);
// 		CString	StrgatewayMAC(pAdaptMenuSet->menuset.gatewayMAC);
// 		CString	StrdisplayName(pAdaptMenuSet->menuset.displayName);
// 		CString	StradapterName(pAdaptMenuSet->adaptset.adapterName);
// 
// 		wchar_t	wzDiskItemsBuffer[4][32] = { 0 };
// 		
// 		CString	StrarDiskItems0(pAdaptMenuSet->menuset.arDiskItems[0]);
// 		CString	StrarDiskItems1(pAdaptMenuSet->menuset.arDiskItems[1]);
// 		CString	StrarDiskItems2(pAdaptMenuSet->menuset.arDiskItems[2]);
// 		CString	StrarDiskItems3(pAdaptMenuSet->menuset.arDiskItems[3]);
// 
// 		AddChar(StrarDiskItems0.GetBuffer(),wzDiskItemsBuffer[0],32);
// 		AddChar(StrarDiskItems1.GetBuffer(),wzDiskItemsBuffer[1],32);
// 		AddChar(StrarDiskItems2.GetBuffer(),wzDiskItemsBuffer[2],32);
// 		AddChar(StrarDiskItems3.GetBuffer(),wzDiskItemsBuffer[3],32);
// 
// 		StrData.Format(_T("['%d','%d','%d','%s','%s','%s','%d','%d','%d','%d','%s','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%s','%ld','%d','%d','%s','%s','%s','%s','%s','%s','%s','%d','%d','%s','%s','%s'],"),
// 			pAdaptMenuSet->menuset.waitTime,
// 			pAdaptMenuSet->menuset.isShowHostIP,
// 			pAdaptMenuSet->menuset.isVipLogon,
// 			StradapterSet,
// 			StrwksArea,
// 			StrMenuGatway,
// 			pAdaptMenuSet->menuset.numberLength,
// 			pAdaptMenuSet->menuset.bootOrd,
// 			pAdaptMenuSet->menuset.bootOrd1,
// 			pAdaptMenuSet->menuset.bootOrd2,
// 			StrMenudns1,
// 			StrMenudns2,
// 			wzDiskItemsBuffer[0],
// 			wzDiskItemsBuffer[1],
// 			wzDiskItemsBuffer[2],
// 			wzDiskItemsBuffer[3],
// 			StrcomPre,
// 			StrcomAfx,
// 			pAdaptMenuSet->menuset.startNumber,
// 			StrworkGroup,
// 			StrscrRes,
// 			StrgatewayMAC,
// 			StrcoverDirIp,
// 			StrcoverMirrIp,
// 			StrcoverHotBakIP,
// 			pAdaptMenuSet->menuset.m_WksMemory,
// 			pAdaptMenuSet->menuset.m_WksAutoClear,
// 			pAdaptMenuSet->menuset.m_UseHotBackup,
// 			StrdisplayName,
// 			MenuName,
// 			StradapterName,
// 			StrloginIP,
// 			StrspareLoginIp,
// 			StrwksStartIp,
// 			StrwksSubMask,
// 			pAdaptMenuSet->adaptset.subsectionIp,
// 			pAdaptMenuSet->adaptset.dhcpCount,
// 			Strgateway,
// 			Strdns1,
// 			Strdns2);
// 		AdaptMenuSetList.Add(StrData);
// 		pAdaptMenuSet++;
// 	}
// 	return AdaptMenuSetList.GetCount();
// }
// 
// CString	CMzd::SetGlobalInfo(GlobalSet *pGlobalSet)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(GlobalSet);
// 
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_SET_GLOBAL_SET_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pGlobalSet,sizeof(GlobalSet));
// 
// 	CString	StrResult;
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp操作成功！"));
// 	return StrResult;
// }
// 
// int		CMzd::LoadAdaptMenuSet(AdaptMenuSet* pAdaptMenuSet,char* pDataBuffer)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[128] = { 0 };
// 	pPos = strstr(pDataBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 		pAdaptMenuSet->menuset.waitTime = atol(szBuffer);
// 		pDataBuffer += strlen(szBuffer);
// 		pDataBuffer += iSeparate;
// 		memset(szBuffer,0,128);
// 		pPos = strstr(pDataBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 			pAdaptMenuSet->menuset.isShowHostIP = atoi(szBuffer);
// 			pDataBuffer += strlen(szBuffer);
// 			pDataBuffer += iSeparate;
// 			memset(szBuffer,0,128);
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				pAdaptMenuSet->menuset.isVipLogon = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,128);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(pAdaptMenuSet->menuset.adapterSet,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,128);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(pAdaptMenuSet->menuset.wksArea,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,128);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							pAdaptMenuSet->menuset.gateway = inet_addr(szBuffer);
// 							pDataBuffer += strlen(szBuffer);
// 							pDataBuffer += iSeparate;
// 							memset(szBuffer,0,128);
// 							pPos = strstr(pDataBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 								pAdaptMenuSet->menuset.numberLength = atoi(szBuffer);
// 								pDataBuffer += strlen(szBuffer);
// 								pDataBuffer += iSeparate;
// 								memset(szBuffer,0,128);
// 								pPos = strstr(pDataBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 									pAdaptMenuSet->menuset.bootOrd = atoi(szBuffer);
// 									pDataBuffer += strlen(szBuffer);
// 									pDataBuffer += iSeparate;
// 									memset(szBuffer,0,128);
// 									pPos = strstr(pDataBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 										pAdaptMenuSet->menuset.bootOrd1 = atoi(szBuffer);
// 										pDataBuffer += strlen(szBuffer);
// 										pDataBuffer += iSeparate;
// 										memset(szBuffer,0,128);
// 										pPos = strstr(pDataBuffer,"&nbsp");
// 										if (pPos)
// 										{
// 											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 											pAdaptMenuSet->menuset.bootOrd2 = atoi(szBuffer);
// 											pDataBuffer += strlen(szBuffer);
// 											pDataBuffer += iSeparate;
// 											memset(szBuffer,0,128);
// 											pPos = strstr(pDataBuffer,"&nbsp");
// 											if (pPos)
// 											{
// 												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 												pAdaptMenuSet->menuset.dns1 = inet_addr(szBuffer);
// 												pDataBuffer += strlen(szBuffer);
// 												pDataBuffer += iSeparate;
// 												memset(szBuffer,0,128);
// 												pPos = strstr(pDataBuffer,"&nbsp");
// 												if (pPos)
// 												{
// 													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 													pAdaptMenuSet->menuset.dns2 = inet_addr(szBuffer);
// 													pDataBuffer += strlen(szBuffer);
// 													pDataBuffer += iSeparate;
// 													memset(szBuffer,0,128);
// 													pPos = strstr(pDataBuffer,"&nbsp");
// 													if (pPos)
// 													{
// 														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 														//strcpy(pAdaptMenuSet->menuset.arDiskItems[0],szBuffer);
// 														CChineseCode::Utf8ToAscii(szBuffer,pAdaptMenuSet->menuset.arDiskItems[0]);
// 														pDataBuffer += strlen(szBuffer);
// 														pDataBuffer += iSeparate;
// 														memset(szBuffer,0,128);
// 														pPos = strstr(pDataBuffer,"&nbsp");
// 														if (pPos)
// 														{
// 															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 															//strcpy(pAdaptMenuSet->menuset.arDiskItems[1],szBuffer);
// 															CChineseCode::Utf8ToAscii(szBuffer,pAdaptMenuSet->menuset.arDiskItems[1]);
// 															pDataBuffer += strlen(szBuffer);
// 															pDataBuffer += iSeparate;
// 															memset(szBuffer,0,128);
// 															pPos = strstr(pDataBuffer,"&nbsp");
// 															if (pPos)
// 															{
// 																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																//strcpy(pAdaptMenuSet->menuset.arDiskItems[2],szBuffer);
// 																CChineseCode::Utf8ToAscii(szBuffer,pAdaptMenuSet->menuset.arDiskItems[2]);
// 																pDataBuffer += strlen(szBuffer);
// 																pDataBuffer += iSeparate;
// 																memset(szBuffer,0,128);
// 																pPos = strstr(pDataBuffer,"&nbsp");
// 																if (pPos)
// 																{
// 																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																	//strcpy(pAdaptMenuSet->menuset.arDiskItems[3],szBuffer);
// 																	CChineseCode::Utf8ToAscii(szBuffer,pAdaptMenuSet->menuset.arDiskItems[3]);
// 																	pDataBuffer += strlen(szBuffer);
// 																	pDataBuffer += iSeparate;
// 																	memset(szBuffer,0,128);
// 																	pPos = strstr(pDataBuffer,"&nbsp");
// 																	if (pPos)
// 																	{
// 																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																		strcpy(pAdaptMenuSet->menuset.comPre,szBuffer);
// 																		pDataBuffer += strlen(szBuffer);
// 																		pDataBuffer += iSeparate;
// 																		memset(szBuffer,0,128);
// 																		pPos = strstr(pDataBuffer,"&nbsp");
// 																		if (pPos)
// 																		{
// 																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																			strcpy(pAdaptMenuSet->menuset.comAfx,szBuffer);
// 																			pDataBuffer += strlen(szBuffer);
// 																			pDataBuffer += iSeparate;
// 																			memset(szBuffer,0,128);
// 																			pPos = strstr(pDataBuffer,"&nbsp");
// 																			if (pPos)
// 																			{
// 																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																				pAdaptMenuSet->menuset.startNumber = atoi(szBuffer);
// 																				pDataBuffer += strlen(szBuffer);
// 																				pDataBuffer += iSeparate;
// 																				memset(szBuffer,0,128);
// 																				pPos = strstr(pDataBuffer,"&nbsp");
// 																				if (pPos)
// 																				{
// 																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																					strcpy(pAdaptMenuSet->menuset.workGroup,szBuffer);
// 																					pDataBuffer += strlen(szBuffer);
// 																					pDataBuffer += iSeparate;
// 																					memset(szBuffer,0,128);
// 																					pPos = strstr(pDataBuffer,"&nbsp");
// 																					if (pPos)
// 																					{
// 																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																						strcpy(pAdaptMenuSet->menuset.scrRes,szBuffer);
// 																						pDataBuffer += strlen(szBuffer);
// 																						pDataBuffer += iSeparate;
// 																						memset(szBuffer,0,128);
// 																						pPos = strstr(pDataBuffer,"&nbsp");
// 																						if (pPos)
// 																						{
// 																							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																							strcpy(pAdaptMenuSet->menuset.gatewayMAC,szBuffer);
// 																							pDataBuffer += strlen(szBuffer);
// 																							pDataBuffer += iSeparate;
// 																							memset(szBuffer,0,128);
// 																							pPos = strstr(pDataBuffer,"&nbsp");
// 																							if (pPos)
// 																							{
// 																								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																								pAdaptMenuSet->menuset.coverDirIp = inet_addr(szBuffer);
// 																								pDataBuffer += strlen(szBuffer);
// 																								pDataBuffer += iSeparate;
// 																								memset(szBuffer,0,128);
// 																								pPos = strstr(pDataBuffer,"&nbsp");
// 																								if (pPos)
// 																								{
// 																									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																									pAdaptMenuSet->menuset.coverMirrIp = inet_addr(szBuffer);
// 																									pDataBuffer += strlen(szBuffer);
// 																									pDataBuffer += iSeparate;
// 																									memset(szBuffer,0,128);
// 																									pPos = strstr(pDataBuffer,"&nbsp");
// 																									if (pPos)
// 																									{
// 																										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																										pAdaptMenuSet->menuset.coverHotBakIP = inet_addr(szBuffer);
// 																										pDataBuffer += strlen(szBuffer);
// 																										pDataBuffer += iSeparate;
// 																										memset(szBuffer,0,128);
// 																										pPos = strstr(pDataBuffer,"&nbsp");
// 																										if (pPos)
// 																										{
// 																											memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																											pAdaptMenuSet->menuset.m_WksMemory = atol(szBuffer);
// 																											pDataBuffer += strlen(szBuffer);
// 																											pDataBuffer += iSeparate;
// 																											memset(szBuffer,0,128);
// 																											pPos = strstr(pDataBuffer,"&nbsp");
// 																											if (pPos)
// 																											{
// 																												memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																												pAdaptMenuSet->menuset.m_WksAutoClear = atoi(szBuffer);
// 																												pDataBuffer += strlen(szBuffer);
// 																												pDataBuffer += iSeparate;
// 																												memset(szBuffer,0,128);
// 																												pPos = strstr(pDataBuffer,"&nbsp");
// 																												if (pPos)
// 																												{
// 																													memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																													pAdaptMenuSet->menuset.m_UseHotBackup = atoi(szBuffer);
// 																													pDataBuffer += strlen(szBuffer);
// 																													pDataBuffer += iSeparate;
// 																													memset(szBuffer,0,128);
// 																													pPos = strstr(pDataBuffer,"&nbsp");
// 																													if (pPos)
// 																													{
// 																														memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																														strcpy(pAdaptMenuSet->menuset.displayName,szBuffer);
// 																														pDataBuffer += strlen(szBuffer);
// 																														pDataBuffer += iSeparate;
// 																														memset(szBuffer,0,128);
// 																														pPos = strstr(pDataBuffer,"&nbsp");
// 																														if (pPos)
// 																														{
// 																															memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																															strcpy(pAdaptMenuSet->menuset.menuName,szBuffer);
// 																															pDataBuffer += strlen(szBuffer);
// 																															pDataBuffer += iSeparate;
// 																															memset(szBuffer,0,128);
// 																															pPos = strstr(pDataBuffer,"&nbsp");
// 																															if (pPos)
// 																															{
// 																																memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																strcpy(pAdaptMenuSet->adaptset.adapterName,szBuffer);
// 																																pDataBuffer += strlen(szBuffer);
// 																																pDataBuffer += iSeparate;
// 																																memset(szBuffer,0,128);
// 																																pPos = strstr(pDataBuffer,"&nbsp");
// 																																if (pPos)
// 																																{
// 																																	memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																	pAdaptMenuSet->adaptset.loginIP = inet_addr(szBuffer);
// 																																	pDataBuffer += strlen(szBuffer);
// 																																	pDataBuffer += iSeparate;
// 																																	memset(szBuffer,0,128);
// 																																	pPos = strstr(pDataBuffer,"&nbsp");
// 																																	if (pPos)
// 																																	{
// 																																		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																		pAdaptMenuSet->adaptset.spareLoginIp = inet_addr(szBuffer);
// 																																		pDataBuffer += strlen(szBuffer);
// 																																		pDataBuffer += iSeparate;
// 																																		memset(szBuffer,0,128);
// 																																		pPos = strstr(pDataBuffer,"&nbsp");
// 																																		if (pPos)
// 																																		{
// 																																			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																			pAdaptMenuSet->adaptset.wksStartIp = inet_addr(szBuffer);
// 																																			pDataBuffer += strlen(szBuffer);
// 																																			pDataBuffer += iSeparate;
// 																																			memset(szBuffer,0,128);
// 																																			pPos = strstr(pDataBuffer,"&nbsp");
// 																																			if (pPos)
// 																																			{
// 																																				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																				pAdaptMenuSet->adaptset.wksSubMask = inet_addr(szBuffer);
// 																																				pDataBuffer += strlen(szBuffer);
// 																																				pDataBuffer += iSeparate;
// 																																				memset(szBuffer,0,128);
// 																																				pPos = strstr(pDataBuffer,"&nbsp");
// 																																				if (pPos)
// 																																				{
// 																																					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																					pAdaptMenuSet->adaptset.subsectionIp = atoi(szBuffer);
// 																																					pDataBuffer += strlen(szBuffer);
// 																																					pDataBuffer += iSeparate;
// 																																					memset(szBuffer,0,128);
// 																																					pPos = strstr(pDataBuffer,"&nbsp");
// 																																					if (pPos)
// 																																					{
// 																																						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																						pAdaptMenuSet->adaptset.dhcpCount = atoi(szBuffer);
// 																																						pDataBuffer += strlen(szBuffer);
// 																																						pDataBuffer += iSeparate;
// 																																						memset(szBuffer,0,128);
// 																																						pPos = strstr(pDataBuffer,"&nbsp");
// 																																						if (pPos)
// 																																						{
// 																																							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																							pAdaptMenuSet->adaptset.gateway = inet_addr(szBuffer);
// 																																							pDataBuffer += strlen(szBuffer);
// 																																							pDataBuffer += iSeparate;
// 																																							memset(szBuffer,0,128);
// 																																							pPos = strstr(pDataBuffer,"&nbsp");
// 																																							if (pPos)
// 																																							{
// 																																								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																								pAdaptMenuSet->adaptset.dns1 = inet_addr(szBuffer);
// 																																								pDataBuffer += strlen(szBuffer);
// 																																								pDataBuffer += iSeparate;
// 																																								memset(szBuffer,0,128);
// 																																								pPos = strstr(pDataBuffer,"&nbsp");
// 																																								if (pPos)
// 																																								{
// 																																									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 																																									pAdaptMenuSet->adaptset.dns2 = inet_addr(szBuffer);
// 																																									pDataBuffer += strlen(szBuffer);
// 																																									pDataBuffer += iSeparate;
// 																																									memset(szBuffer,0,128);
// 																																									return 1;
// 																																								}
// 																																							}
// 																																						}
// 																																					}
// 																																				}
// 																																			}
// 																																		}
// 																																	}
// 																																}
// 																															}
// 																														}
// 																													}
// 																												}
// 																											}
// 																										}
// 																									}
// 																								}
// 																							}
// 																						}
// 																					}
// 																				}
// 																			}
// 																		}
// 																	}
// 																}
// 															}
// 														}
// 													}
// 												}
// 											}
// 										}
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// CString	CMzd::AdaptMenuSet_Operation(int nFlag, AdaptMenuSet *pAdaptMenuSet)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(AdaptMenuSet);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 	switch (nFlag)
// 	{
// 	case	0:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_ADD_MENU_MSG;
// 			break;
// 		}
// 	case	1:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_MODIFY_ADAPT_OF_MENUSET_MSG;
// 			break;
// 		}
// 	case	2:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_DEL_MENU_MSG;
// 			break;
// 		}
// 	}
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pAdaptMenuSet,sizeof(AdaptMenuSet));
// 	CString		StrResult;
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接MZD服务器"));
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp"));
// 	return StrResult;
// }
// 
// int		CMzd::GetDisksetNameList(CStringArray& StrDisksetNameList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_DISK_NAMELIST_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pRecvBuffer = new byte[DataSizeof];
// 	byte*	pbTemp = pRecvBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (DataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pbTemp,sizeof(DisksetNameList));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pbTemp += iSocketRet;
// 	}
// 	DisksetNameList*	pDisksetNameList = (DisksetNameList*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		CString	StrData;
// 		CString	StrTemp(pDisksetNameList->disksetname);
// 		StrData.Format(_T("['%s'],"),StrTemp);
// 		StrDisksetNameList.Add(StrData);
// 		pDisksetNameList++;
// 	}
// 	return StrDisksetNameList.GetCount();
// }
// 
// int	CMzd::GetServerIoIp(CStringArray&	ServerIoList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_DATA_SERVER_LIST_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pRecvBuffer = new byte[DataSizeof];
// 	byte*	pbTemp = pRecvBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (DataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pbTemp,sizeof(IoServer));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pbTemp += iSocketRet;
// 	}
// 	IoServer*	pIoServer = (IoServer*)pRecvBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		CString	StrData;
// 		CString	StrTemp(pIoServer->ioIp);
// 		StrData.Format(_T("['%s'],"),StrTemp);
// 		ServerIoList.Add(StrData);
// 		pIoServer++;
// 	}
// 	return ServerIoList.GetCount();
// }
// 
// int		CMzd::GetIpBtServerDiskList(CStringArray& DiskList,DisksetByServerIp* pServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(DisksetByServerIp);
// 
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.uCommand = MZD_GET_DISKSET_BYSERVERIP_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pServerIp,sizeof(DisksetByServerIp));
// 	CString		StrResult;
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pRecvBuffer = new byte[DataSizeof];
// 	byte*	pbTempRecv = pRecvBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (DataSizeof != dwCumulative)
// 	{
// 		iSocketRet = Receive(pbTempRecv,sizeof(DiskSet));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pbTempRecv += iSocketRet;
// 	}
// 	DiskSet*	pDiskSet = (DiskSet*)pRecvBuffer;
// 	for(int i = 0;i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzclientWriteDirBuffer[MAX_PATH] = { 0 };
// 		CString	StrclientWriteDir(pDiskSet->clientWriteDir);
// 		AddChar(StrclientWriteDir.GetBuffer(),(wchar_t*)wzclientWriteDirBuffer,MAX_PATH);
// 		sockaddr_in stAddr;
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->dirIp;
// 		CString	StrdirIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->mirrIp;
// 		CString	StrmirrIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->hotBakIP;
// 		CString	StrhotBakIP(inet_ntoa(stAddr.sin_addr));
// 
// 		CString	StrssdVolum(pDiskSet->ssdVolum);
// 
// 		CString	StrdestinationFile(pDiskSet->destinationFile);
// 		TCHAR	wzdestinationFile[MAX_PATH] = { 0 };
// 		AddChar(StrdestinationFile.GetBuffer(),wzdestinationFile,MAX_PATH);
// 
// 		CString	StrarWorkDir0(pDiskSet->arWorkDir[0]);
// 		TCHAR	wzarWorkDir0[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir0.GetBuffer(),wzarWorkDir0,MAX_PATH);
// 
// 		CString	StrarWorkDir1(pDiskSet->arWorkDir[1]);
// 		TCHAR	wzarWorkDir1[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir1.GetBuffer(),wzarWorkDir1,MAX_PATH);
// 
// 		CString	StrarWorkDir2(pDiskSet->arWorkDir[2]);
// 		TCHAR	wzarWorkDir2[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir2.GetBuffer(),wzarWorkDir2,MAX_PATH);
// 
// 		CString	StrarWorkDir3(pDiskSet->arWorkDir[3]);
// 		TCHAR	wzarWorkDir3[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir3.GetBuffer(),wzarWorkDir3,MAX_PATH);
// 
// 		CString	StrdiskName(pDiskSet->diskName);
// 		CString	StrDiskDisplayName(pDiskSet->diskDisplayName);
// 
// 		CString	StrData;
// 		StrData.Format(_T("['%d','%d','%d','%d','%d','%d','%ld','%ld','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s','%ld','%s','%s','%s','%ld','%s','%s','%s','%s','%s','%s','%s','%ld','%ld','%s'],"),
// 			pDiskSet->isAutoUpload,
// 			pDiskSet->isAllowUpload,
// 			pDiskSet->isAllowRevert,
// 			pDiskSet->isAllowClear,
// 			pDiskSet->isAutoRevert,
// 			pDiskSet->isAutoClear,
// 			pDiskSet->readCacheSize,
// 			pDiskSet->writeCacheSize,
// 			pDiskSet->abreastSum,
// 			pDiskSet->retryTimeOut,
// 			pDiskSet->dosReadSize,
// 			pDiskSet->dosWriteSize,
// 			pDiskSet->winReadSize,
// 			pDiskSet->winWriteSize,
// 			pDiskSet->localCacheSize,
// 			pDiskSet->isDelayLoad,
// 			pDiskSet->isIScsiBoot,
// 			wzclientWriteDirBuffer,
// 			pDiskSet->diskQuota,
// 			StrdirIp,
// 			StrmirrIp,
// 			StrhotBakIP,
// 			pDiskSet->ssdCacheSize,
// 			StrssdVolum,
// 			wzdestinationFile,
// 			wzarWorkDir0,
// 			wzarWorkDir1,
// 			wzarWorkDir2,
// 			wzarWorkDir3,
// 			StrdiskName,
// 			pDiskSet->readCacheType,
// 			pDiskSet->writeCacheType,
// 			StrDiskDisplayName);
// 		DiskList.Add(StrData);
// 		pDiskSet++;
// 	}
// 	delete	[]pRecvBuffer;
// 	return DiskList.GetCount();
// }
// 
// CString	CMzd::Wkstation_Operation(int nFlag, Wkstation *pWkstation)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(Wkstation);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 
// 	CString	StrResult;
// 	switch (nFlag)
// 	{
// 	case	0:
// 		Mzd_Quest_Head.uCommand = MZD_ADD_WKS_MSG;
// 		break;
// 	case	1:
// 		Mzd_Quest_Head.uCommand = MZD_MODIFY_WKS_MSG;
// 		break;
// 	case	2:
// 		Mzd_Quest_Head.uCommand = MZD_DEL_WKS_MSG;
// 		break;
// 	case	3:
// 		Mzd_Quest_Head.uCommand = MZD_USE_WKS_MSG;
// 		break;
// 	case	4:
// 		Mzd_Quest_Head.uCommand = MZD_FORBIDDEN_WKS_MSG;
// 		break;
// 	case	5:
// 		Mzd_Quest_Head.uCommand = MZD_CLOSE_WKS_MSG;
// 		break;
// 	case	6:
// 		Mzd_Quest_Head.uCommand = MZD_RESTART_WKS_MSG;
// 		break;
// 	case	7:
// 		Mzd_Quest_Head.uCommand = MZD_WAKEUP_WKS_MSG;
// 		break;
// 	}
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pWkstation,sizeof(Wkstation));
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult = _T("1&nbsp操作成功");
// 	return StrResult;
// }
// 
// CString	CMzd::CreateNewImg_Operation(CreateNewImg*	pCreateNewImg)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(CreateNewImg);
// 
// 	CString	StrResult;
// 
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_CREATE_NEW_IMG_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pCreateNewImg,sizeof(CreateNewImg));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::AccImg_Operation(AccImg*	pAccImg)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(AccImg);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_ACC_IMG_SIZE_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pAccImg,sizeof(AccImg));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::DirectUpdate_Operation(DirectUpdate*	pDirectUpdate)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(DirectUpdate);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_DIRECT_UPDATE_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pDirectUpdate,sizeof(DirectUpdate));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::BackupUpdate_Operation(BackupUpdate*	pBackupUpdate)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(BackupUpdate);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_BACKUP_UPDATE_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pBackupUpdate,sizeof(BackupUpdate));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::RestoreDisk_Operation(RestoreDisk*		pRestoreDisk)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(RestoreDisk);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_SYNC_DISK_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pRestoreDisk,sizeof(RestoreDisk));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::SyncDisk_Operation(SyncDisk*	pSyncDisk)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(SyncDisk);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_SYNC_DISK_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pSyncDisk,sizeof(SyncDisk));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::ServerIo_Operation(int nFlag, ServerDiskListIp*	ServerIp)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(ServerDiskListIp);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	switch (nFlag)
// 	{
// 	case	0:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_ADD_IOSERVER_MSG;
// 			break;
// 		}
// 	case	1:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_DEL_IOSERVER_MSG;
// 			break;
// 		}
// 	}
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,ServerIp,sizeof(ServerDiskListIp));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		goto End;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		goto End;
// 	}
// 	StrResult = _T("1&nbsp操作成功");
// End:
// 	return StrResult;
// }
// 
// int		CMzd::GetRegDiskIdList(CStringArray&	DiskIdList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_GET_PHYSICALDISKID_MSG;
// 
// 	int			iSocketRet;
// 	CString	StrResult;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	for(int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		PhysicalDiskId	DiskId = { 0 };
// 		iSocketRet = Receive(&DiskId,sizeof(PhysicalDiskId));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			break;
// 		}
// 		CString	StrDiskId(DiskId.diskId);
// 		CString	StrData;
// 		StrData.Format(_T("['%s'],"),StrDiskId);
// 		DiskIdList.Add(StrData);
// 	}
// 	return DiskIdList.GetCount();
// }
// 
// CString	CMzd::GetRegStatus()
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_GET_REGISTER_STATUS;
// 
// 	int			iSocketRet;
// 	CString	StrResult;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::UserRegLogin(MZDRegister*	pRegInfo)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(MZDRegister);
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_REGISTER_MSG;
// 
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pTempBuffer = pSendBuffer;
// 	memcpy(pTempBuffer,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pTempBuffer += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pTempBuffer,pRegInfo,sizeof(MZDRegister));
// 
// 	int			iSocketRet;
// 	CString	StrResult;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	Sleep(100);
// 
// 	struct timeval tv_out;
// 	tv_out.tv_sec = 1000 * 60 * 10;
// 	tv_out.tv_usec = 0;
// 	setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));
// 
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString	CMzd::GenerateNewDiskS_Operation(GenerateNewDiskS*	pGenerateNewDiskS)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(GenerateNewDiskS);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_GENERATE_NEW_DISK_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pGenerateNewDiskS,sizeof(GenerateNewDiskS));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString		CMzd::GetCurrentDiskTask(IoServer*	pIoServer)
// {
// 	CString	StrResult;
// 	CString	StrIpAddress(pIoServer->ioIp);
// 	CMzd*	pMzd = new CMzd;
// 	pMzd->Init(StrIpAddress,m_MzdServerPort);
// 	if (pMzd->ConnectServer())
// 	{
// 		SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 		Mzd_Quest_Head.wHead = 1978;
// 		Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 		Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 		Mzd_Quest_Head.uCommand = MZD_GET_CURREENT_RUN_TASK_MSG;
// 
// 		int			iSocketRet;
// 		iSocketRet = pMzd->Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			StrResult = _T("0&nbsp错误！");
// 			goto End;
// 		}
// 		Sleep(100);
// 		SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 		iSocketRet = pMzd->Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			StrResult = _T("0&nbsp错误！");
// 			goto End;
// 		}
// 		tagTask		CurrentTask = { 0 };
// 
// 		iSocketRet = pMzd->Receive(&CurrentTask,sizeof(tagTask));
// 		if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 		{
// 			StrResult = _T("0&nbsp错误！");
// 			goto End;
// 		}
// 		CString	StringServerIp(CurrentTask.servername);
// 		CString	StringSyncIp(CurrentTask.syncservername);
// 
// 		TCHAR	lpwzsImgpath[64] = { 0 };
// 		CString	StringImgpath(CurrentTask.imgPath);
// 		AddChar(StringImgpath.GetBuffer(),(wchar_t*)lpwzsImgpath,64);
// 
// 		TCHAR	lpwzsFixUdopath[64] = { 0 };
// 		CString	StringFixUdopath(CurrentTask.fixudoPath);
// 		AddChar(StringFixUdopath.GetBuffer(),(wchar_t*)lpwzsFixUdopath,64);
// 
// 		TCHAR	lpwzsNewimgpath[64] = { 0 };
// 		CString	StringNewimgpath(CurrentTask.newimgPath);
// 		AddChar(StringNewimgpath.GetBuffer(),(wchar_t*)lpwzsNewimgpath,64);
// 
// 		StrResult.Format(_T("1&nbsp['%d','%d','%d','%s','%s','%s','%d','%s','%s',]"),
// 			CurrentTask.taskId,
// 			CurrentTask.taskFinishPercent,
// 			CurrentTask.taskType,
// 			StringServerIp,
// 			StringSyncIp,
// 			lpwzsImgpath,
// 			CurrentTask.imgSize,
// 			lpwzsFixUdopath,
// 			lpwzsNewimgpath);
// 	}
// End:
// 	pMzd->Close();
// 	delete pMzd;
// 	return StrResult;
// }
// 
// int			CMzd::LoadDiskTask(tagTask*	pDiskTask,	char*	pDataBuffer)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[128] = { 0 };
// 	pPos = strstr(pDataBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 		pDiskTask->taskId = atoi(szBuffer);
// 		pDataBuffer += strlen(szBuffer);
// 		pDataBuffer += iSeparate;
// 		memset(szBuffer,0,128);
// 		pPos = strstr(pDataBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 			pDiskTask->taskFinishPercent = atoi(szBuffer);
// 			pDataBuffer += strlen(szBuffer);
// 			pDataBuffer += iSeparate;
// 			memset(szBuffer,0,128);
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				pDiskTask->taskType = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,128);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					CChineseCode::Utf8ToAscii(szBuffer,pDiskTask->servername);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,128);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						CChineseCode::Utf8ToAscii(szBuffer,pDiskTask->syncservername);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,128);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							CChineseCode::Utf8ToAscii(szBuffer,pDiskTask->imgPath);
// 							pDataBuffer += strlen(szBuffer);
// 							pDataBuffer += iSeparate;
// 							memset(szBuffer,0,128);
// 							pPos = strstr(pDataBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 								pDiskTask->imgSize = atoi(szBuffer);
// 								pDataBuffer += strlen(szBuffer);
// 								pDataBuffer += iSeparate;
// 								memset(szBuffer,0,128);
// 								pPos = strstr(pDataBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 									CChineseCode::Utf8ToAscii(szBuffer,pDiskTask->fixudoPath);
// 									pDataBuffer += strlen(szBuffer);
// 									pDataBuffer += iSeparate;
// 									memset(szBuffer,0,128);
// 									pPos = strstr(pDataBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 										CChineseCode::Utf8ToAscii(szBuffer,pDiskTask->newimgPath);
// 										pDataBuffer += strlen(szBuffer);
// 										pDataBuffer += iSeparate;
// 										memset(szBuffer,0,128);
// 										return 1;
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// CString		CMzd::DiskTask_Operation(tagTask*	pDiskTask)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(tagTask);
// 
// 	CString	StrResult;
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pSendTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.uCommand = MZD_DISK_MAITAIN_MSG;
// 
// 	memcpy(pSendTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pSendTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pSendTemp,pDiskTask,sizeof(tagTask));
// 
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		delete []pSendBuffer;
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// int 		CMzd::GetWkstationEx(CStringArray&	WksArray)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_ALL_WKS_EX_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	CString		StrResult;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	//byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pbBuffer = (byte*)GlobalAlloc(GPTR,DataSizeof);
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(tagWkstationEx));
// 		if (iSocketRet <= NULL)
// 		{
// 			GlobalFree(pbBuffer);
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += iSocketRet;
// 	}
// 	tagWkstationEx*	pWkstation = (tagWkstationEx*)pbBuffer;
// 	for (int u = 0; u < Mzd_Reply_Head.dwCount; u++)
// 	{
// 		//CString	strWksName(pWkstation->wksName);
// 		TCHAR		strWksName[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strWksName,pWkstation->wksName);
// 
// 		//CString	strWksIp(pWkstation->wksIp);
// 		TCHAR		strWksIp[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strWksIp,pWkstation->wksIp);
// 
// 		//CString	strWksMac(pWkstation->wksMac);
// 		TCHAR		strWksMac[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strWksMac,pWkstation->wksMac);
// 
// 		//CString	strWksMask(pWkstation->subMask);
// 		TCHAR		strWksMask[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strWksMask,pWkstation->subMask);
// 
// 		//CString	strWksGateway(pWkstation->gateway);
// 		TCHAR		strWksGateway[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strWksGateway,pWkstation->gateway);
// 
// 		//CString	strWksScrRes(pWkstation->scrRes);
// 		TCHAR		strWksScrRes[20] = { 0 };
// 		CChineseCode::AsciiToUnicode(strWksScrRes,pWkstation->scrRes);
// 
// 		//CString	strPre(pWkstation->comPre);
// 		TCHAR		strPre[20] = { 0 };
// 		CChineseCode::AsciiToUnicode(strPre,pWkstation->comPre);
// 
// 		//CString	strAfx(pWkstation->comAfx);
// 		TCHAR		strAfx[20] = { 0 };
// 		CChineseCode::AsciiToUnicode(strAfx,pWkstation->comAfx);
// 
// 		//CString strDns1(pWkstation->dns1);
// 		TCHAR		strDns1[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strDns1,pWkstation->dns1);
// 
// 		//CString strDns2(pWkstation->dns2);
// 		TCHAR		strDns2[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strDns2,pWkstation->dns2);
// 
// 		//CString	strStartServerIp(pWkstation->startServerIp);
// 		TCHAR		strStartServerIp[32] = { 0 };
// 		CChineseCode::AsciiToUnicode(strStartServerIp,pWkstation->startServerIp);
// 
// 		TCHAR	strWksMenuDisplay1[32] = { 0 };
// 		TCHAR	strWksMenuDisplay2[32] = { 0 };
// 		TCHAR	strWksMenuDisplay3[32] = { 0 };
// 		TCHAR	strWksMenuDisplay4[32] = { 0 };
// 
// 		//TCHAR	strWksMenName1[4][32] = { 0 };
// 		//TCHAR	strWksMenName2[4][32] = { 0 };
// 		//TCHAR	strWksMenName3[4][32] = { 0 };
// 		//TCHAR	strWksMenName4[4][32] = { 0 };
// 
// 		TCHAR	strWksMenName11[32] = { 0 };
// 		TCHAR	strWksMenName12[32] = { 0 };
// 		TCHAR	strWksMenName13[32] = { 0 };
// 		TCHAR	strWksMenName14[32] = { 0 };
// 
// 		TCHAR	strWksMenName21[32] = { 0 };
// 		TCHAR	strWksMenName22[32] = { 0 };
// 		TCHAR	strWksMenName23[32] = { 0 };
// 		TCHAR	strWksMenName24[32] = { 0 };
// 
// 		TCHAR	strWksMenName31[32] = { 0 };
// 		TCHAR	strWksMenName32[32] = { 0 };
// 		TCHAR	strWksMenName33[32] = { 0 };
// 		TCHAR	strWksMenName34[32] = { 0 };
// 
// 		TCHAR	strWksMenName41[32] = { 0 };
// 		TCHAR	strWksMenName42[32] = { 0 };
// 		TCHAR	strWksMenName43[32] = { 0 };
// 		TCHAR	strWksMenName44[32] = { 0 };
// 
// 		CChineseCode::AsciiToUnicode(strWksMenuDisplay1,pWkstation->menuGroup[0].displayname);
// 		CChineseCode::AsciiToUnicode(strWksMenuDisplay2,pWkstation->menuGroup[1].displayname);
// 		CChineseCode::AsciiToUnicode(strWksMenuDisplay3,pWkstation->menuGroup[2].displayname);
// 		CChineseCode::AsciiToUnicode(strWksMenuDisplay4,pWkstation->menuGroup[3].displayname);
// 
// 		CChineseCode::AsciiToUnicode(strWksMenName11,pWkstation->menuGroup[0].diskName[0]);
// 		CChineseCode::AsciiToUnicode(strWksMenName12,pWkstation->menuGroup[0].diskName[1]);
// 		CChineseCode::AsciiToUnicode(strWksMenName13,pWkstation->menuGroup[0].diskName[2]);
// 		CChineseCode::AsciiToUnicode(strWksMenName14,pWkstation->menuGroup[0].diskName[3]);
// 
// 		CChineseCode::AsciiToUnicode(strWksMenName21,pWkstation->menuGroup[1].diskName[0]);
// 		CChineseCode::AsciiToUnicode(strWksMenName22,pWkstation->menuGroup[1].diskName[1]);
// 		CChineseCode::AsciiToUnicode(strWksMenName23,pWkstation->menuGroup[1].diskName[2]);
// 		CChineseCode::AsciiToUnicode(strWksMenName24,pWkstation->menuGroup[1].diskName[3]);
// 
// 		CChineseCode::AsciiToUnicode(strWksMenName31,pWkstation->menuGroup[2].diskName[0]);
// 		CChineseCode::AsciiToUnicode(strWksMenName32,pWkstation->menuGroup[2].diskName[1]);
// 		CChineseCode::AsciiToUnicode(strWksMenName33,pWkstation->menuGroup[2].diskName[2]);
// 		CChineseCode::AsciiToUnicode(strWksMenName34,pWkstation->menuGroup[2].diskName[3]);
// 
// 		CChineseCode::AsciiToUnicode(strWksMenName41,pWkstation->menuGroup[3].diskName[0]);
// 		CChineseCode::AsciiToUnicode(strWksMenName42,pWkstation->menuGroup[3].diskName[1]);
// 		CChineseCode::AsciiToUnicode(strWksMenName43,pWkstation->menuGroup[3].diskName[2]);
// 		CChineseCode::AsciiToUnicode(strWksMenName44,pWkstation->menuGroup[3].diskName[3]);
// 
// 		TCHAR	lpwzsGroupName[18] = { 0 };
// 		CChineseCode::AsciiToUnicode(lpwzsGroupName,pWkstation->groupName);
// 
// 		CString	StrData;
// 		StrData.Format(_T("['%ld','%s','%s','%s','%s','%s','%s','%s','%d','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%d','%d','%d','%d','%s','%s','%s','%s','%s','%d','%d','%d'],"),
// 			pWkstation->wksNumber,
// 			strWksName,
// 			strWksIp,
// 			strWksMac,
// 			strWksMask,
// 			strWksGateway,
// 			strWksScrRes,
// 			lpwzsGroupName,
// 			pWkstation->numberLength,
// 			strWksMenuDisplay1,
// 			strWksMenName11,
// 			strWksMenName12,
// 			strWksMenName13,
// 			strWksMenName14,
// 			strWksMenuDisplay2,
// 			strWksMenName21,
// 			strWksMenName22,
// 			strWksMenName23,
// 			strWksMenName24,
// 			strWksMenuDisplay3,
// 			strWksMenName31,
// 			strWksMenName32,
// 			strWksMenName33,
// 			strWksMenName34,
// 			strWksMenuDisplay4,
// 			strWksMenName41,
// 			strWksMenName42,
// 			strWksMenName43,
// 			strWksMenName44,
// 			pWkstation->startMode,
// 			pWkstation->LocalMemoryCache,
// 			pWkstation->bStartHotBack,
// 			pWkstation->bAutoRestore,
// 			strPre,
// 			strAfx,
// 			strDns1,
// 			strDns2,
// 			strStartServerIp,
// 			pWkstation->bSuperMode,
// 			pWkstation->bOnlineStatus,
// 			pWkstation->bForbidStatus);
// 		pWkstation++;
// 		WksArray.Add(StrData);
// 	}
// 	GlobalFree(pbBuffer);
// 	return WksArray.GetCount();
// }
// 
// int			CMzd::LoadWkstationEx(tagWkstationEx*	pWksation, char*	pBuffer)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[256] = { 0 };
// 	pPos = strstr(pBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 		pWksation->wksNumber = atol(szBuffer);
// 		pBuffer += strlen(szBuffer);
// 		pBuffer += iSeparate;
// 		memset(szBuffer,0,256);
// 		pPos = strstr(pBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 			CChineseCode::Utf8ToAscii(szBuffer,pWksation->wksName);
// 			pBuffer += strlen(szBuffer);
// 			pBuffer += iSeparate;
// 			memset(szBuffer,0,256);
// 			pPos = strstr(pBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 				CChineseCode::Utf8ToAscii(szBuffer,pWksation->wksIp);
// 				pBuffer += strlen(szBuffer);
// 				pBuffer += iSeparate;
// 				memset(szBuffer,0,256);
// 				pPos = strstr(pBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 					CChineseCode::Utf8ToAscii(szBuffer,pWksation->wksMac);
// 					pBuffer += strlen(szBuffer);
// 					pBuffer += iSeparate;
// 					memset(szBuffer,0,256);
// 					pPos = strstr(pBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 						CChineseCode::Utf8ToAscii(szBuffer,pWksation->subMask);
// 						pBuffer += strlen(szBuffer);
// 						pBuffer += iSeparate;
// 						memset(szBuffer,0,256);
// 						pPos = strstr(pBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 							CChineseCode::Utf8ToAscii(szBuffer,pWksation->gateway);
// 							pBuffer += strlen(szBuffer);
// 							pBuffer += iSeparate;
// 							memset(szBuffer,0,256);
// 							pPos = strstr(pBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 								CChineseCode::Utf8ToAscii(szBuffer,pWksation->scrRes);
// 								pBuffer += strlen(szBuffer);
// 								pBuffer += iSeparate;
// 								memset(szBuffer,0,256);
// 								pPos = strstr(pBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 									CChineseCode::Utf8ToAscii(szBuffer,pWksation->groupName);
// 									pBuffer += strlen(szBuffer);
// 									pBuffer += iSeparate;
// 									memset(szBuffer,0,256);
// 									pPos = strstr(pBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 										pWksation->numberLength = atoi(szBuffer);
// 										pBuffer += strlen(szBuffer);
// 										pBuffer += iSeparate;
// 										memset(szBuffer,0,256);
// 
// 										pPos = strstr(pBuffer,"&nbsp");
// 										if (pPos)
// 										{
// 											memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 											CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[0].displayname);
// 											pBuffer += strlen(szBuffer);
// 											pBuffer += iSeparate;
// 											memset(szBuffer,0,256);
// 											pPos = strstr(pBuffer,"&nbsp");
// 											if (pPos)
// 											{
// 												memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 												CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[0].diskName[0]);
// 												pBuffer += strlen(szBuffer);
// 												pBuffer += iSeparate;
// 												memset(szBuffer,0,256);
// 												pPos = strstr(pBuffer,"&nbsp");
// 												if (pPos)
// 												{
// 													memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 													CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[0].diskName[1]);
// 													pBuffer += strlen(szBuffer);
// 													pBuffer += iSeparate;
// 													memset(szBuffer,0,256);
// 													pPos = strstr(pBuffer,"&nbsp");
// 													if (pPos)
// 													{
// 														memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 														CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[0].diskName[2]);
// 														pBuffer += strlen(szBuffer);
// 														pBuffer += iSeparate;
// 														memset(szBuffer,0,256);
// 														pPos = strstr(pBuffer,"&nbsp");
// 														if (pPos)
// 														{
// 															memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 															CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[0].diskName[3]);
// 															pBuffer += strlen(szBuffer);
// 															pBuffer += iSeparate;
// 															memset(szBuffer,0,256);
// 															pPos = strstr(pBuffer,"&nbsp");
// 															if (pPos)
// 															{
// 																memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[1].displayname);
// 																pBuffer += strlen(szBuffer);
// 																pBuffer += iSeparate;
// 																memset(szBuffer,0,256);
// 																pPos = strstr(pBuffer,"&nbsp");
// 																if (pPos)
// 																{
// 																	memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																	CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[1].diskName[0]);
// 																	pBuffer += strlen(szBuffer);
// 																	pBuffer += iSeparate;
// 																	memset(szBuffer,0,256);
// 																	pPos = strstr(pBuffer,"&nbsp");
// 																	if (pPos)
// 																	{
// 																		memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																		CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[1].diskName[1]);
// 																		pBuffer += strlen(szBuffer);
// 																		pBuffer += iSeparate;
// 																		memset(szBuffer,0,256);
// 																		pPos = strstr(pBuffer,"&nbsp");
// 																		if (pPos)
// 																		{
// 																			memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																			CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[1].diskName[2]);
// 																			pBuffer += strlen(szBuffer);
// 																			pBuffer += iSeparate;
// 																			memset(szBuffer,0,256);
// 																			pPos = strstr(pBuffer,"&nbsp");
// 																			if (pPos)
// 																			{
// 																				memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																				CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[1].diskName[3]);
// 																				pBuffer += strlen(szBuffer);
// 																				pBuffer += iSeparate;
// 																				memset(szBuffer,0,256);
// 																				pPos = strstr(pBuffer,"&nbsp");
// 																				if (pPos)
// 																				{
// 																					memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																					CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[2].displayname);
// 																					pBuffer += strlen(szBuffer);
// 																					pBuffer += iSeparate;
// 																					memset(szBuffer,0,256);
// 																					pPos = strstr(pBuffer,"&nbsp");
// 																					if (pPos)
// 																					{
// 																						memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																						CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[2].diskName[0]);
// 																						pBuffer += strlen(szBuffer);
// 																						pBuffer += iSeparate;
// 																						memset(szBuffer,0,256);
// 																						pPos = strstr(pBuffer,"&nbsp");
// 																						if (pPos)
// 																						{
// 																							memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																							CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[2].diskName[1]);
// 																							pBuffer += strlen(szBuffer);
// 																							pBuffer += iSeparate;
// 																							memset(szBuffer,0,256);
// 																							pPos = strstr(pBuffer,"&nbsp");
// 																							if (pPos)
// 																							{
// 																								memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																								CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[2].diskName[2]);
// 																								pBuffer += strlen(szBuffer);
// 																								pBuffer += iSeparate;
// 																								memset(szBuffer,0,256);
// 																								pPos = strstr(pBuffer,"&nbsp");
// 																								if (pPos)
// 																								{
// 																									memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																									CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[2].diskName[3]);
// 																									pBuffer += strlen(szBuffer);
// 																									pBuffer += iSeparate;
// 																									memset(szBuffer,0,256);
// 																									pPos = strstr(pBuffer,"&nbsp");
// 																									if (pPos)
// 																									{
// 																										memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																										CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[3].displayname);
// 																										pBuffer += strlen(szBuffer);
// 																										pBuffer += iSeparate;
// 																										memset(szBuffer,0,256);
// 																										pPos = strstr(pBuffer,"&nbsp");
// 																										if (pPos)
// 																										{
// 																											memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																											CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[3].diskName[0]);
// 																											pBuffer += strlen(szBuffer);
// 																											pBuffer += iSeparate;
// 																											memset(szBuffer,0,256);
// 																											pPos = strstr(pBuffer,"&nbsp");
// 																											if (pPos)
// 																											{
// 																												memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																												CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[3].diskName[1]);
// 																												pBuffer += strlen(szBuffer);
// 																												pBuffer += iSeparate;
// 																												memset(szBuffer,0,256);
// 																												pPos = strstr(pBuffer,"&nbsp");
// 																												if (pPos)
// 																												{
// 																													memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																													CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[3].diskName[2]);
// 																													pBuffer += strlen(szBuffer);
// 																													pBuffer += iSeparate;
// 																													memset(szBuffer,0,256);
// 																													pPos = strstr(pBuffer,"&nbsp");
// 																													if (pPos)
// 																													{
// 																														memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																														CChineseCode::Utf8ToAscii(szBuffer,pWksation->menuGroup[3].diskName[3]);
// 																														pBuffer += strlen(szBuffer);
// 																														pBuffer += iSeparate;
// 																														memset(szBuffer,0,256);
// 																														pPos = strstr(pBuffer,"&nbsp");
// 																														if (pPos)
// 																														{
// 																															memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																															pWksation->startMode = atoi(szBuffer);
// 																															pBuffer += strlen(szBuffer);
// 																															pBuffer += iSeparate;
// 																															memset(szBuffer,0,256);
// 																															pPos = strstr(pBuffer,"&nbsp");
// 																															if (pPos)
// 																															{
// 																																memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																pWksation->LocalMemoryCache = atoi(szBuffer);
// 																																pBuffer += strlen(szBuffer);
// 																																pBuffer += iSeparate;
// 																																memset(szBuffer,0,256);
// 																																pPos = strstr(pBuffer,"&nbsp");
// 																																if (pPos)
// 																																{
// 																																	memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																	pWksation->bStartHotBack = atoi(szBuffer);
// 																																	pBuffer += strlen(szBuffer);
// 																																	pBuffer += iSeparate;
// 																																	memset(szBuffer,0,256);
// 																																	pPos = strstr(pBuffer,"&nbsp");
// 																																	if (pPos)
// 																																	{
// 																																		memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																		pWksation->bAutoRestore = atoi(szBuffer);
// 																																		pBuffer += strlen(szBuffer);
// 																																		pBuffer += iSeparate;
// 																																		memset(szBuffer,0,256);
// 																																		pPos = strstr(pBuffer,"&nbsp");
// 																																		if (pPos)
// 																																		{
// 																																			memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																			CChineseCode::Utf8ToAscii(szBuffer,pWksation->comPre);
// 																																			pBuffer += strlen(szBuffer);
// 																																			pBuffer += iSeparate;
// 																																			memset(szBuffer,0,256);
// 																																			pPos = strstr(pBuffer,"&nbsp");
// 																																			if (pPos)
// 																																			{
// 																																				memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																				CChineseCode::Utf8ToAscii(szBuffer,pWksation->comAfx);
// 																																				pBuffer += strlen(szBuffer);
// 																																				pBuffer += iSeparate;
// 																																				memset(szBuffer,0,256);
// 																																				pPos = strstr(pBuffer,"&nbsp");
// 																																				if (pPos)
// 																																				{
// 																																					memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																					CChineseCode::Utf8ToAscii(szBuffer,pWksation->dns1);
// 																																					pBuffer += strlen(szBuffer);
// 																																					pBuffer += iSeparate;
// 																																					memset(szBuffer,0,256);
// 																																					pPos = strstr(pBuffer,"&nbsp");
// 																																					if (pPos)
// 																																					{
// 																																						memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																						CChineseCode::Utf8ToAscii(szBuffer,pWksation->dns2);
// 																																						pBuffer += strlen(szBuffer);
// 																																						pBuffer += iSeparate;
// 																																						memset(szBuffer,0,256);
// 																																						pPos = strstr(pBuffer,"&nbsp");
// 																																						if (pPos)
// 																																						{
// 																																							memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																							CChineseCode::Utf8ToAscii(szBuffer,pWksation->startServerIp);
// 																																							pBuffer += strlen(szBuffer);
// 																																							pBuffer += iSeparate;
// 																																							memset(szBuffer,0,256);
// 																																							pPos = strstr(pBuffer,"&nbsp");
// 																																							if (pPos)
// 																																							{
// 																																								memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																								pWksation->bSuperMode = atoi(szBuffer);
// 																																								pBuffer += strlen(szBuffer);
// 																																								pBuffer += iSeparate;
// 																																								memset(szBuffer,0,256);
// 																																								pPos = strstr(pBuffer,"&nbsp");
// 																																								if (pPos)
// 																																								{
// 																																									memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																									pWksation->bOnlineStatus = atoi(szBuffer);
// 																																									pBuffer += strlen(szBuffer);
// 																																									pBuffer += iSeparate;
// 																																									memset(szBuffer,0,256);
// 																																									pPos = strstr(pBuffer,"&nbsp");
// 																																									if (pPos)
// 																																									{
// 																																										memcpy(szBuffer,pBuffer,pPos - pBuffer);
// 																																										pWksation->bForbidStatus = atoi(szBuffer);
// 																																										pBuffer += strlen(szBuffer);
// 																																										pBuffer += iSeparate;
// 																																										memset(szBuffer,0,256);
// 																																										return 1;
// 																																									}
// 																																								}
// 																																							}
// 																																						}
// 																																					}
// 																																				}
// 																																			}
// 																																		}
// 																																	}
// 																																}
// 																															}
// 																														}
// 																													}
// 																												}
// 																											}
// 																										}
// 																									}
// 																								}
// 																							}
// 																						}
// 																					}
// 																				}
// 																			}
// 																		}
// 																	}
// 																}
// 															}
// 														}
// 													}
// 												}
// 											}
// 										}
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// CString		CMzd::WksationEx_Operation(int nFlags, tagWkstationEx*	pWksEx)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(_tagWkstationEx);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 
// 	CString	StrResult;
// 	switch (nFlags)
// 	{
// 	case	0:
// 		Mzd_Quest_Head.uCommand = MZD_MODIFY_WKS_EX_MSG;
// 		break;
// 	case	1:
// 		Mzd_Quest_Head.uCommand = MZD_DEL_WKS_EX_MSG;
// 		break;
// 	case	3:
// 		Mzd_Quest_Head.uCommand = MZD_USE_WKS_MSG;
// 		break;
// 	case	4:
// 		Mzd_Quest_Head.uCommand = MZD_FORBIDDEN_WKS_MSG;
// 		break;
// 	case	5:
// 		Mzd_Quest_Head.uCommand = MZD_CLOSE_WKS_MSG;
// 		break;
// 	case	6:
// 		Mzd_Quest_Head.uCommand = MZD_RESTART_WKS_MSG;
// 		break;
// 	case	7:
// 		Mzd_Quest_Head.uCommand = MZD_WAKEUP_WKS_MSG;
// 		break;
// 	}
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pWksEx,sizeof(_tagWkstationEx));
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// CString		CMzd::WksationEx_Add(tagAddWksInfo*	pAddWks)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(tagAddWksInfo);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 
// 	CString	StrResult;
// 	Mzd_Quest_Head.uCommand = MZD_ADD_WKS_EX_MSG;
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pAddWks,sizeof(tagAddWksInfo));
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// int			CMzd::GetServerSetList(CStringArray&	ServerSetLsit)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_SERVER_LIST_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(tagServerCfg));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += sizeof(tagServerCfg);
// 	}
// 	tagServerCfg*	pServerCfg = (tagServerCfg*)pbBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		sockaddr_in stAddr;
// 
// 		CString	strName(pServerCfg->serverName);
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pServerCfg->adaptIp[0];
// 		CString	str(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pServerCfg->adaptIp[0];
// 		CString	stradaptIp1(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pServerCfg->adaptIp[1];
// 		CString	stradaptIp2(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pServerCfg->adaptIp[2];
// 		CString	stradaptIp3(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pServerCfg->adaptIp[3];
// 		CString	stradaptIp4(inet_ntoa(stAddr.sin_addr));
// 
// 
// 		CString	strSSD1(pServerCfg->ssdDisk[0]);
// 		CString	strSSD2(pServerCfg->ssdDisk[1]);
// 
// 		TCHAR	lpwzsWorkDir1[64] = { 0 };
// 		TCHAR	lpwzsWorkDir2[64] = { 0 };
// 		TCHAR	lpwzsWorkDir3[64] = { 0 };
// 		TCHAR	lpwzsWorkDir4[64] = { 0 };
// 
// 		CChineseCode::AsciiToUnicode(lpwzsWorkDir1,pServerCfg->workDir[0]);
// 		CChineseCode::AsciiToUnicode(lpwzsWorkDir2,pServerCfg->workDir[1]);
// 		CChineseCode::AsciiToUnicode(lpwzsWorkDir3,pServerCfg->workDir[2]);
// 		CChineseCode::AsciiToUnicode(lpwzsWorkDir4,pServerCfg->workDir[3]);
// 
// 		TCHAR	lpwzsAdaptName1[64] = { 0 };
// 		TCHAR	lpwzsAdaptName2[64] = { 0 };
// 		TCHAR	lpwzsAdaptName3[64] = { 0 };
// 		TCHAR	lpwzsAdaptName4[64] = { 0 };
// 
// 		CChineseCode::AsciiToUnicode(lpwzsAdaptName1,pServerCfg->adaptName[0]);
// 		CChineseCode::AsciiToUnicode(lpwzsAdaptName2,pServerCfg->adaptName[1]);
// 		CChineseCode::AsciiToUnicode(lpwzsAdaptName3,pServerCfg->adaptName[2]);
// 		CChineseCode::AsciiToUnicode(lpwzsAdaptName4,pServerCfg->adaptName[3]);
// 
// 
// 		TCHAR	lpwzsBuffer[64];
// 		memset(lpwzsBuffer,0,sizeof(TCHAR) * 64);
// 		AddChar(lpwzsWorkDir1,lpwzsBuffer,64);
// 		lstrcpyn(lpwzsWorkDir1,lpwzsBuffer,64);
// 
// 		memset(lpwzsBuffer,0,sizeof(TCHAR) * 64);
// 		AddChar(lpwzsWorkDir2,lpwzsBuffer,64);
// 		lstrcpyn(lpwzsWorkDir2,lpwzsBuffer,64);
// 
// 		memset(lpwzsBuffer,0,sizeof(TCHAR) * 64);
// 		AddChar(lpwzsWorkDir3,lpwzsBuffer,64);
// 		lstrcpyn(lpwzsWorkDir3,lpwzsBuffer,64);
// 
// 		memset(lpwzsBuffer,0,sizeof(TCHAR) * 64);
// 		AddChar(lpwzsWorkDir4,lpwzsBuffer,64);
// 		lstrcpyn(lpwzsWorkDir4,lpwzsBuffer,64);
// 		CString	strData;
// 		strData.Format(_T("['%s','%s','%s','%s','%s','%s','%s','%s','%s','%ld','%ld','%ld','%ld','%s','%s','%s','%s','%s','%s','%d','%d'],"),
// 			strName,
// 			stradaptIp1,
// 			stradaptIp2,
// 			stradaptIp3,
// 			stradaptIp4,
// 			lpwzsAdaptName1,
// 			lpwzsAdaptName2,
// 			lpwzsAdaptName3,
// 			lpwzsAdaptName4,
// 			pServerCfg->writeCacheSize,
// 			pServerCfg->systemCacheSize,
// 			pServerCfg->dataCacheSize,
// 			pServerCfg->ssdCacheSize,
// 			strSSD1,
// 			strSSD2,
// 			lpwzsWorkDir1,
// 			lpwzsWorkDir2,
// 			lpwzsWorkDir3,
// 			lpwzsWorkDir4,
// 			pServerCfg->networkGameGroup,
// 			pServerCfg->bServerUseHotBackup);
// 		ServerSetLsit.Add(strData);
// 		pServerCfg++;
// 	}
// 	return ServerSetLsit.GetCount();
// }
// 
// int			CMzd::LoadServerInfo(tagServerCfg*	pServerInfo, char*	pBuffer)
// {
// 	int iSeparate = strlen("&nbsp");
// 	char*	pPos = NULL;
// 	char	szBuffer[255] = { 0 };
// 	pPos = strstr(pBuffer,"&nbsp");
// 	if (pPos)
// 	{
// 		memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 		CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->serverName);
// 		pBuffer += strlen(szBuffer);
// 		pBuffer += iSeparate;
// 		memset(szBuffer,0,255);
// 		pPos = strstr(pBuffer,"&nbsp");
// 		if (pPos)
// 		{
// 			memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 			pServerInfo->adaptIp[0] = inet_addr(szBuffer);
// 			pBuffer += strlen(szBuffer);
// 			pBuffer += iSeparate;
// 			memset(szBuffer,0,255);
// 			pPos = strstr(pBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 				pServerInfo->adaptIp[1] = inet_addr(szBuffer);
// 				pBuffer += strlen(szBuffer);
// 				pBuffer += iSeparate;
// 				memset(szBuffer,0,255);
// 				pPos = strstr(pBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 					pServerInfo->adaptIp[2] = inet_addr(szBuffer);
// 					pBuffer += strlen(szBuffer);
// 					pBuffer += iSeparate;
// 					memset(szBuffer,0,255);
// 					pPos = strstr(pBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 						pServerInfo->adaptIp[3] = inet_addr(szBuffer);
// 						pBuffer += strlen(szBuffer);
// 						pBuffer += iSeparate;
// 						memset(szBuffer,0,255);
// 						pPos = strstr(pBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 							CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->adaptName[0]);
// 							pBuffer += strlen(szBuffer);
// 							pBuffer += iSeparate;
// 							memset(szBuffer,0,255);
// 							pPos = strstr(pBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 								CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->adaptName[1]);
// 								pBuffer += strlen(szBuffer);
// 								pBuffer += iSeparate;
// 								memset(szBuffer,0,255);
// 								pPos = strstr(pBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 									CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->adaptName[2]);
// 									pBuffer += strlen(szBuffer);
// 									pBuffer += iSeparate;
// 									memset(szBuffer,0,255);
// 									pPos = strstr(pBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 										CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->adaptName[3]);
// 										pBuffer += strlen(szBuffer);
// 										pBuffer += iSeparate;
// 										memset(szBuffer,0,255);
// 										pPos = strstr(pBuffer,"&nbsp");
// 										if (pPos)
// 										{
// 											memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 											pServerInfo->writeCacheSize = atol(szBuffer);
// 											pBuffer += strlen(szBuffer);
// 											pBuffer += iSeparate;
// 											memset(szBuffer,0,255);
// 											pPos = strstr(pBuffer,"&nbsp");
// 											if (pPos)
// 											{
// 												memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 												pServerInfo->systemCacheSize = atol(szBuffer);
// 												pBuffer += strlen(szBuffer);
// 												pBuffer += iSeparate;
// 												memset(szBuffer,0,255);
// 												pPos = strstr(pBuffer,"&nbsp");
// 												if (pPos)
// 												{
// 													memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 													pServerInfo->dataCacheSize = atol(szBuffer);
// 													pBuffer += strlen(szBuffer);
// 													pBuffer += iSeparate;
// 													memset(szBuffer,0,255);
// 													pPos = strstr(pBuffer,"&nbsp");
// 													if (pPos)
// 													{
// 														memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 														pServerInfo->ssdCacheSize = atol(szBuffer);
// 														pBuffer += strlen(szBuffer);
// 														pBuffer += iSeparate;
// 														memset(szBuffer,0,255);
// 														pPos = strstr(pBuffer,"&nbsp");
// 														if (pPos)
// 														{
// 															memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 															strcpy(&pServerInfo->ssdDisk[0],szBuffer);
// 															pBuffer += strlen(szBuffer);
// 															pBuffer += iSeparate;
// 															memset(szBuffer,0,255);
// 															pPos = strstr(pBuffer,"&nbsp");
// 															if (pPos)
// 															{
// 																memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 																strcpy(&pServerInfo->ssdDisk[1],szBuffer);
// 																pBuffer += strlen(szBuffer);
// 																pBuffer += iSeparate;
// 																memset(szBuffer,0,255);
// 																pPos = strstr(pBuffer,"&nbsp");
// 																if (pPos)
// 																{
// 																	memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 																	CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->workDir[0]);
// 																	pBuffer += strlen(szBuffer);
// 																	pBuffer += iSeparate;
// 																	memset(szBuffer,0,255);
// 																	pPos = strstr(pBuffer,"&nbsp");
// 																	if (pPos)
// 																	{
// 																		memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 																		CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->workDir[1]);
// 																		pBuffer += strlen(szBuffer);
// 																		pBuffer += iSeparate;
// 																		memset(szBuffer,0,255);
// 																		pPos = strstr(pBuffer,"&nbsp");
// 																		if (pPos)
// 																		{
// 																			memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 																			CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->workDir[2]);
// 																			pBuffer += strlen(szBuffer);
// 																			pBuffer += iSeparate;
// 																			memset(szBuffer,0,255);
// 																			pPos = strstr(pBuffer,"&nbsp");
// 																			if (pPos)
// 																			{
// 																				memcpy(szBuffer,pBuffer, pPos - pBuffer);
// 																				CChineseCode::Utf8ToAscii(szBuffer,pServerInfo->workDir[3]);
// 																				pBuffer += strlen(szBuffer);
// 																				pBuffer += iSeparate;
// 																				memset(szBuffer,0,255);
// 																				return 1;
// 																			}
// 																		}
// 																	}
// 																}
// 															}
// 														}
// 													}
// 												}
// 											}
// 										}
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 0;
// }
// 
// CString		CMzd::ServerSet_Operation(int nFlags, tagServerCfg*	pServerSet)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(tagServerCfg);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = dwMemory;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 	Mzd_Quest_Head.dwCount = 1;
// 
// 	CString	StrResult;
// 	switch (nFlags)
// 	{
// 	case	0:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_ADD_SERVER_MSG;
// 			break;
// 		}
// 	case	1:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_MODIFY_SERVER_MSG;
// 			break;
// 		}
// 	case	2:
// 		{
// 			Mzd_Quest_Head.uCommand = MZD_DEL_SERVER_MSG;
// 			break;
// 		}
// 	}
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pServerSet,sizeof(tagServerCfg));
// 	int			iSocketRet;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	delete []pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		StrResult = _T("0&nbsp错误！");
// 		return StrResult;
// 	}
// 	StrResult.Format(_T("1&nbsp%d&nbsp"),Mzd_Reply_Head.iErrorCode);
// 	return StrResult;
// }
// 
// int		CMzd::GetDiskSetEx(GetDisksetByServerName *pDiskName, CStringArray& DiskList)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(GetDisksetByServerName);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_DISKSET_BYSERVERNAME_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pDiskName,sizeof(GetDisksetByServerName));
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(DiskSetEx));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += sizeof(DiskSetEx);
// 	}
// 	DiskSetEx*	pDiskSet = (DiskSetEx*)pbBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	wzclientWriteDirBuffer[MAX_PATH] = { 0 };
// 		CString	StrclientWriteDir(pDiskSet->clientWriteDir);
// 		AddChar(StrclientWriteDir.GetBuffer(),(wchar_t*)wzclientWriteDirBuffer,MAX_PATH);
// 		sockaddr_in stAddr;
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->dirIp;
// 		CString	StrdirIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->mirrIp;
// 		CString	StrmirrIp(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->hotBakIP;
// 		CString	StrhotBakIP(inet_ntoa(stAddr.sin_addr));
// 
// 		CString	StrssdVolum(pDiskSet->ssdVolum);
// 
// 		CString	StrdestinationFile(pDiskSet->destinationFile);
// 		TCHAR	wzdestinationFile[MAX_PATH] = { 0 };
// 		AddChar(StrdestinationFile.GetBuffer(),wzdestinationFile,MAX_PATH);
// 
// 		CString	StrarWorkDir0(pDiskSet->arWorkDir[0]);
// 		TCHAR	wzarWorkDir0[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir0.GetBuffer(),wzarWorkDir0,MAX_PATH);
// 
// 		CString	StrarWorkDir1(pDiskSet->arWorkDir[1]);
// 		TCHAR	wzarWorkDir1[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir1.GetBuffer(),wzarWorkDir1,MAX_PATH);
// 
// 		CString	StrarWorkDir2(pDiskSet->arWorkDir[2]);
// 		TCHAR	wzarWorkDir2[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir2.GetBuffer(),wzarWorkDir2,MAX_PATH);
// 
// 		CString	StrarWorkDir3(pDiskSet->arWorkDir[3]);
// 		TCHAR	wzarWorkDir3[MAX_PATH] = { 0 };
// 		AddChar(StrarWorkDir3.GetBuffer(),wzarWorkDir3,MAX_PATH);
// 
// 		CString	StrdiskName(pDiskSet->diskName);
// 		CString	StrDiskDisplayName(pDiskSet->diskDisplayName);
// 		CString	strServerName(pDiskSet->serverName);
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->serverIp[0];
// 		CString	strServerIp0(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->serverIp[1];
// 		CString	strServerIp1(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->serverIp[2];
// 		CString	strServerIp2(inet_ntoa(stAddr.sin_addr));
// 
// 		memset(&stAddr,0,sizeof(sockaddr_in));
// 		stAddr.sin_addr.S_un.S_addr = pDiskSet->serverIp[3];
// 		CString	strServerIp3(inet_ntoa(stAddr.sin_addr));
// 
// 
// 		CString	StrData;
// 		StrData.Format(_T("['%d','%d','%d','%d','%d','%d','%ld','%ld','%d','%d','%d','%d','%d','%d','%d','%d','%d','%s','%ld','%s','%s','%s','%ld','%s','%s','%s','%s','%s','%s','%s','%ld','%ld','%s','%d','%d','%s','%s','%s','%s','%s'],"),
// 			pDiskSet->isAutoUpload,
// 			pDiskSet->isAllowUpload,
// 			pDiskSet->isAllowRevert,
// 			pDiskSet->isAllowClear,
// 			pDiskSet->isAutoRevert,
// 			pDiskSet->isAutoClear,
// 			pDiskSet->readCacheSize,
// 			pDiskSet->writeCacheSize,
// 			pDiskSet->abreastSum,
// 			pDiskSet->retryTimeOut,
// 			pDiskSet->dosReadSize,
// 			pDiskSet->dosWriteSize,
// 			pDiskSet->winReadSize,
// 			pDiskSet->winWriteSize,
// 			pDiskSet->localCacheSize,
// 			pDiskSet->isDelayLoad,
// 			pDiskSet->isIScsiBoot,
// 			wzclientWriteDirBuffer,
// 			pDiskSet->diskQuota,
// 			StrdirIp,
// 			StrmirrIp,
// 			StrhotBakIP,
// 			pDiskSet->ssdCacheSize,
// 			StrssdVolum,
// 			wzdestinationFile,
// 			wzarWorkDir0,
// 			wzarWorkDir1,
// 			wzarWorkDir2,
// 			wzarWorkDir3,
// 			StrdiskName,
// 			pDiskSet->readCacheType,
// 			pDiskSet->writeCacheType,
// 			StrDiskDisplayName,
// 			pDiskSet->diskType,
// 			pDiskSet->disksize,
// 			strServerName,
// 			strServerIp0,
// 			strServerIp1,
// 			strServerIp2,
// 			strServerIp3);
// 		DiskList.Add(StrData);
// 		pDiskSet++;
// 	}
// 	delete []pbBuffer;
// 	return DiskList.GetCount();
// }
// 
// int			CMzd::GetServerAdaptList(CStringArray&	ServerAdaptList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_ALL_SERVER_ADAPT_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(ServerAdaptName));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += sizeof(ServerAdaptName);
// 	}
// 	ServerAdaptName*	pServerAdapt = (ServerAdaptName*)pbBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		TCHAR	lpwzsServerAdaptName[64] = { 0 };
// 		CChineseCode::AsciiToUnicode(lpwzsServerAdaptName,pServerAdapt->ServerAdapt);
// 		CString	strData;
// 		strData.Format(_T("['%s'],"),
// 			lpwzsServerAdaptName);
// 		ServerAdaptList.Add(strData);
// 		pServerAdapt++;
// 	}
// 	return ServerAdaptList.GetCount();
// }
// 
// int			CMzd::GetTaskList(SerIp*	pServerIp, CStringArray&	TaskList)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(SerIp);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_SERVER_TASK_LIST_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pServerIp,sizeof(SerIp));
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	delete	[]pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(tagTask));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += sizeof(tagTask);
// 	}
// 	tagTask*	pTask = (tagTask*)pbBuffer;
// 	for(int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		CString	strServerName(pTask->servername);
// 		CString strSyncIp(pTask->syncservername);
// 		TCHAR	lpwzsImgPath[64] = { 0 };
// 		CString	strImgPath(pTask->imgPath);
// 		AddChar(strImgPath.GetBuffer(),lpwzsImgPath,64);
// 
// 		TCHAR	lpwzsFixUdoPath[64] = { 0 };
// 		CString	strFixUdoPath(pTask->fixudoPath);
// 		AddChar(strFixUdoPath.GetBuffer(),lpwzsFixUdoPath,64);
// 
// 		TCHAR	lpwzsNewImgPath[64] = { 0 };
// 		CString	strNewImgPath(pTask->newimgPath);
// 		AddChar(strNewImgPath.GetBuffer(),lpwzsNewImgPath,64);
// 		CString	strData;
// 		strData.Format(_T("['%d','%d','%d','%s','%s','%s','%d','%s','%s'],"),
// 			pTask->taskId,
// 			pTask->taskFinishPercent,
// 			pTask->taskType,
// 			strServerName,
// 			strSyncIp,
// 			lpwzsImgPath,
// 			pTask->imgSize,
// 			lpwzsFixUdoPath,
// 			lpwzsNewImgPath);
// 		TaskList.Add(strData);
// 		pTask++;
// 	}
// 	return TaskList.GetCount();
// }
// 
// CString	CMzd::GetImgSize(tagGetImgDiskSize* pImgInfo)
// {
// 	DWORD	dwMemory = sizeof(SOCKET_HEAD_REQUEST);
// 	dwMemory += sizeof(tagGetImgDiskSize);
// 	byte*	pSendBuffer = new byte[dwMemory];
// 	byte*	pbTemp = pSendBuffer;
// 
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_IMG_DISK_SIZE_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	memcpy(pbTemp,&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	pbTemp += sizeof(SOCKET_HEAD_REQUEST);
// 	memcpy(pbTemp,pImgInfo,sizeof(tagGetImgDiskSize));
// 
// 	int			iSocketRet;
// 	CString			strResult;
// 	iSocketRet = Send(pSendBuffer,dwMemory);
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		strResult.Format(_T("0&nbsp"));
// 		return strResult;
// 	}
// 	delete	[]pSendBuffer;
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		strResult.Format(_T("0&nbsp"));
// 		return strResult;
// 	}
// 	if (Mzd_Reply_Head.iErrorCode != NULL)
// 	{
// 		strResult.Format(_T("0&nbsp"));
// 		return strResult;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(tagGetImgDiskSize));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			strResult.Format(_T("0&nbsp"));
// 			return strResult;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += sizeof(tagGetImgDiskSize);
// 	}
// 	tagGetImgDiskSize*	pImg = (tagGetImgDiskSize*)pbBuffer;
// 	TCHAR		lpwzsImgPath[MAX_PATH] = { 0 };
// 	CChineseCode::Utf8ToUniCode(pImg->imgPath,lpwzsImgPath);
// 	
// 	strResult.Format(_T("1&nbsp['%s','%d']"),lpwzsImgPath,pImg->imgsectornums);
// 	return strResult;
// }
// 
// int	CMzd::GetAllPacket(CStringArray&	PacketList)
// {
// 	SOCKET_HEAD_REQUEST	Mzd_Quest_Head = { 0 };
// 	Mzd_Quest_Head.wHead = 1978;
// 	Mzd_Quest_Head.dwRequestSize = sizeof(SOCKET_HEAD_REQUEST);
// 	Mzd_Quest_Head.uCommand = MZD_GET_IMG_PARTITION_PHYSICAL_MSG;
// 	Mzd_Quest_Head.wUIVer = CAppMain::m_Ver;
// 
// 	int			iSocketRet;
// 	int			iResult = 0;
// 	iSocketRet = Send(&Mzd_Quest_Head,sizeof(SOCKET_HEAD_REQUEST));
// 	if (iSocketRet == SOCKET_ERROR)
// 	{
// 		return -1;
// 	}
// 	Sleep(100);
// 	SOCKET_HEAD_REPLY	Mzd_Reply_Head;
// 	iSocketRet = Receive(&Mzd_Reply_Head,sizeof(SOCKET_HEAD_REPLY));
// 	if (iSocketRet == SOCKET_ERROR || iSocketRet == NULL)
// 	{
// 		return -1;
// 	}
// 	DWORD	DataSizeof = Mzd_Reply_Head.dwReplySize - sizeof(SOCKET_HEAD_REPLY);
// 	byte*	pbBuffer = new byte[DataSizeof];
// 	byte*	pTemp = pbBuffer;
// 	DWORD	dwCumulative = 0;
// 	while (dwCumulative != DataSizeof)
// 	{
// 		iSocketRet = Receive(pTemp,sizeof(ImgResponse));
// 		if (iSocketRet == SOCKET_ERROR)
// 		{
// 			return -1;
// 		}
// 		dwCumulative += iSocketRet;
// 		pTemp += iSocketRet;
// 	}
// 	ImgResponse*	pPacket = (ImgResponse*)pbBuffer;
// 	for (int i = 0; i < Mzd_Reply_Head.dwCount; i++)
// 	{
// 		CString	strData;
// 		TCHAR	lpwzsBuffer[MAX_PATH] = { 0 };
// 		CString	strPath(pPacket->imgpath);
// 		AddChar(strPath.GetBuffer(),lpwzsBuffer,260);
// 		strData.Format(_T("['%s','%d'],"),lpwzsBuffer,pPacket->imgsectornums);
// 		pPacket++;
// 		PacketList.Add(strData);
// 	}
// 	return PacketList.GetCount();
// }
// 
// int		CMzd::Mzd_Message(int iRequestFlag, char *pDataBuffer, CString &StrResult)
// {
// 	int iResult = 0;
// 	if (!ConnectServer())
// 	{
// 		StrResult.Format(_T("0&nbsp无法连接Mzd服务器!"));
// 		return 1;
// 	}
// 	switch (iRequestFlag)
// 	{
// 	case	MZD_GET_DEFAULT_COLUMN_MSG:
// 		{
// 			CStringArray	ColumnList;
// 			int iRet = GetColumnList(ColumnList);
// 			if (iRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < ColumnList.GetCount(); i++)
// 			{
// 				StrRetData += ColumnList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_WKS_MSG:
// 		{
// 			CStringArray	WksArray;
// 			int iRet = GetWkstation(WksArray);
// 			if (iRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < WksArray.GetCount(); i++)
// 			{
// 				StrRetData += WksArray.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_GLOBAL_SET_MSG:
// 		{
// 			StrResult = GetGlobalInfo();
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_PHYSICAL_DISK_MSG:
// 		{
// 			CStringArray	PhysicsDiskList;
// 			physicalDiskRequest	ServerIp = { 0 };
// 			char	lpBuffer[260] = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 				ServerIp.serverIp[0] = inet_addr(lpBuffer);
// 				pDataBuffer += iSeparate;
// 				pDataBuffer += strlen(lpBuffer);
// 				memset(lpBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 					ServerIp.serverIp[1] = inet_addr(lpBuffer);
// 					pDataBuffer += iSeparate;
// 					pDataBuffer += strlen(lpBuffer);
// 					memset(lpBuffer,0,260);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 						ServerIp.serverIp[2] = inet_addr(lpBuffer);
// 						pDataBuffer += iSeparate;
// 						pDataBuffer += strlen(lpBuffer);
// 						memset(lpBuffer,0,260);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 							ServerIp.serverIp[3] = inet_addr(lpBuffer);
// 							pDataBuffer += iSeparate;
// 							pDataBuffer += strlen(lpBuffer);
// 							memset(lpBuffer,0,260);
// 
// 							int iRet = GetPhysicsDiskList(PhysicsDiskList,&ServerIp);
// 							if (iRet == -1)
// 							{
// 								StrResult.Format(_T("0&nbsp错误"));
// 								iResult = 1;
// 								break;
// 							}
// 							CString			StrRetData;
// 							StrRetData += _T("1&nbsp[");
// 							for (int i = 0;i < PhysicsDiskList.GetCount(); i++)
// 							{
// 								StrRetData += PhysicsDiskList.GetAt(i);
// 							}
// 							StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 							StrResult += _T("]");
// 							iResult = 1;
// 						}
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	FQ_Remote_PhysicsDisk:
// 		{
// 			CStringArray	PhysicsDiskList;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.ServerIp,pDataBuffer,pPos - pDataBuffer);
// 				int iRet = Remote_GetPhysicsDiskList(PhysicsDiskList,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < PhysicsDiskList.GetCount(); i++)
// 				{
// 					StrRetData += PhysicsDiskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_DISK_PARTITION_MSG:
// 		{
// 			CStringArray	PartitionDiskList;
// 			partitionRequest	ServerIp = { 0 };
// 			char	lpBuffer[260] = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 				ServerIp.serverIp[0] = inet_addr(lpBuffer);
// 				pDataBuffer += iSeparate;
// 				pDataBuffer += strlen(lpBuffer);
// 				memset(lpBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 					ServerIp.serverIp[1] = inet_addr(lpBuffer);
// 					pDataBuffer += iSeparate;
// 					pDataBuffer += strlen(lpBuffer);
// 					memset(lpBuffer,0,260);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 						ServerIp.serverIp[2] = inet_addr(lpBuffer);
// 						pDataBuffer += iSeparate;
// 						pDataBuffer += strlen(lpBuffer);
// 						memset(lpBuffer,0,260);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 							ServerIp.serverIp[3] = inet_addr(lpBuffer);
// 							pDataBuffer += iSeparate;
// 							pDataBuffer += strlen(lpBuffer);
// 							memset(lpBuffer,0,260);
// 
// 							int iRet = GetPartitionDiskList(PartitionDiskList,&ServerIp);
// 							if (iRet == -1)
// 							{
// 								StrResult.Format(_T("0&nbsp错误"));
// 								iResult = 1;
// 								break;
// 							}
// 							CString			StrRetData;
// 							StrRetData += _T("1&nbsp[");
// 							for (int i = 0;i < PartitionDiskList.GetCount(); i++)
// 							{
// 								StrRetData += PartitionDiskList.GetAt(i);
// 							}
// 							StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 							StrResult += _T("]");
// 							iResult = 1;
// 						}
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	FQ_Remote_AllDisk:
// 		{
// 			CStringArray	PartitionDiskList;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.ServerIp,pDataBuffer,pPos - pDataBuffer);
// 				int iRet = Remote_GetPartitionDiskList(PartitionDiskList,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < PartitionDiskList.GetCount(); i++)
// 				{
// 					StrRetData += PartitionDiskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_IMG_LIST_MSG:
// 		{
// 			CStringArray	ImgDiskList;
// 			Img	ServerIp = { 0 };
// 			char	lpBuffer[260] = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 				ServerIp.serverIp[0] = inet_addr(lpBuffer);
// 				pDataBuffer += iSeparate;
// 				pDataBuffer += strlen(lpBuffer);
// 				memset(lpBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 					ServerIp.serverIp[1] = inet_addr(lpBuffer);
// 					pDataBuffer += iSeparate;
// 					pDataBuffer += strlen(lpBuffer);
// 					memset(lpBuffer,0,260);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 						ServerIp.serverIp[2] = inet_addr(lpBuffer);
// 						pDataBuffer += iSeparate;
// 						pDataBuffer += strlen(lpBuffer);
// 						memset(lpBuffer,0,260);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 							ServerIp.serverIp[3] = inet_addr(lpBuffer);
// 							pDataBuffer += iSeparate;
// 							pDataBuffer += strlen(lpBuffer);
// 							memset(lpBuffer,0,260);
// 							int iRet = GetImgDiskList(ImgDiskList,&ServerIp);
// 							if (iRet == -1)
// 							{
// 								StrResult.Format(_T("0&nbsp错误"));
// 								iResult = 1;
// 								break;
// 							}
// 							CString			StrRetData;
// 							StrRetData += _T("1&nbsp[");
// 							for (int i = 0;i < ImgDiskList.GetCount(); i++)
// 							{
// 								StrRetData += ImgDiskList.GetAt(i);
// 							}
// 							StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 							StrResult += _T("]");
// 							iResult = 1;
// 						}
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	FQ_Remote_Img:
// 		{
// 			CStringArray	ImgDiskList;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.ServerIp,pDataBuffer,pPos - pDataBuffer);
// 				int iRet = Remote_GetImgDiskList(ImgDiskList,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < ImgDiskList.GetCount(); i++)
// 				{
// 					StrRetData += ImgDiskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_FIX_LIST_MSG:
// 		{
// 			CStringArray	FixDiskList;
// 			FixParameter	stParameter = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char	szBuffer[260] = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				CChineseCode::Utf8ToAscii(szBuffer,stParameter.servername);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					CChineseCode::Utf8ToAscii(szBuffer,stParameter.imgpath);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,260);
// 					int iRet = GetFixDiskList(FixDiskList,&stParameter);
// 					if (iRet == -1)
// 					{
// 						StrResult.Format(_T("0&nbsp错误"));
// 						iResult = 1;
// 						break;
// 					}
// 					CString			StrRetData;
// 					StrRetData += _T("1&nbsp[");
// 					for (int i = 0;i < FixDiskList.GetCount(); i++)
// 					{
// 						StrRetData += FixDiskList.GetAt(i);
// 					}
// 					StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 					StrResult += _T("]");
// 					iResult = 1;
// 				}
// 			}
// 			break;
// 		}
// 	case	FQ_Remote_Fix:
// 		{
// 			CStringArray	FixDiskList;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.ServerIp,pDataBuffer,pPos - pDataBuffer);
// 				int iRet = Remote_GetFixDiskList(FixDiskList,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < FixDiskList.GetCount(); i++)
// 				{
// 					StrRetData += FixDiskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_UPLOAD_FIX_LISG_MSG:
// 		{
// 			CStringArray	UploadFix;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char	lpBuffer[260] = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(lpBuffer,pDataBuffer,pPos - pDataBuffer);
// 				CChineseCode::Utf8ToAscii(lpBuffer,ServerIp.ServerIp);
// 				int iRet = GetUploadFixDiskList(UploadFix,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < UploadFix.GetCount(); i++)
// 				{
// 					StrRetData += UploadFix.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	FQ_Remote_UploadFix:
// 		{
// 			CStringArray	UploadFix;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.ServerIp,pDataBuffer,pPos - pDataBuffer);
// 				int iRet = Remote_GetUploadFixDiskList(UploadFix,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < UploadFix.GetCount(); i++)
// 				{
// 					StrRetData += UploadFix.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	FQ_DiskSet_Operation:
// 		{
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer, pPos - pDataBuffer);
// 				int nFlag = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				DiskSetEx			DiskSetOperation = { 0 };
// 				iResult = LoadDiskSet(pDataBuffer,&DiskSetOperation);
// 				if (iResult == NULL)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				StrResult = DiskSet_Operation(nFlag,&DiskSetOperation);
// 				iResult = 1;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_MENU_MSG:
// 		{
// 			CStringArray	 AdaptMenuSetList;
// 			int iRet = GetAdaptMenuSet(AdaptMenuSetList);
// 			if (iRet == NULL)
// 			{
// 				StrResult = _T("1&nbsp");
// 				iResult = 1;
// 				break;
// 			}
// 			if (iRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < AdaptMenuSetList.GetCount(); i++)
// 			{
// 				StrRetData += AdaptMenuSetList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	FQ_AdaptMenuSet_Operation:
// 		{
// 			AdaptMenuSet	AdaptMenuSetData = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer, pPos - pDataBuffer);
// 				int nFlag = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				int iRet = LoadAdaptMenuSet(&AdaptMenuSetData,pDataBuffer);
// 				if (iRet == NULL)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				StrResult = AdaptMenuSet_Operation(nFlag,&AdaptMenuSetData);
// 				iResult = 1;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_DISK_NAMELIST_MSG:
// 		{
// 			CStringArray	 StrDiskNameList;
// 			int iRet = GetDisksetNameList(StrDiskNameList);
// 			if (iRet == NULL)
// 			{
// 				StrResult = _T("1&nbsp");
// 				iResult = 1;
// 				break;
// 			}
// 			if (iRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < StrDiskNameList.GetCount(); i++)
// 			{
// 				StrRetData += StrDiskNameList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_DATA_SERVER_LIST_MSG:
// 		{
// 			CStringArray	 ServerIoList;
// 			int iRet = GetServerIoIp(ServerIoList);
// 			if (iRet == NULL)
// 			{
// 				StrResult = _T("1&nbsp");
// 				iResult = 1;
// 				break;
// 			}
// 			if (iRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < ServerIoList.GetCount(); i++)
// 			{
// 				StrRetData += ServerIoList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_DISKSET_BYSERVERIP_MSG:
// 		{
// 			int iSeparate = strlen("&nbsp");
// 			DisksetByServerIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.serverIp,pDataBuffer,pPos - pDataBuffer);
// 				CStringArray	 ServerDiskList;
// 				int iRet = GetIpBtServerDiskList(ServerDiskList,&ServerIp);
// 				if (iRet == NULL)
// 				{
// 					StrResult = _T("1&nbsp");
// 					iResult = 1;
// 					break;
// 				}
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < ServerDiskList.GetCount(); i++)
// 				{
// 					StrRetData += ServerDiskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_UDO_LISG_MSG:
// 		{
// 			CStringArray	UdoResponseList;
// 			UdoParameter	stParameter = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char	szBuffer[260] = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				CChineseCode::Utf8ToAscii(szBuffer,stParameter.servername);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					CChineseCode::Utf8ToAscii(szBuffer,stParameter.imgpath);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,260);
// 					int iRet = GetUdoResponseList(UdoResponseList,&stParameter);
// 					if (iRet == -1)
// 					{
// 						StrResult.Format(_T("0&nbsp错误"));
// 						iResult = 1;
// 						break;
// 					}
// 					CString			StrRetData;
// 					StrRetData += _T("1&nbsp[");
// 					for (int i = 0;i < UdoResponseList.GetCount(); i++)
// 					{
// 						StrRetData += UdoResponseList.GetAt(i);
// 					}
// 					StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 					StrResult += _T("]");
// 					iResult = 1;
// 				}
// 			}
// 			break;
// 		}
// 	case	FQ_Remote_Udo:
// 		{
// 			CStringArray	UdoResponseList;
// 			ServerDiskListIp	ServerIp = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(ServerIp.ServerIp,pDataBuffer,pPos - pDataBuffer);
// 				int iRet = Remote_GetUdoResponseList(UdoResponseList,&ServerIp);
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < UdoResponseList.GetCount(); i++)
// 				{
// 					StrRetData += UdoResponseList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	FQ_Wkstation_Operation:
// 		{
// 			Wkstation	WkstationInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				int nFlag = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 
// 				int iRet = LoadWkstation(&WkstationInfo,pDataBuffer);
// 				if (iRet == NULL)
// 				{
// 					break;
// 				}
// 				StrResult = Wkstation_Operation(nFlag,&WkstationInfo);
// 				iResult = 1;
// 				break;
// 			}
// 			break;
// 		}
// 	case	MZD_SET_GLOBAL_SET_MSG:
// 		{
// 			GlobalSet	GlobalSetInfo = { 0 };
// 			int iRet = LoadGlobalSet(&GlobalSetInfo,pDataBuffer);
// 			if (iRet == NULL)
// 			{
// 				iResult = 0;
// 				break;
// 			}
// 			StrResult = SetGlobalInfo(&GlobalSetInfo);
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_CREATE_NEW_IMG_MSG:
// 		{
// 			CreateNewImg	CreateNewImgInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(CreateNewImgInfo.serverIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(CreateNewImgInfo.newimgpath,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						CreateNewImgInfo.imgsize = atol(szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						StrResult = CreateNewImg_Operation(&CreateNewImgInfo);
// 						iResult = 1;
// 						break;
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_ACC_IMG_SIZE_MSG:
// 		{
// 			AccImg	AccImgInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				//strcpy(AccImgInfo.serverIp,szBuffer);
// 				CChineseCode::Utf8ToAscii(szBuffer,AccImgInfo.serverIp);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					//strcpy(AccImgInfo.imgpath,szBuffer);
// 					CChineseCode::Utf8ToAscii(szBuffer,AccImgInfo.imgpath);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						AccImgInfo.Accimgsize = atol(szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						StrResult = AccImg_Operation(&AccImgInfo);
// 						iResult = 1;
// 						break;
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_DIRECT_UPDATE_MSG:
// 		{
// 			DirectUpdate	DirectUpdateInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(DirectUpdateInfo.serverIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(DirectUpdateInfo.imgpath,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(DirectUpdateInfo.fixpath,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						StrResult = DirectUpdate_Operation(&DirectUpdateInfo);
// 						iResult = 1;
// 						break;
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_BACKUP_UPDATE_MSG:
// 		{
// 			BackupUpdate	BackupUpdateInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(BackupUpdateInfo.serverIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(BackupUpdateInfo.imgpath,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(BackupUpdateInfo.fixpath,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						StrResult = BackupUpdate_Operation(&BackupUpdateInfo);
// 						iResult = 1;
// 						break;
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_RESTORE_DISK_MSG:
// 		{
// 			RestoreDisk	RestoreDiskInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(RestoreDiskInfo.serverIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(RestoreDiskInfo.imgpath,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(RestoreDiskInfo.udopath,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						StrResult = RestoreDisk_Operation(&RestoreDiskInfo);
// 						iResult = 1;
// 						break;
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_SYNC_DISK_MSG:
// 		{
// 			SyncDisk	SyncDiskInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(SyncDiskInfo.serverIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(SyncDiskInfo.syncIp,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(SyncDiskInfo.imgpath,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,64);
// 						StrResult = SyncDisk_Operation(&SyncDiskInfo);
// 						iResult = 1;
// 						break;
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	FQ_ServerIo_Operation:
// 		{
// 			ServerDiskListIp	ServerIo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[64] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				int nFlag = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,64);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(ServerIo.ServerIp,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,64);
// 					StrResult = ServerIo_Operation(nFlag,&ServerIo);
// 					iResult = 1;
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_GET_REGISTER_STATUS:
// 		{
// 			StrResult = GetRegStatus();
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_PHYSICALDISKID_MSG:
// 		{
// 			CStringArray	DiskIdList;
// 			int iRet = GetRegDiskIdList(DiskIdList);
// 			if (iRet == -1)
// 			{
// 				StrResult = _T("0&nbsp错误！");
// 				iResult = 1;
// 				break;
// 			}
// 			if (iRet == NULL)
// 			{
// 				StrResult = _T("1&nbsp");
// 				iResult = 1;
// 				break;
// 			}
// 			CString	StrData = _T("1&nbsp[");
// 			for (int i = 0; i < DiskIdList.GetCount(); i++)
// 			{
// 				StrData += DiskIdList.GetAt(i);
// 			}
// 			StrResult = StrData.Left(StrData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_REGISTER_MSG:
// 		{
// 			MZDRegister	RegInfo = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[260] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(RegInfo.diskId,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(RegInfo.agentId,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,260);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(RegInfo.password,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,260);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							RegInfo.lineType = atoi(szBuffer);
// 							pDataBuffer += strlen(szBuffer);
// 							pDataBuffer += iSeparate;
// 							memset(szBuffer,0,260);
// 							pPos = strstr(pDataBuffer,"&nbsp");
// 							if (pPos)
// 							{
// 								memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 								strcpy(RegInfo.smscode,szBuffer);
// 								pDataBuffer += strlen(szBuffer);
// 								pDataBuffer += iSeparate;
// 								memset(szBuffer,0,260);
// 								pPos = strstr(pDataBuffer,"&nbsp");
// 								if (pPos)
// 								{
// 									memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 									strcpy(RegInfo.MzdUserName,szBuffer);
// 									pDataBuffer += strlen(szBuffer);
// 									pDataBuffer += iSeparate;
// 									memset(szBuffer,0,260);
// 									pPos = strstr(pDataBuffer,"&nbsp");
// 									if (pPos)
// 									{
// 										memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 										strcpy(RegInfo.MzdUserPassWord,szBuffer);
// 										pDataBuffer += strlen(szBuffer);
// 										pDataBuffer += iSeparate;
// 										memset(szBuffer,0,260);
// 										StrResult = UserRegLogin(&RegInfo);
// 										iResult = 1;
// 										break;
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_GENERATE_NEW_DISK_MSG:
// 		{
// 			GenerateNewDiskS	NewDiskS = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[260] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(NewDiskS.serverIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					strcpy(NewDiskS.oldimgpath,szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,260);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(NewDiskS.oldfixpath,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,260);
// 						pPos = strstr(pDataBuffer,"&nbsp");
// 						if (pPos)
// 						{
// 							memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 							strcpy(NewDiskS.newimgpath,szBuffer);
// 							pDataBuffer += strlen(szBuffer);
// 							pDataBuffer += iSeparate;
// 							memset(szBuffer,0,260);
// 							StrResult = GenerateNewDiskS_Operation(&NewDiskS);
// 							iResult = 1;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 			break;
// 		}
// 	case	MZD_GET_CURREENT_RUN_TASK_MSG:
// 		{
// 			IoServer	ServerIp = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[260] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(ServerIp.ioIp,szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				StrResult = GetCurrentDiskTask(&ServerIp);
// 				iResult = 1;
// 			}
// 			break;
// 		}
// 	case	MZD_DISK_MAITAIN_MSG:
// 		{
// 			tagTask		DiskTask = { 0 };
// 			iResult = LoadDiskTask(&DiskTask,pDataBuffer);
// 			if (iResult == NULL)
// 			{
// 				break;
// 			}
// 			StrResult = DiskTask_Operation(&DiskTask);
// 			break;
// 		}
// 	case	MZD_GET_ALL_WKS_EX_MSG:
// 		{
// 			CStringArray	WksArray;
// 			int iRet = GetWkstationEx(WksArray);
// 			if (iRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			if (iRet == NULL)
// 			{
// 				StrResult.Format(_T("1&nbsp"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < WksArray.GetCount(); i++)
// 			{
// 				StrRetData += WksArray.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_ADD_WKS_EX_MSG:
// 		{
// 			tagAddWksInfo	NewWks = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[260] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				NewWks.startNumber = atol(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				pPos = strstr(pDataBuffer,"&nbsp");
// 				if (pPos)
// 				{
// 					memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 					NewWks.endNumber = atol(szBuffer);
// 					pDataBuffer += strlen(szBuffer);
// 					pDataBuffer += iSeparate;
// 					memset(szBuffer,0,260);
// 					pPos = strstr(pDataBuffer,"&nbsp");
// 					if (pPos)
// 					{
// 						memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 						strcpy(NewWks.startIp,szBuffer);
// 						pDataBuffer += strlen(szBuffer);
// 						pDataBuffer += iSeparate;
// 						memset(szBuffer,0,260);
// 
// 						iResult = LoadWkstationEx(&NewWks.wks,pDataBuffer);
// 						if (iResult == 0)
// 						{
// 							break;
// 						}
// 						StrResult = WksationEx_Add(&NewWks);
// 						break;
// 					}
// 				}
// 			}
// 		}
// 	case	FQ_WkstationEx_Operation:
// 		{
// 			tagWkstationEx	WksEx = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[260] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				int nFlags = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 				iResult = LoadWkstationEx(&WksEx,pDataBuffer);
// 				if (iResult == 0)
// 				{
// 					break;
// 				}
// 				StrResult = WksationEx_Operation(nFlags,&WksEx);
// 				break;
// 			}
// 		}
// 	case	MZD_GET_SERVER_LIST_MSG:
// 		{
// 			CStringArray	ServerSetList;
// 			int nRet = GetServerSetList(ServerSetList);
// 			if (nRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp"));
// 				iResult = 1;
// 				break;
// 			}
// 			if (nRet == NULL)
// 			{
// 				StrResult.Format(_T("1&nbsp"));
// 				iResult = 1;
// 				break;
// 			}
// 			CString			StrRetData;
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < ServerSetList.GetCount(); i++)
// 			{
// 				StrRetData += ServerSetList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	FQ_ServerList_Operation:
// 		{
// 			tagServerCfg	ServerSet = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			char	szBuffer[260] = { 0 };
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				int nFlags = atoi(szBuffer);
// 				pDataBuffer += strlen(szBuffer);
// 				pDataBuffer += iSeparate;
// 				memset(szBuffer,0,260);
// 
// 				iResult = LoadServerInfo(&ServerSet,pDataBuffer);
// 				if (iResult == NULL)
// 				{
// 					break;
// 				}
// 				StrResult = ServerSet_Operation(nFlags,&ServerSet);
// 				break;
// 			}
// 		}
// 	case	MZD_GET_DISKSET_BYSERVERNAME_MSG:
// 		{
// 			CStringArray	 ServerDiskList;
// 			char	szBuffer[64] = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			GetDisksetByServerName	ServerName = { 0 };
// 			char*	pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				CChineseCode::Utf8ToAscii(szBuffer,ServerName.serverName);
// 				int iRet = GetDiskSetEx(&ServerName,ServerDiskList);
// 				if (iRet == NULL)
// 				{
// 					StrResult = _T("1&nbsp");
// 					iResult = 1;
// 					break;
// 				}
// 				if (iRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				CString			StrRetData;
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < ServerDiskList.GetCount(); i++)
// 				{
// 					StrRetData += ServerDiskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_ALL_SERVER_ADAPT_MSG:
// 		{
// 			CStringArray	ServerAdaptList;
// 			int nRet = GetServerAdaptList(ServerAdaptList);
// 			CString			StrRetData;
// 			if (nRet == NULL)
// 			{
// 				StrResult = _T("1&nbsp");
// 				iResult = 1;
// 				break;
// 			}
// 			if (nRet == -1)
// 			{
// 				StrResult.Format(_T("0&nbsp错误"));
// 				iResult = 1;
// 				break;
// 			}
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < ServerAdaptList.GetCount(); i++)
// 			{
// 				StrRetData += ServerAdaptList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	case	MZD_GET_SERVER_TASK_LIST_MSG:
// 		{
// 			CStringArray	TaskList;
// 			char	szBuffer[64] = { 0 };
// 			SerIp	ServerIp = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				ServerIp.ServerIp[0] = inet_addr(szBuffer);
// 				int nRet = GetTaskList(&ServerIp,TaskList);
// 				CString			StrRetData;
// 				if (nRet == NULL)
// 				{
// 					StrResult = _T("1&nbsp");
// 					iResult = 1;
// 					break;
// 				}
// 				if (nRet == -1)
// 				{
// 					StrResult.Format(_T("0&nbsp错误"));
// 					iResult = 1;
// 					break;
// 				}
// 				StrRetData += _T("1&nbsp[");
// 				for (int i = 0;i < TaskList.GetCount(); i++)
// 				{
// 					StrRetData += TaskList.GetAt(i);
// 				}
// 				StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 				StrResult += _T("]");
// 				iResult = 1;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_IMG_DISK_SIZE_MSG:
// 		{
// 			tagGetImgDiskSize	ImgInfo = { 0 };
// 			char	szBuffer[64] = { 0 };
// 			int iSeparate = strlen("&nbsp");
// 			char*	pPos = NULL;
// 			pPos = strstr(pDataBuffer,"&nbsp");
// 			if (pPos)
// 			{
// 				memcpy(szBuffer,pDataBuffer,pPos - pDataBuffer);
// 				strcpy(ImgInfo.imgPath,szBuffer);
// 				StrResult = GetImgSize(&ImgInfo);
// 				iResult = 1;
// 			}
// 			break;
// 		}
// 	case	MZD_GET_IMG_PARTITION_PHYSICAL_MSG:
// 		{
// 			CStringArray	PacketList;
// 			CString			StrRetData;
// 			int		iRet = GetAllPacket(PacketList);
// 			if (iRet == -1)
// 			{
// 				break;
// 			}
// 			if (iRet == 0)
// 			{
// 				StrResult.Format(_T("1&nbsp"));
// 				iResult = 1;
// 				break;
// 			}
// 			StrRetData += _T("1&nbsp[");
// 			for (int i = 0;i < PacketList.GetCount(); i++)
// 			{
// 				StrRetData += PacketList.GetAt(i);
// 			}
// 			StrResult = StrRetData.Left(StrRetData.GetLength() - 1);
// 			StrResult += _T("]");
// 			iResult = 1;
// 			break;
// 		}
// 	}
// 	Close();
// 	return	iResult;
// }



