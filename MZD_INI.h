#ifndef MZD_INI_H
#define MZD_INI_H

#include "BaseFunc.h"

#pragma pack(push,MZD_INI_,1)

typedef struct _tagKeyValueNode
{
	string keyName;
	string keyValue;
	_tagKeyValueNode* pNext;
}tagKeyValueNode;



struct MZD_INI_SECTION
{
public:
	MZD_INI_SECTION()
	{
		m_Node_List = NULL;
	}

	~MZD_INI_SECTION()
	{
		tagKeyValueNode* pLastNode = NULL;
		tagKeyValueNode* pNode = m_Node_List;
		while(pNode)
		{
			pLastNode = pNode;
			pNode = pNode->pNext;
			delete pLastNode;
		}
	}

	void Write2INI(char* keyName,const char* keyValue)
	{
		if (m_Node_List)
		{
			bool bExist = false;
			tagKeyValueNode* pLastNode = NULL;
			tagKeyValueNode* pNode = m_Node_List;
			while(pNode)
			{
				if (pNode->keyName == keyName)
				{
					bExist = true;
					pNode->keyValue = keyValue;
					break;
				}
				pLastNode = pNode;
				pNode = pNode->pNext;
			}

			if (!bExist)
			{
				tagKeyValueNode* pNewNode = new tagKeyValueNode;
				pNewNode->keyName = keyName;
				pNewNode->keyValue = keyValue;
				pNewNode->pNext = NULL;
				pLastNode->pNext = pNewNode;
			}
		}else
		{
			m_Node_List = new tagKeyValueNode;
			m_Node_List->keyName = keyName;
			m_Node_List->keyValue = keyValue;
			m_Node_List->pNext = NULL;
		}
	}

	void ReadFromINI(char* keyName,char* keyValue,int max_length)
	{
		tagKeyValueNode* pNode = m_Node_List;
		while(pNode)
		{
			if (pNode->keyName == keyName)
			{
				//strcpy_s(keyValue,max_length,pNode->keyValue.c_str());
				strncpy(keyValue,pNode->keyValue.c_str(),max_length);
				break;
			}
			pNode = pNode->pNext;
		}
	}

	void Format2Str(string& ret)
	{
		char strTemp[1024];
		tagKeyValueNode* pNode = m_Node_List;
		while(pNode)
		{
			sprintf(strTemp,"%s=%s\r\n",pNode->keyName.c_str(),pNode->keyValue.c_str());
			ret += strTemp;
			pNode = pNode->pNext;
		}
	}
	tagKeyValueNode* m_Node_List;
};

struct MZD_INI_SECTION_LIST
{
	MZD_INI_SECTION_LIST()
	{
		m_current_num = 0;
		m_Section_List = (MZD_INI_SECTION**)malloc(1024*sizeof(MZD_INI_SECTION*));
		m_current_max_num = 1024;
	}
	~MZD_INI_SECTION_LIST()
	{
		for (int i = 0;i < m_current_num;i++)
		{
			delete m_Section_List[i];
		}
		free(m_Section_List);
	}
	int CreateSecNumber()
	{
		if (m_current_max_num <= m_current_num)
		{
			m_current_max_num += 1024;
			m_Section_List = (MZD_INI_SECTION**)realloc(m_Section_List,m_current_max_num*sizeof(MZD_INI_SECTION*));

		}
		m_Section_List[m_current_num] = new MZD_INI_SECTION;
		return m_current_num++;
	}

	bool CheckSecExist(int sec_num)
	{
		if (sec_num < m_current_num)
		{
			return true;
		}
		return false;
	}

	DWORD GetSectionNums()
	{
		return m_current_num;
	}

	void Write2INI(int sec_num,char* keyName,const char* keyValue)
	{
		if (sec_num < m_current_num)
		{
			m_Section_List[sec_num]->Write2INI(keyName,keyValue);
		}
	}

