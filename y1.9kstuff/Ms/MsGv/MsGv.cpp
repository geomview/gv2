// MsGv.cpp : Defines the class behaviors for the application.
//



#include <stdio.h>
#include <string.h> // for strtok in debugging code below
#include <fcntl.h>
#include <iostream.h>
#include <fstream.h>
#include <crtdbg.h>

#include <io.h>

#include "stdafx.h"

#include "MsGv.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "MsGvDoc.h"
#include "MsGvView.h"
//#include "GeomOldOoglParser.h"
#include "GvPath.h"

#include "OkMessageDlg.h"
#include "DebugDlg.h"
//#include "TreeDlg.h"

#include "UtMemoryTracker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsGvApp

BEGIN_MESSAGE_MAP(CMsGvApp, CWinApp)
        //{{AFX_MSG_MAP(CMsGvApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        ON_COMMAND(ID_PROPERTIES_APPEARANCE, OnPropertiesAppearance)
        ON_COMMAND(ID_PROPERTIES_COLOR, OnPropertiesColor)
        ON_COMMAND(ID_PROPERTIES_DOIT, OnPropertiesDoit)
    //        ON_COMMAND(ID_PROPERTIES_TREE, OnPropertiesTree)
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
        // Standard print setup command
        ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsGvApp construction

CMsGvApp::CMsGvApp()
{
        // TODO: add construction code here,
        // Place all significant initialization in InitInstance
}

CMsGvApp::~CMsGvApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMsGvApp object

CMsGvApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsGvApp initialization

BOOL CMsGvApp::InitInstance()
{
    // Standard initialization
    // If you are not using these features and wish to reduce the size
    //  of your final executable, you should remove from the following
    //  the specific initialization routines you do not need.

#ifdef _AFXDLL
    Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

    //        AfxEnableControlContainer();
    LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    // Register the application's document templates.  Document templates
    //  serve as the connection between documents, frame windows and views.

    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(
                                         IDR_MSGVTYPE,
                                         RUNTIME_CLASS(CMsGvDoc),
                                         RUNTIME_CLASS(CChildFrame), // custom MDI child frame
                                         RUNTIME_CLASS(CMsGvView));
    AddDocTemplate(pDocTemplate);

    AllocConsole();

    int hCrt;
    FILE *hf;

    hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    hf = _fdopen((int)hCrt, "w");
    *stdout = *hf;
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Geomview for WindowsNT\n");

    hCrt = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
    hf = _fdopen((int)hCrt, "r");
    *stdin = *hf;
    setvbuf(stdin, NULL, _IONBF, 0);

    hCrt = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
    hf = _fdopen((int)hCrt, "w");
    *stderr = *hf;
    setvbuf(stderr, NULL, _IONBF, 0);
    // fprintf(stderr, "Testing Error Output!\n");

    // create main MDI Frame window
    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;
    m_pMainWnd = pMainFrame;

    // Parse command line for standard shell commands, DDE, file open
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

        // Dispatch commands specified on the command line
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

        // The main window has been initialized, so show and update it.
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();


    return TRUE;
}

int CMsGvApp::ExitInstance()
{
    // Put cleanup commands here.  The runtime environment calls
    // this function when the application exits.
#if UTMEMORYTRACKER
    UtMemoryTracker::ReportAll();
#endif
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

// Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CAboutDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        //{{AFX_MSG(CAboutDlg)
                // No message handlers
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
                // No message handlers
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMsGvApp::OnAppAbout()
{
        CAboutDlg aboutDlg;
        aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMsGvApp commands

BOOL CMsGvApp::OnIdle(LONG lCount)
{
    //for (int i = 0; i < CMsGvDoc::sDocumentCount; i++)
    //{
    //        CMsGvDoc::spDocuments[i]->UpdateAll();
    //}
                // Intergraph?? -- John had commented the above lines
                // out in his Intergraph version.
    // Sleep(1);    // Hack to make mouse events work on Intergraph machine.
        
    CWinApp::OnIdle(lCount);
    return(1);
}

void CMsGvApp::OnPropertiesAppearance()
{
    //        mpAppearanceDlg = new AppearanceDlg(NULL, mpBaseAppearance);
}

void CMsGvApp::OnPropertiesColor()
{
#if 0
        MgRGB *rgb = (mpBaseAppearance->GetFrontMaterial())->GetDiffuse();
        MgColorDialog *dlg = new MgColorDialog(NULL, rgb);
#endif
}

#if 0 // commented out because GetGeom() is gone now
void CMsGvApp::OnPropertiesTree()
{
    static TreeDlg *treeDlg = new TreeDlg();

    if (CMsGvDoc::DocumentCount() < 1)
        treeDlg->SetGeomTree(NULL);
    else
    {
        CMsGvDoc *doc = CMsGvDoc::GetDocument(0);
        Geom *root = doc->GetGeom();
        treeDlg->SetGeomTree(root);
    }
    treeDlg->Show();
}
#endif


void CMsGvApp::OnPropertiesDoit()
{
    static DebugDlg *debugDlg = new DebugDlg();

    debugDlg->Show();
#if 0

    OkMessageDlg::DoDialog("Here's an error message, you twerp!",
                        "My Geomview Message Window?");

    ::MessageBox(NULL, "Testing this messageBox", "Error!", MB_OK | MB_ICONWARNING);

#endif

}
