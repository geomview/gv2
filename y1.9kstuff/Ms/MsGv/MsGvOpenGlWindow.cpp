// MsGvOpenGlWindow.cpp : implementation file
//

#include "stdafx.h"
//#include "MsGv.h"
//#include "MsGvDoc.h"
//#include "MsGvView.h"
#include "MsGvOpenGlWindow.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsGvOpenGlWindow

TYPE_IMPLEMENT_TYPEINFO1(MsGvOpenGlWindow, GvCamera);

MsGvOpenGlWindow::MsGvOpenGlWindow(CMsGvDoc *doc) : 
    mWindowRC(0), mpWindowDC(0)
{
    // mbp-purify: added some lines here
    mCx = mCy = 0;
    mpDocument = doc;
    mpEventHandler = new EventHandler(doc, 0, 0);
    mpWindowDC = NULL;
    GvCamera::SetTarget(mpDocument->GetBaseWrapped());
    mpDocument->AddFreeCamera(this);
}

MsGvOpenGlWindow::~MsGvOpenGlWindow()
{
    if (mpWindowDC) delete mpWindowDC;        // mbp-purify
    if (mpEventHandler) delete mpEventHandler;        // mbp-purify
    mpDocument->DeleteFreeCamera(this);
}

/////////////////////////////////////////////////////////////////////////////
// Begin non-classwizard implementations

void MsGvOpenGlWindow::SetupWindow(CWnd *parent, char *name, int xloc, int yloc, int width, 
                                   int height, BOOL rgba, BOOL depth, BOOL DoubleB, BOOL setupOpenGL)
{
    CString WindowClass;
    BOOL result;
    
    WindowClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ,
                                      AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

    if (parent != NULL)
    {
        result = Create(WindowClass, name, WS_CHILD, CRect(xloc, yloc, xloc + width, 
                                                           yloc + height), parent, NULL);
    }
    else
    {
        result = CreateEx(WS_EX_OVERLAPPEDWINDOW, WindowClass, name, WS_OVERLAPPEDWINDOW | WS_BORDER, 
                          xloc, yloc, width, height, *parent, NULL);
    }
    if (result == NULL)
    {
        MessageBox("Can't Open Window!");
        PostQuitMessage(0);
    }
    
    if (setupOpenGL)
    {               
        SetupOpenGL(rgba, depth, DoubleB);
    }

    mpEventHandler->SetWindowDim(width, height);
}

void MsGvOpenGlWindow::SetupOpenGL(BOOL rgba, BOOL depth, BOOL DoubleB)
{
    if (InitializeOpenGL(rgba, depth, DoubleB))
    {
        UpdateWindow();
        ShowWindow(SW_SHOW);
    }
    else
        PostQuitMessage(0);     
}

void MsGvOpenGlWindow::SetDocument(CMsGvDoc *doc)
{
    mpDocument = doc;
}

