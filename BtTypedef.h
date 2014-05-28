#if !defined COMMUNICATION_H
#define COMMUNICATION_H
//----------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------����-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------
const		DWORD	SCMD_OK					=	70000;	//UI����ָ��سɹ�
const		WORD	SU_SOCKET_HEAD_VALUE	=	1978;	//����(Service)���û�����(UI)ͨѶ��ͷֵ
const		WORD	CS_SOCKET_HEAD_VALUE	=	2012;	//����������ͨѶ��ͷֵ
//----------��Դ״ֵ̬����
//const		int		RS_FLAG_INVALID			=  -3;		//��Ч����(δ����)	***
const		int		RS_FLAG_MANUAL_DELETE	=  -2;		//��ɾ��(�ֶ�)
const		int		RS_FLAG_AUTO_DELETED	=  -1;		//��ɾ��(�Զ�)
const		int		RS_FLAG_UNDOWNLOAD		=	0;		//δ����
const		int		RS_FLAG_HAVEUPDATE		=	1;		//�и���
const		int		RS_FLAG_FINISHED		=	2;		//����ɸ���


//----------��Դ��ǰ����״̬	
//��λ
const		int		RSWS_NONE				=	0x00;	// û�й���״̬			
const		int		RSWS_ACTIVING			=	0x01;	// ���
const		int		RSWS_ACTIVE_SUPPLY_SEED	=	0x02;	// ���(������)
const		int		RSWS_MOVE_DIRECTORY		=	0x04;	// �����ƶ�Ŀ¼��
const		int		RSWS_DELETE_DIRECTORY	=	0x08;	// ����ɾ��Ŀ¼��
const		int		RSWS_REPLACE_PIECE_DATA	=	0x10;	// ������ʱĿ¼���ݵ�ԴĿ¼
//��λ
const		int		RSWS_INVALID_DATA		=	0x10000;// ��Ч����(�޷��ṩ����)
const		int		RSWS_UNKNOW				=	0x20000;// δ֪״̬
//----------�Ǻ�������ǰ����״̬
const		int		NONCORE_TASK_STATUS_NONE			=0;						//��
const		int		NONCORE_TASK_STATUS_DOWNLOAD_FILE	=1;						//�����ļ�
const		int		NONCORE_TASK_STATUS_CREATE_IDX		=2;						//��������
const		int		NONCORE_TASK_ERROR					=3;						//����

//��Դ��������첽״̬
enum _rtAsynState
{
	rtAsynStateNone = 0,								// û���첽״̬

	//	rtAsynStateWaitFileDownload,						// �Ŷӵȴ������ļ�
	//	rtAsynStateWaitCreateIdxFile,						// �Ŷӵȴ���������
	rtAsynStateWaitClearRedundant,						// �Ŷӵȴ���������ļ�Ŀ¼
	rtAsynStateWaitMoveDirectory,						// �Ŷӵȴ��ƶ�Ŀ¼
	rtAsynStateWaitDeleteDirectory,						// �Ŷӵȴ�ɾ��Ŀ¼
	rtAsynStateWaitReplacePieceData,					// �Ŷӵȴ�����Ŀ¼�������� (��״̬������rtAsynStateClearRedundant״̬)

	rtAsynStateFileDownload,							// �����ļ�
	rtAsynStateCreateIdxFile,							// ��������
	rtAsynStateClearRedundant,							// ��������ļ�Ŀ¼
	rtAsynStateMoveDirectory,							// �ƶ�Ŀ¼
	rtAsynStateDeleteDirectory,							// ɾ��Ŀ¼
	rtAsynStateReplacePieceData,						// ����Ŀ¼�������� (��״̬������rtAsynStateClearRedundant״̬)
	//rtAsynStateRepair,									// �޸�(�������Ҫ���£���ı�״̬ΪrtAsynStateWaitClearRedundant�ȴ���������ļ�)		
};
/*
//��ʱ����Ŀ¼״̬
enum _taskCacheDirectoryState
{
tsCacheDirNone = 0,									//δʹ����ʱĿ¼
tsCacheDirNoneCheck,								
tsCacheDirNoneContrast,
tsCacheDirCheck,									//��ʹ��ԭʼĿ¼У���ļ�
tsCacheDirContrast,									//��ʹ��idx�ļ��Ա�
tsCacheDirDownloading,								//������ʱ����Ŀ¼������
//	tsCacheDirWaitReplace,								//����Ŀ¼������ɣ��ȴ������л�
//	tsCacheDirReplacing,								//����Ŀ¼�����л�����
};*/
//��ǰ����ʹ�õ�Ŀ¼����
enum _taskUseDirectoryType
{
	tsUseDirTypeOriginal = 0,
	tsUseDirTypeCache,
};
//��ǰ����Ŀ¼��״̬
enum _taskDirectoryState
{
	tsDirStateNone = 0,
	tsDirStateInitCheck,
	tsDirStateInitContrast,
	tsDirStateDownloading,
};

//�����Զ�״̬
enum _taskAutoState
{
	tsAutoStateWait = 0,								//�������Ŷӵȴ���(�Զ�ֹͣ)
	tsAutoStateWaitChecked,								//���ڴ��ڵȴ�������
	tsAutoStateActive,									//�����ڻ״̬
	tsAutoStateManualStop,								//�������ֶ�ֹͣ״̬
};
//----------��Դ��չ����
const		int		RSET_NONE				=	0x00;	// ������
const		int		RSET_STOP_UPDATE		=	0x01;	// ��ֹ֧ͣ�ָ���
const		int		RSET_FORCE_PROMOTE		=	0x02;	// ǿ���ƹ�����
const		int		RSET_FORCE_CHANGE		=	0x04;	// ǿ���޸�����
const		int		RSET_FORCE_DELETE		=	0x08;	// ǿ��ɾ������

enum _resExType
{
	resExTypeNone = 0,
	resExTypeStopSupport,
	resExTypePromote,
	resExTypeChange,
	resExTypeDelete,
};
//��������ֵ����
enum _taskType
{
	tsTypeNone = 0,										//�ǻ����
	tsTypeNonCore,										//�Ǻ��Ļ����
	tsTypeCore,											//���Ļ����
};
//�����Ѵ����Ĺ���״̬
enum _taskTrigger
{
	tsTriggerNone =	0,									//���κδ���
	tsTriggerDownload,									//���ر�����
	tsTriggerFinished,									//������ɱ�����
};
//----------�����ʼ��״ֵ̬����
const		UINT	SRV_WS_INITIAL			=	0;
const		UINT	SRV_WS_INITIALED		=	1;
const		UINT	SRVIS_FINISHED			=	100;

enum _srvInitState
{
	srvInitStateNone = 0,
	srvInitStateFinished,
};
//----------�û�ע��״ֵ̬����
const		UINT	USER_STATUS_UNKNOWN		=	0;		//δ֪�û�
const		UINT	USER_STATUS_FREE		=	1;		//����û�
const		UINT	USER_STATUS_VIP			=	2;		//VIP�û�

enum _regUserState
{
	regUserStateUnknow = 0,
	regUserStateFree,
	regUserStateVIP,
};
//----------BT�ṹ�е�Flagsֵ
const		DWORD	BTS_FLAGS_32[33]		=   {0x00000000,
0x00000001,0x00000003,0x00000007,0x0000000F,
0x0000001F,0x0000003F,0x0000007F,0x000000FF,
0x000001FF,0x000003FF,0x000007FF,0x00000FFF,
0x00001FFF,0x00003FFF,0x00007FFF,0x0000FFFF,
0x0001FFFF,0x0003FFFF,0x0007FFFF,0x000FFFFF,
0x001FFFFF,0x003FFFFF,0x007FFFFF,0x00FFFFFF,
0x01FFFFFF,0x03FFFFFF,0x07FFFFFF,0x0FFFFFFF,
0x1FFFFFFF,0x3FFFFFFF,0x7FFFFFFF,0xFFFFFFFF};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------�������ָ��-----------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------
//----------ϵͳָ��
#define		COMMAND_CONNECT_SERV				100		//����BT����						//
#define		COMMAND_UI_LOGIN					101		//UI��¼							//
#define		COMMAND_GET_LOGIN_INFO				102		//��ȡUI��¼��Ϣ					//
#define		COMMAND_SET_PASSWORD				103		//������������						//
#define		COMMAND_SYNC_DATA					106		//ͬ������							//
#define		COMMAND_GET_SYNC_PROGRESS			107		//��ȡͬ������
#define		COMMAND_GET_SERV_WORK_STATUS		270		//��ȡBT������״̬				//
#define		COMMAND_GET_LOG_INFO				119		//��ȡ��־��Ϣ
#define		COMMAND_GET_BT_CONFIG				104		//��ȡBT������Ϣ					//
#define		COMMAND_SET_BT_CONFIG				105		//����BT������Ϣ					//
#define		COMMAND_GET_MENU_CONFIG				113		//��ȡ��Ϸ�˵�������Ϣ				//
#define		COMMAND_SET_MENU_CONFIG				120		//������Ϸ�˵�������Ϣ				//
#define		COMMAND_GET_LIMIT_TIME_PERIOD_INFO	267		//��ȡ����ʱ����Ϣ
#define		COMMAND_CLEAR_BT_REG_INFO			268		//���ע����Ϣ
//----------��ȡ���ݿ����Ϣָ��
#define		COMMAND_GET_GAMES_INFO				108		//��ȡT_GamesInfo��Ϸ��Դ����		//
#define		COMMAND_GET_WG_INFO					110		//��ȡT_WgsInf������������			//
#define		COMMAND_GET_PARENT_CLASS_INFO		111		//��ȡT_ParentClass��������			//
#define		COMMAND_GET_SUB_CLASS_INFO			112		//��ȡT_SubClassС������			//
#define		COMMAND_GET_MOVIE_INFO				260		//��ȡT_MovieInfo����				//
#define		COMMAND_GET_ONLINE_INFO				262		//��ȡT_Online����					//
#define		COMMAND_GET_PLAYER_LIST_INFO		264		//��ȡT_Player����					//
#define		COMMAND_GET_SINGLE_GAME_INFO		266		//��ȡ������Ϸ��Դ��Ϣ
//----------�������ݿ����Ϣָ��
#define		COMMAND_SET_PARENT_CLASS_INFO		121		//����T_ParentClass��������			//
#define		COMMAND_SET_SUB_CLASS_INFO			122		//����T_SubClassС������			//
#define		COMMAND_SET_MOVIE_INFO				261		//����T_MovieInfo����				//
#define		COMMAND_SET_ONLINE_INFO				263		//����T_Online����					//
#define		COMMAND_SET_PLAYER_LIST_INFO		265		//����T_Player����					//
//----------������Ϸ��Դ���á�����ָ��
#define		COMMAND_GET_BT_SYSTEM_INFO			123		//��ȡBTϵͳ�ſ���Ϣ				//
#define		COMMAND_GET_RESOURCE_NUMBER			124		//��ȡ��Դ��						//
#define		COMMAND_GAME_GET_SUPERFLUOUS_INFO	109		//��ȡ�������ֹͣ���µ���Դ����	//
#define		COMMAND_GAME_GET_DELETE_SORT		114		//��ȡ��Ϸɾ��˳������				//
#define		COMMAND_GAME_SET_SIMPLE_PROPERTY	117		//����BT��Դ������				//
#define		COMMAND_GAME_GET_SIMPLE_PROPERTY	118		//��ȡBT��Դ������				//
#define		COMMAND_GAME_DELETE					213		//ɾ����Դ							//
#define		COMMAND_GAME_CLEAR_FILEDIR			214		//��������ļ�Ŀ¼					//
#define		COMMAND_GAME_MOVE_DIRECTORY			215		//�ƶ���ϷĿ¼						//
#define		COMMAND_GAME_REPAIR					239		//��Ϸ�޸�							//
#define		COMMAND_GAME_SET_AUTO_UPDATE		242		//��Դ�����Զ����·�ʽ				//
#define		COMMAND_GAME_SET_MANUAL_UPDATE		243		//��Դ�����ֶ����·�ʽ				//

//----------�Զ�����Ϸ��Դ����ָ��
#define		COMMAND_CUSTOM_GAME_ADD				216		//����Զ�����Ϸ��Դ				//
#define		COMMAND_CUSTOM_WEB_ADD				217		//����Զ���WEB��Դ

