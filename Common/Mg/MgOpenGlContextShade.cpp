#include "MgOpenGlContext.h"
#include "GlHeaders.h"

#define ID_OFFSET 100

//++MgOpenGlContext::N3fEvert [nhpqfohm`o4gfwfsu,mgopenglshade.c]
void MgOpenGlContext::N3fEvert(register Point3 *n, register HPoint3 *p)
{
  Point3 tn;
  register Point3 *cp;
  
  if(!(mHas & HAS_CPOS))
    MgContext::FindCam();
  cp = &mCPos;
  if( (p->x-cp->x) * n->x + (p->y-cp->y) * n->y + (p->z-cp->z) * n->z > 0) {
    tn.x = -n->x;
    tn.y = -n->y;
    tn.z = -n->z;
    glNormal3fv(((float *)&tn));
  } else {
    glNormal3fv(((float *)n));
  }
}
//--

//++MgOpenGlContext::Appearance [nhpqfohm`bqqfbsbodf,mgopenglshade.c]
//void MgOpenGlContext::Appearance( AppearanceStackNode *ma, int mask )
void MgOpenGlContext::Appearance( MgAppearanceStackNode *node, int mask )
{
  MgAppearance *ap = node->GetAppearance();

  if (mask & MgAppearance::F_TRANSPARENCY) {
    if (ap->GetFlags() & MgAppearance::F_TRANSPARENCY) {
      glDepthMask((GL_FALSE));
      glBlendFunc((GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA));
      if((GL_SRC_ALPHA) == GL_ONE && ( GL_ONE_MINUS_SRC_ALPHA) == GL_ZERO)
        glDisable((GL_BLEND));
      else
        glEnable((GL_BLEND));
    } else {
      glDepthMask((GL_TRUE));
      glBlendFunc((GL_ONE,  GL_ZERO));
      if((GL_ONE) == GL_ONE && ( GL_ZERO) == GL_ZERO)
        glDisable((GL_BLEND));
      else
        glEnable((GL_BLEND));
    }
  }

  if (mask & MgAppearance::F_LINEWIDTH) {
    glLineWidth(((GLfloat)(ap->GetLineWidth())));
    mHas &= ~HAS_POINT;
  }

  if (mask & MgAppearance::F_BACKCULL) {
    if(ap->GetFlags() & MgAppearance::F_BACKCULL) {
        glEnable(( GL_CULL_FACE ));
    } else {
        glDisable(( GL_CULL_FACE ));
    }
  }


  if (mask & MgAppearance::F_SHADING) {
    if(!ap->HasShading()) {
        /* switch to constant shading by unbinding the lmodel */

        glDisable((GL_LIGHTING));
        this->mShouldLighting = this->mIsLighting = 0;

        this->mConstantShading = 0;
        //  this->D4f = MgOpenGlC4f;
        this->mLmColor = GL_DIFFUSE;

        glShadeModel((ap->HasSmoothShading() ? GL_SMOOTH : GL_FLAT ));
    }
    else {
        /* turn shading on */
        glEnable((GL_LIGHTING));
        this->mShouldLighting = this->mIsLighting = 1;

        glShadeModel((ap->HasSmoothShading() ? GL_SMOOTH : GL_FLAT ));

        if (ap->GetLighting()->GetValid())
            glCallList((node->GetLightingSeq()));
        glCallList((node->GetMaterialSeq()));

#ifndef TRUE_EMISSION
        if(node->GetMaterialSeq() > 1)
            glCallList((node->GetMaterialSeq()-1));
#endif
        this->mConstantShading = 1;
        this->mLmColor = GL_DIFFUSE;
    }
  }

  if(mask & MgAppearance::F_EVERT) {
    /*
     * Do automatic normal-flipping if requested.
     */
    this->mFlipNormals = (ap->GetFlags() & MgAppearance::F_EVERT);
  }
 
  /*
   * No GL calls are needed for the following attributes because
   * they are always interpreted at draw-time:
   *            MgAppearance::F_FACEDRAW
   *            MgAppearance::F_EDGEDRAW
   *            MgAppearance::F_NORMSCALE
   */

}
//--



