#include "GeomList.h"
//#include "GeomOldOoglParser.h"
#include "GeomOoglParser.h"
#include "IoOoglParseException.h"
//#include "IoOldOoglParseException.h"
#include "UtString.h"

TYPE_IMPLEMENT_TYPEINFO1(GeomList, GeomParent);

GeomList::GeomList(int number, Geom *geoms) : mGeomList(number)
{
    for (int i = 0; i < number; i++)
    {
        mGeomList.AppendItem(&geoms[i]);
    }
}

void GeomList::Clear()
{
    mGeomList.Clear();
}

void GeomList::Draw(MgContext *mg)
{
  // There's apparently a bug in the implementation of UtVRefPtrArray,
  // or somewhere, that causes a segv in the 'for' loop (I think when
  // it tries to access mGeomList[0]) below if the list is empty.  So
  // for now, we check GetChildCount() > 0, but soon we should look
  // into and actually fix this bug.
  // mbp Thu Mar  8 17:31:25 2001
  if (GetChildCount() > 0) {
    for (int i = 0; mGeomList[i] != NULL; i++)
    {
        mGeomList[i]->Draw(mg); 
    }
  }
}

// There are no LIST flags.
static const char  list_keys[] = "";
static const short *list_bits = NULL;
//The above used to be
//   static const short list_bits[] = {};
// but this won't compile with MS VC++.  I think it's OK to just
// replace it with a NULL pointer, since there are no LIST flags
// but double-check this with Lori.
// mbp Wed Nov 12 23:05:55 1997

// Write the List in OOGL format.
int GeomList::Save(char *indent, IoDataStream *s)
{
  char *INDENT = indent ? indent : "";
  s->PrintF("%sLIST", INDENT);
  if (mpName) { s->PrintF("  # %s", mpName); }
  s->PrintF("\n");
  int i, n = GetChildCount();
  char buffer[1024], *NEWINDENT;
  if (indent) {
    sprintf(buffer, "%s  ", indent);
    NEWINDENT = buffer;
  } else {
    NEWINDENT = NULL;
  }
  for (i = 0; i < n; i++) {
    s->PrintF("%s{\n", INDENT);
    mGeomList[i]->Save(NEWINDENT, s);
    s->PrintF("%s}\n", INDENT);
  }
  return !s->error();
}


int GeomList::Load(class IoOoglLexer *lex, char *keyword)
{
  // Make sure keyword is "LIST"
  if (!UtString::CaseInsensitiveStreq(keyword, "LIST")) {
    throw new IoOoglParseException(lex,
	      "LIST object must start with keyword \"LIST\"");
  }

  int brace = 0;
  mGeomList.Clear();

    // Read till the end of file if necessary.
  while (lex->LookAhead() != IoOoglLexer::EOI) {

    // Keep track of the depth of braces.
    if (lex->LookAhead() == IoOoglLexer::LBRACE) {
      lex->Scan();
      brace++;
      continue;
    }

        // May match a { outside of this scope.
    if (lex->LookAhead() == IoOoglLexer::RBRACE) {
      // Read this only if the corresponding open brace was read
      // inside this function.
      if (brace > 0) {
	lex->Scan();
	brace--;
	continue;
      } else {
	break;
      }
    }

    // Parse the Oogl Object and store it in the expandable array.
    Geom *g = GeomOoglParser::Load(lex);
    mGeomList.AppendItem(g);
    // mGeomList.AppendItem() keeps its own reference to the object,
    // so we must delete the reference we created with GeomOldOoglParser()
    // here, since we're done with it now.
    ::DeleteRef(g);
  }

  // Make sure braces are balanced.
  if (brace > 0) {
    throw new IoOoglParseException(lex,
	   "Reading LIST.  Missing %d closing brace%s '}'",
            brace, &"s"[brace==1]);
  }

  return 1;
}

#if 0
IF0  // Read a List in OOGL format.
IF0  int GeomList::Load(IoOldOoglLexer *lex, char *keyword)
IF0  {
IF0      // Do this just to make sure the keyword is correct.
IF0      // Will cause and exception if not.
IF0      GeomOldOoglParser::GetHeader(lex, "LIST", keyword, list_keys, list_bits);
IF0  
IF0      int brace = 0;
IF0      mGeomList.Clear();
IF0  
IF0      // Read till the end of file if necessary.
IF0      while (lex->LookAhead() != NULL)
IF0      {
IF0          // Certain symbols also signal end-of-LIST.
IF0          if ( lex->LookAhead(";") || lex->LookAhead(")") )
IF0              break;
IF0  
IF0          // Keep track of the depth of braces.
IF0          if (lex->LookAhead("{"))        // }
IF0          {
IF0              lex->GetNext();
IF0              brace++;
IF0              continue;
IF0          }
IF0  
IF0          // May match a { outside of this scope.
IF0          if (lex->LookAhead("}"))
IF0          {
IF0              // Read this only if the corresponding open brace was read
IF0              // inside this function.
IF0              if (brace > 0)
IF0              {
IF0                  lex->GetNext();
IF0                  brace--;
IF0                  continue;
IF0              }
IF0              else
IF0                  break;
IF0          }
IF0  
IF0          // Parse the Oogl Object and store it in the expandable array.
IF0          Geom *g = GeomOldOoglParser::Load(lex);
IF0          mGeomList.AppendItem(g);
IF0          // mGeomList.AppendItem() keeps its own reference to the object,
IF0          // so we must delete the reference we created with GeomOldOoglParser()
IF0          // here, since we're done with it now.
IF0          ::DeleteRef(g);
IF0      }
IF0  
IF0      // Make sure braces are balanced.
IF0      if (brace > 0)
IF0          throw new IoOldOoglParseException(lex,       //  {
IF0              "Reading LIST.  Missing %d closing brace%s '}'",
IF0              brace, &"s"[brace==1]);
IF0  
IF0      return 1;
IF0  }
#endif

////////////////////////////////////////////////////////////////////////

int   GeomList::GetChildCount()
{
    return mGeomList.GetCount();
}

Geom *GeomList::GetChild(int index)
{
    if (index >= 0 && index < mGeomList.GetCount()) return mGeomList[index];
    else return NULL;
}


void  GeomList::AddChild(Geom *geom)
{
    mGeomList.AppendItem(geom);
}

void  GeomList::RemoveChild(Geom *geom)
{
    int index = GetChildIndex(geom);
    if (index >= 0) mGeomList.RemoveItem(index);
}

int GeomList::GetChildIndex(Geom *geom)
{
    int i;
    for (i=0; i<mGeomList.GetCount(); ++i)
        if (geom == mGeomList[i]) return i;
    return -1;
}

void  GeomList::RemoveChild(int index)
{
    mGeomList.RemoveItem(index);
}

