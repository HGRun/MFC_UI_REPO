#pragma once
#include "afxwin.h"
#include "CBaseDlg.h"

#define IDC_POP_OK 1
#define IDC_POP_CANCEL 2

class CPopupDlg :
	public CBaseDlg
{
	DECLARE_DYNCREATE(CPopupDlg)

public:
	CPopupDlg();
	~CPopupDlg();

	virtual BOOL Create(LPCTSTR lpszWindowName, const RECT& rect, CWnd* pParentWnd = NULL, UINT nID = NULL);
	virtual BOOL Create(LPCTSTR lpszWindowName, int width, int height, CWnd* pParentWnd = NULL, UINT nID = NULL);
	virtual BOOL Create(LPCTSTR lpszWindowName, int width, int height, BOOL bMode, CWnd* pParentWnd = NULL, UINT nID = NULL);
	DECLARE_MESSAGE_MAP()
};

