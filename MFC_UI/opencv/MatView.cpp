#include "stdafx.h"
#include "MatView.h"

IMPLEMENT_DYNCREATE(CMatView,CWnd)
CMatView::CMatView()
		:m_IsInit(FALSE),
		m_IsPress(FALSE),
		xOff(0),
		yOff(20),
		m_BkColor(RGB(240,240,240))
{
}


CMatView::~CMatView()
{
}

BEGIN_MESSAGE_MAP(CMatView,CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BOOL CMatView::Create(CString sCaption, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	m_Caption = sCaption;
	return CWnd::Create(AfxRegisterWndClass(0), L"", WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID);
}

void CMatView::OnPaint()
{
	IplImage* iplImg = &IplImage(m_Mat);
	if (m_Mat.empty())
	{
		return;
	}
	CDC *pDC = GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect clientRect;
	GetClientRect(&clientRect);
	// output caption
	if (!m_IsInit)
	{
		pDC->FillRect(&CRect(10, 0, clientRect.right, 20), &CBrush(m_BkColor));
		pDC->DrawText(m_Caption, &CRect(10, 0, clientRect.right, 20),100);
	}
	// draw mat
	CRect rect;
	xOff = 10;// (clientRect.Width() - m_Mat.cols) / 2;
	rect.left = xOff;
	rect.right = rect.left + m_Mat.cols;
	rect.top = 20;
	rect.bottom = rect.top + m_Mat.rows;
	cimg.CopyOf(iplImg); // 复制图片
	cimg.DrawToHDC(hDC, &rect); // 将图片绘制到显示控件的指定区域内
	// draw informations of mat
	if (!m_IsInit)
	{
		CString str;
		str.Format(L"width:%d,height:%d,channels:%d,type:%d", m_Mat.cols, m_Mat.rows, m_Mat.channels(), m_Mat.type());
		pDC->FillRect(&CRect(10, rect.bottom, clientRect.right, rect.bottom + 20), &CBrush(m_BkColor));
		pDC->DrawText(str, &CRect(10, rect.bottom, clientRect.right, rect.bottom + 20), 100);
	}
	if (m_IsPress)
	{
		Point point = ClientToMat(m_SelectPoint);
		CString str;
		if (m_Mat.channels()==1)
		{
			uchar val = m_Mat.at<uchar>(point);
			str.Format(L"(%d,%d):%d", point.x, point.y, val);
		}
		else if (m_Mat.channels() == 3)
		{
			Vec3b intensity = m_Mat.at<Vec3b>(point);
			uchar blue = intensity.val[0];
			uchar green = intensity.val[1];
			uchar red = intensity.val[2];
			str.Format(L"(%d,%d):(R:%d,G:%d,B:%d)", point.x, point.y, red, green, blue);
		}
		pDC->FillRect(&CRect(10, rect.bottom + 20, clientRect.right, rect.bottom + 40), &CBrush(m_BkColor));
		pDC->DrawText(str, &CRect(10, rect.bottom + 20, clientRect.right, rect.bottom + 40), 100);
	}
	ReleaseDC(pDC);
	m_IsInit = TRUE;
}

BOOL CMatView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CMatView::OnMouseMove(UINT nFlags, CPoint point)
{
	//CWnd::OnMouseMove(nFlags, point);
	if (m_IsPress)
	{

	}
}

void CMatView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CWnd::OnLButtonDown(nFlags, point);
	m_IsPress = TRUE;
	m_SelectPoint = point;
	//CString str;
	//str.Format(L"%d,%d\r\n", point.x, point.y);
	//OutputDebugString(str);
}

void CMatView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//CWnd::OnLButtonUp(nFlags, point);
	m_IsPress = FALSE;
}

Point CMatView::ClientToMat(CPoint point)
{
	return Point(point.x - xOff, point.y - yOff);
}
