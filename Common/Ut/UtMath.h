//-*-C++-*-
#ifndef UTMATH_H
#define UTMATH_H

// UtMath.h
//    prerequistes: none
//
//    Define some general purpose macros & types

#define UtMathMIN(x,y) ( (x) < (y) ? (x) : (y) )
#define UtMathMAX(x,y) ( (x) > (y) ? (x) : (y) )

#define UtMathPI 3.1415927

// jcm-purify
typedef int UtBool;

#define UtTRUE (0 == 0)
#define UtFALSE (1 == 0)

#endif // UTMATH_H
