#pragma once
 
using namespace std;

#pragma pack(push)
#pragma pack(1)
typedef struct tagUpdateParam
{
	HINSTANCE hInst;  //待升级程序的模块实例句柄(函数内部通过这个句柄定位待升级模块路径) 如果调用方是个exe,填NULL即可
	bool bNotify;     //升级前是否出升级提示 大多数情况请填false
	bool bWait;       //升级函数是否等待升级线程结束才返回 大多数情况请填false
	bool bLibray;     //库方式升级 大多数情况填true

	WORD wPort;       //服务端port 提供给客户端连接升级

	WCHAR pName[32];  //产品名称  例:GWSERVER(代表购物服务端,要和谢敏协商)
	WCHAR pVer[32];   //产品版本  例:201111151516(要和谢敏协商)     //此项可以不填
	WCHAR pType[12];  //产品类型  例:GW(代表购物系统,要和方式义协商) 

    WCHAR pServer[50];  //升级服务器地址，默认为ls.w918.com
	WCHAR pMzp[32];   //通行证账号  客户端可不填
	WCHAR pPwd[32];   //通行证密码   客户端可不填

	WCHAR pCName[32]; //客户产品名称  例:GWCLIENT(代表购物客户端,要和谢敏协商)
	WCHAR pCVer[32];  //客户产品版本  例:20111013(要和谢敏协商)

    bool bService;    //是否服务进程(如果待升级程序是EXE服务或者dll服务则需要填true)
    WCHAR pServiceName[32];  //服务名称(bService=true时需要填，服务管理器中的名称)
public:
	tagUpdateParam()
	{
		hInst = NULL;
		bNotify = false;
		bWait = false;
		bLibray = true;
        bService = false;

		wPort = 21801;

		memset(&pName, 0, sizeof(pName));
		memset(&pVer, 0, sizeof(pVer));
		memset(&pType, 0, sizeof(pType));

        lstrcpyW(pServer, L"ls.w918.com");
		memset(&pMzp, 0, sizeof(pMzp));
		memset(&pPwd, 0, sizeof(pPwd));

		memset(&pCName, 0, sizeof(pCName));
		memset(&pCVer, 0, sizeof(pCVer));
        memset(&pServiceName, 0, sizeof(pServiceName));
	}
}UPDATEPARAM;

//之所以客户端和服务端用两个结构体, 是为了防止使用者在设置参数时晕倒
typedef struct tagUpdateParamClient
{
	HINSTANCE hInst;  //待升级程序的模块实例句柄(函数内部通过这个句柄定位待升级模块路径) 如果调用方是个exe,填NULL即可
	bool bProxy;      //通过服务端来升级则填true,直接连方大师网站升级则填false
	bool bNotify;     //升级前是否出升级提示 大多数情况请填false
	bool bWait;       //升级函数是否等待升级线程结束才返回 大多数情况请填false
	bool bLibray;     //库方式升级 大多数情况填true

	WCHAR pName[32];  //产品名称  例:GWSERVER(代表购物服务端,要和谢敏协商)
	WCHAR pVer[32];   //产品版本  例:201111151516(要和谢敏协商)    //此项可以不填
	WCHAR pType[12];  //产品类型  例:GW(代表购物系统,要和方式义协商)

    WCHAR pServer[50];  //升级服务器地址，默认为ls.w918.com
	WCHAR pMzp[32];   //通行证账号 bProxy=false时需要填
	WCHAR pPwd[32];   //通行证密码 bProxy=false时需要填

	WORD wProxyPort;       //升级代理服务端port bProxy=true时需要填
	WCHAR pProxyIp[16];    //升级代理服务端ip  例:192.168.157.163 bProxy=true时需要填

    bool bService;    //是否服务进程(如果待升级程序是服务或者dll服务则需要填true)
    WCHAR pServiceName[32];  //服务名称(bService=true时需要填，服务管理器中的名称)
public:
	tagUpdateParamClient()
	{
		hInst = NULL;
		bProxy = false;
		bNotify = false;
		bWait = false;
		bLibray = true;
        bService = false;

		memset(&pName, 0, sizeof(pName));
		memset(&pVer, 0, sizeof(pVer));
		memset(&pType, 0, sizeof(pType));

        lstrcpyW(pServer, L"ls.w918.com");
		memset(&pMzp, 0, sizeof(pMzp));
		memset(&pPwd, 0, sizeof(pPwd));

		memset(&pProxyIp, 0, sizeof(pProxyIp));
        memset(&pServiceName, 0, sizeof(pServiceName));
		wProxyPort = 21801;
	}
}UPDATEPARAMCLIENT;	//客户端升级结构

