
#include "GvEvent.h"

GvEventHandler::GvEventHandler()
{

}

GvEventHandler::~GvEventHandler()
{

}

BOOL GvEventHandler::OnLButtonDown(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnLButtonUp(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnLButtonDoubleClick(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnRButtonDown(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnRButtonUp(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnRButtonDoubleClick(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnMButtonDown(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnMButtonUp(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnMButtonDoubleClick(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::OnMouseMove(int x, int y, int time)
{
    return(FALSE);
}

BOOL GvEventHandler::HandleEvent(GvEvent event)
{
    switch(event.mEventType)
    {
    case GvEvent::LBUTTON_DOWN:
        return(OnLButtonDown(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::LBUTTON_UP:
        return(OnLButtonUp(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::LBUTTON_DOUBLE_CLICK:
        return(OnLButtonDoubleClick(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::RBUTTON_DOWN:
        return(OnRButtonDown(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::RBUTTON_UP:
        return(OnRButtonUp(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::RBUTTON_DOUBLE_CLICK:
        return(OnRButtonDoubleClick(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::MBUTTON_DOWN:
        return(OnMButtonDown(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::MBUTTON_UP:
        return(OnMButtonUp(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::MBUTTON_DOUBLE_CLICK:
        return(OnMButtonDoubleClick(event.mLocation.x, event.mLocation.y, event.mTime));
    case GvEvent::MOUSE_MOVE:
        return(OnMouseMove(event.mLocation.x, event.mLocation.y, event.mTime));
    default:
        return(FALSE);
    };
}

void GvEventHandler::HandleEventList()
{

}
