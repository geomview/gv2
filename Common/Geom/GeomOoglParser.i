//-*-C++-*-
//
// GeomOoglParser.i: swig interface for GeomOoglParser
//

class GeomOoglParser
{
public:
  GeomOoglParser();
  ~GeomOoglParser();
  Geom *Load(char *file);
};
