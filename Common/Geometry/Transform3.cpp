#include <math.h>
#include <stdio.h>
#include <memory.h>  // for memcpy()
#include "Transform3.h"
#include "IoOoglParseException.h"
#include "UtString.h"

Transform3 Transform3::IDENTITY = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f 
};

int Transform3::Load(IoOoglLexer *lex)
{
  if (lex->LookAhead() == IoOoglLexer::STRING) {
    lex->Scan();
    if (!UtString::CaseInsensitiveStreq(lex->GetStringValue(), "transform")) {
      lex->UnScan();
      throw new IoOoglParseException(lex,
        "while reading transform: expected \"transform\" or number");
    }
  }

  int brace = 0;
  if (lex->LookAhead() == IoOoglLexer::LBRACE) {
    lex->Scan();
    brace = 1;
  }

  int ngot = lex->ExpectNum(16, D.m, IoOoglLexer::FLOAT);
  if (ngot < 16) {
    throw new IoOoglParseException(lex,
      "while reading transform: expected 16 numbers; got only %1d", ngot);
  }

  if (brace) {
    if (lex->LookAhead() == IoOoglLexer::RBRACE) {
      lex->Scan();
    } else {
      throw new IoOoglParseException(lex, "missing '}' at end of transform");
    }
  }

  return 1;
}

char *Transform3::ToLeakyString()
{
  char *buffer = new char[256];
  return ToString(buffer);
}


char *Transform3::ToString(char *buffer)
{
  sprintf(buffer, "%12.8f  %12.8f  %12.8f  %12.8f\n\
%12.8f  %12.8f  %12.8f  %12.8f\n\
%12.8f  %12.8f  %12.8f  %12.8f\n\
%12.8f  %12.8f  %12.8f  %12.8f\n",
          D.M[0][0], D.M[0][1], D.M[0][2], D.M[0][3],
          D.M[1][0], D.M[1][1], D.M[1][2], D.M[1][3],
          D.M[2][0], D.M[2][1], D.M[2][2], D.M[2][3],
          D.M[3][0], D.M[3][1], D.M[3][2], D.M[3][3]);
  return buffer;
}

void Transform3::Copy(const Transform3 *src)
{
  ::memcpy( (char *)this, (char *)src, sizeof(Transform3) );
}

void Transform3::Scale(float sx, float sy, float sz)
{
  Identity();
  CScale( sx, sy, sz );
}

void Transform3::CScale(float sx, float sy, float sz)
{
  register Transform3::Coord *aptr = D.M[0];

  // row 1
  *aptr++ *= sx;
  *aptr++ *= sx;
  *aptr++ *= sx;
  *aptr++ *= sx;

  // row 2
  *aptr++ *= sy;
  *aptr++ *= sy;
  *aptr++ *= sy;
  *aptr++ *= sy;

  // row 3
  *aptr++ *= sz;
  *aptr++ *= sz;
  *aptr++ *= sz;
  *aptr++ *= sz;

  // row 4 is unchanged
}

void Transform3::CAlignZ(const HPoint3 *axis)
{
  CAlign( axis, &(HPoint3::ZAXIS) );
}

void Transform3::CAlign(const HPoint3 *axis, const HPoint3 *newaxis)
{
  Transform3 T;
  T.Align( axis, newaxis );
  Concat(&T, this);
}

