//-*-C++-*-
//
// GvCamera.i: swig interface for GvCamera
//

class GvCamera :  public Geom
{

public:
  GvCamera();
  ~GvCamera();
  void              Render();
  void              SetMgContext(class MgContext *mg);
  class MgContext * GetMgContext();
  void              SetTarget(class Geom *geom);
  Geom *            GetTarget();
  MgCamera *        GetMgCamera();
  void              SetW2C(Transform3 *T);
  void              GetW2C(Transform3 *T);

};
