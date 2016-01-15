#include "stdafx.h"
#include "DrawView.h"

IMPLEMENT_DYNCREATE(CDrawView,CWnd)
CDrawView::CDrawView()
{
	m_BkColor = RGB(0,0,0);
	m_GridColor = RGB(153, 153, 153);
	m_LableColor = RGB(255, 255, 255);
	m_XLableCount = 0;
	m_YLableCount = 0;
	m_XGridCount = 0;
	m_YGridCount = 0;
	m_IsInit = TRUE;
	m_IsPress = FALSE;
	m_XMax = 100;
	m_YMax = 100;
	m_XMin = 0;
	m_YMin =  0;
	m_LineCount = 0;
	m_BezierCount = 0;
	m_Scale = 1;
	m_dScale = 0;
	m_XMinShow=0;
	m_XMaxShow=100;
	m_YMinShow=100;
	m_YMaxShow=0;
}


CDrawView::~CDrawView()
{
}

BEGIN_MESSAGE_MAP(CDrawView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CDrawView::OnPaint()
{
	GetClientRect(&clientRect);
	drawRect.CopyRect(&clientRect);
	drawRect.DeflateRect(10, 10, 10, 10);

	if (m_IsInit)
	{
		m_XRatio = (double)drawRect.Width() / (m_XMax - m_XMin);
		m_YRatio = (double)drawRect.Height() / (m_YMax - m_YMin);
		m_XMinShow = drawRect.left;
		m_YMinShow = drawRect.bottom;
		m_IsInit = FALSE;
	}

	CPaintDC dc(this);
	CDC* pDC = &dc;
	pDC->SetBkMode(TRANSPARENT);
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, m_GridColor);
	pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(m_BkColor);
	pDC->SelectObject(&brush);

	// Draw Background
	pDC->FillRect(&clientRect, &brush);

	// Draw xAxis and yAxis
	pDC->Rectangle(&drawRect);
	pen.DeleteObject();
	
	// Draw Grid
	pen.CreatePen(PS_DOT, 1, m_GridColor);
	pDC->SelectObject(&pen); 
	pDC->SelectObject(&brush);
	// Draw xGrid
	int xGridWidth = drawRect.Width() / (m_XGridCount + 1);
	for (int i = 1; i < m_XGridCount+1;i++)
	{
		pDC->MoveTo(drawRect.left, drawRect.top + xGridWidth*i);
		pDC->LineTo(drawRect.right, drawRect.top + xGridWidth*i);
	}
	// Draw yGrid
	int yGridWidth = drawRect.Height() / (m_YGridCount + 1);
	for (int i = 1; i < m_YGridCount + 1; i++)
	{
		pDC->MoveTo(drawRect.left + yGridWidth * i, drawRect.top);
		pDC->LineTo(drawRect.left + yGridWidth * i, drawRect.bottom);
	}
	pen.DeleteObject();

	// Draw Lines
	for (int i = 0; i < lines.size(); i++)
	{
		CLine line = lines.at(i);
		m_KeyPoints = line.m_Points;
		pen.CreatePen(PS_SOLID, 1, line.m_Color);
		pDC->SelectObject(&pen);
		CPoint* points = new CPoint[line.m_Points.size()];
		for (int j = 0; j < line.m_Points.size(); j++)
		{
			points[j] = NormalizePoint(line.m_Points[j]);
			pDC->Ellipse(points[j].x - 5, points[j].y - 5, points[j].x + 5, points[j].y + 5);
		}
		if (line.m_LineType == LINE_DOTBYDOT)
		{
			pDC->Polyline(points, line.m_Points.size());
		}
		else if (line.m_LineType == LINE_SPLINE)
		{
			pDC->PolyBezier(points, line.m_Points.size());
		}
		delete[] points;
		pen.DeleteObject();
	}

	brush.DeleteObject();
}

BOOL CDrawView::Create(const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(AfxRegisterWndClass(0), L"", WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID);
}

CPoint CDrawView::NormalizePoint(CPoint point)
{
	CPoint resPoint;
	resPoint.x = m_XMinShow + point.x * m_XRatio;
	resPoint.y = m_YMinShow - point.y * m_YRatio;
	return resPoint;
}

void CDrawView::AddLine(CLine line)
{
	m_LineCount++;
	lines.push_back(line);
}

void CDrawView::AddLine(CPoints points, COLORREF lineColor /*= RGB(0, 0, 0)*/, int lineType /*= LINE_DOTBYDOT*/)
{
	m_LineCount++;
	lines.push_back(CLine(points, lineColor, lineType));
}

CLine CDrawView::GetLine(int index)
{
	return lines.at(index);
}

BOOL CDrawView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//CString str;
	//str.Format(L"%d ", zDelta);
	//OutputDebugString(str);

	m_dScale = zDelta / 120 * 0.1;
	m_ScaleCenter = pt;

	//m_XMinShow = m_XMinShow - m_XRatio * m_dScale;
	//m_YMinShow = m_YMinShow - m_YRatio * m_dScale;
	m_XRatio = m_XRatio * (1 + m_dScale);
	m_YRatio = m_YRatio * (1 + m_dScale);
	//m_XMinShow = 0;
	//m_YMinShow = 500;

	Invalidate();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CWnd::OnLButtonDown(nFlags, point);
	CString str;
	str.Format(L"%d,%d ", point.x,point.y);
	OutputDebugString(str);
	SetFocus();
	m_IsPress = TRUE;
}

void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_IsPress)
	{
		OutputDebugString(L"m");
	}
}

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_IsPress = FALSE;
}