//++MgOpenGlContext::LightDef [nhpqfohm`mjhiuefg,mgopenglshade.c]
int MgOpenGlContext::LightDef( int lightno, MgLight *light, MgLighting *lgt, int mask)
{
    GLfloat f[4];

    f[3] = 1.0;

    glLightfv((lightno, GL_AMBIENT, (float *)(light->GetAmbientColor())));

    ;
    f[0] = (float)(light->GetIntensity() * light->GetColor().GetRed());
    f[1] = (float)(light->GetIntensity() * light->GetColor().GetGreen());
    f[2] = (float)(light->GetIntensity() * light->GetColor().GetBlue());
    glLightfv((lightno, GL_DIFFUSE, f));

    glLightfv((lightno, GL_POSITION, light->GetGlobalPositionF()));
    if( mask & (MgLighting::F_ATTENCONST | MgLighting::F_ATTENMULT)) {
        glLightf((lightno, GL_CONSTANT_ATTENUATION, lgt->GetAttenConst()));
        glLightf((lightno, GL_LINEAR_ATTENUATION, lgt->GetAttenMult()));
    }

    return lightno;
}
//--


//++MgOpenGlContext::Lighting [nhpqfohm`mjhiujoh,mgopenglshade.c]
//void MgOpenGlContext::Lighting(AppearanceStackNode *astk, int mask)
void MgOpenGlContext::Lighting(MgAppearanceStackNode *node, int mask)
{
    // MgLight *light;
    //MgLighting *li = &astk->p_mLighting;
    MgLighting *li = node->GetAppearance()->GetLighting();

  if (li->GetValid()) {
      //MgOpenGlContext::LightModelDef( astk->p_mLightSeq, li,
      //                                li->GetValid(mask), astk );
      //glCallList( astk->p_mLightSeq);
      MgOpenGlContext::LightModelDef( node->GetLightingSeq(), li,
                                      li->GetValid(mask), node );
      glCallList(( node->GetLightingSeq() ));
  }

  glMatrixMode((GL_MODELVIEW));
  glPushMatrix(());
  glLoadMatrixf(( (GLfloat *) &mW2C));
  MgOpenGlContext::Lights( li->GetLightList(), node);
  glPopMatrix(());
}
//--


//++MgOpenGlContext::LightModelDef [nhpqfohm`mjhiunpefmefg,mgopenglshade.c]
//int MgOpenGlContext::LightModelDef(int lightmodel, MgLighting *lgt,
//                                   int mask, AppearanceStackNode *astk)
int MgOpenGlContext::LightModelDef(int lightmodel, MgLighting *lgt,
                                   int mask, MgAppearanceStackNode *node)
{
    GLfloat f[4];

    glNewList(( lightmodel, GL_COMPILE));

    f[3] = 1.0;
    if( mask & MgLighting::F_AMBIENT) {
        f[0] = (float)(lgt->GetAmbient()->GetRed());
        f[1] = (float)(lgt->GetAmbient()->GetGreen());
        f[2] = (float)(lgt->GetAmbient()->GetBlue());
        glLightModelfv((GL_LIGHT_MODEL_AMBIENT, f));
    }

    if( mask & MgLighting::F_LOCALVIEWER) {
        glLightModelf((GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE));
    }

#ifndef TRUE_EMISSION
        /* This causes trouble if the vertex order makes GL consider
         * our polygon to be backfacing -- then GL_LIGHT_MODEL_TWO_SIDE causes it
         * to be mis-shaded from both sides..
         */
    //if((astk->p_mMat.GetValid() & MgMaterial::F_EMISSION) ) {
    //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //}
    if( node->GetAppearance()->GetFrontMaterial()->GetValid()
        & MgMaterial::F_EMISSION ) {
        glLightModelf((GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE));
    }
#endif

    glEndList(());
    return lightmodel;
}
//--


