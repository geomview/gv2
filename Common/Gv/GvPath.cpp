#include "GvPath.h"
#include "GeomWrapped.h"
#include "UtException.h"
#include "UtString.h"

TYPE_IMPLEMENT_TYPEINFO1(GvPath, RefObject);

GvPath::GvPath(GvUniverse *world, Geom *geom)
{
  mpWorld = ::NewRef(world);
  if (!FindAncestry(geom)) {
    throw new UtException(UtException::ERROR, 
			  "GvPath: cannot construct path; "
			  "the given geom (%x) does not appear "
			  "in the given world (%x)",
			  geom, mpWorld);
  }
}

int GvPath::FindAncestry(Geom *geom)
{
  UtLStack<Geom *>stack;

  (*(stack.Push())) = mpWorld->GetUniverseBase();
  if (FindStack(&stack, geom)) {
    mAncestryLength = stack.Depth();
    for (int i=mAncestryLength-1; i>=0; --i) {
      mAncestry[i] = *(stack.Top());
      stack.Pop();
    }
    return 1;
  } else {
    return 0;
  }
}

int GvPath::FindStack(UtLStack<Geom *> *stack, Geom *geom)
{
  Geom *g = *(stack->Top());
  if ( g == geom ) { return 1; }
  if (g->IsInstanceOf(TYPE_INFO(GeomParent))) {
    GeomParent *p = (GeomParent*)g;
    int nchildren = p->GetChildCount();
    for (int i=0; i<nchildren; ++i) {
      (*(stack->Push())) = p->GetChild(i);
      if (FindStack(stack, geom)) {
	return 1;
      }
      stack->Pop();
    }
  }
  return 0;
}


GvPath::~GvPath()
{
  if (mpWorld) ::DeleteRef(mpWorld);
}


Geom *GvPath::Resolve()
{
  return mAncestry[mAncestryLength-1];
}

Transform3  *GvPath::GetLocalTransform()
{
  if (mAncestryLength <= 1) { return &Transform3::IDENTITY; }
  Geom *parent = mAncestry[mAncestryLength-2];
  if (!parent->IsInstanceOf(TYPE_INFO(GeomWrapped))) {
    return NULL;
  }
  return ((GeomWrapped*)parent)->GetTransform();
}

void GvPath::GetCumulativeTransform(Transform3 *T)
{
  T->Identity();
  int i;
  for (i=0; i<mAncestryLength; ++i) {
    Geom *g = mAncestry[i];
    if (g->IsInstanceOf(TYPE_INFO(GeomWrapped))) {
      Transform3 *M = ((GeomWrapped*)g)->GetTransform();
      // Explanation of the order of multiplication: Our
      // transform libarary treats data points as row vectors;
      // transforms act on them by right multiplication, i.e.
      // [point] * [matrix] = [new point].  Transforms lower in
      // the heirarchy are closer to the data points (the one
      // just above the leaf node Geom being the one that acts
      // on it first), so the order in which the product of
      // transformations act on a point is:
      //  [point] * [transf n] * ... * [transf 1] * [transf 0]
      //   = [new point]
      // At this point, we've accumulated the product
      //  [transf i-1] ... [transf 0]
      // in T, and we're about to multiply it by [transf i]
      // (which is in M), so the order should be M * T.
      T->Concat(M, T);
    }
  }
}


void GvPath::GetChangeOfCoordsTransform(Transform3 *T,
                                        GvPath *that)
{
    // GetCumulativeTransform returns a transform that converts
    // from the end node's coordinate system to that of the path's
    // root. So, to return a path to convert from this path's
    // end node coord system to that of the root, we construct:
    //
    //   [transf which converts from this end to root]
    //      * [transf which converts from root to that end]
    // = [cumulative transf for this path]
    //      * [inverse of cumulative transf for that path]

    Transform3 thatT, thatTinverse;
    this->GetCumulativeTransform(T);
    that->GetCumulativeTransform(&thatT);
    thatTinverse.InverseOf(&thatT);
    T->Concat(T, &thatTinverse);
}

void GvPath::Dump()
{
  printf("GvPath (0x%x):\n", this);
  printf("             mpWorld = 0x%x\n", mpWorld);
  printf("mpWorld->BaseWrapped = 0x%x\n", mpWorld->GetUniverseBase());
  printf("     mAncestryLength = %1d\n", mAncestryLength);
  for (int i=0; i<mAncestryLength; ++i) {
    printf("       mAncestry[%2d] = 0x%x\n", i, mAncestry[i]);
  }
}
