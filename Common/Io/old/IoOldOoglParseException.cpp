#include "IoOldOoglParseException.h"

#include <string.h>
#include <stdio.h>
#include "IoOldOoglLexer.h"
#include "UtString.h"

IoOldOoglParseException::IoOldOoglParseException(IoOldOoglLexer *lex,
	const char *format, ...)
:   UtException(UtException::ERROR, NULL, UtException::DYNAMIC)
{
    va_list alist;
    va_start(alist, format);
    UtString str(format, alist);
    mpMessage = str.StealBuf();
    va_end(alist);

    mFileName = lex->FileName();
    mLineNumber = lex->LineNumber();
}
