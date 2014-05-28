#pragma once
#include "FQ_Socket.h"
#include "MzdTypedef.h"
#include "CriticalSectionLock.h"
#include "JsonEx.h"

class CMzd
{
 public:
 	CMzd(void);
 	~CMzd(void);
// 	void		Init(CString	MzdServerIpAddress, UINT	MzdServerPort);
// 	BOOL		ConnectServer();
// 	int 		GetWkstation(CStringArray&	WksArray);
// 	int			LoadWkstation(Wkstation*	pWkstation,	char*	pDataBuffer);
// 	CString		Wkstation_Operation(int nFlag, Wkstation*	pWkstation);
// 	int			GetColumnList(CStringArray&	ColumnList);
// 	CString		GetGlobalInfo();
// 	int			LoadGlobalSet(GlobalSet*	pGlobalSet, char*	pDataBuffer);
// 	CString		SetGlobalInfo(GlobalSet*	pGlobalSet);
// 	int			Remote_GetPhysicsDiskList(CStringArray&	PhysicsDiskList, ServerDiskListIp*	pServerIp);
// 	int			GetPhysicsDiskList(CStringArray&	PhysicsDiskList, physicalDiskRequest*	pServerIp);
// 
// 	int			Remote_GetPartitionDiskList(CStringArray&	PartitionDiskList, ServerDiskListIp*	pServerIp);
// 	int			GetPartitionDiskList(CStringArray&	PartitionDiskList, partitionRequest*	pServerIp);
// 
// 	int			Remote_GetImgDiskList(CStringArray&	ImgDiskList, ServerDiskListIp*	pServerIp);
// 	int			GetImgDiskList(CStringArray&	ImgDiskList, Img*	pServerIp);
// 
// 	int			Remote_GetFixDiskList(CStringArray&	FixDiskList, ServerDiskListIp*	pServerIp);
// 	int			GetFixDiskList(CStringArray&	FixDiskList, FixParameter*	pParameter);
// 
// 	int			Remote_GetUploadFixDiskList(CStringArray&	UploadFixDiskList, ServerDiskListIp*	pServerIp);
// 	int			GetUploadFixDiskList(CStringArray&	UploadFixDiskList, ServerDiskListIp*	pServerIp);
// 
// 	int			Remote_GetUdoResponseList(CStringArray&	UdoResponseList,ServerDiskListIp*	pServerIp);
// 	int			GetUdoResponseList(CStringArray&	UdoResponseList,UdoParameter*	pParameter);
// 
// 	int			LoadDiskSet(char*	pDataBuffer,DiskSetEx*	pDiskSet);
// 	CString		DiskSet_Operation(int nFlag,DiskSetEx*	pDiskSet);
// 	int			GetAdaptMenuSet(CStringArray&	AdaptMenuSetList);
// 	int			LoadAdaptMenuSet(AdaptMenuSet*	pAdaptMenuSet,char*	pDataBuffer);
// 	CString		AdaptMenuSet_Operation(int nFlag,AdaptMenuSet*	pAdaptMenuSet);
// 	int			GetDisksetNameList(CStringArray&	StrDisksetNameList);
// 	int			GetServerIoIp(CStringArray&	ServerIoList);
// 	CString		ServerIo_Operation(int nFlag, ServerDiskListIp*	ServerIp);
// 	int			GetIpBtServerDiskList(CStringArray&		DiskList,DisksetByServerIp*	pServerIp);
// 	CString		CreateNewImg_Operation(CreateNewImg*	pCreateNewImg);
// 	CString		AccImg_Operation(AccImg*	pAccImg);
// 	CString		DirectUpdate_Operation(DirectUpdate*	pDirectUpdate);
// 	CString		BackupUpdate_Operation(BackupUpdate*	pBackupUpdate);
// 	CString		RestoreDisk_Operation(RestoreDisk*		pRestoreDisk);
// 	CString		SyncDisk_Operation(SyncDisk*	pSyncDisk);
// 	CString		GenerateNewDiskS_Operation(GenerateNewDiskS*	pGenerateNewDiskS);
// 	CString		GetRegStatus();
// 	int			GetRegDiskIdList(CStringArray&	DiskIdList);
// 	CString		UserRegLogin(MZDRegister*	pRegInfo);
// 	CString		GetCurrentDiskTask(IoServer*	pIoServer);
// 	int			LoadDiskTask(tagTask*	pDiskTask,	char*	pDataBuffer);
// 	CString		DiskTask_Operation(tagTask*	pDiskTask);
// 
// 	int 		GetWkstationEx(CStringArray&	WksArray);
// 	int			LoadWkstationEx(tagWkstationEx*	pWksation, char*	pBuffer);
// 	CString		WksationEx_Operation(int nFlags, tagWkstationEx*	pWksEx);
// 	CString		WksationEx_Add(tagAddWksInfo*	pAddWks);
// 
// 	int			GetServerSetList(CStringArray&	ServerSetLsit);
// 	int			LoadServerInfo(tagServerCfg*	pServerInfo, char*	pBuffer);
// 	CString		ServerSet_Operation(int nFlags, tagServerCfg*	pServerSet);
// 	int			GetDiskSetEx(GetDisksetByServerName*	pDiskName, CStringArray&	DiskList);
// 	int			GetServerAdaptList(CStringArray&	ServerAdaptList);
// 	int			GetTaskList(SerIp*	pServerIp, CStringArray&	TaskList);
// 	CString		GetImgSize(tagGetImgDiskSize* pImgInfo);
// 	int			GetAllPacket(CStringArray&	PacketList);
// 	int			Mzd_Message(int iRequestFlag, char*	pDataBuffer,CString&	StrResult);
// private:
// 	CString		m_MzdServerIpAddress;
// 	UINT		m_MzdServerPort;
// 	CCriticalSectionLock	m_Lock;

