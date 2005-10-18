#include <math.h>
#include <stdarg.h>
#include "Geometry.h"
#include "MgCamera.h"
#include "IoDataStream.h"

#define SETFLAG(flag, bit, value)       \
        if (value) flag |= bit;         \
        else     flag &= ~bit

#define GETFLAG(flag, bit)      ( (flag & bit) != 0 )

TYPE_IMPLEMENT_TYPEINFO2(MgCamera, RefObject, StorageObject);

MgCamera::MgCamera()
{
  Init();
}

MgCamera::~MgCamera()
{
  // do reference decrementing here, and really delete only if 0 ???
}


int MgCamera::Save(IoDataStream *s)
{ return 0; }


int MgCamera::Load(IoDataStream *s)
{ return 0; }


void MgCamera::Init()
{
  mFlag = F_PERSP;
  mFrameAspect = (float)(4.0/3.0);
  mFocus = 3.0;
  Reset();   // this sets all other data fields  (mbp-purify)
}

void MgCamera::SetProjection(Projection p)
{
  switch (p) {
  default:
  case PERSPECTIVE:
    mFlag |= F_PERSP;
    break;
  case ORTHOGONAL:
    mFlag &= ~F_PERSP;
    break;
  }
}

MgCamera::Projection MgCamera::GetProjection()
{
  if (mFlag & F_PERSP) {
    return PERSPECTIVE;
  } else {
    return ORTHOGONAL;
  }
}

void MgCamera::SetC2W(Transform3 *T)
{
  mCamToWorld.Copy(T);
  mWorldToCam.InverseOf(T);

  mChanged |= F_NEWC2W;
  mChanged &= ~F_W2C;
}

void MgCamera::GetC2W(Transform3 *T)
{
  // mCamToWorld is always up to date, so just copy
  T->Copy(&mCamToWorld);
}

void MgCamera::SetW2C(Transform3 *T)
{
  mWorldToCam.Copy(T);
  mCamToWorld.InverseOf(&mWorldToCam);

  mChanged |= F_W2C;
  mChanged &= ~F_NEWC2W;
}

void MgCamera::GetW2C(Transform3 *T)
{
  /* mWorldToCam is not always up to date, so update if necessary ... */
  if (mFlag & F_NEWC2W ) {
    mWorldToCam.InverseOf(&mCamToWorld);
    mFlag &= ~F_NEWC2W;
  }
  /* ... then copy */
  T->Copy(&mWorldToCam);
}

void MgCamera::SetFOV(double degrees)
{
  double v = degrees / 2;
  mChanged |= F_FOV;
  if(mFlag & F_PERSP) {
    if(v >= 180/2) v = 120/2;
    v = tan( RADIANS(v) );
  }
  SetHalfField(v);
}

double MgCamera::GetFOV()
{
  return 2 * ( (mFlag & F_PERSP)
               ? DEGREES( atan( (double)(GetHalfField()) ) )
               : GetHalfField());
}

void MgCamera::SetHalfYField(double val)
{
  mHalfYField = (float)val;
  if(mFlag & F_PERSP)
    mHalfYField *= mFocus;
  mChanged |= F_FOV;
}

double MgCamera::GetHalfYField()
{
  return (mFlag & F_PERSP) ? mHalfYField / mFocus
     : mHalfYField;
}

void MgCamera::SetAspectRatio(double aspect)
{
  if(aspect > 0) {
    mFrameAspect = (float)aspect;
    SetHalfField(GetHalfField());
    mChanged |= F_ASPECT;
  }
}

double MgCamera::GetAspectRatio()
{
  return mFrameAspect;
}

void MgCamera::SetFocus(double f)
{
  if(f > 0) {
    if(mFlag & F_PERSP)
      mHalfYField *= (float)(f / mFocus);
    mFocus = (float)f;
    mChanged = F_FOCUS;
  }
}

double MgCamera::GetFocus()
{
  return mFocus;
}

void MgCamera::SetNearClip(double z)
{
  mCNear = (float)z;
  mChanged = F_NEAR;
}

double MgCamera::GetNearClip()
{
  return mCNear;
}

void MgCamera::SetFarClip(double z)
{
  mCFar = (float)z;
  mChanged = F_FAR;
}

double MgCamera::GetFarClip()
{
  return mCFar;
}

void MgCamera::Copy(MgCamera *src)
{
  // *this = *src;

  mCamToWorld.Copy(&src->mCamToWorld);
  mWorldToCam.Copy(&src->mWorldToCam);

  mFlag = src->mFlag;
  mHalfYField = src->mHalfYField;
  mFrameAspect = src->mFrameAspect;
  mFocus = src->mFocus;
  mCNear = src->mCNear;
  mCFar = src->mCFar;
  mChanged = src->mChanged;
  ////////////////
}

