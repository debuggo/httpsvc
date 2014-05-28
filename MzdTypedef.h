#pragma once
#include "MZD_INI.h"

#pragma pack(push)//�������״̬
#pragma pack(1)//�������״̬

#define MZD_MAX_WKS_NUMBER_LENGTH 4   //����վ���ֱ�ų���
#define MZD_DISPLAYNAME_LENGTH 32 //��ʾ���Ƴ���
#define MZD_BACKUP_ADAPT_NAME_LENGTH (32*2) //���÷�������������
#define MZD_UNDODIR_LENGTH 64 //undo·������
#define MZD_SERVER_NAME_LENGTH 32 //����������,����
#define MZD_DISKSET_NAME_LENGTH 32
#define MZD_WORKDIR_LENGTH 32
#define MZD_COMPOSE_NAME_LENGTH (3*MZD_SERVER_NAME_LENGTH) //������Ƴ���
#define MZD_SRCRES_LENGTH 20 //�ֱ��ʳ���
#define MZD_PRE_AFX_NAME_LENGTH 20 //ǰ��׺����
#define MZD_GROUP_NAME_LENGTH 32 //���鳤��

#define MZD_GET_WKS_MSG 1//��ȡ���й���վ
#define MZD_ADD_WKS_MSG 2//��ӹ���վ
#define MZD_MODIFY_WKS_MSG 3//�޸Ĺ���վ
#define MZD_DEL_WKS_MSG 4//ɾ������վ
#define MZD_WKS_CMD_MSG 5// ����վ����
#define MZD_ADD_DISK_MSG 6//��Ӵ�������
#define MZD_MODIFY_DISK_MSG 7//�޸Ĵ�������
#define MZD_DEL_DISK_MSG 8//ɾ����������
#define MZD_GET_MENU_MSG 9//��ȡ�˵�����
#define MZD_GET_GLOBAL_SET_MSG 13//��ȡȫ������
#define MZD_SET_GLOBAL_SET_MSG 14//�޸�ȫ������
#define MZD_GET_INI_MSG 15//��ȡINI//������������ΪINI���ݣ�����Ҫ�ṹ
#define MZD_GET_LOG_MSG 16//��ȡ��־//	������������Ϊ��־���ݣ�����Ҫ�ṹ
#define MZD_GET_FIX_LIST_MSG 18//��ȡFIX�б�
#define MZD_GET_UPLOAD_FIX_LISG_MSG 19//��ȡ���ϴ�FIX�б�
#define MZD_GET_UDO_LISG_MSG 20//��ȡUDO�б�
#define MZD_DISK_FORMAT_CHANGE_MSG 23//IMG����ʽת��
#define MZD_DISK_FORMAT_CHANGE_CHECK_MSG 24//IMG����ʽת����֤
#define MZD_GET_MZD_LIST_MSG 25//��ȡMZD�ļ��б�
#define MZD_GET_DISK_NAMELIST_MSG 26//��ȡ�����б�����
#define MZD_GET_PHYSICALDISKID_MSG 27//��ȡӲ�����к�
#define MZD_REGISTER_MSG 28 //ע������ 
#define MZD_DISK_MAITAIN_MSG 31 //����ά������
#define MZD_GET_UPDATE_FILE_MSG 32 //��ȡ�������°汾//SOCKET���������ͷ
#define MZD_ADD_SERVER_MSG 33 //��ӷ���������(�°���Ϣ)
#define MZD_MODIFY_SERVER_MSG 34 //�޸ķ���������(�°���Ϣ)
#define MZD_DEL_SERVER_MSG 35  //ɾ������������(�°���Ϣ)
#define MZD_GET_SERVER_LIST_MSG 36//��ȡ���з���������(�°���Ϣ)
#define MZD_GET_IMG_DISK_SIZE_MSG 37 //��ȡIMG�����̴�С
#define MZD_GET_DISKSET_BYSERVERNAME_MSG 38//��ȡָ������������������
#define MZD_GET_ALL_SERVER_ADAPT_MSG 39 //��ȡ���з����������п���������
#define MZD_GET_SERVER_TASK_LIST_MSG 40 //���ݷ���������ȡ�÷����������б�
#define MZD_GET_IMG_PARTITION_PHYSICAL_MSG 41 //��ȡIMG��,����,������
#define MZD_MODIFY_WKS_LIST_MSG 42//�����޸Ĺ���վ
#define MZD_GET_SERVICE_STATUS_MSG 43 //��ȡ����״̬
#define MZD_GET_SERVER_WORKDIR_MSG 44 //��ȡ����������Ŀ¼״̬
#define MZD_SERVER_CMD_MSG 45 //�������������
#define MZD_GET_GET_SERVER_INFO_MSG 46 //��ȡ��������Ϣ����
#define MZD_GET_MZ_REG_MSG 47 //��ȡ�÷�����ע����Ϣ
#define MZD_GET_DISKSET_BYSERVERNAME_MSG_EX 48//��ȡָ������������������
#define MZD_GET_CACHE_INFO_MSG 49  //��ȡ������Ϣ
#define MZD_MODIFY_WKS_MAC_MSG 50//�޸Ĺ���վMAC��ַ
#define MZD_GET_CACHE_REG_INFO_MSG 51//��ȡ�����ע����Ϣ
#define MZD_SET_CACHE_MSG 52 //���û���
#define MZD_REMOVE_CACHE_MSG 53 //ȡ������
#define MZD_REMOVE_CACHE_EX_MSG 54 //ȡ������,���ǲ�ɾ������,�´�����ʱ����Ч
#define MZD_CHANGE_WKS_NUMBER_MSG 55 //��������վ���
#define MZD_GET_WKS_BY_WKSNUM_MSG 56 //��ȡָ������վ����Ϣ

