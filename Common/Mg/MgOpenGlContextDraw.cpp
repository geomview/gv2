#include "MgOpenGlContext.h"
#include "GlHeaders.h"

#ifndef WIN32
#ifndef alloca
#include <alloca.h>
#endif
#endif


#ifndef NO_ZNUDGE
# define mgopengl_v4ffunc(v)  glVertex4fv((&(v)->x));
#else
# define mgopengl_v4ffunc(v)  MgOpenGlContext::V4fCloser(v)
#endif

/*  The following is from polylistP.h:  ------------------------------ */

struct MgContext::Vertex
{
        HPoint3 pt;
        MgColorA        vcol;
        Point3  vn;
        float st[2];
};

// typedef struct Vertex Vertex;

struct MgContext::Poly
{
        int     n_vertices;
        struct Vertex   **v;
        MgColorA  pcol;
        Point3  pn;
};

// typedef struct Poly Poly;


#  define         PL_HASVN      0x1     /* Per-vertex normals (vn) valid */
#  define         PL_HASPN      0x2     /* Per-polygon normals (pn) valid */
#  define         PL_HASVCOL    0x4     /* Per-vertex colors (vcol) valid */
#  define         PL_HASPCOL    0x8     /* Per-polygon colors (pcol) valid */
#  define         PL_EVNORM     0x10    /* Normals are everted */

/*  end of stuff from polylistP.h:  ---------------------------------- */


//++MgOpenGlContext::Polygon [nhpqfohm`qpmzhpo,mgopengldraw.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::Polygon
 * Description: draw a polygon
 * Author:      mbp, munzner
 * Date:        Mon Jul 29 16:53:56 1991
 * Notes:       See mg.doc.
 *
 *              do later: Different shading cases separated into different
 *              loops for speed.
 */
void MgOpenGlContext::Polygon(int nv,  HPoint3 *V, 
                      int nn,  Point3 *N, 
                      int nc,  MgColorA *C)
{
  register int i;       
  register HPoint3 *v;
  register Point3 *n;
  register MgColorA *c;
  int cinc, ninc;
  int flag;


  flag = mAStk.Top()->GetAppearance()->GetFlags();
  if (mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetOverride(MgMaterial::F_DIFFUSE)) {
    nc = 0;
  }
  cinc = (nc > 1);
  ninc = (nn > 1);
  if(nc == 0)
    C = mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetDiffuse();


  /* reestablish correct drawing color if necessary */

  if (flag & MgAppearance::F_FACEDRAW) {
    MayLight();
    glColorMaterial((GL_FRONT_AND_BACK, this->mLmColor));
    glEnable((GL_COLOR_MATERIAL));
    glBegin((GL_POLYGON));
    if (nc <= 1) {
        D4f(mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetDiffuse());
    }
    for (n = N, c = C, v = V, i = 0; i<nv; ++i, ++v) {
        if (nc) { D4f(c); c += cinc; }
        if (nn) { N3f(n,v); n += ninc; }
        glVertex4fv(((float *)v));
    }
    glEnd(());
  }

  if( flag & (MgAppearance::F_EDGEDRAW|MgAppearance::F_NORMALDRAW) ) {
    if(this->mZNudge) MgOpenGlContext::Closer();
    glDisable((GL_COLOR_MATERIAL));
    DontLight();
    if (flag & MgAppearance::F_EDGEDRAW) {
        glColor3fv(((float *)(*mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetEdgeColor())));
        glBegin((GL_LINE_LOOP));
        for (v = V, i = 0; i<nv; ++i, ++v)
          mgopengl_v4ffunc(v);
        glEnd(());
    }

    if (flag & MgAppearance::F_NORMALDRAW) {
        glColor3fv(((float *)(*mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetNormalColor())));
        for (n = N, v = V, i = 0; i<nv; ++i, ++v, n += ninc) {
            MgOpenGlContext::Drawormal(v, n);
        }
    }
    if(this->mZNudge) MgOpenGlContext::Farther();
  }
}
//--


