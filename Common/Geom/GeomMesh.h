//-*-C++-*-
#ifndef MESH_H
#define MESH_H


// class GeomMesh
// 
// The GeomMesh object is a rectangularly-connected mesh of squares.
// 
// OOGL ASCII format:
//	[U][C][N][Z][4][u][v][n]MESH [ndim]
//	Nu Nv
//	Vertex(0,0) ... Vertex(Nu-1,Nv-1)
//
// The optional prefix characters mean: 
//
// `U' Each vertex includes a 3-component texture space parameter.  The first
//     two components are the usual S and T texture parameters for that vertex;
//     the third should be specified as zero. 
// `C' Each vertex includes a 4-component color. 
// `N' Each vertex includes a surface normal vector. 
// `Z' Of the 3 vertex position values, only the Z component is present;
//     X and Y are omitted, and assumed to equal the mesh (u,v) coordinate so X
//     ranges from 0 .. (Nu-1), Y from 0 .. (Nv-1) where Nu and Nv are the mesh
//     dimensions.
// `4' Vertices are 4D, each consists of 4 floating values. `Z' and `4' cannot
//     both be present. 
// `u' The mesh is wrapped in the u-direction, so the (0,v)'th vertex is
//     connected to the (Nu-1,v)'th for all v. 
// `v' The mesh is wrapped in the v-direction, so the (u,0)'th vertex is
//     connected to the (u,Nv-1)'th for all u. Thus a u-wrapped or v-wrapped
//     mesh is topologically a cylinder, while a uv-wrapped mesh is a torus. 
// `n' Specifies a mesh whose vertices live in a higher dimensional space.
//     The dimension follows the "MESH" keyword. Each vertex then has Ndim
//     components. 
//
// BINARY format is not yet supported.

#include "Geom.h"

class GeomMesh : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomMesh);

public:
    GeomMesh();
    virtual ~GeomMesh();

  //virtual int Load(class IoOldOoglLexer *lex, char *keyword);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

    enum
    {
	MESH_UWRAP	= 0x1,
	MESH_VWRAP	= 0x2,
	MESH_C		= 0x4,
	MESH_N		= 0x8,
	MESH_U		= 0x10,
	MESH_D		= 0x20,
	MESH_EVERT	= 0x40,
	MESH_Z		= 0x100,
	MESH_4D		= 0x200,
    };

    inline int NUVerts() { return mNu; }
    inline int NVVerts() { return mNv; }
    inline int NUQuads() { return ((mFlags & MESH_UWRAP) ? mNu : mNu - 1); }
    inline int NVQuads() { return ((mFlags & MESH_VWRAP) ? mNv : mNv - 1); }

    // Returns the index of a point into the mesh array given its u,v coords.
    inline int index(int u, int v) { return (v%mNv)*mNu + (u%mNu); }

private:
    void ComputeNormals();

// The dimensions of the mesh are stored in integers mNu and mNv.
// The coordinates of the vertices are stored in an array of homogeneous points
private:
    int			mFlags;
    int			mNu, mNv;	// Dimensions of the mesh.
    class HPoint3	*mP;		// Array[mNu x mNv] of vertices.
    class Point3 	*mN;		// Array[mNu x mNv] of normals.
    class Point3 	*mU;		// Array[mNu x mNv] of texture coords.
    class MgColorA	*mColors;	// Array[mNu x mNv] of vertex colors.
};


#endif // MESH_H
