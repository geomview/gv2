//-*-C++-*-
//
// GvAction.i: swig interface for GvAction
//

class GvAction
{
public:
  virtual void        Execute(unsigned int t = 0) = 0;

//
// Note: figure out how to map UtBool to python int
//   is this a case for typemap?
//

  virtual int      IsFinished() = 0;
  virtual int      IsFragile() = 0;
  virtual int      IsLike(GvAction *action) = 0;
};
