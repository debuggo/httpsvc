#include "FQ_Std.h"
#include "JsonEx.h"
#include "AppMain.h"
#include "mylog.h"
#include "ChineseCode.h"
#include "BtTypedef.h"
#include "Bt.h"


#ifdef	_DEBUG
#pragma comment(lib,"json_vc71_libmtd.lib")
#else
#pragma comment(lib,"json_vc71_libmt.lib")
#endif

CJsonEx::CJsonEx(void)
{
}

CJsonEx::~CJsonEx(void)
{
}

//��ʼ��JSON����BT��Դ
BOOL	CJsonEx::InitStBt()
{
	pStVirtual	lpDataVal = NULL;
	CString strAppPath = CAppMain::GetAppPath();
	CString	strBtDataPath = strAppPath + _T("BT\\*.*");
	CFileFind	hFindFile;
	BOOL bFlags = hFindFile.FindFile(strBtDataPath);
	if (!bFlags)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,_T("%s"),_T("�޷�����BT�����ļ���"));
		return FALSE;
	}
	while(bFlags)
	{
		bFlags = hFindFile.FindNextFile();
		if (!hFindFile.IsDirectory() && !hFindFile.IsDots())
		{
			int nPos = (hFindFile.GetFileName()).ReverseFind('.');
			CString strStName = (hFindFile.GetFileName()).Left(nPos);
			CStdioFile	hFile;
			if (!hFile.Open(hFindFile.GetFilePath(),CFile::modeRead))
			{
				WRITE_LOG(LOG_LEVEL_FATAL,_T("�޷����ļ���%s"),hFindFile.GetFileName());
				return FALSE;
			}
			int	nRow = 0;//��ȡ����
			CString	strData;
			while (hFile.ReadString(strData))
			{
				nRow++;
			}
			hFile.SeekToBegin();
			Vect_BtVirtual*	pStVal = new Vect_BtVirtual;
			for (int i = 0; i < nRow / 3; i++)
			{
				pStVirtual pDataVal = new StVirtual;
				hFile.ReadString(pDataVal->strName);
				hFile.ReadString(pDataVal->strVirtualType);
				if (pDataVal->strVirtualType == _T("%st"))
				{
					hFile.ReadString(pDataVal->strClass);
				}
				else
				{
					CString	strLen;
					hFile.ReadString(strLen);
					pDataVal->nLen = _ttoi(strLen);
				}
				if (pDataVal->strVirtualType == _T("%ws"))
				{
					pDataVal->nLen = pDataVal->nLen * 2;
				}
				pStVal->push_back(pDataVal);
				//delete pDataVal;
				//pDataVal = NULL;
			}
			m_StBt.insert(Map_StBt::value_type(strStName,pStVal));
			//delete pStVal;
			//pStVal = NULL;
			hFile.Close();
		}
	}
	hFindFile.Close();
	return TRUE;
}

//��ʼ��MZD����MZD��Դ
BOOL	CJsonEx::InitStMzd()
{
	pStVirtual	lpDataVal = NULL;
	CString strAppPath = CAppMain::GetAppPath();
	CString	strBtDataPath = strAppPath + _T("MZD\\*.*");
	CFileFind	hFindFile;
	BOOL bFlags = hFindFile.FindFile(strBtDataPath);
	if (!bFlags)
	{
		WRITE_LOG(LOG_LEVEL_FATAL,_T("%s"),_T("�޷�����Mzd�����ļ���"));
		return FALSE;
	}
	while(bFlags)
	{
		bFlags = hFindFile.FindNextFile();
		if (!hFindFile.IsDirectory() && !hFindFile.IsDots())
		{
			int nPos = (hFindFile.GetFileName()).ReverseFind('.');
			CString strStName = (hFindFile.GetFileName()).Left(nPos);
			CStdioFile	hFile;
			if (!hFile.Open(hFindFile.GetFilePath(),CFile::modeRead))
			{
				WRITE_LOG(LOG_LEVEL_FATAL,_T("�޷����ļ���%s"),hFindFile.GetFileName());
				return FALSE;
			}
			int	nRow = 0;//��ȡ����
			CString	strData;
			while (hFile.ReadString(strData))
			{
				nRow++;
			}
			hFile.SeekToBegin();
			Vect_BtVirtual*	pStVal = new Vect_BtVirtual;
			for (int i = 0; i < nRow / 3; i++)
			{
				pStVirtual pDataVal = new StVirtual;
				hFile.ReadString(pDataVal->strName);
				hFile.ReadString(pDataVal->strVirtualType);
				if (pDataVal->strVirtualType == _T("%st"))
				{
					hFile.ReadString(pDataVal->strClass);
				}
				else
				{
					CString	strLen;
					hFile.ReadString(strLen);
					pDataVal->nLen = _ttoi(strLen);
				}
				if (pDataVal->strVirtualType == _T("%ws"))
				{
					pDataVal->nLen = pDataVal->nLen * 2;
				}
				pStVal->push_back(pDataVal);
			}
			m_StBt.insert(Map_StBt::value_type(strStName,pStVal));
			hFile.Close();
		}
	}
	hFindFile.Close();
	return TRUE;
}