	BOOL		Init();
	
	int			Mzd_GetGlobal(CString&	strResult);
	int			Mzd_SetGlobal(CString	strJson,	CString&	strResult);
	int			Mzd_GetSvrCfg(CString&	strResult);
	int			Mzd_ModSvrCfg(CString	strJson,	CString&	strResult);
	int			Mzd_AddSvrCfg(CString	strJson,	CString&	strResult);
	int			Mzd_DelSvrCfg(CString	strJson,	CString&	strResult);
	int			Mzd_GetDiskList(CString	strJson,	CString&	strResult);
	int			Mzd_GetDiskNameList(CString&	strResult);
	int			Mzd_ModifyDiskCfg(CString	strJson,	CString&	strResult);
	int			Mzd_DelDiskCfg(CString	strJson,	CString&	strResult);
	int			Mzd_AddDiskCfg(CString	strJson,	CString&	strResult);
	int			Mzd_GetWksCfg(CString&	strResult);
	int			Mzd_ModWksCfg(CString	strJson,	CString&	strResult);
	int			Mzd_ModWksCount(CString	strJson,	CString&	strResult);
	int			Mzd_DelWksCfg(CString	strJson,	CString&	strResult);
	int			Mzd_AddWksCfg(CString	strJson,	CString&	strResult);
	int			Mzd_Register(CString	strJson,	CString&	strResult);
	int			Mzd_GetAdaptMenu(CString&	strResult);
	int			Mzd_GetPhysicalDiskId(CString&	strResult);
	int			Mzd_GetServerAdaptName(CString&	strResult);
	int			Mzd_GetImgPartitionPhysical(CString	strJson,	CString&	strResult);
	int			Mzd_GetFix(CString	strJson,	CString&	strResult);
	int			Mzd_GetUdo(CString	strJson,	CString&	strResult);
	int			Mzd_DoDiskMaitainTask(CString	strJson,	CString&	strResult);
	int			Mzd_GetDiskMaitainTaskList(CString	strJson,	CString&	strResult);
	int			Mzd_WksCmd(CString	strJson,	CString&	strResult);
	int			Mzd_GetSrvAdpName(CString&	strResult);
	int			Mzd_GetServiceStatus(CString&	strResult);
	int			Mzd_CheckWorkDir(CString	strJson,	CString&	strResult);
	int			Mzd_ServerCmd(CString	strJson,	CString&	strResult);
	int			Mzd_GetMZRegInfo(CString&	strResult);
	int			Mzd_GetDiskSetCfgEx(CString	strJson,	CString&	strResult);
	int			Mzd_GetCacheInfo(CString	strJson,	CString&	strResult);
	int			Mzd_ModifyWksMac(CString	strJson,	CString&	strResult);

	int			GetMzdApiCallAddress();
	int 		GetMzdFreeAddress();
public:
	CJsonEx		m_JsonEx;
private:
	string GetQueryString(string wksNumber);
};