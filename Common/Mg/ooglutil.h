/* Copyright (c) 1992 The Geometry Center; University of Minnesota
   1300 South Second Street;  Minneapolis, MN  55454, USA;
   
This file is part of geomview/OOGL. geomview/OOGL is free software;
you can redistribute it and/or modify it only under the terms given in
the file COPYING, which you should have received along with this file.
This and other related software may be obtained via anonymous ftp from
geom.umn.edu; email: software@geom.umn.edu. */

/* Authors: Charlie Gunn, Stuart Levy, Tamara Munzner, Mark Phillips */

#ifndef OOGLUTILDEF

#define OOGLUTILDEF

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define M_PI 3.14159265358979323
#endif


/*
 * Definition so that (obsolete Irix 3) SGIs won't barf on member function prototypes.
 */
#ifdef no_prototypes
#define P(foo) ()
#else
#define P(foo) foo
#endif


#define	COUNT(array)	(sizeof(array)/sizeof(array[0]))

/*
 * Public definitions for miscellaneous useful OOGL internal stuff.
 */

#define	OOGLMagic(key, vers)    (0x9c800000 | (((key)&0x7f)<<16) | ((vers)&0xffff) )
#define OOGLIsMagic(magic)	(((magic) & 0xff800000) == 0x9c800000)


#define	OOGLNew(t)		(t *)(*OOG_NewP)(sizeof(t))
#define	OOGLNewN(t,N)		(t *)(*OOG_NewP)(sizeof(t)*(N))
#define	OOGLRenewN(t,p,N)	(t *)(*OOG_RenewP)(p, sizeof(t)*(N))
#define	OOGLRealloc(t,p)	(t *)(*OOG_RenewP)(p, sizeof(t))

#define	OOGLNewE(t, errmsg)	(t *)OOG_NewE(sizeof(t), errmsg)
#define	OOGLNewNE(t,N, errmsg)	(t *)OOG_NewE(sizeof(t)*(N), errmsg)
#define	OOGLRenewNE(t,p,N, errmsg) (t *)OOG_RenewE(p, sizeof(t)*(N), errmsg)

/*
 * Backward compatibility
 */
#define	GeomNew(t)		OOGLNew(t)
#define	GeomNewN(t,N)		OOGLNewN(t,N)
#define	GeomFree(p)		OOGLFree(p)
#define	GeomError  		OOGLError

/*
 * Variable-sized arrays ("vectors").  Manipulates variables of type "vvec".
 * Maintains the data they point to, but doesn't allocate the vvec's themselves;
 * typical use might be
 *   vvec myvec;
 *   VVINIT(myvec, float, 10);
 *   while( ... ) {
 *	*VVAPPEND(myvec, float) = something;
 *   }
 *   for(i = 0; i < VVSIZE(myvec); i++)
 *	... VVEC(myvec, float)[i] ...
 * 
 */
typedef struct vvec {
	char *base;	/* The real data */
	int count;	/* Number of elements in use (indices 0..count-1) */
	int allocated;	/* Number of elements allocated */
	int elsize;	/* sizeof(element type) */
	char dozero;	/* Zero-fill all new elements */
	char malloced;	/* "base" has been malloced */
	char spare1, spare2; /* for future extensions */
} vvec;

/*
 * Macros take 'vvec' arguments, while functions take addresses of vvec's.
 * VVINIT() : initialize new empty array; first malloc will grab >= 'minelems'.
 * VVZERO() : request that all newly allocated elements be cleared to zeros
 * VVINDEX() : return address of index'th element, ensuring that it exists.
 * VVAPPEND() : increments array size, returning address of new last element
 * VVEC()   : returns address of array base; VVEC()[i] is the i'th element
 *		assuming that its existence was ensured by earlier call to
 *		VVAPPEND() or VVINDEX() or vvneeds().
 * VVCOUNT() : number of valid elements in array.  Maintained by user.
 */
#define	VVINIT(vv,type,minelems)  vvinit(&(vv), sizeof(type), minelems)
#define	VVEC(vv, type)		((type *)((vv).base))
#define	VVCOUNT(vv)		(vv).count
#define	VVINDEX(vv,type,index)	((type *)vvindex(&(vv), (index)))
#define	VVAPPEND(vv, type)  	VVINDEX(vv, type, (vv).count++)



