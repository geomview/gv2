#include "GvPath.h"
#include "GeomWrapped.h"
#include "UtException.h"
#include "UtString.h"

UtLList<GvPath *> GvPath::sMasterList;


TYPE_IMPLEMENT_TYPEINFO(GvPath);

GvPath::GvPath()
{
    mpRoot = NULL;
    mIndexCount = 0;

    sMasterList.AppendItem(this);
}

GvPath::GvPath(const GvPath &path)
{
    mpRoot = path.mpRoot;
    mIndexCount = path.mIndexCount;
    mIndices = path.mIndices;

    sMasterList.AppendItem(this);
}

GvPath::~GvPath()
{
    sMasterList.RemoveItemByContents(this);
    if (mpRoot) ::DeleteRef(mpRoot);
}

GvPath &GvPath::operator=(const GvPath &path)
{
    mpRoot = path.mpRoot;
    mIndexCount = path.mIndexCount;
    mIndices = path.mIndices;

    return(*this);
}

void GvPath::SetRoot(Geom *root)
{
    if (mpRoot) ::DeleteRef(mpRoot);
    mpRoot = ::NewRef(root);
}

void GvPath::PromoteBottomToWrapped(void)
{
    Geom *parentGeom = Resolve(mIndexCount - 1);
	if (!parentGeom->IsInstanceOf(TYPE_INFO(GeomParent))) {
			throw new UtException(UtException::ERROR,
					"GvPath::PromoteBottomToWrapped: parent is not a GeomParent");
	}
	GeomParent *parent = (GeomParent*)parentGeom;
    Geom *tail = parent->GetChild(mIndices[mIndexCount-1]);

    if ( parent->IsInstanceOf(TYPE_INFO(GeomWrapped)) || 
         tail->IsInstanceOf(TYPE_INFO(GeomWrapped)) )
        return;

    GeomWrapped *newGeom = new GeomWrapped(tail);

	parent->RemoveChild(mIndices[mIndexCount-1]);
	parent->AddChild(newGeom);
    UpdateMasterList(parent, mIndices[mIndexCount-1], 0);
}


void GvPath::UpdateMasterList(Geom *parent, int child, int newIndex)  
{
    for (UtLListIter<GvPath *> it(sMasterList); it; ++it)
    {
        GvPath **path = it();

        int end = (*path)->GetLength();
        for (int i = 0; i < end; i++)
        {
            Geom *geom = (*path)->Resolve(i);
            
            if (geom == parent)
                (*path)->InsertIndex(i, newIndex);
        }
    }
}
                                  
Geom *GvPath::Resolve(int level)
{
    // Note: the number of indices we'll use from the mIndex array is
    // "level"; these are indices [0] ... [level-1].

    // (a) If level=0, return the root (use no indices)
    if (level==0) return mpRoot;

    // (b) if asked for more levels than we have, return NULL.
    //     level-1 is the highest index we'll use, and mIndexCount-1
    //     is the highest that exists, so we want to make sure that
    //     level-1 <= mIndexCount-1, i.e. level <= mIndexCount.  Note
    //     that this takes care of the case mIndexCount=0, since at
    //     this point we know that level>0.
    if (level > (int)mIndexCount) return NULL;
        // Note: the (int) cast above is to avoid a compiler
        // warning about comparing int to unsigned int.  Need
        // to fix this soon by being more consistent about
        // where we use unsigned vs int.  mbp 11/12/97.

    // (c) if level comes in equal to BOTTOM, it means go all the way,
    //     i.e. level = mIndexCount.
    if (level == BOTTOM) level = mIndexCount;

    // Loop throught the levels
    Geom *g = mpRoot;
    int i;
    for (i=0; i < level; ++i)
    {
        g = g->GetChild(mIndices[i]);
        if (g == NULL)
        {
            UtString s("child not found at index %1d in GvPath::Resolve()",
                       mIndices[i]);
            throw(new UtException(UtException::ERROR,
                                  s.StealBuf(),
                                  UtException::DYNAMIC));
        }
    }

    return g;
}


