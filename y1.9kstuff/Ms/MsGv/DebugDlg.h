//-*-C++-*-
#if !defined(AFX_DEBUGDLG_H__2E3DDF79_5AB4_11D1_9996_00C04FB616FB__INCLUDED_)
#define AFX_DEBUGDLG_H__2E3DDF79_5AB4_11D1_9996_00C04FB616FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// debugdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DebugDlg dialog

class DebugDlg : public CDialog
{
    // Construction
public:
    DebugDlg(CWnd* pParent = NULL);   // standard constructor

    // Dialog Data
    //{{AFX_DATA(DebugDlg)
    enum { IDD = IDD_DEBUG_DLG };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA

    void Show() { ShowWindow(SW_SHOW); }

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(DebugDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL


    virtual void OnCancel();
    virtual void OnOK();

    // Implementation
protected:

    CString GetInputText();
    void AppendOutputText(const char *text);
    void ClearOutputText();

    // Generated message map functions
    //{{AFX_MSG(DebugDlg)
    afx_msg void OnDoit();
	afx_msg void OnDebugClear();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBUGDLG_H__2E3DDF79_5AB4_11D1_9996_00C04FB616FB__INCLUDED_)
