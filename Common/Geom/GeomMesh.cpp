#include "GeomMesh.h"

#include <math.h>
#include "HPoint3.h"
#include "MgColor.h"
#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomMesh, Geom);

GeomMesh::GeomMesh()
{
    mP = NULL;
    mN = NULL;
    mU = NULL;
    mColors = NULL;
}

GeomMesh::~GeomMesh()
{
    if (mP) delete mP;
    if (mN) delete mN;
    if (mU) delete mU;
    if (mColors) delete mColors;
}

static void
mnorm(HPoint3 * ap,
      Point3  * an,
      int       nu,
      int       nv,
      int       uwrap,
      int       vwrap,
      int       evert)
{
  register HPoint3 *prev, *next;
  register Point3 *n;
  register int k;
  int u, v;
  float x,y,z, norm;
  float unit;

  /*
   * We set the normal at each point to be the mean of the
   * cross products at the four adjacent points.  I.e.:
   *   n                Given mesh point p and its four orthogonal neighbors
   * w p e      e, n, w, s we define displacements E=e-p, N=n-p, ...
   *   s                and compute normal(p) = ExN + NxW + WxS + SxE
   * This turns out to be equal to (e-w) x (n-s) -- independent of p!
   *
   * Since the index arithmetic gets a bit messy at the boundaries
   * we make two passes.  Pass 1 computes e-w and holds it in
   * the array to be filled with normals.
   * Pass 2 computes n-s, takes the cross product and normalizes.
   */

  unit = evert ? -1.0f : 1.0f;

  for(u = 0; u < nu; u++) {
    if(u == 0) {
      prev = &ap[uwrap ? nu-1 : 0];
      next = &ap[u+1];
    } else if(u == nu-1) {
      prev = &ap[u-1];
      next = &ap[uwrap ? 0 : u];
    } else {
      prev = &ap[u-1];
      next = &ap[u+1];
    }
    n = &an[u];
    k = nv;
    do {
      n->x = next->x - prev->x; /* e - w */
      n->y = next->y - prev->y;
      n->z = next->z - prev->z;
      n += nu;                  /* advance to next v row */
      prev += nu;
      next += nu;
    } while(--k > 0);
  }

  for(v = 0; v < nv; v++) {
    if(v == 0) {
      prev = &ap[vwrap ? nu*(nv-1) : 0];
      next = &ap[nu*1];
    } else if(v == nv-1) {
      prev = &ap[nu*(v-1)];
      next = &ap[vwrap ? 0 : nu*v];
    } else {
      prev = &ap[nu*(v-1)];
      next = &ap[nu*(v+1)];
    }
    n = &an[nu*v];
    k = nu;
    do {
      Point3 t;

      t.x = next->x - prev->x;
      t.y = next->y - prev->y;
      t.z = next->z - prev->z;
      x = n->y * t.z - n->z * t.y;
      y = n->z * t.x - n->x * t.z;
      z = n->x * t.y - n->y * t.x;
      norm = x*x + y*y + z*z;
      if(norm == 0.0) {
        /*
         * Oh no, degenerate norm.
         * Let's hope it happened because (part of) a row of
         * mesh points coincided -- maybe even though N=S,
         * NE != SE or NW != SW.
         */
        if(t.x == 0.0 && t.y == 0.0 && t.z == 0.0) {
          if(k > 1) {
            t.x = (next+1)->x - (prev+1)->x;
            t.y = (next+1)->y - (prev+1)->y;
            t.z = (next+1)->z - (prev+1)->z;
          }
          if(t.x == 0.0 && t.y == 0.0 && t.z == 0.0 && k < nu) {
            t.x = (next-1)->x - (prev-1)->x;
            t.y = (next-1)->y - (prev-1)->y;
            t.z = (next-1)->z - (prev-1)->z;
          }
        }
        if(n->x == 0.0 && n->y == 0.0 && n->z == 0.0) {
          /* Do likewise in E-W direction. */
          register HPoint3 *cur = &ap[nu*(v+1) - k];

          if(k == 1) cur--;
          else if(k == nu) cur++;
          if(v > 0) {
            cur -= nu;          /* SE-SW */
            n->x = (cur+1)->x - (cur-1)->x;
            n->y = (cur+1)->y - (cur-1)->y;
            n->z = (cur+1)->z - (cur-1)->z;
          }
          if(n->x==0.0 && n->y==0.0 && n->z==0.0 && v < nv-1) {
            cur += 2*nu;        /* NE-NW */
            n->x = (cur+1)->x - (cur-1)->x;
            n->y = (cur+1)->y - (cur-1)->y;
            n->z = (cur+1)->z - (cur-1)->z;
          }
        }
        x = n->y * t.z - n->z * t.y;
        y = n->z * t.x - n->x * t.z;
        z = n->x * t.y - n->y * t.x;
        norm = x*x + y*y + z*z;
        if(norm == 0.0) {
          /* Oh well. */
          n->x = unit;
          norm = 1.0f;
        }
      }
      norm = (float)(unit / sqrt(norm));
      n->x = x*norm;
      n->y = y*norm;
      n->z = z*norm;

      n++;                      /* Next u column */
      prev++;
      next++;
    } while(--k > 0);
  }
}