//��ʼ������WEB��Դ
BOOL	CJsonEx::InitStWeb()
{
	pStVirtual	lpDataVal = NULL;
	CString strAppPath = CAppMain::GetAppPath();
	CString	strBtDataPath = strAppPath + _T("FQ\\*.*");
	CFileFind	hFindFile;
	BOOL bFlags = hFindFile.FindFile(strBtDataPath);
	if (!bFlags)
	{
		WRITE_LOGLINE(LOG_LEVEL_FATAL,_T("%s"),_T("δ�ҵ�FQ�����ļ���"));
		return FALSE;
	}
	while(bFlags)
	{
		bFlags = hFindFile.FindNextFile();
		if (!hFindFile.IsDirectory() && !hFindFile.IsDots())	//����Ƿ����ļ��л�.
		{
			int nPos = (hFindFile.GetFileName()).ReverseFind('.');	
			CString strStName = (hFindFile.GetFileName()).Left(nPos);	//ȡ���ļ��� ��������ֵ
			CStdioFile	hFile;
			if (!hFile.Open(hFindFile.GetFilePath(),CFile::modeRead))
			{
				WRITE_LOG(LOG_LEVEL_FATAL,_T("�޷����ļ���%s"),hFindFile.GetFileName());
				return FALSE;
			}
			int	nRow = 0;//��ȡ����
			CString	strData;
			while (hFile.ReadString(strData))
			{
				nRow++;
			}
			hFile.SeekToBegin();
			Vect_BtVirtual*	pStVal = new Vect_BtVirtual;
			for (int i = 0; i < nRow / 3; i++)		//ÿ�λ�ȡ���е�����
			{
				pStVirtual pDataVal = new StVirtual;
				hFile.ReadString(pDataVal->strName);
				hFile.ReadString(pDataVal->strVirtualType);
				if (pDataVal->strVirtualType == _T("%st"))
				{
					hFile.ReadString(pDataVal->strClass);
				}
				else
				{
					CString	strLen;
					hFile.ReadString(strLen);
					pDataVal->nLen = _ttoi(strLen);
				}
				if (pDataVal->strVirtualType == _T("%ws"))
				{
					pDataVal->nLen = pDataVal->nLen * 2;
				}
				pStVal->push_back(pDataVal);
				//delete pDataVal;
				//pDataVal = NULL;
			}
			m_StBt.insert(Map_StBt::value_type(strStName,pStVal));	//���ļ���Ϊkey����һ��StVirual����
			/*delete pStVal;*/
			//pStVal = NULL;
			hFile.Close();
		}
	}
	hFindFile.Close();
	return TRUE;
}

