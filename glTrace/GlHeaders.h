#ifndef MGMSGLHEADERS_H
#define MGMSGLHEADERS_H

#ifndef __WIN32__
#include "config.h"
#endif

// If we're on Windows, include <windows.h>
#ifdef __WIN32__
#ifndef WINDOWS_H  // external include guard
#define WINDOWS_H
#include <windows.h>
#ifdef ERROR	  // wingdi.h, which is included by windows.h, defines ERROR
#undef ERROR	  // which is a terrible thing to do, so we undo it here
#endif // ERROR
#endif // WINDOWS_H
#endif // __WIN32__

#ifdef GEOM_GLTRACE
/* vote yes for GEOM_GLTRACE */
#  include "glTraceProtos.h"
#  include "glTraceMacros.h"
#else
/* just say no to GEOM_GLTRACE */
#  include <GL/gl.h>
#  include "glNoTraceMacros.h"
#endif
#include <GL/glu.h>

#endif MGMSGLHEADERS_H