//++MgOpenGlContext::Polylist [nhpqfohm`qpmzmjtu,mgopengldraw.c]
/*-----------------------------------------------------------------------
 * Function:    MgOpenGlContext::Polylist
 * Description: draws a Polylist: collection of Polys
 * Author:      munzner
 * Date:        Wed Oct 16 20:21:56 1991
 * Notes:       see mg.doc
 */
void MgOpenGlContext::Polylist( int np, struct Poly *mP, int nv, struct Vertex *V, int plflags )
{
  register int i,j;
  register struct Poly *p;
  register struct Vertex **v, *vp;
//  register Point3 *n;
  //AppearanceStackNode *ma = mAStk.Top();
  MgAppearanceStackNode *top = mAStk.Top();
  int flag,shading;
  int nonsurf = -1;
  flag = top->GetAppearance()->GetFlags();
  shading = top->GetAppearance()->GetShading();


  switch(shading) {
  case MgAppearance::F_FLAT: plflags &= ~PL_HASVN; break;
  case MgAppearance::F_SMOOTH: plflags &= ~PL_HASPN; break;
  default: plflags &= ~(PL_HASVN|PL_HASPN); break;
  }

  if(mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetOverride(MgMaterial::F_DIFFUSE))
    plflags &= ~(PL_HASVCOL | PL_HASPCOL);

  if (flag & MgAppearance::F_FACEDRAW) {
    glColorMaterial((GL_FRONT_AND_BACK, this->mLmColor));
    glEnable((GL_COLOR_MATERIAL));
    MayLight();
    /* reestablish correct drawing color if necessary*/
    if (!(plflags & (PL_HASPCOL | PL_HASVCOL))) {
        D4f(top->GetAppearance()->GetFrontMaterial()->GetDiffuse());
    }

    for (p = mP, i = 0; i < np; i++, p++) {
        if (plflags & PL_HASPCOL)
            D4f(&p->pcol);
        if (plflags & PL_HASPN) {
          N3f(&(p->pn), &(*p->v)->pt);
        }
        v = p->v;
        if((j = p->n_vertices) <= 2) {
            nonsurf = i;
        } else if(j <= 4 || !(flag & MgAppearance::F_CONCAVE)
                        || !MgOpenGlContext::TrickyPolygon(p, plflags)) {

            glBegin((GL_POLYGON));
            switch(plflags & (PL_HASVCOL|PL_HASVN)) {
            case 0:
                do {
                    glVertex4fv(((float *)&(*v)->pt));
                    v++;
                } while(--j > 0);
                break;
            case PL_HASVCOL:
                do {
                    D4f((&(*v)->vcol));
                    glVertex4fv(((float *)&(*v)->pt));
                    v++;
                } while(--j > 0);
                break;
            case PL_HASVN:
                do {
                    N3f((&(*v)->vn), (&(*v)->pt));
                    glVertex4fv(((float *)&(*v)->pt));
                    v++;
                } while(--j > 0);
                break;
            case PL_HASVCOL|PL_HASVN:
                do {
                    D4f((&(*v)->vcol));
                    N3f((&(*v)->vn), (&(*v)->pt));
                    glVertex4fv(((float *)&(*v)->pt));
                    v++;
                } while(--j > 0);
                break;
            default:
                do {
                    if (plflags & PL_HASVCOL) D4f((&(*v)->vcol));
                    if (plflags & PL_HASVN) N3f((&(*v)->vn), (&(*v)->pt));
                    glVertex4fv(((float *)&(*v)->pt));
                    v++;
                } while(--j > 0);
                break;
            }
            glEnd(());
        }
    }
  }

  if (flag & (MgAppearance::F_EDGEDRAW|MgAppearance::F_NORMALDRAW) || nonsurf >= 0) {
    if(this->mZNudge) MgOpenGlContext::Closer();
    glDisable((GL_COLOR_MATERIAL));
    DontLight();

    if (flag & MgAppearance::F_EDGEDRAW) {
        glColor3fv(((float *)(*mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetEdgeColor())));
        for (p = mP, i = 0; i < np; i++, p++) {
            glBegin((GL_LINE_LOOP));
            for (j=0, v=p->v; j < p->n_vertices; j++, v++) {
                mgopengl_v4ffunc(&(*v)->pt);
            }
            glEnd(());
        }
    }

    if (flag & MgAppearance::F_NORMALDRAW) {
        glColor3fv(((float *)(*mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetNormalColor())));
        if (plflags & PL_HASPN) {
            for (p = mP, i = 0; i < np; i++, p++) {
                for (j=0, v=p->v; j < p->n_vertices; j++, v++)
                  MgOpenGlContext::Drawormal(&(*v)->pt, &p->pn);
            }
        } else if (plflags & PL_HASVN) {
            for (vp = V, i = 0; i < nv; i++, vp++) {
                MgOpenGlContext::Drawormal(&vp->pt, &vp->vn);
            }
        }
    }


    if (nonsurf >= 0) {
      /* reestablish correct drawing color if necessary*/
      if (!(plflags & (PL_HASPCOL | PL_HASVCOL))) {
        D4f(top->GetAppearance()->GetFrontMaterial()->GetDiffuse());
      }
      
      for(p = mP, i = 0; i <= nonsurf; p++, i++) {
        if (plflags & PL_HASPCOL)
          D4f((&p->pcol));
        v = p->v;
        switch(j = p->n_vertices) {
        case 1:
          if(plflags & PL_HASVCOL) glColor4fv(((float *)(*v)->vcol));
          MgOpenGlContext::Point(&(*v)->pt);
          break;
        case 2:
          glBegin((GL_LINE_STRIP));
          do {
            if(plflags & PL_HASVCOL) glColor4fv(((float *)(*v)->vcol));
            glVertex4fv(((float *)&(*v)->pt));
            v++;
          } while(--j > 0);
          glEnd(());
          break;
        }
      }
    }
    if(this->mZNudge) MgOpenGlContext::Farther();
  }
}
//--