//���Ĵ��룡JSONת�ɽṹ��
int		CJsonEx::ToStructFrom(byte* pStByte, CString	strName, CString strData, CString DataType, int nLen)
{
	if (DataType == _T("%d"))
	{
		int n = _ttoi(strData);
		memcpy(pStByte,&n,nLen);
		goto Success;
	}
	if (DataType == _T("%ld"))
	{
		int n = _ttoi(strData);
		memcpy(pStByte,&n,nLen);
		goto Success;
	}
	if (DataType == _T("%ip"))
	{
		char	szIpBuffer[16] = { 0 };
		CChineseCode::UniCodeToAscii(szIpBuffer,strData.GetBuffer());
		DWORD	dwIp = inet_addr(szIpBuffer);
		memcpy(pStByte,&dwIp,nLen);
		goto	Success;
	}
	if (DataType == _T("%02f"))
	{
		float f = _wtof(strData.GetBuffer());
		memcpy(pStByte,&f,nLen);
		goto Success;
	}
	if (DataType == _T("%02ff"))
	{
		double dd = _wtof(strData.GetBuffer());
		memcpy(pStByte,&dd,nLen);
		goto Success;
	}
	if (DataType == _T("%I64d"))
	{
		INT64	i64 = _wtoi64(strData.GetBuffer());
		memcpy(pStByte,&i64,nLen);
		goto Success;
	}
	if (DataType == _T("%time"))
	{
		SYSTEMTIME	sTime;
		int  nYear   = 0;
		int  nMonth  = 0;
		int  nDay    = 0;
		int  nHour   = 0;
		int  nSecond = 0;
		int  nMinute = 0;
		_stscanf(strData,_T("%d-%d-%d %d:%d:%d"),&nYear,&nMonth,&nDay,&nHour,&nMinute,&nSecond);
		if (nMonth==0 || nDay==0)
			_stscanf(strData,_T("%d/%d/%d %d:%d:%d"),&nYear,&nMonth,&nDay,&nHour,&nMinute,&nSecond);
		sTime.wYear   = nYear;
		sTime.wMonth  = nMonth;
		sTime.wDay    = nDay;
		sTime.wHour   = nHour;
		sTime.wSecond = nSecond;
		sTime.wMinute = nMinute;
		memcpy(pStByte,&sTime,nLen);
		goto Success;
	}
	if (DataType == _T("%s"))
	{
		char	strAscii[1024] = { 0 };
		CChineseCode::UniCodeToAscii((char*)strAscii,strData.GetBuffer());
		memcpy(pStByte,strAscii,nLen);
		goto Success;
	}
	if (DataType == _T("%x"))
	{
		char	strAscii[1024] = { 0 };
		CChineseCode::UniCodeToAscii((char*)strAscii,strData.GetBuffer());
		memcpy(pStByte,strAscii,nLen);
		goto Success;
	}
	if (DataType == _T("%ws"))
	{
		int nstrLen = strData.GetLength() * sizeof(wchar_t);
		if (nstrLen >= nLen)
		{
			nstrLen = nLen - sizeof(wchar_t);
		}
		memcpy(pStByte,strData.GetBuffer(),nstrLen);
		goto Success;
	}
	if (DataType == _T("%st"))
	{
		if (ToStruct(strData,strName,(PVOID*)pStByte) == 1)
		{
			goto Success;
		}
	}
	return 0;
Success:
	return 1;
}

