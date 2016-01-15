#include "stdafx.h"
#include "TabViewCtrl.h"


CTabViewCtrl::CTabViewCtrl()
{
	nItemOld = 0;
}


CTabViewCtrl::~CTabViewCtrl()
{
}

void CTabViewCtrl::insertView(int nItem, LPCTSTR lpszItem, CBaseDlg* dlg)
{
	InsertItem(nItem, lpszItem);
	if (nItem>=dlgs.size())
	{
		dlgs.push_back(dlg);
	} 
	else
	{
		std::vector<CBaseDlg*>::iterator it = dlgs.begin() + nItem;
		dlgs.insert(it, dlg);
	}
	//SetCurSel(nItem);
}

void CTabViewCtrl::OnPaint()
{
	CTabCtrl::OnPaint();
	
}

void CTabViewCtrl::SetCurSel(int nItem)
{
	CTabCtrl::SetCurSel(nItem);
	CRect clientRC;
	GetClientRect(clientRC);
	clientRC.DeflateRect(2, 25, 2, 2);

	//CWnd* oldDlg = dlgs.at(nItemOld);
	//oldDlg->ShowWindow(SW_HIDE);
	for (int i = 0; i < dlgs.size();i++)
	{
		dlgs.at(i)->ShowWindow(SW_HIDE);
	}

	CBaseDlg* dlg = dlgs.at(nItem);
	dlg->MoveWindow(clientRC);
	dlg->ShowWindow(SW_SHOW);

	nItemOld = nItem;
}

BOOL CTabViewCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL result = CTabCtrl::OnChildNotify(message, wParam, lParam, pResult);
	if (*(LPDWORD)((LPBYTE)lParam + 8) == TCN_SELCHANGE)
	{
		CRect clientRC;
		GetClientRect(clientRC);
		clientRC.DeflateRect(2, 25, 2, 2);

		CBaseDlg* oldDlg = dlgs.at(nItemOld);
		oldDlg->ShowWindow(SW_HIDE);

		UINT nItem = GetCurSel();
		CBaseDlg* dlg = dlgs.at(nItem);
		dlg->MoveWindow(clientRC);
		dlg->ShowWindow(SW_SHOW);

		nItemOld = nItem;
	}
	return result;
}

CBaseDlg* CTabViewCtrl::GetItemDlg(UINT nItem)
{
	if (nItem<dlgs.size())
	{
		return dlgs.at(nItem);
	} 
	else
	{
		return NULL;
	}
}
