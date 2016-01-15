//************************************
// Copyright:    XT
// Authors:  Run
// Date:    2016/1/14 
// Descriptions:   创建基础对话框，
//			包括子对话框、弹出对话框
//************************************
#pragma once
#include "TabViewCtrl.h"
#include "GradientBackground.h"
#include "SliderGroup.h"
#include "Indicator.h"
#include "MyCheckButton.h"
#include "ImageButton.h"
#include "ColorText.h"
#include "DrawView.h"
#include "MyDlgTemplate.h"
#define CGroupBox CButton

enum BASE_CTRL_STYLE
{
	BASE_BUTTON,// 基本按钮
	BASE_COMMOM_BUTTON,// 通用按钮
	BASE_CHECK_BUTTON,// 状态按钮
	BASE_STATIC,// 静态文本控件
	BASE_COLOR_TEXT,// 颜色文本控件
	BASE_EDIT_CSTRING,// 文本编辑框
	BASE_EDIT_DOUBLE,// 数字编辑框态按钮
	BASE_SLIDER,// 滑动条
	BASE_PROGRESS,// 进度条
	BASE_GROUPBOX,// 群组控件
	BASE_COMBOBOX,// 组合框
	BASE_LIST,// 列表框
	BASE_EDIT_PARAM,// 参数输入组合
	BASE_CHECK_PARAM,// 参数状态组合
	BASE_COMBO_PARAM,// 参数组合框组合
	BASE_TEXT_PARAM,// 参数文字组合
	BASE_CHECK_EDIT_PARAM,// 参数状态输入组合
	BASE_TABVIEW,// 标签视图控件
	BASE_SLIDER_GROUP,// 滑动条组合框
	BASE_INDICATOR,// 指示器
	BASE_MY_CHECK_BUTTON,// 用于指示的状态
	BASE_GRADIENT_BACKGROUND,// 渐变背景
	BASE_DRAWVIEW// 画图控件，还没完成
};

typedef struct
{
	// 控件类型
	int type;
	CString sCaption;
	DWORD dwStyle;
	CRect rect;
	CWnd* pParent;// 父控件
	UINT nID;// 本控件id
	CWnd* pCtrl;// 本控件
	LPVOID pInOutData;// 输入输出数据
	int nMaxChars;// 输入最大长度，BASE_EDIT_CSTRING有效
	double dMaxVal;// 输入最大值
	double dMinVal;// 输入最小值
	int nDataCount;// 输入数据数量
} BaseDlgCtrlStruct;

class CTabViewCtrl;
class CBaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseDlg();

// Attributes
private:
	CWnd* pParent;// 父控件指针
	COLORREF m_bkColor;// 背景颜色
	vector<BaseDlgCtrlStruct> m_vecCtrl;// 内部控件容器
	BOOL m_bMode;// 是否为模态对话框
	BOOL m_bInit;// 是否初始化了
	CFont mFont;// 字体
	int mFontSize;// 字体大小
	CMyDlgTemplate m_dlgTemp;//窗体模板
	HICON  m_hIcon;// 图标
	enum { IDICON = 1 };// 图标ID

protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

// Overridables
public:
	virtual BOOL CreateEx(LPCTSTR lpszWindowName, CRect rect, CWnd* pParentWnd, DWORD style = WS_CHILD | WS_VISIBLE, UINT nID = 0);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	BOOL ShowWindow(int nCmdShow);

