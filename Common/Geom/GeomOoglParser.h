//-*-C++-*-
#ifndef GEOMOOGLPARSER_H
#define GEOMOOGLPARSER_H

#include "Geom.h"
#include "TypeObject.h"
#include "IoOoglLexer.h"

class GeomOoglParser : virtual public TypeObject
{
    TYPE_DECLARE_TYPEINFO(GeomOoglParser);

public:
  static class Geom *Load(class IoOoglLexer *lex);

  static class Geom *Load(char *file) {
    IoOoglLexer lex(file);
    return Load(&lex);
  }

};


#endif // GEOMOOGLPARSER_H
