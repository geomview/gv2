//-*-C++-*-
#ifndef OOGLPARSER_H
#define OOGLPARSER_H

#include "TypeObject.h"
#include "UtScalarArray.h"

// class GeomOldOoglParser
// 
// This class contains routines to help parse OOGL files.
// load(file) and Load(lex) will read a geom.  The actual parsing
// of the Geom (OFF, MESH, etc.) is done in the class itself in the
// Load(lex) function, which returns T/F.  Load and Save may call
// GetHeader and MakeHeader to help read and write headers.
// Since Transforms do not have Load or Save routines, they are
// provided here.
//
// Perhaps MakeHeader and Save should be part of an OoglWriter class.

#include "Transform3.h"

class GeomOldOoglParser : virtual public TypeObject
{
    TYPE_DECLARE_TYPEINFO(GeomOldOoglParser);

public:
    static class Geom *load(const char *file);
  //static class Geom *Load(class IoOldOoglLexer *lex);

    static int KeywordMatch(const char *keyword, const char *string);

    // Read a header from 'string' looking for characters in 'keys'
    // before the keyword 'keyword'.  Characters must appear only in
    // the order they are in 'keys'.  Once a character is found,
    // the corresponding flag from 'bits' is set in an integer, which
    // is returned after all flags have been read and set.
    //
    // If the remaining keyword after character flags have been read
    // does not match 'keyword,' then a -1 is returned instead.
    // (see GeomOff.cpp and GeomMesh.cpp for examples of using these
    // functions.)
    //
    // If the word "BINARY" appears as the next token on input, then
    // the datatype of 'lex' is set to binary.

#if 0
IF0      static int GetHeader(class IoOldOoglLexer *lex,
IF0                  const char *keyword, const char *string,
IF0                  const char keys[], const short bits[]);
IF0      static int GetHeader(class IoOldOoglLexer *lex,
IF0                  const char *keyword, const char *string,
IF0                  const char *keys[], const short bits[]);
#endif

    // These functions do the reverse of GetHeader.  They find the bits
    // that are set in 'flags' and add their corresponding characters to
    // a string.  'string' must be long enough to hold all option characters.
    // The 'string' is always returned.
    static char *MakeHeader(
                const int flags, char *string,
                const char keys[], const short bits[]);
    static char *MakeHeader(
                const int flags, char *string,
                const char *keys[], const short bits[]);

  // Read and write transforms.
  //static int Load(class IoOldOoglLexer *lex, class Transform3 *t);
  // static int Load(class IoOldOoglLexer *lex, class UtUArray &a);
  //static int Load(class IoOldOoglLexer *lex, UtScalarArray<Transform3> &a);
    static int Save(class IoDataStream *s, class Transform3 *t);
    // static int Save(class IoDataStream *s, class UtUArray &a);
    static int Save(class IoDataStream *s, UtScalarArray<Transform3> &a);

    // Read and write appearances.
    static class MgAppearance *loadAppearance(const char *file);
  //static class MgAppearance *fLoadAppearance(class IoOldOoglLexer *lex);
  //static int Load(class IoOldOoglLexer *lex, class MgAppearance *a);
    static int Save(class IoDataStream *s, class MgAppearance *a);

#if OLDSTYLE_PARSE_ERROR
    // Report all parsing errors through this function.
    // ParseError always returns a 0.
    static int ParseError(class IoOldOoglLexer *lex, const char *format, ...);
#endif // OLDSTYLE_PARSE_ERROR

private:
  //    static void GetHeaderCommon(class IoOldOoglLexer *lex,
  //                const char *keyword, const char *string);
};


#endif // OOGLPARSER_H
