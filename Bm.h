#pragma once
#include "BmTypedef.h"
#include "JsonEx.h"
#include "MzdTypedef.h"
#include "mylog.h"
#include <string>
#include "IniFile.h"
#include <vector>
#include "Action.h"
typedef struct _SignalPack
{
	int iSignalHead;//信号头类型---枚举SignalOperType
	int iFileSize;//文件大小，或者字符总长度
	char szMachineName[64];//机器名，
	int iCurSendNum;//多次发送时，发送编号1-N
	BYTE info[1024];//1024
}SignalPack,*pSignalPack;

enum SignalOperType
{
	SH_CYBERCAFE_INFO_REQ  = 13478, //获取桌面包配置文件/桌面配置包
	SH_CYBERCAFE_INFO_RSP,
	SH_DOWNLOAD_DESKTOP_REQ,//下载菜单桌面包
	SH_DOWNLOAD_DESKTOP_RSP,

	SH_CALLBOARD_MODIFY_REQ,//修改公告板
	SH_CALLBOARD_MODIFY_RSP,

	SH_HARDWARE_INFO_REQ,//上传硬件信息
	SH_HARDWARE_INFO_RSP,

	SH_GET_HARDWARE_REQ,//总网吧保姆要求上抟硬件信息
	SH_GET_HARDWARE_RSP,

	SH_GETMZP_INFO_REQ,//得到MZP请求
	SH_GETMZP_INFO_RSP,

	SH_TRANSFERFILE,//传文件
	SH_HTTP_SERVER_COMMAND,//总控向下发送命令
	SH_MIDDLECTL_LOGIN,

	SH_SERVERHARDWARE_INFO_REQ,//上传服务器硬件信息
	SH_SERVERHARDWARE_INFO_RSP,

	SH_UPDATEPACK_REQ,//更新包请求  //客户端下载clientcfg.ini/clcfg.Ini

	SH_UPDATECFG_REQ,  //13496, 上传配置文件 //服务端有用，客户端无用
};

#define SERVER_TCP_PORT	    26504   //保姆服务器开放的TCP端口
#define SERVER_UDP_PORT 	26504   //保姆服务器开放的UDP端口
#define MONITOR_UDP_PORT    26505   //监控查看端开放的UDP端口
const string kMonitorPath = "\\Update\\ClientCfg.ini";	//保姆的clientcfg.ini的相对路径

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

	/**
	*清除工作站传入的文件
	*@param wksInfo 工作站编号
	*@return true成功,FALSE失败
	*/
	BOOL DeleteWksInfo(std::string wksInfo);

	/****************************************************************************************************
	* 传入action_type查询在配置文件中存在的监控行为
	*	\param strJson 传入的json请求字符串里面应包含action_type信息
	*	\param strResult 用于返回字符串信息unicode编码
	*	\return 错误信息
	*	\retval true 成功
	*	\retval false 失败,将在strResult中返回错误信息
	****************************************************************************************************/
	bool QueryMonitorAction(CString strJson, CString &strResult);

//private:
//	BOOL MyDeleteFile(const CString &strFilePath);
private:

	/**
	 @fn	CString CBm::GetClientCfgPath();
	
	 @brief	获取ClientCfg.ini的路径.
	
	 @date	8/8/2014
	
	 @return	CString ClientCfg.ini的绝对路径.
	 */

	CString GetClientCfgPath();

	CString GetOperationActionsByType(const int action_type);
	bool GetUnOperationActionsByType(const int action_type);
	bool RefreshAllActions();
	void AddActionToIni(const int action_index, const Action &add_action);
	CString GetJsonStringByType(const int get_how, const int action_type);
	CString GetJsonFromVector(const CString &list_name, std::vector<Action> &actions);
	CIniFile ini_;
	std::vector<Action> actions_;
	std::vector<Action> operation_actions_;
	std::vector<Action> unoperation_actions_;
};

