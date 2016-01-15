#pragma once
#include "CBaseDlg.h"
class CChildDlg :
	public CBaseDlg
{
	DECLARE_DYNCREATE(CChildDlg)

public:
	CChildDlg();
	~CChildDlg();

	virtual BOOL Create(CRect& rect, CWnd* pParentWnd = NULL, UINT nID = NULL);
	virtual BOOL Create(int x, int y, int width, int height, CWnd* pParentWnd = NULL, UINT nID = NULL);
};

