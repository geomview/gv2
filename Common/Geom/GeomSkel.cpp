#include "GeomSkel.h"

#include <math.h>
#include <string.h>

#include "HPoint3.h"
#include "MgColor.h"
#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomSkel, Geom);

// We must initialize all MgColorA's in the array mColors to something,
// otherwise the class's virtual functions will not work.  The program
// will crash if you try to call them.
static MgColorA black = MgColorA(0,0,0,1);

GeomSkel::GeomSkel() :
    // Initialize the variable-length vectors to the proper sizes.
    mVI(sizeof(int), NULL, 40),
    mColors(sizeof(MgColorA), &black, 10)
{
    mFlags = 0;
    mDim = 3;
    mNVerts = mNLines = 0;
    mNVI = mNColors = 0;
    mP = NULL;
    mLines = NULL;
}

GeomSkel::~GeomSkel()
{
    if (mP) delete mP;
    if (mLines) delete mLines;
    // The variable-length arrays will automatically be deleted.
}

static const char  skel_keys[] = "c4n";
static const short skel_bits[] = {
  GeomSkel::SK_PCOL,
  GeomSkel::SK_HOMOGEN,
  GeomSkel::SK_NDIM,
};


#if 0
IF0  int GeomSkel::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      register int i, k, got;
IF0      MgColorA *cp;
IF0      float *vp;
IF0      Skline *lp;
IF0  
IF0      if (mP) delete mP;
IF0      if (mLines) delete mLines;
IF0      mP = NULL;
IF0      mLines = NULL;
IF0      mNVerts = mNLines = 0;
IF0      mNVI = mNColors = 0;
IF0  
IF0      mFlags = GeomOldOoglParser::GetHeader(lex,
IF0  	"SKEL", keyword, skel_keys, skel_bits);
IF0  
IF0      mDim = 3;
IF0      if (mFlags & SK_NDIM && lex->ExpectInt(1, &mDim) < 1)
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading SKEL.  Expected dimension");
IF0  
IF0      //s->dim = s->geomflags & SK_HOMOGEN ? dim : dim+1;
IF0      if (!(mFlags & SK_HOMOGEN))
IF0          mDim++;
IF0  
IF0      if (lex->ExpectInt(1, &mNVerts) < 1 ||
IF0          lex->ExpectInt(1, &mNLines) < 1)
IF0      {
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading SKEL.  Expected nvertices, nlines");
IF0      }
IF0  
IF0      mP = new float[mNVerts * mDim];
IF0      mLines = new Skline[mNLines];
IF0  
IF0  
IF0      // Read the vertices into mP.
IF0  
IF0      k = (mFlags & SK_HOMOGEN) ? mDim : mDim - 1;
IF0      for (i = 0, vp = mP; i < mNVerts; i++, vp += mDim)
IF0      {
IF0  	vp[mDim - 1] = 1.0;			/* homogeneous component */
IF0  	if (lex->ExpectFloat(k, vp) < k)
IF0  	{
IF0  	    throw new IoOldOoglParseException(lex,
IF0  	        "Reading SKEL.  Error reading vertex %d of %d", i, mNVerts);
IF0  	}
IF0      }
IF0  
IF0  
IF0      // Read the polylines into mLines.
IF0  
IF0      mNVI = mNColors = 0;
IF0      for (i = 0, lp = mLines; i < mNLines; i++, lp++)
IF0      {
IF0  	// Read the number of vertices first.
IF0  	if (lex->ExpectInt(1, &lp->nv) < 1 || lp->nv <= 0)
IF0  	{
IF0  	    throw new IoOldOoglParseException(lex,
IF0  	        "Reading SKEL.  Expected vertex count on polyline %d of %d",
IF0  	        i, mNLines);
IF0  	}
IF0  
IF0  	// Then read the vertex-indices to our global list.
IF0  	lp->v0 = mNVI;
IF0  	mNVI += lp->nv;
IF0  	mVI.Get(mNVI); // Make sure there is room for more ints.
IF0  
IF0  	if (lex->ExpectInt(lp->nv, (int*)mVI.Get(lp->v0)) < lp->nv)
IF0  	{
IF0  	    throw new IoOldOoglParseException(lex,
IF0  	        "Reading SKEL.  Expected %d vertex indices in polyline %d of %d",
IF0  	        lp->nv, i, mNLines);
IF0  	}
IF0  
IF0  	// If there are per-polyline colors, 
IF0  	lp->c0 = mNColors;
IF0  	if (mFlags & SK_PCOL)
IF0  	{
IF0  	    // First read the number of color components, then the components.
IF0  	    int ncol;
IF0              if (lex->ExpectInt(1, &ncol) < 1)
IF0  		throw new IoOldOoglParseException(lex,
IF0  		    "Reading SKEL.  Expected number of color components");
IF0  	    cp = (MgColorA*)mColors.Get(mNColors++);
IF0  	    *cp = black;
IF0              if ( (got=lex->ExpectFloat(ncol, (float *)*cp)) < ncol)
IF0  		throw new IoOldOoglParseException(lex,
IF0  		    "Reading SKEL.  Expected %d color components, got %d",
IF0  		    ncol, got);
IF0  	    lp->nc = 1;
IF0  	}
IF0  	else
IF0  	    lp->nc = 0;
IF0      }
IF0  
IF0      return 1;
IF0  }
#endif

int GeomSkel::Save(IoDataStream *s)
{
    int i, j, d;
    float *p;
    int *vp;
    Skline *l;

    char keys[sizeof(skel_keys)/sizeof(skel_keys[0])+1];

    // Make the header and print it out.
    //    GeomOldOoglParser::MakeHeader(mFlags, keys, skel_keys, skel_bits);
    s->PrintF("%sSKEL", keys);

    // Print the number of dimensions if it was specified in the flags.
    d = mFlags & SK_HOMOGEN ? mDim : mDim-1;
    if (mFlags & SK_NDIM)
        s->PrintF(" %d", d);
    s->PrintF("\n%d %d\n\n", mNVerts, mNLines);

    // Print the vertices.
    for (i = 0, p = mP; i < mNVerts; i++, p += mDim)
    {
	s->fputnf(d, p, IoDataStream::ASCII);
	s->PutC('\n');
    }
    s->PutC('\n');

    // Print the polylines.
    for (i = 0, l = mLines; i < mNLines; i++, l++)
    {
	// Print the count and the indices.
	s->PrintF("%d\t", l->nv);
	for (j = 0, vp = (int*)mVI.Get(l->v0); j < l->nv; j++, vp++)
	    s->PrintF("%d ", *vp);

	// Print the colors, if any.
	if (l->nc > 0)
	{
	    s->PrintF("\t4  ");
	    s->fputnf(4, (float*)*(MgColorA*)mColors.Get(l->c0), IoDataStream::ASCII);
	}
	s->PutC('\n');
    }

    return !s->error();
}


void GeomSkel::Draw(class MgContext *mg)
{
}

