#include "GeomOldOoglParser.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "UtScalarArray.h"
#include "Transform3.h"
#include "MgAppearance.h"
#include "IoDataStream.h"
#include "IoOldOoglLexer.h"
#include "IoOoglParseException.h"
#include "IoOldOoglParseException.h"
#include "GeomOff.h"
#include "GeomMesh.h"
#include "GeomQuad.h"
#include "GeomVect.h"
#include "GeomSkel.h"
#include "GeomList.h"
#include "GeomComment.h"
#include "GeomBezier.h"
#include "GeomWrapped.h"
#include "GeomHandle.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomOldOoglParser, Geom);

Geom *GeomOldOoglParser::load(const char *file)
{
    IoOldOoglLexer lex;

    if (!lex.Open(file))
        throw new IoOldOoglParseException(&lex,
            "Reading Geom.  Could not open file \"%s\".", file);

    try
    {
        Geom *geom = GeomOldOoglParser::Load(&lex);
        lex.Close();
        return geom;
    }

    catch (IoOoglParseException *pe)
    {
        lex.Close();
        throw pe;
    }
}

static
Geom *eofTooSoon(IoOldOoglLexer *lex)
{
    throw new IoOldOoglParseException(lex,
        "Reading Geom.  End-of-file unexpected.");
    return NULL;
}

Geom *GeomOldOoglParser::Load(IoOldOoglLexer *lex)
{
    char *keyword, *name;
    Geom *geom = NULL;
    int brace = 0;

    //  [ "define" <symbolname> ]
    //  [ ["="] <object-keyword> ...
    //   | "<"  <filename>
    //   | ":"  <symbolname> ]

    keyword = lex->GetNext();
    if (keyword == NULL)
        return eofTooSoon(lex);

    // This is an OK place for a open brace.
    if (strcmp(keyword, "{") == 0)              // Don't forget closing "}"
    {
        brace++;
        keyword = lex->GetNext();
        if (keyword == NULL)
            return eofTooSoon(lex);
    }

    // Skip the optional definition symbol.
    if (strcmp(keyword, "define") == 0)
    {
        name    = lex->GetNext();
        keyword = lex->GetNext();
        if (keyword == NULL)
            return eofTooSoon(lex);
    }

//fprintf(stderr, "keyword = %s.\n", keyword);
    // This is an OK place for a open brace.
    if (strcmp(keyword, "{") == 0)              // Don't forget closing "}"
    {
        brace++;
        keyword = lex->GetNext();
        if (keyword == NULL)
            return eofTooSoon(lex);
    }

//fprintf(stderr, "keyword = %s.\n", keyword);
    // The equal sign is ignored.
    if (strcmp(keyword, "=") == 0)
    {
        keyword = lex->GetNext();
//fprintf(stderr, "keyword = %s.\n", keyword);
        if (keyword == NULL)
            return eofTooSoon(lex);
    }

    // We don't yet know how to read in from a file.
    if (strcmp(keyword, "<") == 0)
    {
        name = lex->GetNext();
        if (name == NULL) return eofTooSoon(lex);
        geom = load(name);
        goto done;
    }

    // We don't yet use handles for geoms.
    else if (strcmp(keyword, ":") == 0)
    {
        name = lex->GetNext();
        if (name == NULL)
            return eofTooSoon(lex);
//fprintf(stderr, "name = %s.\n", name);
        geom = new GeomHandle();
    }

    else if ( strcmp(keyword, "appearance") == 0
           || KeywordMatch(keyword, "transform")
           || KeywordMatch(keyword, "INST") )
        geom = (Geom *) new GeomWrapped;

    else if (KeywordMatch(keyword, "MESH"))
        geom = (Geom *) new GeomMesh;
    else if (KeywordMatch(keyword, "OFF"))
        geom = (Geom *) new GeomOff;
    else if (KeywordMatch(keyword, "QUAD"))
        geom = (Geom *) new GeomQuad;
    else if (KeywordMatch(keyword, "VECT"))
        geom = (Geom *) new GeomVect;
    else if (KeywordMatch(keyword, "SKEL"))
        geom = (Geom *) new GeomSkel;
    else if (KeywordMatch(keyword, "LIST"))
        geom = (Geom *) new GeomList;
    else if (KeywordMatch(keyword, "COMMENT"))
        geom = (Geom *) new GeomComment;
    else if (KeywordMatch(keyword, "BEZ"))
        geom = (Geom *) new GeomBezier("BEZ");
    else if (KeywordMatch(keyword, "BBP"))
        geom = (Geom *) new GeomBezier("BBP");

    else
        throw new IoOldOoglParseException(lex,
            "Reading Geom.  Unknown Geom type %s.", keyword);

    // Load the geom ("Load" is a virtual function).
    try {
      geom->Load(lex, keyword);
    } catch (IoOoglParseException *pe) {
      delete geom; throw pe;
    }

done:
    // Close all opening "{".
    while (brace > 0 && lex->LookAhead("}"))
    {
        lex->GetNext();
        brace--;
    }
    if (brace > 0)
    {
        // Error.  Brackets not resolved.
        delete geom;
        throw new IoOldOoglParseException(lex,          // {
            "Reading Geom.  Missing %d closing brace%s '}'",
            brace, &"s"[brace==1]);
    }

    return geom;
}

