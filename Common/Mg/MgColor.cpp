#include "MgColor.h"

#define MAX(a,b) (a)>(b)?(a):(b)

double MgColor::Normalize()
{
  double coeff = MAX(mR, mG);
  coeff = MAX(mB, coeff);

  if( coeff != 0.0 ) {
    mR /= (float)coeff;
    mG /= (float)coeff;
    mB /= (float)coeff;
  }
  return coeff;
}
