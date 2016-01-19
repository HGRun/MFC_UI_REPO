MFC quick programming
============================

[TOC]

Introduction
------------
[MFC\\_UI_REPO](https://github.com/HGRun/MFC_UI_REPO.git) is help to MFC quick programming.

Environment
------------
VS2013 (and OpenCV if need)

1. download vs2013 ，not comment on vs2015   
2. If OpenCV, set up your OpenCV Environment (OpenCV 2.x or 3.x if need) 
3. download [MFC\\_UI_REPO](https://github.com/HGRun/MFC_UI_REPO.git) 
4. New a MFC project
5. Add MFC\_UI\_REPO to your project

6. Add ChildDlg and PopupDlg

7. Add Controls

	```python
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
	```
8. If OpenCV, define OpenCV and use AddMatView