// this = Ta * Tb
void Transform3::Concat(const Transform3 *Ta, const Transform3 *Tb)
{
  register int i;
  
#define MAKEPRODUCT(T)                                  \
    for( i=0; i<4; i++ ) {                              \
        T[i][0] = Ta->D.M[i][0]*Tb->D.M[0][0] +         \
                  Ta->D.M[i][1]*Tb->D.M[1][0] +         \
                  Ta->D.M[i][2]*Tb->D.M[2][0] +         \
                  Ta->D.M[i][3]*Tb->D.M[3][0];          \
        T[i][1] = Ta->D.M[i][0]*Tb->D.M[0][1] +         \
                  Ta->D.M[i][1]*Tb->D.M[1][1] +         \
                  Ta->D.M[i][2]*Tb->D.M[2][1] +         \
                  Ta->D.M[i][3]*Tb->D.M[3][1];          \
        T[i][2] = Ta->D.M[i][0]*Tb->D.M[0][2] +         \
                  Ta->D.M[i][1]*Tb->D.M[1][2] +         \
                  Ta->D.M[i][2]*Tb->D.M[2][2] +         \
                  Ta->D.M[i][3]*Tb->D.M[3][2];          \
        T[i][3] = Ta->D.M[i][0]*Tb->D.M[0][3] +         \
                  Ta->D.M[i][1]*Tb->D.M[1][3] +         \
                  Ta->D.M[i][2]*Tb->D.M[2][3] +         \
                  Ta->D.M[i][3]*Tb->D.M[3][3];          \
      }

  if( Ta == this || Tb == this ) {
    Transform3 T;
    MAKEPRODUCT(T.D.M);
    memcpy( this, &T, sizeof(Transform3) );
  }
  else {
    MAKEPRODUCT(this->D.M);
  }

#undef MAKEPRODUCT
}


/*-----------------------------------------------------------------------
 * Function:    InverseOf
 * Description: compute the inverse of a Transform
 * Args:        T: the transform to compute inverse of
 *              (sets "this" to its inverse)
 * Returns:     nothing
 *              Actually, returns 1.  Need to fix this so that the return
 *                value is meaningful, like return 0 if the Transform
 *                is not invertible.  Or at least change the return type
 *                to void, if it turns out that it's best to not return
 *                a value at all.
 * Author:      mbp (original by njt, Sat Jul 18 12:04:19 CDT 1992)
 * Date:        Tue Jun 24 16:45:54 1997
 */
Transform3::Coord Transform3::InverseOf(const Transform3 *T)
{
  register int i, j, k;
  float x, f;
  Transform3 R;

  R.Copy(T);
  this->Identity();

  /* Components of unrolled inner loops: */
#define SUB(v,k)  v[j][k] -= f*v[i][k]
#define SWAP(v,k) x = v[i][k], v[i][k] = v[largest][k], v[largest][k] = x

  for (i = 0; i < 4; i++) {
    int largest = i;
    float largesq = R.D.M[i][i]*R.D.M[i][i];
    for (j = i+1; j < 4; j++)
      if ((x = R.D.M[j][i]*R.D.M[j][i]) > largesq)
        largest = j,  largesq = x;

    /* swap R.D.M[i][] with R.D.M[largest][] */
    SWAP(R.D.M,0);  SWAP(R.D.M,1);  SWAP(R.D.M,2);  SWAP(R.D.M,3);
    SWAP(this->D.M,0); SWAP(this->D.M,1); SWAP(this->D.M,2); SWAP(this->D.M,3);

    for (j = i+1; j < 4; j++) {
      f = R.D.M[j][i] / R.D.M[i][i];
      /* subtract f*R.D.M[i][] from R.D.M[j][] */
      SUB(R.D.M,0); SUB(R.D.M,1); SUB(R.D.M,2); SUB(R.D.M,3);
      SUB(this->D.M,0); SUB(this->D.M,1); SUB(this->D.M,2); SUB(this->D.M,3);
    }
  }
  for (i = 0; i < 4; i++) {
    f = R.D.M[i][i];
    for (k = 0; k < 4; k++) {
      R.D.M[i][k] /= f;
      this->D.M[i][k] /= f;
    }
  }
  for (i = 3; i >= 0; i--)
    for (j = i-1; j >= 0; j--) {
      f = R.D.M[j][i];
      SUB(R.D.M,0); SUB(R.D.M,1); SUB(R.D.M,2); SUB(R.D.M,3);
      SUB(this->D.M,0); SUB(this->D.M,1); SUB(this->D.M,2); SUB(this->D.M,3);
    }
                                
  return 1;

#undef  SUB
#undef  SWAP
}