	void ReadFromINI(int sec_num,char* keyName,char* keyValue,int keyValueMaxLength)
	{
		if (sec_num < m_current_num)
		{
			m_Section_List[sec_num]->ReadFromINI(keyName,keyValue,keyValueMaxLength);
		}
	}

	void Format2Str(char* className,string& ret)
	{
		char strTemp[MAX_PATH];
		for (int i = 0;i < m_current_num;i++)
		{
			sprintf(strTemp,"[%s%08d]\r\n",className,i);
			ret += strTemp;
			m_Section_List[i]->Format2Str(ret);
		}
	}
	MZD_INI_SECTION** m_Section_List;
	int m_current_num;//当前已使用的SECTION数
	int m_current_max_num;//最大SECTION数
};

struct tagNode
{
	char section_name[MAX_PATH];
	MZD_INI_SECTION_LIST* key_value_list;
	tagNode* pNext;
};


struct MZD_INI
{
	tagNode* m_List;

	MZD_INI(char* pInI = NULL)
	{
		m_List = NULL;
		//Load(pInI);
	}

	~MZD_INI()
	{
		Clear();
	}

	void Clear()
	{
		tagNode* pNode = m_List;
		tagNode* pTempNode = NULL;
		while(pNode)
		{
			pTempNode = pNode;
			pNode = pNode->pNext;
			delete pTempNode->key_value_list;
			delete pTempNode;
		}
		m_List = NULL;
	}

	void Load(char* pInI)
	{
		char secName[1024]={0};
		char keyName[1024]={0};
		char keyValue[1024]={0};
		int sec_num;
		char className[1024];
		char pTempBuff[1024];
		char* pStartPos = pInI;
		char* pA1 = NULL;
		char* pA2 = NULL;
		int ilength = 0;
		while(pStartPos)
		{
			memset(pTempBuff,0,1024);
			char* pPos = strstr(pStartPos,"\r\n");
			if (pPos)
			{
				ilength = pPos - pStartPos;
				memcpy(pTempBuff,pStartPos,ilength);
				pStartPos += ilength + 2;

				pA1 = strstr(pTempBuff,"[");
				pA2 = strstr(pTempBuff,"]");
				if (pA1&&pA2&&(pA1 == pTempBuff)&&(pA2 > pA1))
				{
					//新节名称
					memcpy(secName,pA1 + 1,pA2 - pA1 - 1);
					secName[pA2 - pA1 - 1] = '\0';
					MZD_INI::SpliteSecName(secName,sec_num,className);
					sec_num = CreateSecNumber(className);
				}else
				{
					//key数据
					pA1 = strstr(pTempBuff,"=");
					if (pA1)
					{
						memcpy(keyName,pTempBuff,pA1 - pTempBuff);
						keyName[pA1 - pTempBuff] = '\0';

						strcpy_s(keyValue,pA1 + 1);

						Write2INI(className,sec_num,keyName,keyValue);
					}
				}
			}else
			{
				break;
			}
		}
	}

	static void GetSectionName(char* className,int sec_num,char* pOut,DWORD out_length = 0)
	{
		sprintf(pOut,"%s%08d",className,sec_num);
	}

	static void SpliteSecName(char* secName,int& sec_num,char* className = NULL)
	{
		if (strlen(secName) > 8)
		{
			if (className)
			{
				strcpy(className,secName);
				className[strlen(secName) - 8] = '\0';
			}

			sec_num = atoi(secName + strlen(secName) - 8);
		}
	}

	int CreateSecNumber(char* className)
	{
		tagNode* pNode = m_List;
		tagNode* pLastNode = NULL;
		while(pNode)
		{
			if (strcmp(pNode->section_name,className) == 0)
			{
				return pNode->key_value_list->CreateSecNumber();
			}
			pLastNode = pNode;
			pNode = pNode->pNext;
		}

		tagNode* pNewNode = new tagNode;
		strcpy(pNewNode->section_name,className);
		pNewNode->key_value_list = new MZD_INI_SECTION_LIST;
		pNewNode->pNext = NULL;
		if (pLastNode)
		{
			pLastNode->pNext = pNewNode;
		}else
		{
			m_List = pNewNode;
		}

		return pNewNode->key_value_list->CreateSecNumber();
	}

