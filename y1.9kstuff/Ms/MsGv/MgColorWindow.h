#if !defined(AFX_MGCOLORWINDOW_H__CF350BD2_D775_11D0_B887_0060B01A76F2__INCLUDED_)
#define AFX_MGCOLORWINDOW_H__CF350BD2_D775_11D0_B887_0060B01A76F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MgColorWindow.h : header file
//

void RGBToHSL(double r, double g, double b, double &H, double &S, double &L);
void HSLToRGB(double h, double s, double l, double &R, double &G, double &B);
void MyHSLToRGB(double H, double S, double L, double &R, double &G, double &B);

/////////////////////////////////////////////////////////////////////////////
// MgColorWindow window

class MgColorWindow : public CWnd
{
// Construction
public:
	MgColorWindow();
	MgColorWindow(CWnd *Parent, int xloc, int yloc, int Width, int Height,
				  double currentH = .5, double currentS = 1.0);

	double GetH() { return(CurrentH); }
	double GetS() { return(CurrentS); }

	void SetH(double H) { CurrentH = H; InvalidateRect(NULL, FALSE); }
	void SetS(double S) { CurrentS = S; InvalidateRect(NULL, FALSE); }

	double CurrentH, CurrentS;

private:
	int width, height, bits;
	BOOL lButtonDown;
	int OldPointX;
	int OldPointY;
	CBitmap bitmap;
	CDC cdc;
	CWnd *parent;
	static int redDepth, blueDepth, greenDepth;
	
	void DrawBorder(CDC *dc);
	void DrawPointer(CDC *dc);
	void SetupBitmap(void);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MgColorWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MgColorWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(MgColorWindow)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MGCOLORWINDOW_H__CF350BD2_D775_11D0_B887_0060B01A76F2__INCLUDED_)
