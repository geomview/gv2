//-*-C++-*-
//
// GvMotion.i: swig interface for GvMotion
//

class GvMotion : public GvAction
{
public:
  enum MotionType {
    ONESHOT,
    INERTIAL
  };
};
