//-*-C++-*-
#ifndef MGCONTEXT_H
#define MGCONTEXT_H

#include <stdlib.h>
#include "MgColor.h"
#include "Geometry.h"
#include "MgWindow.h"
#include "MgCamera.h"
#include "MgAppearance.h"
#include "MgMaterial.h"
#include "MgLight.h"
#include "MgLighting.h"
#include "MgAppearanceStack.h"
#include "UtLStack.h"
#include <ooglutil.h>


class MgContext {

public:

    MgContext(void);

    virtual ~MgContext(void);
    //  Class destructor.

    virtual void          SetWindow(MgWindow *win);
    //  Set the context's associated MgWindow object.

    virtual MgWindow *    GetWindow();
    //  Return a pointer to the context's associated MgWindow object.

    enum OptionBit {
        // Bitwise ORable options for SetOptions() / GetOptions()
        O_DOUBLEBUFFER      = 0x1,   // Default single buffered
        O_HIDDEN            = 0x2,   // Default not Z-buffered
        O_BACKFACECULL      = 0x4,   // Default back-faces shown
        O_INHIBITBACKGROUND = 0x8,   // Default background drawn
        O_INHIBITCLEAR      = 0x10,  // Default clear at WorldBegin
        O_INHIBITSWAP       = 0x20,  // Default swapbufs at WorldEnd
        O_NORED             = 0x40,  // Inhibit drawing into red
        O_NOGREEN           = 0x80,  // ... green ...
        O_NOBLUE            = 0x100, // ... or blue planes
        O_INHIBITCAM        = 0x200  // Don't load matrix in WorldBegin()
    };

    virtual void          SetOptions(int mask);
    //  Set some options; mask is a bitwise ORed selection of options

    virtual void          UnsetOptions(int mask);
    //  UnSet some options; mask is a bitwise ORed selection of options

    virtual int           GetOptions();
    //  Return the option mask

    virtual void          SetBackgroundColor(MgColorA color);
    //  Set the background color

    inline void SetBackgroundColor(float r, float g, float b) {
      MgColorA color(r,g,b,1.0);
      SetBackgroundColor(color);
    }

    virtual MgColorA      GetBackgroundColor();
    //  Return the background color

    virtual void          SetZNudge(double znudge);
    //  Set the fraction of the z-range by which lines and edges are
    //  nudged nearer the viewpoint than polygons.

    virtual double        GetZNudge();
    //  Return the fraction of the z-range by which lines and edges are
    //  nudged nearer the viewpoint than polygons.

    typedef int (*MgShadeFunc)(int npoints,
                               HPoint3 *points,
                               Point3 *normals,
                               MgColorA *colors,
                               MgColorA *newcolors );

    //virtual void          SetShaderFunc(MgShadeFunc func, void *data);
    //  Set the software shading function

    virtual int           GetBitDepth();

    enum WinWhy {
        // win_why values for (*mpWinChange) callback
        W_WINCHANGE,
        W_WINDELETE
    };

    typedef void (*MgWinchFunc)(MgContext *ctx,
                                void *data,
                                WinWhy win_why,
                                ...);

    virtual void          SetWinchFunc(MgWinchFunc func, void *data);
   

    virtual void          Sync( void );
    //  Insures that all graphics operations have been sent to the device,
    //  and instructs the device to process them to whatever extent it can
    //  at the time.  The idea is to force the device to display as much
    //  as it can, for example, to guarantee (in singlebuffer mode) that
    //  everything that has been drawn so far is actually visible in the
    //  window.  It might also be necessary for telling mg and/or the
    //  device to flush any internal buffering of graphics operations.
    //  WorldEnd() calls Sync() implicitly; clients can call Sync()
    //  explicitly in order to force the display to be current, although
    //  the exactly definition of what Sync() does is up to each
    //  individual device.

    virtual void          WorldBegin( void );
    //  Tells the context that we're about to clear the screen and to
    //  prepare for drawing.  All calls to graphics drawing functions
    //  should be bracketed between calls to WorldBegin() and WorldEnd().

    virtual void          WorldEnd( void );
    //  Ends a series of graphics calls, and causes the context to do
    //  whatever wrapup is necessary.  This might involve swapping buffers,
    //  closing files, or whatever.

