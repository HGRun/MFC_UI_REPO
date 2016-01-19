#include "stdafx.h"
#include "PopupDlg.h"
#include "SliderGroup.h"

IMPLEMENT_DYNCREATE(CPopupDlg, CBaseDlg)
CPopupDlg::CPopupDlg()
{
}


CPopupDlg::~CPopupDlg()
{
}

BEGIN_MESSAGE_MAP(CPopupDlg, CBaseDlg)
END_MESSAGE_MAP()

BOOL CPopupDlg::Create(LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	//** when not creating a child window, lpParam should be NULL **//
	//return CWnd::CreateEx(WS_EX_DLGMODALFRAME, AfxRegisterWndClass(0), lpszWindowName, WS_TILEDWINDOW, rect, this, nID,NULL);
	return CBaseDlg::CreateModeDlg(lpszWindowName, rect, TRUE, pParentWnd);
}

BOOL CPopupDlg::Create(LPCTSTR lpszWindowName, int width, int height, CWnd* pParentWnd /*= NULL*/, UINT nID /*= NULL*/)
{
	//** when not creating a child window, lpParam should be NULL **//
	CRect rect(0, 0, width, height);
	return CBaseDlg::CreateModeDlg(lpszWindowName, rect, TRUE, pParentWnd);
}

BOOL CPopupDlg::Create(LPCTSTR lpszWindowName, int width, int height, BOOL bMode, CWnd* pParentWnd /*= NULL*/, UINT nID /*= NULL*/)
{
	CRect rect(0, 0, width, height);
	if (bMode)
	{
		return CBaseDlg::CreateModeDlg(lpszWindowName, rect, TRUE, pParentWnd);
	}
	else
	{
		return CWnd::CreateEx(WS_EX_DLGMODALFRAME, AfxRegisterWndClass(0), lpszWindowName, WS_TILEDWINDOW, rect, this, nID, NULL);
	}
}
