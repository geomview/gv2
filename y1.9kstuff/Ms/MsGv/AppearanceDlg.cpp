// AppearanceDlg.cpp : implementation file
//

#include "stdafx.h"

//#include "MDITest.h"
#include "resource.h"

#include "AppearanceDlg.h"
#include "MgAppearance.h"
#include "MgMaterial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AppearanceDlg dialog


AppearanceDlg::AppearanceDlg(CWnd* pParent /*=NULL*/)
        : CDialog(AppearanceDlg::IDD, pParent)
{
        //{{AFX_DATA_INIT(AppearanceDlg)
                // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT
}

AppearanceDlg::AppearanceDlg(CWnd *pParent /*=NULL*/, MgAppearance *ap) : 
         CDialog(AppearanceDlg::IDD, pParent)
{
        appearance = ap;

        defaultFlag = appearance->GetFlags();
        defaultValid = appearance->GetValid();
        defaultOverride = appearance->GetOverride();
        defaultNormalScale = (float)appearance->GetNormalScale();
        defaultLineWidth = appearance->GetLineWidth();
        defaultShading = appearance->GetShading();
        appearance->GetPatchDice(defaultDice, defaultDice+1);

        Create(IDD_APPEARANCE_DLG);

        CButton *box;
        switch (defaultShading)
        {
        case MgAppearance::F_CONSTANT:
                box = (CButton *)GetDlgItem(IDC_CONSTANT);
                box->SetCheck(1);
                break;
        case MgAppearance::F_FLAT:
                box = (CButton *)GetDlgItem(IDC_FLAT);
                box->SetCheck(1);
                break;
        case MgAppearance::F_SMOOTH:
                box = (CButton *)GetDlgItem(IDC_SMOOTH);
                box->SetCheck(1);
                break;
        case MgAppearance::F_CSMOOTH:
                box = (CButton *)GetDlgItem(IDC_NO_LIGHTING);
                box->SetCheck(1);
                break;
        };

        if (defaultFlag && MgAppearance::F_FACEDRAW)
        {
                box = (CButton *)GetDlgItem(IDC_FACES);
                box->SetCheck(1);
        }
        if (defaultFlag && MgAppearance::F_EDGEDRAW)
        {
                box = (CButton *)GetDlgItem(IDC_EDGES);
                box->SetCheck(1);
        }
        if (!(defaultFlag && MgAppearance::F_NORMALDRAW))
        {
                box = (CButton *)GetDlgItem(IDC_NORMALS);
                box->SetCheck(1);
        }
        if (defaultFlag && MgAppearance::F_VECTDRAW)
        {
                box = (CButton *)GetDlgItem(IDC_VECTORS);
                box->SetCheck(1);
        }
        if (defaultShading == MgAppearance::F_CONSTANT)
        {
        }
        
        dlg = NULL;

        ShowWindow(SW_SHOW);
}

void AppearanceDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(AppearanceDlg)
                // NOTE: the ClassWizard will add DDX and DDV calls here
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AppearanceDlg, CDialog)
        //{{AFX_MSG_MAP(AppearanceDlg)
        ON_BN_CLICKED(IDC_CONSTANT, OnConstant)
        ON_BN_CLICKED(IDC_EDGES, OnEdges)
        ON_BN_CLICKED(IDC_FACES, OnFaces)
        ON_BN_CLICKED(IDC_FLAT, OnFlat)
        ON_BN_CLICKED(IDC_INHERIT_SHADING, OnInheritShading)
        ON_BN_CLICKED(IDC_INHERIT_SHOW, OnInheritShow)
        ON_BN_CLICKED(IDC_NO_LIGHTING, OnNoLighting)
        ON_BN_CLICKED(IDC_NORMALS, OnNormals)
        ON_BN_CLICKED(IDC_OVERRIDE_SHADING, OnOverrideShading)
        ON_BN_CLICKED(IDC_OVERRIDE_SHOW, OnOverrideShow)
        ON_BN_CLICKED(IDC_SHOW, OnShow)
        ON_BN_CLICKED(IDC_SMOOTH, OnSmooth)
        ON_BN_CLICKED(IDC_VECTORS, OnVectors)
        ON_WM_CTLCOLOR()
        ON_WM_DRAWITEM()
        ON_BN_CLICKED(IDC_COLOR_EDGES, OnColorEdges)
        ON_BN_CLICKED(IDC_COLOR_FACES, OnColorFaces)
        ON_BN_CLICKED(IDC_COLOR_NORMALS, OnColorNormals)
        ON_WM_DESTROY()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AppearanceDlg message handlers

void AppearanceDlg::OnConstant() 
{
        appearance->SetShading(MgAppearance::F_CONSTANT);
}

void AppearanceDlg::OnEdges() 
{
        CButton *box = (CButton *)GetDlgItem(IDC_EDGES);
        int f_edgeDraw = MgAppearance::F_EDGEDRAW;
        if (box->GetCheck() == 1)
                appearance->SetFlags(appearance->GetFlags() | f_edgeDraw);
        else 
                appearance->SetFlags((appearance->GetFlags() | f_edgeDraw) ^ f_edgeDraw);
}

void AppearanceDlg::OnFaces() 
{
        CButton *box = (CButton *)GetDlgItem(IDC_FACES);
        int f_faceDraw = MgAppearance::F_FACEDRAW;
        if (box->GetCheck() == 1)
                appearance->SetFlags(appearance->GetFlags() | f_faceDraw);
        else 
                appearance->SetFlags((appearance->GetFlags() | f_faceDraw) ^ f_faceDraw);
}

void AppearanceDlg::OnFlat() 
{
        appearance->SetShading(MgAppearance::F_FLAT);
}

