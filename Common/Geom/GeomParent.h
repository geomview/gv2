//-*-C++-*-
#ifndef GEOMPARENT_H
#define GEOMPARENT_H

#include "Geom.h"

class GeomParent : public Geom
{
    TYPE_DECLARE_TYPEINFO(GeomParent);

public:
   virtual int   GetChildCount()            = 0;
   virtual Geom *GetChild(int index = 0)    = 0;
   virtual void  AddChild(Geom *geom)       = 0;
   virtual void  RemoveChild(Geom *geom)    = 0;
   virtual int   GetChildIndex(Geom *geom)  = 0;
   virtual void  RemoveChild(int index = 0) = 0;
};


#endif // GEOMPARENT_H