enum MzdTaskType
{
	Mzd_New_Img_Type = 0,
	Mzd_Acc_Img_Type,
	Mzd_Direct_Update_Type,
	Mzd_Backup_Update_Type,
	Mzd_Restore_Disk_Type,
	Mzd_Sync_Disk_Type,
	Mzd_Generate_New_Disk_Type,
	Mzd_Sync_Disk_Remote_Img_Type,
	Mzd_Change_format_Type,
	Mzd_Img_Check_Type
};

enum WKS_CMD_TYPE
{
	WKS_SHUTDOWN_TYPE = 0,//�رչ���վ
	WKS_RESTART_TYPE,//��������վ
	WKS_WAKEUP_TYPE,//���ѹ���վ
	WKS_FORBIDDEN_TYPE,//���ù���վ
	WKS_REUSE_TYPE,//���ù���վ
};

enum tagMzdResult
{
	MZD_SUCCESS = 0,//�ɹ�
	MZD_MODIFY_NAME_FAILED =1,//�޸ĳɹ����������޸�ʧ��
	MZD_ADD_FAILED_REASON_EXIST = 2,//���ʧ�ܣ����ڸ�����,��Ŵ��ڻ�MAC����
	MZD_CFG_NOT_EXIST_ERROR = 3,//�����ڸ�����
	MZD_SERVER_NOT_EXIST_ERROR = 4,//���������ò�����
	MZD_DISKNAME_IMGPATH_ERROR = 5,//��������IMG��·������
	MZD_DISKSET_IS_IN_USE_ERROR = 6,//��������,��������������ʹ���У�����ɾ��
	MZD_GET_REMOTE_IMG_SECTOR_ERROR = 7,//��ȡԶ��������ʧ��
	MZD_NETWORK_ERROR = 8,//�������
	MZD_FORBIDDEN_ERROR = 9,//��ֹ����
	MZD_WKS_CFG_EXIST_ERROR = 10,//����վ����,��ʾ�Ƿ�ɾ��
	MZD_MODIFY_NAME_EXIST_ERROR = 11,//�޸����ƴ���,���ܽ����޸�Ϊ������
	MZD_PASSWORD_ERROR = 12,//ͨѶ�������
	MZD_ILLEGAL_CONNECT_ERROR = 13,//�Ƿ�����
	MZD_MODIFY_GLOBAL_SUPERWKS_ERROR = 14,//�޸�ȫ���������޸ĳ���ʧ�ܣ�ԭ���ܹ���վ���ߣ���Ҫ�����ó��ܹ���վ
	MZD_IP_CLASH_ERROR = 15,//IP��ַ���������õ�IP��ͻ
	MZD_MAC_CLASH_ERROR = 16,//����ʧ��,MAC��ַ��ͻ
	MZD_NUMBER_CLASH_ERROR = 17,//����ʧ��,��ų�ͻ
	MZD_SERVERNAME_ERROR = 18,//����ʧ��,���������Ƴ�ͻ
	MZD_GATEWAY_ERROR = 19,//����ʧ��,���������Ƴ�ͻ
	MZD_Res_Msg_Succeed = 40,//�����ɹ�
	MZD_Res_Msg_Succeed_Login = 41,//
	MZD_Res_Msg_Succeed_Login_KEYFILE = 42,//ȡ������KEY�ļ��ɹ�
	MZD_Res_Msg_Succeed_Verify = 43,//У��ɹ�
	MZD_Res_Msg_Succeed_ChangePCCount = 45,//���Ļ���̨���ɹ�
	MZD_Res_Msg_fail_Interval = 51,//= '(51)ȡ����̫��';
	MZD_Res_Msg_fail_HD_UnReg = 52,//= 'Ӳ�̺�δע��';
	MZD_Res_Msg_fail_IPError = 53,//= '(53)ע��IP����';
	MZD_Res_Msg_fail_PassErr = 54,//= '(54)�û��������';
	MZD_Res_Msg_fail_TimeOut = 55,//= '(55)ʹ�������ѹ�';         
	MZD_Res_Msg_fail_Active = 56,//= '(56)�û�������ʹ��';
	MZD_Res_Msg_fail_VerOld = 57,//= '(57)����°汾';
	MZD_Res_Msg_fail_VerDisable = 58,//= '(58)�˰汾������ʹ��';
	MZD_Res_Msg_fail_BindClinet = 59,//    = '(59)�󶨿ͻ�����Ҫ���߰汾';
	MZD_Res_Msg_fail_DEMO = 60,//= 'DEMO��';
	MZD_Res_Msg_fail_NetErr = 61,//= '(61)�������';
	MZD_Res_Msg_fail_AgentNOFail = 62,//= '�����´����̱���'; 
	MZD_Res_Msg_fail_Verify = 63,//= 'У��ʧ��,ʱ�����';
	MZD_Res_Msg_fail_Unknown = 64,// = 'δ֪����';
	MZD_Res_Msg_fail_SmsCode = 65,//��������֤����
	Res_Msg_fail_MobileInvalid = 66,//��Ч���ֻ���������ҵ���ֻ��������
	Res_Msg_fail_MobileBlack = 67,//�ֻ������Ǻ�����
	Res_Msg_fail_MobileProtect = 68,//Ŀ���ֻ������ڱ���������
	Res_Msg_fail_MobileFail = 69,//���Ͷ���ʧ��
	Res_Msg_fail_Login = 70,//��¼ʧ��
	Res_Msg_fail_HDExpired = 71,//Ӳ���ѹ���
	Res_Msg_fail_Save = 72,//��������ʧ��
	MZD_UNKOWN_MSG_ERROR = 73,//δ֪��Ϣ
	MZD_SERVICE_NOT_START = 74,//����δ����
};

