//#include "GeomOldOoglParser.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "GeomOoglParser.h"
#include "GeomOff.h"
#include "GeomWrapped.h"
#include "GeomList.h"
#include "UtString.h"
#include "IoOoglParseException.h"

TYPE_IMPLEMENT_TYPEINFO(GeomOoglParser)

class Geom *
GeomOoglParser::Load(class IoOoglLexer *lex)
{
  char keyword[128];
  Geom *geom = NULL;
  int brace = 0;

  // Get the first token
  lex->Scan();

  // If it's a LBRACE, remember this fact and move on to the
  // next token
  if (lex->GetType() == IoOoglLexer::LBRACE) {
    brace = 1;
    lex->Scan();
  }

  // This one better be a string
  if (lex->GetType() != IoOoglLexer::STRING) {
    throw new IoOoglParseException(lex,
     "Reading Geom.  First token read [%s] does not appear to be a keyword",
				   lex->GetStringValue());
  }
  strcpy(keyword, lex->GetStringValue());

  //
  // This'll need to be expanded soon to allow for NOFF, COFF, 4NCOFF, etc...
  //
  if (UtString::CaseInsensitiveStreq(keyword, "OFF")) {
    geom = (Geom *) new GeomOff;
  } else if (UtString::CaseInsensitiveStreq(keyword, "transform")) {
    // If we encounter a "transform" at this level, assume we're
    // reading an INST that's just missing the "INST" keyword
    lex->UnScan();
    geom = (Geom *) new GeomWrapped;
  } else if (UtString::CaseInsensitiveStreq(keyword, "INST")) {
    geom = (Geom *) new GeomWrapped;
  } else if (UtString::CaseInsensitiveStreq(keyword, "LIST")) {
    geom = (Geom *) new GeomList;
  } else {
    throw new IoOoglParseException(lex,
      "Reading Geom.  Unknown Geom type %s.", keyword);
  }

  // Load the geom ("Load" is a virtual function).
  try {
    geom->Load(lex, keyword);
  } catch (IoOoglParseException *pe) {
    delete geom;
    throw pe;
  }

  // If we got an LBRACE at the beginning of this GEOM, make
  // sure we get a closing one to match it now.
  if (brace) {
    if (lex->LookAhead() != IoOoglLexer::RBRACE) {
      throw new IoOoglParseException(lex, "missing '}'");
    }
    lex->Scan();
  }
  
  return geom;
}
