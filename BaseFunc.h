#ifndef BASE_FUNC_H
#define BASE_FUNC_H
#include <io.h>
#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <time.h>
#include "Shlwapi.h"
#include <WinIoCtl.h>
#include <vector>
#include <string>
#include <map>
#include <tchar.h>
#include <cstring>
using namespace std;

#pragma  warning(disable:4996) 
#pragma  warning(disable:4244) 

#pragma comment(lib,"ws2_32")

//这里保存着不依赖于其他函数库的公共函数

typedef BYTE u8;
typedef WORD u16;
typedef DWORD u32;
typedef INT64 u64;

#ifdef MZDIO
#define MZD_CHAR char
#define MZD_T(x) x
#define MZD_MEMSET memset
#define MZD_MEMCPY memcpy
#define MZD_MEMCPY_S memcpy_s
#define MZD_SPRINTF_S sprintf_s
#define MZD_SPRINTF sprintf
#define MZD_STRSTR strstr
#define MZD_STRLEN strlen
#define MZD_STRCPY strcpy
#define MZD_STRING string
#define MZD_STRCPY_S strcpy_s
#define MZD_STRCAT strcat
#define MZD_STRCAT_S strcat_s
#define MZD_STRCMP strcmp
#define MZD_ATOI atoi
#define __MZD_FUNCTION__ __FUNCTION__
#define STR(a) #a
#else
#define MZD_CHAR wchar_t
#define MZD_T(x) L##x
#define MZD_MEMSET wmemset
#define MZD_MEMCPY wmemcpy
#define MZD_MEMCPY_S wmemcpy_s
#define MZD_SPRINTF_S swprintf_s
#define MZD_SPRINTF swprintf
#define MZD_STRSTR wcsstr
#define MZD_STRLEN wcslen
#define MZD_STRCPY wcscpy
#define MZD_STRING wstring
#define MZD_STRCPY_S wcscpy_s
#define MZD_STRCAT wcscat
#define MZD_STRCAT_S wcscat_s
#define MZD_STRCMP wcscmp
#define MZD_ATOI _wtoi
#define __MZD_FUNCTION__ __FUNCTIONW__
#define STR(a) L###a
#endif

#define MZD_SAFE_MEMCPY(pDes,pSrc,length) do {MZD_MEMCPY(pDes,pSrc,length);pDes[length - 1] = '\0';} while (0);

#define GETCLASSNAME(a,b) do{MZD_MEMSET(a,0,b);MZD_STRCPY_S(a,b,__MZD_FUNCTION__);MZD_CHAR* pPos = MZD_STRSTR(a,MZD_T("::"));if (pPos){*pPos = '\0';}} while (0);


inline int AnsiToUnicode( const char* szStr,wchar_t* pOutStr,int outMaxLength)
{
	//memset(pOutStr,0,outMaxLength);
	//int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	//if (nLen == 0)
	//{
	//	return 0;
	//}
	//else
	//{
	//	if (nLen > outMaxLength)
	//	{
	//		return -nLen;
	//	}
	//	else
	//	{
	//		MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pOutStr, nLen );
	//		return nLen;
	//	}
	//}
	return MultiByteToWideChar(CP_ACP,0,szStr,-1,pOutStr,outMaxLength);
}
//----------------------------------------------------------------------------------
// 将 宽字节wchar_t* 转换 单字节char*
inline int UnicodeToAnsi( const wchar_t* szStr,char* pStr,int outMaxLength)
{
	memset(pStr,0,outMaxLength);
	int nLen = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );
	if (nLen == 0)
	{
		return 0;
	}else
	{
		if (nLen > outMaxLength)
		{
			return -nLen;
		}else
		{
			WideCharToMultiByte( CP_ACP, 0, szStr, -1, pStr, nLen, NULL, NULL );
			return nLen;
		}
	}
}


inline void IpInt2Str(DWORD ip,char* strIp)
{
	in_addr addr;
	addr.s_addr = ip;
	strcpy(strIp,inet_ntoa(addr));
}

inline void IpInt2Str(DWORD ip,WCHAR* strIp)
{
	char tempIp[32];
	in_addr addr;
	addr.s_addr = ip;
	strcpy(tempIp,inet_ntoa(addr));
	AnsiToUnicode(tempIp,strIp,32);
}

inline unsigned long IpStr2Int(char* strIp)
{
	return inet_addr(strIp);
}

inline unsigned long IpStr2Int(WCHAR* strIp)
{
	char tempIp[32];
	UnicodeToAnsi(strIp,tempIp,32);
	return inet_addr(tempIp);
}

