// MsGvView.cpp : implementation of the CMsGvView class
//

#include "MsGvView.h"

//#include "stdafx.h"
#include "mmsystem.h"
#include "MsGv.h"
#include "MsGvDoc.h"
#include "MsGvOpenGlWindow.h"
#include "MsGvThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CMsGvView

IMPLEMENT_DYNCREATE(CMsGvView, CView)

    BEGIN_MESSAGE_MAP(CMsGvView, CView)
    //{{AFX_MSG_MAP(CMsGvView)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_ERASEBKGND()
    ON_WM_MOVE()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
    END_MESSAGE_MAP()

    //////////////////////////////////////////////////////////////////////
    // CMsGvView construction/destruction

    CMsGvView::CMsGvView() 
{
    mpWin = NULL;
    mWindowInitialized = FALSE;
    mLastTextUpdate = 0;
    mpThread = NULL;
    //      CMsGvDoc *doc = GetDocument();
    //      doc->nviews++;
}

CMsGvView::~CMsGvView()
{
    CMsGvDoc *doc = GetDocument();
    if (mpWin) ::DeleteRef(mpWin);
    doc->RemoveView(this);
}

BOOL CMsGvView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs
    cs.style |=  ( WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
    return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMsGvView drawing

void CMsGvView::OnDraw(CDC* pDC)
{
    UpdateScene();
}

void CMsGvView::UpdateScene(void)
{
#ifdef MULTITHREADED
    if (mpThread != NULL)
        if ( (!mpThread->IsPainting()) && (mpThread->mPaintCount == 0)) 
        {
            mpThread->mPaintCount++;
            mpThread->PostThreadMessage(MsGvThread::MST_PAINT, 0, 0);
        }

#else
    if (mpWin != NULL) mpWin->UpdateScene();
#endif

    CMsGvDoc *doc = GetDocument();

    if (timeGetTime() - mLastTextUpdate > 1000)
    {
        char Text[100];
        sprintf(Text, "Frames per second: %lf    Draw time %d", 
                doc->p_mFramesPerSecond, doc->p_mDrawTime);
        // Fix for thread problem
        ::SetWindowText(::GetParent(GetSafeHwnd()), Text);

        doc->p_mFrameCount = 0;
        doc->p_mFramesPerSecond = 0;
        doc->p_mDrawTime = 0;
        mLastTextUpdate = timeGetTime();
    }
}

/////////////////////////////////////////////////////////////////////////////
// CMsGvView printing

BOOL CMsGvView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CMsGvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CMsGvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMsGvView diagnostics

#ifdef _DEBUG
void CMsGvView::AssertValid() const
{
    CView::AssertValid();
}

void CMsGvView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CMsGvDoc* CMsGvView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsGvDoc)));
    return (CMsGvDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMsGvView message handlers

void CMsGvView::OnSize(UINT nType, int cx, int cy) 
{
    CView::OnSize(nType, cx, cy);

    if (mpWin != NULL)
    {
        if (::IsWindow(mpWin->m_hWnd))
        {
            mpWin->MoveWindow(0, 0, cx, cy, FALSE);
        }
    }
}

void CMsGvView::MakeWin()
{
    // This code needs to be executed in this view's thread, so it
    // appears here in a separate procedure (rather than in OnCreate).
    // (I'm not sure why it has to be executed in the same thread, it
    // just doesn't seem to work otherwise).
    // mbp Mon Dec 29 22:24:20 1997

    mpWin = new MsGvOpenGlWindow(GetDocument());
    mpWin = mpWin;
    CRect rect;
    GetWindowRect(&rect);
    mpWin->SetupWindow(this, "Test Window",
                       0, 0, rect.Width(), rect.Height(), 
                       TRUE, TRUE, TRUE, TRUE);
    mWindowInitialized = TRUE;
    mpWin->MakeCurrent();
}


int CMsGvView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

#ifdef MULTITHREADED
    mpThread = new MsGvThread(this);
    mpThread->CreateThread();
    // MakeWin() happens in the thread's InitInstance(), which is called
    // by CreateThread() above.
#else
    // In the single-threaded case, just set up the window here.
    MakeWin();
#endif

    return 0;
}

void CMsGvView::OnDestroy()
{
    if (mpWin) {
        ::DeleteRef(mpWin);
        mpWin = NULL;
    }

#ifdef MULTITHREADED
    mpThread->PostThreadMessage(MsGvThread::MST_QUIT, 0, 0);
    DWORD result = ::WaitForSingleObject(mpThread->m_hThread, 500);
    if (result == WAIT_TIMEOUT)
        ::TerminateThread(mpThread->m_hThread, 0);
#endif

    CView::OnDestroy();
}

//LRESULT CMsGvView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//    GvEvent event;
//
//    switch(message)
//    {
//    case WM_LBUTTONDOWN:
//        event.mEventData.mLocation.x = LOWORD(lParam);
//        event.mEventData.mLocation.y = HIWORD(lParam);
//        event.mEventType = GvEvent::GV_LBUTTON_DOWN;
//        if(mEventHandler.HandleEvent(event))
//            return(TRUE);
//    default:
//        return(CView::WindowProc(message, wParam, lParam));
//    }
//}