//���Ĵ��룡 ת���ṹ��������
int 	CJsonEx::ToStruct(CString	strJson, CString	strTableName, PVOID*	lpStData)
{
	Sleep(1);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json�޷�ʶ�� ��%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	Iter_St_Bt IterSt = m_StBt.find(strTableName);
	if (IterSt == m_StBt.end())
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ��ṹ ��%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	int nStlen = 0;
	Vect_BtVirtual*	pBtVal = IterSt->second;
	Iter_BtVirtual	Iter_BtVal = pBtVal->begin();
	for (; Iter_BtVal != pBtVal->end(); Iter_BtVal++)
	{
		nStlen += ((pStVirtual)*Iter_BtVal)->nLen;
	}
	byte*	pStByte = new byte[nStlen];
	memset(pStByte,0,nStlen);
	byte*	pTemp = pStByte;
	Iter_BtVal = pBtVal->begin();
	for (; Iter_BtVal != pBtVal->end(); Iter_BtVal++)
	{
		char	szKeyName[512] = { 0 };
		CString	strKeyName = ((pStVirtual)*Iter_BtVal)->strName;
		CChineseCode::UniCodeToAscii(szKeyName, strKeyName.GetBuffer());
		Json::Value ValKey = Root[szKeyName];
		if (ValKey.isNull())
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",pDocument);
			delete []pStByte;
			return NULL;
		}
		if (ValKey.isString())
		{
			char* pKeyData = (char*)ValKey.asCString();
			CString	strKeyData(pKeyData);
			if (!ToStructFrom(pTemp,((pStVirtual)*Iter_BtVal)->strName, strKeyData, ((pStVirtual)*Iter_BtVal)->strVirtualType,((pStVirtual)*Iter_BtVal)->nLen))
			{
				WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ����� ��%s",pDocument);
				delete []pStByte;
				return NULL;
			}
		}
		if (ValKey.isObject())
		{
			Json::FastWriter	JsonWrite;
			std::string	strStdJson = JsonWrite.write(ValKey);
			CString	strInJson(strStdJson.c_str());
			PVOID	pData = NULL;
			if (!ToStruct(strInJson,strKeyName,&pData))
			{
				WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ����� ��%s",pDocument);
				delete []pStByte;
				return NULL;
			}
			memcpy(pTemp,pData,((pStVirtual)*Iter_BtVal)->nLen);
			ToStructRelease(pData);
		}
		pTemp += ((pStVirtual)*Iter_BtVal)->nLen;
	}
	*(int*)lpStData = (int)pStByte;

	return 1;
}

VOID	CJsonEx::ToStructRelease(PVOID lpStData)
{
	if (lpStData != NULL)
	{
		delete []lpStData;
	}

}

//���Ĵ��룡 �ṹ��תJSON
int		CJsonEx::ToJsonExFrom(byte* pStByte,  CString	strName, CString DataType, int nLen, CString& strData)
{
	if (DataType == _T("%d"))
	{
		int		nData = 0;
		memcpy(&nData,pStByte,nLen);
		strData.Format(_T("%d"),nData);
		goto	Success;
	}
	if (DataType == _T("%ld"))
	{
		DWORD		nData;
		if (nLen > 4)
		{
			memcpy(&nData,pStByte,sizeof(DWORD));
		}
		else
		{
			memcpy(&nData,pStByte,nLen);
		}
		strData.Format(_T("%ld"),nData);
		goto	Success;
	}
	if (DataType == _T("%ip"))
	{
		sockaddr_in stAddr = { 0 };
		DWORD	dwIp;
		memcpy(&dwIp,pStByte,nLen);
		stAddr.sin_addr.S_un.S_addr = dwIp;
		wchar_t	wzsBuffer[16] = { 0 };
		CChineseCode::AsciiToUnicode(wzsBuffer,inet_ntoa(stAddr.sin_addr));
		strData.Format(_T("%s"),wzsBuffer);
		goto Success;
	}
	if (DataType == _T("%02f"))
	{
		float	fData;
		memcpy(&fData,pStByte,nLen);
		strData.Format(_T("%02f"),fData);
		goto Success;
	}
	if (DataType == _T("%02ff"))
	{
		double	dd;
		memcpy(&dd,pStByte,nLen);
		strData.Format(_T("%02f"),dd);
		goto	Success;
	}
	if (DataType == _T("%I64d"))
	{
		INT64 i64;
		memcpy(&i64,pStByte,nLen);
		strData.Format(_T("%I64d"),i64);
		goto Success;
	}
	if (DataType == _T("%time"))
	{
		SYSTEMTIME	sTime;
		memcpy(&sTime,pStByte,nLen);
		strData.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),sTime.wYear,sTime.wMonth,sTime.wDay,sTime.wHour,sTime.wMinute,0);
		goto Success;
	}
	if (DataType == _T("%s"))
	{
		char*	lpc = new char[nLen + 1];
		memset(lpc,0,nLen);
		memcpy(lpc,pStByte,nLen);
		int nstrlen = strlen(lpc);
		wchar_t lpwc[1024] = { 0 };
		//CChineseCode::AsciiToUnicode(lpwc,lpc);
		 MultiByteToWideChar(CP_ACP,0,lpc,nstrlen,lpwc,1024);
		strData.Format(_T("%s"),lpwc);
		delete	[]lpc;
		goto	Success;
	}
	if (DataType == _T("%x"))
	{
		byte*	lpByte = new byte[nLen + 1];
		memset(lpByte,0,nLen);
		memcpy(lpByte,pStByte,nLen);

		for (int i = 0; i < nLen; i++)
		{
			CString	strFormat;
			strFormat.Format(_T("%x"),lpByte[i]);
			strData += strFormat;
		}
		delete	[]lpByte;
		goto	Success;
	}
	if (DataType == _T("%ws"))
	{
		wchar_t*	lpwc = new wchar_t[nLen / sizeof(wchar_t)];
		//wchar_t*	lpwc2 = new wchar_t[nLen];
		memset(lpwc,0,nLen);
		memcpy(lpwc,pStByte,nLen);
		//AddChar(lpwc,lpwc2,nLen / sizeof(wchar_t));
		strData.Format(_T("%s"),lpwc);
		delete	[]lpwc;
		//delete	[]lpwc2;
		goto	Success;
	}
	if (DataType == _T("%RGB"))
	{
		DWORD	dwData;
		memcpy(&dwData,pStByte,nLen);
		strData.Format(_T("%06X"),GetRGB(dwData));
		goto Success;
	}
	if (DataType == _T("%st"))
	{
		if (ToJsonEx(strName,pStByte,strData) == 1)
		{
			return 2;
		}
	}
	return 0;
