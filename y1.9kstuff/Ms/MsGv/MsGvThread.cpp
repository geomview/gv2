// MsGvThread.cpp : implementation file
//

#include "MsGvThread.h"

#include "mmsystem.h"
#include "MsGv.h"
#include "MsGvView.h"
#include "MsGvOpenGlWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsGvThread

IMPLEMENT_DYNCREATE(MsGvThread, CWinThread)

MsGvThread::MsGvThread()
{
}

MsGvThread::MsGvThread(CMsGvView *view)
{
    mpView = view;
    mPainting = FALSE;
    mPaintCount = 0;
}

MsGvThread::~MsGvThread()
{
}

BOOL MsGvThread::InitInstance()
{
    mpView->MakeWin();
    return TRUE;
}

int MsGvThread::ExitInstance()
{
    // TODO:  perform any per-thread cleanup here
    return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MsGvThread, CWinThread)
    //{{AFX_MSG_MAP(MsGvThread)
            // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
    ON_THREAD_MESSAGE(MST_PAINT, Paint)
    ON_THREAD_MESSAGE(MST_QUIT, Quit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsGvThread message handlers

afx_msg void MsGvThread::Paint(UINT param1, LONG param2)
{
    mPainting = TRUE;
    mpView->GetWin()->UpdateScene();
    mPainting = FALSE;
    mPaintCount--;
}

afx_msg void MsGvThread::Quit(UINT param1, LONG param2)
{
    AfxEndThread(0);
}

BOOL MsGvThread::OnIdle(LONG lCount) 
{
    //mpWin->UpdateScene();
    //return(CWinThread::OnIdle(lCount));
    return(0);
}
