// MgColorDialog.cpp : implementation file
//

#include "stdafx.h"
//#include "MDITest.h"
#include "resource.h"
#include "MgColorDialog.h"
#include "MgColor.h"
#include "MgColorWindow.h"      
#include "MgColorSlider.h"
#include "MgColorChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MgColorDialog dialog

BOOL MgColorDialog::initialized = false;
MgColor MgColorDialog::CustomRGBs[22];

MgColorDialog::MgColorDialog(CWnd* pParent /*=NULL*/)
        : CDialog(MgColorDialog::IDD, pParent)
{
        //{{AFX_DATA_INIT(MgColorDialog)
                // NOTE: the ClassWizard will add member initialization here
        //}}AFX_DATA_INIT
}

MgColorDialog::MgColorDialog(CWnd *pParent, MgRGB *Color) :
        CDialog(MgColorDialog::IDD, pParent)
{
        if (!Create(IDD_COLOR_DIALOG))
        {
                MessageBox("Couldn't Create Dialog");
                PostQuitMessage(0);
        }

        color = Color;

        BeginR = color->GetRed();
        BeginG = color->GetGreen();
        BeginB = color->GetBlue();

        CurrentR = BeginR;
        CurrentB = BeginB;
        CurrentG = BeginG;

        CurrentIndex = -1;

        if (!initialized)
        {
                initializeColors();
        }

        double H, S, L;
        RGBToHSL(CurrentR, CurrentG, CurrentB, H, S, L);

        CRect rect;
        GetWindowRect(rect);
        width = rect.Width();
        height = rect.Height();

        win = new MgColorWindow(this, (int)(.331950 * width), (int)(.024331 * height), 
                                                                  (int)(.518672 * width), (int)(.608273 * height), H, S);
        slider = new MgColorSlider(this, (int)(.892116 * width), (int)(.024331 * height), 
                                                                         (int)(.082988 * width), (int)(.608273 * height), H, S, L);

        boxInitialX = (int)(.041494 * width);
        boxInitialY = (int)(.681265 * height);
        boxInitialY2 = (int)(.754258 * height);
        boxWidth = (int)(.062241 * width);
        boxHeight = (int)(.048662 * height);
        boxIncrement = (int)(.082988 * width);
        for (int i = 0; i < 11; i++)
        {
                CustomColors[2*i] = new MgColorChoice(this, boxInitialX + i * boxIncrement,
                                                boxInitialY, boxWidth, boxHeight, 2*i, CustomRGBs[2*i].GetRed(), 
                                                CustomRGBs[2*i].GetGreen(), CustomRGBs[2*i].GetBlue());
                CustomColors[2*i + 1] = new MgColorChoice(this, boxInitialX + i * boxIncrement,
                                                boxInitialY2, boxWidth, boxHeight, 2*i + 1, CustomRGBs[2*i+1].GetRed(), 
                                                CustomRGBs[2*i+1].GetGreen(), CustomRGBs[2*i+1].GetBlue());
        }       

        OnColorChanged(0, 0);
        
        UpdateWindow();
        ShowWindow(SW_SHOW);

        initialized = TRUE;
}

MgColorDialog::~MgColorDialog()
{
        delete win;
        delete slider;
        for (int i = 0; i < 22; i++)
                delete CustomColors[i];
}

void MgColorDialog::initializeColors()
{
        for (int i = 0; i < 22; i++)
        {
                CustomRGBs[i].SetRed(0);
                CustomRGBs[i].SetGreen(0);
                CustomRGBs[i].SetBlue(0);
        }
}

void MgColorDialog::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(MgColorDialog)
                // NOTE: the ClassWizard will add DDX and DDV calls here
        //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MgColorDialog, CDialog)
        //{{AFX_MSG_MAP(MgColorDialog)
        ON_WM_LBUTTONDOWN()
        ON_WM_LBUTTONUP()
        ON_WM_MOUSEMOVE()
        ON_WM_PAINT()
        ON_BN_CLICKED(IDC_OK, OnOk)
        ON_BN_CLICKED(IDC_CANCEL, OnCancel)
        //}}AFX_MSG_MAP
        ON_MESSAGE(MG_COLOR_CHANGED, OnColorChanged)
        ON_MESSAGE(MG_CUSTOM_COLOR_CLICKED, OnCustomClicked)
        ON_MESSAGE(MG_CUSTOM_COLOR_DOUBLE_CLICKED, OnCustomDoubleClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MgColorDialog message handlers

void MgColorDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
        if (CurrentIndex >= 0)
        {
                CurrentIndex = -1;
                InvalidateRect(CRect(boxInitialX - 2, boxInitialY - 2, boxInitialX + 22 * boxIncrement,
                                                         boxInitialY + 2 * boxIncrement), TRUE);
        }
        CDialog::OnLButtonDown(nFlags, point);
}

