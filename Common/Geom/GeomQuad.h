//-*-C++-*-
#ifndef GEOMQUAD_H
#define GEOMQUAD_H


// class GeomQuad
// 
// A QUAD is a collection of quadrilaterals.  Any number of quadrilaterals
// may appear in the object.
//
// OOGL ASCII format:
//	[C][N][4]QUAD
//	Vertex(1,1) Vertex(1,2) Vertex(1,3) Vertex(1,4)
//	Vertex(2,1) Vertex(2,2) Vertex(2,3) Vertex(2,4)
//	...
//	Vertex(N,1) Vertex(N,2) Vertex(N,3) Vertex(N,4)
// for some N
//
// BINARY format is not yet supported.

#include "UtVVec.h"
#include "Geom.h"
#include "HPoint3.h"
#include "MgColor.h"

typedef HPoint3 QuadP[4];
typedef Point3 QuadN[4];
typedef MgColorA QuadC[4];

class GeomQuad : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomQuad);

public:
  GeomQuad();
  virtual ~GeomQuad();

  //virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
  virtual int Save(class IoDataStream *s);
  virtual void Draw(class MgContext *mg);

  enum {
    QU_VCOL	= 0x1,	// Per-vertex colors valid
    QU_NORM	= 0x2,	// Per-vertex normals
    QU_FOURDIM	= 0x4,	// Four dimensional
  };

  //  int GetQuad(IoOldOoglLexer *lex, int dimn, int limit = -1);

//extern GeomClass *QuadMethods( void );
//extern char *QuadName( void );
//extern GeomQuad *QuadLoad( char * );
//extern GeomQuad *QuadFLoad( FILE *, char *fname );
//extern GeomQuad *QuadSave( GeomQuad *, char * );
//extern GeomQuad *QuadFSave( GeomQuad *, FILE *, char *fname );
//extern BBox *QuadBound( GeomQuad *, Transform );
//extern Geom *QuadSphere( GeomQuad *, Transform, int );
//extern GeomQuad *QuadEvert( GeomQuad * );
//extern GeomQuad *QuadDraw( GeomQuad * );
//extern GeomQuad *QuadTransform( GeomQuad *, Transform );
//extern GeomQuad *QuadTransformTo( GeomQuad *, Transform );

private:
  int  mFlags;
  int  mSeq;            /* for 4D -> 3D tforms */
  int  nMaxQuad;	// The number of quadrilaterals in the object.
  UtVVec mP;		// A variable length list of the vertices.
  UtVVec mN;		// A variable length list of the normals, if supplied.
  UtVVec mColors;		// A variable length list of the colors, if supplied.
};

#endif // QUAD_H
