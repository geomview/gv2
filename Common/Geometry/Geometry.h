#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <math.h>
#include <stdio.h>
#include "Point3.h"
#include "HPoint3.h"
#include "Transform3.h"

/* From Knuth: vol I */
#ifndef PI
#define  PI 3.1415926535897932384626433832795028841972
#endif

#define RADIANS(angle) ((PI/180.0)*(angle))
#define DEGREES(angle) ((180.0/PI)*(angle))

#endif /* GEOMETRY_H */
