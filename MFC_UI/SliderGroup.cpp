#include "stdafx.h"
#include "SliderGroup.h"
#include <afxcontrolbarutil.h>

IMPLEMENT_DYNAMIC(CSliderGroup, CWnd)
CSliderGroup::CSliderGroup()
{
	nCurPos = 0;
}


CSliderGroup::~CSliderGroup()
{
}

BEGIN_MESSAGE_MAP(CSliderGroup, CWnd)
	ON_COMMAND(IDC_SLIDER_BUTTON_LEFT, OnDecrease)
	ON_COMMAND(IDC_SLIDER_BUTTON_RIGHT, OnIncrease)
END_MESSAGE_MAP()

void CSliderGroup::OnDecrease()
{
	nCurPos = GetPos()-10;
	if (nCurPos<0)
	{
		SetPos(0);
	}
	else
	{
		SetPos(nCurPos);
	}
	//Invalidate();
	//RedrawWindow();
}

void CSliderGroup::OnIncrease()
{
	nCurPos = GetPos() + 10;
	if (nCurPos > 100)
	{
		SetPos(100);
	}
	else
	{
		SetPos(nCurPos);
	}
	//Invalidate();
	//RedrawWindow();
}

BOOL CSliderGroup::Create(CString text, DWORD style, CRect rc, CWnd* pParent, DWORD id)
{
	// 动态创建控件    
	BOOL res = CWnd::CreateEx(0,AfxRegisterWndClass(0),text, style, rc, pParent, id);
	GetClientRect(&rc);
	btnLeft = new CCommonButton(L"./res/arrow_left_normal.png");
	btnLeft->Create(L"1", WS_CHILD | WS_VISIBLE, CRect(0, rc.bottom / 2 - 5, 20, rc.bottom / 2 + 5), this, IDC_SLIDER_BUTTON_LEFT);
	btnRight = new CCommonButton(L"./res/arrow_right_normal.png", L"./res/arrow_right_down.png");
	btnRight->Create(L"2", WS_CHILD | WS_VISIBLE, CRect(rc.right - 20, rc.bottom / 2 - 5, rc.right, rc.bottom / 2 + 5), this, IDC_SLIDER_BUTTON_RIGHT);
	slider = new CDrawSlider();
	slider->Create(WS_CHILD | WS_VISIBLE | TBS_FIXEDLENGTH | TBS_BOTTOM, CRect(20, rc.top, rc.right - 20, rc.bottom), this, id);
	return res;
}

CSliderCtrl* CSliderGroup::GetSlider()
{
	return slider;
}

void CSliderGroup::SetPos(int nPos)
{
	slider->SetPos(nPos);
}

int CSliderGroup::GetPos()
{
	return slider->GetPos();
}