#define MZD_CMD_PORT 10700



typedef struct _tagGlobalSet
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч

	DWORD	undoNums;	//���ԭ����
	TCHAR	wksDefPassword[20];	//13303  13187069098 
	DWORD	passwordCrc;
	TCHAR	undoDir[64];	//��ԭ�ļ�Ŀ¼
	bool	isDisableTelnet;	//Զ�̽��濪��
	bool	isDisableDebug;	//��ʽģʽ����
	bool	isShowRegFMFlag;      // for IO Server Not Show Reg FM ����IO����������ʾע�ᴰ��
	WORD	dhcpFastMode;			//dhcp����ģʽ������һ���Զ෢25��OFFER��
	BYTE	fixFormat;
	bool	isWanTonFlag;				//��¼ע����·�ǲ�����ͨ
	bool	isEnableStrap;		//MHD��ҿ���
	bool	isAutoNumber;				//�Զ����
	bool	isAutoAdd;					//�Զ���ӹ���վ
	bool	isCompulsoryNumber;			////�Զ����Ǳ��
	bool	isDisableDhcp;				//�ر�MS DHCP ����
	TCHAR	regDomainAddress[64];	//ע�����������
	TCHAR	removeIp[255];   //����DHCPʱ��Ҫ�ų���IP�б�
	DWORD	loginServerIP; //����IP
	WORD	superWks;				//��������վ���
	bool	isEnableSysDiskForSuperWks;  //��������վ�ܸĶ��Ĵ��̿���
	bool 	isEnableDataDisk1ForSuperWks;
	bool 	isEnableDataDisk2ForSuperWks;
	bool 	isEnableDataDisk3ForSuperWks;
	bool	isDhcpQuickResponse;
	bool	isAutoSyncUpdateForSuperWks;//��������վ�ػ����Զ�ͬ�����ء�
	DWORD	arDataSourceIP[64];		//IMG��ͬ������ԴIP�б�
	TCHAR	runExternal[255];		//�����ⲿ����	
	bool	isWaitCompleted;	//�ȴ������ⲿ����������ɡ�
	TCHAR	LanguagePack[255];	//���԰�
	DWORD   m_MemType;//�ڴ�ģʽ,0:��ͨ�ڴ棬1��AWE�ڴ�
	TCHAR m_WksWorkDir[255];//����վ����Ŀ¼
	TCHAR m_SsdPartition[2];//ssd�̷�
	DWORD dwFlags1; // ���ƺ����ĸ��ֶ���Ч

	bool bRestartRestore;//�����Զ��ָ�
	DWORD m_LastUpdateTime;//����޸ĵ�ʱ��
	DWORD m_LogLevel;//��־�ȼ�
	DWORD	spareServerIP; //����ע���IP
}tagGlobalSet;

typedef struct _tagGetGlobalSetEx
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	_tagGlobalSet globalset;
	TCHAR RegisterHdid[16];
	TCHAR spareRegisterHdid[16];
}tagGetGlobalSetEx;


typedef struct _tagServerCfg
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч

	TCHAR serverName[32];//����������
	DWORD adaptIp[4];//����������IP
	TCHAR backupAdaptName[4][96];//���÷�������������
	DWORD writeCacheSize;//д�����С
	DWORD systemCacheSize;//ϵͳ�̻����С
	DWORD dataCacheSize;//�����̻����С
	DWORD ssdCacheSize;//SSD�����С
	TCHAR ssdDisk[2];//SSD�̷�
	TCHAR workDir[4][32];//����·��
	TCHAR networkGameGroup[32];//��Ϸ����������
	bool bServerUseHotBackup;//�Ƿ������ȱ�
	int serverConnectStatus;//����������״̬
	int serverType;//����������
}tagServerCfg;

typedef	struct _tagServerName
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR servername[32];
}tagServerName;

typedef	struct _tagServerIp
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	DWORD serverIp[4];
}tagServerIp;

