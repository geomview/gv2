#include "GeomOff.h"

#include <string.h>
#include <math.h>

#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
#include "IoOoglParseException.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"


TYPE_IMPLEMENT_TYPEINFO1(GeomOff, Geom);

GeomOff::GeomOff()
{
  mNPolys = 0;
  mNVerts = 0;
  mP = NULL;
  mVL = NULL;
  mFlags = 0;
  mSeq = 0;
}

GeomOff::~GeomOff()
{
// jcm-purify 12/5/97
  if (mP) delete [] mP;
  if (mVL) delete [] mVL;
}

static const char *off_keys[] = { "ST", "C", "c", "N", "4", "S", NULL };
static const short off_bits[] = {
    GeomOff::PL_HASST,
    GeomOff::PL_HASVCOL,
    GeomOff::PL_HASPCOL,
    GeomOff::PL_HASVN,
    GeomOff::PL_FOURDIM,
    GeomOff::PL_MAKENORM,
};


int GeomOff::Load(class IoOoglLexer *lex, char *keyword)
{
    int edges;
    register Vertex *v;
    register int i;

    int dimn = 3;
    int makenorm = 0;

    static MgColorA black = MgColorA(0,0,0,0);

    // Fix mFlags later; it gets set with values from the keyword.
    // For now, just assume keyword was "OFF".
    mFlags = 0;


    if (mFlags & PL_FOURDIM)
        dimn = 4;
    if (mFlags & PL_MAKENORM)
        makenorm = 1;

    if (mP)  delete mP;
    if (mVL) delete mVL;
    mP = NULL;
    mVL = NULL;

    {
      int bad = (lex->ExpectNum(1, &mNVerts, IoOoglLexer::INT) < 1);
      if (!bad) bad |= (lex->ExpectNum(1, &mNPolys, IoOoglLexer::INT) < 1);
      if (!bad) bad |= (lex->ExpectNum(1, &edges,   IoOoglLexer::INT) < 1);
      if (bad) {
        throw new IoOoglParseException(lex,
	      "Reading OFF.  Expected  NVertices NFaces NEdges");
      }
    }

    //    printf("mNVerts = %1d\n", mNVerts);
    //    printf("mNPolys = %1d\n", mNPolys);
    //    printf("edges = %1d\n", edges);

    // Read all the vertices.
    mVL = new Vertex[mNVerts];
    for (v = mVL, i = 0; i < mNVerts; v++, i++)
    {
      int bad = (lex->ExpectNum(dimn,(float *)&v->pt,
				IoOoglLexer::FLOAT) < dimn);
      if (!bad && mFlags&PL_HASVN)
	bad |= (lex->ExpectNum(3,(float *)&v->vn,
				 IoOoglLexer::FLOAT) < 3);
      if (!bad && mFlags&PL_HASVCOL)
	bad |= (lex->ExpectNum(4,(float *)&v->vcol,
				 IoOoglLexer::FLOAT)<4);
      if (!bad && mFlags&PL_HASST)
	bad |= (lex->ExpectNum(2, &v->st[0],
				 IoOoglLexer::FLOAT) < 2);
      if (bad) {
	throw new IoOoglParseException(lex,
                "Reading OFF.  Bad vertex %d (of %d)", i, mNVerts);
      }
      if (dimn == 3)  v->pt.w = 1.0f;
    }


    // From this point on (to the end of the OFF), newlines are significant.
    StoreLexerNewlineSignificance(lex);
    lex->SetNewlineSignificance(1);
    // Except that before starting to parse the vertices, we want
    // to make sure we've read past any current newlines and
    // are ready to read the first token on the first vertex line.
    while (lex->LookAhead() == IoOoglLexer::NEWLINE) {
      lex->Scan();
    }

    // Read all the faces (polygons).
    mP = new Poly[mNPolys];
    for(i = 0; i < mNPolys; i++)
    {
        register Poly *p;
        register int k;

        p = &mP[i];

        // Read the number of vertices in the polygon.
	{
	  int bad = (lex->ExpectNum(1, &p->n_vertices,
				    IoOoglLexer::INT) < 1);
	  if (bad || p->n_vertices <= 0) {
	    RestoreLexerNewlineSignificance(lex);
            throw new IoOoglParseException(lex,
                "Reading OFF.  Bad %d'th polygon (of %d)", i, mNPolys);
	  }
	}

        // Read the index of each of the vertices.
        p->v = new Vertex*[p->n_vertices];
        for(k = 0; k < p->n_vertices; k++)
        {
	  int index;

	  int bad = (lex->ExpectNum(1, &index, IoOoglLexer::INT) < 1);
	  if(bad || index < 0 || index >= mNVerts) {
	    mNPolys = ++i;
	    RestoreLexerNewlineSignificance(lex);
	    throw new IoOoglParseException(lex,
	              "Reading OFF.  Bad index %d on %d'th polygon (of %d)", 
					   index, i, p->n_vertices);
            }
	  p->v[k] = &mVL[index];
        }

        // Pick up the color, if any.
	{
	  double rgba[4] = {0.0, 0.0, 0.0, 170/255.0};
	  // default alpha 'semitransparent' from old oogl code
	  int k = 0;
	  do {
	    if (k > 4) {
	      RestoreLexerNewlineSignificance(lex);
	      throw new IoOoglParseException(lex,
					     "Reading OFF.  Bad face color "
					     "on face %d (of %d) [can't have "
					     "> 4 color components",
					     i, mNPolys);
	    }
	    lex->Scan();
	    if ( (lex->GetType()!=IoOoglLexer::NEWLINE) &&
		 (lex->GetType()!=IoOoglLexer::EOI)        ) {
	      mFlags |= PL_HASPCOL;
	      switch (lex->GetType()) {
	      case IoOoglLexer::INT:
		rgba[k] = lex->GetIntValue()/255.0;
		break;
	      case IoOoglLexer::DOUBLE:
		rgba[k] = lex->GetDoubleValue();
		break;
	      default:
		RestoreLexerNewlineSignificance(lex);
		throw new IoOoglParseException(lex,
	       "Reading OFF.  Bad face color on face %d (of %d)",
					       i, mNPolys);
		break;
	      }
	    }
	    ++k;
	  } while ( (lex->GetType()!=IoOoglLexer::NEWLINE) &&
		    (lex->GetType()!=IoOoglLexer::EOI)        );

	  // At this point, k is the number of color components
	  // we got (0-4).  We apply it to the polygon iff we
	  // don't already have vertex colors.
	  if ((mFlags & PL_HASVCOL) == 0) {
	    if (k==3) {
	      rgba[3] = 170/255.0;
	    }
	    // Note: this code currently does not support the case
	    // of 1 color component, which is supposed to be an
	    // index into a colormap.  Add that later.
	    p->pcol.SetRGBA(rgba[0], rgba[1], rgba[2], rgba[3]);
	  }

	}
    }

    if (makenorm && !(mFlags & PL_HASVN)) {
        mFlags |= PL_HASVN;
        mFlags &= ~PL_HASPN;            /* Leave vertex-normals only */
    }

    RestoreLexerNewlineSignificance(lex);
    return 1;
}



