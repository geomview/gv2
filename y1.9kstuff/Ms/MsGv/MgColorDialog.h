#if !defined(AFX_MGCOLORDIALOG_H__CF350BD1_D775_11D0_B887_0060B01A76F2__INCLUDED_)
#define AFX_MGCOLORDIALOG_H__CF350BD1_D775_11D0_B887_0060B01A76F2__INCLUDED_

#include "MgColor.h"
#include "MgColorWindow.h"
#include "MgColorSlider.h"
#include "mgColorChoice.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MgColorDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MgColorDialog dialog		  

#define MG_COLOR_CHANGED WM_USER + 101
#define MG_CUSTOM_COLOR_CLICKED WM_USER + 102
#define MG_CUSTOM_COLOR_DOUBLE_CLICKED WM_USER + 103

class MgColorDialog : public CDialog
{
// Construction
public:
	MgColorDialog(CWnd* pParent = NULL);   // standard constructor	
	MgColorDialog(CWnd *pParent, MgRGB *Color);
	~MgColorDialog();

private:
	MgRGB *color;
	int width, height;
	MgColorWindow *win;
	MgColorSlider *slider;
	MgColorChoice *CustomColors[22];
	static MgColor CustomRGBs[22];
	static BOOL initialized;
	double CurrentR, CurrentG, CurrentB;
	int CurrentIndex;
	double BeginR, BeginG, BeginB;
	int boxInitialX;
	int boxInitialY;
	int boxInitialY2;
	int boxWidth;
	int boxHeight;
	int boxIncrement;

	void initializeColors();

// Dialog Data
	//{{AFX_DATA(MgColorDialog)
	enum { IDD = IDD_COLOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MgColorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MgColorDialog)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnOk();
	afx_msg void OnCancel();
	//}}AFX_MSG
	LONG OnColorChanged(UINT param1, LONG param2);
	LONG OnCustomClicked(UINT param1, LONG param2);
	LONG OnCustomDoubleClicked(UINT param1, LONG param2);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MGCOLORDIALOG_H__CF350BD1_D775_11D0_B887_0060B01A76F2__INCLUDED_)
