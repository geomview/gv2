//-*-C++-*-
#ifndef __MSGVOPENGLWINDOW_H__
#define __MSMGOPENGLWINDOW_H__

#if !defined(AFX_MSMGOPENGLWINDOW_H__0015F0F1_C70B_11D0_B881_0060B01A76F2__INCLUDED_)
#define AFX_MSMGOPENGLWINDOW_H__0015F0F1_C70B_11D0_B881_0060B01A76F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MsGvDoc.h"
#include "MgOpenGlContext.h"
#include "MgWindow.h"
#include "GvCamera.h"
#include "EventHandler.h"

// MsGvOpenGlWindow.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// MsGvOpenGlWindow window

class MsGvOpenGlWindow : public CWnd, public MgWindow, public GvCamera
{
    // Construction
public:
    MsGvOpenGlWindow(CMsGvDoc *doc);

    // Attributes
public:

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MsGvOpenGlWindow)
    //}}AFX_VIRTUAL

    // Implementation
public:
    virtual ~MsGvOpenGlWindow();

                   // Generated message map functions
protected:
    //{{AFX_MSG(MsGvOpenGlWindow)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Begin non-classwizard stuff

    BOOL InitializeOpenGL(BOOL rgba, BOOL depth, BOOL DoubleB);
    BOOL SetupPixelFormat(BOOL rgba, BOOL DoubleB);

    HGLRC             mWindowRC;
    CDC             * mpWindowDC;

    int               mCx, mCy;
    char              mTitle[256];
    CMsGvDoc        * mpDocument;
    EventHandler    * mpEventHandler;

    LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    
public:
    void SetupWindow(CWnd *parent, char *name, int xloc, int yloc, int width, 
                     int height, BOOL rgba, BOOL depth, BOOL DoubleB,
                     BOOL setupOpenGL);
    void SetupOpenGL(BOOL rgba, BOOL depth, BOOL DoubleB);
    void SetDocument(CMsGvDoc *doc);

    virtual void            SwapBuffers();
    virtual void            MakeCurrent();
    virtual void            UpdateScene();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSMGOPENGLWINDOW_H__0015F0F1_C70B_11D0_B881_0060B01A76F2__INCLUDED_)

#endif