typedef	struct _tagDiskSet
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	bool	isAutoUpload;  //�ϴ���ԭ����
	bool	isAllowUpload;
	bool	isAllowRevert;
	bool	isAllowClear;
	bool	isAutoRevert;
	bool	isAutoClear;
	DWORD	readCacheSize;     // Per Disk Read Cache Size//�������С
	DWORD	writeCacheSize;    // MZD Server Write Cache Size
	BYTE	abreastSum;			//������
	int		retryTimeOut;      //�ͷ����ʧȥ����ʱ������ʱ��  ��-1 ������ʱ
	BYTE	dosReadSize,dosWriteSize; // Win 4-7 bits ,dos 0-3 bits    // -1
	BYTE	winReadSize,winWriteSize; // win 4-7 bits ,dos 0-3 bits    // -1
	short	localCacheSize;				//���ػ����ܿ���
	bool	isDelayLoad;				 //��ʱ����
	bool	isIScsiBoot;				//iSCSI��������
	TCHAR	clientWriteDir[32];		//�ͻ��˻�дĿ¼
	DWORD	diskQuota;		//�������
	DWORD	dirIp;					// Disk Img Host address
	DWORD	mirrIp;					 //���̾���IP
	DWORD	hotBakIP;
	DWORD	ssdCacheSize;				 //SSD ����
	TCHAR	ssdVolum[8];
	TCHAR	destinationFile[64];			//����Ŀ���豸
	TCHAR	arWorkDir[4][32];		//���̹���·��
	TCHAR	diskName[96];		//������������
	DWORD readCacheType;//0:��ͨ�ڴ棬1��AWE�ڴ�
	DWORD writeCacheType;//0:��ͨ�ڴ棬1��AWE�ڴ�
	TCHAR    diskDisplayName[32];//����������ʾ����
	DWORD diskType;//�������ͣ�0������ϵͳ�̣�1�����������̣�
	DWORD disksize;//���̴�С��MB��

	DWORD dwFlags1; // ���ƺ����ĸ��ֶ���Ч
	TCHAR serverName[32];
	DWORD serverIp[4];//������IP
}tagDiskSet;

typedef	struct _tagGetDisksetNameList
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR disksetname[96];
}tagGetDisksetNameList;

typedef struct _tagMenuSetEx
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR displayname[MZD_DISPLAYNAME_LENGTH];
	TCHAR diskName[4][MZD_COMPOSE_NAME_LENGTH];
	DWORD start_mode;//����ģʽ
}tagMenuSetEx;

typedef struct _tagWkstationEx
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	DWORD wksNumber;
	TCHAR  wksName[32];
	DWORD wksIp;
	TCHAR wksMac[32];
	DWORD subMask;
	DWORD gateway;
	TCHAR scrRes[20];//�ֱ���
	TCHAR groupId[32];//��������
	DWORD numberLength;//��ų���
	tagMenuSetEx menuGroup[4];
	DWORD startMode;
	DWORD LocalMemoryCache;//����վ���ػ���
	bool bStartHotBack;//�Ƿ������ȱ�
	bool bAutoRestore;//����վ�Ƿ��Զ���ԭ
	TCHAR comPre[20];//�����ǰ׺
	TCHAR comAfx[20];//�������׺
	DWORD dns1;
	DWORD dns2;
	DWORD startServerIp;//����������IP
	bool bSuperMode;
	bool bOnlineStatus;
	bool bForbidStatus;
	bool bSuperOnline;//�������߼��
}tagWkstationEx;

enum MzdErrorCmd
{
	REPORT_ERROR,//�������
	IGNORE_ONE_ERROR,//������������һ�δ���
	IGNORE_ALL_ERROR,//���������������д���
	JUMP_ONE_ERROR,//����һ�δ������
	JUMP_ALL_ERROR//�������д������
};


