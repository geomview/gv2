#include "GlHeaders.h"
#include "MgOpenGlContext.h"

//++MgOpenGlContext::Mesh [nhpqfohm`nfti,mgopenglmesh.c]
void MgOpenGlContext::Mesh(int wrap,
                           int nu, int nv,
                           HPoint3 *meshP, Point3 *meshN,
                           MgColorA *meshC, Point3 *meshSTR)
{
  MgOpenGlContext::Submesh( wrap, nu, nv, 0, nu-1, 0, nv-1, meshP, meshN, meshC, meshSTR);
}
//--


//++MgOpenGlContext::Submesh [nhpqfohmtvcnfti,mgopenglmesh.c]
void MgOpenGlContext::Submesh(int wrap,
                              int nu, int nv,
                              int umin, int umax,
                              int vmin, int vmax,
                              HPoint3 *meshP, Point3 *meshN,
                              MgColorA *meshC, Point3 *meshSTR)
{
  register int u, v;
  int ucnt, vcnt;
  register HPoint3 *P;
  register Point3 *N;
  register MgColorA *C;
  Point3 *STR;
  register int prev;
  int du;
  int douwrap;
//  HPoint3  tp;
//  Point3 tn;
  int i;
  int has;
  MgAppearance *ap;

#undef P
/* ^^^ evil kludge XXX to get the P variables here to not get confused
 * with the P prototype macro. -nils */
#define HAS_N   0x1
#define HAS_C   0x2
#define HAS_SMOOTH 0x4
#define HAS_STR 0x8

  if(nu <= 0 || nv <= 0)
    return;

  ap = mAStk.Top()->GetAppearance();
  if (mAStk.Top()->GetAppearance()->GetFrontMaterial()->GetOverride(MgMaterial::F_DIFFUSE))
    meshC = 0;

  has = 0;
  if(meshN)
    has = HAS_N;
  if(meshC)
    has |= HAS_C;
  if(ap->HasSmoothShading())
    has |= HAS_SMOOTH;


  if( ap->GetFlags() & MgAppearance::F_FACEDRAW && nu > 1 && nv > 1 ) { /* Draw faces */

    /* We triangulate strips of (v,u) mesh points:
     *  (v,u)    (v,u+1)    (v,u+2) ...
     *  (v+1,u)  (v+1,u+1)  (v+1,u+2) ...
     * using the vertex sequence
     *  (v,u) , (v+1,u), (v,u+1), (v+1,u+1), (v,u+2), ...
     * This covers the territory from v to v+1; then repeat for other v's.
     * If we hit the 256-vertex triangle-mesh limit, the strip is spliced
     * by redrawing the latest (v,u+i),(v+1,u+i) pair of vertices.
     */

    glColorMaterial((GL_FRONT_AND_BACK, this->mLmColor));glEnable((GL_COLOR_MATERIAL));
    MayLight();

    if(!(has & HAS_C))
        D4f(ap->GetFrontMaterial()->GetDiffuse());

    v = vmax - vmin + 1;
    du = umin + vmin * nu;

    if(wrap & MESH_VWRAP) {
      /* V-wrapping: cur = mesh[vmin,u], prev = mesh[vmax,u] */
      prev = nu * (v - 1);
    } else {
      /* Not V-wrapping: cur = mesh[vmin+1,u], prev = mesh[vmin,u] */
      du += nu;
      prev = -nu;
      v--;      /* One less V-row, too */
    }

    do {                                        /* Loop over V */
     P = meshP + du;
     N = meshN + du;
     C = meshC + du;
     STR = meshSTR + du;
     ucnt = umax - umin + 1;
     glBegin((GL_TRIANGLE_STRIP));
     douwrap = (wrap & MESH_UWRAP);
     do {
        /* Loop over U */
        u = ucnt;
        ucnt = 0;

        switch( has ) {

        case 0:
        case HAS_SMOOTH:
          do {
            glVertex4fv(((float *)P+prev));
            glVertex4fv(((float *)P));
            P++;
          } while(--u);
          break;

        case HAS_C:
          do {
            D4f(C+prev);
            glVertex4fv(((float *)(P+prev)));
            glVertex4fv(((float *)P));
            C++; P++;
          } while(--u);
          break;

        case HAS_C|HAS_SMOOTH:
          do {
            D4f(C+prev);
            glVertex4fv(((float *)(P+prev)));
            D4f(C);
            glVertex4fv(((float *)P));
            C++; P++;
          } while(--u);
          break;

        case HAS_N:
          do {
            N3f(N+prev, P);
            glVertex4fv(((float *)(P+prev)));
            glVertex4fv(((float *)P));
            N++; P++;
          } while(--u);
          break;

        case HAS_N|HAS_SMOOTH:
          do {
            N3f(N+prev, P);
            glVertex4fv(((float *)(P+prev)));
            N3f(N, P);
            glVertex4fv(((float *)P));
            N++; P++;
          } while(--u);
          break;

        case HAS_C|HAS_N:
          do {
            D4f(C+prev);
            N3f(N+prev, P);
            glVertex4fv(((float *)(P+prev)));
            glVertex4fv(((float *)P));
            C++; N++; P++;
          } while(--u);
          break;

        case HAS_C|HAS_N|HAS_SMOOTH:
          do {
            D4f(C+prev);
            N3f(N+prev, P);
            glVertex4fv(((float *)(P+prev)));
            D4f(C);
            N3f(N, P);
            glVertex4fv(((float *)P));
            C++; N++; P++;
          } while(--u);
          break;

        case HAS_STR:
          do {
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            P++; STR++;
          } while(--u);
          break;

        case HAS_C|HAS_STR:
          do {
            D4f(C+prev);
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            C++; P++; STR++;
          } while(--u);
          break;

        case HAS_C|HAS_SMOOTH|HAS_STR:
          do {
            D4f(C+prev);
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            D4f(C);
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            C++; P++; STR++;
          } while(--u);
          break;

        case HAS_N|HAS_STR:
          do {
            N3f(N+prev, P);
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            N++; P++; STR++;
          } while(--u);
          break;

        case HAS_N|HAS_SMOOTH|HAS_STR:
          do {
            N3f(N+prev, P);
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            N3f(N, P);
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            N++; P++; STR++;
          } while(--u);
          break;

        case HAS_C|HAS_N|HAS_STR:
          do {
            D4f(C+prev);
            N3f(N+prev, P);
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            C++; N++; P++; STR++;
          } while(--u);
          break;

        case HAS_C|HAS_N|HAS_SMOOTH|HAS_STR:
          do {
            D4f(C+prev);
            N3f(N+prev, P);
            // glTexCoord2fv((float *)(STR+prev));
            glVertex4fv(((float *)(P+prev)));
            D4f(C);
            N3f(N, P);
            // glTexCoord2fv((float *)STR);
            glVertex4fv(((float *)P));
            C++; N++; P++; STR++;
          } while(--u);
          break;
        }

        if(ucnt == 0) {
          if(douwrap) {
            douwrap = 0;        /* Loop again on first vertex */
            ucnt = 1;
            P = meshP + du;
            N = meshN + du;
            C = meshC + du;
            STR = meshSTR + du;
          }
        } else {
          glEnd(());           /* Hit tmesh limit, splice */
          glBegin((GL_TRIANGLE_STRIP));
          C--; N--; P--; STR--; /* Redraw last vertex */
        }
     } while(ucnt);

     glEnd(());
     prev = -nu;
     du += nu;
   } while(--v > 0);
  }

  if(ap->GetFlags() & (MgAppearance::F_EDGEDRAW|MgAppearance::F_NORMALDRAW)
        || (ap->GetFlags() & MgAppearance::F_FACEDRAW && (nu == 1 || nv == 1))) {
    glDisable((GL_COLOR_MATERIAL));
    DontLight();
    if(this->mZNudge) MgOpenGlContext::Closer();
    if(ap->GetFlags() & MgAppearance::F_EDGEDRAW) {                     /* Draw edges */
        glColor3fv(((float *)(*ap->GetFrontMaterial()->GetEdgeColor())));

        du = umin + vmin * nu;
        ucnt = umax - umin + 1;
        vcnt = vmax - vmin + 1;
        v = vcnt;
        do {
            if(wrap & MESH_UWRAP)
                glBegin((GL_LINE_LOOP));
            else
                glBegin((GL_LINE_STRIP));
            u = ucnt;
            P = meshP + du;
            do {
                glVertex4fv(((float *)P));
                P++;
            } while(--u > 0);
            if(wrap & MESH_UWRAP)
                glEnd(());
            else
                glEnd(());
            du += nu;
        } while(--v > 0);

        du = umin + vmin * nu;
        u = ucnt;
        do {
            v = vcnt;
            if(wrap & MESH_VWRAP)
                glBegin((GL_LINE_LOOP));
            else
                glBegin((GL_LINE_STRIP));
            P = meshP + du;
            do {
                glVertex4fv(((float *)P));
                P += nu;
            } while(--v > 0);
            if(wrap & MESH_VWRAP)
                glEnd(());
            else
                glEnd(());
            du++;
        } while(--u > 0);
    }

    if(ap->GetFlags() & MgAppearance::F_NORMALDRAW && meshN != NULL) {
        glColor3fv(((float *)(*ap->GetFrontMaterial()->GetNormalColor())));

        for (i = nu*nv, P=meshP, N=meshN; --i >= 0; P++, N++) {
            MgOpenGlContext::Drawormal(P, N);
        }
    }
    if(this->mZNudge) MgOpenGlContext::Farther();
  }
}
//--


