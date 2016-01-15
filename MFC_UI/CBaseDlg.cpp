//************************************
// Copyright:    XT
// Authors:  Run
// Date:    2016/1/14 
// Descriptions:   创建基础对话框，
//				包括子对话框、弹出对话框
//************************************
#include "stdafx.h"
#include "CBaseDlg.h"
#include "afxdialogex.h"


// CSceneDlg 对话框

IMPLEMENT_DYNAMIC(CBaseDlg, CDialogEx)
CBaseDlg::CBaseDlg(CWnd* pParent /*=NULL*/)
{
	this->pParent = pParent;
	m_bMode = FALSE;
	m_bInit = FALSE;
	m_hIcon = AfxGetApp()->LoadStandardIcon(IDI_APPLICATION);
	//mFont必须是成员变量，不能是局部变量，只能create一次
	mFontSize = 100;
	mFont.CreatePointFont(mFontSize, L"宋体");

	m_bkColor = RGB(240, 240, 240);
}

CBaseDlg::~CBaseDlg()
{
}

void CBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	// 对话框数据更新,非模态对话框的数据必须为全局变量
	for (int i = 0; i < m_vecCtrl.size();i++)
	{
		switch (m_vecCtrl[i].type)
		{
		case BASE_EDIT_CSTRING:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData!=NULL)
			{
				DDX_Text(pDX, m_vecCtrl[i].nID, *(CString*)m_vecCtrl[i].pInOutData);
				DDV_MaxChars(pDX, *(CString*)m_vecCtrl[i].pInOutData, m_vecCtrl[i].nMaxChars);
			}
			break;
		}
		case BASE_EDIT_DOUBLE:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData != NULL)
			{
				DDX_Text(pDX, m_vecCtrl[i].nID, *(double*)m_vecCtrl[i].pInOutData);
				DDV_MinMaxDouble(pDX, *(double*)m_vecCtrl[i].pInOutData, m_vecCtrl[i].dMinVal, m_vecCtrl[i].dMaxVal);
			}
			break;
		}
		case BASE_CHECK_BUTTON:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData != NULL)
			{
				DDX_Check(pDX, m_vecCtrl[i].nID, *(BOOL*)m_vecCtrl[i].pInOutData);
			}
			break;
		}
		case BASE_COMBOBOX:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData != NULL)
			{
				DDX_CBString(pDX, m_vecCtrl[i].nID, *(CString*)m_vecCtrl[i].pInOutData);
				DDV_MaxChars(pDX, *(CString*)m_vecCtrl[i].pInOutData, m_vecCtrl[i].nMaxChars);
			}
			break;
		}
		case BASE_PROGRESS:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData != NULL)
			{
				DDX_Slider(pDX, m_vecCtrl[i].nID, *(int*)m_vecCtrl[i].pInOutData);
				DDV_MinMaxInt(pDX, *(int*)m_vecCtrl[i].pInOutData, m_vecCtrl[i].dMinVal, m_vecCtrl[i].dMaxVal);
			}
			break;
		}
		case BASE_SLIDER:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData != NULL)
			{
				DDX_Slider(pDX, m_vecCtrl[i].nID, *(int*)m_vecCtrl[i].pInOutData);
				DDV_MinMaxInt(pDX, *(int*)m_vecCtrl[i].pInOutData, m_vecCtrl[i].dMinVal, m_vecCtrl[i].dMaxVal);
			}
			break;
		}
		case BASE_SLIDER_GROUP:
		{
			if (m_vecCtrl[i].nID != 65535U && m_vecCtrl[i].pInOutData != NULL)
			{
				DDX_SliderGroup(pDX, m_vecCtrl[i].nID, *(int*)m_vecCtrl[i].pInOutData);
				DDV_MinMaxInt(pDX, *(int*)m_vecCtrl[i].pInOutData, m_vecCtrl[i].dMinVal, m_vecCtrl[i].dMaxVal);
			}
			break;
		}
		default:
			break;
		}
	}
}

BEGIN_MESSAGE_MAP(CBaseDlg, CDialogEx)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//************************************
// Method:    CreateEx
// FullName:  CBaseDlg::CreateEx
// Access:    virtual public 
// Returns:   BOOL
// Qualifier:
// Parameter: LPCTSTR lpszWindowName
// Parameter: CRect rect
// Parameter: CWnd * pParentWnd
// Parameter: DWORD style
// Parameter: UINT nID
//************************************
BOOL CBaseDlg::CreateEx(LPCTSTR lpszWindowName, CRect rect, CWnd* pParentWnd, DWORD style /*= WS_CHILD | WS_VISIBLE*/, UINT nID)
{
	return CDialogEx::CreateEx(0, AfxRegisterWndClass(0), lpszWindowName, style, rect, pParentWnd, nID, NULL);
}