    virtual void          ReshapeViewport( void );
    //  Instructs the context that the window information in its
    //  associated MgWindow object (A_WINDOW attribute) has changed and
    //  that it should update whatever is necessary in its internal state
    //  to account for this.  Should not be called between WorldBegin()
    //  and WorldEnd().

    virtual void          SetTransform( Transform3 *T );
    //  Set the top of the transform stack to T.

    virtual void          GetTransform( Transform3 *T );
    //  Return the matrix at the top of the transform stack; it's written
    //  to the space pointed to by T.

    virtual void          Identity( void );
    //  Set the top of the transform stack to the identity matrix.

    virtual void          Transform( Transform3 *T );
    //  (Pre)multiply the top of the transform stack by T.  Specifically,
    //  if the stack top was initially A, then after this call it will be
    //  T * A.

    virtual void          PushTransform( void );
    //  Push a copy of the top matrix onto the stack, so that the stack
    //  ends up with two copies of that matrix at its top:
    //               before  after
    //                 A       A     <-- top
    //                 B       A
    //                 C       B
    //                ...      C
    //                        ...

    virtual void          PopTransform( void );
    // Pop a matrix off the top of the transform stack (discarding it).
    // If you want to know what matrix was popped off, get it with
    // GetTransform() before calling PopTransform().

    virtual void          PushAppearance(void);
    // Push an appearance onto the appearance stack.  Similar to
    // PushTransform(), in that the top of the stack is duplicated.

    virtual void          PopAppearance(void);
    // Pop an appearance off the stack.

    enum MergeType {
        // merge types for mgSetAppearance()
        M_SET,
        M_MERGE
    };

    // virtual MgAppearance   *SetAppearance(MgAppearance *ap, MergeType mergeflag);
    // Set the top of the appearance stack to the given appearance, merged
    // with the current appearance according to mergeflag.  I don't completely
    // understand the types of merging yet.

    virtual MgAppearance   *GetAppearance(void)
    {
        return( mAStk.Top()->GetAppearance() );
    }
    // Return a pointer to the current appearance.  This pointer points
    // to the real thing, not a copy, so modifying it changes the current
    // appearance.

    void MergeAppearance(MgAppearance *ap);

    virtual void          SetCamera( MgCamera *cam );
    // Set the camera associated with this context.  This is the same
    // as Setting the A_CAMERA attribute.  Should we get rid of this
    // procedure??  mbp Thu Apr 10 17:06:11 1997

    virtual void          Polygon(int nv, HPoint3 *v, int nn, Point3 *n,
                                  int nc,MgColorA *c );
    // Draw a polygon; fill in details about what all these args mean later.

    struct Vertex;
    struct Poly;

    virtual void          Polylist(int np, struct Poly *p, int nv,
                                   struct Vertex *v, int plflags);
    // Draw a polylist; fill in details about what all these args mean later.

    enum MeshWrapStyle {
        // Bitwise ORable values for the "wrap" int passed to "Mesh()"
        MESH_NOWRAP = 0x0,
        MESH_UWRAP  = 0x1,
        MESH_VWRAP  = 0x2
    };

    virtual void          Mesh(int wrap,int nu,int nv, HPoint3 *p,
                               Point3 *n,MgColorA *c,Point3 *str );
    // Draw a mesh; fill in details about what all these args mean later.

    virtual void          Line( HPoint3 *p1, HPoint3 *p2 );
    // Draw a line; fill in details about what all these args mean later.

    virtual void          Polyline(int nv, HPoint3 *verts, int nc,
                                   MgColorA *colors, int wrapped );
    // Draw a polyline; fill in details about what all these args mean later.

    virtual void          Quads(int nquads, HPoint3 *verts, Point3 *normals,
                                MgColorA *colors );
    // Draw some quads; fill in details about what all these args mean later.

    virtual void          Bezier(int du, int dv, int dimn, float *ctrlpts,
                                 float *txmapst, MgColorA *c);
    // Draw a bezier patch; fill in details about what all these args mean later.

