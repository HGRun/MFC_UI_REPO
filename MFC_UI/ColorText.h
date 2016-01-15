#pragma once
#include "afxwin.h"
#include "CPropertyBuilder.h"
class CColorText :
	public CStatic
{
public:
	CColorText(COLORREF textColor = RGB(255, 0, 0), int textSize = 100, COLORREF bgColor = RGB(240, 240, 240), LPCTSTR m_lpszFaceName = L"ËÎÌו");
	~CColorText();

	DECLARE_MESSAGE_MAP()

	CPROPERTY_BUILD(COLORREF, BkColor,CColorText*)

	CPROPERTY_BUILD(COLORREF, TextColor, CColorText*)

	CPROPERTY_BUILD(int, TextSize, CColorText*)

	CPROPERTY_BUILD(LPCTSTR, LpszFaceName, CColorText*)

		//CPROPERTY_BUILD(CFont*, TextFont)
		CFont* m_TextFont;
	//void SetTextFont(CFont* v){
	//	m_TextFont = v;
	//};

	afx_msg void OnPaint();
};

