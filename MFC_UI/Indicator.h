#pragma once
#include "afxwin.h"
class CIndicator :
	public CStatic
{
	DECLARE_DYNAMIC(CIndicator)
public:
	CIndicator(COLORREF highlightColor=RGB(255,0,0),COLORREF normalColor=RGB(255,255,255));
	~CIndicator();

	DECLARE_MESSAGE_MAP()
	COLORREF normalColor;
	COLORREF highlightColor;
	BOOL bHighLight;
	afx_msg void OnPaint();
	afx_msg void SetHighLight(BOOL bHighLight);
	afx_msg BOOL getHighLight();
};