#if KEYWORD_INSENSITIVE
static void strtoupper(char *s)
{
  while (*s != '\0') {
    *s = toupper(*s);
    ++s;
  }
}
#endif // KEYWORD_INSENSITIVE

int GeomOldOoglParser::KeywordMatch(const char *keyword, const char *string)
{
    return strstr(keyword, string) != NULL;
#if KEYWORD_INSENSITIVE
  char *k = new char[strlen(keyword)+1];
  strcpy(k, keyword);
  strtoupper(k);
  char *s = new char[strlen(string)+1];
  strcpy(s, string);
  strtoupper(s);
  int found = (strstr(k, s) != NULL);
  delete s;
  delete k;
  return found;
#endif // KEYWORD_INSENSITIVE
}

int GeomOldOoglParser::GetHeader(IoOldOoglLexer *lex,
                const char *keyword, const char *string,
                const char keys[], const short bits[])
{
    const char *k = string ? string : lex->GetNext();
    int i, flags = 0;
    for (i = 0; keys[i] != '\0'; i++)
    {
        if (*k == keys[i])
        {
            flags |= bits[i];
            k++;
        }
    }
    GetHeaderCommon(lex, keyword, k);
    return flags;
}

int GeomOldOoglParser::GetHeader(IoOldOoglLexer *lex,
                const char *keyword, const char *string,
                const char *keys[], const short bits[])
{
    const char *k = string ? string : lex->GetNext();
    int i, n, flags = 0;
    for (i = 0; keys[i] != NULL; i++)
    {
        n = strlen(keys[i]);
        if (strncmp(k, keys[i], n) == 0)
        {
            flags |= bits[i];
            k += n;
        }
    }
    GetHeaderCommon(lex, keyword, k);
    return flags;
}

void GeomOldOoglParser::GetHeaderCommon(IoOldOoglLexer *lex,
                const char *keyword, const char *k)
{
    if (strcmp(k, keyword) != 0)
        throw new IoOldOoglParseException(lex,
            "Reading %s.  Incorrect keyword %s.", keyword, k);

    if (lex->LookAhead("BINARY"))
    {
        lex->GetNext();
        lex->DataTypeBinary();
    }
}

char *GeomOldOoglParser::MakeHeader(
                const int flags, char *string,
                const char keys[], const short bits[])
{
    int i;
    char *k = string;

    for (i = 0; keys[i] != '\0'; i++)
        if (flags & bits[i])
            *k++ = keys[i];
    *k = '\0';

    return string;
}