//����޸Ĺ���վʹ��ͬһ���ṹ��
typedef struct _tagModifyWksInfo
{
	DWORD startIp;//��ʼIP(���ʹ��)
	DWORD oldWksNumber;//ԭ����վ���(�޸�ʹ��)(��ȡ����վ��Ϣʱ��������ñ��)
	MzdErrorCmd bIgnoreError;//�������߼�
	bool bAloneWks;//�Ƿ�̨����վ(��̨���ʱ����վIPΪ�û�ָ��,������ӹ���վ��IP�Ǹ�����ʼIP�ͱ��ȷ��)
	DWORD startNumber;//��ʼ���
	DWORD endNumber;//�������
	_tagWkstationEx wks;//����վ��Ϣ
	_tagModifyWksInfo()
	{
		memset(this,0,sizeof(_tagModifyWksInfo));
	}

	/*void SetValue(MZD_INI& ini,DWORD secNum = 0)
	{
		MZD_CHAR classname[MAX_PATH];
		GETCLASSNAME(classname,MAX_PATH);
		ini.ReadIpFromINI(classname,secNum,STR(startIp),startIp,MZD_T("0.0.0.0"));
		ini.ReadFromINI(classname,secNum,STR(oldWksNumber),oldWksNumber,0);
		ini.ReadFromINI(classname,secNum,STR(bIgnoreError),(int&)bIgnoreError,0);
		ini.ReadFromINI(classname,secNum,STR(bAloneWks),bAloneWks,false);
		ini.ReadFromINI(classname,secNum,STR(startNumber),startNumber,0);
		ini.ReadFromINI(classname,secNum,STR(endNumber),endNumber,0);
		MZD_CHAR temp_sec_name[MAX_PATH];
		int temp_sec_num;
		ini.ReadFromINI(classname,secNum,STR(wks),temp_sec_name,MAX_PATH,MZD_T(""));
		MZD_INI::SpliteSecName(temp_sec_name,temp_sec_num);
		wks.SetValue(ini,temp_sec_num);
	}

	DWORD Write2INI(MZD_INI& ini,MZD_CHAR* pOutClassName = NULL,DWORD max_length = 0)
	{
		MZD_CHAR classname[MAX_PATH];
		GETCLASSNAME(classname,MAX_PATH);
		DWORD sec_num = ini.CreateSecNumber(classname);
		ini.WriteIp2INI(classname,sec_num,STR(startIp),startIp);
		ini.Write2INI(classname,sec_num,STR(oldWksNumber),oldWksNumber);
		ini.Write2INI(classname,sec_num,STR(bIgnoreError),bIgnoreError);
		ini.Write2INI(classname,sec_num,STR(bAloneWks),bAloneWks);
		ini.Write2INI(classname,sec_num,STR(startNumber),startNumber);
		ini.Write2INI(classname,sec_num,STR(endNumber),endNumber);
		MZD_CHAR temp_sec_name[MAX_PATH];
		int temp_sec_num = wks.Write2INI(ini,temp_sec_name,MAX_PATH);
		ini.Write2INI(classname,sec_num,STR(wks),temp_sec_name);
		if (pOutClassName)
		{
			MZD_INI::GetSectionName(classname,sec_num,pOutClassName,max_length);
		}
		return sec_num;
	}*/
}tagModifyWksInfo,tagAddWksInfo,tagAddWksInfoUI,_tagAddWksInfoUI,tagModifyWksInfoUI,_tagModifyWksInfoUI,tagGetWksInfo,tagGetWksInfoUI;

//typedef struct _tagModifyWksInfo
//{
//	//DWORD cbSize; // �ṹ�ܵĴ�С
//	//DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
//	DWORD startIp;//��ʼIP(���ʹ��)
//	DWORD oldWksNumber;//ԭ����վ���(�޸�ʹ��)
//	int	  nIgnoreError;//�����־λ
//	bool bAloneWks;//�Ƿ�̨����վ(��̨���ʱ����վIPΪ�û�ָ��,������ӹ���վ��IP�Ǹ�����ʼIP�ͱ��ȷ��)
//	DWORD startNumber;//��ʼ���
//	DWORD endNumber;//�������
//	_tagWkstationEx wks;//����վ��Ϣ
//	_tagModifyWksInfo()
//	{
//		memset(this,0,sizeof(_tagModifyWksInfo));
//		cbSize = sizeof(_tagModifyWksInfo);
//		dwFlags = 0x0F;
//	}
//}tagModifyWksInfo,tagAddWksInfo;
//

typedef struct _tagModifyServer
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR oldservername[32];//ԭ��������������(�޸�ʱʹ��)
	int   bIgnoreError;//ֱ�Ӳ���,���Դ���
	tagServerCfg servercfg;//�޸ĺ�ķ���������
}tagModifyServer,tagAddServer;

typedef	struct _tagImgResponse
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR imgpath[260];
	DWORD imgsectornums;
	DWORD freeimgsectornums;//ʣ��������(ֻ���ڷ������������ʱֵ����Ч)
}tagImgResponse;

typedef	struct _tagGetFixListRequest
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR servername[32];
	TCHAR imgpath[260];
}tagGetFixListRequest;

typedef	struct _tagFixResponse
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR fixpath[260];
}tagFixResponse;

typedef	struct _tagGetUdoListRequest
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR servername[32];
	TCHAR imgpath[260];
}tagGetUdoListRequest;

typedef	struct _tagUdoResponse
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR fixpath[260];
}tagUdoResponse;

typedef struct _tagTask
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	DWORD taskId;
	DWORD taskPercent;
	int	 taskType;
	TCHAR servername[32];
	TCHAR syncservername[32];
	TCHAR imgPath[64];
	DWORD imgSize;
	TCHAR fixudoPath[64];
	TCHAR newimgPath[64];
}tagTask;

typedef	struct _tagMZDRegister
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR diskId[256];
	TCHAR agentId[64];//�����̱��
	TCHAR password[256];//����
	DWORD lineType;//��·��0����ͨ��1������
	TCHAR smscode[8];//������֤��
	TCHAR mzdusername[20];
	TCHAR mzdpassword[32];
}tagMZDRegister;