#define		COMMAND_CUSTOM_GAME_GET_MAXID       218     //�Զ���ȡ����Զ�����Ϸ���		//
#define		COMMAND_CUSTOM_GAME_GET_PROPERTY	247		//��ȡ�û��Զ�����Ϸ����			//(�Զ�����Զ���ͳһ����)
#define		COMMAND_CUSTOM_GAME_MODIFY_PROPERTY	248		//�޸��û��Զ�����Ϸ����			//
#define		COMMAND_CUSTOM_GAME_DELETE			249		//�û��Զ�����Ϸɾ��				//
//----------������ȡ��Ϣ������ָ��
#define		COMMAND_GET_TASKS_INFO				196		//��ȡ���л������Ϣ				//
#define		COMMAND_GET_TASK_TRACKER_INFO		197		//��ȡָ�������Tracker��Ϣ			//
#define		COMMAND_GET_TASK_PEER_INFO			198		//��ȡָ������Ľڵ���Ϣ			//
#define		COMMAND_TASK_ADD_DOWNLOAD			200		//���һ����������					//(��COMMAND_TASK_ADD�޸�)
#define		COMMAND_TASK_SSD_DOWNLOAD			240		//SSD���̷�ʽ����					//(��COMMAND_TASK_SSD_ADD�޸�)
#define		COMMAND_TASK_PROPERTY_DOWNLOAD		241		//���Է�ʽ�������					//(��COMMAND_TASK_PROPERTY_ADD�޸�)
#define		COMMAND_TASK_ADD_SEED				199		//���һ����������					//(��COMMAND_TASK_SEED�޸�)
#define		COMMAND_TASK_ADD_SEED_SOURCE		219		//��ָ���������һ����Դ			//
#define		COMMAND_TASK_START					202		//��ʼ����							//
#define		COMMAND_TASK_STOP					203		//ֹͣ����							//
#define		COMMAND_TASK_CHECK					204		//�������							//
#define		COMMAND_TASK_REMOVE					205		//�Ƴ�����							//
#define		COMMAND_TASK_TOP					207     //�ö�								//
#define		COMMAND_TASK_UP						208		//����								//
#define		COMMAND_TASK_DOWN					209		//����								//
#define		COMMAND_TASK_LIMIT_SPEED			210		//�����ϴ��������ٶ�				//
#define		COMMAND_TASK_SORT					211		//����								//
#define		COMMAND_TASK_REFRESH_TRACKER		212		//ǿ������һ��Tracker				//				
//----------���顢����վ��������
#define		COMMAND_INSERT_GROUP				244		//���һ��������Ϣ					//
#define		COMMAND_MODIFY_GROUP				245		//�޸�һ��������Ϣ					//
#define		COMMAND_DELETE_GROUP				246		//ɾ��һ��������Ϣ					//
#define		COMMAND_GET_GROUP_INFO				221		//��ȡ���з�����Ϣ					//
#define		COMMAND_GET_GROUP_WORKSTATION		222		//��ȡָ�������еĹ���վ��Ϣ		//
#define		COMMAND_GET_GROUP_SERVER			229		//��ȡָ�������еķ�������Ϣ		//
#define		COMMAND_DELETE_WORKSTATION			253		//ɾ��һ̨����վ					//
#define		COMMAND_DELETE_SERVER				254		//ɾ��һ̨������					//
#define		COMMAND_SET_WORKSTATION_PROPERTY	223		//����һ̨����վ����(û�о��¼�)	//
#define		COMMAND_GET_WORKSTATION_PROPERTY    224     //��ȡһ̨����վ����				//
#define		COMMAND_SET_SERVER_PROPERTY			251		//����һ̨����������(û�о��¼�)	//
#define		COMMAND_GET_SERVER_PROPERTY			252		//��ȡһ̨����������				//
#define		COMMAND_SYNC_MZD_WORKSTATION		255		//ͬ��MZD����վ��Ϣ
#define		COMMAND_SYNC_MZD_SERVER				256		//ͬ��MZD��������Ϣ
//----------����Ŀ¼����ָ��
#define		COMMAND_GET_DISK_INFO				225		//��ȡ������Ϣ						//
#define     COMMAND_GET_FILE_DIRECTORY_INFO     226     //��ȡ�ļ�Ŀ¼��Ϣ					//
#define		COMMAND_GET_FILE_DIRECTORY_PROPERTY 227		//��ȡ�ļ�Ŀ¼����					//
#define		COMMAND_GET_DIRECTORY_SIZE			228		//��ȡĿ¼��С(��λByte��			//
//----------��Դ������λ����ָ��
#define		COMMAND_GAME_START_SEARCH			230		//��ʼ��Ϸ��λ����					
#define     COMMAND_GAME_COVER_LOCATE			235		//���Ƿ�ʽ��λ
#define		COMMAND_GAME_END_SEARCH				231		//������Ϸ��λ����					//����
#define		COMMAND_GAME_GET_LOCATE				232		//��ȡ��Ϸ��λ��Ϣ					//����
#define		COMMAND_GAME_GET_LOCATE_STATUS		233		//��ȡ��Ϸ��λ״̬					//����
#define		COMMAND_GAME_SET_LOCATE				234		//������Ϸ��λ��Ϣ

//----------����ƽ̨����ָ��
#define		COMMAND_MENU_GET_SINGLE_GAME_INFO	331		//��ȡ������Ϸ��Ϣ
#define		COMMAND_MENU_CLOSE					332		//�رյ�����Ϸ
//----------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------��ȡָ����Ŀ���͵���Դ����ֵ------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

#define		COMMAND_GET_SINGLE_PARENT_CLASS_NAME 271	//��ȡ��������Ĭ������
#define		COMMAND_GET_SINGLE_SUB_CLASS_NAME	272		//��ȡ����С��Ĭ������

//��ȡ��Դ��Ϣ�������
enum ParamGetGames
{
	getAll	= 0,										// ��ȡ����BT��Դ
	getToday,											// ��ȡ���ո�����Դ
	getHaveUpdat,										// �и�����Դ
	getUndownload,										// ��ȡδ������Դ
	getNew,												// ��ȡ��������Դ
	getLocal,											// ��ȡ����BT��Դ
	getDelete,											// ��ȡ������ɾ����Դ��¼
	getMenuClassGame,									// ��ȡ�˵�������Դ��Ϣ(game��)
	getMenuClassWeb,									// ��ȡ�˵�������Դ��Ϣ(web��)
	//getGroupGame										// ��ȡ������Ϸ��Ϣ
};
//��ѯ��Դ����
enum QueryType
{
	qtAll = 0,											// ����
	qtGamesOnline,										// ������Ϸ
	qtGamesLAN,											// ������Ϸ
	qtChess,											// ���ƶ�ս
	qtTools,											// �������
	qtFinancial,										// ����֤ȯ
	qtInternet,											// ���칤��
	qtGamesFUN,											// ������Ϸ
	qtApplications,										// ��������
	//�˵���Դ����(A~Z)
	//qtMenuClass											// �˵�����
};
//�˵���ԴС��
enum QuerySubClass
{
	qscAll = 0,									
	qscSubClass1,
	qscSubClass2,
	qscSubClass3,
	qscSubClass4,
	qscSubClass5,
	qscSubClass6,
	qscSubClass7,
	qscSubClass8,
	qscSubClass9,
};
//������������Դ�ķ�ʽ
enum ADD_SEED_SOURCE_MODE
{
	modeIpaddr = 0,										// IPPORTģʽ
	modeHttpUrl = 1										// HTTPģʽ
};
// �������ص�״̬
enum DL_DLBT_DOWNLOAD_STATE
{	
	P_BTDS_QUEUED,										// �����	
	P_BTDS_CHECKING_FILES,								// ���ڼ��У���ļ�
	P_BTDS_DOWNLOADING_TORRENT,							// ������ģʽ�£����ڻ�ȡ���ӵ���Ϣ	
	P_BTDS_DOWNLOADING,									// ����������
	P_BTDS_FINISHED,									// ָ�����ļ��������
	P_BTDS_SEEDING,										// �����У������е������ļ�������ɣ� 	
	P_BTDS_ALLOCATING,									// ����Ԥ������̿ռ� -- Ԥ����ռ䣬���ٴ�����Ƭ���� 
	// ����ѡ���йأ�����ʱ���ѡ��Ԥ������̷�ʽ�����ܽ����״̬
};
//----------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------�ṹ-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------begin  [ע:����Ҫ���ֽڶ���]
//��������Tracker��������Ϣ1
struct DL_TRACKER_INFO_ENTRY
{
	int				tier;               
	int				failCount;							// ����ʧ���˶��ٴ��ˣ��ɹ��󣬻ᱻ���㣬ֻ��¼�����ϴγɹ����ʧ�ܴ�����

	char			url[128];
	char			trackerID[128];   
	char			message[128];						// tracker��error����warning�·��ص�message������HttpЭ���е�һЩ������Ϣ

	DWORD			trackerError;						// �Ƿ�ʧ�ܣ�> 0 ��ʧ�ܣ�һ�����Ϣ����message�����ȡ������Ϊʧ�ܵ�ֵ�ܶ࣬ûһһ���ţ������ʧ�ܣ����Լ�¼�����ֵ���Ҳ鿴����ʲô��ʽ��ʧ��
	bool			announcing;							// ��ǰ���������С���
	bool			haveResponsed;						// �Ƿ��յ����ظ�
};

// ÿ�������ϵĽڵ㣨�û�������Ϣ1  
struct DL_PEER_INFO_ENTRY
{
	int				connectionType;						// �������� 0����׼BT(tcp); 1: P2SP��http�� 2: udp��������ֱ�����ӻ��ߴ�͸��
	int             downloadSpeed;						// �����ٶ�
	int             uploadSpeed;						// �ϴ��ٶ�
	UINT64          downloadedBytes;					// ���ص��ֽ���
	UINT64          uploadedBytes;						// �ϴ����ֽ���

	DWORD           peerFlag;							// tracker���ص�PeerFlag���������ͨ��tracker��õģ���Ϊ0
	USHORT          port;
	char            ip [64];							// �Է�IP
	char            client [64];						// �Է�ʹ�õĿͻ���
};

// ������������Ļ�����Ϣ1
struct DL_DOWNLOADER_INFO
{
	DL_DLBT_DOWNLOAD_STATE          state;				// ���ص�״̬
	float           percentDone;						// ��ɵı���
	int             downConnectionCount;				// ���ؽ�����������
	int             downloadLimit;						// ���������������
	int             connectionCount;					// �ܽ������������������ϴ���
	int             totalCompletedSeeds;				// Tracker������������������ɵ����������Tracker��֧��scrap���򷵻�-1
	int             inCompleteNum;						// �ܵ�δ��ɵ����������Tracker��֧��scrap���򷵻�-1
	int             seedConnected;						// ���ϵ�������ɵ�����
	int             totalCurrentSeedCount;				// ��ǰ���ߵ��ܵ�������ɵ��������������ϵĺ�δ���ϵģ�
	int             totalCurrentPeerCount;				// ��ǰ���ߵ��ܵ����ص��������������ϵĺ�δ���ϵģ�
	float           currentTaskProgress;				// ��ǰ����Ľ���

	BOOL            bPaused;							// �Ƿ���ͣ
	BOOL            bError;								// �Ƿ����������д���̳����ԭ����ϸԭ�����ͨ������DLBT_Downloader_GetLastError��֪
	BOOL            bReleasingFIles;					// �Ƿ�����ʹ��IO���

	UINT            downloadSpeed;						// ���ص��ٶ�
	UINT            uploadSpeed;						// �ϴ����ٶ�
	UINT64          wastedByteCount;					// �����ݵ��ֽ�����������Ϣ�ȣ�
	UINT64          totalDownloadedBytes;				// ���ص����ݵ��ֽ���
	UINT64          totalUploadedBytes;					// �ϴ������ݵ��ֽ���

	// Torrent��Ϣ
	UINT64          totalFileSize;						// �����ļ����ܴ�С
	UINT64          totalFileSizeExcludePadding;		// ʵ���ļ��Ĵ�С������padding�ļ�
	UINT64          totalPaddingSize;					// ����padding�Ĵ�С
	int             pieceCount;							// �ֿ���
	int             pieceSize;							// ÿ����Ĵ�С
	char            infoHash [256];						// �ļ���Hashֵ
	WCHAR           torrentName[260];					// torrentName
};
//------------------------------------------------------end

