#include <stdio.h>
#include "MgOpenGlContext.h"
#include "MgAppearance.h"
#include "MgWindow.h"
#include "GlHeaders.h"
#include "UtException.h"

#include <stdarg.h>

MgOpenGlContext::MgOpenGlContext()
{
  this->Init();
}

//++MgOpenGlContext::ctxdelete [nhpqfohm`duyefmfuf,mgopengl.c]
MgOpenGlContext::~MgOpenGlContext()
{
  vvfree(&(this->mRoom));
}
//--

void MgOpenGlContext::SetDither(DitherValue onoff)
{
  this->mDither = onoff;
}

MgOpenGlContext::DitherValue MgOpenGlContext::GetDither()
{
  return this->mDither;
}



//++MgOpenGlContext::Sync [nhpqfohm`tzod,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::Sync
 * Description: flush buffered GL commands
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:06:09 1991
 * Notes:       Just flushes the GL buffer -- needed for remote displays.
 */
void MgOpenGlContext::Sync( void )
{
  glFlush(());
}
//--


//++MgOpenGlContext::WorldBegin [nhpqfohm`xpsmecfhjo,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::WorldBegin
 * Description: prepare to draw a frame
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:06:58 1991
 */
void MgOpenGlContext::WorldBegin( void )
{
  Transform3 V;
  int which = (mOpts & O_DOUBLEBUFFER) ? DBL : SGL;

  MgContext::WorldBegin();      /* Initialize mW2C, mC2W, mW2S, mS2W, etc. */

  if((mOpts ^ this->mOldOpts) & O_DOUBLEBUFFER) {
    MgOpenGlContext::InitWin();
    this->mOldOpts = mOpts;
  }

  glColorMask((  mOpts & O_NORED ? GL_FALSE : GL_TRUE,
                mOpts & O_NOGREEN ? GL_FALSE : GL_TRUE,
                mOpts & O_NOBLUE ? GL_FALSE : GL_TRUE,
                GL_TRUE ));

  if(this->MgOpenGlContext::mpWin->Changed(MgWindow::F_VIEWPORT))
    MgOpenGlContext::SetViewport();

  /* Erase to background color & initialize z-buffer */
  if (mOpts & O_INHIBITCLEAR) {
        glClearDepth((1.));
        glClear((GL_DEPTH_BUFFER_BIT));
  } else { 
    glClearDepth(( this->mZMax));
    glClearColor(((float)(mBackground.GetRed()),
		  (float)(mBackground.GetGreen()),
		  (float)(mBackground.GetBlue()),
		  (float)(mBackground.GetAlpha())));

    glClear((GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT));

    // texture mapping / bgimage stuff removed from here
  }

  glEnable((GL_DEPTH_TEST));

  glRenderMode((GL_RENDER));

  if(this->mDither) glEnable((GL_DITHER));
  else glDisable((GL_DITHER));

  mHas = 0;

  /* Interpret the camera: load the proper matrices onto the GL matrix
     stacks.  */
  if(!(mOpts & O_INHIBITCAM)) {
      glMatrixMode((GL_PROJECTION));
      mpCam->GetViewProjection(&V);
      glLoadMatrixf(( (GLfloat *) &V));
      glMatrixMode((GL_MODELVIEW));
      glLoadMatrixf(( (GLfloat *) &mW2C));
  }

  /* Bind the lights; do this here so we get lights in world coords. */
  /* Only do this if we're supposed to do lighting */

  if (mAStk.Top()->GetAppearance()->GetShading() != MgAppearance::F_CONSTANT)
    Lights(mAStk.Top()->GetAppearance()->GetLighting()->GetLightList(),
           mAStk.Top());
}
//--


//++MgOpenGlContext::WorldEnd [nhpqfohm`xpsmefoe,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::WorldEnd
 * Description: finish drawing a frame
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:08:02 1991
 */
void MgOpenGlContext::WorldEnd( void )
{
  glFlush(());
  if((mOpts&O_DOUBLEBUFFER) && !(mOpts&O_INHIBITSWAP)) {
    mpWin->SwapBuffers();
  }
}
//--


