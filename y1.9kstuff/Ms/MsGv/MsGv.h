//-*-C++-*-
// MsGv.h : main header file for the MsGv application
//

#ifndef __AFXWIN_H__
        #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "AppearanceDlg.h"
#include "MgColorDialog.h"
#include "MgAppearance.h"

/////////////////////////////////////////////////////////////////////////////
// CMsGvApp:
// See MsGv.cpp for the implementation of this class
//

#include "GvApp.h"

class CMsGvApp : public CWinApp, public GvApp
{
private:
    AppearanceDlg *mpAppearanceDlg;

    BOOL OnIdle(LONG lCount);

public:
    CMsGvApp();
    ~CMsGvApp();
    virtual int ExitInstance();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMsGvApp)
public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

    // Implementation

    //{{AFX_MSG(CMsGvApp)
    afx_msg void OnAppAbout();
    afx_msg void OnPropertiesAppearance();
    afx_msg void OnPropertiesColor();
    afx_msg void OnPropertiesDoit();
    afx_msg void OnPropertiesTree();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