#pragma pack(push)//�������״̬
#pragma pack(1)//�������״̬

//��������Tracker��������Ϣ2
typedef struct _PACK_TRACKER_INFO_ENTRY
{
	DWORD			cbSize;
	DWORD			dwFlags;							// �������tie�ṹ�е���Ŀ

	DL_TRACKER_INFO_ENTRY	tie;

	_PACK_TRACKER_INFO_ENTRY()
	{
		memset(this,0,sizeof(_PACK_TRACKER_INFO_ENTRY));
		cbSize = sizeof(_PACK_TRACKER_INFO_ENTRY);
		dwFlags = BTS_FLAGS_32[8];
	}
}PACK_TRACKER_INFO_ENTRY;

// ÿ�������ϵĽڵ㣨�û�������Ϣ2  
typedef struct _PACK_PEER_INFO_ENTRY
{
	DWORD			cbSize;
	DWORD			dwFlags;							// �������pie�ṹ�е���Ŀ

	DL_PEER_INFO_ENTRY	pie;

	_PACK_PEER_INFO_ENTRY()
	{
		memset(this,0,sizeof(_PACK_PEER_INFO_ENTRY));
		cbSize = sizeof(_PACK_PEER_INFO_ENTRY);
		dwFlags = BTS_FLAGS_32[9];
	}
}PACK_PEER_INFO_ENTRY;

// ������������Ļ�����Ϣ2
typedef struct _PACK_DOWNLOADER_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;							// ����di�ṹ�е���Ŀ

	DL_DOWNLOADER_INFO	di;

	_PACK_DOWNLOADER_INFO()
	{
		memset(this,0,sizeof(_PACK_DOWNLOADER_INFO));
		cbSize = sizeof(_PACK_DOWNLOADER_INFO);
		dwFlags = BTS_FLAGS_32[25];
	}
}PACK_DOWNLOADER_INFO;

//SOCKET���������ͷ�ṹ
typedef struct _BT_SOCKET_HEAD_REQUEST
{	
	DWORD			cbSize;
	DWORD			dwFlags;

	WORD			wHead;								// 1978
	WORD			wUIVer;								// UI�汾
	UINT			uCommand;							// ָ��
	DWORD			dwRequestSize;						// ����ĳ���
	DWORD			dwCount;							// ��¼����
	wchar_t			wszPassword[16];					// ��������
	//DWORD			dwCRC;								// ����У��ֵ

	_BT_SOCKET_HEAD_REQUEST()
	{
		memset(this,0,sizeof(_BT_SOCKET_HEAD_REQUEST));
		cbSize = sizeof(_BT_SOCKET_HEAD_REQUEST);
		dwFlags = BTS_FLAGS_32[6];
	}
}BT_SOCKET_HEAD_REQUEST;
//SOCKET���������ͷ�ṹ
typedef struct _BT_SOCKET_HEAD_REPLY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	WORD			wHead;								// 1978
	WORD			wServiceVer;						// BT����汾
	UINT			uCommand;							// ָ��
	DWORD			dwReplySize;						// ������ĳ���
	DWORD			dwCount;							// ��¼����
	int				iErrorCode;							// �������(10000:��ʾ�ɹ�,������ʾʧ�ܣ�������Ϣ��ͨ��COMM_GetUIErrorInfoString��ȡ)
	//DWORD			dwCRC;								// ����У��ֵ

	_BT_SOCKET_HEAD_REPLY()
	{
		memset(this,0,sizeof(_BT_SOCKET_HEAD_REPLY));
		cbSize = sizeof(_BT_SOCKET_HEAD_REPLY);
		dwFlags = BTS_FLAGS_32[6];
	}
}BT_SOCKET_HEAD_REPLY;
//SOCKET���ջ���ṹ
typedef struct _SOCKET_BUFF
{
	int				iSize;								// ʵ����Ч�Ļ��������ݴ�С
	char			szBuff[1024*4];						// ������(4KB)
}SOCKET_BUFF;

//��������ṹ
typedef struct _COMMAND_PARAM
{
	DWORD			cbSize;
	DWORD			dwFlags;

	ParamGetGames	pgg;								// ��ȡ��Դ��Ϣ�������
	QueryType		qt;									// ��ѯ��Դ����
	QuerySubClass	qsc;								// ��ѯ��Դ����
	int				iSortItem;							// Ҫ�������Ŀ����(<0����Ŀ��Ĭ�ϣ�
	int				iSortFlag;							// ����ʽ��0:����1:����)		
	wchar_t			wszGroupName[18];					// getMenuClassGame��getMenuClassWeb:�˵����� getGroupGame:��������
	wchar_t			wszQueryString[32];					// ��ѯ�ַ�(Ϊ�վͲ���) (2013-08-08�¼�)
	int				nPage;					//ҳ��
	int				nCount;					//ҳ������

	_COMMAND_PARAM()
	{
		memset(this,0,sizeof(_COMMAND_PARAM));
		cbSize = sizeof(_COMMAND_PARAM);
		dwFlags = BTS_FLAGS_32[9];
	}
}COMMAND_PARAM;

//UI������Ҫ�ĵ�¼������Ϣ
typedef struct _UI_LOGIN_REPLY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszNetbarName[32];					// ��������
	wchar_t			wszAgentName[64];					// ����������
	wchar_t			wszAgentID[16];						// �����̱��
	WORD			wDay;								// ���ж����쵽��
	//
	DWORD			dwLoginStatus;						// (0x00:�޵�¼����;0x01:���ڵ�¼��֤��;0x02:��¼ʧ����Ҫ�ظ���¼)
	WORD			wUserStatus;						// �û�״̬(0:δ֪�û�,1:����û�,2:vip)USER_STATUS_UNKNOWN,USER_STATUS_FREE,USER_STATUS_VIP
	DWORD			dwError;							// ����ֵ(0:�޴���)
	wchar_t			wszError[128];						// ������Ϣ
	wchar_t			wszUserName[64];					// �û���
	int				iSoftMode;							// ���ģʽ(0:����ģʽ,1:�ӷ�ģʽ,2:��������ģʽ)

	_UI_LOGIN_REPLY()
	{
		memset(this,0,sizeof(_UI_LOGIN_REPLY));
		cbSize = sizeof(_UI_LOGIN_REPLY);
		dwFlags = BTS_FLAGS_32[10];
	}
}UI_LOGIN_REPLY;

//�Ǻ���������Ϣ�ṹ
typedef struct _WAIT_TASK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Size;						//�� ��Ϸ��Դ��С
	DWORD			dwStatus;							//�� �Ǻ�������ǰ����(NONCORE_TASK_STATUS_NONE,NONCORE_TASK_STATUS_DOWNLOAD_FILE,NONCORE_TASK_STATUS_CREATE_IDX)
	DWORD			dwTotalBtye;						//�� �ܵ��ֽ���
	DWORD			dwCompletedBtye;					//�� ����ɵ��ֽ���
	BOOL			bStop;								//�� �Ƿ�ֹͣ�ȴ�
	wchar_t			wszHashNew[41];						//�� �µ�HASHֵ
	wchar_t			wszHashOld[41];						//�� �ϵ�HASHֵ

	_WAIT_TASK_INFO()
	{
		memset(this,0,sizeof(_WAIT_TASK_INFO));
		cbSize = sizeof(_WAIT_TASK_INFO);
		dwFlags = BTS_FLAGS_32[7];
	}
}WAIT_TASK_INFO;

// ���������Ϣ
typedef struct _BASIC_TASK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								//�̱��
	DWORD			dwIndex;							//������ֵ(����),Ĭ����������ػ������ǰ���ȴ��������У��ϴ����������
	//_taskType		tsType;								//����������(TASK_TYPE_NONCORE:�Ǻ�������TASK_TYPE_CORE:��������)
	_taskAutoState	tsAutoState;						//�̵�ǰ�������״̬(TASK_STATUS_WAITING:�ȴ���TASK_STATUS_ACTIVE:�������TASK_STATUS_MANUAL_STOP:�ֶ�ֹͣ)
	//DWORD			dwCommand;							//����ǰ����ָ�� (�޸�:2013-05-07) ***��������***
	_taskUseDirectoryType	tsUseDirType;				//  ʹ��Ŀ¼������(��ʱʹ��dwCommand�Ŀռ䣩
	_taskTrigger	tsTrigger;							//�����ش�����(0:TSWS_TRIGGER_NONE)
	SYSTEMTIME		tmAdd;								//������ʱ��
	SYSTEMTIME		tmStart;							//�̿�ʼ�ʱ��
	SYSTEMTIME		tmFinished;							//���������ʱ��
	//
	HANDLE			hDownloader;						//�̻������**
	wchar_t			wszGame_Name[64];					// ��������**
	wchar_t			wszDirectoryName[64];				// Ŀ¼����(���ݿ���ִ���ļ�Ŀ¼������Ŀ¼����Ϊʵ�����ص�Ŀ¼��)**
	wchar_t			wszIdxPath[360];					// Idx�ļ�·��
	wchar_t			wszDirectory[360];					// ����Ŀ¼
	wchar_t			wszCacheDirectory[360];				// ����Ŀ¼
	wchar_t			wszHash[41];						// ������ֵ ��2013-8-3 �¼ӣ�
	char			szErrorInfo[128];					// ������Ϣ(�˴�����Ϊ���ֽڣ�����Ϊ�ں˴�����������Ƕ��ֽڵ�)
	//_taskCacheDirectoryState tsCacheDirState;			// ����Ŀ¼��״̬
	_taskDirectoryState	tsDirState;						// Ŀ¼��״̬

	DWORD			dwWorkImage;						// ����״̬ͼ��
	wchar_t			wszWorkStatus[360];					// ����״̬��Ϣ�ı�

	int				iChangePieces;						// ��Ҫ���µĿ�ĸ���
	int*			pChangePiecesArray;					// ��Ҫ���µģ��б仯��piece����Ϣ

	_BASIC_TASK_INFO()
	{
		memset(this,0,sizeof(_BASIC_TASK_INFO));
		cbSize = sizeof(_BASIC_TASK_INFO);
		dwFlags = BTS_FLAGS_32[21];
	}
}BASIC_TASK_INFO;
//����ṹ
typedef struct _TASK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 0x01 wti, 0x02 di,0x04 bti,

	PACK_DOWNLOADER_INFO	pdi;						// ��������
	//WAIT_TASK_INFO	wti;								// �Ǻ�������	
	BASIC_TASK_INFO	bti;								// ���������Ϣ   

	_TASK_INFO()
	{
		////memset(this,0,sizeof(_TASK_INFO));			// ����������
		cbSize = sizeof(_TASK_INFO);
		dwFlags = BTS_FLAGS_32[3];
	}
}TASK_INFO;

