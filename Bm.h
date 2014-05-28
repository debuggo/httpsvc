#pragma once
#include "BmTypedef.h"
#include "JsonEx.h"
#include "MzdTypedef.h"
#include "mylog.h"
#include <string>
typedef struct _SignalPack
{
	int iSignalHead;//�ź�ͷ����---ö��SignalOperType
	int iFileSize;//�ļ���С�������ַ��ܳ���
	char szMachineName[64];//��������
	int iCurSendNum;//��η���ʱ�����ͱ��1-N
	BYTE info[1024];//1024
}SignalPack,*pSignalPack;

enum SignalOperType
{
	SH_CYBERCAFE_INFO_REQ  = 13478, //��ȡ����������ļ�/�������ð�
	SH_CYBERCAFE_INFO_RSP,
	SH_DOWNLOAD_DESKTOP_REQ,//���ز˵������
	SH_DOWNLOAD_DESKTOP_RSP,

	SH_CALLBOARD_MODIFY_REQ,//�޸Ĺ����
	SH_CALLBOARD_MODIFY_RSP,

	SH_HARDWARE_INFO_REQ,//�ϴ�Ӳ����Ϣ
	SH_HARDWARE_INFO_RSP,

	SH_GET_HARDWARE_REQ,//�����ɱ�ķҪ������Ӳ����Ϣ
	SH_GET_HARDWARE_RSP,

	SH_GETMZP_INFO_REQ,//�õ�MZP����
	SH_GETMZP_INFO_RSP,

	SH_TRANSFERFILE,//���ļ�
	SH_HTTP_SERVER_COMMAND,//�ܿ����·�������
	SH_MIDDLECTL_LOGIN,

	SH_SERVERHARDWARE_INFO_REQ,//�ϴ�������Ӳ����Ϣ
	SH_SERVERHARDWARE_INFO_RSP,

	SH_UPDATEPACK_REQ,//���°�����  //�ͻ�������clientcfg.ini/clcfg.Ini

	SH_UPDATECFG_REQ,  //13496, �ϴ������ļ� //��������ã��ͻ�������
};

#define SERVER_TCP_PORT	    26504   //��ķ���������ŵ�TCP�˿�
#define SERVER_UDP_PORT 	26504   //��ķ���������ŵ�UDP�˿�
#define MONITOR_UDP_PORT    26505   //��ز鿴�˿��ŵ�UDP�˿�

class	CBm
{
public:
	CBm();
	~CBm();

	int		Init();

	int		GetXmlHardware(TCHAR* pstrFile, Json::Value& stJson);
	int		GetXmlStatus(TCHAR*	pstrPath, Json::Value&	stJson);

	int		GetHardware(CString&	strResult);
	int		GetStatus(CString&	strResult);

	BOOL DeleteWksInfo(std::string wksInfo);
//private:
//	BOOL MyDeleteFile(const CString &strFilePath);

};