//++MgOpenGlContext::Line [nhpqfohm`mjof,mgopengldraw.c]
void MgOpenGlContext::Line( HPoint3 *p1, HPoint3 *p2 )
{
  DontLight();
  glBegin((GL_LINE_STRIP));
  glVertex4fv(((float *)p1));
  glVertex4fv(((float *)p2));
  glEnd(());
}
//--


//++MgOpenGlContext::Polyline [nhpqfohm`qpmzmjof,mgopengldraw.c]
void MgOpenGlContext::Polyline( int nv, HPoint3 *v, int nc, MgColorA *c, int wrapped )
{
//  int remain;

  DontLight();

  /* note we don't reset to current material color because we could be
   * in the middle of a list of lines and should inherit the color from 
   * the last color call.
   */
  
  if(!(wrapped & 2)) {
        /* First member of batch */
      if(this->mZNudge) MgOpenGlContext::Closer();
      if(nc)
          glDisable((GL_COLOR_MATERIAL));
  }
  if (nv == 1) {
    if(nc > 0) glColor4fv(((float *)*c));
    MgOpenGlContext::Point(v);
  } 
  else if(nv > 0) {
    glBegin((GL_LINE_STRIP));
    if(wrapped & 1) {
      if(nc > 0) glColor4fv(((float *)*(c + nc - 1)));
        mgopengl_v4ffunc(v + nv - 1);
    }

    do {
        if(--nc >= 0) glColor4fv(((float *)*(c++)));
        mgopengl_v4ffunc(v++);
    } while(--nv > 0);
    glEnd(());
  }
  if(!(wrapped & 4) && this->mZNudge) MgOpenGlContext::Farther();
}
//--


