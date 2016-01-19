#pragma once
#include "afxwin.h"
#include "opencv2/core.hpp"
#include "..\CPropertyBuilder.h"
#include "CvvImage.h"
using namespace cv;
class CMatView :
	public CWnd
{
	DECLARE_DYNCREATE(CMatView)
public:
	CMatView();
	~CMatView();

	virtual BOOL Create(CString sCaption, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnPaint();
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

protected:
	BOOL m_IsInit;
	BOOL m_IsPress;
	CvvImage cimg;
	Point ClientToMat(CPoint point);
	int xOff;
	int yOff;

	CPROPERTY_BUILD(Mat,Mat,CMatView*)
	CPROPERTY_BUILD(CString, Caption,CMatView*)
	CPROPERTY_BUILD(CPoint, SelectPoint, CMatView*)
	CPROPERTY_BUILD(COLORREF, BkColor, CMatView*)
};

