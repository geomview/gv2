//-*-C++-*-
#ifndef COMMENT_H
#define COMMENT_H


// class GeomComment
// 
// The COMMENT object is a mechanism for encoding arbitrary data within an
// OOGL object. It can be used to keep track of data or pass data back and
// forth between external modules. 
//
// OOGL ASCII format:
//	COMMENT <name> <type> { <arbitrary data> }
//
// BINARY format is not yet supported.
//
// The data, which must be enclosed by curly braces, can include anything
// except unbalanced curly braces.  The type field can be used to identify
// data of interest to a particular program through naming conventions. 


#include "Geom.h"

class GeomComment : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomComment);
public:
    GeomComment();
    virtual ~GeomComment();

  //virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

private:

// Why were these "const char *"'s before?  Some problems here with VC++;
    char *mName;
    char *mType;
    char *mData;
};


#endif // COMMENT_H
