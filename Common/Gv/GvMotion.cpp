#include <typeinfo>
#include "GvMotion.h"
#include "GeomWrapped.h"
#include "UtException.h"
#include "Geometry.h"

TYPE_IMPLEMENT_TYPEINFO1(GvMotion, GvAction);

GvMotion::GvMotion(MotionType   type,
		   GvPath      *moving,
		   GvPath      *center,
		   GvPath      *frame,
		   unsigned int t0)
{
  mMotionType = type;
  mpMoving    = ::NewRef(moving);
  mpCenter    = ::NewRef(center);
  mpFrame     = ::NewRef(frame);
  mT0         = t0;
}

GvMotion::~GvMotion()
{
  ::DeleteRef(mpMoving);
  ::DeleteRef(mpCenter);
  ::DeleteRef(mpFrame);
}

#define PRINTTRANSFORM( T ) printf("%s =\n%s\n", #T, T.ToString(buffer))

void GvMotion::Execute(unsigned int t)
{
  char buffer[1024];
  //printf("GvMotion::Execute------- this=0x%x ---------\n", this);

  Transform3 Vfp, Tm, Tminv, Tc, Tcinv, Tf, Tfinv, Pf, Pfinv, A;

  ComputeLocalTransform(&Vfp, t);

  mpMoving->GetCumulativeTransform(&Tm);
  mpCenter->GetCumulativeTransform(&Tc);
  mpFrame->GetCumulativeTransform(&Tf);

  Tminv.InverseOf(&Tm);
  Tcinv.InverseOf(&Tc);
  Tfinv.InverseOf(&Tf);

  //
  // This could be significantly optimized later.
  //

  HPoint3 p0;
  Tc.HPoint3Transform(&HPoint3::ORIGIN, &p0);   // p0 = p * Tc
  HPoint3 pf;
  Tfinv.HPoint3Transform(&p0, &pf);             // pf = p0 * Tfinv
  Pf.TranslateOrigin(&pf);
  Pfinv.InverseOf(&Pf);

  A.Copy(&Tm);		// A = Tm
//printf("Tm = %s", A.ToString(buffer));
  A.Concat(&A, &Tfinv);	// A = Tm * Tfinv
//printf("Tm * Tfinv = %s", A.ToString(buffer));
  A.Concat(&A, &Pfinv);	// A = Tm * Tfinv * Pfinv
//printf("Tm * Tfinv * Pinv = %s", A.ToString(buffer));
  A.Concat(&A, &Vfp);	// A = Tm * Tfinv * Pfinv * Vfp
//printf("Tm * Tfinv * Pinv * Vfp = %s", A.ToString(buffer));
  A.Concat(&A, &Pf);	// A = Tm * Tfinv * Pfinv * Vfp * Pf
//printf("Tm * Tfinv * Pinv * Vfp * Pf = %s", A.ToString(buffer));
  A.Concat(&A, &Tf);	// A = Tm * Tfinv * Pfinv * Vfp * Pf * Tf
//printf("Tm * Tfinv * Pinv * Vfp * Pf * Tf = %s", A.ToString(buffer));
  A.Concat(&A, &Tminv);	// A = Tm * Tfinv * Pfinv * Vfp * Pf * Tf * Tminv
//printf("Tm * Tfinv * Pinv * Vfp * Pf * Tf * Tminv = %s", A.ToString(buffer));


  Transform3 *movingLocal = mpMoving->GetLocalTransform();
  if (movingLocal == NULL) {
    throw new
      UtException(UtException::ERROR,
		  "GvMotion::Execute: can't find local "
		  "transform of moving object");
  }

//  PRINTTRANSFORM(Vfp);
//  PRINTTRANSFORM(Tm);
//  PRINTTRANSFORM(Tminv);
//  PRINTTRANSFORM(Tc);
//  PRINTTRANSFORM(Tcinv);
//  PRINTTRANSFORM(Tf);
//  PRINTTRANSFORM(Tfinv);
//  PRINTTRANSFORM(Pf);
//  PRINTTRANSFORM(Pfinv);
//  PRINTTRANSFORM(A);
//  PRINTTRANSFORM((*movingLocal));
//  printf("appying A now\n");

  movingLocal->Concat(&A, movingLocal);

//  PRINTTRANSFORM((*movingLocal));

}

UtBool GvMotion::IsFinished()
{
    switch (mMotionType) {
    case ONESHOT: return UtTRUE;
    default:
    case INERTIAL: return UtFALSE;
    }
}

UtBool GvMotion::IsFragile()
{
    switch (mMotionType) {
    case ONESHOT: return UtFALSE;
    default:
    case INERTIAL: return UtTRUE;
    }
}

UtBool GvMotion::IsLike(GvAction *action)
{
  // if 'action' is not a GvMotion, then we can't be like it
  if (!action->IsInstanceOf(TYPE_INFO(GvMotion))) {
    return UtFALSE;
  }


  // For now, any two motions are like if they have the same 'moving'
  // object.  (We check for equality of the actual moving Geom, rather
  // than just comparing the two mpMoving GvPath pointers.)
  Geom *thisMovingGeom = mpMoving->Resolve();
  Geom *thatMovingGeom = ((GvMotion*)action)->mpMoving->Resolve();
  return (thisMovingGeom == thatMovingGeom);
}