//��T_GamesInfo�����ݽṹ 
typedef struct	_T_GamesInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;
	DWORD			dwFlags1;

	wchar_t			wszGame_Id[8];						//  ���
	wchar_t			wszGame_Text[32];					//--����
	wchar_t			wszGame_Path[128];					//--�ļ���·��(��Ϸִ���ļ����·��,��ʽ"��ϷĿ¼\\..\\xx.exe")
	wchar_t			wszGame_Reg[128];					//--���������·��(��Ϸ����Ŀ¼,��ʽ"�̷�:\\..\\��ϷĿ¼")
	wchar_t			wszGame_Exe_Param[128];				//  ���в���
	wchar_t			wszGame_URL[32];					//  �ͻ���·��
	DWORD			dwGame_Click_Rate;					//  �ܵ��
	int				nGame_Flag;							//  �������(�μ�"��Դ״ֵ̬����",-4:δ֪״̬,-3:��Ч����(δ����) ,-2:��ɾ��(�ֶ�),-1:��ɾ��(�Զ�),0:δ����,1:�и���,2:�Ѿ����£���ɣ�,3:���ڸ���)
	wchar_t			wszGame_Abc[16];					//--ƴ����д
	wchar_t			wszGame_Only[128];					//--�ؼ��ļ�
	DWORD			dwGame_Show;						//  ��ʾ/��Ա
	DWORD			dwGame_Sort;						//  ����
	DWORD			dwGame_Type;						//--����(��������,0:δ����,֧��0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80... 32����)
	wchar_t			wszGame_Save[128];					//--����浵
	DWORD			dwNet_Sort;							//--��������
	wchar_t			wszGame_BM[32];						//  ����								-		
	SYSTEMTIME		InstTime;							//  ��������
	SYSTEMTIME		UpdateTime;							//  ��������
	DWORD			dwUpdate_Click_Rate;				//  ���º�ĵ����[�����µ����]
	DWORD			dwGameSize;							//--��Դ��С(��ȷ��MB)
	wchar_t			wszClass[32];						//--��Դ��������
	wchar_t			wszHashOld[41];						//  ���ص�HASH							-
	wchar_t			wszHashNew[41];						//--�������µ�HASH						-
	SYSTEMTIME		NetInstTime;						//--���簲װʱ��
	SYSTEMTIME		NetUpdateTime;						//--�������ʱ��
	BOOL			bIsPlan;							//  �ƻ�����(���·�ʽ,TRUE:�Զ����� FALSE:�ֶ�����)
	BOOL			bClearFile;							//  ��ֹ�Զ���������ļ�
	BOOL			bIsBT;								//--�Ƿ�����Ч��BT��Դ					-
	DWORD			dwTopGrade;							//  ��Ŀ�ȼ�
	BOOL			bRestoreTime;						//--�Ƿ�ԭ�ļ�ʱ��
	wchar_t			wszMonthDetail[121];				//  ���ص���ʵ�����ϸ					-
	DWORD			dwDeleteGrade;						//  ɾ���ȼ�
	double			fMonthClick;						//  ƽ���µ��
	wchar_t			wszFuzzyIndex[32];					//--ģ��Ŀ¼
	int				nUpdateRange;						//--���·�Χ(0:��ȫ������,1:ȫ������)	-
	DWORD			dwOSType;							//--֧�ֵĲ���ϵͳ(0x00:XP,0x01:WIN7��
	DWORD			dwGame3D;							//--3D��Ϸ�ȼ�							-
	wchar_t			wszReadme3D[128];					//--3D����˵��							-
	SYSTEMTIME		DelayUpdateTime;					//--������ʱʱ��(*�¼�)					-
	DWORD			dwRunMode;							//--��Ϸ����ģʽ(*�¼�)
	DWORD			dwShortcut;							//--���������ݷ�ʽ(0������,1����) �¼�:2013-06-07

	_T_GamesInfo()
	{
		memset(this,0,sizeof(_T_GamesInfo));
		cbSize = sizeof(_T_GamesInfo);
		dwFlags = BTS_FLAGS_32[32];
		dwFlags1 = BTS_FLAGS_32[9];
	}
}T_GamesInfo;

//��չ��Ϣ
typedef struct	_T_GamesInfoEx
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Id;							// ��ŵ�������
	wchar_t			wszDirectoryName[32];				// Ĭ�ϵ�Ŀ¼��xx (��strGame_Path�л�ȡ\xx\...\yy.zz ��xx)			-
	wchar_t			wszSubDirectory[64];				// ִ����Ŀ¼��...(��strGame_Path�л�ȡ\xx\...\yy.zz ��... )		-
	wchar_t			wszFileName[32];					// ִ���ļ���yy.zz (��strGame_Path�л�ȡ\xx\...\yy.zz �� yy.zz)		-
	DWORD			dwMonthDetail[30];					// ���ص���ʵ�����ϸֵ(��30�ݶ�Ӧһ���µ�30��)						-
	float			fNetInstalledDay;					// �����Ѱ�װ������(�뱾��ʱ��Ա�)									-
	float			fInstalledDay;						// �����Ѿ���װ������
	int				nServerGameStatus;					// �������ϵ���Ϸ״̬

	DWORD			dwWorkImage;						// ����ͼ��()
	DWORD			dwWorkColor;						// ������ɫ
	DWORD			dwWorkStatus;						//������״̬Ĭ��(RSWS_NONE:û�й���״̬;RSWS_ACTIVING:���;RSWS_ACTIVE_SUPPLY_SEED:���(������);RSWS_MOVE_DIRECTORY:�����ƶ�Ŀ¼��;RSWS_DELETE_DIRECTORY:����ɾ��Ŀ¼��;RSWS_RESTORE_CACHE_DIRECTORY:����Ŀ¼���ݻ�ԭ��)
	wchar_t			wszWorkStatus[32];					// ����״̬�ı���Ϣ

	//�޸�:2013-05-02	�¼�
	DWORD			dwExType;							// ��Դ��չ����(0x00:����չ���� 0x01:��ֹ֧ͣ�ָ��µ���Դ 0x02:ǿ���ƹ����Դ 0x04:ǿ���޸ĵ���Դ 0x08:ǿ��ɾ������Դ)

	_T_GamesInfoEx()
	{
		memset(this,0,sizeof(_T_GamesInfoEx));
		cbSize = sizeof(_T_GamesInfoEx);
		dwFlags = BTS_FLAGS_32[13];
	}
}T_GamesInfoEx;
//��Դ��Ϣ�ṹ 
typedef struct _RESOURCE_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 0x01 gi,0x02 giex;

	T_GamesInfo		gi;									// ��T_GameInfo�����ֶ���Ϣ
	T_GamesInfoEx   giex;								// ��չ��Ϣ

	_RESOURCE_INFO()
	{
		////memset(this,0,sizeof(_RESOURCE_INFO));		//����������
		cbSize = sizeof(_RESOURCE_INFO);
		dwFlags = BTS_FLAGS_32[2];
	}
}RESOURCE_INFO;

//��Դ����
typedef	struct _RESOURCE_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;							// 0x01 gi,0x02 wszAllGroupName;

	T_GamesInfo		gi;
	wchar_t			wszAllGroupName[32*18];				// ��Ч�ķ������ƺ��Ƿ�ѡ,��ʽ:[�Ƿ�ѡ][��������]|[�Ƿ�ѡ][��������]...|,����(0����|1����|1����|0����|)(֧��32�����飬ÿ��������Ϣռwchar_t[18])

	_RESOURCE_PROPERTY()
	{
		//memset(this,0,sizeof(_RESOURCE_PROPERTY));   //���ܰ�gi�����һ����
		memset(wszAllGroupName,0,sizeof(wszAllGroupName));
		cbSize = sizeof(_RESOURCE_PROPERTY);
		dwFlags = BTS_FLAGS_32[2];
	}
}RESOURCE_PROPERTY;

//��T_WgsInfo�ṹ
typedef struct 	_T_WgsInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszWg_Text[64];						// ����			0x01
	wchar_t			wszWg_FTP_Path[128];				// ·��			0x02
	wchar_t			wszWg_URL[128];						// �ͻ���·��	0x04
	wchar_t			wszWg_Ver[128];						// �����·��	0x08
	wchar_t			wszGame_Id[48];						// ��Ӧ��Ϸ���	0x10
	DWORD			dwWg_Flag;							// �������		0x20
	DWORD			dwWg_Show;							// ��ʾ/��Ա	0x40

	_T_WgsInfo()
	{
		memset(this,0,sizeof(_T_WgsInfo));
		cbSize = sizeof(_T_WgsInfo);
		dwFlags = BTS_FLAGS_32[7];
	}
}T_WgsInfo;

//��T_SubClass��T_ParentClass�ṹ 
typedef struct	 _T_ClassInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszID[3];							// �˵�����
	wchar_t 		wszName[32];						// �˵�������
	DWORD			dwShowIndex;						// ��ʾ˳��
	DWORD			dwShow;								// �Ƿ���ʾ
	wchar_t			wszTypeId[2];						// ��������(NULL,0:��� 1:���� 2:����)

	_T_ClassInfo()
	{
		memset(this,0,sizeof(_T_ClassInfo));
		cbSize = sizeof(_T_ClassInfo);
		dwFlags = BTS_FLAGS_32[5];
	}
}T_ClassInfo;

//��T_Manager�ṹ
typedef struct _T_Manager
{
	DWORD			cbSize;
	DWORD			dwFlags;
	DWORD			dwFlags1;
	DWORD			dwFlags2;

	wchar_t			wszNetwork_Disk[128];				// ������·��		***
	int				nNetwork_Level;						// �������			***
	wchar_t			wszTools_Disk[128];					// �������ߴ���		***
	wchar_t			wszQQ_Exe[64];						// QQ�ļ�			***
	wchar_t			wszMusic_Exe[128];					// ǧǧ�����ļ�		***
	BYTE			BaseInfo[1024];
	int				nInfoSize;
	int				nDbVer;								// ���ݿ�汾
	wchar_t			wszServerIP[16];					// ��Ϸ�����IP		***
	wchar_t			wszLoginServerIp[16];				// ��¼IP
	wchar_t			wszUsbServerIp[16];					// ����U��IP
	wchar_t			wszFtpServerIp[16];					// �浵IP
	wchar_t			wszCall1ServerIp[16];				// ����IP
	wchar_t			wszCall2ServerIp[16];
	wchar_t			wszCall3ServerIp[16];
	wchar_t			wszCall4ServerIp[16];
	wchar_t			wszCall5ServerIp[16];
	int				nEnterInfo;							// �Ƿ���ʾ
	int				nAutoReadSave;						// �Զ��浵
	int				nShowSaveWin;						// ��ʾ�浵����
	int				nShowAsIcon;						// ��ʾ��ʽ��ͼƬͼ��	***
	int				nPicSpacing;						// ͼƬ���				***
	int				nNormalIconSpacing;					// ��׼ͼ����			***
	int				nSmallIconSpacing;					// ����ͼ����			***
	int				nBigIconSpacing;					// ����ͼ����			***
	wchar_t			wszSkinFileName[128];				// Ƥ���ļ�				***
	wchar_t			wszBgFileName[128];					// �����ļ�				***
	int				nHideGameTools;						// ���ظ�������			***
	int				nHideCallBoard;						// ���ع����           ***(ע�ͣ����ز˵��ұߵ���Ϸ���а�)
	int				nNetConnection;						// ���ӣ�������ͨ
	int				nUserRegIp;							// �û�ע��IP
	wchar_t			wszUserRegName[64];					// ͨ��֤
	int				nIsFixedDisk;						// ��������
	wchar_t			wszWallpaperFileName[128];			// ǽֽ�ļ�
	int				nAutoWallpaper;						// �Զ�ѡ��ǽֽ
	int				nTimerWallpaper;					// ��ʱ�л�ǽֽ
	wchar_t			wszUpdate1ServerIP[16];				// �Զ�����IP
	wchar_t			wszUpdate2ServerIP[16]; 
	wchar_t			wszUpdate3ServerIP[16];
	wchar_t			wszUpdate4ServerIP[16];
	wchar_t			wszUpdate5ServerIP[16];
	int				nNoExistRun;						// ��Ϸ������ʱ���з�ʽ
	wchar_t			wszUpdatePwd[64];					// �Զ���������
	int				nUpdateMode;						// �Զ����·�ʽ
	wchar_t			wszGroupType[80];					// ��������
	int				nUserCallTimer;						// �������ܼ��ʱ��
	wchar_t			wszShowBoardText[256];				// ������ı�
	int				nShowBoardTime;						// �Ƿ񵯳������(ע�ͣ�if(ShowBoardTime&0x02):����ʱ��ʾ�����, if(ShowBoardTime&0x01):Ĭ����ʾ������ı� else ��ʾnbboard.htm�ļ�����)
	int				nRunIsMode;							// ������Ϸ����С�������� ***
	int				nIsUpdate;							// �Զ����·���
	int				IsNetUsb;							// ����U��
	wchar_t			wszCustomExe1[128];					// �Զ����ļ�
	wchar_t			wszCustomExe2[128];
	wchar_t			wszCustomExe3[128];
	wchar_t			wszCustomExe4[128];
	int				nVerType;							// �汾����
	int				nShowClass;							// �Ƿ���ʾ�ӷ���
	int				nWmConfig;							// �Զ�������Ϸ�������ó���(*)
	int				nToolsPrompt;						// ���и�������ʱ�Ƿ񾯸���ʾ(*)
	wchar_t			wszAgentID[32];						// �����̱��(*)
	wchar_t			wszAgentMZP[64];					// ������ͨ��֤(*)
	wchar_t			wszCustomName1[128];
	wchar_t			wszCustomName2[128];
	wchar_t			wszCustomName3[128];
	wchar_t			wszCustomName4[128];
	int				nSwitchWndSave;						// 1 ��ʾ�л������Զ����棬0 ��ʾ������
	int				nIeNewWin;
	SYSTEMTIME		Clicktime;
	int				nClickDay;
	int				nAlphaIcon;							//0:256ɫ 1:͸��ͨ����ɫ
	BOOL			bExitPopAd;							// �˳�ʱ�Ƿ񵯳����
	int				nLanguageId;						// ���Ե������(֧�ֶ�������)
	wchar_t			wszCityName[20];					// ��������

	_T_Manager()
	{
		memset(this,0,sizeof(_T_Manager));
		cbSize = sizeof(_T_Manager);
		dwFlags = BTS_FLAGS_32[32];
		dwFlags1 = BTS_FLAGS_32[32];
		dwFlags2 = BTS_FLAGS_32[9];
	}
}T_Manager;

