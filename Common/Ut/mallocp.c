/* Copyright (c) 1992 The Geometry Center; University of Minnesota
   1300 South Second Street;  Minneapolis, MN  55454, USA;
   
This file is part of geomview/OOGL. geomview/OOGL is free software;
you can redistribute it and/or modify it only under the terms given in
the file COPYING, which you should have received along with this file.
This and other related software may be obtained via anonymous ftp from
geom.umn.edu; email: software@geom.umn.edu. */

/* Authors: Charlie Gunn, Stuart Levy, Tamara Munzner, Mark Phillips */

#include <stdlib.h>	/* Declare malloc() */
#include <stddef.h>	/* Define NULL */
#if CUTOUT
XX #include "ooglutil.h"	/* Declare OOGLError */
#endif /* CUTOUT */

/*
 * Pointers needed for OOGLNew(), etc.  Placed in a separate module so
 * non-shared-memory users needn't link with that code.
 */
void *OOG_CurSM		= NULL;

#ifdef sgi
void *(*OOG_NewP)(size_t)		= malloc;
void  (*OOGLFree)(void *)		= free;
void *(*OOG_RenewP)(void *, size_t)	= realloc;
#else
void *(*OOG_NewP)(int)			= malloc;
void  (*OOGLFree)(void *)		= free;
void *(*OOG_RenewP)(void *,int)		= realloc;
#endif


void *
OOG_NewE(int n, char *msg)
{
    register void *p;

    p = (*OOG_NewP)(n);
    if(p == NULL && n != 0) {
#if CUTOUT
XX 	OOGLError(1/*Fatal mem alloc*/,
XX 	    "OOGLNew: couldn't allocate %d bytes: %s: %s", n, msg, sperror());
#endif /* CUTOUT */
	exit(1);
    }
    return p;
}

void *
OOG_RenewE(void *p, int n, char *msg)
{
    p = (*OOG_RenewP)(p, n);
    if(p == NULL && n != 0) {
#if CUTOUT
XX 	OOGLError(1/*Fatal mem alloc*/,
XX 		"OOGLRenewN: couldn't reallocate %d bytes (from %x): %s: %s",
XX 		n, p, msg, sperror());
#endif /* CUTOUT */
	exit(1);
    }
    return p;
}
