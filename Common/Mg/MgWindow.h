//-*-C++-*-
#ifndef MGWINDOW_H
#define MGWINDOW_H

#include <stdio.h>
#include "RefObject.h"

// class MgWindow
//
// The MgWindow class holds information that MG needs related to a
// window.  Each MgContext object has an associated MgWindow object,
// corresponding to that MgContext's window.  The interface for the
// MgWindow class provides a device-independent way of accessing
// window-specific information.
// 
// The MgWindow class itself is an abstraction. There are derived
// classes which correspond to specific window systems (e.g.
// MgMSWindow, MgXWindow, etc); client programs should instantiate one
// of these subclasses rather than MgWindow itself (and associate that
// subclass object with an MgContext).
// 
// When deriving a subclass from MgWindow, it is important that the
// subclass correctly maintain the information in the MgWindow class
// fields.  In the documentation below, I've tried to signal places
// which point out things that subclass authors need to do by flagging
// them with the string "SUBCLASS".  In cases where the comments say
// that you should override a function, the new implementation of the
// function should arrange to call the superclass version of it; this
// is the part that does the info bookkeeping, and it's important that
// this happen in addition to whatever subclass actions are necessary.
// 
// In the documentation related to window positions & sizes below, the
// term "close to" is used to mean "as close as physically
// possible". This arises when dealing with the differences between a
// window's requested size/position and the actual size as allowed by
// the window system, which may be different from that requested.

class MgWindow : virtual public RefObject {

public:
    MgWindow();
    virtual ~MgWindow();

    // mbp-purify: added Zero() function to this struct:
    typedef struct Position {
        int p_XMin, p_XMax, p_YMin, p_YMax;
        void Zero() { p_XMin = p_XMax = p_YMin = p_YMax = 0; }
    } Position;

    // GENERAL NOTE: the MgWindow object consists of a bunch of window-
    // related "attributes", like size, location, whether
    // double-buffering is on, etc.  To Set an attribute, call its
    // SetXXX() member function.  To get its value, call the
    // corresponding getXXX() function.  Most attributes are also
    // "unSettable", in the sense that they can have "no value"
    // associated with them (the interpretation in this case is to let
    // the underlying window system use whatever defaults make sense).
    // For these, there is a corresponding unSetXXX() function.  Also,
    // for these unSettable attributes, the default for a new window is
    // that they have no value.

  
    virtual void          SetPreferredPosition(Position pos);
    virtual int           GetPreferredPosition(Position *pos);
    virtual void          UnsetPreferredPosition();
    // Set/get the window's "preferred position" Setting.  If the
    // window isn't on the screen at the time this is Set, the Setting
    // is saved for use when the window is made visible.  If the window
    // is visible, then Setting this value results in the window
    // actually moving (close) to the new position (in window systems
    // where this is possible).
    //
    // SUBCLASS: when creating a new window, if preferred position
    // has a value, use it to determine the initial window location
    // and size (to the extent possible).  Also, override
    // SetPrefferredPosition() with a function that actually moves
    // the window on the screen, if it's visible.

    virtual void          SetPreferredSize(int x, int y);
    virtual int           GetPreferredSize(int *x, int *y);
    virtual void          UnsetPreferredSize();
    // Set/get the window's preferred size.  This is similar to the
    // preferred position but just indicates window size, not location.
    // Setting the preferred size affects the size of the window when
    // it's made visible, letting the window system deal with the
    // location.  The preferred szie is maintained independently from
    // the preferred position.  If both a preferred size and a preferred
    // position have been specified when the window is made visible, the
    // preferred position takes precedence (the size Setting is ignored
    // in this case).
    //
    // SUBCLASS: when creating a new window, if preferred size
    // has a value, use it to determine the initial window size
    // (to the extent possible).  Unless preferred position also
    // has a value, in which case use it instead.  Also, override
    // SetPrefferredSize() with a function that actually resizes
    // the window on the screen, if it's visible.


    virtual void          SetCurrentPosition(Position pos);
    virtual int           GetCurrentPosition(Position *pos);
    virtual void          UnsetCurrentPosition();

    inline  void          SetCurrentPosition(int xMin, int xMax,
					     int yMin, int yMax) {
      Position pos = {xMin, xMax, yMin, yMax};
      SetCurrentPosition(pos);
    }
    inline  int           GetCurrentPosition(int *xMin, int *xMax,
					     int *yMin, int *yMax) {
      Position pos;
      int v = GetCurrentPosition(&pos);
      *xMin = pos.p_XMin;
      *xMax = pos.p_XMax;
      *yMin = pos.p_YMin;
      *yMax = pos.p_YMax;
      return v;
    }
    inline int 	  MapToStandardSquare(int x, int y,
					      double *sx, double *sy) {
      *sx =
	2 * ((double)(x                       - mCurrentPosition.p_XMin))
	  / ((double)(mCurrentPosition.p_XMax - mCurrentPosition.p_XMin))
	- 1;
      *sy =
	2 * ((double)(y                       - mCurrentPosition.p_YMin))
	  / ((double)(mCurrentPosition.p_YMax - mCurrentPosition.p_YMin))
	- 1;
      return 0;
    }

