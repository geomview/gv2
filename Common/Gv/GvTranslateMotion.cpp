#include <typeinfo>
#include <math.h>
#include "GvTranslateMotion.h"
#include "UtException.h"
#include "Geometry.h"

TYPE_IMPLEMENT_TYPEINFO1(GvTranslateMotion, GvMotion);

GvTranslateMotion::GvTranslateMotion(MotionType   type,
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

void GvTranslateMotion::ComputeLocalTransform(Transform3 *M,
					   unsigned int t)
{
  M->Translate(mDx, -mDy, 0);
}
