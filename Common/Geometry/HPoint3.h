//-*-C++-*-
#ifndef HPOINT3_H
#define HPOINT3_H

#include "Point3.h"

class HPoint3 {
public:
    typedef float Coord;
    Coord x, y, z, w;

    char *ToString(char *buffer);

    void        Subtract(const HPoint3 *a, const HPoint3 *b);
    // void HPt3Sub( HPoint3 *a, HPoint3 *b, HPoint3 *aminusb  );

    void        Copy(const HPoint3 *p);
    // void HPt3Copy( HPoint3 *pt1, HPoint3 *pt2 );

    Coord Distance(const HPoint3 *a);
    // HPt3Coord HPt3Distance( HPoint3 *a, HPoint3 *b );

    void        Normalize();
    // void HPt3Normalize( HPoint3 *pt1, HPoint3 *pt2 );
    //    (pt2 = pt1 normalized)



    static void Point3ToHPoint3(const Point3 *src, HPoint3 *dst, int npoints);
    // void Pt3ToPt4( Point3 *src, HPoint3 *dst, int npoints  );

    static void toPoint3(const HPoint3 *src, Point3 *dst);
    // void HPt3ToPt3( HPoint3 *src, Point3 *dst );

    static void SubtractToPoint3(const HPoint3 *a, const HPoint3 *b,
                               Point3 *c);  // (c = a - b)
    //   (This is equivalent to (but faster than) normalizing a and b
    //    to Point3 and subtracting them.)
    // void HPt3SubPt3(register HPoint3 *p1, register HPoint3 *p2,
    //               register Point3 *v);
    //          (v = p1 - p2)



    static HPoint3 XAXIS;
    // HPoint3    TM3_XAXIS;
    static HPoint3 YAXIS;
    // HPoint3    TM3_YAXIS;
    static HPoint3 ZAXIS;
    // HPoint3    TM3_ZAXIS;

    static HPoint3 ORIGIN;


};

#endif // HPOINT3_H