char *GeomOldOoglParser::MakeHeader(
                const int flags, char *string,
                const char *keys[], const short bits[])
{
    int i, n;
    char *k = string;

    for (i = 0; keys[i] != NULL; i++)
        if (flags & bits[i])
        {
            n = strlen(keys[i]);
            strncpy(k, keys[i], n);
            k += n;
        }
    *k = '\0';

    return string;
}


// Load a bunch of transforms.
int GeomOldOoglParser::Load(IoOldOoglLexer *lex, UtScalarArray<Transform3> &a)
{
    // This should also allow for handles (:) and redirection (<).

//fprintf(stderr, "fload Transform:lex->LookAhead() = %s\n", lex->LookAhead());
    int brace = 0;
    if ( lex->LookAhead("transforms")
      || lex->LookAhead("transform") )
    {
        lex->GetNext();
    }

    if (lex->LookAhead("{"))    // }
    {
        lex->GetNext();
        brace = 1;
    }

    while (lex->LookAhead(IoOldOoglToken::NUMBER))
    {
        Transform3 *t = new Transform3;
        if (lex->ExpectFloat(16, (float *)t) < 16)
            throw new IoOldOoglParseException(lex,
                "Reading transforms.  Expected 4x4 array of numbers.");
        a[a.GetCount()] = *t;
//  jcm-purify 12/4/97
        delete t;
    }

    if (brace > 0)
    {                  // {
        if (!lex->Expect("}"))
            throw new IoOldOoglParseException(lex,                 // {
                "Reading transforms.  Expected closing brace '}'.");
    }

    return 1;
}


int GeomOldOoglParser::Load(IoOldOoglLexer *lex, Transform3 *t)
{
    // This should also allow for handles (:) and redirection (<).

    int brace = 0;
    if (lex->LookAhead("transform"))
        lex->GetNext();

    if (lex->LookAhead("{"))    // }
    {
        lex->GetNext();
        brace = 1;
    }

    if (lex->ExpectFloat(16, (float *)t) < 16)
        throw new IoOldOoglParseException(lex,
            "Reading transform.  Expected 4x4 array of numbers.");

    if (brace > 0)
    {                  // {
        if (!lex->Expect("}"))
            throw new IoOldOoglParseException(lex,         // {
                "Reading transform.  Expected closing brace '}'.");
    }

    return 1;
}

int GeomOldOoglParser::Save(IoDataStream *s, UtScalarArray<Transform3> &a)
{
    s->PrintF("transforms {\n");
    for (int i=0; i<a.GetCount(); i++)
        s->fputtransform(1, (float *)&a[i], IoDataStream::ASCII);
    s->PrintF("}\n");
    return !s->error();
}

int GeomOldOoglParser::Save(IoDataStream *s, Transform3 *t)
{
    s->PrintF("transform {\n");
    if (t) s->fputtransform(1, (float *)t, IoDataStream::ASCII);
    s->PrintF("}\n");
    return !s->error();
}


MgAppearance *GeomOldOoglParser::loadAppearance(const char *file)
{
    IoOldOoglLexer lex;

    if (!lex.Open((char *)file))
        throw new IoOldOoglParseException(&lex,
            "Reading Appearance.  Could not open file \"%s\".", file);

    try
    {
        MgAppearance *a = GeomOldOoglParser::fLoadAppearance(&lex);
        lex.Close();
        return a;
    }
    catch (IoOoglParseException *pe)
    {
        lex.Close();
        throw pe;
    }
}

MgAppearance *GeomOldOoglParser::fLoadAppearance(IoOldOoglLexer *lex)
{
    MgAppearance *a = new MgAppearance();
    try { a->Load(lex); }
    catch (IoOoglParseException *pe)
    {
        delete a;
        throw pe;
    }
    return a;
}

int GeomOldOoglParser::Load(IoOldOoglLexer *lex, MgAppearance *a)
{
    return a->Load(lex);
}

int GeomOldOoglParser::Save(IoDataStream *s, MgAppearance *a)
{
    return a->Save(s);
}

