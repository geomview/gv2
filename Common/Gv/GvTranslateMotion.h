//-*-C++-*-
#ifndef GVTRANSLATEMOTION_H
#define GVTRANSLATEMOTION_H

#include "GvMotion.h"
#include "GvPath.h"

class GvTranslateMotion : public GvMotion
{

  TYPE_DECLARE_TYPEINFO(GvTranslateMotion);

public:
  GvTranslateMotion(MotionType   type,
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


#endif // GVTRANSLATEMOTION_H