void    Transform3::Rotate(float angle, const HPoint3 *axis)
{
  Point3 Vu;
  float sinA, cosA, versA;
        
  if(      axis == &HPoint3::XAXIS ) RotateX( angle );
  else if( axis == &HPoint3::YAXIS ) RotateY( angle );
  else if( axis == &HPoint3::ZAXIS ) RotateZ( angle );
  else {
    Vu.x = axis->x;
    Vu.y = axis->y;
    Vu.z = axis->z;
    Vu.Unitize();

    sinA = (float)sin(angle); 
    cosA = (float)cos(angle); 
    versA = 1 - cosA;

    this->Identity();
    this->D.M[0][0] = Vu.x*Vu.x*versA + cosA;
    this->D.M[1][0] = Vu.x*Vu.y*versA - Vu.z*sinA;
    this->D.M[2][0] = Vu.x*Vu.z*versA + Vu.y*sinA;

    this->D.M[0][1] = Vu.y*Vu.x*versA + Vu.z*sinA;
    this->D.M[1][1] = Vu.y*Vu.y*versA + cosA;
    this->D.M[2][1] = Vu.y*Vu.z*versA - Vu.x*sinA;

    this->D.M[0][2] = Vu.x*Vu.z*versA - Vu.y*sinA;
    this->D.M[1][2] = Vu.y*Vu.z*versA + Vu.x*sinA;
    this->D.M[2][2] = Vu.z*Vu.z*versA + cosA;
  }
}


/* 
 * Pre-multiply a matrix by a rotate about an arbitrary axis
 *
 * [this] = [ rotation] * [this]
 *             
 */
void    Transform3::CRotate(float angle, const HPoint3 *axis)
{
  if(      axis == &(HPoint3::XAXIS) ) CRotateX( angle );
  else if( axis == &(HPoint3::YAXIS) ) CRotateY( angle );
  else if( axis == &(HPoint3::ZAXIS) ) CRotateZ( angle );
  else {
    Transform3 Ta;
    Ta.Rotate(angle, axis);
    Concat(&Ta, this);
  }
}

/* 
 * Pre-multiply a matrix by a rotate about the x axis.
 *
 *       (  1  0  0  0 )      
 *       (  0  c  s  0 )      
 * [a] = (  0 -s  c  0 )  * [a]
 *       (  0  0  0  1 )      
 */
void    Transform3::CRotateX(float angle)
{
  register int i;
  double t,s,c;

  s=sin(angle);
  c=cos(angle);
  for (i=0; i<4; ++i) {
    t = this->D.M[1][i] * c + this->D.M[2][i] * s;
    this->D.M[2][i] = (float)(this->D.M[2][i] * c - this->D.M[1][i] * s);
    this->D.M[1][i] = (float)t;
  }
}

/* 
 * Pre-multiply a matrix by a rotate about the y axis.
 *
 *       (  c  0  s  0 )      
 *       (  0  1  0  0 )      
 * [a] = ( -s  0  c  0 ) * [a]
 *       (  0  0  0  1 )      
 */
void    Transform3::CRotateY(float angle)
{
  register int i;
  double t,s,c;

  s=sin(angle);
  c=cos(angle);
  for (i=0; i<4; ++i) {
    t = this->D.M[2][i] * c - this->D.M[0][i] * s;
    this->D.M[0][i] = (float)(this->D.M[0][i] * c + this->D.M[2][i] * s);
    this->D.M[2][i] = (float)t;
  }
}

/* 
 * Pre-multiply a matrix by a rotate about the z axis.
 *
 *       (  c  s  0  0 )      
 *       ( -s  c  0  0 )      
 * [a] = (  0  0  1  0 ) * [a]
 *       (  0  0  0  1 )      
 */
void    Transform3::CRotateZ(float angle)
{
  register int i;
  double t,s,c;

  s=sin(angle);
  c=cos(angle);
  for (i=0; i<4; ++i) {
    t = this->D.M[0][i] * c + this->D.M[1][i] * s;
    this->D.M[1][i] = (float)(this->D.M[1][i] * c - this->D.M[0][i] * s);
    this->D.M[0][i] = (float)t;
  }
}


void Transform3::RotateX( float angle )
{
  Identity();
  CRotateX(angle);
}