//++MgOpenGlContext::ReshapeViewport [nhpqfohm`sftibqfwjfxqpsu,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::ReshapeViewport
 * Description: adjust to a new window size
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:08:30 1991
 * Notes:       adjusts both GL's internal viewport Setting, as well as
 *              MgContext context MgWindow's current position and camera's
 *              aspect ratio.
 */
void MgOpenGlContext::ReshapeViewport( void )
{
//  long w, h;
  double pixasp = 1.0;
  MgWindow::Position vp;

  mpWin->GetPixelAspect(&pixasp);
  mpWin->GetViewport(&vp);
  MgOpenGlContext::SetViewport();
  mpCam->SetAspectRatio(pixasp * (double)(vp.p_XMax-vp.p_XMin+1) /
                                     (double)(vp.p_YMax-vp.p_YMin+1));
}
//--


//++MgOpenGlContext::SetTransform [nhpqfohm`tfuusbotgpsn,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::SetTransform
 * Description: Set the current object xform to T
 * Args:        T
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:29:43 1991
 * Notes:       We use the GL ModelView matrix stack, not the mgcontext's
 *              stack.  This means we must first load mW2C onto the
 *              modelview stact, then premult by T.
 *
 *              This assumes we're already in GL_MODELVIEW mode.
				  */
void MgOpenGlContext::SetTransform( Transform3 *T )
{
  glLoadMatrixf(( (GLfloat *) &mW2C));
  glMultMatrixf(( (GLfloat *) T));
  mXStk.Top()->p_mT.Copy(T);
  mHas = mXStk.Top()->p_mHasInv = 0;
}
//--


//++MgOpenGlContext::GetTransform [nhpqfohm`hfuusbotgpsn,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::GetTransform
 * Description: get the current object xform
 * Args:        T: place to write the current object xform
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:29:43 1991
 * Notes:       We use the GL ModelView matrix stack, not the mgcontext's
 *              stack.  This means we must multiply on the right by
 *              the current mC2W matrix after reading the GL ModelView
 *              matrix.
 *
 *              This assumes we're already in GL_MODELVIEW mode.
 */
void MgOpenGlContext::GetTransform( Transform3 *T )
{
  T->Copy(&mXStk.Top()->p_mT);
}
//--


//++MgOpenGlContext::Identity [nhpqfohm`jefoujuz,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::Identity
 * Description: Set the current object xform to Identity
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:23:48 1991
 * Notes:       We use the GL ModelView matrix stack, not the mgcontext's
 *              stack.
 *
 *              This assumes we're already in GL_MODELVIEW mode.
 */
void MgOpenGlContext::Identity( void )
{
  /* [ obj xform ] = identity corresponds to having current mW2C on
     ModelView stack */
  MgOpenGlContext::SetTransform( &Transform3::IDENTITY );

}
//--


//++MgOpenGlContext::Transform [nhpqfohm`usbotgpsn,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::Transform
 * Description: premultiply the object xform by T
 * Args:        T
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:24:57 1991
 * Notes:       We use the GL ModelView matrix stack, not the mgcontext's
 *              stack.
 *
 *              This assumes we're already in GL_MODELVIEW mode.
 */
void MgOpenGlContext::Transform( Transform3 *T )
{
  glMultMatrixf(( (GLfloat *) (T)));
  mXStk.Top()->p_mT.Concat(T, &mXStk.Top()->p_mT);
  mHas = mXStk.Top()->p_mHasInv = 0;
}
//--


//++MgOpenGlContext::PushTransform [nhpqfohm`qvtiusbotgpsn,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::PushTransform
 * Description: push the object xform stack
 * Returns:     nothing (???)
 * Author:      mbp
 * Date:        Fri Sep 20 12:25:43 1991
 * Notes:       We use the GL ModelView matrix stack, not the mgcontext's
 *              stack.
 *
 *              This assumes we're already in GL_MODELVIEW mode.
 */
void MgOpenGlContext::PushTransform( void )
{
  glPushMatrix(());
  MgContext::PushTransform();
}
//--