    // Set/get the window's actual current position. This may differ
    // from the preferred position because the window system may not
    // have allowed the exact preferred position (or the preferred
    // position may not have been Set).  MG does not Set this value; it
    // just gets it.  The SetCurrentPosition() function exists to allow
    // client programs (or subclasses) to Set the current position value
    // whenever the window size changes (i.e. when the user has resized
    // the window).  SetCurrentPosition() does not affect the size of
    // the actual window --- it just changes the Setting stored with the
    // object.  Client programs should be sure that this value is
    // correct before calling MgContext::WorldBegin().
    //
    // SUBCLASS: make sure that the current position value is always
    // updated (1) when a window is created, (2) when it's size or
    // location are changed via SetPreferredSize() or
    // SetPreferredPosition(), and (3) when the user moves/resizes the
    // window.  The latter probably requires catching an event, which
    // happens outside this class; so just assume that the client
    // program will call SetCurrentPosition() when this has
    // happened. (Or possibly provide a subclass-specific function that
    // the client program can call to cause this object to update itself
    // with the new position information; in this case the call to
    // SetCurrentPosition() will happen insid that function.)

    virtual void          SetViewport(Position pos);
    virtual int           GetViewport(Position *pos);
    virtual void          UnsetViewport();
    // Set/get the part of the window which we're actually drawing into.
    // I'm not sure about the coordinate system for this, but I think
    // it's relative to the window itself.  Check on this later.  Also,
    // if no viewport has been explicitly Set, GetViewport() Sets *pos
    // to something reasonable anyway.  Its return value indicates
    // whether this value is one that was explictly Set (1), or not (0).
    // mbp Mon Apr 28 12:33:43 1997
    //
    // SUBCLASS: I'm not sure what subclasses should do here.  Should
    // they take action to arrange that we really only draw into the
    // viewport, or is this information here just to indicate that MG
    // will only be drawing into this part already?  The answer depends
    // on what MG does, which I don't totally understand yet.  For now,
    // though, our example program doesn't use viewports, so subclasses
    // can ignore this part (just leave these functions in the
    // superclass).

    virtual void          SetTitle(char *name);
    virtual int           GetTitle(char **name);
    virtual void          UnsetTitle();
    // Set/get the text used in the window's title bar. GetTitle() Sets
    // *name to point to the internal copy of the name; don't modify or
    // free this string!
    //
    // SUBCLASS: override SetTitle() with a function that actually
    // changes the title, if possible.

    typedef enum BufferMode {
        SINGLEBUFFER,
        DOUBLEBUFFER
    } BufferMode;

    virtual void          SetBufferMode(BufferMode mode);
    virtual int           GetBufferMode(BufferMode *mode);
    virtual void          UnsetBufferMode();
    // wether the window is in SINGLEBUFFER or DOUBLEBUFFER mode.
    //
    // SUBCLASS: override SetBufferMode() with a function that does it.

    virtual void          SetBorder(int onoff);
    virtual int           GetBorder(int *onoff);
    virtual void          UnsetBorder();
    // whether the window has a border
    //
    // SUBCLASS: override SetBorder() with a function that does actually
    // removes or adds a border around the window.

    virtual double        GetAspect();
    // Return the window's current aspect ratio.  Cannot be Set or unSet.
    // Computed from the current position.

    virtual void          SetPixelAspect(double a);
    virtual int           GetPixelAspect(double *a);
    // The window's pixel aspect ratio.  Cannot be unSet.  Default value is 1.
    //
    // SUBCLASS: call SetPixelAspect() when doing things that affect the
    // pixel aspect ratio.  This feature was added for handling hardware
    // stereo mode on SGIs, which involves streching the window vertically
    // by a factor of 2.  On MS windows, at least for now, we can ignore
    // this.

    virtual void          Show();
    // Make this window visible on the screen, if it's not already visible.
    //
    // SUBCLASS: override this with a function that does the job.

    virtual void          MakeCurrent();
    // Make this the current window for drawing operations. MG calls this
    // before drawing into this window.
    //
    // SUBCLASS: override this with a function that does the job.
  
    virtual void          SwapBuffers();
    // Swap front and back buffers, if doublebuffering.
    //
    // SUBCLASS: override this with a function that does the job.

    virtual void          Destroy();
    // Destroy the window (i.e. remove it from the screen, and
    // free up storage associcated with it).
    //
    // SUBCLASS: override this with a function that does the job.

    typedef enum {
        // ORable flags for use in SetBits and changedBits
        F_PREFERRED_POSITION        = 0x001,
        F_PREFERRED_SIZE            = 0x002,
        F_CURRENT_POSITION          = 0x004,
        F_VIEWPORT                  = 0x008,
        F_TITLE                     = 0x010,
        F_BUFFERMODE                = 0x020,
        F_BORDER                    = 0x040
    } FlagBit;

    int  Changed(FlagBit bit) { return ( (mChangedBits & bit) != 0 ); }
    void ClearChangedBit(FlagBit bit) { mChangedBits &= ~bit; }
    void ClearAllChangedBits() { mChangedBits = 0; }

    // ************************************************************************
    // ************************************************************************
    //
    // END OF PUBLIC INTERFACE.  Everything below is point is
    //   implementation-dependent; clients should ignore it all.
    //
    // ************************************************************************
    // ************************************************************************

private:
    Position      mPreferredPosition;
    int           mPreferredXSize;
    int           mPreferredYSize;
    Position      mCurrentPosition;
    Position      mViewport;
    char         *mpTitle;
    BufferMode    mBufferMode;
    int           mBorder;
    double        mPixelAspect;
    long int      mSetBits;
    long int      mChangedBits;

    void Init();
    void SetBit(FlagBit bit)        { mSetBits |= bit; mChangedBits |= bit; }
    void ClearBit(FlagBit bit)      { mSetBits &= !bit; }
    int  GetBit(FlagBit bit)        { return ( (mSetBits & bit) != 0 ); }
};

#endif // MGWINDOW_H
