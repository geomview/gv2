#include <stdio.h>
#include "Geom.h"
#include "IoOoglLexer.h"
#include "GeomOoglParser.h"
#include "UtException.h"
#include "IoOoglParseException.h"
#include "GvMotion.h"
#include "Transform3.h"

int main(int argc, char *argv[])
{
  Transform3 T;
  Geom *g = NULL;

  T.Identity();

#if 0
  GvMotion m(GvMotion::ONESHOT, g, T);


  if (argc <= 1) {
    fprintf(stderr, "usage: loadtest FILE\n");
    exit(1);
  }

  char *file = argv[1];

  Geom *g;
  IoOoglLexer *lex = new IoOoglLexer(file);

  if (lex == NULL) {
    fprintf(stderr, "can't create lexer on file %s\n", file);
    exit(1);
  }

  try {
    g = GeomOoglParser::Load(lex);
  }
  catch (IoOoglParseException *e) {
      fprintf(stderr, "IoOoglParseException caught: %s\n", e->Message());
      fprintf(stderr, "%s\n", e->Context());
      delete e;
      exit(1);
  }

  catch (UtException *e) {
      static char errmsg[256];
      sprintf(errmsg, "UtException caught: %s", e->Message());
      fprintf(stderr, "%s\n", errmsg);
      delete e;
      exit(1);
  }


  fprintf(stderr, "Got a geom of type %s\n", g->GetType()->mpName);

  IoDataStream out(stdout);
  g->Save(&out);
#endif
}