#if 0
IF0  int GeomOff::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      int edges;
IF0      register Vertex *v;
IF0      register int i;
IF0  
IF0      int dimn = 3;
IF0      int makenorm = 0;
IF0  
IF0      static MgColorA black = MgColorA(0,0,0,0);
IF0  
IF0      mFlags = GeomOldOoglParser::GetHeader(lex,
IF0          "OFF", keyword, off_keys, off_bits);
IF0  
IF0      if (mFlags & PL_FOURDIM)
IF0          dimn = 4;
IF0      if (mFlags & PL_MAKENORM)
IF0          makenorm = 1;
IF0      if (lex->DataType() == IoDataStream::BINARY)
IF0          mFlags |= PL_HASPCOL;
IF0  
IF0      if (mP) delete mP;
IF0      if (mVL) delete mVL;
IF0      mP = NULL;
IF0      mVL = NULL;
IF0  
IF0      if ( lex->ExpectInt(1, &mNVerts) < 1 ||
IF0           lex->ExpectInt(1, &mNPolys) < 1 ||
IF0           lex->ExpectInt(1, &edges) < 1 )
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading OFF.  Expected  NVertices NFaces NEdges");
IF0  
IF0      // Read all the vertices.
IF0      mVL = new Vertex[mNVerts];
IF0      for (v = mVL, i = 0; i < mNVerts; v++, i++)
IF0      {
IF0          if (                 lex->ExpectFloat(dimn,(float *)&v->pt) < dimn ||
IF0            ((mFlags&PL_HASVN)   && lex->ExpectFloat(3,(float *)&v->vn) < 3) ||
IF0            ((mFlags&PL_HASVCOL) && lex->ExpectFloat(4,(float *)&v->vcol)<4) ||
IF0            ((mFlags&PL_HASST)   && lex->ExpectFloat(2, &v->st[0]) < 2) )
IF0          {
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading OFF.  Bad vertex %d (of %d)", i, mNVerts);
IF0          }
IF0          if (dimn == 3)  v->pt.w = 1.0f;
IF0      }
IF0  
IF0      // Read all the faces (polygons).
IF0      mP = new Poly[mNPolys];
IF0      for(i = 0; i < mNPolys; i++)
IF0      {
IF0          register Poly *p;
IF0          register int k;
IF0  
IF0          p = &mP[i];
IF0  
IF0          // Read the number of vertices in the polygon.
IF0          int rcode = lex->ExpectInt(1, &p->n_vertices);
IF0          if (rcode < 1 || p->n_vertices <= 0)
IF0          {
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading OFF.  Bad %d'th polygon (of %d)", i, mNPolys);
IF0          }
IF0  
IF0          // Read the index of each of the vertices.
IF0          p->v = new Vertex*[p->n_vertices];
IF0          for(k = 0; k < p->n_vertices; k++)
IF0          {
IF0              int index;
IF0  
IF0  	    int rcode = lex->ExpectInt(1, &index);
IF0              if(rcode <= 0 ||
IF0                 index < 0 || index >= mNVerts)
IF0              {
IF0                  mNPolys = ++i;
IF0                  throw new IoOldOoglParseException(lex,
IF0                      "Reading OFF.  Bad index %d on %d'th polygon (of %d)", 
IF0                      index, i, p->n_vertices);
IF0              }
IF0              p->v[k] = &mVL[index];
IF0          }
IF0  
IF0          // Pick up the color, if any.
IF0          k = 0; p->pcol = black;
IF0  	if (lex->DataType() == IoDataStream::BINARY) {
IF0  	  // In the binary format, every face is followed by an
IF0  	  // integer specifying the number of color components for
IF0  	  // that face, and then by that number of floats (the
IF0  	  // components themselves).
IF0  	  int rcode1 = lex->ExpectInt(1, &k);
IF0  	  int rcode2 = lex->ExpectFloat(k, (float *)(p->pcol));
IF0  	  if ( rcode1 < 1 || rcode2 < k ) {
IF0              throw new IoOldOoglParseException(lex,
IF0  		"Reading OFF.  Bad face color on face %d (of %d)",
IF0                  i, mNPolys);
IF0  	  }
IF0  	}
IF0  
IF0          // Apply the color to the polygon only if we are not already applying
IF0          // color to the vertices.
IF0          if ((mFlags & PL_HASVCOL) == 0)
IF0          {
IF0              if (k != 1 && (  p->pcol.GetRed() > 1
IF0                          || p->pcol.GetGreen() > 1
IF0                          || p->pcol.GetBlue() > 1
IF0                          || p->pcol.GetAlpha() > 1) )
IF0              {
IF0                  p->pcol.SetRed( p->pcol.GetRed() / 255 );
IF0                  p->pcol.SetGreen( p->pcol.GetGreen() / 255 );
IF0                  p->pcol.SetBlue( p->pcol.GetBlue() / 255 );
IF0                  p->pcol.SetAlpha( p->pcol.GetAlpha() / 255 );
IF0              }
IF0  
IF0              switch(k)
IF0              {
IF0              case 0:
IF0                  p->pcol.SetRed(170/255.0);              /* Gray */
IF0                  p->pcol.SetGreen(p->pcol.GetRed());
IF0              case 2:
IF0                  p->pcol.SetBlue(p->pcol.GetBlue());
IF0              case 3:
IF0                  p->pcol.SetAlpha(170/255.0);            /* Semitransparent */
IF0                  break;
IF0              case 1:                                     /* use colormap */
IF0                  //if ( colormap == NULL )
IF0                  //  LoadCmap("cmap.fmap");
IF0                  // index = p->pcol.GetRed();
IF0                  // if((unsigned)index >= SIZEOF_CMAP) index = 0;
IF0                  // p->pcol = colormap[index];
IF0                  break;
IF0              }                           /* case 4, all components supplied */
IF0          }
IF0      }
IF0  
IF0      if (makenorm && !(mFlags & PL_HASVN))
IF0      {
IF0          mFlags |= PL_HASVN;
IF0          mFlags &= ~PL_HASPN;            /* Leave vertex-normals only */
IF0      }
IF0      return 1;
IF0  }
#endif