//++MgOpenGlContext::PopTransform [nhpqfohm`qpqusbotgpsn,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    mgopengl_popransform
 * Description: pop the object xform stack
 * Returns:     nothing (???)
 * Author:      mbp
 * Date:        Fri Sep 20 12:25:43 1991
 * Notes:       We use the GL ModelView matrix stack, not the mgcontext's
 *              stack.
 *
 *              This assumes we're already in GL_MODELVIEW mode.
 */
void MgOpenGlContext::PopTransform( void )
{
  glPopMatrix(());
  MgContext::PopTransform();
}
//--


//++MgOpenGlContext::PushAppearance [nhpqfohm`qvtibqqfbsbodf,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::PushAppearance
 * Description: push the MgContext context appearance stack
 * Returns:     nothing
 * Author:      mbp
 * Date:        Fri Sep 20 12:54:19 1991
 */
void MgOpenGlContext::PushAppearance( void )
{
  MgContext::PushAppearance();
}
//--

void MgOpenGlContext::PopAppearance( void )
{
    //register AppearanceStackNode *mastk = mAStk.Top();
    register MgAppearanceStackNode *top = mAStk.Top();

    if (mAStk.Depth() < 2) {
        throw new UtException(UtException::ERROR,
     "MgOpenGlContext::PopAppearance: appearance stack has only 1 entry.");
    }

    //register AppearanceStackNode *mastk_next = mAStk.Second();
    register MgAppearanceStackNode *second = mAStk.Second();

    if ( ( (top->GetLightingSeq() != second->GetLightingSeq())
           // lighting changed
#ifndef TRUE_EMISSION
           || ( (        top->GetAppearance()->GetFrontMaterial()->GetValid()
                         ^ second->GetAppearance()->GetFrontMaterial()->GetValid() )
                & MgMaterial::F_EMISSION )
           // GL_LIGHT_MODEL_TWO_SIDE changed
#endif
           )
         && second->GetAppearance()->HasShading() )
    {
        // lighting on
        Lighting(second,
                 second->GetAppearance()->GetLighting()->GetValid());
    }
    Appearance(second,
               second->GetAppearance()->GetFrontMaterial()->GetValid());

    MgContext::PopAppearance();
}


void MgOpenGlContext::MergeAppearance( MgAppearance* ap )
{
  static float nullarray[] = { 0.0 };
  int changed, mat_changed, lng_changed;
  //AppearanceStackNode *mastk = mAStk.Top();
  MgAppearanceStackNode *top = mAStk.Top();
  MgAppearance *topAp = top->GetAppearance();

  // Decide what changes
  changed =ap->GetValid() &~ (topAp->GetOverride() &~ ap->GetOverride());

  mat_changed =
      ap->GetFrontMaterial()
      ?    ap->GetFrontMaterial()->GetValid()
        &~ ( topAp->GetFrontMaterial()->GetOverride()
             &~ ap->GetFrontMaterial()->GetOverride() )
      : 0;

    lng_changed =
      ap->GetLighting()
        ? ap->GetLighting()->GetValid()
          &~ ( topAp->GetLighting()->GetOverride()
               &~ ap->GetLighting()->GetOverride() )
        : 0;


  /*
   * Update current appearance; this needs to be done before making GL
   * calls because it is conceivable that we might need to make a GL call
   * corresponding to something in the current appearance for which the
   * valid bit in *ap isn't Set. (???)  By updating the current
   * appearance before making GL calls, our GL calls can always take data
   * from the current appearance, rather than worrying about whether to
   * read *ap or the current appearance.
   */
  MgContext::MergeAppearance( ap );

  /* Bring GL device into accord with new appearance */
  if (this->mBorn) {

    /*
     * No bit in "changed" corresponds to {lighting,mat}.  We think of
     * ap->{lighting,mat} as an extension to *ap which is interpreted to
     * have all valid bits 0 if the {lighting,ap} pointer is NULL.  Note
     * that this means there is no way for the parent to override the
     * entire {lighting,mat} structure as a whole.  It can, however, Set
     * the individual override bits in the {lighting,mat} structure.
     */
      //AppearanceStackNode *mastk_next = mAStk.Second();
      MgAppearanceStackNode *second = mAStk.Second();
    if ((ap->GetLighting()) && (second)) {
      if (top->GetLightingSeq() == second->GetLightingSeq()) {
          top->LightingSeqIncr();
        /*
         * We need a new lighting model.
         * To ensure we don't have any leftover garbage in GL's copy of this
         * lighting model, we force GL to reSet to defaults, then
         * reinitialize everything.
         */

        glNewList(( top->GetLightingSeq(), GL_COMPILE));
        glMaterialf((GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, * nullarray));
        glEndList(());;
        lng_changed |= topAp->GetLighting()->GetValid();   /* "All fields changed" */
      }
    }
    if (topAp->GetShading() != MgAppearance::F_CONSTANT &&
                (ap->GetLighting() != NULL 
#ifndef TRUE_EMISSION
        /* Hack: must enable GL_LIGHT_MODEL_TWO_SIDE lighting if so */
                || (second && 
                    (top->GetAppearance()->GetFrontMaterial()->GetValid()
                     ^ second->GetAppearance()->GetFrontMaterial()->GetValid())
                    & MgMaterial::F_EMISSION)
#endif
                                        )) {
      MgOpenGlContext::Lighting( top, lng_changed );
    }

        /* Let MgOpenGlContext::material() decide if we need a new material */
    if (ap->GetFrontMaterial())
      MgOpenGlContext::Material( top, mat_changed );

    MgOpenGlContext::Appearance( top, changed );

  }
}

