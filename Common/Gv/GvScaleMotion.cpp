#include <typeinfo>
#include <math.h>
#include "GvScaleMotion.h"
#include "UtException.h"
#include "Geometry.h"

TYPE_IMPLEMENT_TYPEINFO1(GvScaleMotion, GvMotion);

GvScaleMotion::GvScaleMotion(MotionType   type,
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
}

void GvScaleMotion::ComputeLocalTransform(Transform3 *M,
					   unsigned int t = 0)
{
  double s = exp( (mDx-mDy)/2 );
  M->Scale(s, s, s);
}
