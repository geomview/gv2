//-*-C++-*-
#ifndef MGOPENGLCONTEXT_H
#define MGOPENGLCONTEXT_H

#include "GlHeaders.h"
#include "MgContext.h"
//#include "MgOpenGlContextShade.h"



class MgOpenGlContext : public MgContext {
public:

  MgOpenGlContext(void);
  virtual ~MgOpenGlContext();

  //
  // OPENGL-SPECIFIC functions:
  //

  virtual void          SetGlWinID(int id);
  virtual int           GetGlWinID();
  // Set/get the window id (returned by winopen) associated with this
  // context.

  virtual int           IsBorn();
  // Return 1 if this window has been born (created), 0 if not

  virtual int           GetZMax();
  // Return the max z-buffer value

  typedef enum DitherValue {
    DITHER_ON,
    DITHER_OFF
  } DitherValue;

  virtual void          SetDither(DitherValue onoff);
    // Set dithering control

  virtual DitherValue   GetDither();
    // Get dithering control




  //
  // OVERRIDDEN FUNCTIONS (inherited):
  //

  virtual void          SetZNudge(double znudge);
    //virtual void          SetShaderFunc(MgShadeFunc func, void *data);
  virtual int           GetBitDepth();
  virtual void          Sync( void );
  virtual void          WorldBegin( void );
  virtual void          WorldEnd( void );
  virtual void          ReshapeViewport( void );

  virtual void          SetTransform( Transform3 *T );
  virtual void          GetTransform( Transform3 *T );
  virtual void          Identity( void );
  virtual void          Transform( Transform3 *T );
  virtual void          PushTransform( void );
  virtual void          PopTransform( void );
  virtual void          PushAppearance(void);
  virtual void          PopAppearance(void);
  virtual void          MergeAppearance(MgAppearance *ap);
  virtual MgAppearance *GetAppearance(void);

  virtual void          Polygon(int nv, HPoint3 *v, int nn, Point3 *n,
                                int nc,MgColorA *c );
  virtual void          Polylist(int np, struct Poly *p, int nv,
                                 struct Vertex *v, int plflags);
  virtual void          Mesh(int wrap,int nu,int nv, HPoint3 *p,
                             Point3 *n,MgColorA *c,Point3 *str );
  virtual void          Line( HPoint3 *p1, HPoint3 *p2 );
  virtual void          Polyline(int nv, HPoint3 *verts, int nc,
                                 MgColorA *colors, int wrapped );
  virtual void          Quads(int nquads, HPoint3 *verts, Point3 *normals,
                              MgColorA *colors );


  // ************************************************************************
  // ************************************************************************
  //
  // END OF PUBLIC INTERFACE.  Everything below is point is
  //   implementation-dependent; clients should ignore it all.
  //
  // ************************************************************************
  // ************************************************************************


private:

  enum {
    SGL=0,
    DBL=1
  };

  // Max possible depth of MgOpenGlContext::Closer()/Farther() calls:
  static const int MAXZNUDGE;

/* We save the current W2C/C2W xforms on each call to MgOpenGlContext::WorldBegin()
 * because the ModelView matrix stack actually stores both our object
 * xform and the view matrix:
 *
 *   ModelView = [ obj xform ] * [ W2C ]
 *
 * Since we use the GL ModelView stack to keep track of our object xform,
 * instead of using the actual stack in the mgcontext struct, having
 * ModelView = W2C corresponds to [ obj xform ] = identity.  We save W2C
 * and C2W on each MgOpenGlContext::WorldBegin() because _mgc->cam might change
 * during the course of the frame, but isn't supposed to be reinterpreted
 * until the next MgOpenGlContext::WorldBegin().
 */


  void              Init(void);

  void              Appearance( MgAppearanceStackNode *node, int mask );
  void              Material(MgAppearanceStackNode *node, int mask);
  int               LightDef(int lightno, MgLight *light,
                             MgLighting *lgt, int mask);
  void              Lighting(MgAppearanceStackNode *node, int mask);
  int               LightModelDef(int lightmodel, MgLighting *lgt,
                                  int mask, MgAppearanceStackNode *node);
  void              Lights(MgLightList *lightList,
                           MgAppearanceStackNode *node);

  void              Closer();
  void              D4f(MgColorA *color);
  void              Drawormal(register HPoint3 *p, Point3 *n);
  void              Farther();
  MgContext         * FindCtx( int winid );
  void              InitZRange();
  void              InitWin();
  void              N3fEvert(register Point3 *n, register HPoint3 *p);
  void              Point(register HPoint3 *v);
  void              SetViewport();
  int               TrickyPolygon( Poly *p, int plflags ) ;
  void              V4fCloser(HPoint3 *p);
  void              Submesh(int wrap, int nu, int nv,
                            int umin, int umax,
                            int vmin, int vmax,
                            HPoint3 *meshP, Point3 *meshN,
                            MgColorA  *meshC, Point3 *meshSTR);
  void              Tessvert(Vertex *vp);
  int               mFlipNormals;
  void              N3f(Point3 *normal, HPoint3 *base) {
                        if (mFlipNormals) { N3fEvert(normal, base); }
                        else { glNormal3fv(((float*)normal)); }
                    }

  int               mConstantShading;
  int mTessPlFlags;
  int mBorn;                     /* Has window been displayed on the screen? */
  int mGlWinId;                  /* GL window ID, or 0 */
  double mZMin, mZMax;            /* max z-buffer value */
  short mIsPI;                  /* Personal Iris? (pgon vs tmesh speed) */
  short mTurbo;                  /* Turbo PI flag: for bug workaround */
  MgColorA mCd;                  /* Cached diffuse color = mat->diffuse * Kd */
  int mLmColor;                  /* mLmColor: GL_DIFFUSE or XXX lmc_COLOR */
  double mZNudge;                /* _mgc.mZFNudge in integer Z-buffer units */
  double mZNear, mZFar;           /* Current Z-buffer glDepthRange(, $2) limits */
  int mOldOpts;                  /* For knowing when we need to reconfigure */
  vvec mRoom;                    /* Scratch space */
  int mShouldLighting, mIsLighting; /* Lighting flags so we can turn off
                                        lighting for points&lines */
  DitherValue mDither;           /* Dither enabled? */

  float mKd;

  inline void MayLight(void)  {
    if(this->mShouldLighting && !this->mIsLighting) {
      glEnable((GL_LIGHTING));
      this->mIsLighting = 1;
    }
  }

  inline void DontLight(void) {
    if(this->mIsLighting) {
      glDisable((GL_LIGHTING));
      this->mIsLighting = 0;
    }
  }

};





#endif /* MGOPENGLCONTEXT_H */