void MgColorDialog::OnLButtonUp(UINT nFlags, CPoint point) 
{
        CDialog::OnLButtonUp(nFlags, point);
}

void MgColorDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
        CDialog::OnMouseMove(nFlags, point);
}

void MgColorDialog::OnPaint() 
{
        CPaintDC dc(this); // device context for painting

        dc.SelectStockObject(NULL_BRUSH);
        if (CurrentIndex >= 0)
        {
                int Xind = CurrentIndex / 2;
                if (CurrentIndex % 2 == 0)
                {
                        dc.Rectangle(boxInitialX + Xind * boxIncrement - 2, boxInitialY - 2,
                                                 boxInitialX + Xind * boxIncrement + boxWidth,
                                                 boxInitialY + boxHeight);
                }
                else
                {
                        dc.Rectangle(boxInitialX + Xind * boxIncrement - 2, boxInitialY2 - 2,
                                                 boxInitialX + Xind * boxIncrement + boxWidth,
                                                 boxInitialY2 + boxHeight);
                }
        }
}

void MgColorDialog::OnOk() 
{
        ShowWindow(SW_HIDE);
        win->DestroyWindow();
        slider->DestroyWindow();
        DestroyWindow();
        delete this;
}

void MgColorDialog::OnCancel() 
{
        color->SetRed(BeginR);
        color->SetGreen(BeginG);
        color->SetBlue(BeginB);

        ShowWindow(
                SW_HIDE);
        DestroyWindow();
        delete this;
}

LONG MgColorDialog::OnColorChanged(UINT param1, LONG param2)
{
        double H = win->GetH();
        double S = win->GetS();
        double L = slider->GetL();

        HSLToRGB(H, S, L, CurrentR, CurrentG, CurrentB);

        slider->SetH(H);
        slider->SetS(S);
        color->SetRed(CurrentR);
        color->SetGreen(CurrentG);
        color->SetBlue(CurrentB);

        char text[20];
        CEdit *edit;
        edit = (CEdit *)GetDlgItem(IDC_RED);
        sprintf(text, "%1.2lf", CurrentR);
        edit->SetWindowText(text);
        edit->UpdateWindow();

        edit = (CEdit *)GetDlgItem(IDC_GREEN);
        sprintf(text, "%1.2lf", CurrentG);
        edit->SetWindowText(text);
        edit->UpdateWindow();

        edit = (CEdit *)GetDlgItem(IDC_BLUE);
        sprintf(text, "%1.2lf", CurrentB);
        edit->SetWindowText(text);
        edit->UpdateWindow();

        edit = (CEdit *)GetDlgItem(IDC_HUE);
        sprintf(text, "%1.2lf", H);
        edit->SetWindowText(text);
        edit->UpdateWindow();

        edit = (CEdit *)GetDlgItem(IDC_SATURATION);
        sprintf(text, "%1.2lf", S);
        edit->SetWindowText(text);
        edit->UpdateWindow();

        edit = (CEdit *)GetDlgItem(IDC_LUMINOCITY);
        sprintf(text, "%1.2lf", L);
        edit->SetWindowText(text);
        edit->UpdateWindow();

        if (CurrentIndex >= 0)
        {
                CustomColors[CurrentIndex]->SetRGB(CurrentR, CurrentG, CurrentB);
                CustomRGBs[CurrentIndex].SetRed(CurrentR);
                CustomRGBs[CurrentIndex].SetGreen(CurrentG);
                CustomRGBs[CurrentIndex].SetBlue(CurrentB);
        }

        return(1);
}

LONG MgColorDialog::OnCustomClicked(UINT param1, LONG param2)
{
        CurrentIndex = param1;
        InvalidateRect(CRect(boxInitialX - 2, boxInitialY - 2, boxInitialX + 22 * boxIncrement,
                                                 boxInitialY + 2 * boxIncrement), TRUE);
        UpdateWindow();
        return(1);
}

LONG MgColorDialog::OnCustomDoubleClicked(UINT param1, LONG param2)
{
        CurrentIndex = param1;
        CurrentR = CustomRGBs[CurrentIndex].GetRed();
        CurrentG = CustomRGBs[CurrentIndex].GetGreen();
        CurrentB = CustomRGBs[CurrentIndex].GetBlue();

        color->SetRed(CurrentR);
        color->SetGreen(CurrentG);
        color->SetBlue(CurrentB);

        double H, S, L;
        RGBToHSL(CurrentR, CurrentG, CurrentB, H, S, L);
        win->CurrentH = H;
        win->CurrentS = S;      
        win->InvalidateRect(NULL, FALSE);
        win->UpdateWindow();
        slider->CurrentH = H;
        slider->SetS(S);
        slider->CurrentL = L;
        slider->InvalidateRect(NULL, FALSE);
        slider->UpdateWindow();
        return(1);
}
