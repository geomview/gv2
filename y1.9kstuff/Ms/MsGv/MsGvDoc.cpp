// MsGvDoc.cpp : implementation of the CMsGvDoc class
//
    
#include "stdafx.h"
#include "mmsystem.h"
#include "MsGv.h"
#include "GeomOff.h"
#include "GeomMesh.h"
#include "GeomList.h"
    
#include "MsGvDoc.h"
#include "MsGvView.h"
//#include "GeomOldOoglParser.h"
    
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
    
/////////////////////////////////////////////////////////////////////////////
// CMsGvDoc  
    
IMPLEMENT_DYNCREATE(CMsGvDoc, CDocument)
    
BEGIN_MESSAGE_MAP(CMsGvDoc, CDocument)
    //{{AFX_MSG_MAP(CMsGvDoc)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
    
/////////////////////////////////////////////////////////////////////////////
// CMsGvDoc construction/destruction
    
CMsGvDoc::CMsGvDoc()
{
    m_bAutoDelete = TRUE;
    
    extern CMsGvApp theApp;
    theApp.AddWorld(this);
    
    p_mOldTime = p_mCurTime = timeGetTime();
    p_mElapsedTime = 0;
    p_mFramesPerSecond = 0.0;
    p_mFrameCount = 0;
    p_mDrawTime = 0;
}
    
CMsGvDoc::~CMsGvDoc()
{
    extern CMsGvApp theApp;
    theApp.RemoveWorld(this);
}
    
BOOL CMsGvDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    return TRUE;
}
    
/////////////////////////////////////////////////////////////////////////////
// CMsGvDoc diagnostics
    
#ifdef _DEBUG
void CMsGvDoc::AssertValid() const
{
    CDocument::AssertValid();
}
    
void CMsGvDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG
    
/////////////////////////////////////////////////////////////////////////////
// CMsGvDoc commands
    
BOOL CMsGvDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    // if (!CDocument::OnOpenDocument(lpszPathName))
    //   return FALSE;
    
    IoOldOoglLexer lex;
    if (!lex.Open(lpszPathName)) return FALSE;
    Geom *g = GeomOldOoglParser::Load(&lex);
    if (g == NULL) return FALSE;

    AddGeometry(g);
    ::DeleteRef(g);

    return TRUE;
}
    

void CMsGvDoc::UpdateAll()
{
    CMsGvView *curView;
    POSITION position;


    position = GetFirstViewPosition();
    while (position != NULL)
    {
        curView = (CMsGvView *)(GetNextView(position));
        curView->UpdateScene();
    }
}

#if 0    
void CMsGvDoc::DrawScene(MgContext *mg)
{
    p_mCurTime = timeGetTime();
    p_mElapsedTime = p_mCurTime - p_mOldTime;
    p_mOldTime = p_mCurTime;
    
    double tmpFramesPerSecond = 1000.0 / p_mElapsedTime;
    if (p_mElapsedTime > 0)
        p_mFramesPerSecond = (p_mFrameCount * p_mFramesPerSecond
                               + tmpFramesPerSecond) / (p_mFrameCount + 1);
    
    p_mCurTime = timeGetTime();

    mg->WorldBegin();
    mWorld.Draw(mg);
    mg->WorldEnd();
    
    unsigned long tmpDrawTime = timeGetTime() - p_mCurTime;
    if (tmpDrawTime != 0)
        p_mDrawTime = (p_mFrameCount * p_mDrawTime + tmpDrawTime)
                         / (p_mFrameCount + 1);
    
    p_mFrameCount++;
}
#endif // 0

void CMsGvDoc::DeleteContents() 
{
    // TODO: Add your specialized code here and/or call the base class
    CDocument::DeleteContents();
}
