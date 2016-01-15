#include "stdafx.h"
#include "ColorText.h"


CColorText::CColorText(COLORREF textColor /*= RGB(255, 0, 0)*/, int textSize /*= 100*/, COLORREF bgColor /*= RGB(240, 240, 240)*/, LPCTSTR m_lpszFaceName /*= L"ËÎÌו"*/)
{
	m_TextColor = textColor;
	m_TextSize = textSize;
	m_BkColor = bgColor;
	m_LpszFaceName = m_lpszFaceName;
	m_TextFont = new CFont();
}


CColorText::~CColorText()
{
}

BEGIN_MESSAGE_MAP(CColorText,CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CColorText::OnPaint()
{
	CRect clientRect;
	GetClientRect(&clientRect);

	m_TextFont->CreatePointFont(m_TextSize, m_LpszFaceName);
	
	CPaintDC dc(this);
	CDC* pDC = &dc;

	pDC->FillRect(&clientRect, &CBrush(m_BkColor));

	pDC->SelectObject(m_TextFont);
	pDC->SetBkMode(TRANSPARENT);
	CString text;
	GetWindowText(text);
	pDC->SetTextColor(m_TextColor);
	pDC->DrawText(text, clientRect, DT_CENTER | DT_VCENTER);
}