void Transform3::RotateY(float angle)
{
  Identity();
  CRotateY(angle);
}

void Transform3::RotateZ(float angle)
{
  Identity();
  CRotateZ(angle);
}

/*
 * Initialize a matrix to Identity
 *
 *       ( 1 0 0 0 )
 *       ( 0 1 0 0 )
 * [a] = ( 0 0 1 0 )
 *       ( 0 0 0 1 )
 */
void    Transform3::Identity()
  // void Tm3Identity( Transform3 T )
{
  Copy( &Transform3::IDENTITY );
}


void Transform3::TranslateOrigin(HPoint3 *pt)
  // void Tm3TranslateOrigin(Transform3 T, HPoint3 *pt)
{
  Identity();
  this->D.M[3][0] = pt->x / pt->w;
  this->D.M[3][1] = pt->y / pt->w;
  this->D.M[3][2] = pt->z / pt->w;
}

void    Transform3::Translate(Coord x, Coord y, Coord z)
{
  HPoint3 pt;
  pt.x = x;
  pt.y = y;
  pt.z = z;
  pt.w = 1;
  TranslateOrigin(&pt);
}


/*
 *     (  2*n/(r-l)      0             0          0 )
 *     (     0        2*n/(t-b)        0          0 )
 * T = ( (r+l)/(r-l) (t+b)/(t-b)  (f+n)/(n-f)    -1 )
 *     (     0           0        2*f*n/(n-f)     0 )
 *
 * Transform a row vector {xw,yw,zw,w} * T => {X,Y,Z,-z}
 * mapping the given viewing frustum into the cube -1 <= {X,Y,Z} <= 1,
 * with Z = -1 at near plane (z = -n), +1 at far plane (z = -f)
 * since the camera is looking in its -Z direction.
 * Here l and r are the x coordinates, and b and t the y coordinates,
 * of the edges of the viewing frustum at the near plane, z = -n.
 *
 * Note that n and f should be the positive distances to the near & far planes,
 * not the negative Z coordinates of those planes.
 */
void    Transform3::Perspective(float l, float r, float b,
                                float t, float n, float f)
{
  Identity();

  if( l == r ) {
    return;
  }
  if( b == t ) {
    return;
  }
  if( n == f ) {
    return;
  }

  D.M[0][0] = 2*n/(r-l);
  D.M[1][1] = 2*n/(t-b);
  D.M[2][2] = -(f+n)/(f-n);
  D.M[3][3] = 0.;
  D.M[2][3] = -1;
  D.M[2][0] = (r+l)/(r-l);
  D.M[2][1] = (t+b)/(t-b);
  D.M[3][2] = 2*n*f/(n-f);
}

/*
 *     (     2/(r-l)          0             0        0 )
 *     (        0          2/(t-b)          0        0 )
 * T = (        0             0         -2/(f-n)     0 )
 *     (  -(r+l)/(r-l)  -(t+b)/(t-b)  -(f+n)/(f-n)   1 )
 *
 * Transform to the unit cube! Also flips from rh to lh. 
 */
void Transform3::Orthographic(float l, float r, float b,
                              float t, float n, float f)
{
  Identity();

  if( l == r ) {
    fprintf( stderr, "Tm3Orthographic: l and r must be different.\n" );
    return;
  }
  if( b == t ) {
    fprintf( stderr, "Tm3Orthographic: b and t must be different.\n" );
    return;
  }
  if( n == f ) {
    fprintf( stderr, "Tm3Orthographic: n and f must be different.\n" );
    return;
  }

  D.M[0][0] =  2/(r-l);
  D.M[1][1] =  2/(t-b);
  D.M[2][2] = -2/(f-n);
  D.M[3][0] = -(r+l)/(r-l);
  D.M[3][1] = -(t+b)/(t-b);
  D.M[3][2] = -(f+n)/(f-n);
}

/*
 * Transform and project an HPoint3 onto a plain Point3.
 * Transforms pin . T -> pout,
 * then projects pout.{x,y,z} /= pout.w.
 * Returns pout.w.
 */