//++MgOpenGlContext::Quads [nhpqfohm`rvbet,mgopengldraw.c]
void MgOpenGlContext::Quads(int count,  HPoint3 *V, Point3 *N, MgColorA *C)
{
  int i;        
//  register int k;
  register HPoint3 *v;
  register Point3 *n;
  register MgColorA *c;
  MgColorA cs[4];
  int flag;

#define QUAD(stuff)  { \
                register int k = 4;             \
                glBegin((GL_POLYGON));          \
                do { stuff; } while(--k > 0);   \
                glEnd(());                      \
        }
  if(count <= 0)
    return;
  flag = mAStk.Top()->GetAppearance()->GetFlags();
  if (mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetOverride(MgMaterial::F_DIFFUSE))
    C = NULL;
  
  /* reestablish correct drawing color if necessary */

  if (flag & MgAppearance::F_FACEDRAW) {
    glColorMaterial((GL_FRONT_AND_BACK, this->mLmColor));
    glEnable((GL_COLOR_MATERIAL));

    MayLight();

    // If glVertex4fv is defined as a macro, as it would be if we're compiling
    // for glTracing, undefine it.  This means that these calls aren't traced,
    // but this is the only way to get the calls to the QUAD macro below to
    // compile. mbp Tue Nov  7 23:02:38 2000
#ifdef glVertex4fv
#undef glVertex4fv
#endif // glVertex4f
    i = count;
    v = V; c = C; n = N;
    if(c) {
        if(n) {
            do {
              QUAD( (D4f(c++),
                     N3f(n++, v),
                     glVertex4fv((float*)(v++)) ));
            } while(--i > 0);
        } else {
            /* Colors, no normals */
            do {
                QUAD( (D4f(c++), glVertex4fv((float*)v++)) );
            } while(--i > 0);
        }
    } else {
        c = mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetDiffuse();
        if(n) {
            D4f(c);
            do {
              QUAD( (N3f(n++, v),
                     glVertex4fv((float*)v++)) );
            } while(--i > 0);
        } else {
            D4f(c);
            do {
                QUAD( (glVertex4fv((float*)v++)) );
            } while(--i > 0);
        }
    }
  }


  if( flag & (MgAppearance::F_EDGEDRAW|MgAppearance::F_NORMALDRAW) ) {
    if(this->mZNudge) MgOpenGlContext::Closer();
    glDisable((GL_COLOR_MATERIAL));
    DontLight();

    if (flag & MgAppearance::F_EDGEDRAW) {
        glColor3fv(((float *)(*mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetEdgeColor())));
        i = count; v = V;
        do {
            register int k = 4;
            glBegin((GL_LINE_LOOP));
            do { mgopengl_v4ffunc(v++); } while(--k > 0);
            glEnd(());
        } while(--i > 0);
    }

    if (flag & MgAppearance::F_NORMALDRAW && N) {
        glColor3fv(((float *)(*mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetNormalColor())));
        i = count*4; v = V; n = N;
        do {
            MgOpenGlContext::Drawormal(v++, n++);
        } while(--i > 0);
    }
    if(this->mZNudge) MgOpenGlContext::Farther();
  }
}
//--


//++MgOpenGlContext::Closer [nhpqfohm`dmptfs,mgopengldraw.c]
void MgOpenGlContext::Closer()
{
#ifndef NO_ZNUDGE
  glDepthRange(( this->mZNear -= this->mZNudge,  this->mZFar -= this->mZNudge ));
#endif
}
//--


