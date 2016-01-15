#pragma once
#include "afxwin.h"
#include "CPropertyBuilder.h"
#include <vector>

using namespace std;

typedef vector<CPoint> CPoints;
enum LineType
{
	LINE_DOTBYDOT,
	LINE_SPLINE
};

class CLine{
public:
	CPoints m_Points;
	COLORREF m_Color;
	int m_LineType;
	int m_LineWidth;

	CLine(CPoints points, COLORREF lineColor, int lineType=LINE_DOTBYDOT){
		m_Points = points;
		m_Color = lineColor;
		m_LineType = lineType;
		m_LineWidth = 1;
	};
	CLine(CPoints points, COLORREF lineColor, int lineWidth, int lineType){
		m_Points = points;
		m_Color = lineColor;
		m_LineType = lineType;
		m_LineWidth = lineWidth;
	};
	~CLine(){};

};

typedef vector<CLine> CLines;

class CDrawView :
	public CWnd
{
	DECLARE_DYNCREATE(CDrawView)
public:
	CDrawView();
	~CDrawView();
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnPaint();
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);

	CRect clientRect;
	CRect drawRect;
	int m_LineCount;
	int m_BezierCount;
	BOOL m_IsInit;
	BOOL m_IsPress;
	int m_XMinShow;
	int m_XMaxShow;
	int m_YMinShow;
	int m_YMaxShow;
	double m_XRatio;
	double m_YRatio;
	CLines lines;
	CPoints m_KeyPoints;
	CPoint m_ScaleCenter;
	double m_Scale;
	double m_dScale;

	// 添加一条自定义的曲线
	afx_msg void AddLine(CLine line);
	afx_msg void AddLine(CPoints points, COLORREF lineColor = RGB(0, 0, 0), int lineType = LINE_DOTBYDOT);

	afx_msg CLine GetLine(int index);

	CPoint NormalizePoint(CPoint point);

	CPROPERTY_BUILD(COLORREF,BkColor,CDrawView*)
	CPROPERTY_BUILD(COLORREF, GridColor, CDrawView*)
	CPROPERTY_BUILD(COLORREF, LableColor, CDrawView*)
	CPROPERTY_BUILD(int, XLableCount, CDrawView*)
	CPROPERTY_BUILD(int, YLableCount, CDrawView*)
	CPROPERTY_BUILD(int, XGridCount, CDrawView*)
	CPROPERTY_BUILD(int, YGridCount, CDrawView*)
	CPROPERTY_BUILD(int, XMax, CDrawView*)
	CPROPERTY_BUILD(int, YMax, CDrawView*)
	CPROPERTY_BUILD(int, XMin, CDrawView*)
	CPROPERTY_BUILD(int, YMin, CDrawView*)

	DECLARE_MESSAGE_MAP()
};

