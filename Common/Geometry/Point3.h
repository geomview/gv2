//-*-C++-*-
#ifndef POINT3_H
#define POINT3_H

class Point3 {
public:
    typedef float Coord;
    Coord x, y, z;

    char *ToString(char *buffer);

    // mbp-purify: added this function
    // Set all coords to 0 (not done automatically by the constructor)
    void Zero();

    Coord Dot(const Point3 *a);
    // Pt3Coord   Pt3Dot(const Point3 *a, const Point3 *b);

    void  Subtract(const Point3 *a, const Point3 *b);
    // void       Pt3Sub(const Point3 *a, const Point3 *b, Point3 *c);
    //                    (c = a - b)

    void  ScalarMultiply(Coord s, const Point3 *p);
    // void       Pt3Mul( double s, const Point3 *v1, Point3 *v2 )

    void  Copy(const Point3 *a);
    // void       Pt3Copy(const Point3 *a, Point3 *b);

    void  Unitize();
    // void       Pt3Unit(Point3 *a);

    void  Cross(const Point3 *a, const Point3 *b);
    // void       Pt3Cross(const Point3 *a, const Point3 *b, Point3 *c);

    Coord Length();
    // Pt3Coord   Pt3Length(const Point3 *p);

    Coord Distance(const Point3 *a);
    // Pt3Coord   Pt3Distance(const Point3 *a, const Point3 *b);

};

#endif //* POINT3_H
