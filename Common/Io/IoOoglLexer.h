//-*-C++-*-
#ifndef IOOOGLLEXER_H
#define IOOOGLLEXER_H

#include <stdlib.h>
#include <stdio.h>
#include "IoDataStream.h"
#include "UtLStack.h"

// class IoOoglLexer
// 
// Lexical scanner for OOGL files.  This class reads from an input source
// and converts it into a sequence of tokens.  In general, use like:
// 
//   IoOoglLexer *lex = new IoOoglLexer(...);
//      // arguments to constructor specify where to take input from
// 
//   while (lex->Scan()) {
//     switch (lex->GetType()) {
//       case IoOoglLexer::INT:
// 	printf("%10s   %1d\n", "INT",     lex.GetIntValue());
// 	break;
//       case IoOoglLexer::DOUBLE:
// 	printf("%10s   %1g\n", "DOUBLE",  lex.GetDoubleValue());
// 	break;
//       case IoOoglLexer::STRING:
// 	printf("%10s   '%s'\n", "STRING", lex.GetStringValue());
// 	break;
//       case IoOoglLexer::NEWLINE:
// 	printf("%10s\n", "NEWLINE");
// 	break;
//       //
//       // ... etc ...   There are more token types; see below for
//       //               the complete list.
//       //
//     }
//   }

class IoOoglLexer {
public:
  typedef enum {
    INT,
    STRING,
    DOUBLE,
    COLON,
    LBRACE,
    RBRACE,
    EQUAL,
    NEWLINE,
    EOI,
    FLOAT
    // Note: the scanner will never return a FLOAT; the FLOAT value
    // here is just for passing to ExpectNum when you want to scan
    // into an array of floats rather than doubles.  It actually scans
    // as if you'd passed DOUBLE, but assumes the array it's writing
    // into conists of floats.
  } TokenType;


private:
  typedef struct Token {
    TokenType  mType;
    char       mValueBuffer[512];
    int        mReturnValue;
    union {
      double d;
      int    i;
      // don't use this for string values; use mValueBuffer instead
    } mValue;
  } Token;
  UtLStack<Token> mTokenStack;

public:
  IoOoglLexer(IoDataStream *ds);
  IoOoglLexer(char *file);
  IoOoglLexer(FILE *fp);
  ~IoOoglLexer();

  // Parse the next token from the data stream; returns 1 if it
  // found a token, 0 if not.  After return, the type of the token
  // found can be fetched via GetType(), and the value via
  // GetDoubleValue(), GetIntValue(), or GetStringValue().
  int Scan();

  // Returns the type of the *next* token that Scan() will return.
  // You'll need to actually call Scan() before you can access the
  // actual value of the token.
  IoOoglLexer::TokenType LookAhead();

  inline TokenType GetType()        { return mTokenStack.Top()->mType;    }
  inline double    GetDoubleValue() { return mTokenStack.Top()->mValue.d; }
  inline int       GetIntValue()    { return mTokenStack.Top()->mValue.i; }
  inline char *    GetStringValue() { return mTokenStack.Top()->mValueBuffer; }
  // Note:  GetStringValue() can always be called to get the
  //   string representation of the last token read, verbatim
  //   as it came from the input, even when the token type
  //   is something other than STRING.

  void SetNewlineSignificance(int sig);
  int GetNewlineSignificance();

  inline IoDataStream *GetIoDataStream() { return mpDs; }

  inline int LineNumber() { return mLine; }

  const char *FileName() { return mpDs->GetFileName(); }

  virtual int ExpectNum(int count, void *array,
			IoOoglLexer::TokenType type);

  const char *IoOoglLexer::Context();

  void UnScan();

  char *ToString();

  typedef unsigned char UChar;
  typedef unsigned int  UInt;

private:


  IoDataStream  *mpDs;
  UChar		*mpBot, *mpTok, *mpPtr, *mpCur, *mpPos, *mpLim, *mpTop, *mpEof;
  UInt		mLine;
  int           mNewlineIsSignificant;
  int		mOwnDs;
  UChar		*mpLastBuf;

  UChar         *Fill(UChar *cursor);
  void		Init(IoDataStream *ds);

  int		mUnScanned;

  char          mToStringBuffer[512];
};

#endif // IOOOGLLEXER_H
