#include "IoOoglParseException.h"

#include <string.h>
#include <stdio.h>
#include "IoOoglLexer.h"
#include "UtString.h"

IoOoglParseException::IoOoglParseException(IoOoglLexer *lex,
	const char *format, ...)
:   UtException(UtException::ERROR, NULL, UtException::DYNAMIC)
{
    va_list alist;
    va_start(alist, format);
    UtString str(format, alist);
    mpMessage = str.StealBuf();
    va_end(alist);

    this->lex   = lex;
    mFileName   = lex->FileName();
    mLineNumber = lex->LineNumber();
}

const char *IoOoglParseException::Context() {
  return lex->Context();
}
