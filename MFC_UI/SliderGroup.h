#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "DrawSlider.h"
#include "ImageButton.h"

#define IDC_SLIDER_BUTTON_LEFT 30000
#define IDC_SLIDER_BUTTON_RIGHT 30001

class CSliderGroup :
	public CWnd
{
	DECLARE_DYNAMIC(CSliderGroup)
protected:
	DECLARE_MESSAGE_MAP()

	void OnDecrease();
	void OnIncrease();

	int nCurPos;

	CCommonButton* btnLeft;
	CCommonButton* btnRight;
	CDrawSlider* slider;

public:
	CSliderGroup();
	~CSliderGroup();

	BOOL Create(CString text, DWORD style, CRect rc, CWnd* pParent, DWORD id = 0);
	CSliderCtrl* GetSlider();
	void SetPos(int nPos);
	int GetPos();
};

