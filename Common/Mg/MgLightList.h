//-*-C++-*-
#ifndef MGLIGHTLIST_H
#define MGLIGHTLIST_H

#include "UtException.h"

class MgLightList {
public:
    // Constructors:
    MgLightList() { mCount = 0; }
    ~MgLightList();
    MgLightList(const MgLightList &list);             // copy constructor
    MgLightList & operator= (const MgLightList &src); // assigment operator

    // Add (a reference to) a light to the list:
    void AddLight(class MgLight *light);

    // Remove (a reference to) a light from the list.  Returns 1
    // if the light was actually found in the list (and removed);
    // returns 0 otherwise.
    int RemoveLight(class MgLight *light);

    // Add (references to) all the lights in an existing lights list
    // to this list.
    void AddAllLightsFrom(const class MgLightList *list);

    // Remove all lights from the list:
    void Clear();

    // Maximum number of lights allowed in a list
    enum { MAXLIGHTS = 8 };

private:
    class MgLight *mLights[MgLightList::MAXLIGHTS];
    int mCount;

    friend class MgLightListIter;
};

class MgLightListIter {
private:
    MgLightList *mpList;
    int mCurrent;
public:
    MgLightListIter(MgLightList &list) {
        mpList = &list;
        Reset();
    }
    ~MgLightListIter() {}

    // RESET TO BEGINNING OF LIST
    void Reset() {
        if (mpList->mCount > 0) mCurrent = 0;
        else mCurrent = -1;
    }

    // VALID CURRENT LIGHT TEST:
    // "cast to int" operator; used for testing whether we really
    // have a current light in the list. (i.e. is it OK to call the "cast
    // to MgLight" operator). Should return non-0 if there are more
    // lights, 0 if not.
    operator int () {
        return ( (mCurrent >=0) && (mCurrent < mpList->mCount) );
    }

    // GET CURRENT LIGHT:
    // "cast to MgLight *" operator; returns the current light.  This should
    // only be called after a non-NULL return from the "cast to void *"
    // operator above.
    class MgLight * operator()() {
        if ( (mCurrent < 0) || (mCurrent >= mpList->mCount) )
        {
            throw new UtException(UtException::ERROR,
                    "MgLightListIter has no current value (index %1d)",
                              mCurrent);
        }
        return mpList->mLights[mCurrent];
    }

    // ADVANCE TO NEXT LIGHT:
    // pre-increment operator; advances to the next light in the list
    class MgLight * operator ++ () {
        ++mCurrent;
        return (class MgLight*)this;
    }
};

#endif // MGLIGHTLIST_H
