// TreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "TreeDlg.h"

#include "Geom.h"
#include "GvPath.h"
#include "GeomWrapped.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TreeDlg dialog


TreeDlg::TreeDlg(CWnd* pParent /*=NULL*/)
        : CDialog(TreeDlg::IDD, pParent)
{
        //{{AFX_DATA_INIT(TreeDlg)
                // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT
    mpGeom = NULL;
    mpTreeCtrl = NULL;
    mpOutputBox = NULL;
    mDlgInitialized = FALSE;
    Create(IDD_TREE_DLG);
}

void TreeDlg::GetDlgItems()
{
    mpTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE1);
    mpOutputBox = (CEdit*)GetDlgItem(IDC_TREE_OUTPUT_EDIT);
}

BOOL TreeDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    GetDlgItems();
    if (mpGeom)
    {
        mpTreeCtrl->DeleteAllItems();
        InsertGeomSubTree(mpGeom, TVI_ROOT);
    }
    mDlgInitialized = TRUE;
    return TRUE;
}

BOOL TreeDlg::ComputePath(GvPath *path,
                          HTREEITEM hCurrentItem,
                          HTREEITEM hItemInQuestion)
{
    GetDlgItems();
    if (hCurrentItem == hItemInQuestion) return TRUE;

    if (mpTreeCtrl->ItemHasChildren(hCurrentItem))
    {
        int n = 0;
        HTREEITEM hChild = mpTreeCtrl->GetChildItem(hCurrentItem);
        while (hChild != NULL)
        {
            path->AppendIndex(n);
            if (ComputePath(path, hChild, hItemInQuestion))
                return TRUE;
            path->RemoveLastIndex();
            ++n;
            hChild = mpTreeCtrl->GetNextSiblingItem(hChild);
        }
    }
    return FALSE;
}


GvPath *TreeDlg::PathOfItem(HTREEITEM hItemInQuestion)
{
    GetDlgItems();

    GvPath *path = new GvPath();
    path->SetRoot(mpGeom);
    if (hItemInQuestion == TVI_ROOT) return path;

    HTREEITEM hTreeRootItem = mpTreeCtrl->GetRootItem();

    if (ComputePath(path, hTreeRootItem, hItemInQuestion))
        return path;
    else
        return NULL;
}


void TreeDlg::SetGeomTree(Geom *g)
{
    GetDlgItems();

    if (mpGeom) ::DeleteRef(mpGeom);
    if (g != NULL) mpGeom = ::NewRef(g);
    else mpGeom = NULL;

    if (mDlgInitialized)
    {
        mpTreeCtrl->DeleteAllItems();
        InsertGeomSubTree(mpGeom, TVI_ROOT);
    }
}

void TreeDlg::InsertGeomSubTree(Geom *g, HTREEITEM hParent)
{
    GetDlgItems();

    if (g != NULL) {
        HTREEITEM hItem = mpTreeCtrl->InsertItem(g->GetType()->mpName,
                                                 hParent);
        if (g->IsInstanceOf(TYPE_INFO(GeomParent))) {
            GeomParent *p = (GeomParent*)g;
            int childCount = p->GetChildCount();
            for (int i=0; i<childCount; ++i)
            {
                InsertGeomSubTree(p->GetChild(i), hItem);
            }
        }
    }
}

void TreeDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(TreeDlg)
                // NOTE: the ClassWizard will add DDX and DDV calls here
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TreeDlg, CDialog)
        //{{AFX_MSG_MAP(TreeDlg)
        ON_BN_CLICKED(IDC_TREE_COMPUTE_PATH_BUTTON, OnTreeComputePath)
        ON_BN_CLICKED(IDC_TREE_EXPAND_BUTTON, OnTreeExpand)
        ON_BN_CLICKED(IDC_TREE_GET_TRANSFORM_BUTTON, OnTreeGetTransform)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void TreeDlg::AppendOutputText(const char *text)
{
    mpOutputBox->SetSel(-1, -1);
    mpOutputBox->ReplaceSel(text);
}

void TreeDlg::ClearOutputText()
{
    mpOutputBox->SetSel(0, -1);
    mpOutputBox->SetReadOnly(FALSE);
    mpOutputBox->Clear();
    mpOutputBox->SetReadOnly(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// TreeDlg message handlers

void TreeDlg::OnTreeComputePath() 
{
    GetDlgItems();
    ClearOutputText();

    HTREEITEM hSelectedItem = mpTreeCtrl->GetSelectedItem();
    if (hSelectedItem == NULL)
        AppendOutputText("No item is selected");
    else
    {
        GvPath *selectedItemPath = PathOfItem(hSelectedItem);
        if (selectedItemPath == NULL)
            AppendOutputText("[PathOfItem(...) returned NULL");
        else
        {
            UtScalarArray<int> *indexArray = selectedItemPath->GetIndexArray();
            int count = selectedItemPath->GetIndexCount();
            AppendOutputText("Selected ");
            Geom *g = selectedItemPath->Resolve();
            AppendOutputText(g->GetType()->mpName);
            AppendOutputText(" at path");
            char buf[20];
            for (int i=0; i<count; ++i) {
                sprintf(buf, " %d", (*indexArray)[i]);
                AppendOutputText(buf);
            }
        }
    }
}

void TreeDlg::RecursiveExpand(HTREEITEM hItem)
{
    GetDlgItems();
    mpTreeCtrl->Expand(hItem, TVE_EXPAND);
    if (mpTreeCtrl->ItemHasChildren(hItem))
    {
        HTREEITEM hChild = mpTreeCtrl->GetChildItem(hItem);
        while (hChild != NULL)
        {
            RecursiveExpand(hChild);
            hChild = mpTreeCtrl->GetNextSiblingItem(hChild);
        }
    }            
}

void TreeDlg::OnTreeExpand() 
{
    GetDlgItems();
    HTREEITEM hFirstVisible = mpTreeCtrl->GetFirstVisibleItem();
    RecursiveExpand(mpTreeCtrl->GetSelectedItem());
    if (hFirstVisible) mpTreeCtrl->SelectSetFirstVisible(hFirstVisible);
}

void TreeDlg::OnTreeGetTransform() 
{
    int i;
    char buf[80];

    GetDlgItems();
    ClearOutputText();
    HTREEITEM hSelected = mpTreeCtrl->GetSelectedItem();
    if (hSelected == NULL)
    {
        AppendOutputText("<No item selected>");
        return;
    }
    GvPath *path = PathOfItem(hSelected);
    //Transform3 *T = path->GetLocalTransform();
    Transform3 M, *T = &M;
    path->GetCumulativeTransform(T);
    if (T == NULL)
    {
        AppendOutputText("path->GetLocalTransform() returned NULL");
        return;
    }

    UtScalarArray<int> *indexArray = path->GetIndexArray();
    int count = path->GetIndexCount();
    AppendOutputText("Transform for path ");
    for (i=0; i<count; ++i) {
        sprintf(buf, " %d", (*indexArray)[i]);
        AppendOutputText(buf);
    }
    AppendOutputText(" is\r\n");
    for (i=0; i<4; ++i) {
        sprintf(buf, "%7.3f  %7.3f  %7.3f  %7.3f",
                T->D.M[i][0],   T->D.M[i][1],
                T->D.M[i][2],   T->D.M[i][3]);
        AppendOutputText(buf);
        if (i<3) AppendOutputText("\r\n");
    }
}

