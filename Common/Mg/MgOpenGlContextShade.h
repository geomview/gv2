//-*-C++-*-
#ifndef MGOPENGLCONTEXTSHADE_H
#define MGOPENGLCONTEXTSHADE_H

/* Copyright (c) 1992 The Geometry Center; University of Minnesota
   1300 South Second Street;  Minneapolis, MN  55454, USA;
   
This file is part of geomview/OOGL. geomview/OOGL is free software;
you can redistribute it and/or modify it only under the terms given in
the file COPYING, which you should have received along with this file.
This and other related software may be obtained via anonymous ftp from
geom.umn.edu; email: software@geom.umn.edu. */

/* Authors: Charlie Gunn, Stuart Levy, Tamara Munzner, Mark Phillips */

extern void	mgopengl_material(struct mgastk *, int mask );
extern void	mgopengl_lighting( struct mgastk *, int mask );
extern void	mgopengl_lights( MgLight *light, struct mgastk * );
extern int	mgopengl_materialdef( int matno, MgMaterial *mat, int mask );
extern int	mgopengl_lightdef( int lightno, MgLight *light, MgLighting *lgt, int mask);
extern int	mgopengl_lightmodeldef(int lightmodel, MgLighting *lgt, int mask, struct mgastk *);
extern void	mgopengl_d4f( float *c );

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
extern void mgopengl_c4f(float *c);
// extern void mgopengl_n3f(float *c, float *dummy);
#else
#define mgopengl_c4f glColor4fv
// #define mgopengl_n3f glNormal3fv
#endif /*_WIN32*/

#ifdef __cplusplus
}
#endif

#endif /* MGOPENGLCONTEXTSHADE_H */
