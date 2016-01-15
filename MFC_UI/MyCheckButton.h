#pragma once
#include "afxwin.h"
class CMyCheckButton :
	public CButton
{
	DECLARE_DYNAMIC(CMyCheckButton)
public:
	CMyCheckButton();
	~CMyCheckButton();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

};

