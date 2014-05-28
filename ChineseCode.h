#pragma once

class CChineseCode
{
public:
	CChineseCode(void);
	~CChineseCode(void);
	static	DWORD	WINAPI	UniCodeToUtf8(LPCWSTR	lpWstr,LPSTR	lpAstr);
	static	DWORD	WINAPI	Utf8ToUniCode(LPSTR	lpAstr, LPWSTR	lpWstr);
	static	DWORD	WINAPI	Utf8ToAscii(LPSTR	lpUtf8, LPSTR lpAscii);
	static	DWORD	WINAPI	UniCodeToAscii(LPSTR	lpAscii, LPWSTR	lpUniCode);
	static	DWORD	WINAPI	AsciiToUnicode(LPWSTR	lpUniCode, LPSTR	lpAscii);
};

extern "C"
{
	DWORD	WINAPI	ToInternetProtocolW(wchar_t*	lpwszIp);

	DWORD	WINAPI	ToInternetProtocolA(char*	lpszIp);

	int		WINAPI	ToDwordByInternetProtocolW(DWORD	dwInDword, wchar_t*	lpwszOut);

	int		WINAPI	ToDwordByInternetProtocolA(DWORD	dwInDword, char*	lpszOut);
};