inline unsigned long TimeStr2Int(char* strTime)
{
	struct tm tmtime={0};;
	if (strTime&& strlen(strTime) > 5)
	{
		tmtime.tm_year = atoi(strTime) - 1900;
		strTime += 5;

		if (strTime&& strlen(strTime) > 3)
		{
			tmtime.tm_mon = atoi(strTime);
			strTime += 3;

			if (strTime&& strlen(strTime) > 3)
			{
				tmtime.tm_hour = atoi(strTime);
				strTime += 3;

				if (strTime&& strlen(strTime) > 3)
				{
					tmtime.tm_min = atoi(strTime);
					strTime += 3;

					if (strTime&& strlen(strTime) > 3)
					{
						tmtime.tm_sec = atoi(strTime);
					}
				}
			}
		}
	}

	return mktime(&tmtime);
}

inline unsigned long TimeStr2Int(WCHAR* strTime)
{
	struct tm tmtime={0};
	if (strTime&& wcslen(strTime) > 5)
	{
		tmtime.tm_year = _wtoi(strTime) - 1900;
		strTime += 5;

		if (strTime&& wcslen(strTime) > 3)
		{
			tmtime.tm_mon = _wtoi(strTime);
			strTime += 3;

			if (strTime&& wcslen(strTime) > 3)
			{
				tmtime.tm_hour = _wtoi(strTime);
				strTime += 3;

				if (strTime&& wcslen(strTime) > 3)
				{
					tmtime.tm_min = _wtoi(strTime);
					strTime += 3;

					if (strTime)
					{
						tmtime.tm_sec = _wtoi(strTime);
					}
				}
			}
		}
	}
	return mktime(&tmtime);
}

inline void TimeInt2Str(DWORD time,char* strTime)
{
	struct tm *local;
	time_t tt = time;
	local=localtime(&tt);
	sprintf(strTime,"%04d %02d %02d:%02d:%02d",local->tm_year + 1900,local->tm_mon,local->tm_hour,local->tm_min,local->tm_sec);
}

inline void TimeInt2Str(DWORD time,WCHAR* strTime)
{
	struct tm *local;
	time_t tt = time;
	local=localtime(&tt);
	swprintf(strTime,_T("%04d %02d %02d:%02d:%02d"),local->tm_year + 1900,local->tm_mon,local->tm_hour,local->tm_min,local->tm_sec);
}


inline bool IsLocalIp(int ip)
{
	char   szHostName[128];
	unsigned   long   *   pLocalIP=NULL; 
	if (ip == inet_addr("127.0.0.1"))
	{
		return true;
	}

	if(   gethostname(szHostName,   128)   ==   0   )
	{
		//   Get   host   adresses
		struct   hostent   *   pHost;
		int   i;

		pHost   =   gethostbyname(szHostName);

		for(   i   =   0;   pHost!=   NULL   &&   pHost-> h_addr_list[i]!=   NULL;   i++   )
		{
			pLocalIP = (unsigned   long   *)pHost->h_addr_list[i];
			if ( *pLocalIP == ip)
			{
				return true;
			}
		}
	} 
	return false;
}


//************************************
// 方法:	GetNumberFromString
// 权限:	public 
// 返回:	BOOL
// 参数:	IN const TCHAR * strString
// 参数:	OUT TCHAR * strNumber
// 说明:	分析字符串中的数字并以TCHAR方式返回
//************************************
//inline BOOL GetNumberFromString(IN const TCHAR* strString, OUT TCHAR* strNumber)
//{
//	if (_tcslen(strString) == 0 || strNumber == NULL)
//	{
//		return FALSE;
//	}
//	
//	int nFlag = 1, i = 0, j =0, h = 0;
//	double m = 0, sum = 0, n=0;
//	for (; i < _tcslen(strString); ++i)
//	{
//		if ( (strString[i] <= '9' && strString[i] >= '0') || strString[i] == '+' || strString[i] == '-' )
//			break;
//		else
//			j++;
//	}
//	if (strString[i] == '-')
//		nFlag = -1;
//	if (strString[i] == '-' || strString[i] == '+')
//		j++;
//	i = j;
//
//	h=j;
//	for(; i < _tcslen(strString); i++)
//	{
//		if( (strString[i] <= '9' && strString[i] >= '0') || strString[i] == '.')
//			h++;
//		else
//			break;
//	}
//	h -= 1;
//
//	if (j<h && strString[h] != '.')
//	{
//		for (j++; j <= h; h--)
//		{
//			m = m*0.1+strString[h] - '0';
//		}
//		m *= 0.1;
//	}
//	sum = n + m;
//	sum = sum * nFlag;
//#ifdef _UNICODE
//	_itow(sum, strNumber, 10);
//#else
//	_itoa_s(sum, strNumber, 10);
//#endif // _UNICODE
//	return TRUE;
//}
#endif