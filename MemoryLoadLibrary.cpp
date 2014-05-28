
#include <windows.h>
#include "MemoryLoadLibrary.h"

CMemoryLoadLibrary::CMemoryLoadLibrary(void)
{
	m_pMemoryAddress = NULL;
	m_pNTHeader = NULL;
	m_pSectionHeader = NULL;
}

CMemoryLoadLibrary::~CMemoryLoadLibrary(void)
{
}

BOOL		CMemoryLoadLibrary::FQ_LoadLibrary(TCHAR *pDllPath)
{
	if (m_pMemoryAddress)
	{
		return FALSE;
	}
	HANDLE	hFile = CreateFile(pDllPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	DWORD	dwFileLen = 0;
	GetFileSize(hFile,&dwFileLen);
	void*	pModule = (HMODULE)GlobalAlloc(GPTR,dwFileLen);
	if (pModule == NULL)
	{
		CloseHandle(hFile);
		return NULL;
	}
	DWORD	dwFileByteLen;
	ReadFile(hFile,pModule,dwFileLen,&dwFileByteLen,NULL);
	if (dwFileByteLen != dwFileLen)
	{
		GlobalFree(pModule);
		CloseHandle(hFile);
		return FALSE;
	}
	CloseHandle(hFile);


	PIMAGE_DOS_HEADER	pDosHeader = (PIMAGE_DOS_HEADER)pModule; //��ȡDOSͷ
	if(pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return FALSE;
	if((DWORD)dwFileLen < (pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS))) //��鳤��
		return FALSE;
	m_pNTHeader = (PIMAGE_NT_HEADERS)( (unsigned long)pModule + pDosHeader->e_lfanew);// ��ȡPEͷ
	if(m_pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return FALSE;
	if((m_pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL) == 0) //0��2000: File is a DLL
		return FALSE;
	if((m_pNTHeader->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0) //0��0002: ָ���ļ���������
		return FALSE;
	if(m_pNTHeader->FileHeader.SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER))
		return FALSE;

	m_pSectionHeader = (PIMAGE_SECTION_HEADER)((int)m_pNTHeader + sizeof(IMAGE_NT_HEADERS));//ȡ�ýڱ��α�
	for(int i = 0; i< m_pNTHeader->FileHeader.NumberOfSections; i++)
	{
		//��֤ÿ���ڱ�Ŀռ�
		if((m_pSectionHeader[i].PointerToRawData + m_pSectionHeader[i].SizeOfRawData) > (DWORD)dwFileLen)
			return FALSE;
	}

}

int		CMemoryLoadLibrary::FQ_CalcTotalImageSize()
{
	int Size;
	if(m_pNTHeader == NULL)return 0;
	int nAlign = m_pNTHeader->OptionalHeader.SectionAlignment; //�ζ����ֽ���

	// ��������ͷ�ĳߴ硣����dos, coff, peͷ �� �α�Ĵ�С
	Size = FQ_GetAlignedSize(m_pNTHeader->OptionalHeader.SizeOfHeaders, nAlign);
	// �������нڵĴ�С
	for(int i = 0; i < m_pNTHeader->FileHeader.NumberOfSections; ++i)
	{
		//�õ��ýڵĴ�С
		int CodeSize = m_pSectionHeader[i].Misc.VirtualSize ;
		int LoadSize = m_pSectionHeader[i].SizeOfRawData;
		int MaxSize = (LoadSize > CodeSize) ? (LoadSize):(CodeSize);

		int SectionSize = FQ_GetAlignedSize(m_pSectionHeader[i].VirtualAddress + MaxSize, nAlign);
		if(Size < SectionSize)
			Size = SectionSize; //Use the Max;
	}
	return Size;

}

int		CMemoryLoadLibrary::FQ_GetAlignedSize(int Origin, int Alignment)
{
	return (Origin + Alignment - 1) / Alignment * Alignment;
}