//全新的自动升级类用的参数
typedef struct tagNewUpdateParam
{
	bool bClient;     //是否是客户端 false=客户端 true=服务端
	bool bWait;       //升级函数是否等待升级线程结束才返回 大多数情况请填false
	WCHAR pVer[32];   //产品版本  例:201111151516

	WCHAR szXml[MAX_PATH];   //服务端升级XML文件 //服务端(bClient = false时)需要填

	WORD wPort;       //要连接的升级代理服务端port 客户端(bClient=true时)需填保姆服务器port，  
	WCHAR pIp[16];    //要连接的升级代理服务端ip  例:192.168.157.163 客户端(bClient=true时)需填保姆服务器IP
public:
	tagNewUpdateParam()
	{
		bClient = true;
		bWait = false;
		memset(&pVer, 0, sizeof(pVer));

		memset(&szXml, 0, sizeof(szXml));
		
        wPort = 26504;
		memset(&pIp, 0, sizeof(pIp));
	}
}UPDATEPARAMNEW;
 
#pragma pack(pop)

//全新的自动升级类
HANDLE NewUpdate(tagNewUpdateParam tag);
DWORD GetFileCRC32(LPCWSTR ptsFile);

//自动升级类
class CAtuoUpdate
{
// 构造
public:
	CAtuoUpdate(HWND pParent = NULL);	// 标准构造函数
	virtual ~CAtuoUpdate()              //析构
	{  
		//delete Instance();  
	}   
public:  //公用
 	static CAtuoUpdate*  Instance(void);

	//服务端
	BOOL StartUpdate(UPDATEPARAM param);
	//客户端
	BOOL StartUpdateClient(UPDATEPARAMCLIENT param);

	////一般性质升级 bNotify=true 有升级提示更新 bNotify=false 静默更新
	//BOOL StartUpdate(LPCWSTR lpMzp, LPCWSTR lpPwd, LPCWSTR lpProductType, LPCWSTR lpProductName, LPCWSTR lpProductVer, bool bWait, bool bNotify = true);
	////代理级服务端
	//BOOL StartUpdateProxy(LPCWSTR lpMzp, LPCWSTR lpPwd, WORD port, LPCWSTR lpProductType, LPCWSTR lpProductName, LPCWSTR lpProductVer,  LPCWSTR lpCProductName, LPCWSTR lpCProductVer, bool bWait);

	////代理级客户端
	//BOOL StartUpdateProxy(LPCWSTR lpIp, WORD port, LPCWSTR lpProductType, LPCWSTR lpProductName, LPCWSTR lpProductVer, bool bWait);

	//设置升级程序自身版本号  一般情况请不要调用
	void SetUpdaterVer(LPCSTR lpVer);
	//取升级线程句柄(非阻塞模式使用)
	HANDLE GetUpdateThread() {return m_hThread;}
	//销毁自身
	void UnInit();

    //这个是提供给wmbsvc.dll用的，请不要随意使用
	static int ShellUpdate(wstring packagePath, bool bLibrary, HINSTANCE hUpdateMod, bool bService, TCHAR* pServerName, LPCTSTR pRegName);
private:  //私有
	static unsigned __stdcall UpdateThreadProc(void* pParam);
	int UpdateSelf(void);
	int UpdateProduct(void);
	int UpdateThead();

	int UpdateProductByProxy(void);
    static int StartMainProcess(wstring processname,bool bStart);
	int UpdateSelfByProxy(void);

	HANDLE m_hThread;
	DWORD m_dwLoginTime;  //升级间隔时间
};

//取出句柄对应的文件版本号
extern BOOL GetFileVersion(HINSTANCE hInst, string& strVersion);

//版本比较
//目前仅支持201205061213这样的纯数字版本 
//新版本比当前版本新返回true, 版本旧或者相等返回false
extern bool CompareVersion(wstring strNewVer, string strCurVer);