void GeomMesh::ComputeNormals()
{
  if(mN) delete mN;
  mN = new Point3[mNu * mNv];
  mFlags |= MESH_N;
  mnorm(mP, mN, mNu, mNv,
        mFlags & MESH_UWRAP,
        mFlags & MESH_VWRAP,
        mFlags & MESH_EVERT);
}


void GeomMesh::Draw(MgContext *mg)
{
  /* We pass this->flag verbatim to GeomMesh() -- MESH_[UV]WRAP == MM_[UV]WRAP */

        MgContext::MergeType merge = MgContext::M_MERGE;
// if (appearance)
//        mg->pushAppearance(appearance, merge);

        if(!(this->mFlags & MESH_N)) 
        {
                MgAppearance *ap = mg->GetAppearance();
                if ( (ap->GetShading() != MgAppearance::F_CONSTANT)
                  || (ap->GetFlags()    != MgAppearance::F_NORMALDRAW) ) 
                {
                        ComputeNormals();
                }
        }
        mg->Mesh(mFlags, mNu, mNv, mP, mN, mColors, mU);
}
#if 0
IF0  static int
IF0  getmeshvert(IoOldOoglLexer *lex,
IF0              int flag,
IF0              int u,
IF0              int v,
IF0              HPoint3 *p,
IF0              Point3 *n,
IF0              MgColorA *c,
IF0              Point3 *t)  /* actually u, the texture parameter */
IF0  {
IF0  
IF0      if (flag & GeomMesh::MESH_Z)
IF0      {
IF0          if (lex->ExpectFloat(1, &p->z) <= 0)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading MESH.  Expected z-value.");
IF0          p->x = (float) u;
IF0          p->y = (float) v;
IF0          p->w = 1.0f;
IF0      }
IF0      else if (flag & GeomMesh::MESH_4D)
IF0      {
IF0          if (lex->ExpectFloat(4, (float *)p) < 4)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading MESH.  Expected x,y,z,w coordinates.");
IF0      }
IF0      else
IF0      {
IF0          if (lex->ExpectFloat(3, (float *)p) < 3)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading MESH.  Expected x,y,z coordinates.");
IF0          p->w = 1.0f;
IF0      }
IF0  
IF0      if (flag & GeomMesh::MESH_N && lex->ExpectFloat(3, (float *)n) < 3)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading MESH.  Expected Normal vector (x,y,z).");
IF0  
IF0      if (flag & GeomMesh::MESH_C && lex->ExpectFloat(4, (float *)*c) < 4)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading MESH.  Expected Color vector (r,g,b,a).");
IF0  
IF0      if (flag & GeomMesh::MESH_U && lex->ExpectFloat(3, (float *)t) < 3)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading MESH.  Expected Texture Map coordinates (s,t,u).");
IF0  
IF0      return 1;
IF0  }
#endif

