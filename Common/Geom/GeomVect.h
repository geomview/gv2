//-*-C++-*-
#ifndef VECT_H
#define VECT_H


// class GeomVect
// 
// VECT objects represent lists of polylines (strings of connected line
// segments, possibly closed).  A degenerate polyline can be used to
// represent a point. 
//
// OOGL ASCII format:
//	[4]VECT
//	NPolylines NVertices NColors
//	Nv(0) ... Nv(NPolylines-1)
//	Nc(0) ... Nc(NPolylines-1)
//	Vert(0) ... Vert(NVertices-1)
//	Color(0) ... Color(NColors-1)
//
// BINARY format is supported, but hasn't been tested.
//
// NPolylines, NVertices, and NColors, represent the number of polylines,
// the total number of vertices, and the number of colors in the file,
// respectively.
//
// The integers, Nv(0) through Nv(NPolylines-1) give the number of vertices
// in each polyline.  A negative number indicates a closed polyline;
// 1 denotes a single-pixel point. The sum (of absolute values) of the Nv[i]
// must equal NVertices. 
//
// The integers, Nc(0) through Nc(NPolylines-1) give the number of new colors
// in each polyline.  Normally one of three values: 
//	0	No color is specified for this polyline.  It's drawn in 
//		the same color as the previous polyline. 
//	1	A single color is specified.  The entire polyline is drawn
//		in that color.
// The sum of the Nc[i] must equal NColors. 
//
// Vert(0) through Vert(NVertices-1) represent the coordinates of all the
// vertices.  The first abs|Nv(0)| of them form the first polyline, the next
// abs|Nv(1)| form the second and so on.  If the keyword is 4VECT then there
// are 4 values per vertex, otherwise 3.
//
// Finally, Color(0) through Color(NColors-1) represent the colors (if any).
// Each color has 4 components (Red, Green, Blue, Alpha (opacity)).
// The first Nc(0) of them apply to the first polyline.

#include "Geom.h"

class GeomVect : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomVect);

public:
    GeomVect();
    virtual ~GeomVect();

  //virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

    enum {
        VE_FOURDIM	= 0x1,	// Four dimensional
    };

private:
    int VectSane();

private:
    int     mFlags;
    int	  mNVec, mNVerts, mNColors;
    int     mSeq;           /* for 4D -> 3D tforms */
    short   *mNVert;       /* mNVert[nvec] (# mP[]'s per vec) */
    short   *mVNColors;      /* mVNColors[nvec] (# mColors[]'s per vec) */
    class HPoint3 *mP;      /* mP[nvert] */
    class MgColorA  *mColors;    /* mColors[ncolor] */
};


#endif // VECT_H