//��Ϸ�˵���չ����
typedef struct _MENU_CONFIG_EX
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwMenuStyle;						// ��Ϸ�˵����(0:�����,1:��ͨ��,2:��ͳ��,3:Win7��,4:ʱ�а�)
	DWORD			dwClassTemplate;					// ��Ϸ����ģ��(0:��ģ��,1~3Ĭ��ģ��һ����,4�Զ���ģ��)

	_MENU_CONFIG_EX()
	{
		memset(this,0,sizeof(_MENU_CONFIG_EX));
		cbSize = sizeof(_MENU_CONFIG_EX);
		dwFlags = BTS_FLAGS_32[2];
	}
}MENU_CONFIG_EX;

//��Ϸ�˵�����
typedef struct _MENU_CONFIG
{
	DWORD			cbSize;								
	DWORD			dwFlags;							// 0x01 manager, 0x02 mcex

	T_Manager		manager;
	MENU_CONFIG_EX	mcex;

	_MENU_CONFIG()
	{
		//memset(this,0,sizeof(_MENU_CONFIG));			//����������(����manager,mcex��ʼֵҲ�������)
		cbSize = sizeof(_MENU_CONFIG);
		dwFlags = BTS_FLAGS_32[2];
	}
}MENU_CONFIG;

//��T_Promotion�ṹ(Today.mdb)
typedef struct	_T_Promotion
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwAutoID;							// �Զ����
	wchar_t			wszFileName[8];						// 6λ��Դ��Ŀ���
	wchar_t			wszArea[10];						// ����(Area��MZP�໥�ų⣬ֻȡһ������ȡArea,���Ϊ�գ���ȡMZP)
	wchar_t			wszMZP[32];							// ����ͨ��֤
	DWORD			dwFlag;								// (��������(0:ǿɾ1:ǿ�ƹ�2:ǿ����))
	wchar_t			wszVerType[6];						// �û��汾����(WMP -�ֱ��Ӧ- WMB|MZD|PXD)

	_T_Promotion()
	{
		memset(this,0,sizeof(_T_Promotion));
		cbSize = sizeof(_T_Promotion);
		dwFlags = BTS_FLAGS_32[6];
	}
}T_Promotion;

//��T_GroupList�ṹ 
typedef struct	_T_GroupList
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwComputerID;						// ��������
	wchar_t			wszComputerName[32];				// �������
	DWORD			dwComputerGroup;					// ��������
	wchar_t			wszIP[16];							// IP��ַ
	wchar_t			wszMAC[18];							// MAC������ַ
	wchar_t			wszGateway[16];						// ����
	wchar_t			wszDNS1[16];						// DNS1
	wchar_t			wszDNS2[16];						// DNS2		
	wchar_t			wszSubnetMask[16];					// ��������
	wchar_t			wszResolution[10];					// �ֱ���

	_T_GroupList()
	{
		memset(this,0,sizeof(_T_GroupList));
		cbSize = sizeof(_T_GroupList);
		dwFlags = BTS_FLAGS_32[10];
	}
}T_GroupList;

//��T_WorkstationInfo  ����վ��Ϣ
typedef struct _T_WorkstationInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// ����վ���
	DWORD			dwGroup;							// ��������
	wchar_t			wszName[32];						// ����վ����
	wchar_t			wszIP[16];							// ����վIP
	wchar_t			wszMAC[32];							// ����MAC��ַ

	_T_WorkstationInfo()
	{
		memset(this,0,sizeof(_T_WorkstationInfo));
		cbSize = sizeof(_T_WorkstationInfo);
		dwFlags = BTS_FLAGS_32[5];
	}
}T_WorkstationInfo;

//��T_ServerInfo		��������Ϣ
typedef	struct _T_ServerInfo
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszName[32];						// ����������
	DWORD			dwGroup;							// ��������
	wchar_t			wszIP[4][16];						// IP��ַ(֧��4��)

	_T_ServerInfo()
	{
		memset(this,0,sizeof(_T_ServerInfo));
		cbSize = sizeof(_T_ServerInfo);
		dwFlags = BTS_FLAGS_32[3];
	}
}T_ServerInfo;

//��T_Movie
typedef struct _T_Movie
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwMovie_Index;						// ����
	wchar_t			wszMovie_Path[255];					// ·��
	wchar_t			wszMovie_Disk[2];					// �̷�
	wchar_t			wszLogin_Name[30];					// ��¼�ʺ�
	wchar_t			wszLogin_Pass[30];					// ��¼����
	wchar_t			wszMovie_Name[50];					// ����
	DWORD			dwMovie_Show;						// ��ʾ���Ա
	DWORD			dwIsDefault;						// ��ҳ

	_T_Movie()
	{
		memset(this,0,sizeof(_T_Movie));
		cbSize = sizeof(_T_Movie);
		dwFlags = BTS_FLAGS_32[8];
	}
}T_Movie;

//��T_Online
typedef struct _T_Online
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwIdx;								// ����
	wchar_t			wszLink[255];						// ·��
	wchar_t			wszCaption[20];						// ����
	DWORD			dwShow;								// ��ʾ���Ա
	DWORD			dwIsDefault;						// ��ҳ

	_T_Online()
	{
		memset(this,0,sizeof(_T_Online));
		cbSize = sizeof(_T_Online);
		dwFlags = BTS_FLAGS_32[5];
	}
}T_Online;

//��T_PlayerList
typedef struct _T_PlayerList
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszPlayerFile[255];					// �������ļ�
	wchar_t			wszPlayerExt[255];					// ��չ���б�
	DWORD			dwPlayerType;						// ����Ӱ��/����

	_T_PlayerList()
	{
		memset(this,0,sizeof(_T_PlayerList));
		cbSize = sizeof(_T_PlayerList);
		dwFlags = BTS_FLAGS_32[3];
	}
}T_PlayerList;

//BTϵͳ�ſ���Ϣ
typedef struct _BT_SYSTEM_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwDownloads;						// ��������������
	DWORD			dwLimitDownloads;					// ͬʱ�������������
	DWORD			dwWaitDownloads;					// �ȴ�����
	DWORD			dwTimePeriodLimitSpeed;				// ��ʱ������
	BOOL			bTimePeriodLimitSpeed;				// �Ƿ����˷�ʱ������
	BOOL			bPortUPNP;							// �Ƿ����˶˿�ӳ��
	int				iLine;								// ѡ����·
	DWORD			dwDownloadSpeed;					// �����ٶ�(KB)
	DWORD			dwTotalGames;						// ������Ϸ����
	__int64			ulTotalGameSize;					// ������Ϸ����(Byte)
	DWORD			dwLocalGames;						// ���������ص���Ϸ
	__int64			ulLocalGameSize;					// ������Ϸ����(Byte)
	DWORD			dwLocalHaveUpdateGames;				// ����δ���µ���Ϸ��

	_BT_SYSTEM_INFO()
	{
		memset(this,0,sizeof(_BT_SYSTEM_INFO));
		cbSize = sizeof(_BT_SYSTEM_INFO);
		dwFlags = BTS_FLAGS_32[13];
	}
}BT_SYSTEM_INFO;

//��Դ����������
typedef struct  _BT_RESOURCE_NUMBER
{
	DWORD			cbSize;
	DWORD			dwFlags;

	int				nNetResource;						// ȫ����Դ
	int				nTodayUpdate;						// ���ո���
	int				nHaveUpdate;						// �и�����Ϸ
	int				nUndownload;						// δ������Ϸ
	int				nNew;								// ��������Ϸ
	int				nStopUpdate;						// ��ͣ����Ϸ
	//	int				nLocal;								// ������Դ(2013-06-04����)

	int				nLocalBtGame;						// ����BT��Ϸ(2013-06-04�¼�)
	int				nLocalBtWeb;						// ����BTWeb(2013-06-04�¼�)
	int				nLocalUserGame;						// �����û���Ϸ(2013-06-04�¼�)
	int				nLocalUserWeb;						// �����û�Web(2013-06-04�¼�)

	int				nNetGame;							// ������Ϸ
	int				nDiskGame;							// ������Ϸ
	__int64			ulNetGameSize;						// ������Ϸ��С
	__int64			ulDiskGameSize;						// ������Ϸ��С
	__int64			ulResourceSize;						// ��Դ��С

	_BT_RESOURCE_NUMBER()
	{
		memset(this,0,sizeof(_BT_RESOURCE_NUMBER));
		cbSize = sizeof(_BT_RESOURCE_NUMBER);
		dwFlags = BTS_FLAGS_32[15];
	}
}BT_RESOURCE_NUMBER;


//�ƶ���ԴĿ¼��Ϣ
typedef struct _GAME_MOVE_DIRECTORY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// Ҫ�ƶ�����Դ���
	wchar_t			wszOrgDirectory[360];				// ԭʼĿ¼ 
	wchar_t			wszDestDirectory[360];				// Ҫ�ƶ�����Ŀ��Ŀ¼
	BOOL			bForceMove;							// �Ƿ�����ǿ���ƶ�

	_GAME_MOVE_DIRECTORY()
	{
		memset(this,0,sizeof(_GAME_MOVE_DIRECTORY));
		cbSize = sizeof(_GAME_MOVE_DIRECTORY);
		dwFlags = BTS_FLAGS_32[4];
	}
}GAME_MOVE_DIRECTORY;

//�ƶ���ԴĿ¼������Ϣ
typedef struct _GAME_MOVE_DIRECTORY_PROPERSS
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// ��Դ���
	DWORD			dwMax;								// ������ֵ
	DWORD			dwCurPos;							// ��ǰ����λ��

	_GAME_MOVE_DIRECTORY_PROPERSS()
	{
		memset(this,0,sizeof(_GAME_MOVE_DIRECTORY_PROPERSS));
		cbSize = sizeof(_GAME_MOVE_DIRECTORY_PROPERSS);
		dwFlags = BTS_FLAGS_32[3];
	}
}GAME_MOVE_DIRECTORY_PROPERSS;

//ֱ�������ϴ��ṹ
typedef struct _TASK_SEED_DATA
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// ��Դ���
	BOOL			bQuickSeed;							// �Ƿ�����ϴ�����
	wchar_t			wszIdxPath[256];					// idx�ļ�·��
	wchar_t			wszDirectory[256];					// ��ԴĿ¼

	_TASK_SEED_DATA()
	{
		memset(this,0,sizeof(_TASK_SEED_DATA));
		cbSize = sizeof(_TASK_SEED_DATA);
		dwFlags = BTS_FLAGS_32[4];
	}
}TASK_SEED_DATA;

//�����Դ�ṹ
typedef struct _ADD_SEED_SOURCE
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwID;								// ��Դ���
	wchar_t			wszIP[64];							// ��ԴIP��ַ
	WORD			wPort;								// ��ԴBT�˿ں�
	ADD_SEED_SOURCE_MODE	addMode;					// ���ģʽ

	_ADD_SEED_SOURCE()
	{
		memset(this,0,sizeof(_ADD_SEED_SOURCE));
		cbSize = sizeof(_ADD_SEED_SOURCE);
		dwFlags = BTS_FLAGS_32[4];
	}
}ADD_SEED_SOURCE;

