//-*-C++-*-
#ifndef GVPATH_H
#define GVPATH_H

#include "Geom.h"
#include "UtLList.h"
#include "MgAppearance.h"
#include "UtScalarArray.h"
#include "TypeObject.h"

class GvPath : virtual public TypeObject
{
    TYPE_DECLARE_TYPEINFO(GvPath);

private:
    Geom                *mpRoot;
    UtScalarArray<int>   mIndices;
    unsigned int         mIndexCount;
    enum Level
    {
        BOTTOM = -1
    };

    static UtLList<GvPath *> sMasterList;

public:
    GvPath();
    GvPath(const GvPath &path);
    ~GvPath();

    GvPath &operator=(const GvPath &path);

    void          AppendIndex(int index);
    void          InsertIndex(int location, int index);
    void          RemoveLastIndex();
    void          ClearIndices();
    void          SetRoot(Geom *root);
    
    int GetLength(void) { return(mIndices.GetCount()); }

    // we should throw an exception when this fails.
    int operator[](unsigned int i) 
    { 
        if (i < mIndexCount) return(mIndices[i]); 
        else 
        {   
            throw(new UtException(UtException::ERROR, 
            "Bad Index in path [] operator\n")); return(-1); 
        } 
    }

    // This method promotes the last geom in the path to a GeomWrapped
    // if it is not already Wrapped by its immediate parent.  Then
    // it updates all of the other paths in the master list which
    // match.
    void PromoteBottomToWrapped(void);
    void UpdateMasterList(Geom *parent, int child, int newIndex)  ;

    // Return a pointer to the Geom at the given level in the path.
    // level = 0 means return the root of the path
    // level = n > 0 means return an nth-generation child of the root
    // level = GvPath::BOTTOM means go to whatever the max level in
    //   the path is.
    Geom *Resolve(int level = BOTTOM);

    // Return a pointer to the "local" transform for a particular level in
    // the path.  The "local" transform is the one in the GeomWrapped
    // that is immediately above the given level.  This doesn't make sense
    // if the parent of the given level is not a GeomWrapped; in that
    // case we return NULL.  It also doesn't make sense for the root level,
    // so if level=0 we also return NULL.
    //
    // The pointer that this function returns points to the internal
    // copy of the transform.  You can read it and modify it, but
    // don't free or delete it.
    Transform3 *GetLocalTransform(int level = BOTTOM);

    // Same idea, but for appearance rather than transform:
    MgAppearance *GetLocalAppearance(int level = BOTTOM);


    // Get the complete transformation for a particular level in the path,
    // relative to the root.  This is the product of all transformations
    // that occur in GeomWrapped objects along the path.  The
    // transformation is copied into the Transform3 pointed to by T,
    // overwriting anything that was there.
    //
    // For the root of the path (level=0), this function sets T to the
    // identity.  For level=n>0, it returns the product of the n
    // transforms at each level up to n (i.e. levels 0 through n-1).  For
    // each level that is not a GeomWrapped, we assume that the transform
    // is the identity
    void GetCumulativeTransform(Transform3 *T, int level = BOTTOM);


    // Get the transform which converts from the coordinate system of
    // this path to the coordinate system of another path.  The
    // transformation is copied into the Transform3 pointed to by T,
    // overwriting anything that was there. Thereafter,
    //   [this coords] * T = [that coords]
    // Note: in order for this to make sense, the root of each path
    // should be the same.  This function does not check to make sure
    // this is the case; if it is not the case, however, then the
    // transform it returns will probably be meaningless .
    void GetChangeOfCoordsTransform(Transform3 *T,
                                    int thisLevel,
                                    GvPath *that,
                                    int thatLevel);

    // Default-level version of the above. (We can't use default args
    // because the args that we want to "default" are not the last
    // ones.)
    void GetChangeOfCoordsTransform(Transform3 *T,
                                    GvPath *that)
    {
        GetChangeOfCoordsTransform(T,    BOTTOM,
                                   that, BOTTOM);
    }


    // for debugging only:
    //   (or maybe we'll need something like these to be public?)
    unsigned int GetIndexCount() { return mIndexCount; }
    UtScalarArray<int> *GetIndexArray() { return &mIndices; }
};

#endif // GVPATH_H
