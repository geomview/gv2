
#include "EventHandler.h"
#include "HPoint3.h"
#include "Transform3.h"
#include "GvMotion.h"

#ifdef sqr
#undef sqr
#endif
#define sqr(x) (x)*(x)


BOOL EventHandler::OnLButtonDown(int x, int y, int time)
{
    mLButtonDown = TRUE;
    mOldX = x; mOldY = y;
    return(TRUE);
}

BOOL EventHandler::OnLButtonUp(int x, int y, int time)
{
    mLButtonDown = FALSE;
    return(TRUE);
}

BOOL EventHandler::OnLButtonDoubleClick(int x, int y, int time)
{
    return(TRUE);
}

BOOL EventHandler::OnMouseMove(int x, int y, int time)
{
    if (mLButtonDown)
    {
        double dx = (double)(x - mOldX) / (double)mWindowWidth * 2.0;
        double dy = (double)(y - mOldY) / (double)mWindowHeight * 2.0;
        double length = sqrt(sqr(dx)+sqr(dy));

        mCurAxisX = dx; mCurAxisY = dy;
        HPoint3 axis;
        axis.x = (float)dy; axis.y = (float)dx, axis.z = 0.0f;

        Transform3 rotation;

        rotation.Rotate((float)length, &axis);

        //  Transform3 *objectTransform = mpDocument->GetWorldTransform();
        //  objectTransform->Concat(objectTransform, &rotation);



        GvMotion *motion = new GvMotion(GvMotion::ONESHOT,
                                        mpDocument->GetGeometryWrapped(),
                                        rotation);

		        mpDocument->AddAction(motion);
        ::DeleteRef(motion);



        mOldX = x; mOldY = y;

        mpDocument->Tick();
		mpDocument->UpdateAll();


//        tmpVelocity = 2.0 * length / (CurTime - LastTime);

//        InvalidateRect(NULL);

//        double AngleInc = x - mOldX;
//        mpDocument->angle -=(double)AngleInc / 3.0;
//        mOldX = x;
    }
    return(TRUE);
}