void GeomOff::ComputeNormals()
{
  register int  i, n;
  float           len;
  register Poly *p;
  Vertex                **vp;
  register Vertex       *v, *v2, *v3;
  register float        x, y, z;

  if(!(mFlags & PL_HASPN)) {
    /* Create per-polygon normals */
    for (i = mNPolys, p = mP; --i >= 0; p++) {
      x = y = z = 0.0f;
      if((n = p->n_vertices) >= 3) {
        v = p->v[n-2];
        v2 = p->v[n-1];
        vp = p->v;

#define ANTI(P,Q)  (v2->pt.P - v->pt.P) * (v3->pt.Q - v->pt.Q) - \
        (v2->pt.Q - v->pt.Q) * (v3->pt.P - v->pt.P)

          do {
            v3 = *vp;
            x += ANTI(y,z);
            y += ANTI(z,x);
            z += ANTI(x,y);
            v = v2;
            v2 = v3;
            vp++;
          } while(--n > 0);
        len = (float)sqrt(x*x + y*y + z*z);
        if(len > 0.0) {
          if(mFlags & PL_EVNORM)
            len = -len;
          len = 1.0f/len;
          x *= len;
          y *= len;
          z *= len;
        }
        p->pn.x = x;
        p->pn.y = y;
        p->pn.z = z;
      }
    }
    mFlags |= PL_HASPN;
  }

  if(!(mFlags & PL_HASVN)) {
            
    for(i = mNVerts, v = mVL; --i >= 0; v++) {
      v->vn.x = v->vn.y = v->vn.z = 0.0f;
    }
    for(i = mNPolys, p = mP; --i >= 0; p++) {
      for(n = p->n_vertices, vp = p->v; --n >= 0; vp++) {
        v = *vp;
        v->vn.x += p->pn.x;
        v->vn.y += p->pn.y;
        v->vn.z += p->pn.z;
      }
    }
    for(i = mNVerts, v = mVL; --i >= 0; v++) {
      len = (float)sqrt(v->vn.x*v->vn.x + v->vn.y*v->vn.y + v->vn.z*v->vn.z);
      if(len > 0) {
        if(mFlags & PL_EVNORM)
          len = -len;
        len = 1.0f/len;
        v->vn.x *= len;
        v->vn.y *= len;
        v->vn.z *= len;
      }
    }
    mFlags |= PL_HASVN;
  }

}


