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
//char buffer[1024];
//printf("GvMotion::Execute--------------------------------------\n");

  Transform3 Vfp;
  ComputeLocalTransform(&Vfp, t);
//PRINTTRANSFORM(Vfp);

  Transform3 Tm, Tc, Tf;
  mpMoving->GetCumulativeTransform(&Tm);
  mpCenter->GetCumulativeTransform(&Tc);
  mpFrame->GetCumulativeTransform(&Tf);
//PRINTTRANSFORM(Tm);
//PRINTTRANSFORM(Tc);
//PRINTTRANSFORM(Tf);


  //
  // This could be significantly optimized later.
  //

  Transform3 Tfinv;
  Tfinv.InverseOf(&Tf);
//PRINTTRANSFORM(Tfinv);
  HPoint3 p0;
  Tc.HPoint3Transform(&HPoint3::ORIGIN, &p0);   // p0 = p * Tc
  HPoint3 pf;
  Tfinv.HPoint3Transform(&p0, &pf);             // pf = p0 * Tfinv
  Transform3 Pf;
  Pf.TranslateOrigin(&pf);
//PRINTTRANSFORM(Pf);
  Transform3 Pfinv;
  Pfinv.InverseOf(&Pf);
//PRINTTRANSFORM(Pfinv);
  Transform3 Tminv;
  Tminv.InverseOf(&Tm);
//PRINTTRANSFORM(Tminv);

  Transform3 A;
  A.Copy(&Tm);		// A = Tm
  A.Concat(&A, &Tfinv);	// A = Tm * Tfinv
  A.Concat(&A, &Pfinv);	// A = Tm * Tfinv * Pfinv
  A.Concat(&A, &Vfp);	// A = Tm * Tfinv * Pfinv * Vfp
  A.Concat(&A, &Pf);	// A = Tm * Tfinv * Pfinv * Vfp * Pf
  A.Concat(&A, &Tf);	// A = Tm * Tfinv * Pfinv * Vfp * Pf * Tf
  A.Concat(&A, &Tminv);	// A = Tm * Tfinv * Pfinv * Vfp * Pf * Tf * Tminv

//PRINTTRANSFORM(A);

  Transform3 *movingLocal = mpMoving->GetLocalTransform();
  if (movingLocal == NULL) {
    throw new
      UtException(UtException::ERROR,
		  "GvMotion::Execute: can't find local "
		  "transform of moving object");
  }
//PRINTTRANSFORM((*movingLocal));
//printf("appying A now\n");
  movingLocal->Concat(movingLocal, &A);
//PRINTTRANSFORM((*movingLocal));
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