typedef	struct _tagMenuSet
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	int		waitTime;	//����վ��������ȴ�ʱ��
	bool	isShowHostIP;	//��ʾLogin������IP����
	bool	isVipLogon;
	TCHAR	adapterSet[20];	//����������������
	TCHAR	wksArea[255];        //255 MAX STRING ����վ����б�
	DWORD	gateway;
	int		numberLength;	//��ų���
	BYTE	bootOrd;	//����˳��
	BYTE	bootOrd1;
	BYTE	bootOrd2;
	DWORD	dns1;			//DNS
	DWORD	dns2;			//DNS
	TCHAR	arDiskItems[4][32];	//��ǰ���õĴ���
	TCHAR	comPre[20];	//�������ǰ׺
	TCHAR	comAfx[20];	//���������׺
	int		startNumber;				//���������ʼ���
	TCHAR	workGroup[20];	//������
	TCHAR	scrRes[20];	//����վ����Ļ�ֱ���
	TCHAR	gatewayMAC[20];		//����MAC
	DWORD	coverDirIp;               // Disk Img Host address
	DWORD	coverMirrIp;              //���̾���IP
	DWORD	coverHotBakIP;
	DWORD m_WksMemory;//����վ�ڴ滺��
	BYTE  m_WksAutoClear;//�����Զ����
	BYTE  m_UseHotBackup;//�����ȱ�
	TCHAR	displayName[20]; //���һ��Ҫ�������  �˵�����
	TCHAR	menuName[20]; //���һ��Ҫ�������  �˵�����
}tagMenuSet;

typedef	struct _tagAdapt
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч

	TCHAR	adapterName[20];//������������
	DWORD	loginIP;		//������¼IP	
	DWORD	spareLoginIp;	//�ӷ���¼IP
	DWORD	wksStartIp;		//��ʼDHCP IP
	DWORD	wksSubMask;		//DHCP ����
	BYTE	subsectionIp;	//IP�ֶε�	
	int		dhcpCount;		//��Χ����
	DWORD gateway;//����
	DWORD dns1;
	DWORD dns2;
}tagAdapt;

typedef	struct _tagAdaptMenuSet
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	_tagMenuSet menuset;
	_tagAdapt adaptset;
}tagAdaptMenuSet;

typedef	struct _tagPhysicalDiskId
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR diskId[256];
}tagPhysicalDiskId;

typedef	struct _tagServerAdaptName
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR ServerAdapt[96];
}tagServerAdaptName;

typedef struct _tagWksCmd
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	DWORD startWksId;
	DWORD endWksId;
	int   wksCmd;
}tagWksCmd;

typedef struct _tagCheckServerWorkDir
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	DWORD serverIp[4];
	bool bWorkDirExist[4];//U,V,W,X�Ƿ����
	bool bSSDExist;//S��
}tagCheckServerWorkDir;

typedef struct _tagServerCmd
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	DWORD serverIp[4];
	int		cmdType;
}tagServerCmd;

typedef	struct _tagMZRegInfo
{
	DWORD cbSize; // �ṹ�ܵĴ�С
	DWORD dwFlags; // ���ƺ����ĸ��ֶ���Ч
	TCHAR netbarname[64];//������
	TCHAR hdid[16];//ע��Ӳ�����к�
	TCHAR sparehdid[16];//����ע��Ӳ�����к�
	TCHAR proxyname[64];//������
	SYSTEMTIME expiretime;//����ʱ��
	int   serverType;//����������
	TCHAR passport[32];//ͨ��֤
}tagMZRegInfo;

typedef struct _tagAddWksInfoError
{
	DWORD wksNumberInError;//��Ӹñ��ʱ��������
	bool bIpClash;//����������վIP��ͻ
	bool bMacClash;//����������վMAC��ͻ
	bool bNumberClash;//����������վ��ų�ͻ
	bool bServerNameClash;//����������������ͻ
	bool bServerIpClash;//������������IP��ͻ
	bool bGateWayClash;//�����س�ͻ
	DWORD wksIpInError;//��Ӹù���վIPʱ���ʹ���(��Ϊ�µ���ʼIP)
	int	 ErorrCode;  //�ӿڴ���ֵ
	_tagAddWksInfoError()
	{
		memset(this,0,sizeof(_tagAddWksInfoError));
	}
	_tagAddWksInfoError(_tagAddWksInfoError& A)
	{
		wksNumberInError = A.wksNumberInError;
		bIpClash = A.bIpClash;
		bMacClash = A.bMacClash;
		bNumberClash = A.bNumberClash;
		bServerNameClash = A.bServerNameClash;
		bGateWayClash = A.bGateWayClash;
	}
}tagAddWksInfoError;

typedef struct _tagAddServerError
{
	bool bIpClash;//����������վIP��ͻ
	bool bServerIpClash;//������������IP��ͻ
	bool bServerNameClash;//����������������ͻ
	bool bGateWayClash;//�����س�ͻ
	int	 ErorrCode;  //�ӿڴ���ֵ
	_tagAddServerError()
	{
		bIpClash = false;
		bServerIpClash = false;
		bServerNameClash = false;
		bGateWayClash = false;
	}
}tagAddServerError;

typedef struct _tagHookCache
{
	DWORD cache_size;//�����С
	DWORD rw_type;//��������(1 = д���� �����Ƕ�)
	TCHAR owner[128];//ʹ����
	INT64 total_rw_secs;//�ܶ�/д������
	INT64 hit_rw_secs;//����������
	INT64 hit_percent;//������
	INT64 rw_nums;//��д�ܴ���
	INT64 IOPS;//ÿ����ж�д��I/O�������Ĵ���
	INT64 rw_speed;//��д����
	DWORD current_time;//��ǰ���ʱ��
}tagHookCache;


