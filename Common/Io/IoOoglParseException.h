//-*-C++-*-
#ifndef IO_OOGLPARSEEXCEPTION_H
#define IO_OOGLPARSEEXCEPTION_H

#include "UtException.h"
#include "IoOoglLexer.h"

class IoOoglParseException : public UtException
{
public:
  IoOoglParseException(class IoOoglLexer *lex, const char *format, ...);
  inline int LineNumber() const { return mLineNumber; }
  inline const char *FileName() const { return mFileName; }
  const char *Context();

private:
  int mLineNumber;
  const char *mFileName;
  IoOoglLexer *lex;
};

#endif // IO_OOGLPARSEEXCEPTION_H
