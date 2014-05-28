#include "FQ_Std.h"
#include "FQ_Crc.h"


ULONG	m_Table[255] = { 0 };

CFQ_Crc::CFQ_Crc(void)
{
}

CFQ_Crc::~CFQ_Crc(void)
{
}


VOID	CFQ_Crc::InitCrc()
{
	ULONG ulPolynomial = 0x04c11db7;
	for(int i = 0; i <= 255; i++)
	{
		m_Table[i] = Reflect(i, 8) << 24;
		for(int j = 0; j < 8; j++)
		{
			m_Table[i] = (m_Table[i] << 1) ^ (m_Table[i] & (1 << 31) ? ulPolynomial : 0);
		}
		m_Table[i] = Reflect(m_Table[i], 32);
	}
}

ULONG	CFQ_Crc::Reflect(ULONG ref,char ch)
{
	ULONG value = NULL;

	for(int i = 1; i < (ch + 1); i++)
	{
		if(ref & 1)
		{
			value |= 1 << (ch - i);
		}
		ref >>= 1;
	}
	return value;
}

//************************************
// 方法名:	GetCrc
// 全名称:	CFQ_Crc::GetCrc
// 访问级:	public 
// 返回值:	ULONG
// 限定符:	
// 参  数:	char * pszData	数据
// 参  数:	DWORD dwSize	大小
// 备  注:	获取CRC编码
//************************************
ULONG	CFQ_Crc::GetCrc(char *pszData, DWORD dwSize)
{
	ULONG  crc(0xffffffff);
	int len;
	unsigned char* buffer;

	len = dwSize;
	buffer = (unsigned char*)pszData;
	while(len--)
	{
		crc = (crc >> 8) ^ m_Table[(crc & 0xFF) ^ * buffer++];
	}
	return crc^0xffffffff;
}