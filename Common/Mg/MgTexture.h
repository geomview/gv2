//-*-C++-*-
#ifndef MGTEXTURE_H
#define MGTEXTURE_H


// class MgTexture
// 

#include "MgProperty.h"
#include "MgColor.h"
#include "Transform3.h"

class MgTexture : public MgProperty
{
public:
    MgTexture();
	virtual ~MgTexture();

    enum
    {
	F_DOCLAMP		= 0x1,
	F_FILE			= 0x2,
	F_ALPHAFILE		= 0x4,
	F_APPLY			= 0x8,
	F_HANDLE_TRANSFORM	= 0x10,
	F_XSIZE			= 0x20,
	F_YSIZE			= 0x40,
	F_CHANNELS		= 0x80,
	F_BACKGROUND		= 0x100,
	F_COORDS		= 0x200,

	TXF_LOADED		= 0x400,   // Has this texture been loaded?
					   // (tried to read those files yet?)
	TXF_RGBA		= 0x800,   // In loaded data, is R first byte?
					   // (else ABGR) */
	TXF_USED		= 0x1000,  // Recently rendered a geom
					   // containing this texture
    };
    enum
    {
	TXF_SCLAMP	= 0x1,   /* Clamp if s outside 0..1 (else wrap) */
	TXF_TCLAMP	= 0x2,   /* Clamp if t outside 0..1 (else wrap) */
    };
    enum
    {
	TXF_MODULATE	= 0,
	TXF_BLEND	= 1,
	TXF_DECAL	= 2,
    };
    enum
    {
	TXF_COORD_GIVEN  = 0,   /* given as part of object (default) */
	TXF_COORD_LOCAL  = 1,   /* In coord system of texture map */
	TXF_COORD_CAMERA = 2,   /* In camera coords */
	TXF_COORD_NORMAL = 3,   /* Taken from surface-normal, for env map */
    };

  //    virtual int LoadProcess(class IoOldOoglLexer *lex, int id, void *args);
    virtual int SaveProcess(class IoDataStream *s, int mask);

    virtual const char *GetKeyword();
    virtual const KeywordTable *GetKeywordTable();
    virtual int GetNumKeywords();
    virtual const char *GetIndent();

private:
    char *_filename;             // ppm or pgm (.Z) file
    char *_alphafilename;        // If present, this is a .pgm (.Z) file
    char *mData;                 // Raw data, top to bottom, read from file
    int _xsize, _ysize, _channels;
    unsigned int _apply;	 // Application style (decal, modulate, blend)
    unsigned int _coords;        // Texture-coord auto generation
    MgColorA _background;        // background color: outside of clamped texture
    //Handle *_tfmhandle;
    Transform3 _tfm;             // texture-coord transformation
    //TxUser *_users;            // Users of this texture register here
    MgTexture *mpNext;            // Link in list of all loaded textures
};


#endif // MGTEXTURE_H
