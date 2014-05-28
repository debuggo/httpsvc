#pragma once
#include <map>

using namespace std;

typedef	struct	_HtmlInfo
{
	TCHAR			lpwzsRelativePath[260];
	ULONG			ulFileLength;
	PVOID			lpData;
}HtmlInfo, *pHtmlInfo;

typedef	std::map<CString, pHtmlInfo>	Map_HtmlList;
typedef	Map_HtmlList::iterator			Iter_HtmlList;

class CHtmlFile
{
public:
	CHtmlFile(void);
	~CHtmlFile(void);
	VOID			InitHtmlFile();
	pHtmlInfo		GetHtmlFile(CString	HtmlPath);
	BOOL			IsModule();
public:
	Map_HtmlList	m_MapHtmlList;	//html文件列表<路径,HtmlInfo结构>
	BOOL			m_Module;
};
