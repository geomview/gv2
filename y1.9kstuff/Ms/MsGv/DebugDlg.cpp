// DebugDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DebugDlg.h"
#include "MsGvDoc.h"

#include "GvPath.h"
#include "Geom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DebugDlg dialog


DebugDlg::DebugDlg(CWnd* pParent /*=NULL*/)
        : CDialog(DebugDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(DebugDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    
    Create(IDD_DEBUG_DLG);
    SetWindowText("Geomview Debug Dialog");

    // taken out for persistance
    // ShowWindow(SW_SHOW);
}


void DebugDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(DebugDlg)
                // NOTE: the ClassWizard will add DDX and DDV calls here
        //}}AFX_DATA_MAP
}

void DebugDlg::OnCancel()
{
    DestroyWindow();
}

void DebugDlg::OnOK()
{
    ShowWindow(SW_HIDE);
    // DestroyWindow();
}



BEGIN_MESSAGE_MAP(DebugDlg, CDialog)
        //{{AFX_MSG_MAP(DebugDlg)
        ON_BN_CLICKED(IDC_DOIT_BUTTON, OnDoit)
        ON_BN_CLICKED(IDC_DEBUG_CLEAR_BUTTON, OnDebugClear)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DebugDlg message handlers

void DebugDlg::PostNcDestroy() 
{
        // TODO: Add your specialized code here and/or call the base class
        
    CDialog::PostNcDestroy();
    delete this;
}

CString DebugDlg::GetInputText()
{
    CEdit *editBox = (CEdit*)GetDlgItem(IDC_DEBUG_EDIT1);
    CString text;
    editBox->GetWindowText(text);
    return text;
}

void DebugDlg::AppendOutputText(const char *text)
{
    CEdit *outputBox = (CEdit*)GetDlgItem(IDC_DEBUG_OUTPUT_EDIT);
    outputBox->SetSel(-1, -1);
    outputBox->ReplaceSel(text);
}

void DebugDlg::ClearOutputText()
{
    CEdit *outputBox = (CEdit*)GetDlgItem(IDC_DEBUG_OUTPUT_EDIT);
    outputBox->SetSel(0, -1);
    outputBox->SetReadOnly(FALSE);
    outputBox->Clear();
    outputBox->SetReadOnly(TRUE);
}

void DebugDlg::OnDoit() 
{
#if 0  // commented out because GetGeom() is now gone.
    if (CMsGvDoc::DocumentCount() < 1)
    {
        AppendOutputText("no documents found\r\n");
        return;
    }

    CMsGvDoc *doc = CMsGv:GetDocument(0);
    Geom *root = doc->GetGeom();

    CString text = GetInputText();
    LPTSTR textBuffer = text.GetBuffer(0);
    char *tok = strtok(textBuffer, " \t");
    int n;
    GvPath path;
    path.SetRoot(root);
    while (tok != NULL)
    {
        n = atoi(tok);
        path.AppendIndex(n);
        tok = strtok(NULL, " \t");
    }

    Geom *g;
    try {
        g = path.Resolve();
    }
    catch (UtException *e) {
        AppendOutputText("Error: ");
        AppendOutputText(e->Message());
        AppendOutputText("\r\n");
        delete e;
        return;
    }

    char output[1024];
    sprintf(output, "geom at that path is of type %s",
            g->GetType()->mpName);
    AppendOutputText(output);
    AppendOutputText("\r\n");

#endif
}

void DebugDlg::OnDebugClear() 
{
    ClearOutputText();
}
