//-*-C++-*-
#ifndef GVPATH_H
#define GVPATH_H

#include "Geom.h"
#include "GvUniverse.h"
#include "UtScalarArray.h"
#include "TypeObject.h"
#include "UtLStack.h"

class GvPath : virtual public RefObject
{
  TYPE_DECLARE_TYPEINFO(GvPath);

private:

  // pointer to GvUniverse of this path
  GvUniverse               *mpWorld; 
				
  // Array of pointers to the geoms in this path. mAncestry[0] is the
  // root note (world's mpUniverseBase), and
  // mAncestry[mAncestryLength-1] is a pointer to the geom itself
  UtScalarArray<Geom *>  mAncestry;

  // Length of mAncestry --- i.e. number of entries used.  The
  // entries are mAncestry[0] through mAncestry[mAncestryLength-1].
  int                    mAncestryLength;

public:
  GvPath(GvUniverse *world, Geom *g);
  ~GvPath();

  Geom *operator[](unsigned int i) 
  { 
    if (i < mAncestryLength) {
      return(mAncestry[i]); 
    } else {
      throw(new UtException(UtException::ERROR, 
	    "Bad index (%1d) in path [] operator\n", i));
    } 
  }

  // Return a pointer to the Geom at the end of the path.
  Geom *Resolve();

  // Return a pointer to the "local" transform for the geom at the end
  // of this path.  This is the one in the GeomWrapped that is
  // immediately above the end of the path.  This doesn't make sense
  // if the penultimate geom in the ancestry
  // (i.e. mAncestry[mAncestryLength-2]) is not a GeomWrapped; in that
  // case we return NULL.
  //
  // The pointer that this function returns points to the internal
  // copy of the transform.  You can read it and modify it, but
  // don't free or delete it.
  Transform3 *GetLocalTransform();


  // Get the complete transformation for a the path, starting with
  // the root (world's mpUniverseBase) and going down to the end
  // of the path.  This is the product of all transformations
  // that occur in GeomWrapped objects along the path.  The
  // transformation is copied into the Transform3 pointed to by T,
  // overwriting anything that was there.
  void GetCumulativeTransform(Transform3 *T);


  // Get the transform which converts from the coordinate system of
  // this path to the coordinate system of another path.  The
  // transformation is copied into the Transform3 pointed to by T,
  // overwriting anything that was there. Thereafter,
  //   [this coords] * T = [that coords]
  // Note: in order for this to make sense, both paths should be in
  // the same world.  This function does not check to make sure this
  // is the case; if it is not the case, however, then the transform
  // it returns will probably be meaningless .
  void GetChangeOfCoordsTransform(Transform3 *T,
				  GvPath *that);

  void Dump();

private:
  int FindAncestry( Geom *g );
  int FindStack(UtLStack<Geom *>*stack, Geom *geom);
};

#endif // GVPATH_H
