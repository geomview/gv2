#include <stdio.h>
#include <math.h>
#include "Point3.h"

char *Point3::ToString(char *buffer)
{
  sprintf(buffer, "(%9.5f, %9.5f, %9.5f)", x, y, z);
  return buffer;
}

// mbp-purify: added this function
void Point3::Zero()
{
    this->x = this->y = this->z = 0.0f;
}

Point3::Coord   Point3::Dot(const Point3 *a)
{
  return this->x*a->x
       + this->y*a->y
       + this->z*a->z;
}

/* v3 = v1 - v2 */
void    Point3::Subtract(const Point3 *a, const Point3 *b)
{
  this->x = a->x - b->x;
  this->y = a->y - b->y;
  this->z = a->z - b->z;
}

void    Point3::Copy(const Point3 *a)
{
  this->x = a->x;
  this->y = a->y;
  this->z = a->z;
}

void    Point3::ScalarMultiply(Point3::Coord s, const Point3 *p)
{
  this->x = s * p->x;
  this->y = s * p->y;
  this->z = s * p->z;
}

void    Point3::Unitize()
{
  Point3::Coord len = Length();
  if( len != 0. && len != 1. )
    ScalarMultiply( (float)(1.0/len), this );
}



void    Point3::Cross(const Point3 *a, const Point3 *b)
{
  this->x = a->y*b->z-a->z*b->y; 
  this->y = a->z*b->x-a->x*b->z; 
  this->z = a->x*b->y-a->y*b->x;
}

Point3::Coord   Point3::Length()
{
  return (float)sqrt(  this->x*this->x
              + this->y*this->y
              + this->z*this->z );
}

Point3::Coord   Point3::Distance(const Point3 *a)
{
  Point3 diff;

  diff.Subtract(this, a);
  return diff.Length();
}
