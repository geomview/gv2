//-*-C++-*-
#ifndef UTEXCEPTION_H
#define UTEXCEPTION_H

#include <stdio.h>
#include <stdarg.h>

// class UtException.h
//	prerequisites:
//	    compile: none
//	       link: UtString.o
//
//	General purpose base class for exceptions.


////////////////////////////////////////////////////////////////////////
// Microsoft twerps #define ERROR in wingdi.h, which is included
// by windows.h, which some clients of this file need.  So just
// in case, we undefine it here, so that it doesn't clash with our
// enum value below.

#ifdef ERROR
#undef ERROR
#endif
////////////////////////////////////////////////////////////////////////

class UtException {
public:
  typedef enum {
    MESSAGE,
    WARNING,
    ERROR,
    FATAL
  } SeverityLevel;
  typedef enum {
    DYNAMIC,
    STATIC
  } MessageStorageType;
protected:
  SeverityLevel mSeverity;
  MessageStorageType mMessageStorageType;
  char *mpMessage;
public:
  UtException(SeverityLevel severity,
              char *message,
              MessageStorageType type = STATIC) {
    mSeverity = severity;
    mpMessage = message;
    mMessageStorageType = type;
  }
  UtException(SeverityLevel severity,
              const char *format, ...);
  ~UtException() {
      if (mMessageStorageType == DYNAMIC) delete mpMessage;
  }
  virtual char * Message();
  virtual char * Severity();
};

#endif // UTEXCEPTION_H
