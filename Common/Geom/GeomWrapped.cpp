#include "GeomWrapped.h"

#include <string.h>

#include "Transform3.h"
#include "MgAppearance.h"
#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "GeomOldOoglParser.h"
#include "GeomOoglParser.h"
#include "UtString.h"
#include "IoOoglParseException.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomWrapped, GeomParent);

// Assume for now that there will be no more than 1 appearance and 1 transform.
// The arrays will be expanded later if more are given.
GeomWrapped::GeomWrapped()
{
  Init();
}

void GeomWrapped::Init()
{
  mFlags       = 0;
  mpGeom       = NULL;
  mpAppearance = NULL;
  mTransform.Identity();
}


GeomWrapped::~GeomWrapped()
{
    Clear();
}

void GeomWrapped::Clear()
{
    // Get rid of the geom.
    if (mpGeom) {
        ::DeleteRef(mpGeom);
    }

    // Get rid of the appearance
    if (mpAppearance) {
        ::DeleteRef(mpAppearance);
    }

    // Re-initialize
    Init();
}

void GeomWrapped::SetTransform(const Transform3 &T)
{
    mTransform = T;
}

Transform3 *GeomWrapped::GetTransform()
{
    return &mTransform;
}


void GeomWrapped::SetAppearance(MgAppearance *ap)
{
    if (mpAppearance) ::DeleteRef(mpAppearance);
    mpAppearance = ::NewRef(ap);
}

MgAppearance *GeomWrapped::GetAppearance()
{
    return mpAppearance;
}

static const char  wrap_keys[] = "4";
static const short wrap_bits[] = {
    GeomWrapped::WR_FOURDIM,
};

int GeomWrapped::Save(IoDataStream *s)
{
  s->PrintF("INST\n");

    // Print the appearance and the transform.
    if (mpAppearance) mpAppearance->Save(s);
    //    GeomOldOoglParser::Save(s, &mTransform);

    // Print the geom inside of braces {}.
    if (mpGeom) {
        s->PrintF("geom { ");
        mpGeom->Save(s);
        s->PrintF("}\n");
    }

    return !s->error();
}


int GeomWrapped::Load(IoOoglLexer *lex, char *keyword)
{
  Clear();

  int got_geom      = 0;
  int got_transform = 0;
  int got_location  = 0;
  int got_origin    = 0;

  do {
    lex->Scan();
    if (lex->GetType() != IoOoglLexer::EOI) {

      if (lex->GetType() == IoOoglLexer::RBRACE) {
	// If we encounter a right brace, we assume it goes with a
	// left brace that's outside the current scope, so we put it
	// back and return immediately.
	lex->UnScan();
	return 1;
      }

      if (lex->GetType() != IoOoglLexer::STRING) {
	throw new IoOoglParseException(lex,
		"expected string while parsing INST (got %s)",
				       lex->ToString());
      }
      char field[128];
      strcpy(field, lex->GetStringValue());
      if ( UtString::CaseInsensitiveStreq(field, "geom") ||
	   UtString::CaseInsensitiveStreq(field, "unit")    ) {
	if (got_geom) {
	  throw new IoOoglParseException(lex,
					 "can have only 1 geom per INST");
	}
	mpGeom = GeomOoglParser::Load(lex);
	if (!mpGeom) {
	  throw new IoOoglParseException(lex,
			  "error reading geom embedded in INST");
	}
	got_geom = 1;
      } else if ( UtString::CaseInsensitiveStreq(field, "transform") ) {
	if (got_transform) {
	  throw new IoOoglParseException(lex,
  	    "can have only 1 transform/transforms section per INST");
	}
	mTransform.Load(lex);
	got_transform = 1;
      } else if ( UtString::CaseInsensitiveStreq(field, "location") ) {
	if (got_location) {
	  throw new IoOoglParseException(lex,
  	    "can have only 1 'location' per INST");
	}
	got_location = 1;
      } else if ( UtString::CaseInsensitiveStreq(field, "origin") ) {
	if (got_origin) {
	  throw new IoOoglParseException(lex,
  	    "can have only 1 'origin' per INST");
	}
	got_origin = 1;
      }
    }
  } while (lex->GetType() != IoOoglLexer::EOI);
  return 1;
}



