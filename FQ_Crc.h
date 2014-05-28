#pragma once


class CFQ_Crc
{
public:
	CFQ_Crc(void);
	~CFQ_Crc(void);

	VOID			InitCrc();
	ULONG			Reflect(ULONG ref,char ch);
	ULONG			GetCrc(char *pszData, DWORD dwSize);

};
