//-*-C++-*-
#ifndef MGCAMERA_H
#define MGCAMERA_H

#include "Geometry.h"
#include "RefObject.h"
#include "StorageObject.h"

class MgCamera : virtual public RefObject,
                 virtual public StorageObject
{
    TYPE_DECLARE_TYPEINFO(MgCamera);

public:

  MgCamera();
  ~MgCamera();


  // WARNING: the original Camera code provided for "unset" values ---
  // i.e. settable attributes which don't have a value.  This current
  // implementation does not have this feature.  As far as I know, it's
  // not used in any of the current code, but we may need to add it
  // back in the future. mbp Tue Apr 15 13:47:17 1997.

  typedef enum Projection {
    ORTHOGONAL,
    PERSPECTIVE
  } Projection;

  void          SetProjection(Projection p);
  Projection    GetProjection();
  // Set/get camera projection type (default: PERSPECTIVE)
    
  void          SetC2W(Transform3 *T);
  void          GetC2W(Transform3 *T);
  // Set/get camera-to-world transform: <world> * C2W = <cam>

  void          SetW2C(Transform3 *T);
  void          GetW2C(Transform3 *T);
  // Set/get world-to-camera transform (inverse of C2W)

  void          SetFOV(double degrees);
  double        GetFOV();
  // get/Set field of view (in degrees)

  void          SetHalfYField(double val);
  double        GetHalfYField();
  // get/Set FOV half-width at z=1 (Y direction)

  void          SetHalfField(double val);
  double        GetHalfField();
  // min FOV half-width

  void          SetAspectRatio(double aspect);
  double        GetAspectRatio();
  // get/Set aspect ratio, X/Y

  void          SetFocus(double f);
  double        GetFocus();
  // nominal focal distance for perspec<->ortho

  void          SetNearClip(double z);
  double        GetNearClip();
  // near clipping plane (distance from eye)

  void          SetFarClip(double z);
  double        GetFarClip();
  // far clipping plane (distance from eye)

  void  Reset(void);
  // reset everything back to default values

  void  GetViewProjection(Transform3 *T);
  // Sets T to the camera's projection transformation

  void  GetView(Transform3 *T);
  // Sets T to the complete transformation from world -> projected coordinates

  void  Transform(Transform3 *T);
  // Transform camera by T (in world coords)

  void          RotateX(float angle);
  void          RotateY(float angle);
  void          RotateZ(float angle);
  // rotate camera by angle radians in world coords

  void          Translate(float x, float y, float z);
  // translate camera in world coords

  void          Scale(float x, float y, float z);
  // scale the camera's transformation matrix; changes the size
  //  of the world as seen by the camera

  void          AlignZ(float x, float y, float z);
  // Rotate the camera to align its Z axis with (x,y,z) (in world coords)
  //  ?? not sure about these coord systems.  Check this.
  
  void          Copy(MgCamera *src);
  // Copy everything from *src camera to this one.

  void          Merge(MgCamera *src);
  // Merge values from *src camera to this one (only things that are
  //   actually set in *src get copied).  ?? Check this.

  int Save(class IoDataStream *s);
  int Load(class IoDataStream *s);

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
    /* bits for 'flag' and 'changed' fields */
    F_PERSP             = 0x01,
    F_NEWC2W            = 0x04,

    /* bits for 'changed' only */
    F_W2C               = 0x100,
    F_FOV               = 0x200,
    F_ASPECT            = 0x400,
    F_FOCUS             = 0x800,
    F_NEAR              = 0x1000,
    F_FAR               = 0x2000
  };

  Transform3    mCamToWorld;     /* this moves the camera to its spot */
  Transform3    mWorldToCam;     /* this puts the camera at the origin, etc*/
  int   mFlag;
  float mHalfYField,             /* FOV half-width at z=1 (Y direction) */
    mFrameAspect,                /* Aspect ratio, X/Y */
    mFocus,                      /* Nominal focal distance for perspec<->ortho*/
    mCNear, mCFar;                /* Near & far clipping distances */
  int           mChanged;        /* Mask of "changed" fields, for CamMerge */

  void  Init(void);

};

#endif /* MGCAMERA_H */
                                   