// Operations
public:
	//************************************
	// Method:    CreateModeDlg
	// FullName:  CBaseDlg::CreateModeDlg
	// Access:    public 
	// Returns:   BOOL
	// Qualifier:
	// Description: create modal or modeless popup window
	// Parameter: CString strCaption
	// Parameter: CRect rect
	// Parameter: BOOL bMode
	// Parameter: CWnd * pParent
	//************************************
	BOOL CreateModeDlg(CString strCaption, CRect rect, BOOL bMode = TRUE, CWnd* pParent = NULL);

	//************************************
	// Method:    AddButton
	// FullName:  CBaseDlg::AddButton
	// Access:    public 
	// Returns:   CButton*
	// Qualifier:
	// Description: add base buttons
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CButton* AddButton(CString sCaption, CRect rect, UINT nID);

	//************************************
	// Method:    AddCommonButton
	// FullName:  CBaseDlg::AddCommonButton
	// Access:    public 
	// Returns:   CImageButton*
	// Qualifier:
	// Description: add common pushbuttons
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	// Parameter: BUTTON_CLICKED_CALLBACK pFunc
	//************************************
	CCommonButton* AddCommonButton(CString sCaption, CRect rect, UINT nID, BUTTON_CLICKED_CALLBACK pFunc);

	//************************************
	// Method:    AddCommonButton
	// FullName:  CBaseDlg::AddCommonButton
	// Access:    public 
	// Returns:   CImageButton*
	// Qualifier:
	// Description: add common color buttons
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	// Parameter: COLORREF bgColor
	// Parameter: COLORREF textColor
	// Parameter: COLORREF frameColor
	//************************************
	CCommonButton* AddCommonButton(CString sCaption, CRect rect, UINT nID, COLORREF bgColor = RGB(255, 0, 0), COLORREF textColor = RGB(255, 255, 255), COLORREF frameColor = RGB(0, 0, 0));

	//************************************
	// Method:    AddCheckButton
	// FullName:  CBaseDlg::AddCheckButton
	// Access:    public 
	// Returns:   CButton*
	// Qualifier:
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	// Parameter: BOOL & bCheck
	//************************************
	CButton* AddCheckButton(CString sCaption, CRect rect, UINT nID);
	CButton* AddCheckButton(CString sCaption, CRect rect, UINT nID, BOOL& bCheck);

	//************************************
	// Method:    AddStatic
	// FullName:  CBaseDlg::AddStatic
	// Access:    public 
	// Returns:   CStatic*
	// Qualifier:
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CStatic* AddStatic(CString sCaption, CRect rect, UINT nID = 65535U);


	//************************************
	// Method:    AddColorText
	// FullName:  CBaseDlg::AddColorText
	// Access:    public 
	// Returns:   CColorText*
	// Qualifier:
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CColorText* AddColorText(CString sCaption, CRect rect, UINT nID = 65535U);

	//************************************
	// Method:    AddGroupBox
	// FullName:  CBaseDlg::AddGroupBox
	// Access:    public 
	// Returns:   CGroupBox*
	// Qualifier:
	// Description: create GroupBox
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CGroupBox* AddGroupBox(CString sCaption, CRect rect, UINT nID = 65535U);

	//************************************
	// Method:    AddComboBox
	// FullName:  CBaseDlg::AddComboBox
	// Access:    public 
	// Returns:   CComboBox*
	// Qualifier:
	// Parameter: CString sItem[]
	// Parameter: int nCount
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CComboBox* AddComboBox(CString sItem[], int nCount, CRect rect, UINT nID=65535U);
	CComboBox* AddComboBox(CString sItem[], int nCount, CRect rect, UINT nID, CString& sCaption, int maxChars = INT_MAX);

	//************************************
	// Method:    AddListCtrl
	// FullName:  CBaseDlg::AddListCtrl
	// Access:    public 
	// Returns:   CListCtrl*
	// Qualifier:
	// Parameter: CRect rect
	// Parameter: UINT nID
	// Parameter: int bColHeader
	//            0 -- no colHeader
	//            1 -- has colHeader
	//************************************
	CListCtrl* AddListCtrl(CRect rect, UINT nID, int bColHeader = 0);

	//************************************
	// Method:    AddTabViewCtrl
	// FullName:  CBaseDlg::AddTabViewCtrl
	// Access:    public 
	// Returns:   CTabViewCtrl*
	// Qualifier:
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CTabViewCtrl* AddTabViewCtrl(CRect rect, UINT nID);

	//************************************
	// Method:    AddEdit
	// FullName:  CBaseDlg::AddEdit
	// Access:    public 
	// Returns:   CEdit*
	// Qualifier:
	// Description: add CString,int,float,double edit ctrl that verify input and output data
	// Parameter: CRect rect
	// Parameter: UINT nID
	// 
	// Parameter: CString & strData
	// Parameter: int maxChars
	// 
	// Parameter: double & dData
	// Parameter: double minVal
	// Parameter: double maxVal
	//************************************
	CEdit* AddEdit(CRect rect, UINT nID = 65535U);
	CEdit* AddEdit(CRect rect, UINT nID, CString& strData, int maxChars = INT_MAX);
	CEdit* AddEdit(CRect rect, UINT nID, double& dData, double minVal = DBL_MIN, double maxVal = DBL_MAX);

	//************************************
	// Method:    AddProgressBar
	// FullName:  CBaseDlg::AddProgressBar
	// Access:    public 
	// Returns:   CProgressCtrl*
	// Qualifier:
	// Parameter: CRect rect
	// Parameter: UINT nID
	// 
	// Parameter: int & nPos
	// Parameter: int minVal
	// Parameter: int maxVal
	//************************************
	CProgressCtrl* AddProgressBar(CRect rect, UINT nID = 65535U);
	CProgressCtrl* AddProgressBar(CRect rect, UINT nID, int& nPos, int minVal = 0, int maxVal = 100);

	//************************************
	// Method:    AddSliderBar
	// FullName:  CBaseDlg::AddSliderBar
	// Access:    public 
	// Returns:   CSliderCtrl*
	// Qualifier:
	// Parameter: CRect rect
	// Parameter: UINT nID
	// 
	// Parameter: int & nPos
	// Parameter: int minVal
	// Parameter: int maxVal
	//************************************
	CSliderCtrl* AddSliderBar(CRect rect, UINT nID = 65535U);
	CSliderCtrl* AddSliderBar(CRect rect, UINT nID, int& nPos, int minVal = 0, int maxVal = 100);

	//************************************
	// Method:    AddSliderGroup
	// FullName:  CBaseDlg::AddSliderGroup
	// Access:    public 
	// Returns:   CSliderGroup*
	// Qualifier:
	// Description: add slidebars with two button
	// Parameter: CRect rect
	// Parameter: UINT nID
	// Parameter: int & nPos
	// Parameter: int minVal
	// Parameter: int maxVal
	//************************************
	CSliderGroup* AddSliderGroup(CRect rect, UINT nID=65535U);
	CSliderGroup* AddSliderGroup(CRect rect, UINT nID, int& nPos, int minVal = 0, int maxVal = 100);

	//************************************
	// Method:    AddIndicator
	// FullName:  CBaseDlg::AddIndicator
	// Access:    public 
	// Returns:   CIndicator*
	// Qualifier:
	// Parameter: CRect rect
	// Parameter: UINT nID
	// Parameter: COLORREF highlightColor
	// Parameter: COLORREF normalColor
	//************************************
	CIndicator* AddIndicator(CRect rect, UINT nID,COLORREF highlightColor =RGB(255,0,0),COLORREF normalColor=RGB(255,255,255));

	//************************************
	// Method:    AddMyCheckButton
	// FullName:  CBaseDlg::AddMyCheckButton
	// Access:    public 
	// Returns:   CMyCheckButton*
	// Qualifier:
	// Description: add checkbuttons that cannot change state by clicked, only for indication
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CMyCheckButton* AddMyCheckButton(CString sCaption, CRect rect, UINT nID);

	//************************************
	// Method:    AddDrawView
	// FullName:  CBaseDlg::AddDrawView
	// Access:    public 
	// Returns:   CDrawView*
	// Qualifier:
	// Description: add drawviews, but not complete
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CDrawView* AddDrawView(CRect rect, UINT nID = 0);

	//************************************
	// Method:    AddEditParam
	// FullName:  CBaseDlg::AddEditParam
	// Access:    public 
	// Returns:   CEdit*
	// Qualifier:
	// Description: add edit ctrls with groupbox
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	// 
	// Parameter: CString & strData
	// Parameter: int maxChars
	// 
	// Parameter: double & dData
	// Parameter: double minVal
	// Parameter: double maxVal
	//************************************
	CEdit* AddEditParam(CString sCaption, CRect rect, UINT nID = 65535U);
	CEdit* AddEditParam(CString sCaption, CRect rect, UINT nID, CString& strData, int maxChars = INT_MAX);
	CEdit* AddEditParam(CString sCaption, CRect rect, UINT nID, double& dData, double minVal = DBL_MIN, double maxVal = DBL_MAX);

	//************************************
	// Method:    AddCheckParam
	// FullName:  CBaseDlg::AddCheckParam
	// Access:    public 
	// Returns:   CButton*
	// Qualifier:
	// Description: add CheckButton with Groupbox
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	// 
	// Parameter: BOOL & bCheck
	//************************************
	CButton* AddCheckParam(CString sCaption, CRect rect, UINT nID);
	CButton* AddCheckParam(CString sCaption, CRect rect, UINT nID, BOOL& bCheck);

	//************************************
	// Method:    AddComboParam
	// FullName:  CBaseDlg::AddComboParam
	// Access:    public 
	// Returns:   CComboBox*
	// Qualifier:
	// Description: add ComboBox with Groupbox
	// Parameter: CString sCaption
	// Parameter: CString sItem[]
	// Parameter: int nCount
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CComboBox* AddComboParam(CString sCaption, CString sItem[], int nCount, CRect rect, UINT nID);
	CComboBox* AddComboParam(CString sCaption, CString sItem[], int nCount, CRect rect, UINT nID, CString& strCaption, int maxChars = INT_MAX);
	
	//************************************
	// Method:    AddTextParam
	// FullName:  CBaseDlg::AddTextParam
	// Access:    public 
	// Returns:   CStatic*
	// Qualifier:
	// Description: add Static text with Groupbox
	// Parameter: CString sCaption
	// Parameter: CString sParam
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CStatic* AddTextParam(CString sCaption, CString sParam, CRect rect, UINT nID = 65535U);
	
	//************************************
	// Method:    AddCheckEditParam
	// FullName:  CBaseDlg::AddCheckEditParam
	// Access:    public 
	// Returns:   CEdit*
	// Qualifier:
	// Description: add Edit with CheckButton and Groupbox
	// Parameter: CString sCaption
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CEdit* AddCheckEditParam(CString sCaption, CRect rect, UINT nID = 65535U);
	CEdit* AddCheckEditParam(CString sCaption, CRect rect, UINT nID, BOOL& bCheck, CString& sData, int maxChars = INT_MAX);
	CEdit* AddCheckEditParam(CString sCaption, CRect rect, UINT nID, BOOL& bCheck, double& dData, double minVal = DBL_MIN, double maxVal = DBL_MAX);

	//************************************
	// Method:    AddBackground
	// FullName:  CBaseDlg::AddBackground
	// Access:    public 
	// Returns:   CGradientBackground*
	// Qualifier:
	// Parameter: CRect rect
	// Parameter: UINT nID
	//************************************
	CGradientBackground* AddBackground(CRect rect, UINT nID = 65535U);

// DDX and DDV
protected:
	void AFXAPI DDX_SliderGroup(CDataExchange* pDX, int nIDC, int& value);
	void AFXAPI DDX_Progress(CDataExchange* pDX, int nIDC, int& value);
};