BOOL CBaseDlg::CreateModeDlg(CString strCaption, CRect rect, BOOL bMode /*= TRUE*/, CWnd* pParent /*= NULL*/)
{
	m_bMode = bMode;
	BOOL bResult = FALSE;
	DLGTEMPLATE* pTemp = NULL;

	// 先获得dpi
	HDC	hdc = ::GetDC(0);
	int		nDpiX = GetDeviceCaps(hdc, LOGPIXELSX);
	int		nDpiY = GetDeviceCaps(hdc, LOGPIXELSY);
	::ReleaseDC(0, hdc);
	ASSERT(nDpiX = nDpiY);
	double fScaleData = 64.0 / nDpiX;
#ifdef		WINCE
	fScaleData = fScaleData * 0.859;
#endif
	rect.left = (int)(rect.left*fScaleData);
	rect.top = (int)(rect.top*fScaleData);
	rect.right = (int)(rect.right*fScaleData);
	rect.bottom = (int)(rect.bottom*fScaleData);

	pTemp = m_dlgTemp.CreateTemplate(WS_POPUPWINDOW | DS_MODALFRAME | WS_CAPTION, rect, strCaption);
	if (bMode)
	{
		bResult = InitModalIndirect(pTemp, pParent);
	}
	else
	{
		bResult = CreateIndirect(pTemp, pParent);
	}
	return bResult;
}

BOOL CBaseDlg::ShowWindow(int nCmdShow)
{
	if (!m_bMode&&!m_bInit)
	{
		OnInitDialog();
	}
	return CWnd::ShowWindow(nCmdShow);
}

