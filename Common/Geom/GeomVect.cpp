#include "GeomVect.h"

#include <string.h>
#include <math.h>

#include "HPoint3.h"
#include "MgColor.h"
#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomVect, Geom);

GeomVect::GeomVect()
{
    mNVec = mNVerts = mNColors = 0;
    mFlags = 0;
    mSeq = 0;
    mP = NULL;
    mColors = NULL;
    mNVert = NULL;
    mVNColors = NULL;
}

GeomVect::~GeomVect()
{
    if (mNVert) delete mNVert;
    if (mVNColors) delete mVNColors;
    if (mP) delete mP;
    if (mColors) delete mColors;
}

static const char  vect_keys[] = "4";
static const short vect_bits[] = {
    GeomVect::VE_FOURDIM,
};

#define VSANE   (0 <= mNColors && mNColors <= mNVerts && \
                mNVec <= mNVerts && mNVerts < 9999999)

int GeomVect::VectSane()
{
    register int i;
    register int vleft, cleft;
    register short *p, *c;

    if (!VSANE) return 0;
    vleft = mNVerts;
    cleft = mNColors;
    for(i = mNVec, p = mNVert, c = mVNColors; --i >= 0; p++, c++) {
        if (*p == 0 || (vleft -= abs(*p)) < 0)
            return 0;
        if (*c < 0 || (cleft -= *c) < 0)
            return 0;
    }
    if (vleft > 0 || cleft > 0)
        return 0;
    return 1;
}

int GeomVect::Save(IoDataStream *s)
{
    register int i; //, k;
    HPoint3 *p;
//    Point3 *n;
    MgColorA *c;

    // Make the header and print it out.
    char keys[sizeof(vect_keys)/sizeof(vect_keys[0])+1];
    //    GeomOldOoglParser::MakeHeader(mFlags, keys, vect_keys, vect_bits);
    s->PrintF("%sVECT\n%d %d %d\n\n", keys, mNVec, mNVerts, mNColors);

    // Print the vertices per polyline, followed by the colors per polyline.
    for (i = 0; i < mNVec; i++)
        s->PrintF( "%d\n", mNVert[i]);
    s->PutC('\n');
    for (i = 0; i < mNVec; i++)
        s->PrintF( "%d\n", mVNColors[i]);
    s->PutC('\n');

    // Print the vertices, either 3 or 4 dimensional.
    const char *fmt = (mFlags & VE_FOURDIM)? "%g %g %g %g\n" : "%g %g %g\n";
    for (i = mNVerts, p = mP; --i >= 0; p++)
        s->PrintF(fmt, p->x, p->y, p->z, p->w);
    s->PutC('\n');

#if 0 // Old code.
    if (mFlags & VE_FOURDIM)
        for (i = mNVerts, p = mP; --i >= 0; p++)
            s->PrintF( "%g %g %g %g\n", p->x, p->y, p->z, p->w);
    else
        for (i = mNVerts, p = mP; --i >= 0; p++)
            s->PrintF( "%g %g %g\n", p->x, p->y, p->z);
#endif

    // Print the colors.
    for(i = mNColors, c = mColors; --i >= 0; c++)
        s->PrintF( "%.3g %.3g %.3g %.3g\n",
                c->GetRed(), c->GetGreen(), c->GetBlue(), c->GetAlpha());

    return !s->error();
}


#if 0
IF0  int GeomVect::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      register int i;
IF0      int dimn = 3;
IF0  
IF0      // Read and process the flags.
IF0      mFlags = GeomOldOoglParser::GetHeader(lex,
IF0          "VECT", keyword, vect_keys, vect_bits);
IF0      if (mFlags & VE_FOURDIM)
IF0          dimn = 4;
IF0  
IF0      // Clear any old data.
IF0      if (mNVert) delete mNVert;
IF0      if (mVNColors) delete mVNColors;
IF0      if (mP) delete mP;
IF0      if (mColors) delete mColors;
IF0      mNVert = NULL;
IF0      mVNColors = NULL;
IF0      mP = NULL;
IF0      mColors = NULL;
IF0  
IF0      // Read the header and see if they make sense.
IF0      if (lex->ExpectInt(1, &mNVec) < 1 ||
IF0          lex->ExpectInt(1, &mNVerts) < 1 ||
IF0          lex->ExpectInt(1, &mNColors) < 1)
IF0      {
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading VECT.  Can't read header counts");
IF0      }
IF0      if (!VSANE)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading VECT.  Inconsistent VECT header counts %d %d %d",
IF0              mNVec, mNVerts, mNColors);
IF0  
IF0      // Read the vertex and color counts of for each polyline.
IF0      mNVert = new short[mNVec];
IF0      mVNColors = new short[mNVec];
IF0      mP = new HPoint3[mNVerts];
IF0      mColors = new MgColorA[(mNColors>0) ? mNColors : 1];
IF0      if ((i = lex->ExpectShort(mNVec, mNVert)) < mNVec)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading VECT.  Bad vertex count in %d'th polyline (of %d)",
IF0              i, mNVec);
IF0      if ((i = lex->ExpectShort(mNVec, mVNColors)) < mNVec)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading VECT.  Bad color count in %d'th polyline (of %d)",
IF0              i, mNVec);
IF0  
IF0      // Read the vertices.
IF0      /* if the points are 3D points, we have to convert them to the native
IF0          4D data structure */
IF0      if (dimn == 3)
IF0      {
IF0          register HPoint3 *p;
IF0          for(i = mNVerts, p = mP; --i >= 0; p++)
IF0          {
IF0              if (lex->ExpectFloat(3, (float *)p) < 3)
IF0                  throw new IoOldOoglParseException(lex,
IF0                      "Reading VECT.  Bad %dth vertex (of %d)",
IF0                      mNVerts-i, mNVerts);
IF0              p->w = 1;
IF0          }
IF0      }
IF0  #if 0 // I dont know why this else statement doesnt work!  -- Lori Nov 11, 1997
IF0      // (it causes an internal compiler error with gcc, hence this
IF0      // awkward workaround.  mbp Wed Nov 12 22:53:57 1997)
IF0      else
IF0  #endif
IF0      if (dimn != 3)
IF0      {
IF0          i = lex->ExpectFloat(4*mNVerts, (float *)mP);
IF0          if (i < 4*mNVerts)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading VECT.  Bad %dth vertex (of %d)", int(i/4), mNVerts);
IF0      }
IF0  
IF0      // Read the colors.
IF0      if (mNColors > 0)
IF0      {
IF0        for (int j = 0; j < mNColors; j++)
IF0          if ((i=lex->ExpectFloat(4, (float *)mColors[j])) < 4)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading VECT.  Bad %dth color (of %d)", j, mNColors);
IF0      }
IF0  
IF0      // Make sure the polyline/color add up to the vertex and color counts
IF0      // in the header.
IF0      // NOTE: This could be done right after reading the vertex and color counts.
IF0      if (!VectSane())
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading VECT.  Polyline/color counts inconsistent with header");
IF0  
IF0      return 1;
IF0  }
#endif

void GeomVect::Draw(class MgContext *mg)
{
}

