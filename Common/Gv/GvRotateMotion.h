//-*-C++-*-
#ifndef GVROTATEMOTION_H
#define GVROTATEMOTION_H

#include "GvMotion.h"
#include "GvPath.h"

class GvRotateMotion : public GvMotion
{

  TYPE_DECLARE_TYPEINFO(GvRotateMotion);

public:
  GvRotateMotion(MotionType   type,
		 GvPath      *moving,
		 GvPath      *center,
		 GvPath      *frame,
		 unsigned int t0,
		 double       dx,
		 double       dy,
		 int          dt);
  virtual void ComputeLocalTransform(Transform3 *M,
				     unsigned int t = 0);

 private:
  double mDx;
  double mDy;
  double mXAngle;
  double mZAngle;
  int mDt;

};


#endif // GVROTATEMOTION_H
