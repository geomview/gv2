//-*-C++-*-
//
// GvPath.i: swig interface for GvPath
//

class GvPath
{

public:
  GvPath(GvUniverse *world, Geom *g);
  ~GvPath();
  Geom *Resolve();
  Transform3 *GetLocalTransform();
  void GetCumulativeTransform(Transform3 *T);
  void GetChangeOfCoordsTransform(Transform3 *T,
				  GvPath *that);
  void Dump();
};