Success:
	return 1;
}

//JSON ����ṹ���JSON�ַ���
int		CJsonEx::ToJsonEx(CString strStTable, PVOID lpStData, CString &strJson)
{
	Sleep(1);

	Json::Value			JsonVal;
	Json::FastWriter	JsonWrite;
	Json::Value			JsonRoot;

	Iter_St_Bt	Iter_St = m_StBt.find(strStTable);
	if (Iter_St == m_StBt.end())
	{
		WRITE_LOG(LOG_LEVEL_ERROR,_T("û���ҵ��ṹ���� ��%s"),strStTable.GetBuffer());
		return -1;
	}
	Vect_BtVirtual*	pMapBtVal = Iter_St->second;
	
	Iter_BtVirtual	Iter_BtVal = pMapBtVal->begin();
	byte*	pStByte = (byte*)lpStData;
	char	szBuffer[1024] = { 0 };
	for (; Iter_BtVal != pMapBtVal->end(); Iter_BtVal++)
	{
		CString	strKeyName = ((pStVirtual)*Iter_BtVal)->strName;
		CString	strData;
		int		nDataLen = ((pStVirtual)*Iter_BtVal)->nLen;
		//CString strType = ((pStVirtual)*Iter_BtVal)->strVirtualType;
		//if (strType == _T("%st"))
		//{
		//	strKeyName = ((pStVirtual)*Iter_BtVal)->strClass;
		//}
		int		nFromError = ToJsonExFrom(pStByte,((pStVirtual)*Iter_BtVal)->strName,((pStVirtual)*Iter_BtVal)->strVirtualType,nDataLen,strData);
		//int		nFromError = ToJsonExFrom(pStByte,strKeyName,((pStVirtual)*Iter_BtVal)->strVirtualType,nDataLen,strData);
		if (nFromError == NULL)
		{
			WRITE_LOG(LOG_LEVEL_ERROR,_T("û���ҵ�Key���� ��%s"),strKeyName.GetBuffer());
			return -1;
		}
		char	szDataVal[4096] = { 0 };
		CChineseCode::UniCodeToAscii(szBuffer,strKeyName.GetBuffer());
		CChineseCode::UniCodeToAscii(szDataVal,strData.GetBuffer());
		if (nFromError == 1)
		{
			JsonVal[szBuffer] = Json::Value(szDataVal);
		}
		if (nFromError == 2)
		{
			Json::Reader	JsonReadOb;
			Json::Value		JsonSt;
			JsonReadOb.parse(szDataVal,JsonSt);
			JsonVal[szBuffer] = JsonSt;
		}
		memset(szBuffer,0,1024);
		pStByte += nDataLen;
	}
	memset(szBuffer,0,1024);
	CChineseCode::UniCodeToAscii(szBuffer,strStTable.GetBuffer());
	//JsonRoot[szBuffer].append(JsonVal);
	std::string	strStdJson = JsonWrite.write(JsonVal);
	strJson = strStdJson.c_str();
	return 1;
}

