#include "MgLightList.h"
#include "MgLight.h" // needed so we can call ::NewRef/::DeleteRef
                     // on lights

MgLightList::~MgLightList()
{
    Clear();
}

MgLightList & MgLightList::operator= (const MgLightList &src)
{
    int i;
    for (i=0; i<src.mCount; ++i) {
        mLights[i] = ::NewRef(src.mLights[i]);
    }
    mCount = src.mCount;
    return (*this);
}

MgLightList::MgLightList(const MgLightList &list)
{
    *this = list;     // (calls operator= above)
}


void MgLightList::AddLight(MgLight *light)
{
    if (mCount >= MgLightList::MAXLIGHTS)
    {
        throw new UtException(UtException::WARNING,
             "MgLightList::AddLight: can't have more than %1d lights",
                          MgLightList::MAXLIGHTS);
    }
    mLights[mCount++] = ::NewRef(light);
}

void MgLightList::AddAllLightsFrom(const MgLightList *list)
{
    int i;
    for (i=0; i<list->mCount; ++i) AddLight(list->mLights[i]);
}


int MgLightList::RemoveLight(MgLight *light)
{
    int i;
    int found = 0;
    for (i=0; i<mCount; ++i)
    {
        if (!found)
        {
            if (mLights[i] == light)
            {
                ::DeleteRef(light);
                found = 1;
            }
        }
        else
        {
            mLights[i-1] = mLights[i];
        }
    }
    if (found) --mCount;
    return found;
}

void MgLightList::Clear()
{
    int i;
    for (i=0; i<mCount; ++i) ::DeleteRef(mLights[i]);
    mCount = 0;
}

