//-*-C++-*-
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "IoOoglLexer.h"
#include "IoOoglParseException.h"
#include "UtString.h"

#define	BSIZE	8192

IoOoglLexer::IoOoglLexer(IoDataStream *ds)
{
  Init(ds);
}

void IoOoglLexer::Init(IoDataStream *ds)
{
  this->mpDs = ds;
  mpBot = mpTok = mpPtr = mpCur = mpPos = mpLim = mpTop = mpEof = 0;
  mLine = 0;
  mNewlineIsSignificant = 0;
  mOwnDs = 0;
  mTokenStack.Push(); // create top node in stack
}

IoOoglLexer::IoOoglLexer(char *file)
{
  Init(new IoDataStream(file, "r"));
  mOwnDs = 1;
}

IoOoglLexer::IoOoglLexer(FILE *fp)
{
  Init(new IoDataStream(fp));
  mOwnDs = 1;
}

IoOoglLexer::~IoOoglLexer()
{
  if (mOwnDs && mpDs!=NULL) {
    delete mpDs;
  }
}

char *IoOoglLexer::ToString()
{
  switch (GetType()) {
  case     INT: sprintf(mToStringBuffer, "INT[%s]",     GetStringValue());
  case  STRING: sprintf(mToStringBuffer, "STRING[%s]",  GetStringValue());
  case  DOUBLE: sprintf(mToStringBuffer, "DOUBLE[%s]",  GetStringValue());
  case   COLON: sprintf(mToStringBuffer, "COLON[%s]",   GetStringValue());
  case  LBRACE: sprintf(mToStringBuffer, "LBRACE[%s]",  GetStringValue());
  case  RBRACE: sprintf(mToStringBuffer, "RBRACE[%s]",  GetStringValue());
  case   EQUAL: sprintf(mToStringBuffer, "EQUAL[%s]",   GetStringValue());
  case NEWLINE: sprintf(mToStringBuffer, "NEWLINE[%s]", GetStringValue());
  case     EOI: sprintf(mToStringBuffer, "EOI",         GetStringValue());
  case   FLOAT: sprintf(mToStringBuffer, "FLOAT[%s]",   GetStringValue());
  default     : sprintf(mToStringBuffer, "UNKNOWN TOKEN TYPE");
  }
  return mToStringBuffer;
}


int IoOoglLexer::ExpectNum(int count, void *array,
			      IoOoglLexer::TokenType wantType)
{
  int i;
  for (i=0; i<count; ++i) {
    Scan();
    int gotType = GetType();
    switch (wantType) {
    case INT:
      switch (gotType) {
      case INT:
	((int*)array)[i] = GetIntValue();
	break;
      default:
	UnScan();
	return i;
      }
      break;
    case DOUBLE:
      switch (gotType) {
      case DOUBLE:
	((double*)array)[i] = GetDoubleValue();
	break;
      case INT:
	((double*)array)[i] = GetIntValue();
	break;
      default:
	UnScan();
	return i;
	break;
      }
      break;
    case FLOAT:
      switch (gotType) {
      case DOUBLE:
	((float*)array)[i] = (float)GetDoubleValue();
	break;
      case INT:
	((float*)array)[i] = (float)GetIntValue();
	break;
      default:
	UnScan();
	return i;
	break;
      }
      break;
    default:
	throw new IoOoglParseException(this,
          "unrecognized number type in IoOoglLexer::ExpectNum");
	break;
      }
  }
  return i;
}


void IoOoglLexer::SetNewlineSignificance(int sig)
{
  mNewlineIsSignificant = sig;
}

int IoOoglLexer::GetNewlineSignificance()
{
  return mNewlineIsSignificant;
}

IoOoglLexer::UChar *IoOoglLexer::Fill(UChar *cursor)
{
  if (!this->mpEof) {
    UInt cnt = this->mpTok - this->mpBot;
    if (cnt) {
      memcpy(this->mpBot, this->mpTok, this->mpLim - this->mpTok);
      this->mpTok  = this->mpBot;
      this->mpPtr -= cnt;
      cursor      -= cnt;
      this->mpPos -= cnt;
      this->mpLim -= cnt;
    }
    if ((this->mpTop - this->mpLim) < BSIZE) {
      UChar *buf =
	(UChar*) malloc(((this->mpLim - this->mpBot) + BSIZE)*sizeof(UChar));
      memcpy(buf, this->mpTok, this->mpLim - this->mpTok);
      this->mpLastBuf = 
	this->mpTok = buf;
      this->mpPtr = &buf[this->mpPtr - this->mpBot];
      cursor      = &buf[cursor    - this->mpBot];
      this->mpPos = &buf[this->mpPos - this->mpBot];
      this->mpLim = &buf[this->mpLim - this->mpBot];
      this->mpTop = &this->mpLim[BSIZE];
      free(this->mpBot);
      this->mpBot = buf;
    }
    if ((cnt = this->mpDs->Read((char*) this->mpLim, BSIZE)) != BSIZE) {
      this->mpEof = &this->mpLim[cnt];
      *(this->mpEof)++ = '\n';
    }
    this->mpLim += cnt;
  }
  return cursor;
}