void AppearanceDlg::OnInheritShading() 
{
        // TODO: Add your control notification handler code here
        
}

void AppearanceDlg::OnInheritShow() 
{
        // TODO: Add your control notification handler code here
        
}

void AppearanceDlg::OnNoLighting() 
{
        appearance->SetShading(MgAppearance::F_CSMOOTH);
}

void AppearanceDlg::OnNormals() 
{
        CButton *box = (CButton *)GetDlgItem(IDC_NORMALS);
        int f_normalDraw = MgAppearance::F_NORMALDRAW;
        if (box->GetCheck() == 1)
                appearance->SetFlags(appearance->GetFlags() | f_normalDraw);
        else 
                appearance->SetFlags((appearance->GetFlags() | f_normalDraw) ^ f_normalDraw);
}

void AppearanceDlg::OnOverrideShading() 
{
        // TODO: Add your control notification handler code here
        
}

void AppearanceDlg::OnOverrideShow() 
{
        // TODO: Add your control notification handler code here
        
}

void AppearanceDlg::OnShow() 
{
        // TODO: Add your control notification handler code here
        
}

void AppearanceDlg::OnSmooth() 
{
        appearance->SetShading(MgAppearance::F_SMOOTH);
}

void AppearanceDlg::OnVectors() 
{
        CButton *box = (CButton *)GetDlgItem(IDC_NORMALS);
        int f_vectorDraw = MgAppearance::F_VECTDRAW;
        if (box->GetCheck() == 1)
                appearance->SetFlags(appearance->GetFlags() | f_vectorDraw);
        else 
                appearance->SetFlags((appearance->GetFlags() | f_vectorDraw) ^ f_vectorDraw);
}

HBRUSH AppearanceDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
        HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
        
//      CBrush *brush = new CBrush();
//      brush->CreateSolidBrush(RGB(255, 255, 255));

        return(hbr);
}

void AppearanceDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
        CClientDC *dc = new CClientDC(CWnd::FromHandle(lpDrawItemStruct->hwndItem));
        CWnd *button = CWnd::FromHandle(lpDrawItemStruct->hwndItem);
        CRect rect(lpDrawItemStruct->rcItem);
        MgRGB *color;

        if (lpDrawItemStruct->hDC == NULL)
                return;

        if (dc == NULL)
        {
                CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
                return;
        }

        switch (nIDCtl)
        {
        case IDC_COLOR_FACES:
                color = appearance->GetFrontMaterial()->GetDiffuse();
                break;
        case IDC_COLOR_EDGES:
                color = appearance->GetFrontMaterial()->GetEdgeColor();
                break;
        case IDC_COLOR_NORMALS:
                color = appearance->GetFrontMaterial()->GetNormalColor();
                break;
        };

        double r = color->GetRed(), g = color->GetGreen(), b = color->GetBlue();
        double h, s, l;
        RGBToHSL(r, g, b, h, s, l);
        double rLight, gLight, bLight;
        double lLight = .75 + l / 4.0;
        HSLToRGB(h, s, lLight, rLight, gLight, bLight);
        double rDark, gDark, bDark;
        double lDark = l / 4.0;
        HSLToRGB(h, s, lDark, rDark, gDark, bDark);

        if (lpDrawItemStruct->itemState & ODS_SELECTED)
        {
                dc->SelectObject(new CPen(PS_SOLID, 1, RGB(0, 0, 0)));
                dc->SelectObject(new CBrush(RGB(255 * r, 255 * g, 255 * b)));
                dc->Rectangle(rect);
        }
        else
        {
                if (0) // (lpDrawItemStruct->itemState & ODS_FOCUS)
                {
                        dc->SelectObject(new CPen(PS_SOLID, 2, RGB(0, 0, 0)));
                        dc->SelectObject(new CBrush(RGB(255 * r, 255 * g, 255 * b)));
                        dc->Rectangle(rect);
                        rect.DeflateRect(1, 1);
                        dc->Draw3dRect(rect, RGB(255 * rLight, 255 * gLight, 255 * bLight), 
                                RGB(255 * rDark, 255 * gDark, 255 * bDark));
                        rect.DeflateRect(1, 1);
                        dc->Draw3dRect(rect, RGB(255 * rLight, 255 * gLight, 255 * bLight), 
                                RGB(255 * rDark, 255 * gDark, 255 * bDark));
                }
                else
                {
                        dc->SelectObject(new CPen(PS_SOLID, 1, RGB(255, 0, 0)));
                        dc->SelectObject(new CBrush(RGB(255 * r, 255 * g, 255 * b)));
                        dc->Rectangle(rect);
                        dc->Draw3dRect(rect, RGB(255 * rLight, 255 * gLight, 255 * bLight), 
                                RGB(255 * rDark, 255 * gDark, 255 * bDark));
                        rect.DeflateRect(1, 1);
                        dc->Draw3dRect(rect, RGB(255 * rLight, 255 * gLight, 255 * bLight), 
                                RGB(255 * rDark, 255 * gDark, 255 * bDark));
                }
        }

        UpdateWindow();

        CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void AppearanceDlg::OnColorEdges() 
{
        dlg = new MgColorDialog(NULL, appearance->GetFrontMaterial()->GetEdgeColor());
}

void AppearanceDlg::OnColorFaces() 
{
        dlg = new MgColorDialog(NULL, appearance->GetFrontMaterial()->GetDiffuse());
}

void AppearanceDlg::OnColorNormals() 
{
        dlg = new MgColorDialog(NULL, appearance->GetFrontMaterial()->GetNormalColor());
}

void AppearanceDlg::OnDestroy() 
{
        CDialog::OnDestroy();
        
//      if (dlg)
//              delete dlg;
}