#if CUTOUT
XX /*
XX  * Error handling
XX  */
XX extern char *_GFILE;		/* Name of file where error is found */
XX extern int _GLINE;		/* Line number in file where error is found */
XX extern int OOGL_Errorcode;	/* Unique integer error code */
XX extern void OOGLWarn (char *fmt, ...);
XX extern char *sperrno(unsigned int);
XX extern char *sperror(void);
XX 
XX /* Kludge for obtaining file name and line number of error: */
XX #define OOGLError (_GFILE= __FILE__, _GLINE=__LINE__,0)?0:_OOGLError
XX 
XX extern int _OOGLError(int, char *fmt, ...);
XX 
XX extern void OOGLSyntax(FILE *, char *fmt, ...); 
XX 
XX 	/* Bit fields in error codes */
XX #define	OE_VERBOSE	0x1
XX #define	OE_FATAL	0x2
XX 
XX 
XX /*
XX  * File-I/O utility routines
XX  */
XX extern int fnextc(FILE *, int flags);
XX extern int fexpectstr(FILE *, char *string);
XX extern int fexpecttoken(FILE *, char *string);
XX extern char *ftoken(FILE *, int fnextc_flags);
XX extern char *fdelimtok(char *delims, FILE *f, int flags);
XX 
XX extern int fgetnf(FILE *, int nfloats, float *floatp, int binary);
XX extern int fputnf(FILE *, int nfloats, float *floatp, int binary);
XX extern int fgetni(FILE *, int nints, int *intp, int binary);
XX extern int fgetns(FILE *, int nshorts, short *shortp, int binary);
XX extern int fgettransform(FILE *, int ntrans, float *transforms, int binary);
XX extern int fputtransform(FILE *, int ntrans, float *transforms, int binary);
XX extern FILE *fstropen(char *buf, int buflen, char *mode);
XX extern int fhasdata(FILE *);
XX 
XX /*
XX  * fcontext(f) returns a string indicating the current position of file f,
XX  * or the empty string if no data are available.
XX  */
XX extern char *fcontext(FILE *f);
XX 
XX 
XX #define	NODATA	-2	/* async_fnextc() and async_getc() return NODATA if
XX 			 * none is immediately available
XX 			 */
XX 
XX extern int async_fnextc(FILE *, int flags);
XX extern int async_getc(FILE *);
XX 
XX extern struct stdio_mark *stdio_setmark(struct stdio_mark *, FILE *);
XX extern int		  stdio_seekmark(struct stdio_mark *);
XX extern void		  stdio_freemark(struct stdio_mark *);
XX 
XX /*
XX  * int fnextc(FILE *f, int flags)
XX  *	Advances f to the next "interesting" character and
XX  *	returns it.  The returned char is ungetc'ed so the next getc()
XX  *	will yield the same value.
XX  *	Interesting depends on flags:
XX  *	  0 : Skip blanks, tabs, newlines, and comments (#...\n).
XX  *	  1 : Skip blanks, tabs, and comments, but newlines are interesting
XX  *		(including the \n that terminates a comment).
XX  *	  2 : Skip blanks, tabs, and newlines, but stop at #.
XX  *	  3 : Skip blanks and tabs but stop at # or \n.
XX  *
XX  * int
XX  * fexpectstr(FILE *file, char *string)
XX  *	Expect the given string to appear immediately on file.
XX  *	Return 0 if the complete string is found,
XX  *	else the offset+1 of the last matched char within string.
XX  *	The first unmatched char is ungetc'd.
XX  *
XX  * int
XX  * fexpecttoken(FILE *file, char *string)
XX  *	Expect the given string to appear on the file, possibly after
XX  *	skipping some white space and comments.
XX  *	Return 0 if found, else the offset+1 of last matched char in string.
XX  *	The first unmatched char is ungetc'd.
XX  *
XX  * char *ftoken(FILE *f, int flags)
XX  *	Skips uninteresting characters with fnextc(f, flags),
XX  *	then returns a "token" - string of consecutive interesting characters.
XX  *	Returns NULL if EOF is reached with no token, or if
XX  *	flags specifies stopping at end-of-line and this is encountered with
XX  *	no token found.
XX  *	The token is effectively statically allocated and will be
XX  *	overwritten by the next ftoken() call.
XX  */
XX /*
XX  * int fgetnf(file, nfloats, floatp, binary)
XX  *	Read an array of floats from a file in "ascii" or "binary" format.
XX  *	Returns number of floats successfully read, should = nfloats.
XX  *	"Binary" means "IEEE 32-bit floating-point" format.
XX  *
XX  * int fgetni(FILE *file, int nints, int *intsp, int binary)
XX  *	Read an array of ints from a file in "ascii" or "binary" format.
XX  *	Returns number of ints successfully read, should = nints.
XX  *	"Binary" means "32-bit big-endian" integer format.
XX  *
XX  * int fgetns(FILE *file, int nshorts, short *intsp, int binary)
XX  *	Read an array of shorts from a file in "ascii" or "binary" format.
XX  *	Returns number of shorts successfully read, should = nints.
XX  *	"Binary" means "16-bit big-endian" integer format.
XX  *
XX  * int fgettransform(FILE *f, int ntransforms, float *transforms, int binary)
XX  *	Reads 4x4 matrices from FILE.  Returns the number of matrices found,
XX  *	up to ntransforms.  Returns 0 if no numbers are found.
XX  *	On finding incomplete matrices (not a multiple of 16 floats)
XX  *	returns -1, regardless of whether any whole matrices were found.
XX  *	In ASCII (binary==0) mode, matrices are read in conventional order
XX  *	which is the transpose of the internal form.  Binary mode reads
XX  *	32-bit IEEE floats in internal order.
XX  *
XX  * int fputtransform(FILE *f, int ntransforms, float *transforms, int binary)
XX  *	Writes 4x4 matrices to FILE.  Returns the number written, i.e.
XX  *	ntransforms unless an error occurs.  See fgettransform() for format.
XX  *
XX  * FILE *fstropen(str, len, mode)
XX  *	Opens a string (buffer) as a "file".
XX  *	Mode is the usual "r", "w", etc. stuff.
XX  *	Reads should return EOF on encountering end-of-string,
XX  *	writes past end-of-string should also yield an error return.
XX  *	fclose() should be used to free the FILE after use.
XX  */
XX 
XX extern char *findfile(char *superfile, char *file);
XX extern void filedirs(char *dirs[]);
XX extern char **getfiledirs();
XX char *envexpand(char *s);
XX 
XX extern char **ooglglob(char *s);
XX extern ooglblkfree(char **av0);
XX 
#endif /* CUTOUT */

