#include "MgProperty.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"
#include <string.h>

TYPE_IMPLEMENT_TYPEINFO2(MgProperty, RefObject, StorageObject);

MgProperty::AnyArg MgProperty::spReadArgs[MAX_AP_ARGS];

MgProperty::MgProperty()
{
  mValid = mOverride = mFlags = 0;
}

void MgProperty::SetDo(int bitmask) {
  mFlags |= bitmask;
  mValid |= bitmask;
}

void MgProperty::SetDont(int bitmask) {
  mFlags &= ~bitmask;
  mValid |= bitmask;
}

int MgProperty::Load(const char *fname) { return 0; }

#if 0
IF0  int MgProperty::Load(IoOldOoglLexer *lex)
IF0  {
IF0    int brace = 0;
IF0    char *w;
IF0    int i; 
IF0    int got;                        // Put this back when ParseError code is reestablished -- jcm 10/22/97
IF0    int over, value;
IF0    int mask;
IF0    const KeywordTable *ktab;
IF0    const char *key = GetKeyword();
IF0  
IF0    if (lex->LookAhead(key))
IF0      lex->GetNext();
IF0    if (lex->LookAhead("{"))
IF0    { lex->GetNext(); brace = 1; }
IF0  
IF0      //else if (*w == '<') { w++; }
IF0      //else if (*w == ':') { w++; }
IF0  
IF0    over = 0;
IF0    value = 1;
IF0    while (!lex->LookAhead("}"))
IF0    {
IF0      w = lex->GetNext();
IF0      if (w == NULL)
IF0      {
IF0          if (brace == 0) return 1;
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading %s.  End-of-file unexpected.", key);
IF0      }
IF0  
IF0  //fprintf(stderr, "w = %s\n", w);
IF0  
IF0      if (*w == '*') { over = 1; w++; }   /* 'override' prefix */
IF0      if (*w == '+') { value = 1; w++; }
IF0      if (*w == '-') { value = 0; w++; }
IF0      if (*w == '\0') continue;
IF0  
IF0      ktab = GetKeywordTable();
IF0  
IF0  //fprintf(stderr, "%s:  Looking up word (%s)\n", key, w);
IF0      // Search for the string in the list of keywords.
IF0      for(i = GetNumKeywords(); --i >= 0; )
IF0        if(!strcmp(ktab[i].word, w))
IF0          break;
IF0  
IF0      // If it wasn't found, complain.
IF0      if (i < 0)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading %s.  Unknown keyword \"%s\"", key, w);
IF0  
IF0      // Otherwise, set the flags accordingly, read the arguments,
IF0      // and do any extra processing.
IF0  
IF0      mask = ktab[i].mask;
IF0      int num = ktab[i].numargs;
IF0      int type = ktab[i].typargs;
IF0      //static union { float f; int i; char *s; } array[10];
IF0      if (type == ARGS_REAL)
IF0      {
IF0        if ( (got=lex->ExpectFloat(num, (float*)spReadArgs)) < num)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading %s, keyword %s.  Expected %d number%s, got %d",
IF0              key, ktab[i].word, num, &"s"[num==1], got);
IF0      }
IF0      else if (type == ARGS_INT)
IF0      {
IF0        if ( (got=lex->ExpectInt(num, (int*)spReadArgs)) < num)
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading %s, keyword %s.  Expected %d integer%s, got %d",
IF0              key, ktab[i].word, num, &"s"[num==1], got);
IF0      }
IF0      else if (num > 0) /* Assume One ARGS_STRING */
IF0      {
IF0        char **a = (char **)spReadArgs;
IF0        *a = lex->GetNext();      // OOPS!  This will only work for one string
IF0                                  // because of the way token strings are stored.
IF0        if (lex->GetCurrentType() != IoOldOoglToken::STRING)
IF0            throw new IoOldOoglParseException(lex,
IF0            "Reading %s, keyword %s.  Couldn't read string following keyword.",
IF0            key, ktab[i].word);
IF0      }   
IF0  
IF0      if (!LoadProcess(lex, ktab[i].id, (void*)spReadArgs)) return 0;
IF0  
IF0      // Set the flags now.
IF0      mValid |= mask;
IF0      if (over)  mOverride |= mask;
IF0      if (value) mFlags |= mask;
IF0      else       mFlags &= ~mask;
IF0  
IF0      /* Reset for next keyword */
IF0      over = 0;
IF0      value = 1;
IF0    }
IF0  
IF0  //fprintf(stderr, "LookAhead = %s.\n", lex->LookAhead());
IF0  
IF0    // Right now we know that the next token (via LookAhead) is a closing brace.
IF0    // Read the closing brace if there was an opening brace to begin with.
IF0    if (brace > 0)
IF0      lex->GetNext();
IF0  
IF0  //if (brace > 0)
IF0  //fprintf(stderr, "Read the corresponding closing brace.\n");
IF0  //fprintf(stderr, "now LookAhead = %s.\n", lex->LookAhead());
IF0  
IF0    return 1;
IF0  }
#endif

int MgProperty::Save(IoDataStream *s, const char *keyword)
{
    int valid, mask;
    register int i;

    const KeywordTable *ktab = GetKeywordTable();

    valid = mValid;
#if PRINTPOINTERS
    s->PrintF("%s%s { #### addr = 0x%08x  [mRefCount=%3d]\n",
              GetIndent(), keyword, this, RefCount());
#else
    s->PrintF("%s%s {\n", GetIndent(), keyword);
#endif

    for(i = 0; i < GetNumKeywords(); i++)
    {
        mask = ktab[i].mask;
        if((valid & mask) == 0)
            continue;
        valid &= ~mask;

        s->PrintF( "\t%s%c %c%s", GetIndent(),
            (mOverride & mask) ? '*' : ' ',
            ((ktab[i].numargs == 0) && (mFlags&mask) == 0) ? '-' : ' ',
            ktab[i].word );
        if (ktab[i].numargs > 0)
            s->PutC(' ');
        if (!SaveProcess(s, mask)) return 0;
        
        s->PutC('\n');
    }

    if (!SaveProcessMore(s)) return 0;

    s->PrintF("%s}\n", GetIndent());
    return 1;
}
