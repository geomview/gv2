//-*-C++-*-
//
// GvUniverse.i: swig interface for GvUniverse
//

class GvUniverse
{

public:
  GvUniverse();
  ~GvUniverse();
  void               AddGeometry(class Geom *geom);
  void               DeleteGeometry(class Geom *geom);
  void               AddFreeCamera(class GvCamera *camera);
  void               DeleteFreeCamera(class GvCamera *camera);
  class GeomWrapped *GetWorldBase();
  class GeomList    *GetWorldList();
  class GeomWrapped *GetUniverseBase();

  void               Dump();

};