static const char mesh_keys[] = "UCNZ4uv";
static const short mesh_bits[] = {
    GeomMesh::MESH_U,
    GeomMesh::MESH_C,
    GeomMesh::MESH_N,
    GeomMesh::MESH_Z,
    GeomMesh::MESH_4D,
    GeomMesh::MESH_UWRAP,
    GeomMesh::MESH_VWRAP,
};

#if 0
IF0  int GeomMesh::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      int n;
IF0      register int i, u, v;
IF0  
IF0      mFlags = GeomOldOoglParser::GetHeader(lex,
IF0          "MESH", keyword, mesh_keys, mesh_bits);
IF0  
IF0      if ( lex->ExpectInt(1, &mNu) < 1 ||
IF0           lex->ExpectInt(1, &mNv) < 1 )
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading MESH.  Expected  Nu Nv");
IF0  
IF0      if ( mNu <= 0 || mNv <= 0 ||
IF0           mNu > 9999999 || mNv > 9999999 )
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading MESH.  Invalid mesh size %d %d", mNu, mNv);
IF0  
IF0      n = mNu * mNv;
IF0  
IF0      if (mP) delete mP;
IF0      if (mN) delete mN;
IF0      if (mU) delete mU;
IF0      if (mColors) delete mColors;
IF0  
IF0      mP = new HPoint3[n];
IF0      mN = NULL;
IF0      mU = NULL;
IF0      mColors = NULL;
IF0  
IF0      if (mFlags & MESH_N) mN = new Point3[n];
IF0      if (mFlags & MESH_C) mColors = new MgColorA[n];
IF0      if (mFlags & MESH_U) mU = new Point3[n];
IF0  
IF0      for (i = 0, v = 0; v < mNv; v++)
IF0          for (u = 0; u < mNu; u++, i++)
IF0          {
IF0              try
IF0              {
IF0                  getmeshvert(lex,mFlags,u,v,&mP[i],&mN[i],&mColors[i],&mU[i]);
IF0              }
IF0              catch (IoOldOoglParseException *pe)
IF0              {
IF0                  // Combine the message from getmeshvert with the one below.
IF0                  // (not yet complete.)
IF0  #if 0
IF0                  throw new IoOldOoglParseException(lex,
IF0                      "Reading MESH.  Bad element (%d,%d) of (0-%d,0-%d)",
IF0                      u, v, mNu-1, mNv-1);
IF0  #endif
IF0                  // Then throw the combination.
IF0                  throw pe;
IF0              }
IF0          }
IF0  
IF0      return 1;
IF0  }
#endif

int GeomMesh::Save(IoDataStream *s)
{
  int i, u, v;
  char keys[sizeof(mesh_keys)/sizeof(mesh_keys[0])+1];

  //  GeomOldOoglParser::MakeHeader(mFlags, keys, mesh_keys, mesh_bits);
  s->PrintF("%sMESH\n%d %d\n\n", keys, mNu, mNv);

  for (i = 0, v = 0; v < mNv; v++)
    for (u = 0; u < mNu; u++, i++)
    {
      if (mFlags & GeomMesh::MESH_Z)
        s->PrintF("%g", mP[i].z);
      else if (mFlags & GeomMesh::MESH_4D)
        s->PrintF("%.7g %.7g %.7g %.7g", mP[i].x, mP[i].y, mP[i].z, mP[i].w);
      else
        s->PrintF("%g %g %g", mP[i].x, mP[i].y, mP[i].z);

      if (mFlags & GeomMesh::MESH_N)
        s->PrintF("  %g %g %g", mN[i].x, mN[i].y, mN[i].z);
      if (mFlags & GeomMesh::MESH_C)
        s->PrintF("  %g %g %g %g",
                float(mColors[i].GetRed()),
                float(mColors[i].GetGreen()),
                float(mColors[i].GetBlue()),
                float(mColors[i].GetAlpha()));
      if (mFlags & GeomMesh::MESH_U)
        s->PrintF("  %g %g %g", mU[i].x, mU[i].y, mU[i].z);

      s->PrintF("\n");
    }

  return 1;
}
