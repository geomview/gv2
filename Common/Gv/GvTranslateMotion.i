//-*-C++-*-
//
// GvTranslateMotion.i: swig interface for GvTranslateMotion
//

class GvTranslateMotion : public GvMotion
{
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
};
