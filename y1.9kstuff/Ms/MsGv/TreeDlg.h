//-*-C++-*-
#if !defined(AFX_TREEDLG_H__C5516A67_5B80_11D1_9999_00C04FB616FB__INCLUDED_)
#define AFX_TREEDLG_H__C5516A67_5B80_11D1_9999_00C04FB616FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TreeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TreeDlg dialog

class TreeDlg : public CDialog
{
    // Construction
public:
    TreeDlg(CWnd* pParent = NULL);   // standard constructor

    void SetGeomTree(class Geom *g);
    void Show() { ShowWindow(SW_SHOW); }
    class GvPath *PathOfItem(HTREEITEM hItem);

    // Dialog Data
    //{{AFX_DATA(TreeDlg)
    enum { IDD = IDD_TREE_DLG };
    // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(TreeDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    virtual BOOL OnInitDialog();                
    Geom *mpGeom;

private:
    CTreeCtrl *mpTreeCtrl;
    CEdit *mpOutputBox;
    BOOL mDlgInitialized;
    void InsertGeomSubTree(class Geom *g, HTREEITEM hParent);
    BOOL TreeDlg::ComputePath(class GvPath *path,
                              HTREEITEM hCurrentItem,
                              HTREEITEM hItemInQuestion);
    void AppendOutputText(const char *text);
    void ClearOutputText();

    void GetDlgItems();
    void RecursiveExpand(HTREEITEM hItem);


    // Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(TreeDlg)
        afx_msg void OnTreeComputePath();
        afx_msg void OnTreeExpand();
        afx_msg void OnTreeGetTransform();
        //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
        };


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEDLG_H__C5516A67_5B80_11D1_9999_00C04FB616FB__INCLUDED_)
