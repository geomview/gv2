#include "MgContext.h"
//#include "MgMerge.h"
#include <memory.h>
#include <assert.h>

void MgContext::SetWinchFunc(MgWinchFunc func, void *data)
{
  mpWinChange = func;
  mpWinChangeInfo = data;
}
   
int MgContext::GetBitDepth()
{
  // ?? mbp Mon Apr 14 11:46:47 1997
  return 0;
}


void MgContext::SetZNudge(double znudge)
{
  mZFNudge = (float)znudge;
}

double MgContext::GetZNudge()
{
  return mZFNudge;
}

int MgContext::GetOptions()
{
  return mOpts;
}

void MgContext::SetBackgroundColor(MgColorA color)
{
  mBackground = color;
}

MgColorA MgContext::GetBackgroundColor()
{
  return mBackground;
}

void MgContext::SetOptions(int mask)
{
  mOpts |= mask;
}

void MgContext::UnsetOptions(int mask)
{
  mOpts &= mask;
}

void MgContext::SetWindow(MgWindow *win)
{
//  int xsize, ysize, flag, reconstrain;
  int positioned = 0;
//  char *name, *oname;

  assert(win != NULL);

  if(win != mpWin) {
    if (mpWin) {
      ::DeleteRef(mpWin);
    }
    mpWin = ::NewRef(win);
  }
}


MgWindow * MgContext::GetWindow()
{
  return mpWin;
}


MgContext::MgContext()
{
  this->Init();
}

//++MgContext::~MgContext [nh`duyefmfuf,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::~MgContext
 * Description: MgContext destructor
 */
MgContext::~MgContext()
{
  if(mpWinChange)
    (*mpWinChange)(this, mpWinChangeInfo, W_WINDELETE, mpWin);

  ::DeleteRef(mpWin);
  ::DeleteRef(mpCam);           // mbp-purify: added this line
}
//--


//++MgContext::Sync [nh`tzod,mg.c]
void MgContext::Sync( void )
{}
//--


//++MgContext::WorldBegin [nh`xpsmecfhjo,mg.c]
void MgContext::WorldBegin( void )
{
  Transform3 S, V;
  MgWindow::Position vp;

  mChanged |= C_USED;
  mpCam->GetW2C(&mW2C);
  mpCam->GetC2W(&mC2W);
  mpCam->GetView((Transform3*)&V);
  mpWin->GetViewport(&vp);
        /* V maps world to [-1..1],[-1..1],[-1..1] */
  S.Translate(1.0f, 1.0f, 0.0f);
  V.Concat(&V, &S); // now maps to [0..2],[0..2],[-1..1]
  S.Scale((float)(.5*(vp.p_XMax-vp.p_XMin+1)), (float)(.5*(vp.p_YMax-vp.p_YMin+1)), 1.);
                        /* now maps to [0..xsize],[0..ysize],[-1..1] */
  mW2S.Concat(&V, &S);  // final world-to-screen matrix
  mS2W.InverseOf(&mW2S);      // and screen-to-world
  mO2S.Copy(&mW2S);
  mS2O.Copy(&mS2W);
  mXStk.Top()->p_mT.Identity();
  mXStk.Top()->p_mHasInv = 0;
  mHas |= HAS_mS2O;
  MgContext::GlobalLights(GetAppearance()->GetLighting()->GetLightList(), 1);
}
//--


//++MgContext::WorldEnd [nh`xpsmefoe,mg.c]
void MgContext::WorldEnd( void )
{}
//--


//++MgContext::ReshapeViewport [nh`sftibqfwjfxqpsu,mg.c]
void MgContext::ReshapeViewport( void )
{}
//--


//++MgContext::SetTransform [nh`tfuusbotgpsn,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::SetTransform
 * Description: Set the current object xform
 * Args:        T
 * Returns:     nothing
 * Author:      slevy (doc by mbp)
 * Date:        Wed Sep 18 16:46:06 1991
 * Notes:       Sets the xform on the top of the current context's xform
 *              stack to T.  Also Sets the C_TRANS bit of
 *              the context's "changed" flag and increment's the current xfm
 *              sequence number.
 * DEVICE USE:  optional --- if the device actually uses the context
 *              structure's xform stack, call this to do the work.  If
 *              the device keeps its own stack, it doesn't have to call
 *              this.
 */
void MgContext::SetTransform( Transform3 *T )
{
  mXStk.Top()->p_mT.Copy(T);
  mChanged |= C_TRANS;
  mXStk.Top()->p_mXfmSeq++;
}
//--


