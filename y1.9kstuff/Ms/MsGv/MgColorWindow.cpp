// MgColorWindow.cpp : implementation file
//

#include <math.h>
#include "stdafx.h"
//#include "MDITest.h"
#include "resource.h"
#include "AppearanceDlg.h"
#include "MgColorDialog.h"
#include "MgColorWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void RGBToHSL(double r, double g, double b, double &H, double &S, double &L)
{
	double v, m, vm, r2, g2, b2;

	v = max(max(r, g), b);
	m = min(min(r, g), b);

	L = (m+v)/2;

	if ( (S = vm = v-m) > 0.0) 
	{
		S /= (L <= 0.5) ? (v + m) : (2.0 - v - m);
	}
	else
	{
		H = 0.0;
		return;
	}
	r2 = (v - r) / vm;
	g2 = (v - g) / vm;
	b2 = (v - b) / vm;

	if (r == v)
		H = (g == m ? 5.0 + b2 : 1.0 - g2);
	else if (g == v)
		H = (b == m ? 1.0 + r2 : 3.0 - b2);
	else
		H = (r == m ? 3.0 + g2 : 5.0 - r2);

	H /= 6;
}

void HSLToRGB(double h, double s, double l, double &R, double &G, double &B)
{
	double v;

	v = (l <= 0.5) ? (l * (1.0 + s)) : (l + s - l*s);

	if (v <= 0)
	{
		R = G = B = 0.0;
	}
	else
	{
		double m, sv, fract, vsf, mid1, mid2;
		int sextant;

		m = l + l - v;
		sv = (v - m) / v;
		h *= 6.0;
		sextant = (int)h;
		fract = h - sextant;
		vsf = v * sv * fract;
		mid1 = m + vsf;
		mid2 = v - vsf;
		switch (sextant)
		{
		case 0: 
			R = v; G = mid1; B = m;
			break;
		case 1:
			R = mid2; G = v; B = m;
			break;
		case 2:
			R = m; G = v; B = mid1;
			break;
		case 3:
			R = m; G = mid2; B = v;
			break;
		case 4:
			R = mid1; G = m; B = v; 
			break;
		case 5:
			R = v; G = m; B = mid2;
			break;
		}
	}
}

void MyHSLToRGB(double H, double S, double L, double &R, double &G, double &B)
{
// GetBaseColor -- Only uses H

	R = max(min(fabs(H - .5) - 1, 1.0), 0.0);
	G = max(min(-fabs(H - .333333333333333333333) + 2, 1.0), 0.0);
	B = max(min(-fabs(H - .666666666666666666666) + 2, 1.0), 0.0);

// Now Apply Saturation
	R = (R - .5)*S + .5;
	G = (G - .5)*S + .5;
	B = (B - .5)*S + .5;

// Now Hue
	if (R < .5)
		R = 2.0*R*L;
	else
		R = 2.0*(1.0 - R)*(L - .5) + R;

	if (G < .5)
		G = 2.0*G*L;
	else
		G = 2.0*(1.0 - G)*(L - .5) + G;

	if (B < .5)
		B = 2.0*B*L;
	else
		B = 2.0*(1.0 - B)*(L - .5) + R;
}

/////////////////////////////////////////////////////////////////////////////
// MgColorWindow

int MgColorWindow::redDepth = 0;
int MgColorWindow::greenDepth = 0;
int MgColorWindow::blueDepth = 0;

MgColorWindow::MgColorWindow()
{
}

MgColorWindow::MgColorWindow(CWnd *Parent, int xloc, int yloc, int Width, int Height,
							 double currentH, double currentS)
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
		MessageBox("Can't Open Color Window!");
		delete this;
	}

	CurrentH = currentH; CurrentS = currentS;

	lButtonDown = FALSE;
	SetupBitmap();

	ShowWindow(SW_SHOW);
	UpdateWindow();
}

MgColorWindow::~MgColorWindow()
{
}


BEGIN_MESSAGE_MAP(MgColorWindow, CWnd)
	//{{AFX_MSG_MAP(MgColorWindow)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MgColorWindow message handlers

void MgColorWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.BitBlt(1, 1, width - 2, height - 2, &cdc, 1, 1, SRCCOPY);

	DrawPointer(&dc);

	DrawBorder(&dc);
}

void MgColorWindow::DrawBorder(CDC *dc)
{
	dc->SelectObject(GetStockObject(WHITE_PEN));
	dc->MoveTo(0, height-1);
	dc->LineTo(width-1, height-1);
	dc->LineTo(width-1, 0);

	dc->SelectObject(GetStockObject(BLACK_PEN));
	dc->MoveTo(width, 0);
	dc->LineTo(0, 0);
	dc->LineTo(0, height);

	dc->SelectObject(GetStockObject(WHITE_PEN));
	dc->MoveTo(0, height-1);
	dc->LineTo(width-1, height-1);
	dc->LineTo(width-1, 0);

	dc->SelectObject(GetStockObject(BLACK_PEN));
	dc->MoveTo(width, 0);
	dc->LineTo(0, 0);
	dc->LineTo(0, height);
}

void MgColorWindow::DrawPointer(CDC *dc)
{
	int x = (int)min(max(CurrentH * width, 1), width - 1);
	int y = (int)min(max(CurrentS * height, 1), height - 1);
	y = height - y;

	dc->SelectObject(GetStockObject(BLACK_BRUSH));
	dc->SelectObject(GetStockObject(BLACK_PEN));
	dc->Rectangle(x - 1, y - 10, x + 1, y - 5);
	dc->Rectangle(x - 1, y + 10, x + 1, y + 5);
	dc->Rectangle(x - 10, y - 1, x - 5, y + 1);
	dc->Rectangle(x + 10, y - 1, x + 5, y + 1);
}

void MgColorWindow::SetupBitmap(void)
{
	int size;
	BYTE *byteArray;
	int depth;
	CDC *dc = new CClientDC(this);

	if (!cdc.CreateCompatibleDC(dc))
		MessageBox("Couldn't Create Color Window Device Context");
	if (!bitmap.CreateCompatibleBitmap(dc, width, height))
		MessageBox("Couldn't Create Bitmap");
	if (!cdc.SelectObject(bitmap))
		MessageBox("Couldn't Select Bitmap Into Device Context");

	bits = dc->GetDeviceCaps(BITSPIXEL);

	if (bits == 8)
	{
		CBrush brush;
		CPen pen;
		double R, G, B;
		double H, S;
		double L = .5;

		for (int i = 0; i < width; i += 1)
		{
			for (int j = 0; j < height; j += 1)
			{
				H = (double)i / width;
				S = (height - (double)j) / height;

				HSLToRGB(H, S, L, R, G, B);
				R *= 255; G *= 255; B *= 255;
//				pen.DeleteObject();
//				brush.DeleteObject();
//				pen.CreatePen(PS_SOLID, 0, RGB(R, G, B));
//				brush.CreateSolidBrush(RGB(R, G, B));
//				cdc.SelectObject(pen);
//				cdc.SelectObject(brush);
//				cdc.Rectangle(i, j, i+3, j+3);
				cdc.SetPixel(i, j, RGB(R, G, B));
			}
		}
		return;
	}
	else if (bits == 16)
	{
		byteArray = new BYTE[width*height*2 + 8];
		size = 2;
		depth = 5;
	}
	else if (bits == 24) 
	{
		byteArray = new BYTE[width*height*4];
		size = 4;
		depth = 8;
	}
	else if (bits == 32)
	{
		byteArray = new BYTE[width*height*4];
		size = 4;
		depth = 8;
	}

	if (redDepth == 0)
	{
		CDC *dc = new CClientDC(this);

		BYTE *bytes = new BYTE[size*width*height];

		if (bits == 16)
		{
			int i = 0;
			for (i = 1; i <= 8; i++)
			{
				cdc.SetPixel(0, 0, RGB(i, 0, 0)); 
				cdc.SetPixel(1, 0, RGB(0, i, 0)); 
				cdc.SetPixel(2, 0, RGB(0, 0, i)); 

				bitmap.GetBitmapBits(size*width*height, bytes);

				redDepth = *((short *)bytes);
				greenDepth = *((short *)bytes + 1);
				blueDepth = *((short *)bytes + 2);
				if (redDepth > 0) 
					break;
			}												
		}
		else
		{
			cdc.SetPixel(0, 0, RGB(1, 0, 0));
			cdc.SetPixel(1, 0, RGB(0, 1, 0));
			cdc.SetPixel(2, 0, RGB(0, 0, 1));
												
			bitmap.GetBitmapBits(size*width*height, bytes);

			redDepth = *((int *)bytes + 2);
			greenDepth = *((int *)bytes + 1);
			blueDepth = *((int *)bytes);
		}
		delete bytes;
	}

	double colMax = pow(2, depth) - 1;
	double r = colMax, g = 0.0, b = 0.0;
	double bandWidth = (double)(width) / 6;
	double xinc = colMax / bandWidth;

	for (int i = 0; i < width; i++)
	{
		r = min(r, colMax);
		r = max(r, 0.0);
		g = min(g, colMax);
		g = max(g, 0.0);
		b = min(b, colMax);
		b = max(b, 0.0);

		double ryinc = (colMax/2 - r) / (double)height;
		double gyinc = (colMax/2 - g) / (double)height;
		double byinc = (colMax/2 - b) / (double)height;
		double tmpr = r;
		double tmpg = g;
		double tmpb = b;
		for (int j = 0; j < height; j++)
		{
			int *value = (int *)(byteArray + size*(width*j + i));

			int rvalue = (int)tmpr;
			int gvalue = (int)tmpg;
			int bvalue = (int)tmpb;

			if (bits == 32)
			{
				int tmp = rvalue;
				rvalue = bvalue;
				bvalue = tmp;
			}

			rvalue *= redDepth;
			bvalue *= blueDepth; 
			gvalue *= greenDepth; 

			*value = bvalue + gvalue + rvalue;

			tmpr += ryinc;
			tmpg += gyinc;
			tmpb += byinc;
		} 

		if (i < bandWidth)
			g += xinc;
		else if (i < 2*bandWidth)
			r -= xinc;
		else if (i < 3*bandWidth)
			b += xinc;
		else if (i < 4*bandWidth)
			g -= xinc;
		else if (i < 5*bandWidth)
			r += xinc;
		else
			b -= xinc;
	}
	bitmap.SetBitmapBits(size*width*height, byteArray);
	delete byteArray;
}