/*
 * macro for grabbing the next value from either a region of
 * memory or a va_list.
 * al should be the address of the va_list
 * p should be the address of a poiner to the region of memory,
 *   or NULL, which means use the va_list instead.
 */
#define OOGL_VA_ARG(type,al,p) (p ? ((type*)((*p)+=sizeof(type)))[-1] \
    : (va_arg (*al, type)))

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
extern int finite(double v);
extern int strcasecmp(char *s1, char *s2);
#endif

/*
 * Memory allocation
 */
#ifdef sgi
extern void *(*OOG_NewP)(size_t);
extern void *(*OOG_RenewP)(void *, size_t);
#else
extern void *(*OOG_NewP)(int);
extern void *(*OOG_RenewP)(void *, int);
#endif

extern void (*OOGLFree)(void *);
extern void *OOG_NewE(int, char *);
extern void *OOG_RenewE(void *, int, char *);

/* Functions take addresses of vvec's.  Besides the above, there are
 * vvtrim() : trim allocated but unused space (beyond VVCOUNT()'th element).
 * vvfree() : free malloced array.
 * vvneeds(): ensure that at least this many elements are allocated
 * vvzero() : all newly allocated elements will be filled with binary zeros
 * vvuse()  : Use the given non-malloced buffer until more room is needed;
 *		call vvuse() after vvinit() but before allocating anything.
 * vvcopy() : copies one vvec into another, allocating space in the 
 *              destination to accommodate the data and copying everything.
 */
extern void vvinit(vvec *v, int elsize, int minelems);
extern void vvuse(vvec *v, void *buf, int allocated);
extern void vvtrim(vvec *v);		/* Trim allocated but unused data */
extern void vvfree(vvec *v);		/* Free all malloced data */
extern void vvneeds(register vvec *v, int needed);
extern void *vvindex(vvec *v, int index);
extern void vvzero(vvec *v);
extern void vvcopy(vvec *src, vvec *dest);



#ifdef __cplusplus
}
#endif




#if CUTOUT
XX #include "porting.h"
#endif /* CUTOUT */

#endif
