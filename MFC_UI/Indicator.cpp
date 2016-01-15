#include "stdafx.h"
#include "Indicator.h"

IMPLEMENT_DYNAMIC(CIndicator, CStatic)
CIndicator::CIndicator(COLORREF highlightColor/*=RGB(255,0,0)*/,COLORREF normalColor/*=RGB(255,255,255)*/)
{
	this->highlightColor = highlightColor;
	this->normalColor = normalColor;
	bHighLight = TRUE;
}


CIndicator::~CIndicator()
{
}
BEGIN_MESSAGE_MAP(CIndicator, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()
void CIndicator::OnPaint()
{
	CRect clienRect;
	GetClientRect(&clienRect);
	if (clienRect.right<clienRect.bottom)
	{
		clienRect.right = clienRect.bottom;
	} 
	else
	{
		clienRect.bottom = clienRect.right;
	}

	CPaintDC dc(this);
	CDC* pDC = &dc;
	CBrush brush;

	if (bHighLight)
	{
		brush.CreateSolidBrush(highlightColor);
		pDC->SelectObject(&brush);
		pDC->Ellipse(&clienRect);
	} 
	else
	{
		brush.CreateSolidBrush(normalColor);
		pDC->SelectObject(&brush);
		pDC->Ellipse(&clienRect);
	}
}

void CIndicator::SetHighLight(BOOL bHighLight)
{
	this->bHighLight = bHighLight;
}

BOOL CIndicator::getHighLight()
{
	return bHighLight;
}
