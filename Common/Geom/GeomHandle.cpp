#include "GeomHandle.h"

#include "UtString.h"
#include "IoDataStream.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
//#include "GeomOldOoglParser.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomHandle, Geom);

GeomHandle::GeomHandle()
{
    mName = NULL;
}

GeomHandle::~GeomHandle()
{
    if (mName) delete mName;
}

// Write the handle in OOGL format.
int GeomHandle::Save(IoDataStream *s)
{
    if (mName) s->PrintF(": %s ",  mName);
    return !s->error();
}

#if 0
IF0  // Read a handle in OOGL format.
IF0  int GeomHandle::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      if ( keyword == NULL && (keyword=lex->GetNext()) == NULL )
IF0  	throw new IoOldOoglParseException(lex,
IF0  	"Reading geom handle.  End-of-file unexpected, needed handle name.");
IF0  
IF0      UtString tmp(keyword);
IF0      mName = (char *) tmp.StealBuf();
IF0      return 1;
IF0  }
#endif

void GeomHandle::Draw(class MgContext *mg)
{
}
