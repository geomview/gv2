#include "UtException.h"

#include <string.h>
#include <stdio.h>

#include "UtString.h"

UtException::UtException(SeverityLevel severity,
                         const char *format, ...)
{
    mSeverity = severity;

    va_list alist;
    va_start(alist, format);
    UtString s(format, alist);
    va_end(alist);
    mpMessage = s.StealBuf();
    mMessageStorageType = DYNAMIC;
}


char * UtException::Severity()
{
    switch (mSeverity) {
    case MESSAGE: return ("MESSAGE");
    case WARNING: return ("WARNING");
    case ERROR:         return ("ERROR");
    case FATAL:         return ("FATAL");
    }
    return ("<UNKNOWN ERROR TYPE>");
}

char * UtException::Message()
{
    return mpMessage;
}