//�ļ�Ŀ¼��Ϣ
typedef struct _FILE_DIRECTORY_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	BOOL			bIsFile;							// �Ƿ����ļ�
	wchar_t			wszName[128];						// �ļ�Ŀ¼��

	_FILE_DIRECTORY_INFO()
	{
		memset(this,0,sizeof(_FILE_DIRECTORY_INFO));
		cbSize = sizeof(_FILE_DIRECTORY_INFO);
		dwFlags = BTS_FLAGS_32[2];
	}
}FILE_DIRECTORY_INFO;

//�ļ�Ŀ¼����
typedef struct _FILE_DIRECTORY_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	BOOL			bDirectory;							// �Ƿ���Ŀ¼
	DWORD			dwFile;								// ���ļ�����
	DWORD			dwDirectory;						// ��Ŀ¼����
	__int64			ulTotalSize;						// �ܵĴ�С

	_FILE_DIRECTORY_PROPERTY()
	{
		memset(this,0,sizeof(_FILE_DIRECTORY_PROPERTY));
		cbSize = sizeof(_FILE_DIRECTORY_PROPERTY);
		dwFlags = BTS_FLAGS_32[4];
	}
}FILE_DIRECTORY_PROPERTY;

//������Ϣ
typedef struct _DISK_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszDisk[4];							// �����̷�
	wchar_t			wszVolumnInfo[64];					// �����Ϣ
	UINT			uDiskType;							// ��������
	__int64			ulTotal;							// �ܹ���С
	__int64			ulRemaining;						// ʣ���С

	_DISK_INFO()
	{
		memset(this,0,sizeof(_DISK_INFO));
		cbSize = sizeof(_DISK_INFO);
		dwFlags = BTS_FLAGS_32[5];
	}
}DISK_INFO;
//������Ϣ����
typedef struct _GroupInfo
{
	wchar_t			wszGroupName[32][18];				// ����֧�ֵ�32����������
}GroupInfo;
//��������
typedef struct _BT_GROUP_NAME
{
	wchar_t			wszGroupName[18];					// ������������,Ϊ�ձ�ʾȫ��
}BT_GROUP_NAME;
//�޸ķ�����Ϣ
typedef struct _MODIFY_GROUP_NAME
{
	BT_GROUP_NAME		oldGroupName;					// �ϵķ�������
	BT_GROUP_NAME		newGroupName;					// ���޸ĵ��·�������
}MODIFY_GROUP_NAME;
//���з�����Ϣ
typedef struct _GROUP_INFO
{
	BT_GROUP_NAME		gn[32];
}GROUP_INFO;

//UI�����¼����
typedef struct _UI_LOGING_USERPSW
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszUserName[64];
	wchar_t			wszPassword[32];

	_UI_LOGING_USERPSW()
	{
		memset(this,0,sizeof(_UI_LOGING_USERPSW));
		cbSize = sizeof(_UI_LOGING_USERPSW);
		dwFlags = BTS_FLAGS_32[2];
	}
}UI_LOGING_USERPSW;

//ͬ�����ݽ��Ƚṹ
typedef struct _SYNC_DATA_PROGRESS
{
	DWORD			cbSize;
	DWORD			dwFlags;

	BOOL			bSyncing;							// �Ƿ���ͬ����
	DWORD			dwStatus;							// ͬ��״̬(0:��ͬ����ͬ�������,1:����ͬ������)
	DWORD			dwFileSize;							// ����ͬ�����ļ���С
	DWORD			dwDownload;							// ����ͬ�����ļ�����ɴ�С
	wchar_t			wszFileName[64];					// ����ͬ�����ļ���
	wchar_t			wszInfo[128];						// ��Ϣ

	_SYNC_DATA_PROGRESS()
	{
		memset(this,0,sizeof(_SYNC_DATA_PROGRESS));
		cbSize = sizeof(_SYNC_DATA_PROGRESS);
		dwFlags = BTS_FLAGS_32[6];
	}
}SYNC_DATA_PROGRESS;

//BT�û��������ô���
typedef	struct _BT_CONFIG_INFO
{
	DWORD			cbSize;
	DWORD			dwFlags;
	DWORD			dwFlags1;

	//�˿�ӳ��
	BOOL			bMapPort;							// �Ƿ�ӳ��BT�˿�
	BOOL			bMapRouterPort;						// �Ƿ�ӳ�䲹�ֶ˿�
	//��¼����
	wchar_t			wszUserName[32];					// BT�û��˺�
	wchar_t			wszPassword[32];					// BT�û�����
	wchar_t			wszOldPID[128];						// �ϴγɹ���¼��PID
	//��������
	BOOL			bDisablePublishGames;				// ��ֹ����������Ϸ
	BOOL			bUPNP;								// �Ƿ���UPNP�Զ��˿�ӳ��
	BOOL			bLimitLocalBandwidth;				// �Ƿ����Ʊ��ش���(�������ء��ϴ��ٶ�)
	BOOL			bAutoDeleteStopUpdate;				// �Ƿ��Զ�ɾ����ֹͣ���µ���Ϸ
	BOOL			bAutoClearSpace;					// �Ƿ��Զ�����ռ�(�ڴ��̿ռ䲻��ʱ)
	BOOL			bNoManualToAuto;					// �ֶ�����ʱ���ı���·�ʽΪ"�Զ�����"
	DWORD			dwUserNetLineType;					// �û�������·���ͼ�����(0:����(ADSL),1:����(10M����),2:����(100M����),3:��ͨ(ADSL),4:��ͨ(10M����),5:��ͨ(100M����),6:����(ADSL),7:����(10M����),8:����(100M����))
	DWORD			dwSyncIntervalTime;					// �������ͬ�����ݼ��ʱ��(����)
	DWORD			dwHoldDiskSpace;					// ��ҪԤ���Ĵ��̿ռ��С
	wchar_t			wszServerIP[16];					// ������IP��ַ(��������������)
	int				iSoftMode;							// ����ģʽ(0:����ģʽ,1:�ӷ�ģʽ,2:����վģʽ
	//�����������ٶ�
	DWORD			dwMaxActiveTask;					// ���������
	DWORD			dwMaxDownloadTask;					// �������������
	DWORD			dwMaxDownloadSpeed;					// ȫ����������ٶ�
	DWORD			dwMaxUploadSpeed;					// ȫ������ϴ��ٶ�

	DWORD			dwLANMaxDownloadSpeed;				// ������������ٶ�(2013-07-24 �¼�)

	//���ض˿�
	DWORD			dwPort;								// BT�˿�
	DWORD			dwRouterPort;						// ���ֶ˿�
	//�Զ��Ƴ��������
	BOOL			bAutoRemoveCompletedTask;			// �Ƿ��Զ��Ƴ�����ɵĻ����
	BOOL			bAutoRemoveTime;					// �Ƿ������Ƴ�ʱ��(�ϴ�ʱ��ﵽ��ֵʱ�����Ƴ�)
	BOOL			bAutoRemoveSpeed;					// �Ƿ������Ƴ��ٶ�(�����ٶ�С�ڴ�ֵʱ�����Ƴ�)
	DWORD			dwAutoRemoveTime;					// �Զ��Ƴ���Ҫ�ϴ�ʱ�䳬����ֵ
	DWORD			dwAutoRemoveSpeed;					// �Զ��Ƴ���Ҫ�����ٶ�С�ڴ�ֵ
	//�Զ���������Ϸ
	BOOL			bAutoAcceptNew;						// �Ƿ��Զ�������������Դ
	BOOL			bAutoAcceptNetGame;					// �Ƿ��Զ������µ�������Ϸ
	BOOL			bAutoAcceptHDGame;					// �Ƿ��Զ������µĵ�����Ϸ
	BOOL			bAutoAcceptToolSoft;				// �Ƿ��Զ������µĹ������
	BOOL			bAutoAcceptFZTool;					// �Ƿ��Զ������µĸ�������
	BOOL			bAutoAcceptSize;					// �Ƿ������Զ����յ�����Դ�Ĵ�С
	BOOL			bAutoAcceptRank;					// �Ƿ������Զ����յ�����Դ������
	DWORD			dwAutoAcceptSize;					// �Զ���������Ϸʱ��Ϸ��С���ô��ڴ�ֵ
	DWORD			dwAutoAcceptRank;					// �Զ���������Ϸʱ��Ϸ�������в��ô��ڴ�ֵ(Ĭ�ϲ�С��20)
	//����Ŀ¼
	wchar_t			wszCacheDirectory[128];				// ���ػ���Ŀ¼��(T:\temp)
	wchar_t			wszDefaultDirectory[8][64];			// �̶�8�����Ĭ������Ŀ¼
	wchar_t			wszSSD[32];							// SSD�̷�(H:\)									
	//ʱ��ο���
	wchar_t			wszLimitSpeedTimePeriod[169];		// �ٶ�����ʱ���(0:������ 1:���� 2:��ֹ��
	DWORD			dwLimitUploadRate;					// ��ǰ�Զ����Ƶ��ϴ��ٶ� 
	DWORD			dwLimitDownloadRate;				// ��ǰ�Զ����Ƶ������ٶ�  
	//�����˳�����
	BOOL			bStartupRun_1;
	BOOL			bStartupRun_2;
	BOOL			bStartupRun_3;
	BOOL			bExitRun_1;
	BOOL			bExitRun_2;
	BOOL			bExitRun_3;
	wchar_t			wszStartupExe_1[64];
	wchar_t			wszStartupExe_2[64];
	wchar_t			wszStartupExe_3[64];
	wchar_t			wszStartupParam_1[64];
	wchar_t			wszStartupParam_2[64];
	wchar_t			wszStartupParam_3[64];
	wchar_t			wszExitExe_1[64];
	wchar_t			wszExitExe_2[64];
	wchar_t			wszExitExe_3[64];
	wchar_t			wszExitParam_1[64];
	wchar_t			wszExitParam_2[64];
	wchar_t			wszExitParam_3[64];	

	_BT_CONFIG_INFO()
	{
		memset(this,0,sizeof(_BT_CONFIG_INFO));
		cbSize = sizeof(_BT_CONFIG_INFO);
		dwFlags = BTS_FLAGS_32[32];
		dwFlags1 = BTS_FLAGS_32[29];
	}
}BT_CONFIG_INFO;

//������Ϸ��Դ�ļ�����
typedef struct _SET_GAME_SIMPLE_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Id;							// ���(*������д)
	DWORD			dwIsPlan;							// ���·�ʽ(0:���ı� 1:�ֶ� 2:�Զ�)
	DWORD			dwClearFile;						// ��������ļ�(0:���ı� 1:�ֶ� 2:�Զ�
	DWORD			dwTopGrade;							// ��Ϸ�ȼ�(0:���ı� 12345)
	DWORD			dwGroupMode;						// ���鷽ʽ(0:���ı� 1:ȡ������ 2:���÷���)
	wchar_t			wszDirectory[360];					// ����Ŀ¼
	wchar_t			wszGroupName[32*18];				// ��ʽ[��ѡ�˵ķ�������]|[��ѡ�˵ķ�������]...

	_SET_GAME_SIMPLE_PROPERTY()
	{
		memset(this,0,sizeof(_SET_GAME_SIMPLE_PROPERTY));
		cbSize = sizeof(_SET_GAME_SIMPLE_PROPERTY);
		dwFlags = BTS_FLAGS_32[7];
	}
}SET_GAME_SIMPLE_PROPERTY;

//��ȡ��Ϸ��Դ�ļ�����
typedef struct _GET_GAME_SIMPLE_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwGame_Id;							// ���(*������д)
	int				nGame_Flag;							// ״̬
	DWORD			dwIsPlan;							// ���·�ʽ(0:���ı� 1:�ֶ� 2:�Զ�)
	DWORD			dwClearFile;						// ��������ļ�(0:���ı� 1:�ֶ� 2:�Զ�
	DWORD			dwTopGrade;							// ��Ϸ�ȼ�(0:���ı� 12345)
	DWORD			dwGroupMode;						// ���鷽ʽ(0:���ı� 1:ȡ������ 2:���÷���)
	wchar_t			wszDirectoryName[64];				// ��ϷĿ¼��
	wchar_t			wszDirectory[360];					// ����Ŀ¼
	wchar_t			wszAllGroupName[32*18];				// ��Ч�ķ������ƺ��Ƿ�ѡ,��ʽ:[�Ƿ�ѡ][��������]|[�Ƿ�ѡ][��������]...|,����(0����|1����|1����|0����|)(֧��32�����飬ÿ��������Ϣռwchar_t[18])

	_GET_GAME_SIMPLE_PROPERTY()
	{
		memset(this,0,sizeof(_GET_GAME_SIMPLE_PROPERTY));
		cbSize = sizeof(_GET_GAME_SIMPLE_PROPERTY);
		dwFlags = BTS_FLAGS_32[9];
	}
}GET_GAME_SIMPLE_PROPERTY;