//++MgContext::GetTransform [nh`hfuusbotgpsn,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::GetTransform
 * Description: Get the current object xform
 * Args:        T
 * Returns:     nothing
 * Author:      slevy (doc by mbp)
 * Date:        Wed Sep 18 16:46:06 1991
 * Notes:       Writes the current object xform, from the top of the
 *              context's xform stack, into T.
 * DEVICE USE:  optional --- if the device actually uses the context
 *              structure's xform stack, call this to do the work.  If
 *              the device keeps its own stack, it doesn't have to call
 *              this.
 */
void MgContext::GetTransform( Transform3 *T )
{
  T->Copy(&mXStk.Top()->p_mT);
}
//--


//++MgContext::Identity [nh`jefoujuz,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::Identity
 * Description: Set the current object xform to the Identity
 * Args:        (none)
 * Returns:     nothing
 * Author:      slevy (doc by mbp)
 * Date:        Wed Sep 18 16:46:06 1991
 * Notes:       Sets the xform on the top of the current context's xform
 *              stack to the identity.  Also Sets the C_TRANS bit of
 *              the context's "changed" flag and increment's the current xfm
 *              sequence number.
 * DEVICE USE:  optional --- if the device actually uses the context
 *              structure's xform stack, call this to do the work.  If
 *              the device keeps its own stack, it doesn't have to call
 *              this.
 */
void MgContext::Identity( void )
{
  mXStk.Top()->p_mT.Identity();
  mChanged |= C_TRANS;
  mXStk.Top()->p_mXfmSeq++;
}
//--


//++MgContext::Transform [nh`usbotgpsn,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::Transform
 * Description: premultiply the current object xform by a transform
 * Args:        T: the transform to premultiply by
 * Returns:     nothing
 * Author:      slevy (doc by mbp)
 * Date:        Wed Sep 18 16:46:06 1991
 * Notes:       If X is the context's current object xform, replaces X
 *              by T X.
 * DEVICE USE:  optional --- if the device actually uses the context
 *              structure's xform stack, call this to do the work.  If
 *              the device keeps its own stack, it doesn't have to call
 *              this.
 */
void MgContext::Transform( Transform3 *T )
{
  mXStk.Top()->p_mT.Concat(T, &mXStk.Top()->p_mT);
  mChanged |= C_TRANS;
  mXStk.Top()->p_mXfmSeq++;
  mXStk.Top()->p_mHasInv = 0;
  mHas = 0;
}
//--


//++MgContext::PushTransform [nh`qvtiusbotgpsn,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::PushTransform
 * Description: push the context xform stack
 * Returns:     nothing
 * Author:      mbp
 * Date:        Thu Sep 19 12:23:26 1991
 * DEVICE USE:  optional --- use if device actually uses our stack
 */
void MgContext::PushTransform( void )
{
  TransformStackNode *oldTop, *newTop;

  oldTop = mXStk.Top();
  newTop = mXStk.Push();
  *newTop = *oldTop;

#if 0
  // pred-UtLStack version
  register struct mgxstk *xfm;
  if(mgxfree) xfm = mgxfree, mgxfree = xfm->mpNext;
  else xfm = OOGLNewE(struct mgxstk, "mgpushTransform");
  *xfm = *mXStk;
  xfm->mpNext = mXStk;
  mXStk = xfm;
#endif
}
//--


//++MgContext::PopTransform [nh`qpqusbotgpsn,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::PopTransform
 * Description: pop the context xform stack
 * Returns:     nothing
 * Author:      mbp
 * Date:        Thu Sep 19 12:23:51 1991
 * DEVICE USE:  optional --- use if device actually uses our stack
 */
void MgContext::PopTransform( void )
{
  mXStk.Pop();

#if 0
  // pre-UtLStack version:
  register struct mgxstk *xfm = mXStk;
  if(xfm->mpNext == NULL)
    return;
  mXStk = xfm->mpNext;
  xfm->mpNext = mgxfree;
  mgxfree = xfm;
  mHas = 0;
#endif
}
//--

void MgContext::PushAppearance()
{
    mAStk.Push();
}

void MgContext::PopAppearance()
{
    mAStk.Pop();
}


void MgContext::MergeAppearance(MgAppearance *ap)
{
    mAStk.Merge(ap);
    GlobalLights(GetAppearance()->GetLighting()->GetLightList(), 0);
}

//++MgContext::SetCamera [nh`tfudbnfsb,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::SetCamera
 * Description: Set the context's camera
 * Args:        *cam: the camera to use
 * Returns:     nothing
 * Author:      slevy (doc by mbp)
 * Date:        Thu Sep 19 11:16:46 1991
 * Notes:       The context does not maintain an internal copy of the
 *              camera.  Only the pointer is stored.
 * DEVICE USE:  required
 */
void MgContext::SetCamera( MgCamera *cam )
{
  if (mpCam) ::DeleteRef(mpCam);
  mpCam = ::NewRef(cam);
  mChanged |= C_CAM;
}
//--


