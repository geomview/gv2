//-*-C++-*-
//
// GvRotateMotion.i: swig interface for GvRotateMotion
//

class GvRotateMotion : public GvMotion
{
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
};
