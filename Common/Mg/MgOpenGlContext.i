//-*-C++-*-
//
// MgOpenGlContext.i: swig interface for MgOpenGlContext
//

class MgOpenGlContext : public MgContext {
public:
  MgOpenGlContext();
  ~MgOpenGlContext();

  void SetWindow(MgWindow *win);
  void WorldBegin( void );
  void WorldEnd( void );
  void SetTransform( Transform3 *T );
  void ReshapeViewport( void );
  void SetBackgroundColor(float r, float g, float b);

  void SetCamera(MgCamera *);
};
