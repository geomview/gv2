// MgColorChoice.cpp : implementation file
//

#include "stdafx.h"
#include "mmsystem.h"
//#include "MDITest.h"
#include "resource.h"
#include "MgColorChoice.h"	 
#include "MgColorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MgColorChoice

MgColorChoice::MgColorChoice()
{
}

MgColorChoice::MgColorChoice(CWnd *Parent, int xloc, int yloc, int Width, int Height,
							 int Index, double currentR, double currentG, double currentB)
{
	CString WindowClass;
	BOOL result;

	parent = Parent;

	width = Width;
	height = Height;

	index = Index;
	
	WindowClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW,
		AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)GetStockObject(NULL_BRUSH), 
		NULL);

	result = Create(WindowClass, NULL, WS_CHILD, CRect(xloc, yloc, xloc + width, 
					yloc + height), parent, NULL);

	if (result == NULL)
	{
		MessageBox("Can't Open Color Window!");
		delete this;
	}  

	Initialized = FALSE;

	SetRGB(currentR, currentG, currentB);
	UpdateWindow();
	ShowWindow(SW_SHOW);
}

MgColorChoice::~MgColorChoice()
{
}

void MgColorChoice::SetRGB(double R, double G, double B)
{
	if (Initialized)
	{
		brush.DeleteObject();
		pen.DeleteObject();
	}

	Initialized = TRUE;

	CurrentR = R;
	CurrentG = G;
	CurrentB = B;									 

	brush.CreateSolidBrush(RGB((int)(CurrentR * 255), (int)(CurrentG * 255), (int)(CurrentB * 255)));
	pen.CreatePen(PS_SOLID, 0, RGB((int)(CurrentR * 255), (int)(CurrentG * 255), (int)(CurrentB * 255)));

	CClientDC dc(this);
	dc.Draw3dRect(0, 0, width - 1, height - 1, RGB(0, 0, 0), RGB(255, 255, 255));
	dc.SelectObject(pen);
	dc.SelectObject(brush);
	dc.Rectangle(1, 1, width - 2, height - 2);
}

BEGIN_MESSAGE_MAP(MgColorChoice, CWnd)
	//{{AFX_MSG_MAP(MgColorChoice)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MgColorChoice message handlers

void MgColorChoice::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.Draw3dRect(0, 0, width - 1, height - 1, RGB(0, 0, 0), RGB(255, 255, 255));
	dc.SelectObject(pen);
	dc.SelectObject(brush);
	dc.Rectangle(1, 1, width - 2, height - 2);
}


void MgColorChoice::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int clickTime = timeGetTime();
	
	if (clickTime - lastTime < 1000)
	{
		parent->PostMessage(MG_CUSTOM_COLOR_DOUBLE_CLICKED, index, 0);
	}
	else
		parent->PostMessage(MG_CUSTOM_COLOR_CLICKED, index, 0);	

	lastTime = clickTime;

	CWnd::OnLButtonUp(nFlags, point);
}

void MgColorChoice::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	parent->PostMessage(MG_CUSTOM_COLOR_DOUBLE_CLICKED, index, 0);
	CWnd::OnLButtonDblClk(nFlags, point);
}
