#if !defined(AFX_APPEARANCEDLG_H__7916BEB1_D135_11D0_B886_0060B01A76F2__INCLUDED_)
#define AFX_APPEARANCEDLG_H__7916BEB1_D135_11D0_B886_0060B01A76F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AppearanceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AppearanceDlg dialog

#include "MgAppearance.h"
#include "MgColorDialog.h"

class AppearanceDlg : public CDialog
{
// Construction
public:
	AppearanceDlg(CWnd* pParent = NULL);   // standard constructor
	AppearanceDlg(CWnd *pParent /*=NULL*/, MgAppearance *ap);

	MgAppearance *appearance;
	MgColorDialog *dlg;
	unsigned int defaultFlag;
	unsigned int defaultValid;
	unsigned int defaultOverride;
	float defaultNormalScale;
	int defaultLineWidth;
	MgAppearance::ShadingType defaultShading;
	int defaultDice[2];

	afx_msg OnAppearance(void);

// Dialog Data
	//{{AFX_DATA(AppearanceDlg)
	enum { IDD = IDD_APPEARANCE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AppearanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AppearanceDlg)
	afx_msg void OnConstant();
	afx_msg void OnEdges();
	afx_msg void OnFaces();
	afx_msg void OnFlat();
	afx_msg void OnInheritShading();
	afx_msg void OnInheritShow();
	afx_msg void OnNoLighting();
	afx_msg void OnNormals();
	afx_msg void OnOverrideShading();
	afx_msg void OnOverrideShow();
	afx_msg void OnShow();
	afx_msg void OnSmooth();
	afx_msg void OnVectors();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnColorEdges();
	afx_msg void OnColorFaces();
	afx_msg void OnColorNormals();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPEARANCEDLG_H__7916BEB1_D135_11D0_B886_0060B01A76F2__INCLUDED_)
