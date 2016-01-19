// ImageButton.cpp : implementation file
//

#include "stdafx.h"
#include "CommonButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ImageButton

CCommonButton::CCommonButton(COLORREF bgColor /*= RGB(255, 0, 0)*/, COLORREF textColor /*= RGB(255, 255, 255)*/, COLORREF frameColor /*= RGB(0, 0, 0)*/)
{
	m_Style = BUTTON_COLOR;
	m_IsPressed = FALSE;
	m_HasLabel = FALSE;
	m_BgColor = bgColor;
	m_TextColor = textColor;
	m_FrameColor = frameColor;
	pngNormal = NULL;
	pngDown = NULL;
	m_ClickedCallback = NULL;
}

CCommonButton::CCommonButton(CString pngFilePathNormal, CString pngPathBtnUp /*= NULL*/)
{
	m_Style = BUTTON_PNG;
	m_IsPressed = FALSE;
	pngNormal = new CImage();
	pngNormal->Load(pngFilePathNormal);
	TransparentPNG(pngNormal);
	if (!pngPathBtnUp.IsEmpty())
	{
		pngDown=new CImage();
		pngDown->Load(pngPathBtnUp);
		TransparentPNG(pngDown);
	}
	m_ClickedCallback = NULL;
}

CCommonButton::CCommonButton(BUTTON_CLICKED_CALLBACK pFunc)
{
	m_Style = BUTTON_PUSHBUTTON;
	m_ClickedCallback = pFunc;
}

CCommonButton::~CCommonButton()
{
}


BEGIN_MESSAGE_MAP(CCommonButton, CButton)
//{{AFX_MSG_MAP(ImageButton)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
//ON_WM_ERASEBKGND()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ImageButton message handlers

void CCommonButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{ 
	if (m_Style==BUTTON_PUSHBUTTON)
	{
		CButton::DrawItem(lpDrawItemStruct);
	} 
	else
	{
		CDC dc ;
		dc.Attach(lpDrawItemStruct ->hDC);							//获得设备上下文
		UINT state = lpDrawItemStruct ->itemState; 					//获取状态
		UINT action = lpDrawItemStruct ->itemAction;	
		CRect clientRect;
		GetClientRect(&clientRect);
		dc.SetBkMode(TRANSPARENT);
		if (m_Style==BUTTON_COLOR)//颜色按钮
		{
			// 按钮被选中或者获得焦点时
			if (m_IsPressed)
			{
				clientRect.DeflateRect(1,1,1,1);
				CBrush brush(m_FrameColor);
				dc.FrameRect(clientRect, &brush);
			}
			else
			{
				//CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
				CBrush brush(m_BgColor);
				dc.SelectObject(&brush);
				dc.Rectangle(&clientRect);
				CBrush brush2(m_FrameColor);
				dc.FrameRect(clientRect, &brush2);
			}
			if (m_HasLabel)
			{
				dc.FillRect(&CRect(5, clientRect.Height() / 2 - 5, 15, clientRect.Height() / 2 + 5), &CBrush(m_LabelColor));
				clientRect.DeflateRect(15, 0, 0, 0);
			}
			CString text;
			GetWindowText(text);
			//clientRect.DeflateRect()
			dc.SetTextColor(m_TextColor);
			dc.DrawText(text, &clientRect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		} 
		else if(m_Style==BUTTON_PNG)// png 按钮
		{
			// 按钮被选中或者获得焦点时
			if (m_IsPressed)
			{
				pngDown->Draw(dc.m_hDC, clientRect);
			}
			else
			{
				pngNormal->Draw(dc.m_hDC, clientRect);
			}
		}
	}
}


void CCommonButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CButton::PreSubclassWindow();
	if (m_Style != BUTTON_PUSHBUTTON)
	{
		ModifyStyle(0, BS_OWNERDRAW);
	}
	
}

void CCommonButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*	CRect rect;
	GetClientRect(rect);
	
	  if (!rect.PtInRect(point)) //判断当前鼠标点是否在按钮区域内
	  {
	  if (isPressed) //如果鼠标不在按钮的区域内,并且按钮处于按下状态,将按钮设置为正常状态
	  isPressed = FALSE;
		}*/
	CButton::OnMouseMove(nFlags, point);
}

void CCommonButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_IsPressed = TRUE; //按钮被按下
	OnEraseBkgnd(GetDC());
	CButton::OnLButtonDown(nFlags, point);
}

void CCommonButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsPressed==TRUE)
	{
		if (m_ClickedCallback!=NULL)
		{
			m_ClickedCallback();
		}
	}
	m_IsPressed = FALSE;	//释放鼠标按钮
	OnEraseBkgnd(GetDC());
	CButton::OnLButtonUp(nFlags, point);
}

void CCommonButton::TransparentPNG(CImage *png)
{
	for (int i = 0; i < png->GetWidth(); i++)  				//遍历像素处理
	{
		for (int j = 0; j < png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(png->GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}

afx_msg CCommonButton* CCommonButton::SetLabelColor(COLORREF labelColor)
{
	m_LabelColor = labelColor;
	m_HasLabel = TRUE;
	return this;
}

CCommonButton* CCommonButton::SetTextSize(int textSize)
{
	m_Font = GetFont();
	CFont font;
	LOGFONT lf;
	m_Font->GetLogFont(&lf);
	lf.lfHeight = textSize/10;
	font.CreateFontIndirect(&lf);
	SetFont(&font, TRUE);
	font.Detach();
	return this;
}
