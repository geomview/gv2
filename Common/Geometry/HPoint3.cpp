#include <stdio.h>
#include <math.h>
#include "HPoint3.h"

HPoint3 HPoint3::XAXIS  = { 1.0, 0.0, 0.0, 0.0 };
HPoint3 HPoint3::YAXIS  = { 0.0, 1.0, 0.0, 0.0 };
HPoint3 HPoint3::ZAXIS  = { 0.0, 0.0, 1.0, 0.0 };
HPoint3 HPoint3::ORIGIN = { 0.0, 0.0, 0.0, 1.0 };

char * HPoint3::ToString(char *buffer)
{
  sprintf(buffer, "[%9.5f, %9.5f, %9.5f, %9.5f]", x, y, z, w);
  return buffer;
}

void    HPoint3::Subtract(const HPoint3 *a, const HPoint3 *b)
{
  this->x = a->x - b->x;
  this->y = a->y - b->y;
  this->z = a->z - b->z;
  this->w = a->w - b->w;
}

void    HPoint3::Copy(const HPoint3 *p)
{
  *this = *p;
}


void HPoint3::Point3ToHPoint3(const Point3 *src, HPoint3 *dst,
                                     int npoints)
{
  register int i;
  for (i = 0; i<npoints; ++i)   {
    *(Point3 *)&dst[i] = src[i];
    dst[i].w = 1.0;
  }
}

void HPoint3::toPoint3(const HPoint3 *src, Point3 *dst)
{
  if(src->w == 1.0 || src->w == 0.0) {
    *dst = *(Point3 *)src;
  } else {
    dst->x = src->x / src->w;
    dst->y = src->y / src->w;
    dst->z = src->z / src->w;
  }
}

void HPoint3::SubtractToPoint3(const HPoint3 *a, const HPoint3 *b,
                               Point3 *c)
{
  if(a->w == b->w) {
    c->x = a->x - b->x;
    c->y = a->y - b->y;
    c->z = a->z - b->z;
  } else if(a->w == 0) {
    *c = *(Point3 *)a;
    return;
  } else if(b->w == 0) {
    *c = *(Point3 *)b;
  } else {
    float s = b->w / a->w;
    c->x = a->x*s - b->x;
    c->y = a->y*s - b->y;
    c->z = a->z*s - b->z;
  }
  if(b->w != 1) {
    c->x /= b->w;
    c->y /= b->w;
    c->z /= b->w;
  }
}

HPoint3::Coord HPoint3::Distance(const HPoint3 *a)
{
  float dx, dy, dz;
  float w1w2 = this->w * a->w;

  if( w1w2 == 0. ) return 0.;

  dx = a->w * this->x - a->x * this->w;
  dy = a->w * this->y - a->y * this->w;
  dz = a->w * this->z - a->z * this->w;

  return (float)(sqrt( dx*dx + dy*dy + dz*dz )) / w1w2;
}

    
void HPoint3::Normalize()
{
  if (    (this->w == (HPoint3::Coord)0.0)
       || (this->w == (HPoint3::Coord)1.0) ) {
    return;
  }
  float inv = (float)(1.0/this->w);
  this->x *= inv;
  this->y *= inv;
  this->z *= inv;
  this->w = (HPoint3::Coord)1.0;
}