	void Format2Str(string& ret)
	{
		tagNode* pNode = m_List;
		while(pNode)
		{
			pNode->key_value_list->Format2Str(pNode->section_name,ret);
			pNode = pNode->pNext;
		}
	}

	void Write2INI(char* className,int sec_num,char* keyName,const char* keyValue)
	{
		tagNode* pNode = m_List;
		while(pNode)
		{
			if (strcmp(pNode->section_name,className) == 0)
			{
				pNode->key_value_list->Write2INI(sec_num,keyName,keyValue);
				break;
			}
			pNode = pNode->pNext;
		}
	}

	void Write2INI(char* secName,int sec_num,char* keyName,int keyValue)
	{
		char strTemp[32];
		sprintf(strTemp,"%d",keyValue);
		Write2INI(secName,sec_num,keyName,strTemp);
	}

	void WriteIp2INI(char* secName,int sec_num,char* keyName,int keyValue)
	{
		char strTemp[32];
		IpInt2Str(keyValue,strTemp);
		Write2INI(secName,sec_num,keyName,strTemp);
	}

	void WriteTime2INI(char* secName,int sec_num,char* keyName,DWORD keyValue)
	{
		char strTemp[32];
		TimeInt2Str(keyValue,strTemp);
		Write2INI(secName,sec_num,keyName,strTemp);
	}

	void ReadFromINI(char* className,int sec_num,char* keyName,char* keyValue,int keyValueMaxLength,char* DefaultKeyValue)
	{
		strcpy_s(keyValue,keyValueMaxLength,DefaultKeyValue);

		tagNode* pNode = m_List;
		while(pNode)
		{
			if (strcmp(pNode->section_name,className) == 0)
			{
				pNode->key_value_list->ReadFromINI(sec_num,keyName,keyValue,keyValueMaxLength);
				break;
			}
			pNode = pNode->pNext;
		}
	}

	void ReadFromINI(char* secName,int sec_num,char* keyName,int& keyValue,int DefaultKeyValue)
	{
		char strTemp[1024];
		char strDefaultValue[32];
		sprintf(strDefaultValue,"%d",DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,MAX_PATH,strDefaultValue);
		keyValue = atoi(strTemp);
	}

	void ReadIpFromINI(char* secName,int sec_num,char* keyName,int& keyValue,char* DefaultIp)
	{
		char strTemp[1024];
		ReadFromINI(secName,sec_num,keyName,strTemp,MAX_PATH,DefaultIp);
		keyValue = IpStr2Int(strTemp);
	}

	void ReadIpFromINI(char* secName,int sec_num,char* keyName,DWORD& keyValue,char* DefaultIp)
	{
		char strTemp[1024];
		ReadFromINI(secName,sec_num,keyName,strTemp,MAX_PATH,DefaultIp);
		keyValue = IpStr2Int(strTemp);
	}

	void ReadTimeFromINI(char* secName,int sec_num,char* keyName,DWORD& keyValue,char* DefaultTime)
	{
		char strTemp[1024]={0};
		ReadFromINI(secName,sec_num,keyName,strTemp,MAX_PATH,DefaultTime);
		keyValue = IpStr2Int(strTemp);
	}

	void ReadFromINI(char* secName,int sec_num,char* keyName,INT64& keyValue,INT64 DefaultKeyValue)
	{
		char strTemp[1024];
		char strDefaultValue[32];
		sprintf(strDefaultValue,"%I64d",DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,MAX_PATH,strDefaultValue);
		keyValue = _atoi64(strTemp);
	}

