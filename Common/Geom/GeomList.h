//-*-C++-*-
#ifndef __LIST_H__
#define __LIST_H__

#include "GeomParent.h"
#include "UtVRefPtrArray.h"
#include "IoOoglLexer.h"


class GeomList : public GeomParent
{
    TYPE_DECLARE_TYPEINFO(GeomList);

public:
    GeomList() { }
    GeomList(int number, Geom *geoms);
    GeomList(UtVRefPtrArray<Geom *> geoms) : mGeomList(geoms) { }
    GeomList(const GeomList &list) : mGeomList(list.mGeomList) { }
    virtual ~GeomList() {
        // note that the UtVRefPtrArray destructor handles freeing
        // its contents, so we don't have to do that here
    }

    virtual void Draw(class MgContext *mg);
  //virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
    virtual int Load(class IoOoglLexer *lex, char *keyword = NULL);
    virtual int Save(class IoDataStream *s);

    // GeomParent functions:
    virtual int   GetChildCount();
    virtual Geom *GetChild(int index = 0);
    virtual void  AddChild(Geom *geom);
    virtual void  RemoveChild(Geom *geom);
    virtual int   GetChildIndex(Geom *geom);
    virtual void  RemoveChild(int index = 0);

private:
    UtVRefPtrArray<Geom *> mGeomList;
    void Clear();
};

#endif //__LIST_H__
