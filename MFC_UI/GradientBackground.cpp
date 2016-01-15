#include "stdafx.h"
#include "GradientBackground.h"


CGradientBackground::CGradientBackground()
{
	r = 200;
	g = 230;
	b = 255;
}

CGradientBackground::CGradientBackground(int R, int G, int B)
{
	r = R;
	g = G;
	b = B;
}


CGradientBackground::~CGradientBackground()
{
}

BEGIN_MESSAGE_MAP(CGradientBackground, CStatic)
	//{{AFX_MSG_MAP(CGroupBox)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGradientBackground::OnPaint()
{
	CPaintDC dc(this);
	CBrush brush;
	CRect rect;
	GetClientRect(&rect);
	for (int m = 0; m < 255; m++)
	{
		brush.DeleteObject();
		brush.CreateSolidBrush(RGB(r + m*(255 - r) / 255, g + m*(255 - g) / 255, b + m*(255 - b) / 255));
		dc.FillRect(CRect(0, 0, rect.Width(), rect.Height() - rect.Height()*m / 255), &brush);
	}
}
