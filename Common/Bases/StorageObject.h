#ifndef __STORAGEOBJECT_H__
#define __STORAGEOBJECT_H__

// class StorageObject
//
// Interface to be used by classes that know how to load & save
// themselves, e.g. Geoms, Cameras, Appearances, etc.

#include "RefObject.h"
#include "IoDataStream.h"
#include "IoOoglLexer.h"
#include "TypeObject.h"

class StorageObject : virtual public TypeObject
{
    TYPE_DECLARE_TYPEINFO(StorageObject);

public:

    virtual ~StorageObject() {}
    virtual int Save(IoDataStream *s) = 0;
    virtual int Save(IoDataStream &s) { return(Save(&s)); }
    virtual int Save(char *fName);

    virtual int Load(IoDataStream *s) = 0;
    virtual int Load(IoDataStream &s) { return(Load(&s)); }
    virtual int Load(IoOoglLexer *lex, char *keyword) { return(0); }
    virtual int Load(IoOoglLexer &lex, char *keyword)
    {
	return(Load(lex, keyword));
    }
    virtual int Load(char *fName);
};

#endif //__STORAGEOBJECT_H__
