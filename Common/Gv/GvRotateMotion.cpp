#include <typeinfo>
#include <math.h>
#include "GvRotateMotion.h"
#include "UtException.h"
#include "Geometry.h"

TYPE_IMPLEMENT_TYPEINFO1(GvRotateMotion, GvMotion);

GvRotateMotion::GvRotateMotion(MotionType   type,
			       GvPath      *moving,
			       GvPath      *center,
			       GvPath      *frame,
			       unsigned int t0,
			       double       dx,
			       double       dy,
			       int          dt)
  : GvMotion(type,
	     moving,
	     center,
	     frame,
	     t0)
{
  mDx = dx;
  mDy = dy;
  mDt = dt;
  double magnitude = sqrt(mDx*mDx + mDy*mDy);
  if (magnitude > .0001) {
    mZAngle = atan2(mDy, mDx);
  } else {
    mZAngle = 0;
  }
  mXAngle = UtMathPI * magnitude / 4;

//  printf("new GvRotateMotion: [mDx,mDy,mDt] = [%5.2f, %5.2f, %5d]\n", mDx, mDy, mDt);
//  printf("  mZAngle = %f\n", mZAngle);
//  printf("  mXAngle = %f\n\n", mXAngle);
//  printf("  this = 0x%x\n", this);

}

#define PRINTTRANSFORM( T ) printf("%s =\n%s\n", #T, T.ToString(buffer))
static char buffer[1024];

void GvRotateMotion::ComputeLocalTransform(Transform3 *M,
					   unsigned int t = 0)
{
  // This is not right yet; just an approximation to test the rest of
  // the motion machinery.  The real version should do something more
  // meaningful with mDx, mDy, and mDt, and should use the value of t
  // passed in.

  M->Identity();
  if (mZAngle != 0.0) { M->CRotateZ( -mZAngle ); }
  M->CRotateY( -mXAngle );
  if (mZAngle != 0.0) { M->CRotateZ(  mZAngle ); }
}
