//************************************
// Copyright:    XT
// Authors:  Run
// Date:    2016/1/14 
// Descriptions:   ���������Ի���
//			�����ӶԻ��򡢵����Ի���
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
	BASE_BUTTON,// ������ť
	BASE_COMMOM_BUTTON,// ͨ�ð�ť
	BASE_CHECK_BUTTON,// ״̬��ť
	BASE_STATIC,// ��̬�ı��ؼ�
	BASE_COLOR_TEXT,// ��ɫ�ı��ؼ�
	BASE_EDIT_CSTRING,// �ı��༭��
	BASE_EDIT_DOUBLE,// ���ֱ༭��̬��ť
	BASE_SLIDER,// ������
	BASE_PROGRESS,// ������
	BASE_GROUPBOX,// Ⱥ��ؼ�
	BASE_COMBOBOX,// ��Ͽ�
	BASE_LIST,// �б��
	BASE_EDIT_PARAM,// �����������
	BASE_CHECK_PARAM,// ����״̬���
	BASE_COMBO_PARAM,// ������Ͽ����
	BASE_TEXT_PARAM,// �����������
	BASE_CHECK_EDIT_PARAM,// ����״̬�������
	BASE_TABVIEW,// ��ǩ��ͼ�ؼ�
	BASE_SLIDER_GROUP,// ��������Ͽ�
	BASE_INDICATOR,// ָʾ��
	BASE_MY_CHECK_BUTTON,// ����ָʾ��״̬
	BASE_GRADIENT_BACKGROUND,// ���䱳��
	BASE_DRAWVIEW// ��ͼ�ؼ�����û���
};

typedef struct
{
	// �ؼ�����
	int type;
	CString sCaption;
	DWORD dwStyle;
	CRect rect;
	CWnd* pParent;// ���ؼ�
	UINT nID;// ���ؼ�id
	CWnd* pCtrl;// ���ؼ�
	LPVOID pInOutData;// �����������
	int nMaxChars;// ������󳤶ȣ�BASE_EDIT_CSTRING��Ч
	double dMaxVal;// �������ֵ
	double dMinVal;// ������Сֵ
	int nDataCount;// ������������
} BaseDlgCtrlStruct;

class CTabViewCtrl;
class CBaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBaseDlg)

public:
	CBaseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseDlg();

// Attributes
private:
	CWnd* pParent;// ���ؼ�ָ��
	COLORREF m_bkColor;// ������ɫ
	vector<BaseDlgCtrlStruct> m_vecCtrl;// �ڲ��ؼ�����
	BOOL m_bMode;// �Ƿ�Ϊģ̬�Ի���
	BOOL m_bInit;// �Ƿ��ʼ����
	CFont mFont;// ����
	int mFontSize;// �����С
	CMyDlgTemplate m_dlgTemp;//����ģ��
	HICON  m_hIcon;// ͼ��
	enum { IDICON = 1 };// ͼ��ID

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
