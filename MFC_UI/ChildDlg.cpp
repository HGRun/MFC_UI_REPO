#include "stdafx.h"
#include "ChildDlg.h"

IMPLEMENT_DYNCREATE(CChildDlg,CBaseDlg)
CChildDlg::CChildDlg()
{

}


CChildDlg::~CChildDlg()
{
}

BOOL CChildDlg::Create(CRect& rect, CWnd* pParentWnd /*= NULL*/, UINT nID /*= NULL*/)
{
	return CBaseDlg::CreateEx(L"", rect, pParentWnd, WS_CHILD|WS_VISIBLE, nID);
}

BOOL CChildDlg::Create(int x, int y, int width, int height, CWnd* pParentWnd /*= NULL*/, UINT nID /*= NULL*/)
{
	CRect rect(x, y, width, height);
	return CBaseDlg::CreateEx(L"", rect, pParentWnd, WS_CHILD | WS_VISIBLE, nID);
}
