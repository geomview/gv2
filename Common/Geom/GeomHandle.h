//-*-C++-*-
#ifndef GEOMHANDLE_H
#define GEOMHANDLE_H


// class GeomHandle
// 
// This geometric object is simply a handle to another geometric object.
// It is not fully implemented; it contains only the handle name.
// It may not even make sense to implement handles this way.  We'll see.
//
// OOGL ASCII format:
//	: <handle_name>

#include "Geom.h"

class GeomHandle : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomHandle);

public:
    GeomHandle();
    virtual ~GeomHandle();

  //virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

private:
    char *mName;
};


#endif // GEOMHANDLE_H