void MgCamera::Merge(MgCamera *src)
{
    int chg;

    if(src == NULL) return;
    chg = src->mChanged;
    if(chg & F_NEWC2W) SetC2W(&src->mCamToWorld);
    if(chg & F_W2C) SetW2C(&src->mWorldToCam);

    double fov = GetFOV();
    if(chg & F_FOCUS) SetFocus(src->mFocus);
    if(chg & F_PERSP) SetProjection(src->GetProjection());
    if(chg & F_FOV) SetFOV(fov);
    if(chg & F_ASPECT) SetAspectRatio(src->mFrameAspect);
    if(chg & F_NEAR) SetNearClip(src->mCNear);
    if(chg & F_FAR) SetFarClip(src->mCFar);
}


void MgCamera::Reset()
{
    Transform3 T;
//  int persp;

    SetNearClip( 0.07 );
    SetFarClip( 100.0 );
    SetFocus( 3.0 );
    SetFOV( GetProjection() == PERSPECTIVE ? 40.0 : 2.2 );

    T.Translate( 0.0, 0.0, mFocus );
    SetC2W(&T);
}

/*
 * Return camera's projection transform in proj.
 * See CamView below for the range of the projection.
 */
void MgCamera::GetViewProjection(register Transform3 *proj)
{
  float y;
  float x;

  y = mHalfYField;
  if(mFlag & F_PERSP)
    y *= mCNear / mFocus;
  x = mFrameAspect * y;

  if(mFlag & F_PERSP) {
    proj->Perspective( -x, x, -y, y, mCNear, mCFar );
  } else {
    proj->Orthographic( -x, x, -y, y, mCNear, mCFar );
  }
}

/*
 * Computes complete transformation from world -> projected coordinates
 * and leaves it in T.
 * Projected coordinates map the visible world into -1 <= {X,Y,Z} <= 1,
 * with Z = -1 at the near plane and Z = +1 at the far plane.
 */
void MgCamera::GetView(Transform3 *T)
{
  Transform3 t;

  GetViewProjection( &t );
  if(mFlag & F_NEWC2W) {
    mWorldToCam.InverseOf(&mCamToWorld);
    mFlag &= ~F_NEWC2W;
  }
  T->Concat(&mWorldToCam, &t);
}

void MgCamera::RotateX(float angle)
{
  mCamToWorld.CRotateX(angle);
  mFlag |= F_NEWC2W;
}

void MgCamera::RotateY(float angle)
{
  mCamToWorld.CRotateY(angle);
  mFlag |= F_NEWC2W;
}

void MgCamera::RotateZ(float angle)
{
  mCamToWorld.CRotateZ(angle);
  mFlag |= F_NEWC2W;
}

/* translate the camera, using the camera's notion of what space it
   is in */
void MgCamera::Translate(float tx, float ty, float tz)
{
  Transform3 T;

  T.Translate( tx, ty, tz );
  mCamToWorld.Concat(&T, &mCamToWorld);
  mFlag |= F_NEWC2W;
}

/* CamScale is a noop if the camera is not in Euclidean space */
void MgCamera::Scale(float sx, float sy, float sz)
{
  mCamToWorld.CScale( sx, sy, sz );
  mFlag |= F_NEWC2W;
}

void MgCamera::AlignZ(float x, float y, float z)
{
  HPoint3 axis;

  axis.x = x;
  axis.y = y;
  axis.z = z;
  mCamToWorld.CAlignZ(&axis);
  mFlag |= F_NEWC2W;
}

/*
 * Apply T to camera as seen by world (== T^-1 to world, as seen by camera)
 */
void MgCamera::Transform(Transform3 *T)
{
  mCamToWorld.Concat(T, &mCamToWorld);
  mFlag |= F_NEWC2W;
}


/*-----------------------------------------------------------------------
 * Function:    SetHalfField
 * Description: Set camera's "halffield" value
 * Args:        *cam: the camera
 *              halffield: the halffied value to Set to
 * Returns:     nothing
 * Author:      mbp
 * Date:        Wed Aug 21 14:26:43 1991
 * Notes:       This procedure modifies the mHalfYField member of cam
 *              in such a way as to guarantee that the min half-width
 *              of the view window is halffield.  This depends on the
 *              camera's current aspect ratio.
 */
void MgCamera::SetHalfField( double halffield )
{
  mHalfYField =
    (mFrameAspect < 1 && mFrameAspect > 0)
        ? (float)(halffield / mFrameAspect)
        : (float)halffield;
  if(mFlag & F_PERSP)
    mHalfYField *= mFocus;
}

/*-----------------------------------------------------------------------
 * Function:    GetHalfField
 * Description: return camera's "halffield" value
 * Args:        *cam: the camera
 * Returns:     the halffield value
 * Author:      mbp
 * Date:        Wed Aug 21 14:29:31 1991
 * Notes:       the "halffield" is the min half-width of the view
 *              window.  If the aspect ratio is >= 1, this is
 *              the vertical half-width (mHalfYField).  If the aspect
 *              ratio is < 1, this is the horizontal half-width.
 */
double MgCamera::GetHalfField()
{
  double v = mHalfYField;
  if(mFrameAspect < 1) v *= mFrameAspect;
  if(mFlag & F_PERSP) v /= mFocus;
  return v;
}

