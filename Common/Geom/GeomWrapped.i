//-*-C++-*-
//
// GeomWrapped.i: swig interface for GeomWrapped
//

class GeomWrapped : public GeomParent
{
public:
  GeomWrapped(Geom *geom);
  ~GeomWrapped();
  void SetTransform(const Transform3 &T);
  Transform3 *GetTransform();
};

