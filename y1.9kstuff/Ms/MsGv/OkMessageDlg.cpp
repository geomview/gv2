// OkMessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "OkMessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OkMessageDlg dialog


OkMessageDlg::OkMessageDlg(char *messageString,
                           char *windowCaption /*=NULL*/,
                           CWnd* pParent /*=NULL*/)
    : CDialog(OkMessageDlg::IDD, pParent)
{
        //{{AFX_DATA_INIT(OkMessageDlg)
                // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT

    mpMessageString = messageString;
    mpWindowCaption = windowCaption;
}

void OkMessageDlg::DoDialog(char *messageString,
                            char *windowCaption /*= NULL*/)
{
    OkMessageDlg msgDlg(messageString, windowCaption);
    msgDlg.DoModal();
}

void OkMessageDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(OkMessageDlg)
                // NOTE: the ClassWizard will add DDX and DDV calls here
        //}}AFX_DATA_MAP
}

BOOL OkMessageDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    if (mpWindowCaption) SetWindowText(mpWindowCaption);
    SetDlgItemText(IDC_MESSAGE_STATIC, mpMessageString);
    return TRUE;
}



BEGIN_MESSAGE_MAP(OkMessageDlg, CDialog)
        //{{AFX_MSG_MAP(OkMessageDlg)
                // NOTE: the ClassWizard will add message map macros here
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OkMessageDlg message handlers
