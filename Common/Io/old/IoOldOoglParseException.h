//-*-C++-*-
#ifndef IO_OOGLPARSEEXCEPTION_H
#define IO_OOGLPARSEEXCEPTION_H

#include "UtException.h"

class IoOldOoglParseException : public UtException
{
public:
    IoOldOoglParseException(class IoOldOoglLexer *lex, const char *format, ...);
//    IoOldOoglParseException(class IoOoglLexer *lex, const char *format, ...);
    inline int LineNumber() const { return mLineNumber; }
    inline const char *FileName() const { return mFileName; }

private:
    int mLineNumber;
    const char *mFileName;
};

#endif // IO_OOGLPARSEEXCEPTION_H