BOOL CBaseDlg::OnInitDialog()
{
	//CDialog::OnInitDialog();
	if (m_hIcon)
	{
		SetIcon(m_hIcon, TRUE);   // 设置大图标
		SetIcon(m_hIcon, FALSE);  // 设置小图标
	}

	m_bInit = TRUE;

	for (int i = 0; i < m_vecCtrl.size(); i++)
	{
		switch (m_vecCtrl[i].type)
		{
		case BASE_BUTTON:
		case BASE_CHECK_BUTTON:
		{
			CButton* pCtrl = (CButton*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_COMMOM_BUTTON:
		{
			CCommonButton* pCtrl = (CCommonButton*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_STATIC:
		{
			CStatic* pCtrl = (CStatic*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_MY_CHECK_BUTTON:
		{
			CMyCheckButton* pCtrl = (CMyCheckButton*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_INDICATOR:
		{
			CIndicator* pCtrl = (CIndicator*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_GROUPBOX:
		{
			CGroupBox* pCtrl = (CGroupBox*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_EDIT_CSTRING:
		case BASE_EDIT_DOUBLE:
		{
			CEdit* pCtrl = (CEdit*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			break;
		}
		case BASE_COLOR_TEXT:
		{
			CColorText* pCtrl = (CColorText*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle,
				m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			break;
		}
		case BASE_DRAWVIEW:
		{
			CDrawView* pCtrl = (CDrawView*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			break;
		}
		case BASE_LIST:
		{
			CListCtrl* pCtrl = (CListCtrl*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			break;
		}
		case BASE_TABVIEW:
		{
			CTabViewCtrl* pCtrl = (CTabViewCtrl*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			break;
		}
		case BASE_GRADIENT_BACKGROUND:
		{
			CGradientBackground* pCtrl = (CGradientBackground*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			break;
		}
		case BASE_COMBOBOX:
		{
			CComboBox* pCtrl = (CComboBox*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			pCtrl->SetFont(&mFont);
			CString caption = m_vecCtrl[i].sCaption;
			for (int j = 0; j < m_vecCtrl[i].nDataCount; j++)
			{
				int endpos = caption.Find(L"\n");
				CString item = caption.Mid(0, endpos);
				pCtrl->AddString(item);
				caption = caption.Right(caption.GetLength()-endpos-1);
			}
			pCtrl->SetCurSel(0);
			break;
		}
		case BASE_PROGRESS:
		{
			CProgressCtrl* pCtrl = (CProgressCtrl*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			if (m_vecCtrl[i].pInOutData != NULL)
			{
				pCtrl->SetRange32((int)m_vecCtrl[i].dMinVal,(int)m_vecCtrl[i].dMaxVal);
			}
			break;
		}
		case BASE_SLIDER:
		{
			CSliderCtrl* pCtrl = (CSliderCtrl*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			if (m_vecCtrl[i].pInOutData != NULL)
			{
				pCtrl->SetRangeMax((int)m_vecCtrl[i].dMaxVal);
				pCtrl->SetRangeMin((int)m_vecCtrl[i].dMinVal);
			}
			break;
		}
		case BASE_SLIDER_GROUP:
		{
			CSliderGroup* pCtrl = (CSliderGroup*)m_vecCtrl[i].pCtrl;
			pCtrl->Create(m_vecCtrl[i].sCaption, m_vecCtrl[i].dwStyle, m_vecCtrl[i].rect, m_vecCtrl[i].pParent, m_vecCtrl[i].nID);
			if (m_vecCtrl[i].pInOutData!=NULL)
			{
				pCtrl->GetSlider()->SetRangeMax((int)m_vecCtrl[i].dMaxVal);
				pCtrl->GetSlider()->SetRangeMin((int)m_vecCtrl[i].dMinVal);
			}
			break;
		}
		default:
			break;
		}
	}
	UpdateData(FALSE);
	return TRUE;
}

void CBaseDlg::OnOK()
{
	CDialog::OnOK();
}

BOOL CBaseDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect clientRect;
	GetClientRect(&clientRect);

	pDC->FillRect(&clientRect, &CBrush(m_bkColor));
	return FALSE;
}

CButton* CBaseDlg::AddButton(CString sCaption, CRect rect, UINT nID)
{
	CButton *pCtrl = new CButton();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_BUTTON, sCaption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, this, nID, pCtrl };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CCommonButton* CBaseDlg::AddCommonButton(CString sCaption, CRect rect, UINT nID, BUTTON_CLICKED_CALLBACK pFunc)
{
	CCommonButton *pCtrl = new CCommonButton(pFunc);
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_COMMOM_BUTTON, sCaption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, this, nID, pCtrl };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CCommonButton* CBaseDlg::AddCommonButton(CString sCaption, CRect rect, UINT nID, COLORREF bgColor /*= RGB(255, 0, 0)*/, COLORREF textColor /*= RGB(255, 255, 255)*/, COLORREF frameColor /*= RGB(0, 0, 0)*/)
{
	CCommonButton *pCtrl = new CCommonButton(bgColor, textColor, frameColor);
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_COMMOM_BUTTON, sCaption, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect, this, nID, pCtrl };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CStatic* CBaseDlg::AddStatic(CString sCaption, CRect rect, UINT nID /*= 65535U*/)
{
	CStatic *pCtrl = new CStatic();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_STATIC, sCaption, WS_CHILD | WS_VISIBLE | SS_REALSIZECONTROL | SS_CENTERIMAGE | SS_CENTER, rect, this, nID, pCtrl };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CGradientBackground* CBaseDlg::AddBackground(CRect rect, UINT nID /*= 65535U*/)
{
	CGradientBackground* pCtrl = new CGradientBackground();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_GRADIENT_BACKGROUND, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CListCtrl* CBaseDlg::AddListCtrl(CRect rect, UINT nID, int bColHeader/*=0*/)
{
	CListCtrl *pCtrl = new CListCtrl();
	ASSERT_VALID(pCtrl);
	DWORD style = WS_CHILD | WS_BORDER | WS_VISIBLE | LVS_REPORT;
	if (0==bColHeader)
	{
		style |= LVS_NOCOLUMNHEADER;
	}
	if (!m_bMode)
	{
		pCtrl->Create(style, rect, this, nID);
		pCtrl->SetFont(&mFont);
	}
	else
	{
		BaseDlgCtrlStruct structCtrl = { BASE_LIST, L"", style, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	}
	return pCtrl;
}

CGroupBox* CBaseDlg::AddGroupBox(CString sCaption, CRect rect, UINT nID /*= 65535U*/)
{
	CButton *pCtrl = new CButton();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_GROUPBOX, sCaption, WS_CHILD | WS_VISIBLE | BS_GROUPBOX, rect, this, nID, pCtrl };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CEdit* CBaseDlg::AddEdit(CRect rect, UINT nID /*= 65535U*/)
{
	CEdit *pCtrl = new CEdit();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_EDIT_CSTRING, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rect, this, nID, pCtrl,NULL };
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CEdit* CBaseDlg::AddEdit(CRect rect, UINT nID, CString& string, int maxChars)
{
	CEdit *pCtrl = new CEdit();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_EDIT_CSTRING, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rect, this, nID, pCtrl, &string };
	structCtrl.nMaxChars = maxChars;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CEdit* CBaseDlg::AddEdit(CRect rect, UINT nID, double& dData, double minVal, double maxVal)
{
	CEdit *pCtrl = new CEdit();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_EDIT_DOUBLE, L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rect, this, nID, pCtrl, &dData };
	structCtrl.dMaxVal = maxVal;
	structCtrl.dMinVal = minVal;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CTabViewCtrl* CBaseDlg::AddTabViewCtrl(CRect rect, UINT nID)
{
	CTabViewCtrl *pCtrl = new CTabViewCtrl();
	if (!m_bMode)
	{
		pCtrl->Create(WS_CHILD | WS_VISIBLE, rect, this, nID); //创建控件
		pCtrl->SetFont(&mFont);
	}
	else
	{
		BaseDlgCtrlStruct structCtrl = { BASE_TABVIEW, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	}
	return pCtrl;
}

CEdit* CBaseDlg::AddEditParam(CString sCaption, CRect rect, UINT nID /*= 65535U*/)
{

	if (rect.Height()>=40)
	{
		AddGroupBox(sCaption, rect);
		rect.DeflateRect(10, 20, 10, 5);
	}
	CEdit *pCtrl = AddEdit(rect, nID);
	return pCtrl;
}

CEdit* CBaseDlg::AddEditParam(CString sCaption, CRect rect, UINT nID, CString& strData, int maxChars /*= INT_MAX*/)
{

	if (rect.Height() >= 40)
	{
		AddGroupBox(sCaption, rect);
		rect.DeflateRect(10, 20, 10, 5);
	}
	CEdit *pCtrl = AddEdit(rect, nID,strData, maxChars);
	return pCtrl;
}

CEdit* CBaseDlg::AddEditParam(CString sCaption, CRect rect, UINT nID, double& dData, double minVal /*= DBL_MIN*/, double maxVal /*= DBL_MAX*/)
{
	
	if (rect.Height() >= 40)
	{
		AddGroupBox(sCaption, rect);
		rect.DeflateRect(10, 20, 10, 5);
	}
	CEdit *pCtrl = AddEdit(rect, nID, dData,minVal,maxVal);
	return pCtrl;
}

CButton* CBaseDlg::AddCheckParam(CString sCaption, CRect rect, UINT nID)
{
	
	if (rect.Height() >= 40)
	{
		AddGroupBox(L"", rect);
		rect.DeflateRect(10, 15, 10, 10);
	}
	CButton *pCtrl = AddCheckButton(sCaption, rect, nID);
	return pCtrl;
}

CButton* CBaseDlg::AddCheckParam(CString sCaption, CRect rect, UINT nID, BOOL& bCheck)
{
	
	if (rect.Height() >= 40)
	{
		AddGroupBox(L"", rect);
		rect.DeflateRect(10, 15, 10, 10);
	}
	CButton *pCtrl = AddCheckButton(sCaption, rect, nID, bCheck);
	return pCtrl;
}

CButton* CBaseDlg::AddCheckButton(CString sCaption, CRect rect, UINT nID)
{
	CButton *pCtrl = new CButton();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_CHECK_BUTTON, sCaption, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, rect, this, nID, pCtrl, NULL};
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CButton* CBaseDlg::AddCheckButton(CString sCaption, CRect rect, UINT nID, BOOL& bCheck)
{
	CButton *pCtrl = new CButton();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_CHECK_BUTTON, sCaption, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, rect, this, nID, pCtrl, &bCheck};
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CComboBox* CBaseDlg::AddComboBox(CString sItem[], int nCount, CRect rect, UINT nID)
{
	CString caption;
	for (int i = 0; i < nCount;i++)
	{
		caption += sItem[i] + L"\n";
	}
	CComboBox *pCtrl = new CComboBox();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_COMBOBOX, caption, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, rect, this, nID, pCtrl, NULL };
	structCtrl.nDataCount = nCount;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CComboBox* CBaseDlg::AddComboBox(CString sItem[], int nCount, CRect rect, UINT nID, CString& strCaption, int maxChars)
{
	CString caption;
	for (int i = 0; i < nCount; i++)
	{
		caption += sItem[i] + L"\n";
	}
	CComboBox *pCtrl = new CComboBox();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_COMBOBOX, caption, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, rect, this, nID, pCtrl, &strCaption };
	structCtrl.nMaxChars = maxChars;
	structCtrl.nDataCount = nCount;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CComboBox* CBaseDlg::AddComboParam(CString sCaption,CString sItem[], int nCount, CRect rect, UINT nID)
{
	
	if (rect.Height() > 40)
	{
		AddGroupBox(sCaption, rect);
		rect.DeflateRect(10, 20, 10, 10);
	}
	CComboBox *pCtrl = AddComboBox(sItem, nCount, rect, nID);
	return pCtrl;
}

CComboBox* CBaseDlg::AddComboParam(CString sCaption, CString sItem[], int nCount, CRect rect, UINT nID, CString& strCaption, int maxChars /*= INT_MAX*/)
{
	if (rect.Height() > 40)
	{
		AddGroupBox(sCaption, rect);
		rect.DeflateRect(10, 20, 10, 10);
	}
	CComboBox *pCtrl = AddComboBox(sItem, nCount, rect, nID, strCaption, maxChars);
	return pCtrl;
}

CProgressCtrl* CBaseDlg::AddProgressBar(CRect rect, UINT nID /*= 65535U*/)
{
	CProgressCtrl *pCtrl = new CProgressCtrl();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_PROGRESS, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl, NULL };
	structCtrl.dMaxVal = 100;
	structCtrl.dMinVal = 0;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CProgressCtrl* CBaseDlg::AddProgressBar(CRect rect, UINT nID, int& nPos, int minVal /*= 0*/, int maxVal /*= 100*/)
{
	CProgressCtrl *pCtrl = new CProgressCtrl();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_PROGRESS, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl, &nPos };
	structCtrl.dMaxVal = maxVal;
	structCtrl.dMinVal = minVal;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CSliderCtrl* CBaseDlg::AddSliderBar(CRect rect, UINT nID)
{
	CSliderCtrl *pCtrl = new CSliderCtrl();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_SLIDER, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl, NULL };
	structCtrl.dMaxVal = 100;
	structCtrl.dMinVal = 0;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CSliderCtrl* CBaseDlg::AddSliderBar(CRect rect, UINT nID, int& nPos, int minVal /*= INT_MIN*/, int maxVal /*= INT_MAX*/)
{
	CSliderCtrl *pCtrl = new CSliderCtrl();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_SLIDER, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl, &nPos};
	structCtrl.dMaxVal = maxVal;
	structCtrl.dMinVal = minVal;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CSliderGroup* CBaseDlg::AddSliderGroup(CRect rect, UINT nID)
{
	CSliderGroup *pCtrl = new CSliderGroup();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_SLIDER_GROUP, L"", WS_CHILD | WS_VISIBLE , rect, this, nID, pCtrl };
	structCtrl.dMaxVal = 100;
	structCtrl.dMinVal = 0;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CSliderGroup* CBaseDlg::AddSliderGroup(CRect rect, UINT nID, int& nPos, int minVal /*0*/, int maxVal /*= 100*/)
{
	CSliderGroup *pCtrl = new CSliderGroup();
	ASSERT_VALID(pCtrl);
	BaseDlgCtrlStruct structCtrl = { BASE_SLIDER_GROUP, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl, &nPos};
	structCtrl.dMaxVal = maxVal;
	structCtrl.dMinVal = minVal;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CStatic* CBaseDlg::AddTextParam(CString sCaption, CString sParam, CRect rect, UINT nID /*= 65535U*/)
{
	CStatic *pCtrl = new CStatic();
	ASSERT_VALID(pCtrl);
	if (rect.Height() >= 25)
	{
		AddGroupBox(sCaption, rect);
		if (sCaption==L""&&rect.Height()<30)
		{
			rect.DeflateRect(10, 10, 10, 5);
		}
		else
		{
			rect.DeflateRect(10, 15, 10, 10);
		}
	}
		BaseDlgCtrlStruct structCtrl = { BASE_STATIC, sParam, WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CEdit* CBaseDlg::AddCheckEditParam(CString sCaption, CRect rect, UINT nID /*= 65535U*/)
{
	CEdit *pCtrl = new CEdit();
	ASSERT_VALID(pCtrl);
	if (rect.Height() >= 40)
	{
		AddGroupBox(L"", rect);
		AddCheckButton(sCaption, CRect(rect.left + 10, rect.top, rect.right - 10, rect.top + 20),nID+1);
		rect.DeflateRect(10, 20, 10, 5);
	}
		BaseDlgCtrlStruct structCtrl = { BASE_EDIT_CSTRING, sCaption, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rect, this, nID, pCtrl, NULL};
		m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CEdit* CBaseDlg::AddCheckEditParam(CString sCaption, CRect rect, UINT nID, BOOL& bCheck, CString& sData, int maxChars /*= INT_MAX*/)
{
	CEdit *pCtrl = new CEdit();
	ASSERT_VALID(pCtrl);
	if (rect.Height() >= 40)
	{
		AddGroupBox(L"", rect);
		AddCheckButton(sCaption, CRect(rect.left + 10, rect.top, rect.right - 10, rect.top + 20), nID + 1, bCheck);
		rect.DeflateRect(10, 20, 10, 5);
	}
	BaseDlgCtrlStruct structCtrl = { BASE_EDIT_CSTRING, sCaption, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rect, this, nID, pCtrl, &sData};
	structCtrl.nMaxChars = maxChars;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CEdit* CBaseDlg::AddCheckEditParam(CString sCaption, CRect rect, UINT nID, BOOL& bCheck, double& dData, double minVal /*= DBL_MIN*/, double maxVal /*= DBL_MAX*/)
{
	CEdit *pCtrl = new CEdit();
	ASSERT_VALID(pCtrl);
	if (rect.Height() >= 40)
	{
		AddGroupBox(L"", rect);
		AddCheckButton(sCaption, CRect(rect.left + 10, rect.top, rect.right - 10, rect.top + 20), nID + 1, bCheck);
		rect.DeflateRect(10, 20, 10, 5);
	}
	BaseDlgCtrlStruct structCtrl = { BASE_EDIT_CSTRING, sCaption, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, rect, this, nID, pCtrl, &dData };
	structCtrl.dMaxVal = maxVal;
	structCtrl.dMinVal = minVal;
	m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CIndicator* CBaseDlg::AddIndicator(CRect rect, UINT nID, COLORREF highlightColor /*=RGB(255,0,0)*/, COLORREF normalColor/*=RGB(255,255,255)*/)
{
	CIndicator *pCtrl = new CIndicator(highlightColor, normalColor);
	ASSERT_VALID(pCtrl);
		BaseDlgCtrlStruct structCtrl = { BASE_INDICATOR, L"", WS_CHILD | WS_VISIBLE, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CMyCheckButton* CBaseDlg::AddMyCheckButton(CString sCaption, CRect rect, UINT nID)
{
	CMyCheckButton *pCtrl = new CMyCheckButton();
	ASSERT_VALID(pCtrl);
		BaseDlgCtrlStruct structCtrl = { BASE_MY_CHECK_BUTTON, sCaption, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

CColorText* CBaseDlg::AddColorText(CString sCaption, CRect rect, UINT nID /*= 65535U*/)
{
	CColorText *pCtrl = new CColorText();
	ASSERT_VALID(pCtrl);
		BaseDlgCtrlStruct structCtrl = { BASE_COLOR_TEXT, sCaption, WS_CHILD | WS_VISIBLE | SS_REALSIZECONTROL | SS_CENTERIMAGE | SS_CENTER, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	//pCtrl->SetFont(&mFont);
	return pCtrl;
}

CDrawView* CBaseDlg::AddDrawView(CRect rect, UINT nID /*= 0*/)
{
	CDrawView *pCtrl = new CDrawView();
	ASSERT_VALID(pCtrl);
		BaseDlgCtrlStruct structCtrl = { BASE_DRAWVIEW, L"", 0, rect, this, nID, pCtrl };
		m_vecCtrl.push_back(structCtrl);
	return pCtrl;
}

void AFXAPI CBaseDlg::DDX_SliderGroup(CDataExchange* pDX, int nIDC, int& value)
{
	CSliderGroup* ctl = (CSliderGroup*)pDX->m_pDlgWnd->GetDlgItem(nIDC);
	if (pDX->m_bSaveAndValidate)
		value = ctl->GetPos();
	else
		ctl->SetPos(value);
}

void AFXAPI CBaseDlg::DDX_Progress(CDataExchange* pDX, int nIDC, int& value)
{
	CProgressCtrl* ctl = (CProgressCtrl*)pDX->m_pDlgWnd->GetDlgItem(nIDC);
	if (pDX->m_bSaveAndValidate)
		value = ctl->GetPos();
	else
		ctl->SetPos(value);
}
