//-*-C++-*-
//
// GvScaleMotion.i: swig interface for GvScaleMotion
//

class GvScaleMotion : public GvMotion
{
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
};