void GeomOff::Draw(MgContext *mg)
{
  /*
   * The drawing routines might need either polygon or vertex normals,
   * so if either is missing and either might be needed,
   * we force it to be computed.
   */
  if((mFlags & (PL_HASVN|PL_HASPN)) != (PL_HASVN|PL_HASPN)) {
    register MgAppearance *ap = mg->GetAppearance();
    if(   (   ap->GetShading() != MgAppearance::F_CONSTANT
           && ap->GetFlags() & MgAppearance::F_FACEDRAW)
       || ap->GetFlags() & MgAppearance::F_NORMALDRAW)
      ComputeNormals();
  }

// We need to get rid of the dual struct poly definitions.

  mg->Polylist(mNPolys, (MgContext::Poly *)mP, mNVerts, (MgContext::Vertex *)mVL, mFlags);
}


///
/// THIS IS JUST FOR TESTING.  SOME FLAGS ARE IGNORED I THINK -Lori.
///
int GeomOff::Save(IoDataStream *s)
{
    Geom::Save(s);

    int i, j;
    Vertex *v;
    char keys[sizeof(off_keys)/sizeof(off_keys[0])*2+1];

    //GeomOldOoglParser::MakeHeader(mFlags, keys, off_keys, off_bits);
    //s->PrintF("%sOFF\n%d %d %d\n\n", keys, mNVerts, mNPolys, 0);
    s->PrintF("OFF\n%d %d %d\n\n", mNVerts, mNPolys, 0);

    for (v = mVL, i = 0; i < mNVerts; v++, i++)
    {
        s->PrintF("%g %g %g", v->pt.x, v->pt.y, v->pt.z);
        if (mFlags & PL_FOURDIM) 
            s->PrintF(" %g", v->pt.w);
        if (mFlags & PL_HASVN) 
            s->PrintF("\t%g %g %g", v->vn.x, v->vn.y, v->vn.z);
        if (mFlags & PL_HASVCOL)
            s->PrintF("\t%g %g %g %g",
                v->vcol[0],v->vcol[1],v->vcol[2],v->vcol[3]);
        if (mFlags & PL_HASST)
            s->PrintF("\t%g %g", v->st[0], v->st[1]);
        s->PrintF("\n");
    }
    s->PrintF("\n");

    for (i=0; i<mNPolys; i++)
    {
        Poly *p = &mP[i];
        s->PrintF("%d  ", p->n_vertices);

        for (j=0; j<p->n_vertices; j++)
            s->PrintF("%d ", p->v[j] - &mVL[0]);

        if (mFlags & PL_HASPCOL)
            s->PrintF("\t%g %g %g %g",
                p->pcol.GetRed(), p->pcol.GetGreen(),
                p->pcol.GetBlue(), p->pcol.GetAlpha());
        s->PrintF("\n");
    }
    s->PrintF("\n");

    return !s->error();
}

