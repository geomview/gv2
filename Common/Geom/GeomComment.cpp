#include "GeomComment.h"

#include "UtVVec.h"
#include "UtString.h"

#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomComment, Geom);

GeomComment::GeomComment()
{
    mName = NULL;
    mType = NULL;
    mData = NULL;
}

GeomComment::~GeomComment()
{
    if (mName) delete mName;
    if (mType) delete mType;
    if (mData) delete mData;
}

#if 0
IF0  // Expects an opening brace, then reads tokens until the corresponding
IF0  // closing brace.
IF0  char *balanced(IoOldOoglLexer *lex)
IF0  {
IF0      char *w;
IF0      UtVVec buf(sizeof(char));
IF0      int index, depth;
IF0  
IF0      // Expect braces of at least one level.
IF0      depth = 1;
IF0      if (!lex->Expect("{"))	// }
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading COMMENT.  Expected opening brace {.");	// }
IF0  
IF0      // Read tokens possibly until end-of-file.
IF0      index = 0;
IF0      while ( (w=lex->GetNext()) != NULL)
IF0      {
IF0  	// Keep track of the depth of braces, stopping of we've reached
IF0  	// the match to the original.
IF0  	if (*w == '{') { ++depth; }
IF0  	else if (*w == '}') { if (--depth <= 0) break; }
IF0  
IF0  	// Copy the token string into the variable length array of characters.
IF0  	int n = strlen(w);
IF0  	buf.Get(index+n+1);	// Make room for the string plus a space.
IF0  	strncpy((char *)buf.Get(index), w, n);
IF0  	*(char *)buf.Get(index+n) = ' ';
IF0  
IF0  	// Prepare for the next token.
IF0  	index += n+1;
IF0      }
IF0  
IF0      // Make sure end-of-file was not reached too soon.
IF0      if (depth > 0)
IF0  	throw new IoOldOoglParseException(lex,		     //  {
IF0  	    "Reading COMMENT.  Missing %d closing brace%s '}'",
IF0  	    depth, &"s"[depth==1]);
IF0  
IF0      // Close the string and return it.
IF0      *(char *)buf.Get(index) = '\0';
IF0      return (char *)buf.StealBuf();
IF0  }
#endif

// Write the GeomComment in OOGL format.
int GeomComment::Save(IoDataStream *s)
{
    s->PrintF("COMMENT %s %s { \"%s\" }\n", mName, mType, mData);
    return !s->error();
}


#if 0
IF0  // Read a GeomComment in OOGL format.
IF0  int GeomComment::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      char *str;
IF0  
IF0      if (mName) delete mName;
IF0      if (mType) delete mType;
IF0      if (mData) delete mData;
IF0      mName = NULL;
IF0      mType = NULL;
IF0      mData = NULL;
IF0  
IF0      // Get the keyword if it was not read already.
IF0      if (keyword == NULL && (keyword=lex->GetNext()) == NULL)
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading COMMENT.  End-of-file unexpected.");
IF0  
IF0      // There should be no other letters (flags) in the keyword.
IF0      if (strcmp("COMMENT", keyword) != 0)
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading COMMENT.  Incorrect Header (should be \"COMMENT\").");
IF0  
IF0      // Read the comment name.
IF0      if ( (str=lex->GetNext()) == NULL
IF0        || lex->GetCurrentType() != IoOldOoglToken::STRING )
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading COMMENT.  Expected comment name.");
IF0      UtString tmp(str);
IF0      mName = tmp.StealBuf();
IF0  
IF0      // Then the comment type.
IF0      if ( (str=lex->GetNext()) == NULL
IF0        || lex->GetCurrentType() != IoOldOoglToken::STRING )
IF0  	throw new IoOldOoglParseException(lex,
IF0  	    "Reading COMMENT.  Expected comment type.");
IF0      mType = strdup(str);
IF0  
IF0      // Then read the arbitrary data surrounded by balanced braces {}.
IF0      if ( (mData = balanced(lex)) == NULL ) return 0;
IF0  
IF0      return 1;
IF0  }
#endif

void GeomComment::Draw(class MgContext *mg)
{
}

