//-*-C++-*-
#ifndef BEZ_H
#define BEZ_H


// class GeomBezier
//
// The GeomBezier object is ...
//
// OOGL ASCII format:
//

#include "Geom.h"
//#include "MgColor.h"
#include "UtUArray.h"

#define MAX_BEZ_DEGREE  12
#define MAX_BEZ_DIMN    4
#define BEZ_DEFAULT_MESH_SIZE   10

class GeomBezier : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomBezier);

public:
    GeomBezier(const char *key = "BEZ");
    virtual ~GeomBezier();

    //virtual int fLoadBEZ(class IoOldOoglLexer *lex, char *keyword);
    //virtual int fLoadBBP(class IoOldOoglLexer *lex, char *keyword);
    //virtual int Load(class IoOldOoglLexer *lex, char *keyword, int iflags);
  //virtual int Load(class IoOldOoglLexer *lex, char *keyword);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

    enum
    {
	    BEZ_P           = 0x0,
	    BEZ_ST          = 0x1,
	    BEZ_C           = 0x2,
	    BEZ_PST         = (BEZ_P | BEZ_ST),
	    BEZ_BINARY      = 0x4,
	    BEZ_REMESH      = 0x8,             /* need to recompute mesh */
	    BEZ_4D          = 0x10,
    };

private:
    void Clear();

// The dimensions of the mesh are stored in integers mNu and mNv.
// These must match mesh dimensions or remake mesh.
//  mCtrlPnts and mStCords are arrays of float pointers
//  mColors is an array of MgColorA pointers
//  mMesh is an array of GeomMesh pointers

private:
    int		mFlags, mHasUVN;
    int		mDegreeU, mDegreeV, mDimN;
    int		mNu, mNv;
    int		mNPatch;	// Number of bezier patches.
    UtUArray	mCtrlPnts;	// Control points of each patch.
    UtUArray	mStCords;	// Texture map coordinates of each patch.
    UtUArray	mColors;		// Colors (4) of each patch.
    UtUArray	mMesh;		// GeomMesh of each patch.
};


#endif // BEZ_H