////初始化,从网吧保姆下载配置  dwCount = 保姆配置数量 pConfigNames为保姆配置名称数组  dwRefCount = 关联配置数量 
//HRESULT WINAPI InitBmConfig(LPCWSTR lpBmServerIp, DWORD& dwCount, TCHAR** pConfigNames, DWORD& dwRefCount, tagRefConfig* pRefConfig);   
////将配置上传到网吧保姆(所有操作进行完后进行，在此之前的所有修改都只是改本地文件)
//HRESULT WINAPI UpdateBmConfig(LPCWSTR lpBmServerIp); 
//
////删除机器和关联配置
//HRESULT WINAPI DelBmRefConfigs(LPCWSTR lpMacName);
////修改关联配置 若要移除关联配置则 lpConfigName设为NULL
//HRESULT WINAPI ModBmRefConfigs(LPCWSTR lpMacName, LPCWSTR lpConfigName);
//
////添加配置
//HRESULT WINAPI AddBmConfigs(LPCWSTR lpConfigName);
////删除配置
//HRESULT WINAPI DelBmConfigs(LPCWSTR lpConfigName);
////修改配置
//HRESULT WINAPI ModBmConfigs(LPCWSTR lpConfigName, LPCWSTR lpNewConfigName);
//
////获得网络控制项 bOpen表示是否启用该设置， dwValue为该项设置的值
//HRESULT WINAPI GetBmNetControl(LPCWSTR lpConfigName, BOOL& bOpen, DWORD& dwValue);  
////设置网络控制项 dwValue必须大于1800
//HRESULT WINAPI SetBmNetControl(LPCWSTR lpConfigName, BOOL bOpen, const DWORD dwValue);  
//
////获得分辨率设置
//HRESULT WINAPI GetBmDisplay(LPCWSTR lpConfigName, BOOL& bOpen, TCHAR* chValue);  
////设置分辨率
//HRESULT WINAPI SetBmDisplay(LPCWSTR lpConfigName, BOOL bOpen, const TCHAR* chValue);  
//
////获得快速关机设置 0 = 禁用; 1 = 闪电; 2 = 极速 3 = 快速
//HRESULT WINAPI GetBmThutdown(LPCWSTR lpConfigName, BOOL& bOpen, int& iValue);  
////设置快速关机
//HRESULT WINAPI SetBmThutdown(LPCWSTR lpConfigName, BOOL bOpen, const int chValue);  
//
////获得VNC开关(主意，要关闭vnc, bOpen设为true, ivalue设为false,  因为vnc有点特殊， 未启用该设置的话，默认为开启的)
//HRESULT WINAPI GetBmVnc(LPCWSTR lpConfigName, BOOL& bOpen, int& iValue);  
////设置VNC开关
//HRESULT WINAPI SetBmVnc(LPCWSTR lpConfigName, BOOL bOpen, const int chValue);  
//
////获得传送文件/开机运行/映射盘符/IPMAC绑定/禁用窗口/禁用程序/禁用网址 参数分辨为配置名称，类型， 开启/关闭,  源文件， 目标文件， 数量
//HRESULT WINAPI GetBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, BOOL& bOpen, TCHAR** chSources, TCHAR** chTargets, int& nCount);  
////添加传送文件/开机运行/映射盘符/IPMAC绑定/禁用窗口/禁用程序/禁用网址
//HRESULT WINAPI AddBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, const TCHAR* chSource, const TCHAR* chTarget);  
////删除传送文件/开机运行/映射盘符/IPMAC绑定/禁用窗口/禁用程序/禁用网址
//HRESULT WINAPI DelBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, UINT index);
////修改传送文件/开机运行/映射盘符/IPMAC绑定/禁用窗口/禁用程序/禁用网址 index为-1时，不设具体值，而是修改列表中所有项的开启/关闭状态
//HRESULT WINAPI ModBmDataSets(LPCWSTR lpConfigName, enuBmConfigType enuType, UINT index, BOOL bOpen, TCHAR* chSource, TCHAR* chTarget);
//
//
/////////////以上是读写关联设置/常规设置/安全设置的功能
////////////////////////////////华丽的分割线////////////////////////////////////////////////////
/////////////以下是读取硬件信息/温度信息的功能
//HRESULT WINAPI LoadHardwareXmls(HWDATA* pData, DWORD& dwCount);        //获取硬件信息和温度信息(包含硬件信息和温度信息)
//HRESULT WINAPI InitWarningSets(LPCWSTR lpIp, LPVOID lpCallBack);       //初始化启动预警  参数为保姆服务端IP和回调函数
//HRESULT WINAPI StopWarning();                                          //关闭预警功能
//HRESULT WINAPI GetWarningSets(enuHSType nType, int& nValue);           //读取预警值 (必须先启动预警)
//HRESULT WINAPI SetWarningSets(enuHSType nType, const int nValue);      //设置预警值 (必须先启动预警)