typedef struct _tagCache
{
	tagHookCache	stHookCache;
	int		bSsd;	//SSD��־λ
}tagCache;
enum EWKSMODE
{
	eNormalMode, eDbgMode,    eDiagMode, eSuperMode, eGhostMode
};
#define MZD_LENGTH_4 4
#define MZD_LENGTH_8 8
#define MZD_LENGTH_16 16
#define MZD_LENGTH_20 20
#define MZD_LENGTH_32 32
#define MZD_LENGTH_64 64
#define MZD_LENGTH_96 96
#define MZD_LENGTH_128 128
#define MZD_LENGTH_255 255
#define MZD_LENGTH_256 256
//����վ
struct _tagWkstation
{
	WORD	wksNumber;  //���
	WORD	loginID;		//��½��
	DWORD	wksCmdCfg;	//�������ĵ�½����
	EWKSMODE	wksMode;
	BYTE	userType; //0:Normal 1:VIP ����վ����

	bool	isDisable;	//��ֹ����վ
	DWORD	wksIp;	//����վIP
	WORD	randKey;	//���KEY
	WORD	loginIPLow;	//��½�ķ�����IP����λ
	DWORD	userSelectCmd;//�û�ѡ������

	MZD_CHAR	strMac[MZD_LENGTH_20];	//����վ��MAC
	MZD_CHAR	comName[MZD_LENGTH_20];	//����վ�ļ������
	MZD_CHAR	currSetCfg[MZD_LENGTH_20];	//��ǰ����վʹ�õ�ϵͳ��������
	MZD_CHAR	menuName[MZD_LENGTH_20];	//��ǰ����վʹ�õĲ˵���������
	MZD_CHAR	userName[MZD_LENGTH_20];	//��½�õ��û���������վʹ�õ���MAC��VIPʹ�õ���VIP�û��� 

	MZD_CHAR	password[MZD_LENGTH_20];	//��½����
	MZD_CHAR	inputName[MZD_LENGTH_20];	//����վ��½ʱ������û���
	MZD_CHAR	inputPass[MZD_LENGTH_20];	//����վ��½ʱ���������
	MZD_CHAR	adaptname[MZD_LENGTH_20];//��ǰ��������
	DWORD	serverIp;		//����վ���ӵ�����IP

	DWORD	dhcpGateway;	//DHCP ������
	DWORD	subMask;
	WORD	clientPort;	//������̨����վ�������ػ��Ķ˿�
	int		wksMemory;

	//��ֹ��Ϊ�Ķ��������ú󣬹���վ�����Ҳ���������Ϣ
	MZD_CHAR	arDiskSetName[4][MZD_LENGTH_96];	// ���浱�ν���ϵͳ�Ĵ���������Ϣ
	MZD_CHAR	arDestinationFile[4][MZD_LENGTH_64];      //
	MZD_CHAR	arDiskWorkDir[4][MZD_LENGTH_32];
	BYTE     RestartAutoClear;//�����Զ����
	MZD_CHAR group[MZD_GROUP_NAME_LENGTH];//��������
	bool bSuperMode;
	DWORD m_LiveSendTime;//����������ʱ��
	DWORD m_LiveRecvTime;//����������ʱ��
	DWORD m_WksPhysicalMemory;//����վ�ϱ��������ڴ�(MB)
	bool bSuperOnline;//��������״̬

	MZD_CHAR menu_set[4][MZD_LENGTH_32];//�˵��ڲ���

	//_tagWkstation()
	//{
	//	memset(this,0,sizeof _tagWkstation);
	//}
	//void m_SetLoginId(WORD ID)
	//{
	//	if (ID < MAX_WORKSTATION_NUMBERS) 
	//		loginID = ID;
	//}

	////��ǰ�Ƿ�VIP�û�ʹ��
	//bool m_IsVipUsing(int cDiskIndex) const
	//{
	//	return  (cDiskIndex < 0 && inputName != strMac);  //inputName == strMac ����վ����ģʽ�����Ի�ԭ��յ�����
	//}

	////���ù���վ���ͣ�VIP ����վ
	//bool m_IsVipUser() const
	//{
	//	return  (userType > 0);  
	//}

	//bool m_IsSuperWks(const MZD_CHAR* pszDiskName, byte byIndex)
	//{
	//	return false;
	//}

	//void CreateComName(DWORD wksLength,MZD_CHAR* comPre,MZD_CHAR* comAfx)
	//{
	//	//��������ĳ������Ϊ16�ֽ�
	//	if (MZD_STRCMP(comPre,MZD_INVALIDE_PRE) == 0)
	//	{
	//		//��Ч��ǰ׺,ֻ��Ҫȡ��׺������
	//		if (MZD_STRLEN(comAfx) > 16 - 1)
	//		{
	//			MZD_MEMCPY(comName,comAfx,16 - 1);
	//			comName[16 - 1] = '\0';
	//		}else
	//		{
	//			MZD_STRCPY(comName,comAfx);
	//		}
	//	}else
	//	{
	//		MZD_CHAR strComName[64];
	//		MZD_CHAR strNumber[32];
	//		MZD_CHAR strComPre[20];
	//		MZD_CHAR strComAfx[20];
	//		if (wksLength > 4)
	//		{
	//			wksLength = 4;
	//		}

