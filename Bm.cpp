#pragma once
#include "FQ_Std.h"
#include "Bm.h"
#include "AppMain.h"
#include "ChineseCode.h"
#include "Bt.h"
#include "mylog.h"
#include "MyFileOperating.h"
#include "IniFile.h"
#include <fstream>
enum kGetHow
{
	kOperationAction,
	kUnOperationAction,
	kAllAction
};
const CString kOperationSectionName = _T("System default");
const CString kUnOperationSectionName = _T("UnOperation");
VOID	WINAPI		OrganizeFile(TCHAR*	pstrFile)
{
	HANDLE hFile2 = CreateFile(pstrFile, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (INVALID_HANDLE_VALUE != hFile2)
	{
		DWORD FileLen = GetFileSize(hFile2, NULL);
		BYTE *ReadList = new BYTE [FileLen];

		DWORD dwReadSize = 0;
		if (ReadFile(hFile2, ReadList, FileLen, &dwReadSize, NULL))
		{//如果读文件成功, 则追加入新文件
			CloseHandle(hFile2);

			hFile2 = CreateFile(pstrFile, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if (INVALID_HANDLE_VALUE != hFile2)
			{
				for (UINT j=0;j<FileLen;j++)
				{
					if (ReadList[j]=='&')
					{
						ReadList[j]=' ';
					}
					else if (ReadList[j] < 0x20)   //解决乱码问题
					{
						ReadList[j]=' ';
					}
					else if (ReadList[j] > 0x7f)    //解决乱码问题
					{
						ReadList[j]=' ';
					}
				}
				if (ReadList[0] == '<')
				{
					DWORD dwReadWriteLen = 0;
					WriteFile(hFile2, ReadList, FileLen, &dwReadWriteLen, NULL);
				}
				CloseHandle(hFile2);
			}
			delete [] ReadList;
		}
	}
}

long	WINAPI		GetXmlChildCount(IXMLDOMNode* pXmlNode)
{
	long nCount = 0;
	IXMLDOMNodeList* pXmlList = 0;
	if(pXmlNode->get_childNodes(&pXmlList) == S_OK && pXmlList != 0)
	{
		pXmlList->get_length(&nCount);
		pXmlList->Release();
	}
	return nCount;
}


CBm::CBm()
{

}

CBm::~CBm()
{

}

//获取保姆硬件信息
int		CBm::GetXmlHardware(TCHAR* pstrFile, Json::Value& stJson)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	int nRet = 0;
	IXMLDOMDocument * pXmlDoc = NULL;
	if (CoCreateInstance(CLSID_DOMDocument, 0, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (LPVOID *)&pXmlDoc) == S_OK && pXmlDoc != 0)
	{
		OrganizeFile(pstrFile); //整理乱码

		VARIANT vtXml;
		memset(&vtXml, 0, sizeof(vtXml));
		BSTR pFile = SysAllocString(pstrFile);
		if (pFile != 0)
		{
			vtXml.vt = VT_BSTR;
			vtXml.bstrVal = pFile; VARIANT_BOOL vtBool = 0;
			if (pXmlDoc->load(vtXml, &vtBool) == S_OK && vtBool == VARIANT_TRUE)
			{	// ROOT节点
				IXMLDOMElement * pXmlElement = NULL;
				if (pXmlDoc->get_documentElement(&pXmlElement) == S_OK && pXmlElement != 0)
				{	// 定位到终端节点
					//IXMLDOMNode * pXmlNode = 0;
					//if (pXmlElement->selectSingleNode(L"Terminal", &pXmlNode) == S_OK && pXmlNode != 0)
					//{	// 取得子节点数
					long nCount = GetXmlChildCount(pXmlElement);
					if (nCount >= 0)        //modify by jianglei 支持关掉取硬件信息开关时仍然显示计算机
					{	// 分配内存
						// memset(pData, 0, sizeof(HWDATA) + nCount * sizeof(HWNAME));
						IXMLDOMNamedNodeMap * pXmlMap = 0;
						if (pXmlElement->get_attributes(&pXmlMap) == S_OK && pXmlMap != 0)
						{	// 取得终端属性
							IXMLDOMNode * pXmlClient = 0;
							if (pXmlMap->getNamedItem(L"IsServer", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 是否服务器
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									//pData->dwIsServer = (_wtoi(pValue) == 1 ? 1 : 0);
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["IsServer"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							pXmlClient = 0;
							if (pXmlMap->getNamedItem(L"MAC", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 网卡物理地址
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									//lstrcpy(pData->pwsMac, pValue);
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["MAC"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							pXmlClient = 0;
							if (pXmlMap->getNamedItem(L"PCName", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 计算机名
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									//lstrcpy(pData->pwsComputer, pValue);
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["PCName"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							pXmlClient = 0;
							if (pXmlMap->getNamedItem(L"IP", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// IP
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["IP"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							pXmlClient = 0;
							if (pXmlMap->getNamedItem(L"Time", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 更新时间
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									//lstrcpy(pData->pwsHTime, pValue);
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["Time"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							pXmlMap->Release();
						}
						long	lCount;
						IXMLDOMNodeList * pXmlList = 0;
						if (pXmlElement->get_childNodes(&pXmlList) == S_OK && pXmlList != 0)
						{
							if (pXmlList->get_length(&lCount) == S_OK && lCount > 0)
							{
								for (int i = 0; i < lCount; i++)
								{
									Json::Value	JsonDev;
									IXMLDOMNode * pXmlDev = 0;
									if (pXmlList->get_item(i, &pXmlDev) == S_OK && pXmlDev != 0)
									{
										wchar_t * pName = 0;
										if (pXmlDev->get_nodeName(&pName) == S_OK && pName != 0)
										{
											if (_tcsicmp(pName, L"CPU") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["CPU"] = szBuffer;

													SysFreeString(pValue);
													//pDev->dwType = enuHwCpu;
													//取出CPU的功耗值
													//pDev->dwPower = 0;
												}
											} 
											else if (_tcsicmp(pName, L"Motherboard") == 0)
											{
												//获得主板名字
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["Motherboard"] = szBuffer;

													SysFreeString(pValue);

													//pDev->dwType = enuHwBoard;
													//取出主板的功耗值
													//pDev->dwPower = 0;
												}
											}
											else if (_tcsicmp(pName, L"Bios") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["Bios"] = szBuffer;

													SysFreeString(pValue);

													//pDev->dwType = enuHwBios;
												}
											}
											else if (_tcsicmp(pName, L"DisplayCard") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["DisplayCard"] = szBuffer;

													SysFreeString(pValue);

													//pDev->dwType = enuHwDisplay;

													//取出显卡的功耗值
													//pDev->dwPower = 0;
												}
											}
											else if (_tcsicmp(pName, L"AudioCard") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["AudioCard"] = szBuffer;

													SysFreeString(pValue);
													//pDev->dwType = enuHwAudio;
												}
											}
											else if (_tcsicmp(pName, L"Netcard") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["Netcard"] = szBuffer;

													SysFreeString(pValue);
													//pDev->dwType = enuHwNetCard;
												}
											}
											else if (_tcsicmp(pName, L"Memory") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["Memory"] = szBuffer;

													SysFreeString(pValue);

													//pDev->dwPower = 3;
													//pDev->dwType = enuHwMem;
												}
											}
											else if (_tcsicmp(pName, L"HardDisk") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["HardDisk"] = szBuffer;

													SysFreeString(pValue);

													//pDev->dwType = enuHwHard;

													//取出硬盘的功耗值
													//pDev->dwPower = 0;
												}
											}
											else if (_tcsicmp(pName, L"USB") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["USB"] = szBuffer;

													SysFreeString(pValue);
													//pDev->dwType = enuHwUsb;
												}
											}
											else if (_tcsicmp(pName, L"Monitor") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["Monitor"] = szBuffer;

													SysFreeString(pValue);
													//pDev->dwType = enuHwMonitor;
												}
											}
											else if (_tcsicmp(pName, L"Chipset") == 0)
											{
												BSTR pValue = 0;
												if (pXmlDev->get_text(&pValue) == S_OK && pValue != 0)
												{
													char	szBuffer[1024] = { 0 };
													CChineseCode::UniCodeToAscii(szBuffer,pValue);
													JsonDev["Chipset"] = szBuffer;

													SysFreeString(pValue);
													//pDev->dwType = enuHwChipset;
												}
											}
											stJson["Dev"].append(JsonDev);
											SysFreeString(pName);
										}
										pXmlDev->Release(); 
									}//if xmldev!= 0
								}
							}
						}// if (pData != 0) 
					}//nCount > 0
					pXmlElement->Release();
					pXmlElement = NULL;
				}//get_documentElement
			}//load
			SysFreeString(pFile);
		}//if (pfile)
		pXmlDoc->Release();
		pXmlDoc = NULL;
	}//CoCreateInstance

	int		nIsServer = atoi(stJson["IsServer"].asCString());
	if (!nIsServer)
	{
		CString	strPath = CAppMain::GetAppPath();
		strPath += _T("update\\clcfg.ini");

		char	szPathIni[MAX_PATH] = { 0 };
		CChineseCode::UniCodeToAscii(szPathIni,strPath.GetBuffer());

		WritePrivateProfileStringA(stJson["MAC"].asCString(),"PCNAME",stJson["PCName"].asCString(),szPathIni);

		WritePrivateProfileStringA(stJson["MAC"].asCString(),"IP",stJson["IP"].asCString(),szPathIni);
	}

	//if (pData != 0)
	//{
	//	if (!pData->dwIsServer)
	//	{
	//		//读mac地址
	//		TCHAR clname[80];
	//		wsprintf(clname, _T("%s"), pData->pwsMac);
	//		//拼配置文件路径，
	//		TCHAR cfginifile[MAX_PATH];
	//		wsprintf(cfginifile, _T("%s\\update\\clcfg.ini"), GetAppPath().c_str());
	//		//写入机器名
	//		TCHAR comptname[24];
	//		wsprintf(comptname, _T("%s"), pData->pwsComputer);
	//		WritePrivateProfileString(clname, _T("PCNAME"), comptname, cfginifile);
	//		//写入IP地址
	//		TCHAR ip[100]={0};
	//		wsprintf(ip, _T("%s"), pData->pwsIp);
	//		WritePrivateProfileString(clname, _T("IP"), ip, cfginifile);
	//	}
	//}
	return 0;
}


//连接保姆服务器下载配置文件
VOID	WINAPI		DownLoadConfigFile(DWORD dwServerIp, LPCSTR lpFileName)
{
	SignalPack SendPack,RecvPack;
	SOCKET ms = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	SOCKADDR_IN ClientAddrk;
	ClientAddrk.sin_family = AF_INET;
	ClientAddrk.sin_port = htons(SERVER_TCP_PORT);//45678--SERVER_PORT
	ClientAddrk.sin_addr.S_un.S_addr = dwServerIp;//服务器IP	默认本机

	//设置接收超时
	int nRecvTimeOut = 100;
	setsockopt(ms, SOL_SOCKET, SO_RCVTIMEO, (const char *)&nRecvTimeOut, sizeof(int)); 

	if (SOCKET_ERROR != connect(ms, (SOCKADDR *)&ClientAddrk,sizeof(SOCKADDR)))
	{
		memset(&SendPack,0,sizeof(SignalPack));
		memset(&RecvPack,0,sizeof(SignalPack));
		SendPack.iSignalHead = SH_UPDATEPACK_REQ;
		SendPack.iFileSize = 0;
		SendPack.iCurSendNum = 1;
		lstrcpynA((char *)SendPack.info, lpFileName, sizeof(SendPack.info));
		if (send(ms,(char *)&SendPack, sizeof(SignalPack),0)==sizeof(SignalPack))//发送
		{
			//SendMessage(hWnd, WM_TASK_DO4, 0, 0);
			UINT nSize = 0, nError = 0;
			for (nSize = 0; nSize < sizeof(SignalPack) && nError < 10; )
			{
				int nRetSize = recv(ms, (char *)&RecvPack + nSize,sizeof(SignalPack) - nSize, 0);
				if (nRetSize < 0)
				{
					break;
				}
				else if (nRetSize == 0)
					nError++;
				else
					nError = 0;
				nSize = nSize + nRetSize;
			}
			TCHAR minifile[MAX_PATH]={0};
			wsprintf(minifile,_T("%s\\%S"), CAppMain::GetAppPath().GetBuffer(), lpFileName);
			DeleteFile(minifile);
			if (nSize == sizeof(SignalPack) && RecvPack.iSignalHead == 13490 && RecvPack.iFileSize > 0)
			{
				SetLastError(0);
				HANDLE hFile = CreateFile(minifile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
				if (INVALID_HANDLE_VALUE != hFile)
				{		 
					nError = 0;
					for (nSize = 0; nSize < (UINT)RecvPack.iFileSize && nError < 10; )
					{
						char buff[1024*4]={0};
						int Recvlen=0;
						if((RecvPack.iFileSize-nSize) > (1024*4))
						{
							Recvlen=1024*4;
						}
						else
						{
							Recvlen=RecvPack.iFileSize-nSize;
						}
						int nRetSize = recv(ms, (char *)buff,Recvlen, 0);
						if (nRetSize < 0)
						{
							break;
						}
						else if (nRetSize == 0)
							nError++;
						else
						{
							nError = 0;

							DWORD iReadWriteLen = 0;
							WriteFile(hFile, buff, nRetSize, &iReadWriteLen, NULL);
						}
						nSize = nSize + nRetSize;
					}
					CloseHandle(hFile);
					//SendMessage(hWnd, WM_TASK_RET4, 0, 0);
				}
				else
				{//一般是多线程写文件出错
					DWORD dd = GetLastError();
					dd = dd;
				}	
			}//接收包头正确
			else
			{
				//ATLVERIFY(FALSE);
				DWORD dd = GetLastError();
				dd = dd;
			}
		}//发送成功
	}//连接成功
	else
	{
		DWORD err = GetLastError();
	}
	closesocket(ms);//关闭套接字
}

//从保姆中获取工作站的状态
int		CBm::GetXmlStatus(TCHAR*	pstrPath, Json::Value&	stJson)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	IXMLDOMDocument * pXmlDoc = NULL;
	if (CoCreateInstance(CLSID_DOMDocument, 0, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument, (LPVOID *)&pXmlDoc) == S_OK && pXmlDoc != 0)
	{
		VARIANT vtXml;
		memset(&vtXml, 0, sizeof(vtXml));
		BSTR pFile = SysAllocString(pstrPath);
		if (pFile != 0)
		{
			vtXml.vt = VT_BSTR;
			vtXml.bstrVal = pFile;

			OrganizeFile(pstrPath);

			VARIANT_BOOL vtBool = 0;
			if (pXmlDoc->load(vtXml, &vtBool) == S_OK && vtBool == VARIANT_TRUE)
			{	// ROOT节点
				IXMLDOMElement * pXmlElement = NULL;
				if (pXmlDoc->get_documentElement(&pXmlElement) == S_OK && pXmlElement != 0)
				{	// 定位到终端节点
					//IXMLDOMNode * pXmlNode = NULL;
					//if (pXmlElement->selectSingleNode(L"Terminal", &pXmlNode) == S_OK && pXmlNode != 0)
					//{	// 取得子节点数
					long nCount = GetXmlChildCount(pXmlElement);
					if (nCount > 0)
					{	// 分配内存
						//memset(pStatus,0,(nCount + 4) * sizeof(HWSTATUS));
						IXMLDOMNamedNodeMap * pXmlMap = 0;
						if (pXmlElement->get_attributes(&pXmlMap) == S_OK && pXmlMap != 0)
						{	// 取得终端属性
							IXMLDOMNode * pXmlClient = 0;
							if (pXmlMap->getNamedItem(L"Time", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 更新时间
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["Time"] = szBuffer;

									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							if (pXmlMap->getNamedItem(L"IsServer", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 是否服务器
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["IsServer"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}

							if (pXmlMap->getNamedItem(L"Ver", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// 版本号
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["Ver"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}

							if (pXmlMap->getNamedItem(L"MAC", &pXmlClient) == S_OK && pXmlClient != 0)
							{	// MAC
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["MAC"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							if (pXmlMap->getNamedItem(L"PCName",&pXmlClient) == S_OK && pXmlClient != 0)
							{
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["PCName"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							if (pXmlMap->getNamedItem(L"IP",&pXmlClient) == S_OK && pXmlClient != 0)
							{
								BSTR pValue = 0;
								if (pXmlClient->get_text(&pValue) == S_OK && pValue != 0)
								{
									char	szBuffer[1024] = { 0 };
									CChineseCode::UniCodeToAscii(szBuffer,pValue);
									stJson["IP"] = szBuffer;
									SysFreeString(pValue);
								}
								pXmlClient->Release();
								pXmlClient = NULL;
							}
							pXmlMap->Release();
						}

						IXMLDOMNodeList * pXmlList = 0;
						if (pXmlElement->get_childNodes(&pXmlList) == S_OK && pXmlList != 0)
						{
							long nCount = 0;
							if (pXmlList->get_length(&nCount) == S_OK && nCount > 0)
							{
								for (long i = 0; i < nCount; i++)
								{
									Json::Value	JsonStatus;
									IXMLDOMNode * pXmlDev = 0;
									if (pXmlList->get_item(i, &pXmlDev) == S_OK && pXmlDev != 0)
									{
										wchar_t * pName = 0;
										if (pXmlDev->get_nodeName(&pName) == S_OK && pName != 0)
										{
											if (_wcsicmp(pName, L"Status") == 0)
											{
												IXMLDOMNode * pXmlType = 0;
												IXMLDOMNode * pXmlValue = 0;
												IXMLDOMNode * pXmlOrder = 0;
												IXMLDOMNode * pXmlMaxVal = 0;
												if (pXmlDev->selectSingleNode(L"Type", &pXmlType) == S_OK && pXmlType != 0)
												{	// 更新时间
													wchar_t * pType = 0;
													wchar_t * pOrder = 0;
													if (pXmlType->get_text(&pType) == S_OK && pType != 0)
													{
														if (_wcsicmp(pType, L"MainTemp") == 0)
														{	// 主板温度
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	//lstrcpy(pStatus->pwsValue, pValue);
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["MotherboardTemp"] = szBuffer;
																	SysFreeString(pValue);
																	//pStatus->nType = enuHsBoard;
																}

																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"CpuTemp") == 0)
														{	// CPU温度
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	//lstrcpy(pStatus->pwsValue, pValue);
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["CpuTemp"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsCpuTemp;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"DiskTemp") == 0)
														{	// 磁盘温度
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	//lstrcpy(pStatus->pwsValue, pValue);
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["DiskTemp"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsHardTemp;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"DispTemp") == 0)
														{	// 显卡温度
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["VioeoTemp"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsDisplay;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"MemTemp") == 0)
														{	// 内存温度
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	//lstrcpy(pStatus->pwsValue, pValue);
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["MemoryTemp"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsMemTemp;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"CpuFan") == 0)
														{	// CPU风扇转速
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["CpuFan"] = szBuffer;
																	SysFreeString(pValue);
																	//pStatus->nType = enuHsCpuFan;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"CPU") == 0)
														{	// 处理器占用率
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["CPU"] = szBuffer;
																	SysFreeString(pValue);
																	//pStatus->nType = enuHsCpuUse;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"gcpu") == 0)
														{	// 单核处理器占用率
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["gcpu"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsCpuDUse;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"Disk") == 0)
														{	// 磁盘占用率
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["Disk"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsHardUse;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"Net") == 0)
														{	// 网卡占用率
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["Net"] = szBuffer;
																	SysFreeString(pValue);
																	//pStatus->nType = enuHsNetcard;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"Bandwidth") == 0)
														{	// 网卡带宽
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["Bandwidth"] = szBuffer;
																	SysFreeString(pValue);
																	//pStatus->nType = enuHsNetWidth;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"Mem") == 0)
														{	// 内存占用率
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Order", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = _wtoi(pOrder);
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	char	szBuffer[1024] = { 0 };
																	CChineseCode::UniCodeToAscii(szBuffer,pValue);
																	JsonStatus["Mem"] = szBuffer;

																	SysFreeString(pValue);
																	//pStatus->nType = enuHsMemUse;
																}
																pXmlValue->Release();
															}
														}
														else if (_wcsicmp(pType, L"space") == 0)
														{	// 空间占用率
															if (pXmlDev->selectSingleNode(L"UseValue", &pXmlValue) == S_OK && pXmlValue != 0)
															{
																if (pXmlDev->selectSingleNode(L"Remarks", &pXmlOrder) == S_OK && pXmlOrder != 0)
																{
																	if (pXmlOrder->get_text(&pOrder) == S_OK && pOrder != 0)
																	{
																		//pStatus->dwNum = *pOrder;
																		SysFreeString(pOrder);
																	}
																	pXmlOrder->Release();
																}
																if (pXmlDev->selectSingleNode(L"MaxValue", &pXmlMaxVal) == S_OK && pXmlMaxVal != 0)
																{
																	BSTR pValue = 0;
																	if (pXmlMaxVal->get_text(&pValue) == S_OK && pValue != 0)
																	{
																		//pStatus->stVal.LowPart = _wtoi(pValue);
																		SysFreeString(pValue);
																		//   pStatus->pwsValue = 0;
																	}
																	pXmlMaxVal->Release();
																}
																BSTR pValue = 0;
																if (pXmlValue->get_text(&pValue) == S_OK && pValue != 0)
																{
																	//pStatus->stVal.HighPart = _wtoi(pValue);
																	SysFreeString(pValue);
																	//lstrcpy(pStatus->pwsValue, _T("-1"));
																	//pStatus->nType = enuHsDriverUse;
																}
																pXmlValue->Release();
															}
														}
														SysFreeString(pType);
													}
													pXmlType->Release();
												}
												if(JsonStatus.size() != 0)
												{
													stJson["Status"].append(JsonStatus);
												}
											}
											SysFreeString(pName);
										}
										pXmlDev->Release();
									}

								}
							}
							pXmlList->Release();
						}
					}// if (nCount > 0)
					//    pXmlNode->Release();
					//    pXmlNode = NULL;
					//}//selectSingleNode
					pXmlElement->Release();
					pXmlElement = NULL;
				}//get_documentElement
			}//loadxml
			SysFreeString(pFile);
		} //if (pFile != 0)
		pXmlDoc->Release();
		pXmlDoc = NULL;
	}//cocreate
	return 0;
}


//初始化保姆
int		CBm::Init()
{

	DWORD dwServerIp = inet_addr(CW2A(_T("127.0.0.1"), CP_ACP));	
	ini_.SetPath(GetClientCfgPath());
	DownLoadConfigFile(dwServerIp, "clientcfg.ini");
	DownLoadConfigFile(dwServerIp, "clcfg.ini");

	return 0;
}

int		CBm::GetHardware(CString &strResult)
{
	CAppMain*	pMainApp = CAppMain::GetAppMain();
	Json::Value	JsonRoot;

	CString	strHardwarePath = pMainApp->GetAppPath() + _T("Hardware\\*.*");
	CFileFind	FileFind;
	int iResult = FileFind.FindFile(strHardwarePath.GetBuffer(),0);

	while (iResult)
	{
		Json::Value	JsomValue;
		iResult = FileFind.FindNextFile();

		CString	strFileName = FileFind.GetFileName();
		if (FileFind.IsDots())
		{
			continue;
		}
		if (FileFind.IsDirectory())
		{
			continue;
		}
		if (lstrcmpi(PathFindExtension(strFileName.GetBuffer()),_T(".xm")) == NULL)
		{
			CStringA buf(strFileName.GetBuffer());
			strFileName.ReleaseBuffer();
			string wks_number = buf.Left(buf.Find('.'));
			if(pMainApp->m_Mzd.TheWksIsExist(wks_number))
			{
				//如果存在就显示
				GetXmlHardware(FileFind.GetFilePath().GetBuffer(), JsomValue);
				JsonRoot["Array"].append(JsomValue);
			}
			else
			{
				//如果不存在就删除该文件
				//DeleteFile(FileFind.GetFilePath());
				continue;
			}
		}
	}
	Json::FastWriter	JsonWriter;
	std::string	strData = JsonWriter.write(JsonRoot);
	strResult = strData.c_str();
	return 0;
}

int		CBm::GetStatus(CString &strResult)
{
	CAppMain*	pMainApp = CAppMain::GetAppMain();
	Json::Value	JsonRoot;

	CString	strHardwarePath = pMainApp->GetAppPath() + _T("Hardware\\status\\*.*");

	CFileFind	FileFind;
	int iResult = FileFind.FindFile(strHardwarePath.GetBuffer(),0);

	while (iResult)
	{
		Json::Value	JsomValue;
		iResult = FileFind.FindNextFile();

		CString	strFileName = FileFind.GetFileName();
		if (FileFind.IsDots())
		{
			continue;
		}
		if (FileFind.IsDirectory())
		{
			continue;
		}
		if (lstrcmpi(PathFindExtension(strFileName.GetBuffer()),_T(".xm")) == NULL)
		{

			CStringA buf(strFileName.GetBuffer());
			strFileName.ReleaseBuffer();
			string wks_number = buf.Left(buf.Find('.'));
			if(pMainApp->m_Mzd.TheWksIsExist(wks_number))
			{
				//如果存在就显示
				GetXmlStatus(FileFind.GetFilePath().GetBuffer(), JsomValue);
				JsonRoot["Array"].append(JsomValue);
			}	
			else
			{
				//如果不存在就删除该文件
				//DeleteFile(FileFind.GetFilePath());
				continue;
			}
		}
	}
	Json::FastWriter	JsonWriter;
	std::string	strData = JsonWriter.write(JsonRoot);
	strResult = strData.c_str();
	return 0;
}

BOOL CBm::DeleteWksInfo( std::string wksInfo )
{
	//获取程序运行路径
	CString strAppPath = CAppMain::GetAppPath(); 
	//工作站MAC
	string strWksMac;
	int pos = wksInfo.find("wksMac=") + strlen("wksMac=");
	int npos = wksInfo.find("subMask") - wksInfo.find("wksMac=") - strlen("wksMax=") - 2 ;
	strWksMac = wksInfo.substr(pos, npos);
	//工作站编号
	string strWksNumber;
	pos = wksInfo.find("wksNumber=") + strlen("wksNumber=");
	npos = wksInfo.find("wksName") - wksInfo.find("wksNumber=") - strlen("wksNumber=") - 2;
	strWksNumber = wksInfo.substr(pos, npos);
	//strWksNumber.Format(_T("%d"), strWksNumber);
	//工作站计算机名
	string strWksName;//(wksInfo->wksName);
	pos = wksInfo.find("wksName=") + strlen("wksName=");
	npos = wksInfo.find("wksIp") - wksInfo.find("wksName=") - strlen("wksName=") - 2;
	strWksName = wksInfo.substr(pos, npos);

	//构建需要删除的路径

	//DeleteFile(hwinfo\MAC.dat); 
	CMyFileOperating fileOp;
	CString strBuf;
	strBuf = strWksMac.c_str();
	//CString strDeleteFile = strAppPath + _T("\\hwinfo\\")+ strWksMac + _T(".bat");
	CString strDeleteFile = strAppPath + _T("Hwinfo\\")+ strBuf + _T(".bat");
	fileOp.MyDeleteFile(strDeleteFile);

	//strDeleteFile = strAppPath + _T("\\hwinfo\\")+ strWksMac +_T(".xml");
	strDeleteFile = strAppPath + _T("hwinfo\\")+ strBuf +_T(".xml");
	fileOp.MyDeleteFile(strDeleteFile);

	strBuf = strWksName.c_str();
	//strDeleteFile = strAppPath + _T("\\handware") + _T("\\")+ strWksName + _T(".xm");
	strDeleteFile = strAppPath + _T("Hardware\\") + strBuf + _T(".xm");
	fileOp.MyDeleteFile(strDeleteFile);

	strDeleteFile = strAppPath + _T("Hardware\\") + strBuf + _T(".cy");
	fileOp.MyDeleteFile(strDeleteFile);
	//strDeleteFile = strAppPath + _T("\\handware\\status") + _T("\\")+ strWksName + _T(".xm");
	strDeleteFile = strAppPath + _T("Hardware\\status") + _T("\\")+ strBuf + _T(".xm");
	fileOp.MyDeleteFile(strDeleteFile);

	strDeleteFile = strAppPath + _T("Hardware\\BAT") + _T("\\")+ strBuf + _T(".BAT");
	fileOp.MyDeleteFile(strDeleteFile);

	strBuf = strWksNumber.c_str();
	////strDeleteFile = strAppPath + _T("\\handware") + _T("\\") + wksInfo->wksNumber + _T(".xm");
	//strDeleteFile.Format(_T("%s%s%s%d%s"),strAppPath , _T("\\handware") , _T("\\") , strWksNumber , _T(".xm"));
	strDeleteFile.Format(_T("%s%s%s%s%s"),strAppPath , _T("hardware") , _T("\\") , strBuf , _T(".xm"));
	fileOp.MyDeleteFile(strDeleteFile);

	////strDeleteFile = strAppPath + _T("\\handware") + _T("\\") + wksInfo->wksNumber + _T(".cy");
	//strDeleteFile.Format(_T("%s%s%s%d%s"), strAppPath , _T("\\handware") , _T("\\") , strWksNumber , _T(".cy") );
	strDeleteFile.Format(_T("%s%s%s%s%s"), strAppPath , _T("hardware") , _T("\\") , strBuf , _T(".cy") );
	fileOp.MyDeleteFile(strDeleteFile);


	////strDeleteFile = strAppPath + _T("\\handware\\status") + _T("\\") + strWksNumber + _T(".xm");
	//strDeleteFile.Format(_T("%s%s%s%d%s"), strAppPath , _T("\\handware\\status") , _T("\\") , strWksNumber , _T(".xm") );
	strDeleteFile.Format(_T("%s%s%s%s%s"), strAppPath , _T("hardware\\status") , _T("\\") , strBuf , _T(".xm") );
	fileOp.MyDeleteFile(strDeleteFile);

	////strDeleteFile = strAppPath + _T("\\handware\\bat") + _T("\\") + strWksNumber + _T(".bat");
	//strDeleteFile.Format(_T("%s%s%s%d%s"), strAppPath , _T("\\handware\\bat") , _T("\\") , strWksNumber , _T(".bat") );
	strDeleteFile.Format(_T("%s%s%s%s%s"), strAppPath , _T("hardware\\bat") , _T("\\") , strBuf , _T(".bat") );
	fileOp.MyDeleteFile(strDeleteFile);
	
	return TRUE;
}

bool CBm::QueryMonitorAction(CString strJson, CString &strResult)
{
	Json::Reader object;
	Json::Value root;
	string json = CW2A(strJson);
	if (!object.parse(json, root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR, L"json解析失败.");
		return false;
	}
	Json::Value valuekey = root["action_type"];
	if (valuekey.isNull())
	{
		return false;
	}
	if (valuekey.isInt())
	{
		int action_type = root["action_type"].asInt();
		strResult = GetOperationActionsByType(action_type);
	}
	return true;
	//using namespace boost::property_tree;
	//bool ret = false;
	//ptree boot;
	//try
	//{
	//	std::stringstream jsonstream;	//json解析流
	//	jsonstream << CW2A(strJson);
	//	read_json(jsonstream, boot);	//解析json
	//	int type = boot.get<int>(L"action_type");
	//	int path = CW2A(CAppMain.GetAppPath());	//获取文件的运行路径
	//	path += kMonitorPath;					//加上ini文件的相对路径
	//	BmIniManagement clientcgf(path);		
	//}
	//catch (json_parser_error err)
	//{
	//	WRITE_LOG(LOG_LEVEL_ERROR, L"解析json错误:", err.what());
	//}
	//
	//return ret;
}



CString CBm::GetClientCfgPath()
{
 return CAppMain::GetAppPath() + L"\\Update\\ClientCfg.ini";
}
CString CBm::GetOperationActionsByType(const int action_type)
{
	
	RefreshAllActions();
	//开始写json
	return GetJsonStringByType(kOperationAction,action_type);
}

bool CBm::RefreshAllActions()
{
	/**
	* 进入方法后清空容器避免重复刷新
	* 检查生效段是否存在,存在则获取其中内容,否则添加至指定ini
	* 检查失效段是否存在,存在获取其中内容,否则添加至指定ini
	*/
	operation_actions_.clear();
	unoperation_actions_.clear();
	if (ini_.SectionExist(kOperationSectionName))	//检测指定段是否存在
	{
		CStringArray keys, values;
		int key_number = ini_.GetAllKeysAndValues(kOperationSectionName, keys, values);
		for (int i = 0; i < key_number; i+=4)//每个action都对应4个值
		{
			Action temp(
			_wtoi(values[i]),	//actiontype
			values[i+1],//param1
			values[i+2],//param2
			true//isoperation
			);
			operation_actions_.push_back(temp);
		}
		//判断最后一个key是否为配置结束
		Action temp(88,L"",L"", true);
		if (!(operation_actions_[operation_actions_.size()-1] == temp))
		{
			operation_actions_.push_back(temp);
			//在配置文件中加入
			AddActionToIni(key_number/4, temp);	//the value "key_number" is all keys number.need / 4
		}
	}
	else
	{
		//TODO:添加生效段的结束
		Action end_action(88,L"", L"", true);
		AddActionToIni(0, end_action);
	}
	if (ini_.SectionExist(kUnOperationSectionName))
	{
		CStringArray keys, values;
		int key_number = ini_.GetAllKeysAndValues(kOperationSectionName, keys, values);
		for (int i = 0; i < key_number; i+=4)//每个action都对应4个值
		{
			Action temp(
				_wtoi(values[i]),	//actiontype
				values[i+1],//param1
				values[i+2],//param2
				false//isoperation
				);
			unoperation_actions_.push_back(temp);
		}
		//判断最后一个key是否为配置结束
		Action temp(88,L"",L"", false);
		if (!(operation_actions_[operation_actions_.size()-1] == temp))
		{
			unoperation_actions_.push_back(temp);
			//在配置文件中加入
			AddActionToIni(key_number/4, temp);	//the value "key_number" is all keys number.need / 4
		}
	}
	else
	{
		Action end_action(88,L"", L"", false);
		AddActionToIni(0, end_action);
	}
	return true;
}



void CBm::AddActionToIni(const int action_index, const Action &add_action)
{
	/**
	* 如果add_action为有效数据就添加到System default中.否则就加入到其他项中
	*/
	CString action_type;
	action_type.Format(L"ActionType%d", action_index);
	CString type_value;
	type_value.Format(L"%d", add_action.type());
	CString section_name;	//控制section
	if (add_action.Isoperation())
	{
		section_name = kOperationSectionName;
	}
	else
	{
		section_name = kUnOperationSectionName;
	}
	ini_.SetKeyValue(section_name, action_type, type_value);
	CString action_param1;
	action_param1.Format(L"Param1%d", action_index);
	ini_.SetKeyValue(section_name, action_param1, add_action.param1());
	CString action_param2;
	action_param2.Format(L"Param2%d", action_index);
	ini_.SetKeyValue(section_name, action_param2, add_action.param2());
	CString action_name;
	action_name.Format(L"ActionName%d", action_index);
	ini_.SetKeyValue(section_name, action_name, add_action.name());
}

CString CBm::GetJsonStringByType(const int get_how, const int action_type)
{
	CString ret;
	switch (get_how)
	{
	case kOperationAction:
		{
			vector<Action> accord_actions;
			for (vector<Action>::iterator it = operation_actions_.begin();
				it != operation_actions_.end(); it++)
			{
				if (it->type() == action_type)
				{
					accord_actions.push_back(*it);
				}
			}
			Json::Value root;
			Json::Value array_actions;
			for (vector<Action>::iterator it = accord_actions.begin();
				it != accord_actions.end(); ++it)
			{
				Json::Value action_value;
				action_value["ActionType"] = it->type();
				CString temp = it->param1();
				string param1_temp = CW2A(temp.GetBuffer());
				temp.ReleaseBuffer();
				action_value["Param1"] = param1_temp;
				temp = it->param2();
				string param2_temp = CW2A(temp.GetBuffer());
				temp.ReleaseBuffer();
				action_value["Param2"] = param2_temp;
				action_value["Valib"] = it->Isoperation();
				array_actions.append(action_value);
			}
			root["listfortype"] = array_actions;
			string temp = root.toStyledString();
			ret = CA2W(temp.c_str());
		}
		break;
	default:
		break;
	}
	return ret;
}



