//-*-C++-*-
// MsGvView.h : interface of the CMsGvView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MsGvVIEW_H__
#define __MsGvVIEW_H__

#include "StdAfx.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

class CMsGvView : public CView
{
protected: // create from serialization only
    CMsGvView();
    DECLARE_DYNCREATE(CMsGvView)

    // Attributes
public:
    class CMsGvDoc* GetDocument();

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMsGvView)
public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    //}}AFX_VIRTUAL

    // Implementation
public:
    virtual ~CMsGvView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Generated message map functions
protected:
    //{{AFX_MSG(CMsGvView)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    class MsGvOpenGlWindow *GetWin() { return mpWin; }
    void MakeWin();
    void UpdateScene();

private:
    class MsGvOpenGlWindow * mpWin;
    BOOL                     mWindowInitialized;
    unsigned long            mLastTextUpdate;
    class MsGvThread       * mpThread;
};

#ifndef _DEBUG  // debug version in MsGvView.cpp
inline class CMsGvDoc* CMsGvView::GetDocument()
   { return (class CMsGvDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////



#endif