////��ʼ��,�����ɱ�ķ��������  dwCount = ��ķ�������� pConfigNamesΪ��ķ������������  dwRefCount = ������������ 
//HRESULT WINAPI InitBmConfig(LPCWSTR lpBmServerIp, DWORD& dwCount, TCHAR** pConfigNames, DWORD& dwRefCount, tagRefConfig* pRefConfig);   
////�������ϴ������ɱ�ķ(���в������������У��ڴ�֮ǰ�������޸Ķ�ֻ�Ǹı����ļ�)
//HRESULT WINAPI UpdateBmConfig(LPCWSTR lpBmServerIp); 
//
////ɾ�������͹�������
//HRESULT WINAPI DelBmRefConfigs(LPCWSTR lpMacName);
////�޸Ĺ������� ��Ҫ�Ƴ����������� lpConfigName��ΪNULL
//HRESULT WINAPI ModBmRefConfigs(LPCWSTR lpMacName, LPCWSTR lpConfigName);
//
////��������
//HRESULT WINAPI AddBmConfigs(LPCWSTR lpConfigName);
////ɾ������
//HRESULT WINAPI DelBmConfigs(LPCWSTR lpConfigName);
////�޸�����
//HRESULT WINAPI ModBmConfigs(LPCWSTR lpConfigName, LPCWSTR lpNewConfigName);
//
////������������ bOpen��ʾ�Ƿ����ø����ã� dwValueΪ�������õ�ֵ
//HRESULT WINAPI GetBmNetControl(LPCWSTR lpConfigName, BOOL& bOpen, DWORD& dwValue);  
////������������� dwValue�������1800
//HRESULT WINAPI SetBmNetControl(LPCWSTR lpConfigName, BOOL bOpen, const DWORD dwValue);  
//
////��÷ֱ�������
//HRESULT WINAPI GetBmDisplay(LPCWSTR lpConfigName, BOOL& bOpen, TCHAR* chValue);  
////���÷ֱ���
//HRESULT WINAPI SetBmDisplay(LPCWSTR lpConfigName, BOOL bOpen, const TCHAR* chValue);  
//
////��ÿ��ٹػ����� 0 = ����; 1 = ����; 2 = ���� 3 = ����
//HRESULT WINAPI GetBmThutdown(LPCWSTR lpConfigName, BOOL& bOpen, int& iValue);  
////���ÿ��ٹػ�
//HRESULT WINAPI SetBmThutdown(LPCWSTR lpConfigName, BOOL bOpen, const int chValue);  
//
////���VNC����(���⣬Ҫ�ر�vnc, bOpen��Ϊtrue, ivalue��Ϊfalse,  ��Ϊvnc�е����⣬ δ���ø����õĻ���Ĭ��Ϊ������)
//HRESULT WINAPI GetBmVnc(LPCWSTR lpConfigName, BOOL& bOpen, int& iValue);  
////����VNC����
//HRESULT WINAPI SetBmVnc(LPCWSTR lpConfigName, BOOL bOpen, const int chValue);  
//
////��ô����ļ�/��������/ӳ���̷�/IPMAC��/���ô���/���ó���/������ַ �����ֱ�Ϊ�������ƣ����ͣ� ����/�ر�,  Դ�ļ��� Ŀ���ļ��� ����
//HRESULT WINAPI GetBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, BOOL& bOpen, TCHAR** chSources, TCHAR** chTargets, int& nCount);  
////���Ӵ����ļ�/��������/ӳ���̷�/IPMAC��/���ô���/���ó���/������ַ
//HRESULT WINAPI AddBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, const TCHAR* chSource, const TCHAR* chTarget);  
////ɾ�������ļ�/��������/ӳ���̷�/IPMAC��/���ô���/���ó���/������ַ
//HRESULT WINAPI DelBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, UINT index);
////�޸Ĵ����ļ�/��������/ӳ���̷�/IPMAC��/���ô���/���ó���/������ַ indexΪ-1ʱ���������ֵ�������޸��б���������Ŀ���/�ر�״̬
//HRESULT WINAPI ModBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, UINT index, BOOL bOpen, TCHAR* chSource, TCHAR* chTarget);
//
//
/////////////�����Ƕ�д��������/��������/��ȫ���õĹ���
////////////////////////////////�����ķָ���////////////////////////////////////////////////////
/////////////�����Ƕ�ȡӲ����Ϣ/�¶���Ϣ�Ĺ���
//HRESULT WINAPI LoadHardwareXmls(HWDATA* pData, DWORD& dwCount);        //��ȡӲ����Ϣ���¶���Ϣ(����Ӳ����Ϣ���¶���Ϣ)
//HRESULT WINAPI InitWarningSets(LPCWSTR lpIp, LPVOID lpCallBack);       //��ʼ������Ԥ��  ����Ϊ��ķ�����IP�ͻص�����
//HRESULT WINAPI StopWarning();                                          //�ر�Ԥ������
//HRESULT WINAPI GetWarningSets(enuHSType nType, int& nValue);           //��ȡԤ��ֵ (����������Ԥ��)
//HRESULT WINAPI SetWarningSets(enuHSType nType, const int nValue);      //����Ԥ��ֵ (����������Ԥ��)






