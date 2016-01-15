#pragma once
#include "afxcmn.h"
#include <vector>
#include "CBaseDlg.h"
class CBaseDlg;
class CTabViewCtrl :
	public CTabCtrl
{
public:
	CTabViewCtrl();
	~CTabViewCtrl();

	std::vector<CBaseDlg*> dlgs;
	int nItemOld;

	void insertView(int nItem, LPCTSTR lpszItem, CBaseDlg* dlg);
	void OnPaint();
	void SetCurSel(int nItem);
	virtual BOOL OnChildNotify(UINT message,WPARAM wParam,LPARAM lParam,LRESULT* pResult);
	CBaseDlg* GetItemDlg(UINT nItem);
	//CTabCtrl::GetItemDlg
};

