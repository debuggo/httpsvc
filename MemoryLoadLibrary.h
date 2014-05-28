#pragma once

class CMemoryLoadLibrary
{
public:
	CMemoryLoadLibrary(void);
	~CMemoryLoadLibrary(void);
public:
	BOOL		FQ_LoadLibrary(TCHAR*	pDllPath);
private:
	int			FQ_CalcTotalImageSize();
	int			FQ_GetAlignedSize(int Origin, int Alignment);

private:
	void*					m_pMemoryAddress;
	PIMAGE_NT_HEADERS		m_pNTHeader;
	PIMAGE_SECTION_HEADER	m_pSectionHeader;
};
