#include "stdafx.h"
#include "MyDlgTemplate.h"


CMyDlgTemplate::CMyDlgTemplate(int nBufferLength)
{
	m_pBuffer = new WORD[nBufferLength];
	if ((!m_pBuffer) || (DLG_TEMPLATE_BUFFER_MAX_LENGT > nBufferLength))
	{
		exit(0);
	}
}


CMyDlgTemplate::~CMyDlgTemplate()
{
}

DLGTEMPLATE* CMyDlgTemplate::CreateTemplate(DWORD dwStyle, CRect& rect, CString strCaption, DWORD dwStyleEx /*= 0*/)
{
	WORD* pTemp = m_pBuffer;
	DLGTEMPLATE* pDlgTemp = (DLGTEMPLATE*)pTemp;
	// 对话框模版
	pDlgTemp->style = dwStyle;
	pDlgTemp->dwExtendedStyle = dwStyleEx;
	pDlgTemp->cdit = 0;
	pDlgTemp->cx = rect.Width();
	pDlgTemp->cy = rect.Height();
	pDlgTemp->x = (short)rect.left;
	pDlgTemp->y = (short)rect.top;
	pTemp = (WORD*)(pDlgTemp + 1);
	// 菜单
	*pTemp++ = 0;
	// class
	*pTemp++ = 0;
	// caption
	//wcscpy((WCHAR*)pTemp, strCaption);
	wcscpy_s((WCHAR*)pTemp, 1000, strCaption);
	pTemp += strCaption.GetLength() + 1;
	// font
	return pDlgTemp;
}
