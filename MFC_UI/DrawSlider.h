#if !defined(AFX_DRAWSLIDER1_H__B8556A3D_25E7_4A00_898D_50A9D359726A__INCLUDED_)
#define AFX_DRAWSLIDER1_H__B8556A3D_25E7_4A00_898D_50A9D359726A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#endif // _MSC_VER > 1000
#include <atlimage.h>
// DrawSlider1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
class CDrawSlider : public CSliderCtrl
{
// Construction
public:
	CDrawSlider();
	BOOL m_bBtnDown;	//鼠标按钮是否按下
	CRect m_OldRC;
	COLORREF bkColor;
	CFont font;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawSlider();
	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawSlider)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWSLIDER1_H__B8556A3D_25E7_4A00_898D_50A9D359726A__INCLUDED_)
