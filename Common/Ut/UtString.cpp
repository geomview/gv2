#include "UtString.h"
#include <string.h>
#include <ctype.h>

char UtString::spBuffer[1024];

UtString::UtString()
{
    mpBuffer = NULL;
}

UtString::UtString(const char *format, ...)
{
    mpBuffer = NULL;
    va_list alist;
    va_start(alist, format);
    VPrintF(format, alist);
    va_end(alist);
}

UtString::UtString(const char *format, va_list alist)
{
    mpBuffer = NULL;
    VPrintF(format, alist);
}

UtString::UtString(const UtString &s)
{
    if (s.mpBuffer)
    {
        mpBuffer = new char[strlen(s.mpBuffer)+1];
        strcpy(mpBuffer, s.mpBuffer);
    }
    else mpBuffer = NULL;
}


UtString::~UtString()
{
    if (mpBuffer) delete [] mpBuffer;
}

void UtString::PrintF(const char *format, ...)
{
    va_list alist;
    va_start(alist, format);
    VPrintF(format, alist);
    va_end(alist);
}

void UtString::VPrintF(const char *format, va_list alist)
{
    vsprintf(spBuffer, format, alist);
    if (mpBuffer) delete [] mpBuffer;
    mpBuffer = new char[strlen(spBuffer)+1];
    strcpy(mpBuffer, spBuffer);
}

char *UtString::StealBuf()
{
    char *buf = mpBuffer;
    mpBuffer = NULL;
    return buf;
}

char *UtString::Strdup(const char *s)
{
    int len = strlen(s);
    char *scopy = new char[len+1];
    strcpy(scopy, s);
    return scopy;
}

int UtString::CaseInsensitiveStreq(const char *a, const char *b)
{
  while ( (*a != '\0') && (*b != '\0') ) {
    if (tolower(*a) != tolower(*b)) { return 0; }
    ++a;
    ++b;
  }
  if ( (*a != '\0') || (*b != '\0') ) { return 0; }
  return 1;
}
