//-*-C++-*-
#ifndef __MSGVTHREAD_H__
#define __MSGVTHREAD_H__

#include "StdAfx.h"

#if !defined(AFX_MSGVTHREAD_H__0DCAB225_CBC7_11D0_B885_0060B01A76F2__INCLUDED_)
#define AFX_MSGVTHREAD_H__0DCAB225_CBC7_11D0_B885_0060B01A76F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// MsGvThread thread

class MsGvThread : public CWinThread
{
    DECLARE_DYNCREATE(MsGvThread)
protected:
    MsGvThread();           // protected constructor used by dynamic creation 
    class CMsGvView *mpView;

public:
    MsGvThread(class CMsGvView *View);

    // Attributes
public:
    enum {
        MST_PAINT = WM_USER + 1,
        MST_QUIT  = WM_USER + 2
    };

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MsGvThread)
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL OnIdle(LONG lCount);
    //}}AFX_VIRTUAL
    afx_msg void Paint(UINT param1, LONG param2);
    afx_msg void Quit(UINT param1, LONG param2);

    // Implementation
protected:
    BOOL mPainting;

public:
    virtual ~MsGvThread();
    BOOL IsPainting(void) { return(mPainting); }
    int mPaintCount;

    // Generated message map functions
    //{{AFX_MSG(MsGvThread)
    // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
        };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGVTHREAD_H__0DCAB225_CBC7_11D0_B885_0060B01A76F2__INCLUDED_)


#endif
