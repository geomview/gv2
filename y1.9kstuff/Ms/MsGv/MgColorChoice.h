#if !defined(AFX_MGCOLORCHOICE_H__CDB542A2_DDC4_11D0_B887_0060B01A76F2__INCLUDED_)
#define AFX_MGCOLORCHOICE_H__CDB542A2_DDC4_11D0_B887_0060B01A76F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MgColorChoice.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MgColorChoice window

class MgColorChoice : public CWnd
{
// Construction
public:
	MgColorChoice();
	MgColorChoice(CWnd *Parent, int xloc, int yloc, int Width, int Height, int Index,
							 double currentR, double currentG, double currentB);

	void SetRGB(double R, double G, double B);

private:
	double CurrentR, CurrentG, CurrentB;
	int width, height;
	int index;
	CBrush brush;
	CPen pen;
	CWnd *parent;
	BOOL Initialized;
	int lastTime;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MgColorChoice)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MgColorChoice();

	// Generated message map functions
protected:
	//{{AFX_MSG(MgColorChoice)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MGCOLORCHOICE_H__CDB542A2_DDC4_11D0_B887_0060B01A76F2__INCLUDED_)