	void ReadFromINI(char* secName,int sec_num,char* keyName,DWORD& keyValue,DWORD DefaultKeyValue)
	{
		char strTemp[1024];
		char strDefaultValue[32];
		sprintf(strDefaultValue,"%d",DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = atoi(strTemp);
	}

	void ReadFromINI(char* secName,int sec_num,char* keyName,bool& keyValue,bool DefaultKeyValue)
	{
		char strTemp[1024];
		char strDefaultValue[32];
		sprintf(strDefaultValue,"%d",DefaultKeyValue?1:0);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = (atoi(strTemp) == 1?true:false);
	}

	void ReadFromINI(char* secName,int sec_num,char* keyName,BYTE& keyValue,DWORD DefaultKeyValue)
	{
		char strTemp[1024];
		char strDefaultValue[32];
		sprintf(strDefaultValue,"%d",DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = atoi(strTemp);
	}

	bool CheckSecExist(char* className,int sec_num)
	{
		tagNode* pNode = m_List;
		while(pNode)
		{
			if (strcmp(pNode->section_name,className) == 0)
			{
				return pNode->key_value_list->CheckSecExist(sec_num);
			}
			pNode = pNode->pNext;
		}

		return false;
	}

	DWORD GetSectionNums(char* className)
	{
		DWORD nums = 0;
		tagNode* pNode = m_List;
		while(pNode)
		{
			if (strcmp(pNode->section_name,className) == 0)
			{
				nums = pNode->key_value_list->GetSectionNums();
				break;
			}
			pNode = pNode->pNext;
		}
		return nums;
	}

#ifdef _UNICODE
	static void GetSectionName(TCHAR* className,int sec_num,TCHAR* pOut,DWORD out_length = 0)
	{
		swprintf(pOut,_T("%s%08d"),className,sec_num);
	}

	static void SpliteSecName(TCHAR* secName,int& sec_num,TCHAR* className = NULL)
	{
		if (wcslen(secName) > 8)
		{
			if (className)
			{
				wcscpy(className,secName);
				className[wcslen(secName) - 8] = '\0';
			}

			sec_num = _wtoi(secName + wcslen(secName) - 8);
		}
	}

	int CreateSecNumber(TCHAR* className)
	{
		char strClassName[1024];
		UnicodeToAnsi(className,strClassName,1024);
		return CreateSecNumber(strClassName);
	}

	void Write2INI(TCHAR* className,int sec_num,TCHAR* keyName,const TCHAR* keyValue)
	{
		char strClassName[1024];
		char strKeyName[1024];
		char strKeyValue[1024];
		UnicodeToAnsi(className,strClassName,1024);
		UnicodeToAnsi(keyName,strKeyName,1024);
		UnicodeToAnsi(keyValue,strKeyValue,1024);
		Write2INI(strClassName,sec_num,strKeyName,strKeyValue);
	}

	void Format2Str(wstring& ret)
	{
		string str;

		tagNode* pNode = m_List;
		while(pNode)
		{
			pNode->key_value_list->Format2Str((char*)pNode->section_name,str);
			pNode = pNode->pNext;
		}

		ret.resize(str.size());
		AnsiToUnicode(str.c_str(),(TCHAR*)ret.c_str(),str.size());
	}

	void Write2INI(TCHAR* secName,int sec_num,TCHAR* keyName,int keyValue)
	{
		TCHAR strTemp[32];
		swprintf(strTemp,_T("%d"),keyValue);
		Write2INI(secName,sec_num,keyName,strTemp);
	}

	void WriteIp2INI(TCHAR* secName,int sec_num,TCHAR* keyName,int keyValue)
	{
		TCHAR strTemp[32];
		IpInt2Str(keyValue,strTemp);
		Write2INI(secName,sec_num,keyName,strTemp);
	}

	void WriteTime2INI(TCHAR* secName,int sec_num,TCHAR* keyName,DWORD keyValue)
	{
		TCHAR strTemp[32];
		TimeInt2Str(keyValue,strTemp);
		Write2INI(secName,sec_num,keyName,strTemp);
	}

	void ReadFromINI(TCHAR* className,int sec_num,TCHAR* keyName,TCHAR* keyValue,int keyValueMaxLength,TCHAR* DefaultKeyValue)
	{
		char strClassName[128];
		char strKeyName[128];
		char* pstrKeyValue = new char[keyValueMaxLength];
		CHAR strDefaultValue[1024];
		UnicodeToAnsi(className,strClassName,128);
		UnicodeToAnsi(keyName,strKeyName,128);
		UnicodeToAnsi(DefaultKeyValue,strDefaultValue,1024);
		ReadFromINI(strClassName,sec_num,strKeyName,pstrKeyValue,keyValueMaxLength,strDefaultValue);
		AnsiToUnicode(pstrKeyValue,keyValue,keyValueMaxLength);
		delete []pstrKeyValue;
	}

	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,int& keyValue,int DefaultKeyValue)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%d"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi(strTemp);
	}

