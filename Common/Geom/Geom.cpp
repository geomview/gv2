#include <stdio.h>
#include "Geom.h"
#include "GeomParent.h"

TYPE_IMPLEMENT_TYPEINFO2(Geom, RefObject, StorageObject);


Geom::Geom()
{
    mpParent = NULL;
}

Geom::~Geom()
{
    if (mpParent) ::DeleteRef(mpParent);
}

void Geom::SetParent(GeomParent *parent)
{
    if (mpParent) ::DeleteRef(mpParent);
    mpParent = ::NewRef(parent);
}


int Geom::Save(char *file)
{
  IoDataStream *ds = new IoDataStream(file, "w");
  if (ds == NULL) { return 0; }
  int code = this->Save(ds);
  delete ds;
  return code;
}
