//-*-C++-*-
#ifndef GVMOTION_H
#define GVMOTION_H

#include "GvAction.h"
#include "GvPath.h"

class GvMotion : public GvAction
{

    TYPE_DECLARE_TYPEINFO(GvMotion);

public:

  typedef enum MotionType {
    ONESHOT,
    INERTIAL
  } MotionType;

  GvMotion(MotionType   type,
	   GvPath      *moving,
	   GvPath      *center,
	   GvPath      *frame,
	   unsigned int t0);
  ~GvMotion();

  virtual void   Execute(unsigned int t = 0);
  virtual UtBool IsFinished();
  virtual UtBool IsFragile();
  virtual UtBool IsLike(GvAction *action);

  virtual void ComputeLocalTransform(Transform3 *M, unsigned int t = 0) = 0;

private:
  MotionType   mMotionType;
  GvPath      *mpMoving;
  GvPath      *mpCenter;
  GvPath      *mpFrame;
  unsigned int mT0;
};


#endif // GVMOTION_H