	//		MZD_MEMCPY(strComPre,comPre,20);
	//		MZD_MEMCPY(strComAfx,comAfx,20);
	//		MZD_SPRINTF_S(strNumber,MZD_T("%d"),wksNumber);
	//		while(MZD_STRLEN(strNumber) < wksLength)
	//		{
	//			MZD_SPRINTF(strComName,MZD_T("0%s"),strNumber);
	//			MZD_STRCPY(strNumber,strComName);
	//		}

	//		//��̬��������������,(����=ǰ׺+wkslength+ ��׺) < 16 - 1
	//		DWORD prelength = MZD_STRLEN(strComPre);
	//		DWORD afxlength = MZD_STRLEN(strComAfx);

	//		if (prelength > 16  - wksLength - 1)
	//		{
	//			prelength = 16 - wksLength - 1;
	//			strComPre[prelength] = '\0';
	//		}

	//		if (prelength + wksLength + 1 < 16)
	//		{
	//			afxlength = 16 - 1 - wksLength - prelength;
	//		}else
	//		{
	//			afxlength = 0;
	//		}
	//		strComAfx[afxlength] = '\0';

	//		MZD_SPRINTF_S(strComName,MZD_T("%s%s%s"),strComPre,strNumber,strComAfx);
	//		MZD_STRCPY(comName,strComName);
	//	}
	//}
};


#pragma pack(pop)



typedef int (*MzdAgentInit)(TCHAR* pIp,short port,TCHAR* pPassword);
typedef void (*MzdAgentFree)(void*);
typedef int (*GetGlobal)(tagGetGlobalSetEx* pCfg);
typedef int (*ModifyGlobal)(_tagGlobalSet* pCfg);
typedef int (*GetServerCfg)(DWORD& nums,_tagServerCfg** pServerList);
typedef int (*ModifyServerCfg)(tagModifyServer* pCfg, tagAddServerError& error);
typedef int (*AddServerCfg)(tagAddServer* pCfg, tagAddServerError& error);
typedef int (*DelServerCfg)(_tagServerCfg* pCfg);
typedef int (*GetDiskSetCfg)(_tagServerName* pServerName,DWORD&,_tagDiskSet**);
typedef int (*GetDiskSetNameList)(DWORD&,_tagGetDisksetNameList**);
typedef int (*ModifyDiskSetCfg)(_tagDiskSet* pCfg);
typedef int (*DelDiskSetCfg)(_tagDiskSet* pCfg);
typedef int (*AddDiskSetCfg)(_tagDiskSet* pCfg);
typedef int (*GetWksCfg)(DWORD&,_tagWkstationEx**);
typedef int (*ModifyWksCfg)(tagModifyWksInfo* pCfg, tagAddWksInfoError& error);
typedef int (*AddWksCfg)(tagAddWksInfo* pCfg, tagAddWksInfoError& error);
typedef int (*ModifyWksCfgList)(tagAddWksInfo*);
typedef int (*DelWksCfg)(DWORD delNums,DWORD* wksList);
typedef int (*GetImgPartitionPhysical)(tagServerIp* pServerIp,DWORD&,_tagImgResponse**);
typedef int (*GetFix)(_tagGetFixListRequest* pServerName,DWORD&,_tagFixResponse**);
typedef int (*GetUdo)(_tagGetUdoListRequest* pServerName,DWORD&,_tagUdoResponse**);
typedef int (*DoDiskMaitainTask)(tagTask*);
typedef int (*GetDiskMaitainTaskList)(tagServerIp* pServerIp,DWORD&,tagTask**);
typedef int (*StartRegister)(_tagMZDRegister*);
typedef int (*GetAdaptMenuCfg)(DWORD&,_tagAdaptMenuSet**);
typedef int (*GetPhysicalDiskId)(DWORD&,_tagPhysicalDiskId**);
typedef int (*GetServerAdaptName)(DWORD& nums,_tagServerAdaptName** pList);
typedef	int (*WksCmd)(tagWksCmd*);
typedef	int (*GetServiceStatus)(int*);
typedef	int	(*CheckServerWorkDir)(tagCheckServerWorkDir*);
typedef	int (*ServerCmd)(tagServerCmd* pCmd);
typedef	int (*GetMZRegInfo)(_tagMZRegInfo* pReg);
typedef int (*GetDiskSetCfgEx)(TCHAR* pServerName,bool bGetImgSize,DWORD& nums,_tagDiskSet** pList);
typedef	int (*GetCacheInfo)(_tagServerIp* pIp,DWORD& mem_nums,tagHookCache** p_mem_list,DWORD& ssd_nums,tagHookCache** p_ssd_list);
typedef int (*ModifyWksMac)(tagModifyWksInfo*);



typedef void (*FreeMZD_INI)(char* pINIBuf);
typedef int (*DoCmd2MZDIO)(DWORD cmd,const char* pINI,char** ppOutBuf);

#define MZD_INVALIDE_PRE MZD_T("_MZD_INVALID_MZD_")