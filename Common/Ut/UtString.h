//-*-C++-*-

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// class UtString
//	prerequisites: none
//
//	A class for creating and manipulating small strings.  The implementation
//	uses a small internal buffer of fixed size (currently 1024; it's
//	spBuffer, defined in UtString.cpp).
//

class UtString
{
public:
    UtString();
    UtString(const char *format, ...);
    UtString(const char *format, va_list alist);
    UtString(const UtString &s);
    ~UtString();
    void PrintF(const char *format, ...);
    char *StealBuf();

    // "cast to char *" operator:
    operator char *() { return mpBuffer; }

    // Here's a version of strdup which uses "new" to allocate the
    // string, rather than "malloc".  It's the caller's responsbility
    // to "delete" (not "free") the string when done with it.
    // (This function is not related to the rest of the UtString
    // class; it's just here because it deals with strings.)
    static char *Strdup(const char *s);


    // General string comparison function; returns 1 iff the two
    // strings are equal.  Use this to avoid having to write things
    // like "if (strcmp(a,b) != 0) { ... }", or the even more cryptic
    // "if (!strcmp(a,b)) { ... }".
    static int Streq(const char *a, const char *b) {
        return (strcmp(a,b) == 0);
    }

  static int CaseInsensitiveStreq(const char *a, const char *b);

private:
    static char spBuffer[];
    char *mpBuffer;
    void VPrintF(const char *format, va_list alist);
};
