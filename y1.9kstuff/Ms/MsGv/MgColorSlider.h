#if !defined(AFX_MGCOLORSLIDER_H__F87B6F95_DCF1_11D0_B887_0060B01A76F2__INCLUDED_)
#define AFX_MGCOLORSLIDER_H__F87B6F95_DCF1_11D0_B887_0060B01A76F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MgColorSlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MgColorSlider window

class MgColorSlider : public CWnd
{
// Construction
public:
	MgColorSlider();
	MgColorSlider(CWnd *parent, int xloc, int yloc, int width, int height, 
				  double currentH = .5, double currentS = 1.0, double currentL = .5);

	void SetH(double h) { CurrentH = h; SetupBitmap(); CDC *dc = new CClientDC(this); 
						  dc->BitBlt(1, 1, width / 2 - 2, height - 2, &cdc, 1, 1, SRCCOPY); }
	void SetS(double s) { CurrentS = s; SetupBitmap(); CDC *dc = new CClientDC(this); 
						  dc->BitBlt(1, 1, width / 2 - 2, height - 2, &cdc, 1, 1, SRCCOPY); }

	double GetL(void) { return(CurrentL); }
	double CurrentH, CurrentS, CurrentL;

private:
	CBitmap bitmap;
	CDC cdc;
	CWnd *parent;
	int width, height;
	int bits;
	BOOL MouseDown;

	void SetupBitmap();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MgColorSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MgColorSlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(MgColorSlider)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MGCOLORSLIDER_H__F87B6F95_DCF1_11D0_B887_0060B01A76F2__INCLUDED_)