//++MgOpenGlContext::Drawormal [nhpqfohm`esbxopsnbm,mgopengldraw.c]
/* There is a basic problem now with 4-d points and 3-d normal vectors.
For now, we'll just ignore the 4-th coordinate of the point when 
computing the tip of the normal vector.  This will work OK with all
existing models, but for genuine 4-d points it won't work.  But,
come to think of it, what is the correct interpretation of the
normal vector when the points live in 4-d?
*/
void MgOpenGlContext::Drawormal(register HPoint3 *p, Point3 *n)
{
  Point3 end, tp;
  float scale;

  if (p->w <= 0.0) return;
  if(p->w != 1) {
    HPoint3::toPoint3(p, &tp);
    p = (HPoint3 *)&tp;
  }

  scale = (float)(mAStk.Top()->GetAppearance()->GetNormalScale());
  if(mAStk.Top()->GetAppearance()->GetFlags() & MgAppearance::F_EVERT) {
    register Point3 *cp = &mCPos;
    if(!(mHas & HAS_CPOS))
        MgContext::FindCam();
    if((p->x-cp->x) * n->x + (p->y-cp->y) * n->y + (p->z-cp->z) * n->z > 0)
        scale = -scale;
  }

  end.x = p->x + scale*n->x;
  end.y = p->y + scale*n->y;
  end.z = p->z + scale*n->z;

  DontLight();

  glBegin((GL_LINE_STRIP));
  glVertex3fv(((float *)p));
  glVertex3fv(((float *)&end));
  glEnd(());
}
//--


//++MgOpenGlContext::Farther [nhpqfohm`gbsuifs,mgopengldraw.c]
void MgOpenGlContext::Farther()
{
#ifndef NO_ZNUDGE
  glDepthRange(( this->mZNear += this->mZNudge,  this->mZFar += this->mZNudge ));
#endif
}
//--

const int MgOpenGlContext::MAXZNUDGE = 8;


//++MgOpenGlContext::InitZRange [nhpqfohm`joju`{sbohf,mgopengldraw.c]
/*
 * Z-shift routines: for moving edges closer than faces, etc.
 */
void MgOpenGlContext::InitZRange()
{
  this->mZNudge = (double) mZFNudge * (this->mZMax - this->mZMin);

  this->mZNear = this->mZMin + fabs(this->mZNudge * (double)MAXZNUDGE);
  this->mZFar  = this->mZMax - fabs(this->mZNudge * (double)MAXZNUDGE);
#ifndef NO_ZNUDGE
  glDepthRange((this->mZNear, this->mZFar));
#endif
}
//--


//++MgOpenGlContext::point [nhpqfohm`qpjou,mgopengldraw.c]
void MgOpenGlContext::Point(register HPoint3 *v)
{
//  int i;
  HPoint3 a;
  register HPoint3 *p, *q;
  float vw;

  DontLight();

  if(mAStk.Top()->GetAppearance()->GetLineWidth() > 1) {
    
    if(!(mHas & HAS_POINT))
      MgContext::MakePoint();
    /* Compute w component of point after projection to screen */
    vw = v->x * mO2S.D.M[0][3] + v->y * mO2S.D.M[1][3]
      + v->z * mO2S.D.M[2][3] + v->w * mO2S.D.M[3][3];
    if(vw <= 0) return;
    
#define  PUT(p)                                         \
    a.x = v->x + p->x*vw; a.y = v->y + p->y*vw; \
      a.z = v->z + p->z*vw; a.w = v->w + p->w*vw;       \
        glVertex4fv(((float *)&a))
          
          p = VVEC((mPointVvec), HPoint3);
    q = p + VVCOUNT((mPointVvec));
    
    if(this->mIsPI) {
      glBegin((GL_POLYGON));
      do {
        PUT(p);
      } while(++p < q);
      glEnd(());
    } else {
      glBegin((GL_TRIANGLE_STRIP));
      PUT(p);
      do {
        p++;
        PUT(p);
        if(p >= q) break;
        q--;
        PUT(q);
      } while(p < q);
      glEnd(());
    }
  } else {
    glBegin((GL_POINTS));
    glVertex4fv(((float *)v));
    glEnd(());
  }
}
//--


