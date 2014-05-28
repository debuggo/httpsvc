#ifdef SPLIOCP_EXPORTS
#define SPLIOCP_API __declspec(dllexport)
#else
#define SPLIOCP_API __declspec(dllimport)
#endif

//IOCP接收数据回调函数声明 返回值暂时无用 参数依次为socket, 接收数据指针，接收数据长度， 回调函数自定义参数
typedef int __stdcall IocpListenCallBack(SOCKET sClient, char * pData, unsigned long DataLength, LPVOID lpParam);

//IOCP连接成功的回调函数声明 返回值暂时无用 参数依次为socket, IOCP运行状态，连接状态(一般为TRUE)， 回调函数自定义参数
typedef int __stdcall IocpConnectCallBack(SOCKET sClient, BOOL* pbIocpRun, BOOL* pbConnected, LPVOID lpParam);

#pragma pack(push)
#pragma pack(1)
struct tagIocpData
{
	HANDLE m_hIocp;         				  //IOCP句柄 核心对象
	HANDLE m_hConnect;      				  //连接成功失败句柄  主动连接时有效
	BOOL m_bIocpRun;        				  //IOCP是否仍在工作  循环终止条件
	BOOL m_bConnected;      				  //IOCP是否连接成功  主动连接时有效
	SOCKET m_sock1;                           //端口1句柄         监听连接时有效
	SOCKET m_sock2;                           //端口2句柄         监听连接时有效
	//以上为传出参数

	//以下为传入参数
	WORD iSvrPort1;       					  //端口1 非0时开启端口1 传入参数
	WORD iSvrPort2;       					  //端口2 非0时开启端口2 传入参数
	int nRecvTimeOut;                         //接收超时
	int nSendTimeOut;                         //发送超时

	IocpListenCallBack* m_pProcessRecvData;   //接收数据的回调函数 传入参数
	IocpConnectCallBack* m_pProc;			  //连接成功的回调函数 传入参数 主动连接时有效
	LPVOID m_lpVoid;						  //IOCP调用者自定义参数(用于传给回调函数的) 传入参数

	LPSTR szUrl;                              //要连接的域名或者ip 主动连接时有效
	WORD iUrlPort;                            //要连接的IP的端口 主动连接时有效
	WORD wThreadNum;                         //工作线程数量 为0时取CPU核心数*2(dwNumberOfProcessors*2)
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
    OP_CONNECT,  //连接消息
    OP_ACCEPT,   //监听消息

    OP_SEND,     //发送消息
    OP_RECV,     //接收消息
}OPERATION_TYPE;

//完成端口结构体 size小了，可能收不完 1k=>8k
#define MSGSIZE 8192
typedef struct
{
	WSAOVERLAPPED  overlap;	
	OPERATION_TYPE OperationType;
	SOCKET         sClient;  //socket

	WSABUF         wsabuf;
	char           szMessage[MSGSIZE];
	DWORD          dwByteRecvSend;  //发送接收长度
	DWORD          Flags;
}PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

#pragma pack(pop)

//IOCP类错误码
typedef enum
{
    IOCP_OK = 0,            //成功
    IOCP_ERR_NOIOCP = -1,   //IOCP未创建
    IOCP_ERR_ALIOCP = -2,   //IOCP已存在
    IOCP_ERR_SOCKET = -3,   //SOCKET错误(需要调用WSAGetLastError来取错误码)
    IOCP_ERR_PARAM = -4,    //参数不对(比较笼统的)
    IOCP_ERR_PROC = -5,     //回调函数不对
    IOCP_ERR_URL = -6,      //URL不对
    IOCP_ERR_PORT = -7,     //绑定端口不对
    IOCP_ERR_BIND = -8,     //bind失败
    IOCP_ERR_LISTEN = -9,   //listen失败
    IOCP_ERR_WSA = -10,      //WSAStartup失败
    IOCP_ERR_IOCPCR = -11,  //IOCP创建失败
    IOCP_ERR_GETPRO = -12,  //获取函数指针失败
}IOCP_ERROR_CODE;

//启动IOCP服务端
typedef int(__stdcall *MyStartListen)(tagIocpData* ptag);
//启动IOCP客户端 返回IOCP_OK表示成功， 否则返回IOCP_ERROR_CODE或者WSAGetLastError
typedef int(__stdcall *MyStartConnect)(tagIocpData* ptag);
//销毁IOCP
typedef int(__stdcall *MyUnInitIocp)(tagIocpData* ptag);

//一般在回调函数中使用，注意，这是同步的发送消息， 不是异步的 返回IOCP_OK表示成功， 否则返回IOCP_ERROR_CODE或者WSAGetLastError
typedef int(__stdcall *MySendMsg)(SOCKET sClient, char * pData, unsigned long Length);
//一般在回调函数中使用，这是异步的发送消息  返回IOCP_OK表示成功， 否则返回IOCP_ERROR_CODE或者WSAGetLastError
typedef int(__stdcall *MySendMsgAsyn)(SOCKET sClient, char * pData, unsigned long Length);

