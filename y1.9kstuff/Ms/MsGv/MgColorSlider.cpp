// MgColorSlider.cpp : implementation file
//

#include "stdafx.h"
//#include "MDITest.h"
#include "resource.h"
#include "AppearanceDlg.h"
#include "MgColorDialog.h"
#include "MgColorSlider.h"
#include "MgColorWindow.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MgColorSlider

MgColorSlider::MgColorSlider()
{
}

MgColorSlider::MgColorSlider(CWnd *Parent, int xloc, int yloc, int Width, int Height, 
							 double currentH, double currentS, double currentL)
{
	CString WindowClass;
	BOOL result;

	parent = Parent;

	width = Width;
	height = Height;
	
	WindowClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH), 
		NULL);

	result = Create(WindowClass, NULL, WS_CHILD, CRect(xloc, yloc, xloc + width, 
					yloc + height), parent, NULL);

	if (result == NULL)
	{
		MessageBox("Can't Open Color Slider!");
		delete this;
	}

	CurrentH = currentH;
	CurrentS = currentS;
	CurrentL = currentL;

	CDC *dc = new CClientDC(this);

	bits = dc->GetDeviceCaps(BITSPIXEL);

	bitmap.CreateCompatibleBitmap(dc, width / 2 - 1, height - 1);
	cdc.CreateCompatibleDC(dc);
	cdc.SelectObject(bitmap);
	SetupBitmap();

	MouseDown = FALSE;

	ShowWindow(SW_SHOW);
	UpdateWindow();
	delete dc;
}

MgColorSlider::~MgColorSlider()
{
}

void MgColorSlider::SetupBitmap()
{		
	double H = CurrentH, S = CurrentS, L = 1.0;
	double R, G, B;
	double Linc = 1.0 / (height - 2);
	CPen pen; 

	for (int i = 0; i < height-1; i++, L -= Linc)
	{
		HSLToRGB(H, S, L, R, G, B);
		R *= 255; G *= 255; B *= 255;
		pen.DeleteObject();
		pen.CreatePen(PS_SOLID, 0, RGB(R, G, B));
		cdc.SelectObject(pen);
		cdc.MoveTo(0, i);
		cdc.LineTo(width/2, i);
	}
}

BEGIN_MESSAGE_MAP(MgColorSlider, CWnd)
	//{{AFX_MSG_MAP(MgColorSlider)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MgColorSlider message handlers

void MgColorSlider::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

void MgColorSlider::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	CurrentL = 1.0 - (double)point.y / (height - 1);
	CurrentL = min(max(CurrentL, 0.0), 1.0);
	MouseDown = TRUE;
	InvalidateRect(NULL, FALSE);
	parent->PostMessage(MG_COLOR_CHANGED, 0, 0);
	CWnd::OnLButtonDown(nFlags, point);
}

void MgColorSlider::OnLButtonUp(UINT nFlags, CPoint point) 
{
	MouseDown = FALSE;
	CurrentL = 1.0 - (double)point.y / (height - 1);
	CurrentL = min(max(CurrentL, 0.0), 1.0);
	ReleaseCapture();
	InvalidateRect(NULL, FALSE);
	parent->PostMessage(MG_COLOR_CHANGED, 0, 0);
	CWnd::OnLButtonUp(nFlags, point);
}

void MgColorSlider::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (MouseDown)
	{
		CurrentL = 1.0 - (double)point.y / (height - 1);
		CurrentL = min(max(CurrentL, 0.0), 1.0);

		CPen pen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE));
		CBrush brush(GetSysColor(COLOR_3DFACE));

		CClientDC dc(this);
		dc.SelectObject(&pen);
		dc.SelectObject(&brush);
		dc.Rectangle(width/2, 0, width, height);

		dc.SelectObject(GetStockObject(BLACK_PEN));
		dc.MoveTo(width/2 - 1, 0);
		dc.LineTo(0, 0);
		dc.LineTo(0, height - 1);

		dc.SelectObject(GetStockObject(WHITE_PEN));
		dc.LineTo(width/2 - 1, height-1);
		dc.LineTo(width/2 - 1, 0);

		double tmpHeight = (1.0 - CurrentL) * (height - 1);
		tmpHeight = max(min(tmpHeight, height - 2), 1);

		POINT points[3];
		points[0].x = width/2 + 1;
		points[0].y = (int)(tmpHeight);
		points[1].x = (int)(3.0 * width / 4);
		points[1].y = (int)(tmpHeight - width / 8);
		points[2].x = points[1].x;
		points[2].y = (int)(tmpHeight + width / 8);

		dc.SelectObject(GetStockObject(BLACK_BRUSH));
		dc.Polygon(points, 3);

		CWnd::OnMouseMove(nFlags, point);
		parent->PostMessage(MG_COLOR_CHANGED, 0, 0);
	}
}

void MgColorSlider::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
					   
	CPen pen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE));
	CBrush brush(GetSysColor(COLOR_3DFACE));

	dc.SelectObject(&pen);
	dc.SelectObject(&brush);
	dc.Rectangle(width/2, 0, width, height);

	dc.SelectObject(GetStockObject(BLACK_PEN));
	dc.MoveTo(width/2 - 1, 0);
	dc.LineTo(0, 0);
	dc.LineTo(0, height - 1);

	dc.SelectObject(GetStockObject(WHITE_PEN));
	dc.LineTo(width/2 - 1, height-1);
	dc.LineTo(width/2 - 1, 0);

	double tmpHeight = (1.0 - CurrentL) * (height - 1);
	tmpHeight = max(min(tmpHeight, height - 2), 1);

	POINT points[3];
	points[0].x = width/2 + 1;
	points[0].y = (int)(tmpHeight);
	points[1].x = (int)(3.0 * width / 4);
	points[1].y = (int)(tmpHeight - width / 8);
	points[2].x = points[1].x;
	points[2].y = (int)(tmpHeight + width / 8);

	dc.SelectObject(GetStockObject(BLACK_BRUSH));
	dc.Polygon(points, 3);

	dc.BitBlt(1, 1, width / 2 - 1, height - 1, &cdc, 1, 1, SRCCOPY);
}