void MgColorWindow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	lButtonDown = TRUE;
	OldPointX = point.x;
	OldPointY = point.y;
	
	CDC *dc = new CClientDC(this);
	InvalidateRect(NULL, FALSE);

	parent->PostMessage(MG_COLOR_CHANGED, 0, 0);
	CWnd::OnLButtonDown(nFlags, point);
}

void MgColorWindow::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDC *dc = new CClientDC(this);

	double x = min(max(point.x, 1), width - 1);
	double y = min(max(point.y, 1), height - 1);

	CurrentH = x / width;
	CurrentS = y / height;
	CurrentS = 1.0 - CurrentS;

	InvalidateRect(NULL, FALSE);

	lButtonDown = FALSE;
	ReleaseCapture();
	parent->PostMessage(MG_COLOR_CHANGED, 0, 0);
	CWnd::OnLButtonUp(nFlags, point);
}

void MgColorWindow::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (lButtonDown)
	{
		double x = min(max(point.x, 1), width - 1);
		double y = min(max(point.y, 1), height - 1);

		int srcx = (int)(CurrentH*(width - 1) - 11);
		int srcy = height - 1 - (int)(CurrentS*(height - 1) + 11);
		CDC *dc = new CClientDC(this);
		dc->BitBlt(srcx, srcy, 22, 22, &cdc, srcx, srcy, SRCCOPY);
		CurrentH = x / width;
		CurrentS = y / height;
		CurrentS = 1.0 - CurrentS;

		DrawPointer(dc);
		DrawBorder(dc);
		delete dc;

		parent->SendMessage(MG_COLOR_CHANGED, 0, 0);
	}
	CWnd::OnMouseMove(nFlags, point);
}

void MgColorWindow::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void MgColorWindow::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
