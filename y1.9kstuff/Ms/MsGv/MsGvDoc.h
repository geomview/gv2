//-*-C++-*-
// MsGvDoc.h : interface of the CMsGvDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MsGvDOC_H__
#define __MsGvDOC_H__

#include "stdafx.h"
#include "GvWorld.h"

class CMsGvDoc : public GvWorld, public CDocument
{
protected: // create from serialization only
    CMsGvDoc();
    DECLARE_DYNCREATE(CMsGvDoc)

public:
    unsigned long p_mOldTime, p_mCurTime, p_mElapsedTime, p_mDrawTime;
    double p_mFramesPerSecond;
    int p_mFrameCount;

    void UpdateAll();

    friend class CMsGvApp;
    friend class CMsGvView;

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMsGvDoc)
public:
    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
    virtual void DeleteContents();
    //}}AFX_VIRTUAL

    // Implementation
public:
    virtual ~CMsGvDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
protected:
    //{{AFX_MSG(CMsGvDoc)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
        };

/////////////////////////////////////////////////////////////////////////////

#endif // __MsGvDOC_H__