//++MgContext::Polygon [nh`qpmzhpo,mg.c]
void MgContext::Polygon( int nv, HPoint3 *v, int nn, Point3 *n, int nc,MgColorA *c )
{}
//--


//++MgContext::Polylist [nh`qpmzmjtu,mg.c]
void MgContext::Polylist(int np, struct Poly *p, int nv, struct Vertex *v, int plflags)
{}
//--


//++MgContext::Mesh [nh`nfti,mg.c]
void MgContext::Mesh(int wrap,
              int nu,
              int nv,
              HPoint3 *p,
              Point3 *n,
              MgColorA *c,
              Point3 *str)
{}
//--


//++MgContext::Line [nh`mjof,mg.c]
void MgContext::Line( HPoint3 *p1, HPoint3 *p2 )
{}
//--


//++MgContext::Polyline [nh`qpmzmjof,mg.c]
void MgContext::Polyline( int nv, HPoint3 *verts, int nc, MgColorA *colors, int wrapped )
{}
//--


//++MgContext::Quads [nh`rvbet,mg.c]
void MgContext::Quads( int nquads, HPoint3 *verts, Point3 *normals, MgColorA *colors )
{
    int i;
    HPoint3 *v = verts;
    Point3 *n = normals;
    MgColorA *c = colors;
    int dn = normals ? 4 : 0;
    int dc = colors ? 4 : 0;

    for(i = 0; i < nquads; i++, v += 4, n += dn, c += dc)
        Polygon(4, v, dn, n, dc, c);
}
//--


//++MgContext::Bezier [nh`cf{jfs,mg.c]
void MgContext::Bezier(int du, int dv, int dimn, float *ctrlpts, float *txmapst, MgColorA *c)
{}
//--

//++MgContext::FindO2S [nh`gjoeP3T,mg.c]
void MgContext::FindO2S()
{
  mO2S.Concat(&mXStk.Top()->p_mT, &mW2S);
}
//--


//++MgContext::FindS2O [nh`gjoeT3P,mg.c]
void MgContext::FindS2O()
{
  if(!(mHas & HAS_mS2O)) {
    if(!mXStk.Top()->p_mHasInv) {
      mXStk.Top()->p_mTinv.InverseOf(&mXStk.Top()->p_mT);
      mXStk.Top()->p_mHasInv = 1;
    }
    mS2O.Concat(&mS2W, &mXStk.Top()->p_mTinv);
    mO2S.Concat(&mXStk.Top()->p_mT, &mW2S);
    mHas |= HAS_mS2O;
  }
}
//--


//++MgContext::FindCam [nh`gjoedbn,mg.c]
/*
 * FindCam() updates the following fields in the current
 *  mgcontext:
 *      mCPos = p * Tinv
 *      mCamZ = d * Tinv
 *      mHas |= HAS_CPOS
 *  where
 *      p = 4th row of current C2W matrix (i.e. position of camera)
 *      d = 4th row of current C2W matrix (i.e. Z directory of camera)
 *      Tinv = inverse of current transform (top of transform stack)
 */
void MgContext::FindCam()
{
  HPoint3 camZ;
  /*
   * Figure out where the camera is in the current coordinate system
   */
  if(!mXStk.Top()->p_mHasInv) {
    mXStk.Top()->p_mTinv.InverseOf(&mXStk.Top()->p_mT);
    mXStk.Top()->p_mHasInv = 1;
  }

  mXStk.Top()->p_mTinv.HPoint3TransformToPoint3((HPoint3*)(&mC2W.D.M[3][0]),
                                                    &mCPos);

  mXStk.Top()->p_mTinv.HPoint3Transform((HPoint3*)(&mC2W.D.M[2][0]),
                                           &camZ);

  camZ.w = ((Point3 *)&camZ)->Length();
  HPoint3::toPoint3(&camZ, &mCamZ);
  mHas |= HAS_CPOS;
}
//--


//++MgContext::GlobalLights [nh`hmpcbmmjhiut,mg.c]
/*
 * Transform light(s) to global coordinate system, if they aren't already.
 * Transforms them in place; this is safe, since mg keeps a private copy of
 * the light structures.
 */
