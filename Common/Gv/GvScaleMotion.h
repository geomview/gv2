//-*-C++-*-
#ifndef GVSCALEMOTION_H
#define GVSCALEMOTION_H

#include "GvMotion.h"
#include "GvPath.h"

class GvScaleMotion : public GvMotion
{

  TYPE_DECLARE_TYPEINFO(GvScaleMotion);

public:
  GvScaleMotion(MotionType   type,
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
  int mDt;
};


#endif // GVSCALEMOTION_H
