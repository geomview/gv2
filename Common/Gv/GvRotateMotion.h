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
		 int          dx,
		 int          dy,
		 int          dt);
  virtual void ComputeLocalTransform(Transform3 *M,
				     unsigned int t = 0);

 private:
  int mDx;
  int mDy;
  int mDt;

};


#endif // GVROTATEMOTION_H