HPoint3::Coord Transform3::HPoint3TransformToPoint3(const HPoint3 *from,
                                                    Point3 *into)
{
  HPoint3 tp;
//  register HPoint3::Coord w;    // This variable is currently unreferenced
                                                                  // jcm - 10/14/97
  
  HPoint3Transform( from, &tp );
  if(tp.w != 1.0 && tp.w != 0.0) {
    into->x = tp.x / tp.w;
    into->y = tp.y / tp.w;
    into->z = tp.z / tp.w;
  } else {
    *into = *(Point3 *)&tp;
  }
  return tp.w;
}

// pt2 = pt1 * this
void Transform3::HPoint3Transform(const HPoint3 *p1, HPoint3 *p2)
{
    register float x = p1->x, y = p1->y, z = p1->z, w = p1->w;

    p2->x = x*D.M[0][0] + y*D.M[1][0] + z*D.M[2][0] + w*D.M[3][0];
    p2->y = x*D.M[0][1] + y*D.M[1][1] + z*D.M[2][1] + w*D.M[3][1];
    p2->z = x*D.M[0][2] + y*D.M[1][2] + z*D.M[2][2] + w*D.M[3][2];
    p2->w = x*D.M[0][3] + y*D.M[1][3] + z*D.M[2][3] + w*D.M[3][3];
}



void    Transform3::Align(const HPoint3 *axis, const HPoint3 *newaxis)
// void Tm3Align(Transform3 T, HPoint3 *axis, HPoint3 *newaxis)
{
  Transform3 Tr;
  Transform3 Tinv;
  HPoint3 o, zaxis, yaxis, newyaxis;
  HPoint3 my_axis, my_newaxis;
    
  o.x = o.y = o.z = 0.0f; o.w = 1.0f;

  my_newaxis.Copy(newaxis);
  ((Point3*)&zaxis)->Cross((Point3*)axis, (Point3*)&my_newaxis);
  ((Point3*)&yaxis)->Cross((Point3*)&zaxis, (Point3*)axis);
  ((Point3*)&newyaxis)->Cross((Point3*)&zaxis, (Point3*)&my_newaxis);

  my_axis.Copy(axis);
  ((Point3*)&my_axis)->Unitize();
  ((Point3*)&yaxis)->Unitize();
  ((Point3*)&zaxis)->Unitize();

  my_axis.w = yaxis.w = zaxis.w = 0.0f;
  Tetrad(&my_axis, &yaxis, &zaxis, &o );
  Tinv.InverseOf(this);

  ((Point3*)&my_newaxis)->Unitize();
  ((Point3*)&newyaxis)->Unitize();

  my_newaxis.w = newyaxis.w = zaxis.w = 0.0f;

  Tr.Tetrad( &my_newaxis, &newyaxis, &zaxis, &o );

  Tr.Concat(&Tinv, &Tr);
  Copy(&Tr);
}

/*-----------------------------------------------------------------------
 * Function:    Tm3Tetrad
 * Description: create a matrix with given vectors as rows
 * Args:        T: the created matrix (OUTPUT)
 *              x: row 1 (INPUT)
 *              y: row 2 (INPUT)
 *              z: row 3 (INPUT)
 *              w: row 4 (INPUT)
 * Returns:     nothing
 * Author:      hanrahan, mbp
 * Date:        Thu Aug  8 13:06:48 1991
 * Notes:       
 */
void Transform3::Tetrad( HPoint3 *x, HPoint3 *y, HPoint3 *z, HPoint3 *w )
{
  D.M[0][0] = x->x;
  D.M[0][1] = x->y;
  D.M[0][2] = x->z;
  D.M[0][3] = x->w;

  D.M[1][0] = y->x;
  D.M[1][1] = y->y;
  D.M[1][2] = y->z;
  D.M[1][3] = y->w;

  D.M[2][0] = z->x;
  D.M[2][1] = z->y;
  D.M[2][2] = z->z;
  D.M[2][3] = z->w;

  D.M[3][0] = w->x;
  D.M[3][1] = w->y;
  D.M[3][2] = w->z;
  D.M[3][3] = w->w;
}