//��Ϸ�Զ�ɾ��˳��ṹ
typedef struct _GAME_AUTO_DELETE_SORT
{
	DWORD		cbSize;
	DWORD		dwFlags;

	DWORD		dwGame_Id;								//���
	wchar_t		wszGame_Text[32];						//����
	wchar_t		wszGame_Reg[128];						//·��
	DWORD		dwGame_Click_Rate;						//�ܵ����
	DWORD		dwNet_Sort;								//��������
	DWORD		dwTopGrade;								//��Ŀ�ȼ�
	float		fInstDay;								//�����Ѿ���װ������

	_GAME_AUTO_DELETE_SORT()
	{
		memset(this,0,sizeof(_GAME_AUTO_DELETE_SORT));
		cbSize = sizeof(_GAME_AUTO_DELETE_SORT);
		dwFlags = BTS_FLAGS_32[7];
	}
}GAME_AUTO_DELETE_SORT;

//ɾ����Ϸ˳��ṹ
typedef struct _GAME_DELETE_SORT
{
	DWORD		cbSize;
	DWORD		dwFlags;

	wchar_t		wszGame_Id[8];							//���
	wchar_t		wszGame_Text[32];						//����
	wchar_t		wszGame_Reg[128];						//·��
	int			nGame_Flag;								//�������(-3:δ֪״̬,-2:��Ч����(δ����),-1:��ɾ��,0:δ����,1:�и���,2:�Ѿ����£���ɣ�,3:���ڸ���) //20121012�޸ļ�
	DWORD		dwNet_Sort;								//��������
	SYSTEMTIME	InstTime;								//���ذ�װʱ��
	DWORD		dwGameSize;								//��С(��ȷ��MB)
	DWORD		dwTopGrade;								//��Ŀ�ȼ�
	DWORD		dwDeleteSort;							//��ʱ��Ϊ����ʣ�ɾ��˳��(ɾ���ȼ�)��
	wchar_t		wszMonthDetail[121];					//
	float		fMonthClick;							//ƽ���µ��
	//
	DWORD		dwMonthDetail[30];						//���ص���ʵ�����ϸֵ
	int			iInstalledDay;							//�����Ѿ���װ������

	_GAME_DELETE_SORT()
	{
		memset(this,0,sizeof(_GAME_DELETE_SORT));
		cbSize = sizeof(_GAME_DELETE_SORT);
		dwFlags = BTS_FLAGS_32[13];
	}
}GAME_DELETE_SORT;
//����վ����
typedef struct _WORKSTATION_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	DWORD			dwOldComputerID;					// �ϵļ�������(*������д)		****(ԭ��:dwComputerID,�޸�:2013-03-25 13:51)
	DWORD			dwNewComputerID;					// �µļ�������(�޸ļ���������,�����dwOldComputerID��ͬ����ʾ��������Ҫ�޸�) ****(�¼�:2013-03-25 13:51)
	wchar_t			wszComputerName[32];				// �������
	wchar_t			wszIP[16];							// IP��ַ
	wchar_t			wszMAC[20];							// MAC��ַ
	wchar_t			wszAllGroupName[32*18];				// ��Ч�ķ������ƺ��Ƿ�ѡ,��ʽ:[�Ƿ�ѡ][��������]|[�Ƿ�ѡ][��������]...|,����(0����|1����|1����|0����|)(֧��32�����飬ÿ��������Ϣռwchar_t[18])

	_WORKSTATION_PROPERTY()
	{
		memset(this,0,sizeof(_WORKSTATION_PROPERTY));
		cbSize = sizeof(_WORKSTATION_PROPERTY);
		dwFlags = BTS_FLAGS_32[6];
	}
}WORKSTATION_PROPERTY;
//����������
typedef struct _SERVER_PROPERTY
{
	DWORD			cbSize;
	DWORD			dwFlags;

	wchar_t			wszOldComputerName[32];				// �ϵļ������(*������д)			****(ԭ��:wszComputerName[32],�޸�:2013-03-25 13:51)
	wchar_t			wszNewComputerName[32];				// �µļ������(�޸ļ��������,�����wszOldComputerName��ͬ����ʾ�������Ҫ�޸�)		****(�¼�:2013-03-25 13:51
	wchar_t			wszIP[4][16];						// IP��ַ
	wchar_t			wszAllGroupName[32*18];				// ��Ч�ķ������ƺ��Ƿ�ѡ,��ʽ:[�Ƿ�ѡ][��������]|[�Ƿ�ѡ][��������]...|,����(0����|1����|1����|0����|)(֧��32�����飬ÿ��������Ϣռwchar_t[18])

	_SERVER_PROPERTY()
	{
		memset(this,0,sizeof(_SERVER_PROPERTY));
		cbSize = sizeof(_SERVER_PROPERTY);
		dwFlags = BTS_FLAGS_32[4];
	}
}SERVER_PROPERTY;
//��������
typedef struct _COMPUTER_ID
{
	DWORD			dwComputerID;						// ��������
}COMPUTER_ID;
//���������
typedef struct _COMPUTER_NAME
{
	wchar_t			wszComputerName[32];				// �������
}COMPUTER_NAME;
//����ʱ����Ϣ
typedef struct _LIMIT_TIME_PERIOD_INFO
{
	int			iMode;									//0:���� 1:���� 2:��ֹ
	DWORD		dwDownloadSpeed;						//�����ٶ�(��λKB/s)
	DWORD		dwUploadSpeed;							//�ϴ��ٶ�(��λKB/s)
}LIMIT_TIME_PERIOD_INFO;
/////////////////////////////////////////////////////////////////////////////////////////////
//����������Ϸ��Դ�������ݽṹ

//��ȡ��Ϸ��λ��Ϣ
typedef struct _GET_GAME_LOCATE_INFO
{
	BOOL			bSuccess;
	DWORD			dwID;
	wchar_t			wszGameName[32];
}GET_GAME_LOCATE_INFO;

//��ȡ��Ϸ�ĸ���״̬����ṹ
typedef struct _GET_GAME_LOCATE_STATUS_REQUEST
{
	int				iMode;								// (0:�Զ� 1:ǿ���и��� 2:ǿ���Ѹ���)
	DWORD			dwID;
	wchar_t			 wszDirectory[128];
}GET_GAME_LOCATE_STATUS_REQUEST;
//��ȡ��Ϸ�ĸ���״̬�𸴽ṹ
typedef struct _GET_GAME_LOCATE_STATUS_REPLY
{
	int				 iFlag;
}GET_GAME_LOCATE_STATUS_REPLY;
//������Ϸ��λ��Ϣ
typedef struct _SET_GAME_LOCATE_INFO
{
	DWORD			dwID;								// ���
	int				iFlag;								// (1:�и��� 2:�Ѹ���)
	wchar_t			wszDirectory[128];
}SET_GAME_LOCATE_INFO;

//��ȡ��Ϸ������Ϣ
typedef struct _SEARCH_INFO
{
	DWORD		cbSize;
	DWORD		dwFlags;

	DWORD		dwGameId;								// ��Ϸ���(0:δ��λ)
	DWORD		dwMode;									// ģʽ(0x01:wmblive.idxƥ��,0x02:Ŀ¼����Ŀ¼��ƥ�� 0x04:Ŀ¼������Ϸ��ƥ�� 0x08:�ؼ���ƥ�� 0x10:ִ���ļ�ƥ�� 0x20:��Ŀ¼
	wchar_t		wszLocalDirectory[128];					// ����Ŀ¼·��
	wchar_t		wszGameText[32];						// ��Ϸ����
	wchar_t		wszDirectoryName[32];					// ����Ŀ¼��

	_SEARCH_INFO()
	{
		memset(this,0,sizeof(_SEARCH_INFO));
		cbSize = sizeof(_SEARCH_INFO);
		dwFlags = BTS_FLAGS_32[5];
	}

}SEARCH_INFO;

#pragma pack(pop)

//----------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------����-----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------------------------

#include "MZD_INI.h"

typedef BOOL	(WINAPI* _btcInitConnect)(wchar_t* pwszIP,wchar_t* pwszPassword);	//��ʼ����������IP������
typedef DWORD   (WINAPI* _btcSendCommand)(const UINT iCommand,const char* pszInIni,const int iInIniSize,char** pszOutIni,int* pOutCount, int* pOutSize);		

typedef DWORD	(WINAPI* _btcGetFlags)(int iCount);
typedef BOOL	(WINAPI* _btcSockInitial)();
typedef int		(WINAPI* _btcSockRelease)();
//typedef BOOL	(WINAPI* _btcInitConnect)(wchar_t* pwszIP,wchar_t* pwszPassword);										//��ʼ������
typedef void	(WINAPI* _btcReleaseEx)(char* pByte);																	//ͳһ�ӿ��ͷ��ڴ�
//--------------
typedef int		(WINAPI* _btcConnectServ)();																			//����BT����
typedef int		(WINAPI* _btcUILogin)(UI_LOGING_USERPSW* pUilup,UI_LOGIN_REPLY* pUilr);									//UI��¼
typedef int		(WINAPI* _btcGetLoginInfo)(UI_LOGIN_REPLY* pUilr);														//��ȡUI��¼��Ϣ
typedef int		(WINAPI* _btcSetConnectPassword)(wchar_t* pwszNewPassword);												//������������
typedef int		(WINAPI* _btcSyncData)();																				//ͬ������
typedef int		(WINAPI* _btcGetSyncProgress)(SYNC_DATA_PROGRESS* pSyncProgress);										//��ȡͬ������
typedef int		(WINAPI* _btcGetServerWorkStatus)(DWORD* pdwSrvWorkStatus);												//��ȡBT������״̬
typedef int		(WINAPI* _btcGetBtConfig)(BT_CONFIG_INFO* pBtConfig);													//��ȡBT���û���
typedef int		(WINAPI* _btcSetBtConfig)(BT_CONFIG_INFO* pBtConfig);													//����BT���û���
typedef int		(WINAPI* _btcGetMenuConfig)(MENU_CONFIG* pMenuConfig);													//��ȡ�˵����û���
typedef int		(WINAPI* _btcSetMenuConfig)(MENU_CONFIG* pMenuConfig);													//���ò˵����û���
typedef int     (WINAPI* _btcGetLimitTimePeriodInfo)(LIMIT_TIME_PERIOD_INFO* pLimitTPI);								//��ȡ����ʱ����Ϣ
typedef int		(WINAPI* _btcClearBtRegInfo)();																			//���BTע����Ϣ
//--------------
typedef int		(WINAPI* _btcGetGamesInfo)(RESOURCE_INFO** pRi,COMMAND_PARAM* pCp,int* piCount);						//��ȡ��Ϸ��Ϣ		
typedef int		(WINAPI* _btcGetGamesInfo_1)(char** pResultBuff,COMMAND_PARAM* pCp,int* piResultCount);

