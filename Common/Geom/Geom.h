//-*-C++-*-
#ifndef GEOM_H
#define GEOM_H

#include "IoDataStream.h"
#include "IoOoglLexer.h"
#include "MgAppearance.h"
#include "MgContext.h"
#include "TypeObject.h"

// A geom is any object which is refrence counted, knows how to load
// and save itself, and can be drawn on an MgContext.  Notice: no
// appearance.  That is in GeomWrapped.

class Geom : virtual public RefObject,
             virtual public StorageObject
{
    TYPE_DECLARE_TYPEINFO(Geom);

public:
    Geom();
    virtual ~Geom();

    virtual void  Draw(MgContext *mg) = 0;
    virtual int   Load(class IoDataStream *s) { return 0; }
  //virtual int   Load(class IoOldOoglLexer *lex) { return Load(lex, NULL); }
  //virtual int   Load(class IoOldOoglLexer *lex, char *keyword) { return 0; }

    virtual int   Load(class IoOoglLexer *lex, char *keyword) { return 0; }

    virtual int   Save(class IoDataStream *s) { return 0; }

    virtual int   Save(char *file);

    class GeomParent *GetParent() { return mpParent; }
    void  SetParent(class GeomParent *parent);

protected:
    class GeomParent *mpParent;
};

#endif // GEOM_H
