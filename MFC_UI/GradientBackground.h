#pragma once
class CGradientBackground :
	public CStatic
{
public:
	CGradientBackground();
	CGradientBackground(int R,int G,int B);
	~CGradientBackground();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
protected:
	int r;
	int g;
	int b;
};