//�ṹ��תJSON֧�ֶ�ṹ��ת��
int		CJsonEx::ToStructCount(CString strJson, CString	strTableName, PVOID* lpStData)
{
	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json�޷�ʶ�� ��%s",pDocument);
		return NULL;
	}
	int nCount = Root["Array"].size();
	Json::Value	Val = Root["Array"];

	Iter_St_Bt IterSt = m_StBt.find(strTableName);
	if (IterSt == m_StBt.end())
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ��ṹ ��%s",pDocument);
		return NULL;
	}
	int nStlen = 0;
	Vect_BtVirtual*	pBtVal = IterSt->second;
	Iter_BtVirtual	Iter_BtVal = pBtVal->begin();
	for (; Iter_BtVal != pBtVal->end(); Iter_BtVal++)
	{
		nStlen += ((pStVirtual)*Iter_BtVal)->nLen;
	}
	byte*	pStByte = new byte[nStlen * nCount];
	memset(pStByte,0,nStlen * nCount);
	byte*	pTemp = pStByte;
	for (int i = 0; i < nCount; i++)
	{
		Iter_BtVal = pBtVal->begin();
		for (; Iter_BtVal != pBtVal->end(); Iter_BtVal++)
		{
			char	szKeyName[512] = { 0 };
			CString	strKeyName = ((pStVirtual)*Iter_BtVal)->strName;
			CChineseCode::UniCodeToAscii(szKeyName, strKeyName.GetBuffer());
			//char* pKeyData = (char*)Root[szKeyName].asCString();

			char* pKeyData = NULL;
			if (Val[i][szKeyName].isNull())
			{
				return NULL;
			}
			if (Val[i][szKeyName].isString())
			{
				pKeyData = (char*)Val[i][szKeyName].asCString();
				CString	strKeyData(pKeyData);
				if (!ToStructFrom(pTemp,((pStVirtual)*Iter_BtVal)->strName, strKeyData, ((pStVirtual)*Iter_BtVal)->strVirtualType,((pStVirtual)*Iter_BtVal)->nLen))
				{
					WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ����� ��%s",pDocument);
					return NULL;
				}
			}

			pTemp += ((pStVirtual)*Iter_BtVal)->nLen;
		}
	}
	*(int*)lpStData = (int)pStByte;
	return nCount;
}

