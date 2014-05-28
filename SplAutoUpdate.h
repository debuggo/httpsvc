#pragma once
 
using namespace std;

#pragma pack(push)
#pragma pack(1)
typedef struct tagUpdateParam
{
	HINSTANCE hInst;  //�����������ģ��ʵ�����(�����ڲ�ͨ����������λ������ģ��·��) ������÷��Ǹ�exe,��NULL����
	bool bNotify;     //����ǰ�Ƿ��������ʾ ������������false
	bool bWait;       //���������Ƿ�ȴ������߳̽����ŷ��� ������������false
	bool bLibray;     //�ⷽʽ���� ����������true

	WORD wPort;       //�����port �ṩ���ͻ�����������

	WCHAR pName[32];  //��Ʒ����  ��:GWSERVER(����������,Ҫ��л��Э��)
	WCHAR pVer[32];   //��Ʒ�汾  ��:201111151516(Ҫ��л��Э��)     //������Բ���
	WCHAR pType[12];  //��Ʒ����  ��:GW(������ϵͳ,Ҫ�ͷ�ʽ��Э��) 

    WCHAR pServer[50];  //������������ַ��Ĭ��Ϊls.w918.com
	WCHAR pMzp[32];   //ͨ��֤�˺�  �ͻ��˿ɲ���
	WCHAR pPwd[32];   //ͨ��֤����   �ͻ��˿ɲ���

	WCHAR pCName[32]; //�ͻ���Ʒ����  ��:GWCLIENT(������ͻ���,Ҫ��л��Э��)
	WCHAR pCVer[32];  //�ͻ���Ʒ�汾  ��:20111013(Ҫ��л��Э��)

    bool bService;    //�Ƿ�������(���������������EXE�������dll��������Ҫ��true)
    WCHAR pServiceName[32];  //��������(bService=trueʱ��Ҫ�����������е�����)
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

//֮���Կͻ��˺ͷ�����������ṹ��, ��Ϊ�˷�ֹʹ���������ò���ʱ�ε�
typedef struct tagUpdateParamClient
{
	HINSTANCE hInst;  //�����������ģ��ʵ�����(�����ڲ�ͨ����������λ������ģ��·��) ������÷��Ǹ�exe,��NULL����
	bool bProxy;      //ͨ�����������������true,ֱ��������ʦ��վ��������false
	bool bNotify;     //����ǰ�Ƿ��������ʾ ������������false
	bool bWait;       //���������Ƿ�ȴ������߳̽����ŷ��� ������������false
	bool bLibray;     //�ⷽʽ���� ����������true

	WCHAR pName[32];  //��Ʒ����  ��:GWSERVER(����������,Ҫ��л��Э��)
	WCHAR pVer[32];   //��Ʒ�汾  ��:201111151516(Ҫ��л��Э��)    //������Բ���
	WCHAR pType[12];  //��Ʒ����  ��:GW(������ϵͳ,Ҫ�ͷ�ʽ��Э��)

    WCHAR pServer[50];  //������������ַ��Ĭ��Ϊls.w918.com
	WCHAR pMzp[32];   //ͨ��֤�˺� bProxy=falseʱ��Ҫ��
	WCHAR pPwd[32];   //ͨ��֤���� bProxy=falseʱ��Ҫ��

	WORD wProxyPort;       //������������port bProxy=trueʱ��Ҫ��
	WCHAR pProxyIp[16];    //������������ip  ��:192.168.157.163 bProxy=trueʱ��Ҫ��

    bool bService;    //�Ƿ�������(��������������Ƿ������dll��������Ҫ��true)
    WCHAR pServiceName[32];  //��������(bService=trueʱ��Ҫ�����������е�����)
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
}UPDATEPARAMCLIENT;	//�ͻ��������ṹ

//ȫ�µ��Զ��������õĲ���
typedef struct tagNewUpdateParam
{
	bool bClient;     //�Ƿ��ǿͻ��� false=�ͻ��� true=�����
	bool bWait;       //���������Ƿ�ȴ������߳̽����ŷ��� ������������false
	WCHAR pVer[32];   //��Ʒ�汾  ��:201111151516

	WCHAR szXml[MAX_PATH];   //���������XML�ļ� //�����(bClient = falseʱ)��Ҫ��

	WORD wPort;       //Ҫ���ӵ�������������port �ͻ���(bClient=trueʱ)���ķ������port��  
	WCHAR pIp[16];    //Ҫ���ӵ�������������ip  ��:192.168.157.163 �ͻ���(bClient=trueʱ)���ķ������IP
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

//ȫ�µ��Զ�������
HANDLE NewUpdate(tagNewUpdateParam tag);
DWORD GetFileCRC32(LPCWSTR ptsFile);

//�Զ�������
class CAtuoUpdate
{
// ����
public:
	CAtuoUpdate(HWND pParent = NULL);	// ��׼���캯��
	virtual ~CAtuoUpdate()              //����
	{  
		//delete Instance();  
	}   
public:  //����
 	static CAtuoUpdate*  Instance(void);

	//�����
	BOOL StartUpdate(UPDATEPARAM param);
	//�ͻ���
	BOOL StartUpdateClient(UPDATEPARAMCLIENT param);

	////һ���������� bNotify=true ��������ʾ���� bNotify=false ��Ĭ����
	//BOOL StartUpdate(LPCWSTR lpMzp, LPCWSTR lpPwd, LPCWSTR lpProductType, LPCWSTR lpProductName, LPCWSTR lpProductVer, bool bWait, bool bNotify = true);
	////���������
	//BOOL StartUpdateProxy(LPCWSTR lpMzp, LPCWSTR lpPwd, WORD port, LPCWSTR lpProductType, LPCWSTR lpProductName, LPCWSTR lpProductVer,  LPCWSTR lpCProductName, LPCWSTR lpCProductVer, bool bWait);

	////�����ͻ���
	//BOOL StartUpdateProxy(LPCWSTR lpIp, WORD port, LPCWSTR lpProductType, LPCWSTR lpProductName, LPCWSTR lpProductVer, bool bWait);

	//����������������汾��  һ������벻Ҫ����
	void SetUpdaterVer(LPCSTR lpVer);
	//ȡ�����߳̾��(������ģʽʹ��)
	HANDLE GetUpdateThread() {return m_hThread;}
	//��������
	void UnInit();

    //������ṩ��wmbsvc.dll�õģ��벻Ҫ����ʹ��
	static int ShellUpdate(wstring packagePath, bool bLibrary, HINSTANCE hUpdateMod, bool bService, TCHAR* pServerName, LPCTSTR pRegName);
private:  //˽��
	static unsigned __stdcall UpdateThreadProc(void* pParam);
	int UpdateSelf(void);
	int UpdateProduct(void);
	int UpdateThead();

	int UpdateProductByProxy(void);
    static int StartMainProcess(wstring processname,bool bStart);
	int UpdateSelfByProxy(void);

	HANDLE m_hThread;
	DWORD m_dwLoginTime;  //�������ʱ��
};

//ȡ�������Ӧ���ļ��汾��
extern BOOL GetFileVersion(HINSTANCE hInst, string& strVersion);

//�汾�Ƚ�
//Ŀǰ��֧��201205061213�����Ĵ����ְ汾 
//�°汾�ȵ�ǰ�汾�·���true, �汾�ɻ�����ȷ���false
extern bool CompareVersion(wstring strNewVer, string strCurVer);
