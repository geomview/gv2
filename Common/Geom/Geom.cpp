#include <stdio.h>
#include "Geom.h"
#include "GeomParent.h"

TYPE_IMPLEMENT_TYPEINFO2(Geom, RefObject, StorageObject);


Geom::Geom()
{
    mpParent = NULL;
    mpName   = NULL;
}

Geom::~Geom()
{
    if (mpParent) ::DeleteRef(mpParent);
    if (mpName) delete(mpName);
}

void Geom::SetParent(GeomParent *parent)
{
    if (mpParent) ::DeleteRef(mpParent);
    mpParent = ::NewRef(parent);
}


int Geom::Save(char *file)
{
  return Save(NULL, file);
}

int Geom::Save(char *indent, char *file)
{
  IoDataStream *ds = new IoDataStream(file, "w");
  if (ds == NULL) { return 0; }
  int code = this->Save(indent, ds);
  delete ds;
  return code;
}

void Geom::SetName(char *name)
{
  if (name) {
    mpName = new char[strlen(name)+1];
    strcpy(mpName, name);
  }
}