typedef void    (WINAPI* _btcReleaseGamesInfo)(RESOURCE_INFO** pRi);													//�ͷŸ���Ϸ��Ϣ
typedef int		(WINAPI* _btcGetWgsInfo)(T_WgsInfo** pWi,int* piCount);													//��ȡ����������Ϣ
typedef void    (WINAPI* _btcReleaseWgsInfo)(T_WgsInfo** pWi);															//�ͷŸ���������Ϣ
typedef int		(WINAPI* _btcGetParentClassInfo)(T_ClassInfo** pPci,int* piCount);										//��ȡ�˵�������Ϣ
typedef void    (WINAPI* _btcReleaseParentClassInfo)(T_ClassInfo** pPci);												//�ͷŲ˵�������Ϣ
typedef int		(WINAPI* _btcGetSubClassInfo)(T_ClassInfo** pSci,int* piCount);											//��ȡ�˵�С����Ϣ
typedef void    (WINAPI* _btcReleaseSubClassInfo)(T_ClassInfo** pPci);													//�ͷŲ˵�С����Ϣ
typedef int		(WINAPI* _btcGetMovieInfo)(T_Movie** pMi,int* piCount);													//��ȡT_MovieInfo����
typedef void    (WINAPI* _btcReleaseMovieInfo)(T_Movie** pMi);															//�ͷ�T_MovieInfo����
typedef int		(WINAPI* _btcGetOnlineInfo)(T_Online** pOi,int* piCount);												//��ȡT_Online����	
typedef void    (WINAPI* _btcReleaseOnlineInfo)(T_Online** pOi);														//�ͷ�T_Online����
typedef int		(WINAPI* _btcGetPlayerListInfo)(T_PlayerList** pPli,int* piCount);										//��ȡT_Player����		
typedef void    (WINAPI* _btcReleasePlayerListInfo)(T_PlayerList** pPli);												//�ͷ�T_Player����
typedef int     (WINAPI* _btcGetSingleGameInfo)(RESOURCE_INFO* pRi);													//��ȡ������Ϸ��Դ��Ϣ
//
typedef int		(WINAPI* _btcSetParentClassInfo)(T_ClassInfo** pCi,int* piCount);										//����T_ParentClass��������
typedef int		(WINAPI* _btcSetSubClassInfo)(T_ClassInfo** pCi,int* piCount);											//����T_SubClassС������
typedef int		(WINAPI* _btcSetMovieInfo)(T_Movie** pMi,int* piCount);													//����T_MovieInfo����
typedef int		(WINAPI* _btcSetOnlineInfo)(T_Online** pOi,int* piCount);												//����T_Online����
typedef int		(WINAPI* _btcSetPlayerListInfo)(T_PlayerList** pPli,int* piCount);										//����T_Player����
//--------------������Ϸ��Դ���á�����ָ��
typedef int		(WINAPI* _btcGameGetSuperfluousInfo)(RESOURCE_INFO** pRi,int* piCount);									//��ȡ�������ֹͣ���µ���Դ����
typedef void	(WINAPI* _btcReleaseGameSuperfluousInfo)(RESOURCE_INFO** pRi);											//�ͷŶ������ֹͣ���µ���Դ����
typedef int		(WINAPI* _btcGameGetDeleteSort)(GAME_DELETE_SORT** pGds,int* piCount);									//��ȡ��Ϸɾ��˳������
typedef void	(WINAPI* _btcReleaseGameDeleteSort)(GAME_DELETE_SORT** pGds);											//�ͷ���Ϸɾ��˳������
typedef int		(WINAPI* _btcGetSimpleProperty)(GET_GAME_SIMPLE_PROPERTY* pgetGsp);										//��ȡָ����Դ�ļ�����
typedef int		(WINAPI* _btcSetSimpleProperty)(SET_GAME_SIMPLE_PROPERTY* psetGsp);										//����ָ����Դ�ļ�����
typedef int		(WINAPI* _btcGetBtSystemInfo)(BT_SYSTEM_INFO* pBtSi);													//��ȡBTϵͳ�ſ���Ϣ
typedef int		(WINAPI* _btcGetResourceNumber)(BT_RESOURCE_NUMBER* pBtRn);												//��ȡ��Դ��
typedef int		(WINAPI* _btcGameDelete)(DWORD dwGameId);																//ɾ����Դ
typedef int		(WINAPI* _btcGameClearFileDir)(DWORD dwGameId);															//��������ļ�Ŀ¼	
typedef int		(WINAPI* _btcGameMoveDirectory)(GAME_MOVE_DIRECTORY* pGmd);												//�ƶ���ϷĿ¼
typedef int		(WINAPI* _btcGameRepair)(DWORD dwGameId);																//��Ϸ�޸�
typedef int		(WINAPI* _btcGameSetAutoUpdate)(DWORD dwGameId);														//��Դ�����Զ����·�ʽ
typedef int		(WINAPI* _btcGameSetManualUpdate)(DWORD dwGameId);														//��Դ�����ֶ����·�ʽ
//--------------�Զ�����Ϸ��Դ����ָ��
typedef int		(WINAPI* _btcAddCustomGame)(RESOURCE_PROPERTY* pRp);													//����Զ�����Ϸ��Դ
typedef int		(WINAPI* _btcAddCustomWeb)(RESOURCE_PROPERTY* pRp);														//����Զ���WEB��Դ
typedef int		(WINAPI* _btcGetCustomGameMaxId)(DWORD* pdwMaxID);														//�Զ���ȡ����Զ�����Ϸ���
typedef int		(WINAPI* _btcGetCustomGameProperty)(DWORD dwGameId,RESOURCE_PROPERTY* pRp);								//��ȡ�Զ�����Ϸ����
typedef int		(WINAPI* _btcModifyCustomGameProperty)(RESOURCE_PROPERTY* pRp);											//�޸��Զ�����Ϸ����
typedef int		(WINAPI* _btcDeleteCustomGame)(DWORD dwGameId);															//ɾ���Զ�����Ϸ
//--------------Task����ָ��
typedef int		(WINAPI* _btcGetTaskInfo)(TASK_INFO** pTask,int* piCount);												//��ȡ���л������Ϣ
typedef void	(WINAPI* _btcReleaseTaskInfo)(TASK_INFO** pTask);														//�ͷ����л������Ϣ
typedef int		(WINAPI* _btcTaskGetTrackerInfo)(DWORD dwID,PACK_TRACKER_INFO_ENTRY* pTie);								//��ȡָ�������Tracker��Ϣ
typedef int		(WINAPI* _btcTaskGetPeerInfo)(DWORD dwID,PACK_PEER_INFO_ENTRY** pPie,int* piCount);						//��ȡָ������Ľڵ���Ϣ
typedef void	(WINAPI* _btcReleaseTaskPeerInfo)(TASK_INFO** pPie);													//�ͷ�ָ������Ľڵ���Ϣ
typedef int		(WINAPI* _btcTaskAddDownload)(DWORD dwID);																//���һ����������
typedef int		(WINAPI* _btcTaskSSDDownload)(DWORD dwID);																//SSD���̷�ʽ����
typedef	int		(WINAPI* _btcTaskPropertyDownload)(SET_GAME_SIMPLE_PROPERTY* psetGsp);									//���Է�ʽ�������
typedef	int		(WINAPI* _btcTaskAddSeed)(TASK_SEED_DATA* pTsd);														//���һ����������
typedef int		(WINAPI* _btcTaskAddSeedSource)(ADD_SEED_SOURCE* pAss);													//��ָ���������һ����Դ
typedef int		(WINAPI* _btcTaskStart)(DWORD dwID);																	//��ʼ����
typedef int		(WINAPI* _btcTaskStop)(DWORD dwID);																		//ֹͣ����
typedef int		(WINAPI* _btcTaskCheck)(DWORD dwID);																	//�������
typedef int		(WINAPI* _btcTaskRemove)(DWORD dwID);																	//�Ƴ�����
typedef int		(WINAPI* _btcTaskTop)(DWORD dwID);																		//�����ö�
typedef int		(WINAPI* _btcTaskUp)(DWORD dwID);																		//��������
typedef int		(WINAPI* _btcTaskDown)(DWORD dwID);																		//��������
typedef int		(WINAPI* _btcTaskLimitSpeed)(DWORD dwID);																//���������ٶ�
typedef int		(WINAPI* _btcTaskSort)(DWORD dwID);																		//��������
typedef int		(WINAPI* _btcTaskRefreshTracker)(DWORD dwID);															//����ǿ������һ��
//--------------���顢����վ��������
typedef int		(WINAPI* _btcInsertGroup)(BT_GROUP_NAME* pInstGroup);													//���һ��������Ϣ
typedef int		(WINAPI* _btcModifyGroup)(MODIFY_GROUP_NAME* pModGroup);												//�޸�һ��������Ϣ
typedef int		(WINAPI* _btcDeleteGroup)(BT_GROUP_NAME* pDelGroup);													//ɾ��һ��������Ϣ
typedef int		(WINAPI* _btcGetGroupInfo)(GroupInfo* pAllGi);															//��ȡ���з�����Ϣ
typedef int		(WINAPI* _btcGetWorkstationInfo)(T_WorkstationInfo** pWk,BT_GROUP_NAME gn,int* piCount);				//��ȡָ�������еĹ���վ��Ϣ	
typedef void    (WINAPI* _btcReleaseWorkstationInfo)(T_WorkstationInfo** pWk);											//�ͷ�ָ�������еĹ���վ��Ϣ
typedef int		(WINAPI* _btcGetServerInfo)(T_ServerInfo** pSrv,BT_GROUP_NAME gn,int* piCount);							//��ȡָ�������еķ�������Ϣ
typedef void    (WINAPI* _btcReleaseServerInfo)(T_ServerInfo** pSrv);													//�ͷ�ָ�������еķ�������Ϣ
typedef int		(WINAPI* _btcDeleteWorkstation)(COMPUTER_ID ci);														//ɾ��һ̨����վ
typedef int		(WINAPI* _btcDeleteServer)(COMPUTER_NAME cn);															//ɾ��һ̨������
typedef int		(WINAPI* _btcGetWorkstationProperty)(WORKSTATION_PROPERTY* pWkp);										//��ȡһ̨����վ����
typedef int		(WINAPI* _btcSetWorkstationProperty)(WORKSTATION_PROPERTY* pWkp);										//����һ̨����վ����(���û���ҵ���Ӧ�Ĺ���վ�����¼�)
typedef int		(WINAPI* _btcGetServerProperty)(SERVER_PROPERTY* pSrvp);												//��ȡһ̨����������
typedef int		(WINAPI* _btcSetServerProperty)(SERVER_PROPERTY* pSrvp);												//����һ̨����������(���û���ҵ���Ӧ�ķ����������¼�)
typedef int		(WINAPI* _btcSyncMzdWorkstation)();																		//ͬ��MZD����վ��Ϣ
typedef int		(WINAPI* _btcSyncMzdServer)();																			//ͬ��MZD��������Ϣ
//--------------����Ŀ¼����ָ��
typedef int		(WINAPI* _btcGetDiskInfo)(DISK_INFO** pDi,int* piCount);												//��ȡ������Ϣ
typedef	void	(WINAPI* _btcReleaseDiskInfo)(DISK_INFO** pDi);															//�ͷŴ�����Ϣ
typedef int		(WINAPI* _btcGetFileDirectoryInfo)(wchar_t* pwszPath,FILE_DIRECTORY_INFO** pFdi,int* piCount);			//��ȡ�ļ�Ŀ¼��Ϣ
typedef void	(WINAPI* _btcReleaseDirectoryInfo)(FILE_DIRECTORY_INFO** pFdi);											//�ͷ��ļ�Ŀ¼��Ϣ
typedef int		(WINAPI* _btcGetFileDirectoryProperty)(wchar_t* pwszPath,FILE_DIRECTORY_PROPERTY* pFdp);				//��ȡ�ļ�Ŀ¼����
typedef int		(WINAPI* _btcGetDirectorySize)(wchar_t* pwszDisk,__int64* pDiskSize);									//��ȡĿ¼��С(��λByte��

//----------��Դ������λ����ָ��
typedef int		(WINAPI* _btcStartSearch)(wchar_t* pSearchParentDirectory);												//��ʼ��Ϸ��λ����	
typedef int		(WINAPI* _btcStopSearch)();																				//������Ϸ��λ����
typedef int		(WINAPI* _btcCoverLocate)();																			//���Ƿ�ʽ��λ				
//pli:			���ض�λ�ľ�����ϢSEARCH_INFO
typedef int		(WINAPI* _btcGetLocate)(SEARCH_INFO** pSearchInfo,int* piCount);												//��ȡ��Ϸ��λ��Ϣ
typedef int		(WINAPI* _btcGetLocateStatus)(GET_GAME_LOCATE_STATUS_REQUEST* pRequest,GET_GAME_LOCATE_STATUS_REPLY* pReply);	//��ȡ��Ϸ��λ״̬
typedef int		(WINAPI* _btcSetLocate)(SET_GAME_LOCATE_INFO* pSet);													//������Ϸ��λ��Ϣ
#endif