const char *IoOoglLexer::Context()
{
  //  UtString str("LastBuf = '%s'\nmpTok = '%s'\n",
  //	       mpLastBuf, mpTok);
  //  static char buffer[1024];
  //  strcpy(buffer, str.StealBuf());

  int pos = mpTok - mpLastBuf;
  int col = 0;
  int bi = 0;
  static char buffer[1024];
  UChar *s = mpLastBuf;
  while (s <= mpTok) {
    buffer[bi++] = *s;
    if (*s == '\n') {
      col = 0;
    } else {
      ++col;
    }
    ++s;
  }
  while ( (*s!='\n') && (*s!='\0') ) {
    buffer[bi++] = *(s++);
  }
  if (buffer[bi-1]!='\n') {
    buffer[bi++]='\n';
  }
  int i;
  for (i=0; i<col-1; ++i) {
    buffer[bi++] = ' ';
  }
  buffer[bi++] = '^';
  buffer[bi++] = '\n';
  buffer[bi++] = '\0';
  return buffer;
}




#define	YYCTYPE		UChar
#define	YYCURSOR	cursor
#define	YYLIMIT		this->mpLim
#define	YYMARKER	this->mpPtr
#define	YYFILL(n)	{cursor = Fill(cursor);}

#define	RET(i)	{this->mpCur = cursor; \
  return (mTokenStack.Top()->mReturnValue=i);}

void IoOoglLexer::UnScan()
{
  if (mTokenStack.Depth() < 2) {
    mTokenStack.Push();
  } else {
    throw new IoOoglParseException(this,
        "IoOoglLexer: multiple UnScans not yet supported");
  }
}

IoOoglLexer::TokenType IoOoglLexer::LookAhead()
{
  Scan();
  TokenType type = GetType();
  UnScan();
  return type;
}
  

int IoOoglLexer::Scan()
{
  if (mTokenStack.Depth() > 1) {
    mTokenStack.Pop();
    return mTokenStack.Top()->mReturnValue;
  }

	UChar *cursor = this->mpCur;
standard:
	this->mpTok = cursor;
/*!re2c
any	= [\000-\377];
O	= [0-7];
D	= [0-9];
L	= [a-zA-Z_];
H	= [a-fA-F0-9];
E	= [Ee] [+-]? D+;
ESC	= [\\] ([abfnrtv?'"\\] | "x" H+ | O+);
*/

/*!re2c
	"#"			{ goto comment; }
	
        "="	{
		  mTokenStack.Top()->mType = EQUAL;
		  strcpy(mTokenStack.Top()->mValueBuffer, "=");
		  RET(1);
		}

        ":"	{
		  mTokenStack.Top()->mType = COLON;
		  strcpy(mTokenStack.Top()->mValueBuffer, ":");
		  RET(1);
		}

        "{"	{
		  mTokenStack.Top()->mType = LBRACE;
		  strcpy(mTokenStack.Top()->mValueBuffer, "{");
		  RET(1);
		}

        "}"	{
		  mTokenStack.Top()->mType = RBRACE;
		  strcpy(mTokenStack.Top()->mValueBuffer, "}");
		  RET(1);
		}

	[+-]? D+
		{
		  mTokenStack.Top()->mType = INT;
	          strncpy(mTokenStack.Top()->mValueBuffer,
		          (char*)(this->mpTok),
		          cursor - this->mpTok);
		  mTokenStack.Top()->mValueBuffer[cursor-this->mpTok] = '\0';
		  mTokenStack.Top()->mValue.i =
		     atoi(mTokenStack.Top()->mValueBuffer);
		  RET(1);
		}

	[+-]? ((D* "." D+ E?) | (D+ "." D* E?) | (D+ E))
		{
		  mTokenStack.Top()->mType = DOUBLE;
	          strncpy(mTokenStack.Top()->mValueBuffer,
		          (char*)(this->mpTok),
		          cursor - this->mpTok);
		  mTokenStack.Top()->mValueBuffer[cursor-this->mpTok] = '\0';
		  mTokenStack.Top()->mValue.d = 
		      atof(mTokenStack.Top()->mValueBuffer);
		  RET(1);
		}

	L+
		{
		  mTokenStack.Top()->mType = STRING;
	          strncpy(mTokenStack.Top()->mValueBuffer,
		          (char*)(this->mpTok),
		          cursor - this->mpTok);
		  mTokenStack.Top()->mValueBuffer[cursor-this->mpTok] = '\0';
		  RET(1);
		}
	[ \t\v\f]+		{ goto standard; }

	"\n"
	    {
	      if (cursor == this->mpEof) {
		  mTokenStack.Top()->mType = EOI;
		  RET(0);
              }
	      if (mNewlineIsSignificant) {
	          mTokenStack.Top()->mType = NEWLINE;
		  this->mpPos = cursor; this->mLine++;
		  RET(1);
	      } else {
	          goto standard;
	      }
            }


	any
	    {
		printf("unexpected character: %c\n", *this->mpTok);
		goto standard;
	    }
*/

comment:
/*!re2c
	"\n"			{ goto standard; }
        any			{ goto comment; }
*/

}


