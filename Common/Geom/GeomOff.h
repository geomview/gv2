//-*-C++-*-
#ifndef OFF_H
#define OFF_H


// class GeomOff
// 
// The OFF (Object File Format) object represent collections of planar
// polygons with possibly shared vertices, a convenient way to describe
// polyhedra.  The polygons may be concave but there's no provision for
// polygons containing holes. 
//
// OOGL ASCII format:
//      [ST][C][c][N][4][n]OFF [ndim]
//      NVerts NFaces NEdges
//      Vertex(0) ... Vertex(NVerts-1)
//      N(0) iVert(0,1) iVert(0,2) ... iVert(0,N(0))    [color]
//      N(1) iVert(1,1) iVert(1,2) ... iVert(1,N(1))    [color]
//      ...
//      N(NFaces) iVert(NFaces,1) iVert(NFaces,2) ... iVert(NFaces,N(1)) [color]
//
// NVerts, NFaces, and NEdges are the number of vertices, faces and edges,
// respectively.  Current software does not use nor check NEdges; it needn't
// be correct but must be present.
//
// Vertex(0) ... Vertex(NVerts-1) are the coordinates of the vertices,
// along with normals, colors, and texture map coordinates if specified
// in the header.
//
// Following the vertices are the faces, each represented with the number of
// vertices on the face first, then the INDICES into the first list of vertices
// of the vertices of the face.
//
// Color is present if the 'c' option is specified in the header.  First
// The number of color components is read, then the components.  A color
// may have 4 or fewer components:
//      0 components:   the default color
//      1 integer:      index into the colormap
//      3 or 4 floating point numbers:
//                      RGB and possibly alpha values in the range 0..255
//      3 or 4 floating point numbers:
//                      RGB and possibly alpha values in the range 0..1
//
// BINARY format is supported but hasn't been tested.

#include "Geom.h"
#include "HPoint3.h"
#include "MgColor.h"
#include "IoOoglLexer.h"

typedef struct Vertex
{
  HPoint3  pt;			// coords of vertex
  MgColorA vcol;		// vertex color
  Point3   vn;			// vertex normal
  float    st[2];		// vertex texture coords
} Vertex;

typedef struct Poly
{
  int       n_vertices;		// # vertices in this polygon
  Vertex    **v;		// array of pointers to 'Vertex'es
  MgColorA  pcol;		// color of this polygon
  Point3    pn;			// normal vector for this polygon

  Poly::Poly()  { v = NULL; }
  Poly::~Poly() { if (v) delete [] v; }

} Poly;

class GeomOff : public Geom
{
  TYPE_DECLARE_TYPEINFO(GeomOff);

public:
  GeomOff();
  virtual ~GeomOff();

  //virtual int Load(class IoOldOoglLexer *lex,    char *keyword = NULL);
  virtual int Load(class IoOoglLexer *lex, char *keyword = NULL);
  virtual int Save(class IoDataStream *s);
  virtual void Draw(class MgContext *mg);

  enum
  {
    PL_HASVN        = 0x1,	// Per-vertex normals (vn) valid
    PL_HASPN        = 0x2,	// Per-polygon normals (pn) valid
    PL_HASVCOL      = 0x4,	// Per-vertex colors (vcol) valid
    PL_HASPCOL      = 0x8,	// Per-polygon colors (pcol) valid
    PL_EVNORM       = 0x10,	// Normals are everted
    PL_HASST        = 0x20,	// Has s,t texture coords

    PL_FOURDIM      = 0x40,	// Four dimensional
    PL_MAKENORM     = 0x80,	// "smooth surface": we compute vtx normals 
  };

private:
  void ComputeNormals();

private:
  int     mFlags;		// Stores option flags.
  int     mNPolys;		// Number of polygons (from header)
  int     mNVerts;		// Number of vertices (from header)
  Poly   *mP;			// Array[_npolys] of polygon info.
  Vertex *mVL;			// Array[_npolys] of vertex info.
  int     mSeq;			// for 4D->3D tforms

  void    StoreLexerNewlineSignificance(IoOoglLexer *lex) {
    mLexerNewlineSignificance = lex->GetNewlineSignificance();
  }
  void    RestoreLexerNewlineSignificance(IoOoglLexer *lex) {
    lex->SetNewlineSignificance(mLexerNewlineSignificance);
  }
  int     mLexerNewlineSignificance;
};


#endif // OFF_H