//INI��ʽתJSON
int		CJsonEx::ToIniByJson(CString	strJson, CString	strTableName, MZD_INI*	pstMZDINI)
{
	Sleep(1);

	Json::Reader	Object;
	Json::Value		Root;
	int nJsonlen = ::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,NULL,0,NULL,NULL);
	char*	pDocument = new char[nJsonlen];
	memset(pDocument,0,nJsonlen);
	::WideCharToMultiByte(CP_ACP,0,strJson.GetBuffer(),-1,pDocument,nJsonlen,NULL,NULL);

	if (!Object.parse(pDocument,Root))
	{
		WRITE_LOG(LOG_LEVEL_ERROR,"Json�޷�ʶ�� ��%s",pDocument);
		delete []pDocument;
		return NULL;
	}
	delete []pDocument;

	Iter_St_Bt IterSt = m_StBt.find(strTableName);
	if (IterSt == m_StBt.end())
	{
		//WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ��ṹ ��%s",pDocument);
		WRITE_LOG(LOG_LEVEL_ERROR,_T("û���ҵ����ݽṹ �� %s"),strTableName.GetBuffer());
		return NULL;
	}
	int	nCountNumber = pstMZDINI->CreateSecNumber(strTableName.GetBuffer());
	
	int nStlen = 0;
	Vect_BtVirtual*	pBtVal = IterSt->second;
	Iter_BtVirtual	Iter_BtVal = pBtVal->begin();
	for (; Iter_BtVal != pBtVal->end(); Iter_BtVal++)
	{
		char	szKeyName[512] = { 0 };
		CString	strKeyName = ((pStVirtual)*Iter_BtVal)->strName;
		CChineseCode::UniCodeToAscii(szKeyName, strKeyName.GetBuffer());
		Json::Value ValKey = Root[szKeyName];
		if (ValKey.isNull())
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
			return NULL;
		}
		//if (!ValKey.isString())
		//{
		//	WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
		//	return NULL;
		//}
		if (ValKey.isString())
		{
			char* pKeyData = (char*)ValKey.asCString();
			CString	strKeyData(pKeyData);
			CString	strIniData;
			pstMZDINI->Write2INI(strTableName.GetBuffer(),nCountNumber,strKeyName.GetBuffer(),strKeyData.GetBuffer());
			continue;
		}
		if (ValKey.isObject())
		{
			//Json::FastWriter	JsonWrite;
			//std::string	strStdJson = JsonWrite.write(ValKey);
			//CString	strInJson(strStdJson.c_str());
			//if (ToIniByJson(strInJson,((pStVirtual)*Iter_BtVal)->strClass,pstMZDINI) == NULL)
			//{
			//	WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
			//	return NULL;
			//}
			int nStCount;
			if (ToIniByJsonEx(ValKey,((pStVirtual)*Iter_BtVal)->strClass,nStCount,pstMZDINI) == NULL)
			{
				WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
				return NULL;
			}
			TCHAR	wszStName[64] = { 0 };
			pstMZDINI->GetSectionName(((pStVirtual)*Iter_BtVal)->strClass.GetBuffer(),nStCount,wszStName);
			pstMZDINI->Write2INI(strTableName.GetBuffer(),nCountNumber,strKeyName.GetBuffer(),wszStName);
			continue;
		}
	}
	return 1;
}
//
int		CJsonEx::ToJsonByIni(MZD_INI* pstMZDINI,CString strTableName, int nCount, CString& strJson)
{
	Json::Value			JsonVal;
	Json::FastWriter	JsonWrite;
	Json::Value			JsonRoot;

	Iter_St_Bt	Iter_St = m_StBt.find(strTableName);
	if (Iter_St == m_StBt.end())
	{
		WRITE_LOG(LOG_LEVEL_ERROR,_T("û���ҵ��ṹ���� ��%s"),strTableName.GetBuffer());
		return NULL;
	}
	if (!pstMZDINI->CheckSecExist(strTableName.GetBuffer(),nCount))
	{
		return NULL;
	}
	Vect_BtVirtual*	pMapBtVal = Iter_St->second;
	Iter_BtVirtual	Iter_BtVal = pMapBtVal->begin();
	for (; Iter_BtVal != pMapBtVal->end(); Iter_BtVal++)
	{
		char	szBuffer[1024] = { 0 };
		char	szDataVal[4096] = { 0 };
		CString	strResultData;

		char	szCharBuffer[2048] = { 0 };
		char	szSection[64] = { 0 };
		char	szName[64] = { 0 };
		CChineseCode::UniCodeToAscii(szSection,strTableName.GetBuffer());
		CChineseCode::UniCodeToAscii(szName,((pStVirtual)*Iter_BtVal)->strName.GetBuffer());
		pstMZDINI->ReadFromINI(szSection,nCount,szName,szCharBuffer,2048,"");
		CString	strData(szCharBuffer);

		if (((pStVirtual)*Iter_BtVal)->strVirtualType == _T("%st"))
		{
			int		nNumber = 0;
			TCHAR	wszStName[64] = { 0 };
			pstMZDINI->SpliteSecName(strData.GetBuffer(),nNumber,wszStName);
			if (!ToJsonByIni(pstMZDINI,((pStVirtual)*Iter_BtVal)->strClass,nNumber,strResultData))
			{
				WRITE_LOG(LOG_LEVEL_ERROR,_T("û���ҵ��ṹ���� ��%s"),((pStVirtual)*Iter_BtVal)->strClass.GetBuffer());
				continue;
			}
			CChineseCode::UniCodeToAscii(szDataVal,strResultData.GetBuffer());
			CChineseCode::UniCodeToAscii(szBuffer,((pStVirtual)*Iter_BtVal)->strName.GetBuffer());
			Json::Reader	JsonReadOb;
			Json::Value		JsonSt;
			JsonReadOb.parse(szDataVal,JsonSt);
			JsonVal[szBuffer] = JsonSt;
			continue;
		}
		strResultData.Format(_T("%s"),strData.GetBuffer());

		CChineseCode::UniCodeToAscii(szBuffer,((pStVirtual)*Iter_BtVal)->strName.GetBuffer());
		CChineseCode::UniCodeToAscii(szDataVal,strResultData.GetBuffer());
		JsonVal[szBuffer] = Json::Value(szDataVal);
		memset(szBuffer,0,1024);
	}
	std::string	strStdJson = JsonWrite.write(JsonVal);
	strJson = strStdJson.c_str();
	return 1;
}

