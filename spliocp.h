#ifdef SPLIOCP_EXPORTS
#define SPLIOCP_API __declspec(dllexport)
#else
#define SPLIOCP_API __declspec(dllimport)
#endif

//IOCP�������ݻص��������� ����ֵ��ʱ���� ��������Ϊsocket, ��������ָ�룬�������ݳ��ȣ� �ص������Զ������
typedef int __stdcall IocpListenCallBack(SOCKET sClient, char * pData, unsigned long DataLength, LPVOID lpParam);

//IOCP���ӳɹ��Ļص��������� ����ֵ��ʱ���� ��������Ϊsocket, IOCP����״̬������״̬(һ��ΪTRUE)�� �ص������Զ������
typedef int __stdcall IocpConnectCallBack(SOCKET sClient, BOOL* pbIocpRun, BOOL* pbConnected, LPVOID lpParam);

#pragma pack(push)
#pragma pack(1)
struct tagIocpData
{
	HANDLE m_hIocp;         				  //IOCP��� ���Ķ���
	HANDLE m_hConnect;      				  //���ӳɹ�ʧ�ܾ��  ��������ʱ��Ч
	BOOL m_bIocpRun;        				  //IOCP�Ƿ����ڹ���  ѭ����ֹ����
	BOOL m_bConnected;      				  //IOCP�Ƿ����ӳɹ�  ��������ʱ��Ч
	SOCKET m_sock1;                           //�˿�1���         ��������ʱ��Ч
	SOCKET m_sock2;                           //�˿�2���         ��������ʱ��Ч
	//����Ϊ��������

	//����Ϊ�������
	WORD iSvrPort1;       					  //�˿�1 ��0ʱ�����˿�1 �������
	WORD iSvrPort2;       					  //�˿�2 ��0ʱ�����˿�2 �������
	int nRecvTimeOut;                         //���ճ�ʱ
	int nSendTimeOut;                         //���ͳ�ʱ

	IocpListenCallBack* m_pProcessRecvData;   //�������ݵĻص����� �������
	IocpConnectCallBack* m_pProc;			  //���ӳɹ��Ļص����� ������� ��������ʱ��Ч
	LPVOID m_lpVoid;						  //IOCP�������Զ������(���ڴ����ص�������) �������

	LPSTR szUrl;                              //Ҫ���ӵ���������ip ��������ʱ��Ч
	WORD iUrlPort;                            //Ҫ���ӵ�IP�Ķ˿� ��������ʱ��Ч
	WORD wThreadNum;                         //�����߳����� Ϊ0ʱȡCPU������*2(dwNumberOfProcessors*2)
public:
	tagIocpData()
	{
		m_hIocp = NULL;
		m_hConnect = INVALID_HANDLE_VALUE;
        m_bIocpRun = FALSE;
        m_bConnected = FALSE;
        m_sock1 = INVALID_SOCKET;
        m_sock2 = INVALID_SOCKET;

		iSvrPort1 = 0;
		iSvrPort2 = 0;
		nRecvTimeOut = 10000;
		nSendTimeOut = 10000;

		m_pProcessRecvData = NULL;
		m_pProc = NULL;	
        m_lpVoid = NULL;

		szUrl = NULL;
		iUrlPort = 80;
		wThreadNum = 0;
	}
};

typedef enum
{	
    OP_CONNECT,  //������Ϣ
    OP_ACCEPT,   //������Ϣ

    OP_SEND,     //������Ϣ
    OP_RECV,     //������Ϣ
}OPERATION_TYPE;

//��ɶ˿ڽṹ�� sizeС�ˣ������ղ��� 1k=>8k
#define MSGSIZE 8192
typedef struct
{
	WSAOVERLAPPED  overlap;	
	OPERATION_TYPE OperationType;
	SOCKET         sClient;  //socket

	WSABUF         wsabuf;
	char           szMessage[MSGSIZE];
	DWORD          dwByteRecvSend;  //���ͽ��ճ���
	DWORD          Flags;
}PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

#pragma pack(pop)

//IOCP�������
typedef enum
{
    IOCP_OK = 0,            //�ɹ�
    IOCP_ERR_NOIOCP = -1,   //IOCPδ����
    IOCP_ERR_ALIOCP = -2,   //IOCP�Ѵ���
    IOCP_ERR_SOCKET = -3,   //SOCKET����(��Ҫ����WSAGetLastError��ȡ������)
    IOCP_ERR_PARAM = -4,    //��������(�Ƚ���ͳ��)
    IOCP_ERR_PROC = -5,     //�ص���������
    IOCP_ERR_URL = -6,      //URL����
    IOCP_ERR_PORT = -7,     //�󶨶˿ڲ���
    IOCP_ERR_BIND = -8,     //bindʧ��
    IOCP_ERR_LISTEN = -9,   //listenʧ��
    IOCP_ERR_WSA = -10,      //WSAStartupʧ��
    IOCP_ERR_IOCPCR = -11,  //IOCP����ʧ��
    IOCP_ERR_GETPRO = -12,  //��ȡ����ָ��ʧ��
}IOCP_ERROR_CODE;

//����IOCP�����
typedef int(__stdcall *MyStartListen)(tagIocpData* ptag);
//����IOCP�ͻ��� ����IOCP_OK��ʾ�ɹ��� ���򷵻�IOCP_ERROR_CODE����WSAGetLastError
typedef int(__stdcall *MyStartConnect)(tagIocpData* ptag);
//����IOCP
typedef int(__stdcall *MyUnInitIocp)(tagIocpData* ptag);

//һ���ڻص�������ʹ�ã�ע�⣬����ͬ���ķ�����Ϣ�� �����첽�� ����IOCP_OK��ʾ�ɹ��� ���򷵻�IOCP_ERROR_CODE����WSAGetLastError
typedef int(__stdcall *MySendMsg)(SOCKET sClient, char * pData, unsigned long Length);
//һ���ڻص�������ʹ�ã������첽�ķ�����Ϣ  ����IOCP_OK��ʾ�ɹ��� ���򷵻�IOCP_ERROR_CODE����WSAGetLastError
typedef int(__stdcall *MySendMsgAsyn)(SOCKET sClient, char * pData, unsigned long Length);