#if 0
IF0  int GeomWrapped::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      char *w;
IF0      int inst = 0;
IF0  
IF0      // Clear any old data.
IF0      Clear();
IF0      mFlags = 0;
IF0      mpGeom = NULL;
IF0  
IF0      // If the first token was already read, put it back in the stream.
IF0      if (keyword != NULL)
IF0          lex->UngetCurrent();
IF0  
IF0      // Peek ahead to the next token.
IF0      while ( (w=lex->LookAhead()) != NULL)
IF0      {
IF0          // If the next token is the keyword (old-style), look for any
IF0          // flags before the keyword.  Only one keyword per object is allowed.
IF0          if (!inst && GeomOldOoglParser::KeywordMatch(w, "INST"))
IF0          {
IF0              mFlags = GeomOldOoglParser::GetHeader(lex,
IF0                  "INST", w, wrap_keys, wrap_bits);
IF0              lex->GetNext();
IF0              inst = 1;
IF0          }
IF0  
IF0          // Check for appearance.
IF0          else if (lex->LookAhead("appearance"))
IF0          {
IF0              if (mpAppearance) ::DeleteRef(mpAppearance);
IF0              mpAppearance = GeomOldOoglParser::fLoadAppearance(lex);
IF0          }
IF0  
IF0          // Then for transform (either with or without an 's').
IF0          #define LEN 9
IF0          else if ( strncmp("transform", w, LEN) == 0
IF0                  && (w[LEN] == '\0' || (w[LEN] == 's' && w[LEN+1] == '\0')) )
IF0          {
IF0              GeomOldOoglParser::Load(lex, &mTransform);
IF0          }
IF0  
IF0          // If nothing else, it must be the geometry.
IF0          else
IF0          {
IF0              // These keywords are optional (were part of old INST format).
IF0              if ( strcmp(w, "geom") == 0
IF0                || strcmp(w, "unit") == 0 )
IF0                  lex->GetNext();
IF0  
IF0              mpGeom = GeomOldOoglParser::Load(lex);
IF0  
IF0              // There can be no more appearance or transform after the geom.
IF0              break;
IF0          }
IF0      }
IF0  
IF0      return 1;
IF0  }
#endif

void GeomWrapped::Draw(class MgContext *mg)
{
    mg->PushTransform();
    mg->Transform( &mTransform );
    if (mpAppearance)
    {
        mg->PushAppearance();
        mg->MergeAppearance( mpAppearance );
    }

    mpGeom->Draw(mg);

    if (mpAppearance) mg->PopAppearance();
    mg->PopTransform();
}

void GeomWrapped::RightMultiply(Transform3 &T)
{
    mTransform.Concat(&mTransform, &T);
}

void GeomWrapped::LeftMultiply(Transform3 &T)
{
    mTransform.Concat(&T, &mTransform);
}

int   GeomWrapped::GetChildCount()
{
    return ( (mpGeom == NULL) ? 0 : 1);
}

Geom *GeomWrapped::GetChild(int index)
{
    if (index != 0)
    {
        throw new UtException(UtException::WARNING,
      "Attempt to get other than 0-th child of a GeomWrapped (index=%1d)",
                              index);
    }
    return mpGeom;
}

void  GeomWrapped::AddChild(Geom *geom)
{
    if (mpGeom)
    {
        throw new UtException(UtException::WARNING,
             "Attempt to add more than 1 child to a GeomWrapped");
    }
    mpGeom = ::NewRef(geom);
}

void  GeomWrapped::RemoveChild(Geom *geom)
{
    if (mpGeom == geom)
    {
        ::DeleteRef(mpGeom);
        mpGeom = NULL;
    }
}

int   GeomWrapped::GetChildIndex(Geom *geom)
{
    if (geom == mpGeom) return 0;
    return -1;
}

void  GeomWrapped::RemoveChild(int index)
{
    if (index != 0)
    {
        throw new UtException(UtException::WARNING,
       "Attempt to remove other than 0-th child of a GeomWrapped (index=%1d)",
                              index);

    }
    if (mpGeom)
    {
        ::DeleteRef(mpGeom);
        mpGeom = NULL;
    }
}
