#include "stdafx.h"
#include "MyCheckButton.h"

IMPLEMENT_DYNAMIC(CMyCheckButton, CButton)
CMyCheckButton::CMyCheckButton()
{
}


CMyCheckButton::~CMyCheckButton()
{
}
BEGIN_MESSAGE_MAP(CMyCheckButton, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CMyCheckButton::OnPaint()
{
	SetCheck(TRUE);
	CButton::OnPaint();
}
