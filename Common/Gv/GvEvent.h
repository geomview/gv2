//-*-C++-*-
#ifndef __GVEVENT_H__
#define __GVEVENT_H__

// Geomview System independent event handling classes.

/*#include <afxwin.h>*/
#include "UtLList.h"

typedef int BOOL;
#define FALSE 0
#define TRUE  0

struct GvEvent
{
    enum EventType
    {
        EMPTY_EVENT,
        LBUTTON_DOWN,
        LBUTTON_UP,
        LBUTTON_DOUBLE_CLICK,
        RBUTTON_DOWN,
        RBUTTON_UP,
        RBUTTON_DOUBLE_CLICK,
        MBUTTON_DOWN,
        MBUTTON_UP,
        MBUTTON_DOUBLE_CLICK,
        MOUSE_MOVE,
        KEY_DOWN,
        KEY_UP,
        TIMER
    };

    enum EventPriority
    {
        LOWEST_PRIORITY,
        LOW_PRIORITY,
        NORMAL_PRIORITY,
        MEDIUM_PRIORITY,
        HIGH_PRIORITY
    };

    struct Coordinate
    {
        short x, y;
    };

    struct KeyInfo
    {
        char mCharacter;
        BOOL mAlt;
        BOOL mCtrl;
        BOOL mShift;
    };

    unsigned int mTime;
    EventType mEventType;
    EventPriority mEventPriority;
    Coordinate mLocation;
    KeyInfo mKeyInfo;
};

class GvEventHandler
{
public:

    GvEventHandler();
    virtual ~GvEventHandler();

    // All of the following event functions will return TRUE if the
    // event was completely handled, Or FALSE if the message either
    // needs to be further handled by the default message system or by
    // a parent window.
    virtual BOOL OnLButtonDown(int x, int y, int time);
    virtual BOOL OnLButtonUp(int x, int y, int time);
    virtual BOOL OnLButtonDoubleClick(int x, int y, int time);
    virtual BOOL OnRButtonDown(int x, int y, int time);
    virtual BOOL OnRButtonUp(int x, int y, int time);
    virtual BOOL OnRButtonDoubleClick(int x, int y, int time);
    virtual BOOL OnMButtonDown(int x, int y, int time);
    virtual BOOL OnMButtonUp(int x, int y, int time);
    virtual BOOL OnMButtonDoubleClick(int x, int y, int time);
    virtual BOOL OnMouseMove(int x, int y, int time);

    virtual BOOL HandleEvent(GvEvent event);
    virtual void HandleEventList();

protected:
    
    // UtLList<GvEvent> mEvents;
    // mbp Sun Dec 07 10:35:25 1997
    // I've commented out the above declaration of mEvents because it
    // doesn't seem to be used right now, and I'm changing the
    // interface to the UtLList class and I want to make sure it's not
    // used anywhere while it's being changed.  If anyone reads this
    // comment before I have a chance to remove it, it's probably OK
    // to add mEvents back in and start using it --- just be sure to
    // consult UtLList.h to see what the proper usage is.
           
};

#endif //__GVEVENT_H__