void MgContext::GlobalLights( MgLightList *lightList, int WorldBegin )
  //
  // This really ought to be an MgLight function !!
  //   move it over there soon
  //   mbp Mon May 05 10:25:33 1997
  //
{
    MgLight *lt;
    HPoint3 oldpos, p, gp;

    MgLightListIter it(*lightList);

    for( ; it; ++it) {
        lt = it();
        oldpos = lt->GetGlobalPosition();
        switch(lt->GetPositionType()) {
        case MgLight::F_GLOBAL:
          lt->SetGlobalPosition(lt->GetPosition());
          break;
        case MgLight::F_CAMERA:
          // HPt3Transform(mC2W, &lt->position, &lt->globalposition);
          p = lt->GetPosition();
          mC2W.HPoint3Transform(&p, &gp);
          lt->SetGlobalPosition(gp);
        break;
        case MgLight::F_LOCAL:
          p = lt->GetPosition();
          mXStk.Top()->p_mT.HPoint3Transform(&p, &p);

          lt->SetPosition(p, MgLight::F_GLOBAL);
          lt->SetGlobalPosition(p);
          break;
        }
        p = lt->GetGlobalPosition();
        if(memcmp(&oldpos, &p, sizeof(HPoint3)) != 0) {
          lt->SetChanged(1);
        }
    }
}
//--


//++MgContext::MakePoint [nh`nblfqpjou,mg.c]
/* Construct a prototype polygonal outline for creating fat points.
 * Curiously, we can do this independently of the position of the point,
 * if we operate in homogeneous space.
 */
void MgContext::MakePoint()
{
  int i, n;
  float t, r, c, s;
  register HPoint3 *p;
  static float nsides = 3.0;

  if(!(mHas & HAS_mS2O))
    MgContext::FindS2O();

  int lineWidth = GetAppearance()->GetLineWidth();
  if(lineWidth <= 3) n = 4;
  else n = (int)(nsides * sqrt((double)lineWidth));
  vvneeds(&mPointVvec, n);
  VVCOUNT(mPointVvec) = n;
  r = (float)(.5 * lineWidth);
  for(i = 0, p = VVEC(mPointVvec, HPoint3);  i < n;  i++, p++) {
    t = (float)(2*M_PI*i/n); s = (float)(r * sin(t)); c = (float)(r * cos(t));
    p->x = mS2O.D.M[0][0]*c + mS2O.D.M[1][0]*s;
    p->y = mS2O.D.M[0][1]*c + mS2O.D.M[1][1]*s;
    p->z = mS2O.D.M[0][2]*c + mS2O.D.M[1][2]*s;
    p->w = mS2O.D.M[0][3]*c + mS2O.D.M[1][3]*s;
  }
  mHas |= HAS_POINT;
}
//--


// mbp-purify:  rearranged and completed this function
//++MgContext::Init [nh`ofxdpoufyu,mg.c]
/*-----------------------------------------------------------------------
 * Function:    MgContext::Init
 * Description: initialize an MgContext instance
 */
void MgContext::Init()
{
  // memSet(this, 0, sizeof(MgContext));
  mEuck1 = 0.0f;
  mEuck2 = 0.0f;
  mFog = 0.0f;
  mHypk1 = 0.0f;
  mHypk2 = 0.0f;
  mSphk1 = 0.0f;
  mSphk2 = 0.0f;
  mChanged = 0;
  mpParent = NULL;
  mpNext = NULL;
  mZFNudge = 0.0f;
  mHas = 0;
  mShown = 1;
  mpWin = new MgWindow;
  mpWin->SetTitle("MG WINDOW <no title>");
  mpCam = new MgCamera;
  mBackground.SetRGBA(0.0, 0.0, 0.0, 1.0);

  register TransformStackNode *mx = mXStk.Push();
  mx->p_mT.Identity();
  mx->p_mXfmSeq = mx->p_mHasInv = 0;

  mOpts = O_HIDDEN|O_DOUBLEBUFFER;

  mW2C.Identity();  mC2W.Identity();
  mW2S.Identity();  mS2W.Identity();
  mO2S.Identity();  mS2O.Identity();
  mT4.Identity();

  mT4Seq = 0;

  VVINIT(mPointVvec, HPoint3, 7);

  mCPos.Zero();
  mCamZ.Zero();

  mpWinChange = NULL;
  mpWinChangeInfo = NULL;

}
//--


//++MgContext::Get4to3 [nhhfu5up4,mg.c]
int MgContext::Get4to3( Transform3 *T )
{
  T->Copy(&mT4);
  return mT4Seq;
}
//--


//++MgContext::Set4to3 [nhtfu5up4,mg.c]
/*
 * Handle 4D->3D transform
 * This allows the drawing routines to compute normals on 4D objects
 * by knowing how they'll appear in 3D, and also to know whether
 * the calculation must be redone (because the 4D->3D transform changed
 * since the normals were last computed).  This transform doesn't really
 * belong in the mg state, but the drawing routines need it, so this is the
 * natural place to put the data.
 */
void MgContext::Set4to3( Transform3 *T, int seq )
{
  mT4.Copy(T);
  mT4Seq = seq;
}
//--