//++MgOpenGlContext::GetAppearance [nhpqfohm`hfubqqfbsbodf,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::GetAppearance
 * Description: return a ptr to current appearance
 * Returns:     ptr to current appearance
 * Author:      mbp
 * Date:        Fri Sep 20 13:00:41 1991
 * Notes:       Applications should not modify the returned appearance
 *              in any way.
 */
MgAppearance * MgOpenGlContext::GetAppearance()
{
    return mAStk.Top()->GetAppearance();
}
//--

void MgOpenGlContext::SetZNudge(double znudge)
{
  MgContext::SetZNudge(znudge);
  mZFNudge = (float)znudge;
  if (this->mBorn) MgOpenGlContext::InitZRange();
}

int MgOpenGlContext::GetBitDepth()
{
  // ?? mbp Mon Apr 14 11:46:47 1997
  return 24;
}

void MgOpenGlContext::SetGlWinID(int id)
{
  this->mGlWinId = id;
}

int MgOpenGlContext::GetGlWinID()
{
  return this->mGlWinId;
}

int MgOpenGlContext::IsBorn()
{
  return this->mBorn;
}

int MgOpenGlContext::GetZMax()
{
  return((int)(this->mZMax));
}

//++MgOpenGlContext::InitWin [nhpqfohm`jojuxjo,mgopengl.c]
void MgOpenGlContext::InitWin()
{
//  MgWindow::Position pos, vp;
//  int xsize, ysize, flag;
  GLdouble zrange[2];
//  char *name;
//  char gver[80];
  //  MgLight *l;

  glEnable((GL_DEPTH_TEST));
  glEnable((GL_NORMALIZE));
  glMatrixMode((GL_PROJECTION));
  glLoadMatrixf(((GLfloat *)&Transform3::IDENTITY));
  glMatrixMode((GL_MODELVIEW));

  this->mOldOpts = mOpts;
  this->mBorn = 1;

  glGetDoublev((GL_DEPTH_RANGE, zrange));
  this->mZMin = zrange[0]; this->mZMax = zrange[1];
  MgOpenGlContext::InitZRange();

  glClearDepth((this->mZMax));
  glClearColor(((float)(mBackground.GetRed()),
               (float)(mBackground.GetGreen()),
               (float)(mBackground.GetBlue()),
               (float)(mBackground.GetAlpha())));
  glClear((GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT));

  if((mOpts&O_DOUBLEBUFFER) && !(mOpts&O_INHIBITSWAP) ) {
    mpWin->SwapBuffers();
  }

  MgOpenGlContext::SetViewport();

  /* Ensure the lighting gets properly entered into this new window --
   * mark all lights as having changed.
   */
  MgLightListIter
      it(*(mAStk.Top()->GetAppearance()->GetLighting()->GetLightList()));
  MgLight *light;
  for( ; it; ++it)
  {
      light = it();
      light->SetChanged(1);
  }


#if 0
  // Kludge: create an empty appearance and merge it onto the
  // appearance stack; the call to MergeAppearance forces
  // the proper GL calls to bring GL into sync with the
  // stack's base appearance.  Maybe find a more direct
  // way to do this later. mbp Thu Dec 18 14:00:22 1997.
  MgAppearance *starterAp = new MgAppearance();
  MgOpenGlContext::MergeAppearance( starterAp );
  ::DeleteRef(starterAp);
#endif

  MgAppearanceStackNode *top = mAStk.Top();
  MgAppearance *topAp = top->GetAppearance();
  Lighting( top, topAp->GetLighting()->GetValid() );
  Material( top, topAp->GetFrontMaterial()->GetValid() );
  Appearance( top, topAp->GetValid()  );

}
//--

