#include "GeomQuad.h"

#include <string.h>
#include <math.h>

#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomQuad, Geom);

//#define  TRYQUADS     1000
#define  TRYQUADS       16

// We must initialize all MgColorA's in the array mColors to something,
// otherwise the class's virtual functions will not work.  The program
// will crash if you try to call them.
static MgColorA blackq[4] = {
        MgColorA(0,0,0,0), MgColorA(0,0,0,0),
        MgColorA(0,0,0,0), MgColorA(0,0,0,0) };

GeomQuad::GeomQuad() :
    // Initialize the variable length vectors to the proper sizes.
    mP(4*sizeof(HPoint3), NULL, TRYQUADS),
    mN(4*sizeof(Point3), NULL, TRYQUADS),
    mColors(4*sizeof(MgColorA), blackq, TRYQUADS)
{
    mFlags = 0;
    mSeq = 0;
    nMaxQuad = 0;
}

GeomQuad::~GeomQuad()
{
    // The arrays will automatically be deleted.
}

static const char  quad_keys[] = "CN4";
static const short quad_bits[] = {
    GeomQuad::QU_VCOL,
    GeomQuad::QU_NORM,
    GeomQuad::QU_FOURDIM,
};

#if 0
IF0  int GeomQuad::GetQuad(IoOldOoglLexer *lex, int dimn, int limit)
IF0  {
IF0      HPoint3 *p;
IF0      Point3 *n;
IF0      MgColorA *c;
IF0      register int i, k;
IF0      int got;
IF0  
IF0      // Read each quadrilateral.
IF0      for (i=0; limit<0 || i<limit; i++)
IF0      {
IF0          // Get the indices into the arrays.
IF0          // IMPORTANT:  'Get(i)' must be called for each quadrilateral
IF0          // to make sure there is room in the array for it.
IF0          p = (HPoint3*)mP.Get(i);
IF0          n = (mFlags & QU_NORM) ? (Point3*)mN.Get(i) : NULL;
IF0          c = (mFlags & QU_VCOL) ? (MgColorA*)mColors.Get(i) : NULL;
IF0  
IF0          // For each vertex in the quadrilateral.
IF0          for (k=0; k<4; k++)
IF0          {
IF0              // Read the coordinates.
IF0              /* set the w-coordinate if the points are 3 dim'nal */
IF0              if (dimn == 3) p->w = 1.0;
IF0              if ((got = lex->ExpectFloat(dimn, (float *)p++)) == 0) goto done;
IF0  
IF0              if (got < dimn)
IF0              {
IF0                  throw new IoOldOoglParseException(lex,
IF0                    "Reading QUAD.  Expected %d number%s, got %d.",
IF0                    dimn, &"s"[dimn==1], got);
IF0              }
IF0  
IF0              // Read the normal vector, if supplied.
IF0              if (n != NULL && (got=lex->ExpectFloat(3, (float *)n++)) < 3)
IF0                  throw new IoOldOoglParseException(lex,
IF0                    "Reading QUAD.  Expected Normal vector (3 numbers, got %d)",
IF0                    got);
IF0  
IF0              // Read the color components, if supplied.
IF0              if (c != NULL && (got=lex->ExpectFloat(4, (float *)*c++)) < 4)
IF0                  throw new IoOldOoglParseException(lex,
IF0                    "Reading QUAD.  Expected Color vector (4 numbers, got %d)",
IF0                    got);
IF0          }
IF0      }
IF0  
IF0  done:
IF0      if (k%4 != 0)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading QUAD.  Expected multiple of 4 vertices, got %d", 4*i+k);
IF0  
IF0      return i;
IF0  }
#endif

int GeomQuad::Save(IoDataStream *s)
{
    // Make the header and print it out.
    char keys[sizeof(quad_keys)/sizeof(quad_keys[0])+1];
    //    GeomOldOoglParser::MakeHeader(mFlags, keys, quad_keys, quad_bits);
    s->PrintF("%sQUAD\n\n", keys);

    // Get the beginning indices into the arrays.
    HPoint3 *p = (HPoint3*)mP.Get(0);
    Point3 *n = (mFlags & QU_NORM) ? (Point3*)mN.Get(0) : NULL;
    MgColorA *c = (mFlags & QU_VCOL) ? (MgColorA*)mColors.Get(0) : NULL;

    // For each quadrilateral, ...
    for (int i=0; i<nMaxQuad; i++)
    {
        // For each vertex in the quadrilateral, ...
        for (int k=0; k<4; k++)
        {
            // Print either 3 or 4 dimensional coordinates.
            if (mFlags & QU_FOURDIM)
                s->PrintF("%g %g %g %g", p->x, p->y, p->z, p->w);
            else
                s->PrintF("%g %g %g", p->x, p->y, p->z);
            p++;

            // Print the normal vector and color components if supplied.
            if (n)
            {
                s->PrintF("  %g %g %g", n->x, n->y, n->z);
                n++;
            }
            if (c)
            {
                s->PrintF("  %.3g %.3g %.3g %.3g",
                    c->GetRed(), c->GetGreen(), c->GetBlue(), c->GetAlpha());
                c++;
            }

            // Each vertex is on a separate line.
            s->PutC('\n');
        }

        // Each quadrilateral is separated by a blank line.
        s->PutC('\n');
    }
    return !s->error();
}


#if 0
IF0  int GeomQuad::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      int got;
IF0      int dimn = 3;
IF0  
IF0      // Read the header and process the flags.
IF0      mFlags = GeomOldOoglParser::GetHeader(lex,
IF0          "QUAD", keyword, quad_keys, quad_bits);
IF0      if (mFlags & QU_FOURDIM)
IF0          dimn = 4;
IF0  
IF0      if (lex->DataType() == IoDataStream::BINARY)
IF0      {
IF0  // BINARY case has not been tested and is not yet used.
IF0          /*
IF0           * Binary case is easy.
IF0           * Read the q count, then the P, N and C arrays.
IF0           * Error if we get less than the q count promised.
IF0           */
IF0          if (lex->ExpectInt(1, &nMaxQuad) <= 0) 
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading QUAD.  Couldn't read number of quads");
IF0          if (nMaxQuad <= 0 || nMaxQuad > 10000000)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading QUAD BINARY.  Incredible number of QUADs 0x%x",
IF0                  nMaxQuad);
IF0  
IF0          if ( (got=GetQuad(lex, dimn)) < nMaxQuad )
IF0          {
IF0              mP.Clear();
IF0              mN.Clear();
IF0              mColors.Clear();
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading QUAD BINARY.  Expected %d quad%s, got %d",
IF0                  nMaxQuad, &"s"[nMaxQuad==1], got);
IF0          }
IF0      }
IF0      else
IF0      {
IF0          // ASCII case:  Read as many quadrilaterals as are found.
IF0          if ( (nMaxQuad=GetQuad(lex, dimn)) <= 0 )
IF0          {
IF0              mP.Clear();
IF0              mN.Clear();
IF0              mColors.Clear();
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading QUAD.  Expected at least one quad, got %d",
IF0                  nMaxQuad, got);
IF0          }
IF0  
IF0          // Release unneeded storage.
IF0          mP.Trim();
IF0          mN.Trim();
IF0          mColors.Trim();
IF0      }
IF0  
IF0      return 1;
IF0  }
#endif

void GeomQuad::Draw(class MgContext *mg)
{
}

