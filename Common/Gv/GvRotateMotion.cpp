#include <typeinfo>
#include "GvRotateMotion.h"
#include "UtException.h"
#include "Geometry.h"

TYPE_IMPLEMENT_TYPEINFO1(GvRotateMotion, GvMotion);

GvRotateMotion::GvRotateMotion(MotionType   type,
			       GvPath      *moving,
			       GvPath      *center,
			       GvPath      *frame,
			       unsigned int t0,
			       int          dx,
			       int          dy,
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
}

void GvRotateMotion::ComputeLocalTransform(Transform3 *M,
					   unsigned int t = 0)
{
  // This is not right yet; just an approximation to test the rest of
  // the motion machinery.  The real version should do something more
  // meaningful with mDx, mDy, and mDt, and should use the value of t
  // passed in.
  M->Identity();
  M->CRotateX( UtMathPI * mDy / 180);
  //M->CRotateY( -UtMathPI * mDx / 180);
}
