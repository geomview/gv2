//-*-C++-*-
#if !defined(AFX_OKMESSAGEDLG_H__FE68B1AD_5A5D_11D1_9995_00C04FB616FB__INCLUDED_)
#define AFX_OKMESSAGEDLG_H__FE68B1AD_5A5D_11D1_9995_00C04FB616FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OkMessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OkMessageDlg dialog

class OkMessageDlg : public CDialog
{
    // Construction
public:
    OkMessageDlg(char *messageString,
                 char *windowCaption = NULL,
                 CWnd* pParent = NULL);   // standard constructor

    static void DoDialog(char *messageString,
                         char *windowCaption = NULL);

    // Dialog Data
    //{{AFX_DATA(OkMessageDlg)
    enum { IDD = IDD_OK_MESSAGE_DLG };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(OkMessageDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    virtual BOOL OnInitDialog();                

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(OkMessageDlg)
    // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

        private:
    char *mpMessageString;
    char *mpWindowCaption;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OKMESSAGEDLG_H__FE68B1AD_5A5D_11D1_9995_00C04FB616FB__INCLUDED_)
