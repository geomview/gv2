#include "GeomBezier.h"
#include "GeomMesh.h"

#include <math.h>
#include <string.h>
#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
#include "HPoint3.h"
#include "MgColor.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomBezier, Geom);

GeomBezier::GeomBezier(const char *key)
{
    mFlags = mDegreeU = mDegreeV = mDimN = 0;
    mHasUVN = key==NULL || strcmp(key, "BEZ")==0;
    mNu = mNv = 0;
    mNPatch = 0;
}

GeomBezier::~GeomBezier()
{
    Clear();
}

void GeomBezier::Clear()
{
    UTUARRAY_CLEAR(mCtrlPnts, float*)
    UTUARRAY_CLEAR(mStCords, float*)
    UTUARRAY_CLEAR(mColors, MgColorA*)
    UTUARRAY_CLEAR(mMesh, GeomMesh*)
}

static const char *bez_keys[] = { "ST", "C", NULL };
static const short bez_bits[] = {
    GeomBezier::BEZ_ST,
    GeomBezier::BEZ_C,
};

#if 0
IF0  int GeomBezier::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      int	totalfloats, i;
IF0  
IF0      Clear();
IF0      mFlags = GeomOldOoglParser::GetHeader(lex,
IF0  	mHasUVN? "BEZ" : "BBP", keyword, bez_keys, bez_bits);
IF0      mFlags |= BEZ_REMESH;
IF0      mDimN = mDegreeU = mDegreeV = 3;	/* Default bicubic 3-D patch */
IF0      mNu = mNv = 0;
IF0      mNPatch = 0;
IF0  
IF0      if (mHasUVN)
IF0      {
IF0  	if ( (lex->ExpectInt(1, &mDegreeU) < 1) ||
IF0  	     (lex->ExpectInt(1, &mDegreeV) < 1) ||
IF0  	     (lex->ExpectInt(1, &mDimN) < 1) )
IF0  	    throw new IoOldOoglParseException(lex,
IF0  	        "Reading BEZ.  Expected  Nu Nv Nd after header");
IF0  
IF0  	if ( (mDegreeU <= 0 || mDegreeU > MAX_BEZ_DEGREE) ||
IF0  	     (mDegreeV <= 0 || mDegreeV > MAX_BEZ_DEGREE) ||
IF0  	     (mDimN < 3 || mDimN > MAX_BEZ_DIMN) )
IF0  	    throw new IoOldOoglParseException(lex,
IF0  	        "Reading BEZ.  Nu Nv Nd out of range");
IF0      }
IF0  
IF0      totalfloats = (mDegreeU+1)*(mDegreeV+1)*mDimN;
IF0      for (i = 0; lex->LookAhead(IoOldOoglToken::NUMBER); i++)
IF0      {
IF0  	mCtrlPnts[i] = new float[totalfloats];
IF0          if (lex->ExpectFloat(totalfloats, (float*)mCtrlPnts[i]) < totalfloats)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading BEZ.  Incomplete array of control points");
IF0  
IF0          if (mFlags & BEZ_C)
IF0          {
IF0  // Again, VC++ is having some trouble interpreting pointer casts as l-values.
IF0  // they couldn't be doing something as stupid as copying the value of this
IF0  // pointer to a temporary variable, could they????  
IF0  // jcm -- 10/16/97
IF0              MgColorA *c = new MgColorA[4];
IF0      	    mColors[i] = (void *)c;
IF0              /* Load 4 colors, for the 4 corners of the patch, v-major order.*/
IF0  	    for (int j=0; j<4; j++, c++)
IF0  		if (lex->ExpectFloat(4, (float*)*c) < 4)
IF0  		    throw new IoOldOoglParseException(lex, "Reading BEZ.  ");
IF0  	}
IF0  	if (mFlags & BEZ_ST)
IF0  	{
IF0  	    mStCords[i] = new float[8];
IF0  	    if (lex->ExpectFloat(8, (float*)mStCords[i]) < 8)
IF0                  throw new IoOldOoglParseException(lex, "Reading BEZ.  ");
IF0          }
IF0      }
IF0  
IF0      mNPatch = i;
IF0      return 1;
IF0  }
#endif


int GeomBezier::Save(IoDataStream *s)
{
    float *p;
    int i, u, v;

    // Create a header and print it out.
    char keys[sizeof(bez_keys)/sizeof(bez_keys[0])+1];
    //    GeomOldOoglParser::MakeHeader(mFlags, keys, bez_keys, bez_bits);
    s->PrintF("%s%s", keys, mHasUVN?"BEZ":"BBP");
    if (mHasUVN)
	s->PrintF(" %d %d %d", mDegreeU, mDegreeV, mDimN);
    s->PutC('\n');

    // Print each patch.
    for (i=0; i<mNPatch; i++)
    {
	    p = (float*)mCtrlPnts[i];
	    for (v = 0; v <= mDegreeV; v++)
	    {
	        s->PutC('\n');
	        for (u = 0; u <= mDegreeU; u++)
	        {
		    if (mDimN == 4)
		        s->PrintF("%11.8g ", *p++);
		    s->PrintF("%11.8g %11.8g %11.8g\n", p[0], p[1], p[2]);
		    p += 3;
	        }
	    }

	    if(mFlags & BEZ_C && mColors[i] != NULL)
	    {
	        s->PutC('\n');
	        MgColorA *c = (MgColorA*)mColors[i];
	        for (u = 0, p = (float*)*c; u < 4; u++, p=(float*)*++c)
		    s->PrintF("%6g %6g %6g %6g\n", p[0], p[1], p[2], p[3]);
	    }

	    if (mFlags & BEZ_ST && mStCords[i] != NULL)
	    {
	        s->PutC('\n');
	        for (u = 0, p = (float*)mStCords[i]; u < 4; u++, p += 2)
		    s->PrintF("%8g %8g  ", p[0], p[1]);
	        s->PutC('\n');
	    }
    }

    return !s->error();
}


void GeomBezier::Draw(MgContext *mg)
{
}