//++MgOpenGlContext::Lights [nhpqfohm`mjhiut,mgopenglshade.c]
//void MgOpenGlContext::Lights( MgLightList *lightList,
//                              AppearanceStackNode *astk)
void MgOpenGlContext::Lights( MgLightList *lightList,
                              MgAppearanceStackNode *node)
{
  int i, lightsused; //, tmp;
  int baselight = -1;
  //MgLighting *li = &astk->p_mLighting;
  MgLighting *li = node->GetAppearance()->GetLighting();
  GLint maxlights;

  glGetIntegerv((GL_MAX_LIGHTS, &maxlights));

  /* unbind all currently bound OpenGL lights */
  for (i=0; i < maxlights; i++)
    glDisable((GL_LIGHT0+i));

  lightsused = 0;
  MgLightListIter it(*lightList);
  MgLight *light;
  for ( ; it; ++it)
  {
      light = it();
    if (light->GetPrivate() == 0) {
      /* this is a new light */
      if(baselight < 0) {
        baselight = 1 + mAStk.Depth() * maxlights;
      }
      light->SetPrivate(lightsused + baselight);
      light->SetChanged(1);  /* Set changed, to force lmdef below */
    }

    if (light->GetChanged()) {
      MgOpenGlContext::LightDef(GL_LIGHT0+lightsused, light, li, li->GetValid());
      light->SetChanged(0);
    } else {
      /* Even unchanged lights might have moved, if the
       * camera has moved since we last installed them.
       */
      glLightfv((GL_LIGHT0 + lightsused,
                GL_POSITION, light->GetGlobalPositionF() ));
    }

    glEnable(( GL_LIGHT0+lightsused));
      
    ++lightsused;
  }
}
//--


//++MgOpenGlContext::material [nhpqfohm`nbufsjbm,mgopenglshade.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::material
 * Description: bind a material. define it if it's not yet defined.
 * Args:        *mat: MgMaterial to bind.
 *              mask: Bitmask telling which material fields are valid.
 *                    Passed into MgOpenGlContext::materialdef.
 * Returns:     
 * Author:      munzner
 * Date:        Wed Oct 16 16:06:47 1991
 * Notes:       We must reSet the "current GL color" after binding a
 *              material.
 *              We want color calls to change the *diffuse* color when
 *              we're in shading mode. Thus we call glColorMgMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);glEnable(GL_COLOR_MATERIAL).
 *              We also must keep track of the diffuse coefficient
 *              for use in mgopengl_d[3,4]f, our wrapper for color calls.
 *              C3f or c4f should never be called directly.
 *              mg draw routines are responsible for establishing the
 *              correct drawing color.
 */