    // ************************************************************************
    // ************************************************************************
    //
    // END OF PUBLIC INTERFACE.  Everything below is point is
    //   implementation-dependent; clients should ignore it all.
    //
    // ************************************************************************
    // ************************************************************************


protected:
    /*
     * Transform stack, pushed by mgpushTransform().
     */
    class TransformStackNode {
    public:
        Transform3  p_mT;        // Current object->world xform
        short       p_mXfmSeq;  // sequence number
        short       p_mHasInv;   // Flag: p_mTinv is valid
        Transform3  p_mTinv;     // inverse of p_mT
    };


    virtual  void         FindCam();

    //    virtual int     AppearanceBits( MgAppearance *ap, int mergeflag,
    //                                    int *valid, int *flag );
    virtual void          FindO2S();
    virtual void          FindS2O();
    virtual void          GlobalLights( MgLightList *lightList, int WorldBegin );
    virtual void          MakePoint();
    virtual int           Get4to3( Transform3 *T );
    virtual void          Set4to3( Transform3 *T, int seq );
#if 0
    virtual int           EucShade(int nv, HPoint3 *v, Point3 *n,
                                   MgColorA *c, MgColorA *cs);
#endif
    virtual void          Cotransform(register Transform3 *Tinv,
                                      register Point3 *in, Point3 *out);

    float mEuck1;          /* inverse power falloff */
    float mEuck2;          /* safety zone around light */
    float mFog;            /* mFog control                  */
    float mHypk1;          /* exponential falloff  */
    float mHypk2;          /* exponential falloff  */
    float mSphk1;          /* exponential falloff  */
    float mSphk2;          /* safety zone around light */

    short mChanged;        /* flags: Must update device state because...*/
    enum ChangedBit {
        C_WIN   = 0x01,  //  window changed (reshaped, &c)
        C_CAM   = 0x02,  //  MgCamera changed
        C_AP    = 0x04,  //  MgAppearance changed
        C_MAT   = 0x08,  //  MgMaterial changed
        C_LIGHT = 0x10,  //  Lighting changed
        C_TRANS = 0x20,  //  Transformation changed
        C_OPT   = 0x40,  //  Options changed
        C_USED  = 0x80   //  WorldBegin called (used by mg_textureclock)
    };
    MgWindow      *mpWin;   /* MgWindow */
    MgCamera      *mpCam;   /* MgCamera */
    MgContext             *mpParent; /* Parent mg MgWindow, if any */
    MgContext             *mpNext;  /* Link in list of all mg contexts */
    MgAppearanceStack   mAStk; // appearance stack
    UtLStack<TransformStackNode> mXStk;   /* Transform stack */
    int           mShown;  /* Is window 'visible'? */
    MgColorA      mBackground; /* Background color */

    int           mOpts;   /* MG_SETOPTIONS flag mask */

    Transform3    mW2C;    /* World->camera transform */
    Transform3    mC2W;    /* MgCamera->world transform */

    Transform3    mT4;     /* 4D->3D transform */
    int           mT4Seq; /* sequence number for mT4 */

    float         mZFNudge; /* fraction of Z-range by which lines are
                             * nudged closer than surfaces. */
    int           mSpace;  /* space in which objects being drawn
                            * live; should be TM_EUCLIDEAN,
                            * TM_HYPERBOLIC, or TM_SPHERICAL
                            */


    Transform3    mW2S, mS2W; /* world-to-screen, screen-to-world xfms */

    int           mHas;    /* Flag bits, Set when cached values valid */
    enum HasBits {
        HAS_CPOS   = 0x1,  // MgCamera position (mCPos, mCamZ)
        HAS_mS2O    = 0x2,  // mS2O, mO2S
        HAS_POINT  = 0x4   // Outline for generic fat point
    };

    // Cached values, computed when needed:
    Point3        mCPos;       // Location of camera in object coordinates
    Point3        mCamZ;       // Direction of camera +Z vector
    Transform3    mO2S, mS2O;   // object-to-screen, screen-to-object xfms
    vvec          mPointVvec; // outline for fat points

    MgWinchFunc   mpWinChange;  // Callback function for mg MgWindow etc. changes
    void          *mpWinChangeInfo; // We call (*mpWinChange)(ctx, mpWinChangeInfo,
    //                      win, changemask)


private:
    void Init();                // mbp-purify (moved this to private)

};

#endif /* MGCONTEXT_H */
