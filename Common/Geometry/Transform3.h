//-*-C++-*-
#ifndef TRANSFORM3_H
#define TRANSFORM3_H

#include "Point3.h"
#include "HPoint3.h"
#include "IoOoglLexer.h"

class Transform3 {
public:
  typedef float Coord;
  union {
    Coord M[4][4];
    Coord m[16];
  } D;

  int Load(IoOoglLexer *lex);

  //done
  char  *ToString(char *buffer);
  // char *     Tm3ToString(Transform3 T);

  char  *ToLeakyString();

  //done
  void  Copy(const Transform3 *src);
  // void       Tm3Copy(Transform3 Tsrc, Transform3 Tdst);


  //done
  void  Scale(float sx, float sy, float sz);
  // void       Tm3Scale(Transform3 T, float sx, float sy, float sz);

  void  CScale(float sx, float sy, float sz);
  // void       Ctm3Scale(Transform3 T, float sx, float sy, float sz);


  void  Align(const HPoint3 *axis, const HPoint3 *newaxis);
  // void       Tm3Align(Transform3 T, HPoint3 *axis, HPoint3 *newaxis)

  void  CAlign(const HPoint3 *axis, const HPoint3 *newaxis);
  // void       Ctm3Align(Transform3 T, HPoint3 *axis, HPoint3 *newaxis);

  void  CAlignZ(const HPoint3 *axis);
  // void       Ctm3AlignZ(Transform3 T, HPoint3 *axis);

  void Tetrad( HPoint3 *x, HPoint3 *y, HPoint3 *z, HPoint3 *w );
  // void        Tm3Tetrad(Transform3 T,
  //                       HPoint3 *x, HPoint3 *y, HPoint3 *z, HPoint3 *w)

  void  Concat(const Transform3 *Ta, const Transform3 *Tb); // this = Ta * Tb
  // void       Tm3Concat(Transform3 Ta, Transform3 Tb, Transform3 Tc);
                // Tc = Ta * Tb

  Coord InverseOf(const Transform3 *T);
  // float      Tm3Invert(Transform3 T, Transform3 Tinv);

  void  Rotate(float angle, const HPoint3 *axis);
  // void       Tm3Rotate(Transform3 T, float angle, HPoint3 *axis);

  void  CRotate(float angle, const HPoint3 *axis);
  // void       Ctm3Rotate(Transform3 T, float angle, HPoint3 *axis);

  void  CRotateX(float angle);
  // void       Ctm3RotateX(Transform3 T, float angle);
  void  RotateX(float angle);

  void  CRotateY(float angle);
  // void       Ctm3RotateY(Transform3 T, float angle);
  void  RotateY(float angle);

  void  CRotateZ(float angle);
  // void       Ctm3RotateZ(Transform3 T, float angle);
  void  RotateZ(float angle);


  void  Identity();
  // void       Tm3Identity(Transform3 T);

  void TranslateOrigin(HPoint3 *pt);
  // void Tm3TranslateOrigin(Transform3 T, HPoint3 *pt)

  void  Translate(Coord x, Coord y, Coord z);
  // void       Tm3Translate(Transform3 T,
  //                         Tm3Coord tx, Tm3Coord ty, Tm3Coord tz);

  void  Perspective(float l, float r, float b,
                    float t, float n, float f);
  // void       Tm3Perspective(Transform3 T,
  //                           float l, float r, float b,
  //                           float t, float n, float f);

  void  Orthographic(float l, float r, float b,
                     float t, float n, float f);
  // void       Tm3Orthographic(Transform3 T,
  //                            float l, float r, float b,
  //                            float t, float n, float f);

  HPoint3::Coord HPoint3TransformToPoint3(const HPoint3 *from, Point3 *into);
  // HPt3Coord HPt3TransPt3(Transform3 T, HPoint3 *from, Point3 *into);

  void HPoint3Transform(const HPoint3 *p1, HPoint3 *p2); // pt2 = pt1 * this
  // void        HPt3Transform(Transform3 T, HPoint3 *pt1, HPoint3 *pt2);

  static Transform3 IDENTITY;

};


#endif // TRANSFORM3_H