//void MgOpenGlContext::Material(AppearanceStackNode *astk, int mask)
void MgOpenGlContext::Material(MgAppearanceStackNode *node, int mask)
  // NOTE about change made when switch to use UtLStack:  
  // I believe this procedure only gets called with astk being the top
  // item on the appearance stack, i.e. it's the same as this->astk.Top().
  // I'm using this assumption below in the place(s) where we need access
  // to the next appearance on the stack.  (Formerly the
  // "next" element on the appearance stack was accessible as astk->next.
  // But this isn't the case with the new UtLStack object, which hides
  // the "next" pointer inside the stack.)
  //
  // At some point we need to verify that indeed this procedure is only
  // called with astk pointing to the top of the stack, and then probably
  // change it to eliminate that argument, since we can access it as
  // mAStk.Top().  The same may be true for the "lighting" and
  // "appearance" methods as well.
  //
  // mbp Mon Mar 24 13:37:38 1997
{
    GLfloat f[4];
    //MgMaterial *mat = &astk->p_mMat;
    MgMaterial *mat = node->GetAppearance()->GetFrontMaterial();
    static float lmnull = (float) 0; /* LMNULL */

    mask &= mat->GetValid();
    if (mask & MgMaterial::F_KD) {
      mKd = (float)(mat->GetKd());
    }


    if (! (mask & MgMaterial::F_EMISSION  ||
           mask & MgMaterial::F_DIFFUSE   ||
           mask & MgMaterial::F_AMBIENT   ||
           mask & MgMaterial::F_SPECULAR  ||
           mask & MgMaterial::F_SHININESS ||
           mask & MgMaterial::F_KD        ||
           mask & MgMaterial::F_KA        ||
           mask & MgMaterial::F_KS        ||
           mask & MgMaterial::F_ALPHA ) ) {
      return;   // No GL changes to make
    }

    if (    (mAStk.Depth() > 1)
         && (mAStk.Second()->GetMaterialSeq() == node->GetMaterialSeq()) ) {
        /*
         * Fresh material needed.  Erase any previous GL definition.
         * We'll need to load all valid fields to initialize it.
         */
        node->MaterialSeqIncr();
#ifndef TRUE_EMISSION
        /* Needs fixing - TOR
        if(mat->GetValid() & MgMaterial::F_EMISSION) {
            glNewList(( astk->p_mMatSeq, GL_COMPILE));
            glMaterialf((GL_BACK, GL_AMBIENT_AND_DIFFUSE, * &lmnull));
            glEndList(());
            glCallList((astk->p_mMatSeq));
            astk->p_mMatSeq++;
        }
        */
#endif /*!TRUE_EMISSION*/
        mask = mat->GetValid();
    }

        /* Build material definition */

    //glNewList( astk->p_mMatSeq, GL_COMPILE);
    glNewList(( node->GetMaterialSeq(), GL_COMPILE));
    f[3] = 1.0;
    
#ifdef TRUE_EMISSION
    if( mask & MTF_EMISSION) {
        f[0] = mat->GetEmission().GetRed();
        f[1] = mat->GetEmission().GetGreen();
        f[2] = mat->gEmission().GetBlue();
        glMaterialfv((GL_FRONT_AND_BACK, GL_EMISSION, f));
    }
#endif

    if( mask & (MgMaterial::F_KD | MgMaterial::F_DIFFUSE)) {
        f[0] = (float)(mat->GetKd() * mat->GetDiffuse()->GetRed());
        f[1] = (float)(mat->GetKd() * mat->GetDiffuse()->GetGreen());
        f[2] = (float)(mat->GetKd() * mat->GetDiffuse()->GetBlue());
        if( mask & MgMaterial::F_ALPHA) f[3] = (float)(mat->GetDiffuse()->GetAlpha());
        glMaterialfv((GL_FRONT_AND_BACK, GL_DIFFUSE, f));
    }
    f[3] = 1.0;
    if( mask & (MgMaterial::F_KA | MgMaterial::F_AMBIENT)) {
        f[0] = (float)(mat->GetKa() * mat->GetAmbient()->GetRed());
        f[1] = (float)(mat->GetKa() * mat->GetAmbient()->GetGreen());
        f[2] = (float)(mat->GetKa() * mat->GetAmbient()->GetBlue());
        glMaterialfv((GL_FRONT_AND_BACK, GL_AMBIENT, f));
    }
    if( mask & (MgMaterial::F_KS | MgMaterial::F_SPECULAR | MgMaterial::F_SHININESS)) {
        f[0] = (float)(mat->GetKs() * mat->GetSpecular()->GetRed());
        f[1] = (float)(mat->GetKs() * mat->GetSpecular()->GetGreen());
        f[2] = (float)(mat->GetKs() * mat->GetSpecular()->GetBlue());
        glMaterialfv((GL_FRONT_AND_BACK, GL_SPECULAR, f));
        glMaterialf((GL_FRONT_AND_BACK, GL_SHININESS, (float)(mat->GetShininess())));
    }
    glEndList(());
    //glCallList(astk->p_mMatSeq);
    glCallList(( node->GetMaterialSeq() ));

#ifndef TRUE_EMISSION   /* Hack: use "emission" field as back diffuse color */
    if(mask & MgMaterial::F_EMISSION) {
        f[0] = (float)(mat->GetKd() * mat->GetEmission()->GetRed());
        f[1] = (float)(mat->GetKd() * mat->GetEmission()->GetGreen());
        f[2] = (float)(mat->GetKd() * mat->GetEmission()->GetBlue());
        //glNewList( astk->p_mMatSeq-1, GL_COMPILE);
        glNewList(( node->GetMaterialSeq(), GL_COMPILE));
        glMaterialfv((GL_BACK, GL_AMBIENT_AND_DIFFUSE, f));
        glEndList(());
    }
#endif /*!TRUE_EMISSION*/
}
//--


//++MgOpenGlContext::V4fCloser [nhpqfohm`w5gdmptfs,mgopenglshade.c]
void MgOpenGlContext::V4fCloser(HPoint3 *p)
{
    HPoint3 tp;
    register Point3 *cp = &mCPos;
    float wn = p->w * mZFNudge;
    
    if(!(mHas & HAS_CPOS))
        MgContext::FindCam();

    tp.x = p->x + wn * cp->x;
    tp.y = p->y + wn * cp->y;
    tp.z = p->z + wn * cp->z;
    tp.w = p->w + wn;
    glVertex4fv(((float *)&tp));
}
//--


