#include <string.h>
#include "MgWindow.h"

MgWindow::MgWindow()
{
  Init();
}

// mbp-purify:  changed this function (completed it)
void MgWindow::Init()
{
  mPreferredPosition.Zero();
  mCurrentPosition.Zero();
  mViewport.Zero();
  mPreferredXSize = 0;
  mPreferredYSize = 0;
  mBufferMode = DOUBLEBUFFER;
  mBorder = 0;
  mPixelAspect = 1.0;
  mpTitle = NULL;
  mChangedBits = mSetBits = 0;
}

MgWindow::~MgWindow()
{
  if (mpTitle) { delete mpTitle; }
  Destroy();
}

//------------------------------------------------------------------------

void MgWindow::SetPreferredPosition(Position pos)
{
  SetBit(F_PREFERRED_POSITION);
  mPreferredPosition = pos;
}


int MgWindow::GetPreferredPosition(Position *pos)
{
  if (!GetBit(F_PREFERRED_POSITION)) return 0;
  *pos = mPreferredPosition;
  return 1;
}

void MgWindow::UnsetPreferredPosition()
{
  ClearBit(F_PREFERRED_POSITION);
}

//------------------------------------------------------------------------

void MgWindow::SetPreferredSize(int x, int y)
{
  SetBit(F_PREFERRED_SIZE);
  mPreferredXSize = x;
  mPreferredYSize = y;
}

int MgWindow::GetPreferredSize(int *x, int *y)
{
  if (!GetBit(F_PREFERRED_SIZE)) return 0;
  *x = mPreferredXSize;
  *y = mPreferredYSize;
  return 1;
}

void MgWindow::UnsetPreferredSize()
{
  ClearBit(F_PREFERRED_SIZE);
}

//------------------------------------------------------------------------

void MgWindow::SetCurrentPosition(Position pos)
{
  SetBit(F_CURRENT_POSITION);
  mCurrentPosition = pos;
}


int MgWindow::GetCurrentPosition(Position *pos)
{
  if (!GetBit(F_CURRENT_POSITION)) return 0;
  *pos = mCurrentPosition;
  return 1;
}

void MgWindow::UnsetCurrentPosition()
{
  ClearBit(F_CURRENT_POSITION);
}

//------------------------------------------------------------------------

void MgWindow::SetViewport(Position pos)
{
  SetBit(F_VIEWPORT);
  mViewport = pos;
}


int MgWindow::GetViewport(Position *pos)
{
  if(!GetBit(F_VIEWPORT)) {
    // Fill in viewport structure with something reasonable
    mViewport.p_XMin = 0;  mViewport.p_YMin = 0;
    if(GetBit(F_CURRENT_POSITION)) {
      mViewport.p_XMax = mCurrentPosition.p_XMax - mCurrentPosition.p_XMin + 1;
      mViewport.p_YMax = mCurrentPosition.p_YMax - mCurrentPosition.p_YMin + 1;
    } else if (GetBit(F_PREFERRED_SIZE)) {
      mViewport.p_XMax = mPreferredXSize;
      mViewport.p_YMax = mPreferredYSize;
    } else {
      mViewport.p_XMax =
        mPreferredPosition.p_XMax - mPreferredPosition.p_XMin + 1;
      mViewport.p_YMax =
        mPreferredPosition.p_YMax - mPreferredPosition.p_YMin + 1;
    }
  }
  *pos = mViewport;
  return GetBit(F_VIEWPORT);
}

void MgWindow::UnsetViewport()
{
  ClearBit(F_VIEWPORT);
}

//------------------------------------------------------------------------

void MgWindow::SetTitle(char *title)
{
  SetBit(F_TITLE);
  if (mpTitle) delete mpTitle;
  mpTitle = new char[strlen(title)+1];
  strcpy(mpTitle, title);
}

int MgWindow::GetTitle(char **title)
{
  if (!GetBit(F_TITLE)) { return 0; }
  *title = mpTitle;
  return 1;
}

void MgWindow::UnsetTitle()
{
  ClearBit(F_TITLE);
  if (mpTitle) delete mpTitle;
  mpTitle = NULL;
}

//------------------------------------------------------------------------

void MgWindow::SetBufferMode(BufferMode mode)
{
  SetBit(F_BUFFERMODE);
  mBufferMode = mode;
}

int MgWindow::GetBufferMode(BufferMode *mode)
{
  if (!GetBit(F_BUFFERMODE)) { return 0; }
  *mode = mBufferMode;
  return 1;
}

void MgWindow::UnsetBufferMode()
{
  ClearBit(F_BUFFERMODE);
}

//------------------------------------------------------------------------

void MgWindow::SetBorder(int onoff)
{
  SetBit(F_BORDER);
  mBorder = onoff;
}

int MgWindow::GetBorder(int *onoff)
{
  if (!GetBit(F_BORDER)) { return 0; }
  *onoff = mBorder;
  return 1;
}

void MgWindow::UnsetBorder()
{
  ClearBit(F_BORDER);
}

//------------------------------------------------------------------------

double MgWindow::GetAspect()
{
  double aspect =  (mCurrentPosition.p_YMax != mCurrentPosition.p_YMin) ? 
    (  (double)(mCurrentPosition.p_XMax - mCurrentPosition.p_XMin)
     / (double)(mCurrentPosition.p_YMax - mCurrentPosition.p_YMin))
    : 1.0;
  return mPixelAspect * aspect;
}

//------------------------------------------------------------------------

void MgWindow::SetPixelAspect(double a)
{
  mPixelAspect = a;
}

int MgWindow::GetPixelAspect(double *a)
{
  *a = mPixelAspect;
  return 1;
}

//------------------------------------------------------------------------

void MgWindow::Show()
{
  // Device-specific subclasses will override this
}

void MgWindow::MakeCurrent()
{
  // Device-specific subclasses will override this
}

void MgWindow::SwapBuffers()
{
  // Device-specific subclasses will override this
}

void MgWindow::Destroy()
{
  // Device-specific subclasses will override this
}

//------------------------------------------------------------------------

#if 0

// Are we really using this??

void MgWindow::Merge(register MgWindow *src)
{
  int chg;
  int mask = 0;

  if(src == NULL) return;

  chg = src->p_changed;

  mFlag = (mFlag & ~chg) | (src->mFlag & chg);
  this->p_changed |= chg;

  if(chg & F_HASPREF) this->pref = src->pref;
  if(chg & F_HASCUR) this->cur = src->cur, this->aspect = src->aspect;
  if(chg & F_HASSIZE) {
    this->xsize = src->xsize;
    this->ysize = src->ysize;
    /* If "size" is Set and not cur/pref/vp, invalidate those. */
    mFlag &= ~((F_HASCUR|F_HASPREF|F_HASVP) & ~chg);
  }
  if(chg & F_HASVP) this->viewport = src->viewport;
  if(chg & src->mFlag & F_HASNAME) SetName(src->win_name);
  if(chg & F_HASPIXASPECT) this->pixaspect = src->pixaspect;
}

#endif