Transform3  *GvPath::GetLocalTransform(int level)
{
    if (level == BOTTOM) level = mIndexCount;

    // Rule out the root level
    if (level == 0) return NULL;

    // Now subtract 1 from level, so "level" now refers to the parent
    --level;

    // Get a pointer to the parent
    Geom *g = Resolve(level);
    if (g == NULL)
    {
        UtString
          s("GvPath::GetLocalTransform() can't find parent at level %1d",
            level);
        throw new UtException(UtException::ERROR,
                              s.StealBuf(),
                              UtException::DYNAMIC);
    }

    // Make sure it's a GeomWrapped
    if (!g->IsInstanceOf(TYPE_INFO(GeomWrapped))) return NULL;
    GeomWrapped *gWrapped = (GeomWrapped*)g;

    // Now we look up the transform in the GeomWrapped.  This
    // will be the mIndices[level]'th transform.  Make sure
    // it exists first.
    if (mIndices[level] >= (int)(gWrapped->GetChildCount()))
    {
        UtString
          s("GvPath::GetLocalTransform(): transform not found in parent \
GeomWrapped.  Requested transform # %1d, but only %1d exist.",
            mIndices[level], gWrapped->GetChildCount());
        throw new UtException(UtException::ERROR,
                              s.StealBuf(),
                              UtException::DYNAMIC);
    }

    // And finally, return it
    return gWrapped->GetTransform( mIndices[level] );
}

MgAppearance  *GvPath::GetLocalAppearance(int level)
{
        return NULL;
#if 0
    if (level == BOTTOM) level = mIndexCount;

    // Rule out the root level
    if (level == 0) return NULL;

    // Now subtract 1 from level, so "level" now refers to the parent
    --level;

    // Get a pointer to the parent
    Geom *g = Resolve(level);
    if (g == NULL)
    {
        throw new UtException(UtException::ERROR,
         "GvPath::GetLocalAppearance() can't find parent at level %1d",
                              level);
    }

    // Make sure it's a GeomWrapped
    if (!g->IsInstanceOf(TYPE_INFO(GeomWrapped))) return NULL;
    GeomWrapped *gWrapped = (GeomWrapped*)g;

    // Now we look up the appearance in the GeomWrapped.  This
    // will be the mIndices[level]'th appearance, unless there
    // aren't that many in the list, in which case it's the last
    // one in the list.
    if (mIndices[level] >= (int)(gWrapped->GetChildCount()))
    {
        UtString
          s("GvPath::GetLocalTransform(): transform not found in parent \
GeomWrapped.  Requested transform # %1d, but only %1d exist.",
            mIndices[level], gWrapped->GetChildCount());
        throw new UtException(UtException::ERROR,
                              s.StealBuf(),
                              UtException::DYNAMIC);
    }

    // And finally, return it
    return gWrapped->GetTransform( mIndices[level] );
#endif
}

void GvPath::GetCumulativeTransform(Transform3 *T, int level)
{
    if (level == BOTTOM) level = mIndexCount;

    if (level > (int)mIndexCount)
    {
        UtString
          s("GvPath::GetCumulativeTransform() can't compute path to level %1d;\
 (only %1d levels exist)", level, mIndexCount);
        throw new UtException(UtException::ERROR,
                              s.StealBuf(),
                              UtException::DYNAMIC);
    }

    T->Identity();
    Geom *g = mpRoot;
    for (int i=0; i<level; ++i) {
        if (g == NULL)
        {
            UtString
                s("GvPath::GetCumulativeTransform() encountered NULL geom at \
level index %1d (while trying to go to level index %1d)", i, level-1);
            throw new UtException(UtException::ERROR,
                                  s.StealBuf(),
                                  UtException::DYNAMIC);
        }
        if (g->IsInstanceOf(TYPE_INFO(GeomWrapped)))
        {
            GeomWrapped *gWrapped = (GeomWrapped*)g;
            Transform3 *M = gWrapped->GetTransform( mIndices[i] );
            if (M == NULL)
            {
                UtString
                    s("GvPath::GetCumulativeTransform() encountered NULL \
Transform pointer (for index %1d) in GeomWrapped at level index %1d",
                      mIndices[i], i);
                throw new UtException(UtException::ERROR,
                                      s.StealBuf(),
                                      UtException::DYNAMIC);
            }
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
        if (i < level - 1) {
            g = g->GetChild(mIndices[i]);
        }
    }
}

void GvPath::AppendIndex(int index)
{
    mIndices[mIndexCount++] = index;
}

void GvPath::InsertIndex(int location, int index)
{
    mIndices.InsertItem(location, index);
    mIndexCount++;
}

void GvPath::RemoveLastIndex()
{
    if (mIndexCount > 0) --mIndexCount;
}

void GvPath::ClearIndices()
{
    mIndices.Clear();
    mIndexCount = 0;
}

void GvPath::GetChangeOfCoordsTransform(Transform3 *T,
                                        int thisLevel,
                                        GvPath *that,
                                        int thatLevel)
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
    this->GetCumulativeTransform(T, thisLevel);
    that->GetCumulativeTransform(&thatT, thatLevel);
    thatTinverse.InverseOf(&thatT);
    T->Concat(T, &thatTinverse);
}
