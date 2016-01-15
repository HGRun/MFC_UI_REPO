// DrawSlider1.cpp : implementation file
//

#include "stdafx.h"
#include "DrawSlider.h"
#include <afxcontrolbarutil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawSlider

CDrawSlider::CDrawSlider()
	:m_bBtnDown(FALSE)
{
	bkColor = RGB(120,120,120);
	font.CreateFontW(13,                                          //   nHeight     
		0,                                                   //   nWidth     
		0,                                                   //   nEscapement   
		0,                                                   //   nOrientation     
		FW_NORMAL,                                   //   nWeight     
		FALSE,                                           //   bItalic     
		FALSE,                                           //   bUnderline     
		0,                                                   //   cStrikeOut     
		ANSI_CHARSET,                             //   nCharSet     
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision     
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision     
		DEFAULT_QUALITY,                       //   nQuality     
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily       
		_T("宋体"));
}

CDrawSlider::~CDrawSlider()
{
}


BEGIN_MESSAGE_MAP(CDrawSlider, CSliderCtrl)
	//{{AFX_MSG_MAP(CDrawSlider)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawSlider message handlers

void CDrawSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	m_bBtnDown = TRUE;	
	CSliderCtrl::OnLButtonDown(nFlags, point);
	Invalidate();
}

void CDrawSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	m_bBtnDown = FALSE;	
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CDrawSlider::OnMouseMove(UINT nFlags, CPoint point)
{
	CSliderCtrl::OnMouseMove(nFlags, point);
	//if (m_bBtnDown = TRUE)
	//{
	//	Invalidate();
	//}
}

void CDrawSlider::OnPaint() 
{
	SetThumbLength(50);

	CPaintDC dc(this);
	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();
	//CPaintDC dc(this);
	//CDC* pDC = &dc;
	pDC->SetBkMode(TRANSPARENT);
	
	//set the text color and the background mode
	CRect ClientRC,ChanelRC;
	GetClientRect(ClientRC);		//获取客户区域
	pDC->FillRect(&ClientRC, &CBrush(RGB(240, 240, 240)));


	//绘制滑块的背景
	GetChannelRect(&ChanelRC);
	pDC->FillRect(&ChanelRC, &CBrush(bkColor));
	CPen pen(PS_SOLID, 1, bkColor);
	CBrush brush(bkColor);
	pDC->SelectObject(&pen);
	pDC->SelectObject(&brush);
	pDC->MoveTo((ChanelRC.left+ChanelRC.right)/2,ChanelRC.top);
	pDC->LineTo((ChanelRC.left + ChanelRC.right) / 2, ChanelRC.top - 4);

	//绘制刻度
	pDC->SelectObject(&font);
	pDC->SetTextColor(bkColor);
	CString strMin;
	strMin.Format(L"%d", GetRangeMin());
	pDC->TextOutW(ChanelRC.left,ChanelRC.bottom,strMin);
	CString strMax;
	strMax.Format(L"%d", GetRangeMax());
	pDC->TextOutW(ChanelRC.right-20, ChanelRC.bottom, strMax);

	//绘制滑块
	CRect ThumbRC;
	GetThumbRect(ThumbRC);			//获取滑块区域
	ThumbRC.right = ThumbRC.left + 10;
	ThumbRC.top = ThumbRC.top + 15;
	ThumbRC.bottom = ThumbRC.top + 20;
	pDC->FillRect(&ThumbRC, &CBrush(RGB(190, 200, 220)));

	//绘制滑块数值
	CString strPos;
	strPos.Format(L"%d", GetPos());
	pDC->TextOutW(ThumbRC.left, ThumbRC.top-15, strPos);

	ReleaseDC(pDC);

}
