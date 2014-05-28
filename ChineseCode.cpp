#include "FQ_Std.h"
#include "ChineseCode.h"

CChineseCode::CChineseCode(void)
{
}

CChineseCode::~CChineseCode(void)
{
}


DWORD	WINAPI	CChineseCode::UniCodeToUtf8(LPCWSTR lpWstr, LPSTR lpAstr)
{
	int WStrLen = ::WideCharToMultiByte(CP_UTF8,0,lpWstr,-1,NULL,0,NULL,NULL);
	WideCharToMultiByte(CP_UTF8,0,lpWstr,-1,lpAstr,WStrLen,NULL,NULL);
	return WStrLen;
}

DWORD	WINAPI CChineseCode::Utf8ToUniCode(LPSTR lpAstr, LPWSTR lpWstr)
{
	int ZStrLen = MultiByteToWideChar(CP_UTF8,0,lpAstr,-1,NULL,0);
	MultiByteToWideChar(CP_UTF8,0,lpAstr,-1,lpWstr,ZStrLen);
	return ZStrLen;
}

DWORD	WINAPI	CChineseCode::UniCodeToAscii(LPSTR	lpAscii, LPWSTR	lpUniCode)
{
	int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, lpUniCode, wcslen(lpUniCode), NULL, 0, NULL, NULL); 
	WideCharToMultiByte(CP_ACP, NULL, lpUniCode, wcslen(lpUniCode), lpAscii, ansiLen, NULL, NULL); 
	return ansiLen;
}

DWORD	WINAPI	CChineseCode::Utf8ToAscii(LPSTR	lpUtf8, LPSTR lpAscii)
{
	int ZStrLen = MultiByteToWideChar(CP_UTF8,0,lpUtf8,-1,NULL,0);
	wchar_t*	wszString = new wchar_t[ZStrLen + 1];
	memset(wszString,0,(ZStrLen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8,0,lpUtf8,-1,wszString,ZStrLen);
	int iRet = UniCodeToAscii(lpAscii,wszString);
	delete	[]wszString;
	return iRet;
}

DWORD	WINAPI	CChineseCode::AsciiToUnicode(LPWSTR lpUniCode, LPSTR lpAscii)
{
	int nLength = MultiByteToWideChar(CP_ACP,0,lpAscii,strlen(lpAscii),NULL,0);
	MultiByteToWideChar(CP_ACP,0,lpAscii,strlen(lpAscii),lpUniCode,nLength);
	return nLength;
}


DWORD	WINAPI	ToInternetProtocolW(wchar_t*	lpwszIp)
{
	DWORD	dwRet = 0;

	int		nAddress[4] = { 0 };
	swscanf(lpwszIp,_T("%d.%d.%d.%d"),&nAddress[0],&nAddress[1],&nAddress[2],&nAddress[3]);

	byte	bArray[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		bArray[i] = nAddress[i];
	}
	memcpy(&dwRet,bArray,sizeof(DWORD));
	return dwRet;
}

DWORD	WINAPI	ToInternetProtocolA(char*	lpszIp)
{
	DWORD	dwRet = 0;

	int		nAddress[4] = { 0 };
	sscanf(lpszIp,"%d.%d.%d.%d",&nAddress[0],&nAddress[1],&nAddress[2],&nAddress[3]);

	byte	bArray[4] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		bArray[i] = nAddress[i];
	}
	memcpy(&dwRet,bArray,sizeof(DWORD));
	return dwRet;
}

int		WINAPI	ToDwordByInternetProtocolW(DWORD	dwInDword, wchar_t*	lpwszOut)
{
	byte	bAddress[4] = { 0 };

	bAddress[0] = dwInDword;
	bAddress[1] = dwInDword >> 8;
	bAddress[2] = dwInDword >> 16;
	bAddress[3] = dwInDword >> 24;

	wsprintfW(lpwszOut,_T("%d.%d.%d.%d"),bAddress[0],bAddress[1],bAddress[2],bAddress[3]);
	return 1;
}

int		WINAPI	ToDwordByInternetProtocolA(DWORD	dwInDword, char*	lpszOut)
{
	byte	bAddress[4] = { 0 };

	bAddress[0] = dwInDword;
	bAddress[1] = dwInDword >> 8;
	bAddress[2] = dwInDword >> 16;
	bAddress[3] = dwInDword >> 24;

	wsprintfA(lpszOut,"%d.%d.%d.%d",bAddress[0],bAddress[1],bAddress[2],bAddress[3]);
	return 1;
}