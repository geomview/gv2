//-*-C++-*-
#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "MsGvDoc.h"
#include "GvEvent.h"

class EventHandler : public GvEventHandler
{
public:
    EventHandler(CMsGvDoc *doc, int width, int height) 
    {
        mpDocument = doc;
        mWindowWidth = width;
        mWindowHeight = height;
        mLButtonDown = FALSE;
    }

    void SetWindowWidth(int width) { mWindowWidth = width; }
    void SetWindowHeight(int height) { mWindowHeight = height; }
    void SetWindowDim(int width, int height)
    {
        mWindowWidth = width;
        mWindowHeight = height;
    } 
    BOOL OnLButtonDown(int x, int y, int time);
    BOOL OnLButtonUp(int x, int y, int time);
    BOOL OnLButtonDoubleClick(int x, int y, int time);
    BOOL OnMouseMove(int x, int y, int time);

private:

    CMsGvDoc *mpDocument;
    double       mWindowWidth, mWindowHeight;
    int          mOldX, mOldY;
    double       mCurAxisX, mCurAxisY;
    BOOL         mLButtonDown;
};

#endif //__EVENTHANDLER_H__