// mbp-purify: completed & rearranged this function
//++MgOpenGlContext::Init [nhpqfohm`ofxdpoufyu,mgopengl.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::Init
 * Description: initialize a new MgOpenGlContext object
 * Returns:     ctx
 * Author:      mbp
 * Date:        Fri Sep 20 13:11:03 1991
 */
void MgOpenGlContext::Init()
{
  mTessPlFlags = 0;
  mZMin =  mZMax = 0.0f;
  mIsPI = 0;
  mTurbo = 0;
  mZNudge = 0.0f;
  mZNear = mZFar = 0.0f;
  mGlWinId = 0;
  mZFNudge = (float)(40.e-6);
  mBorn = 0;
  mFlipNormals = 0;
  mConstantShading = 0;
  mLmColor = GL_DIFFUSE;
  VVINIT(mRoom, char, 180);
  mShouldLighting = mIsLighting = 0;
  mDither = DITHER_ON;
  mKd = 1.0;
  mOldOpts = 0;
}
//--


//++MgOpenGlContext::SetViewport [nhpqfohm`tfuwjfxqpsu,mgopengl.c]
void MgOpenGlContext::SetViewport()
{
  MgWindow::Position vp, whole;

  mpWin->GetViewport(&vp);
  glViewport((vp.p_XMin, vp.p_YMin, vp.p_XMax-vp.p_XMin+1, vp.p_YMax-vp.p_YMin+1));
  glScissor((vp.p_XMin, vp.p_YMin, vp.p_XMax-vp.p_XMin+1, vp.p_YMax-vp.p_YMin+1));

  if  (    !mpWin->GetCurrentPosition(&whole)
        || vp.p_XMax-vp.p_XMin < whole.p_XMax-whole.p_XMin
        || vp.p_YMax-vp.p_YMin < whole.p_YMax-whole.p_YMin ) {
        glEnable((GL_SCISSOR_TEST));
  } else {
        glDisable((GL_SCISSOR_TEST));
  }
  mpWin->ClearChangedBit(MgWindow::F_VIEWPORT);
}
//--

//++MgOpenGlContext::D4f [nhpqfohm`e5g,mgopenglshade.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::D4f
 * Description: wrapper for c4f
 * Args:        c:
 * Returns:     
 * Author:      munzner
 * Date:        Wed Sep 18 21:48:08 1991
 * Notes:       We must multiply by kd (diffuse coefficient of the material)
 *              since we called glColorMgMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);glEnable(GL_COLOR_MATERIAL) earlier in MgOpenGlContext::material
 *              so we're overwriting the diffuse material with every
 *              c4f call.
 */
void MgOpenGlContext::D4f(MgColorA *color)
{
  float d[4];
  float factor = mConstantShading ? 1 : mKd;
  d[0] = (float)(color->GetRed() * factor);
  d[1] = (float)(color->GetGreen() * factor);
  d[2] = (float)(color->GetBlue() * factor);
  d[3] = (float)(color->GetAlpha());
  if (!mConstantShading &&
    (mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetValid()
     & MgMaterial::F_ALPHA &&
     mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetOverride(MgMaterial::F_ALPHA))) {
    d[3] = (float)(mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetDiffuse()->GetAlpha());
  }
  glColor4fv((d));
}
//--
