#pragma once
#define DLG_TEMPLATE_BUFFER_MAX_LENGT 1024
class CMyDlgTemplate
{
public:
	CMyDlgTemplate(int nBufferLength = DLG_TEMPLATE_BUFFER_MAX_LENGT);
	~CMyDlgTemplate();

private:
	WORD* m_pBuffer;
public:
	DLGTEMPLATE* CreateTemplate(DWORD dwStyle, CRect& rect, CString strCaption, DWORD dwStyleEx = 0);
};