int		CJsonEx::ToIniByJsonEx(Json::Value JsonObjet, CString strTableName, int& nCount, MZD_INI* pstMZDINI)
{
	Iter_St_Bt IterSt = m_StBt.find(strTableName);
	if (IterSt == m_StBt.end())
	{
		return NULL;
	}
	int	nCountNumber = pstMZDINI->CreateSecNumber(strTableName.GetBuffer());

	int nStlen = 0;
	Vect_BtVirtual*	pBtVal = IterSt->second;
	Iter_BtVirtual	Iter_BtVal = pBtVal->begin();
	for (; Iter_BtVal != pBtVal->end(); Iter_BtVal++)
	{
		char	szKeyName[512] = { 0 };
		CString	strKeyName = ((pStVirtual)*Iter_BtVal)->strName;
		CChineseCode::UniCodeToAscii(szKeyName, strKeyName.GetBuffer());
		Json::Value ValKey = JsonObjet[szKeyName];
		if (ValKey.isNull())
		{
			WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
			return NULL;
		}
		//if (!ValKey.isString())
		//{
		//	WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
		//	return NULL;
		//}
		if (ValKey.isString())
		{
			char* pKeyData = (char*)ValKey.asCString();
			//wchar_t	wzsBuffer[1024] = { 0 };
			int		nLenKeyData = strlen(pKeyData);
			CString	strKeyData;
			CString	strIniData;
			//if (((pStVirtual)*Iter_BtVal)->strVirtualType == _T("%ip"))
			//{
			//	DWORD	dwIp = atol(pKeyData);
			//	sockaddr_in stAddr = { 0 };
			//	stAddr.sin_addr.S_un.S_addr = dwIp;
			//	CChineseCode::AsciiToUnicode(wzsBuffer,inet_ntoa(stAddr.sin_addr));
			//	strKeyData.Format(_T("%s"),wzsBuffer);
			//}
			//CChineseCode::AsciiToUnicode(pwstrBuffer,pKeyData);
			int nUniCodeLen = MultiByteToWideChar(CP_ACP,0,pKeyData,nLenKeyData,NULL,0);
			wchar_t*	pUniCodeBuffer = new wchar_t[nUniCodeLen + 1];
			memset(pUniCodeBuffer,0,(nUniCodeLen + 1) * sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP,0,pKeyData,nLenKeyData,pUniCodeBuffer,nUniCodeLen);
			strKeyData.Format(_T("%s"),pUniCodeBuffer);
			delete []pUniCodeBuffer;

			pstMZDINI->Write2INI(strTableName.GetBuffer(),nCountNumber,strKeyName.GetBuffer(),strKeyData.GetBuffer());
			continue;
		}
		if (ValKey.isObject())
		{
			int nStCount;
			if (ToIniByJsonEx(ValKey,((pStVirtual)*Iter_BtVal)->strClass,nStCount,pstMZDINI) == NULL)
			{
				WRITE_LOG(LOG_LEVEL_ERROR,"û���ҵ���ֵ ��%s",szKeyName);
				return NULL;
			}
			TCHAR	wszStName[64] = { 0 };
			pstMZDINI->GetSectionName(((pStVirtual)*Iter_BtVal)->strClass.GetBuffer(),nStCount,wszStName);
			pstMZDINI->Write2INI(strTableName.GetBuffer(),nCountNumber,strKeyName.GetBuffer(),wszStName);
			continue;
		}
	}
	nCount = nCountNumber;
	return 1;
}