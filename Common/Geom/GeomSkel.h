//-*-C++-*-
#ifndef SKEL_H
#define SKEL_H


// class GeomSkel
// 
// SKEL files represent collections of points and polylines, with shared
// vertices.  The syntax resembles that of OFF files, with a table of
// vertices followed by a sequence of polyline descriptions, each referring
// to vertices by index in the table.  Each polyline has an optional color.
//
// OOGL ASCII format:
//	[c][4][n]SKEL [ndim]
//	NVerts NPolys
//	Vertex(0) ... Vertex(NVerts-1)
//	N(0) iVert(0,1) iVert(0,2) ... iVert(0,N(0))	[color]
//	N(1) iVert(1,1) iVert(1,2) ... iVert(1,N(1))	[color]
//	...
//	N(NPolys) iVert(NPolys,1) iVert(NPolys,2) ... iVert(NPolys,N(1)) [color]
//	
// NVerts and NPolys are the number of vertices and polylines, respectively.
// For nSKEL objects, each vertex has NDim components.  For 4nSKEL objects,
// each vertex has NDim+1 components; the final component is the homogeneous
// divisor. 
//
// Color is present if the 'c' option is specified in the header.  First
// The number of color components is read, then the components.  A color
// may have 4 or fewer components:
//	0 components:	the default color
//	1 integer:	index into the colormap
//	3 or 4 floating point numbers:
//			RGB and possibly alpha values in the range 0..255
//	3 or 4 floating point numbers:
//			RGB and possibly alpha values in the range 0..1
//
// BINARY format is not yet supported.

#include "Geom.h"
#include "UtVVec.h"

// One of these for each polyline.
typedef struct Skline {
    int nv;			// Number of vertices for this polyline
    int v0;			// offset into vi[] of all vertices on line
    int nc;			// Number of colors for this polyline
    int c0;			// index into c[] of first color
} Skline;

class GeomSkel : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomSkel);

public:
    GeomSkel();
    virtual ~GeomSkel();

  //virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

    enum {
      SK_PCOL		= 0x1,	// Homogeneous Coords
      SK_HOMOGEN	= 0x2,	// Homogeneous Coords
      SK_NDIM		= 0x4,	// N-dimensional
    };

private:
    int mFlags;
    int mNVerts, mNLines;	// Number of vertices and polylines.
    int mDim;		    	// Dimension of points
    float *mP;		    	// Array[nvert][dim] of point coords
    Skline *mLines;	        // GeomList[nlines] of polylines
    int mNVI;	            // Total number of vertex indices
    UtVVec mVI;	            // All vertex index lists
    int mNColors;                // Total number of colors
    UtVVec mColors;         // Array of colors
};


#endif // SKEL_H