//++MgOpenGlContext::TrickyPolygon [nhpqfohm`usjdlzqpmzhpo,mgopengldraw.c]
/*
 * Called when we're asked to deal with a possibly-concave polygon.
 * Note we can only be called if MgAppearance::F_CONCAVE mode is set.
 * Returns 0 if the polygon wasn't concave, and can be rendered by the
 * normal algorithm.
 */
int MgOpenGlContext::TrickyPolygon( struct Poly *p, int plflags ) 
{
  int i;
  struct Vertex *vprev, *vp; //, *vnext;
  Point3 e, eprev, cross;
  int cw = 0, ccw = 0;
  float orient;
  static GLUtriangulatorObj *glutri;

  vprev = (p->v)[p->n_vertices-1];
  vp = (p->v)[0];
  HPoint3::SubtractToPoint3(&vp->pt, &vprev->pt, &e);
  for(i = 1; i < p->n_vertices; i++) {
    eprev = e;
    vprev = vp;
    vp = (p->v)[i];
    HPoint3::SubtractToPoint3(&vp->pt, &vprev->pt, &e);
    cross.Cross(&e, &eprev);
    orient = cross.Dot(&p->pn);
    if(orient < -1e-8) cw = 1;
    else if(orient > 1e-8) ccw = 1;
  }
  if(cw && ccw) {
    /* Has some reflex vertices -- it's concave. */
#if CUTOUT
XX     double *dpts = (double *)alloca(3*p->n_vertices*sizeof(double));
XX     double *dp;
#endif /* CUTOUT */
    double *dpts;
    double *dp;
        fprintf(stderr, "YO!  commented out alloca spot reached!\n");

    if(glutri == NULL) {
        /* Create GLU-library triangulation handle, just once */
        glutri = gluNewTess();
#ifdef _WIN32   /* Windows idiocy.  We shouldn't need to cast standard funcs! */
#if CUTOUT
XX  WHAT??? I cannot get this to compile in Visual C++.  Must
XX    fix it later!!  mbp 2/24/97.
XX      gluTessCallback(glutri, GLU_BEGIN, (GLUtessBeginProc)glBegin);
XX      gluTessCallback(glutri, GLU_VERTEX, (GLUtessVertexProc)MgOpenGlContext::Tessvert);
XX      gluTessCallback(glutri, GLU_END, (GLUtessEndProc)glEnd);
#endif /* CUTOUT */
#else           /* Any reasonable OpenGL implementation */
#if CUTOUT
XX  And Lori says this won't compile with gcc, so I'm commenting this
XX  out too.  Really need to completely re-examine this whole function.
XX  mbp Wed Nov 12 22:33:51 1997
XX      gluTessCallback(glutri, GLU_BEGIN, glBegin);
XX      gluTessCallback(glutri, GLU_VERTEX, MgOpenGlContext::Tessvert);
XX      gluTessCallback(glutri, GLU_END, glEnd);
#endif /* CUTOUT */
#endif
    }

    mTessPlFlags = plflags;
    gluBeginPolygon(glutri);
    for(i = 0, dp = dpts; i < p->n_vertices; i++, dp += 3) {
        vp = (p->v)[i];
        dp[0] = vp->pt.x / vp->pt.w;
        dp[1] = vp->pt.y / vp->pt.w;
        dp[2] = vp->pt.z / vp->pt.w;
        gluTessVertex(glutri, dp, vp);
    }
    gluEndPolygon(glutri);
    return 1;                   /* It was tricky, but we handled it */
  }
  return 0;                     /* It wasn't tricky, you handle it faster */
}
//--


//++MgOpenGlContext::Tessvert [ufttwfsu,mgopengldraw.c]
void MgOpenGlContext::Tessvert(struct Vertex *vp)
{
  if (mTessPlFlags & PL_HASVCOL) D4f(&vp->vcol);
  if (mTessPlFlags & PL_HASVN) N3f(&vp->vn, &vp->pt);
  glVertex4fv((&vp->pt.x));
}
//--