	void ReadIpFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,int& keyValue,TCHAR* DefaultIp)
	{
		TCHAR strTemp[1024];
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,DefaultIp);
		keyValue = IpStr2Int(strTemp);
	}

	void ReadIpFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,DWORD& keyValue,TCHAR* DefaultIp)
	{
		TCHAR strTemp[1024];
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,DefaultIp);
		keyValue = IpStr2Int(strTemp);
	}

	void ReadTimeFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,DWORD& keyValue,TCHAR* DefaultIp)
	{
		TCHAR strTemp[1024];
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,DefaultIp);
		keyValue = TimeStr2Int(strTemp);
	}

	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,INT64& keyValue,INT64 DefaultKeyValue)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%I64d"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi64(strTemp);
	}

	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,DWORD& keyValue,DWORD DefaultKeyValue)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%d"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi(strTemp);
	}

	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,bool& keyValue,bool DefaultKeyValue)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%d"),DefaultKeyValue?1:0);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = (_wtoi(strTemp) == 1?true:false);
	}

	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,BYTE& keyValue,bool DefaultKeyValue)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%d"),keyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi(strTemp);
	}

	bool CheckSecExist(TCHAR* className,int sec_num)
	{
		char strClassName[1024];
		UnicodeToAnsi(className,strClassName,1024);
		return CheckSecExist(strClassName,sec_num);
	}

	DWORD GetSectionNums(TCHAR* className)
	{
		char strClassName[1024];
		UnicodeToAnsi(className,strClassName,1024);
		return GetSectionNums(strClassName);
	}

	//----------------------------------------------Write zhanghua---------------------
	//char*
	void Write2INI(TCHAR* className,int sec_num,TCHAR* keyName,const char* keyValue)
	{
		char strClassName[MAX_PATH];
		char strKeyName[MAX_PATH];
		//char strKeyValue[MAX_PATH];
		UnicodeToAnsi(className,strClassName,MAX_PATH);
		UnicodeToAnsi(keyName,strKeyName,MAX_PATH);
		//UnicodeToAnsi(keyValue,strKeyValue,MAX_PATH);
		Write2INI(strClassName,sec_num,strKeyName,keyValue);//strKeyValue);
	}
	//WORD
	void Write2INI(TCHAR* secName,int sec_num,TCHAR* keyName,WORD& keyValue)
	{
		TCHAR strTemp[32];
		swprintf(strTemp,_T("%d"),keyValue);
		Write2INI(secName,sec_num,keyName,strTemp);
	}
	//DWORD
	void Write2INI(TCHAR* secName,int sec_num,TCHAR* keyName,DWORD& keyValue)
	{
		TCHAR strTemp[32];
		swprintf(strTemp,_T("%u"),keyValue);
		Write2INI(secName,sec_num,keyName,strTemp);
	}
	//__int64
	void Write2INI(TCHAR* secName,int sec_num,TCHAR* keyName,__int64& keyValue)
	{
		TCHAR strTemp[32];
		swprintf(strTemp,_T("%I64d"),keyValue);
		Write2INI(secName,sec_num,keyName,strTemp);
	}
	//float
	void Write2INI(TCHAR* secName,int sec_num,TCHAR* keyName,float& keyValue)
	{
		TCHAR strTemp[32];
		swprintf(strTemp,_T("%1.2f"),keyValue);
		Write2INI(secName,sec_num,keyName,strTemp);
	}
	//SYSTEMTIME
	void Write2INI(TCHAR* secName,int sec_num,TCHAR* keyName,SYSTEMTIME keyValue)
	{
		TCHAR strTemp[32] = {0};
		if(keyValue.wYear != 0)
			swprintf(strTemp,_T("%d-%d-%d %d:%d:%d"),keyValue.wYear,keyValue.wMonth,keyValue.wDay,keyValue.wHour,keyValue.wMinute,keyValue.wSecond);
		Write2INI(secName,sec_num,keyName,strTemp);
	};

	//----------------------------------------------Read
	//char*
	void ReadFromINI(TCHAR* className,int sec_num,TCHAR* keyName,char* keyValue,int keyValueMaxLength,const char* DefaultKeyValue = "")
	{
		char strClassName[1024];
		char strKeyName[1024];
		//char strKeyValue[MAX_PATH];
		//CHAR strDefaultValue[MAX_PATH];
		UnicodeToAnsi(className,strClassName,1024);
		UnicodeToAnsi(keyName,strKeyName,1024);
		//UnicodeToAnsi(DefaultKeyValue,strDefaultValue,MAX_PATH);
		ReadFromINI(strClassName,sec_num,strKeyName,/*strKeyValue*/keyValue,keyValueMaxLength,(char*)DefaultKeyValue/*strDefaultValue*/);
		//AnsiToUnicode(strKeyValue,keyValue,keyValueMaxLength);
	}
	//WORD
	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,WORD& keyValue,const WORD DefaultKeyValue = 0)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%d"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi(strTemp);
	}
	//UINT
	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,UINT& keyValue,const UINT DefaultKeyValue = 0)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%u"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi(strTemp);
	}
	//UINT64
	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,UINT64& keyValue,const UINT64 DefaultKeyValue = 0)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%I64d"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtoi64(strTemp);
	}
	//float
	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,float& keyValue,const float DefaultKeyValue = 0.00)
	{
		TCHAR strTemp[1024];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%1.2f"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,1024,strDefaultValue);
		keyValue = _wtof(strTemp);
	}
	//SYSTEMTIME 
	void ReadFromINI(TCHAR* secName,int sec_num,TCHAR* keyName,SYSTEMTIME& keyValue,const int DefaultKeyValue = 0)
	{
		TCHAR strTemp[MAX_PATH];
		TCHAR strDefaultValue[32];
		swprintf(strDefaultValue,_T("%d"),DefaultKeyValue);
		ReadFromINI(secName,sec_num,keyName,strTemp,MAX_PATH,strDefaultValue);

		_stscanf(strTemp,_T("%d-%d-%d %d:%d:%d"),&keyValue.wYear,&keyValue.wMonth,&keyValue.wDay,&keyValue.wHour,&keyValue.wMinute,&keyValue.wSecond);
		if (keyValue.wYear == 0 || keyValue.wMonth==0 || keyValue.wDay==0)
			_stscanf(strTemp,_T("%d/%d/%d %d:%d:%d"),&keyValue.wYear,&keyValue.wMonth,&keyValue.wDay,&keyValue.wHour,&keyValue.wMinute,&keyValue.wSecond);
		if (keyValue.wMonth==0 || keyValue.wDay==0)
		{
			memset(&keyValue,0,sizeof(SYSTEMTIME));
		}
	}

	//----------------------------------------------Write zhanghua---------------------

#endif

};


#pragma pack(pop,MZD_INI_)


#endif