#include "FQ_Std.h"
#include "HtmlFile.h"
#include "mylog.h"

CHtmlFile::CHtmlFile(void)
{
	m_Module = FALSE;
}

CHtmlFile::~CHtmlFile(void)
{
}


//����WEB�ļ�
VOID	CHtmlFile::InitHtmlFile()
{
	TCHAR	lpwzsPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL,lpwzsPath,MAX_PATH);
	CString	strPath(lpwzsPath);	//�ļ�·��
	int nPos = strPath.ReverseFind('\\');
	CString	strWebFile = strPath.Left(nPos + 1);
	strWebFile += _T("WEB.FQ");	//WEB.FQΪWEB����ļ�

	WRITE_LOGLINE(LOG_LEVEL_DEBUG,_T("��ʼ��ȡWeb�ļ� : %s\r\n"),strWebFile.GetBuffer());
	
	CFile	hFile;
	BOOL	hIS = hFile.Open(strWebFile.GetBuffer(),CFile::modeRead);
	if (!hIS)
	{
		WRITE_LOGLINE(LOG_LEVEL_ERROR,_T("%s û���ҵ���\r\n"),strWebFile.GetBuffer());
		return;
	}
	int		nNumber;
	hFile.Read(&nNumber,sizeof(int));
	
	for (int i = 0; i < nNumber; i++)
	{
		pHtmlInfo	pHtml = new HtmlInfo;
		memset(pHtml,0,sizeof(HtmlInfo));
		hFile.Read(pHtml,sizeof(HtmlInfo));
		//pHtml->lpData  = (PVOID)GlobalAlloc(GPTR,pHtml->ulFileLength);	//����ȫ���ڴ�
		pHtml->lpData = new char[pHtml->ulFileLength];
		hFile.Read(pHtml->lpData,pHtml->ulFileLength);	//��ȡHtml�е�����

		CString	strHtmlKey(pHtml->lpwzsRelativePath);
		m_MapHtmlList.insert(Map_HtmlList::value_type(strHtmlKey,pHtml));
		delete pHtml;
	}
	m_Module = TRUE;
	hFile.Close();
}

pHtmlInfo		CHtmlFile::GetHtmlFile(CString	HtmlPath)
{
	Iter_HtmlList Iter = m_MapHtmlList.find(HtmlPath);
	if (Iter != m_MapHtmlList.end())
	{
		return Iter->second;
	}
	return NULL;
}

BOOL			CHtmlFile::IsModule()
{
	return m_Module;
}