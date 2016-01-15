#if !defined(AFX_IMAGEBUTTON_H__012D2CB2_147D_466A_BCB7_B19E01CCC69D__INCLUDED_)
#define AFX_IMAGEBUTTON_H__012D2CB2_147D_466A_BCB7_B19E01CCC69D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CPropertyBuilder.h"
// ImageButton.h : header file
//

enum ButtonStyle
{
	BUTTON_PUSHBUTTON,
	BUTTON_COLOR,
	BUTTON_PNG,
	BUTTON_LABEL
};

/////////////////////////////////////////////////////////////////////////////
// ImageButton window
typedef void(*BUTTON_CLICKED_CALLBACK)(void);
class CCommonButton : public CButton
{
private:
// Construction
	int m_Style;
	BOOL m_IsPressed;
	BOOL m_HasLabel;
	CFont* m_Font;
	COLORREF m_BgColor;
	COLORREF m_TextColor;
	COLORREF m_FrameColor;
	COLORREF m_LabelColor;
	CImage* pngNormal;
	CImage* pngDown;
	BUTTON_CLICKED_CALLBACK m_ClickedCallback;
public:
	CCommonButton(COLORREF bgColor = RGB(255, 0, 0), COLORREF textColor = RGB(255, 255, 255), COLORREF frameColor = RGB(0, 0, 0));
	CCommonButton(CString pngPathBtnNormal, CString pngPathBtnDown=NULL);
	CCommonButton(BUTTON_CLICKED_CALLBACK pFunc);

	CCommonButton* SetTextSize(int textSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ImageButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	inline void SetClickedCallBack(BUTTON_CLICKED_CALLBACK pFunc)
	{
		m_ClickedCallback = pFunc;
	};

	afx_msg CCommonButton* SetLabelColor(COLORREF labelColor);

	// Generated message map functions
protected:
	//{{AFX_MSG(ImageButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CCommonButton();
	void TransparentPNG(CImage *png);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBUTTON_H__012D2CB2_147D_466A_BCB7_B19E01CCC69D__INCLUDED_)
