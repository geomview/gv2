//-*-C++-*-
//
// Geom.i: swig interface for Geom
//

class Geom
{
public:
  int   Save(char *, char *);
  void  SetName(char *);
  virtual void  Draw(MgOpenGlContext *mg);
};

// I think this method shouldn't really be necessary.  It's here
// because I'm having trouble getting python/swig to recognize that a
// 'GvCamera *' returned by a C function whose return type is 'Geom *'
// (GvPath::Resolve) is actually a 'GvCamera *'.  Until I can figure
// out how to do this, I use this function to explicitly cast the
// 'Geom *' to 'GvCamera *'.

%addmethods Geom {
  GvCamera *CastToGvCamera() {
    return (GvCamera*)self;
  };
};