BOOL MsGvOpenGlWindow::InitializeOpenGL(BOOL rgba, BOOL depth, BOOL DoubleB)
{
#if _TRACEGL
    {
        static FILE *fp = NULL;
        if (fp == NULL) 
        {
            fp = fopen("tracegl.out", "w");
            TRACEglSetOutput(fp);
        }
    }
#endif // _TRACEGL

    if (!(mpWindowDC = new CClientDC(this)))
    {
        MessageBox("Couldn't Get a Device Context For OpenGL Window");
        return(FALSE);
    }

    if (!SetupPixelFormat(rgba, DoubleB))
    {
        return(FALSE);  // this handles error Setting itself
    }

    if (!(mWindowRC = wglCreateContext(mpWindowDC->GetSafeHdc())))
    {
        MessageBox("Couldn't Create a OpenGL Rendering Context");
        return(FALSE);
    }
    if (!wglMakeCurrent(mpWindowDC->GetSafeHdc(), mWindowRC))
    {
        MessageBox("Couldn't Enable the OpenGL Rendering Context");
        return(FALSE);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    if (DoubleB)
    {
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    }

    return(TRUE);
}

BOOL MsGvOpenGlWindow::SetupPixelFormat(BOOL rgba, BOOL DoubleB)
{
    unsigned int mask = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;

    if (rgba)
        mask |= PFD_TYPE_RGBA;
    if (DoubleB)
        mask |= PFD_DOUBLEBUFFER;


    PIXELFORMATDESCRIPTOR pfd = 
    {
        sizeof(PIXELFORMATDESCRIPTOR), 1, 
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE,
        PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
    };

    int pixelFormat;

    if (!(pixelFormat = ChoosePixelFormat(mpWindowDC->GetSafeHdc(), &pfd)))
    {
        MessageBox("Couldn't Find a Compatable Pixel Format");
        return(FALSE);
    }
    if (!(SetPixelFormat(mpWindowDC->GetSafeHdc(), pixelFormat, &pfd)))
    {
        MessageBox("Couldn't Set the Pixel Format");
        return(FALSE);
    }
    return(TRUE);
}

void MsGvOpenGlWindow::SwapBuffers()
{
    CRect rect;
    ::SwapBuffers(mpWindowDC->GetSafeHdc());
}

void MsGvOpenGlWindow::MakeCurrent()
{  
    if (!::wglMakeCurrent(mpWindowDC->GetSafeHdc(), mWindowRC))
        abs(0);
}

void MsGvOpenGlWindow::UpdateScene()
{
#ifndef MULTITHREADED
    MakeCurrent();
#endif
    //      MgWindow::Position pos;
    //      pos.p_XMin = 0;
    //      pos.p_XMax = mCx;
    //      pos.p_YMin = 0;
    //      pos.p_YMax = mCy;
    //      SetCurrentPosition(pos);
    //      CRect rect;
    //      GetWindowRect(&rect);
    //      mpMg->ReshapeViewport();

  //mpDocument->DrawScene(mpMg);
    GvCamera::Render();
}

BEGIN_MESSAGE_MAP(MsGvOpenGlWindow, CWnd)
    //{{AFX_MSG_MAP(MsGvOpenGlWindow)
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
    END_MESSAGE_MAP()


    /////////////////////////////////////////////////////////////////////////////
    // MsGvOpenGlWindow message handlers

    void MsGvOpenGlWindow::OnSize(UINT nType, int cx, int cy) 
{
    CWnd::OnSize(nType, cx, cy);

#ifndef MULTITHREADED   
    MakeCurrent();
#endif
    MgWindow::Position pos;
    pos.p_XMin = 0;
    pos.p_XMax = cx;
    pos.p_YMin = 0;
    pos.p_YMax = cy;
    SetCurrentPosition(pos);
    GetMgContext()->ReshapeViewport();
    mpEventHandler->SetWindowDim(cx, cy);

    mCx = cx;
    mCy = cy;
}

BOOL MsGvOpenGlWindow::OnEraseBkgnd(CDC* pDC) 
{
    return TRUE;  // Don't let Windows erase the background
}

static MgColorA darkblue(0, 0, .2, 1);

int MsGvOpenGlWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    SetFOV(60.0);

    MgContext *mg = new MgOpenGlContext;
    SetMgContext(mg);
    mg->SetWindow(this);
    mg->SetBackgroundColor(darkblue);
    mg->SetCamera(GetMgCamera());

    return 0;
}

void MsGvOpenGlWindow::OnDestroy() 
{
    CWnd::OnDestroy();

    if (FALSE == ::wglMakeCurrent(0, 0))
    {
        MessageBox("Couldn't remove the current rendering context.");
    }
    if (FALSE == ::wglDeleteContext(mWindowRC)) 
    {
        MessageBox("Couldn't delete the rendering context");
    }
    if (mpWindowDC) 
    {
        delete mpWindowDC;
        mpWindowDC = NULL;
    }
}

void MsGvOpenGlWindow::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    //      UpdateScene();
    //      SwapBuffers(dc);
}

LRESULT MsGvOpenGlWindow::WindowProc(UINT message,
                                     WPARAM wParam,
                                     LPARAM lParam)
{
    GvEvent event;
    event.mTime = GetMessageTime();

    switch(message)
    {
    case WM_LBUTTONDOWN:
        SetCapture();
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::LBUTTON_DOWN;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    case WM_LBUTTONUP:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::LBUTTON_UP;
        if(mpEventHandler->HandleEvent(event))
        {
            ReleaseCapture();
            return(0);
        }
        break;
    case WM_LBUTTONDBLCLK:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::LBUTTON_DOUBLE_CLICK;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    case WM_RBUTTONDOWN:
        SetCapture();
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::RBUTTON_DOWN;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    case WM_RBUTTONUP:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::RBUTTON_UP;
        if(mpEventHandler->HandleEvent(event))
        {
            ReleaseCapture();
            return(0);
        }
        break;
    case WM_RBUTTONDBLCLK:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::RBUTTON_DOUBLE_CLICK;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    case WM_MBUTTONDOWN:
        SetCapture();
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::MBUTTON_DOWN;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    case WM_MBUTTONUP:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::MBUTTON_UP;
        if(mpEventHandler->HandleEvent(event))
        {
            ReleaseCapture();
            return(0);
        }
        break;
    case WM_MBUTTONDBLCLK:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::MBUTTON_DOUBLE_CLICK;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    case WM_MOUSEMOVE:
        event.mLocation.x = LOWORD(lParam);
        event.mLocation.y = HIWORD(lParam);
        event.mEventType = GvEvent::MOUSE_MOVE;
        if(mpEventHandler->HandleEvent(event))
            return(0);
        break;
    }
    return(CWnd::WindowProc(message, wParam, lParam));
}

