#include "MgLighting.h"

#include "MgColor.h"
#include "MgLight.h"

void MgLighting::Init()
{
    static MgColor black(0.0, 0.0, 0.0);
    mValid = mOverride = 0;
    mAmbient = black;
    mLocalViewer = 1;
    mAttenConst = 0.0;
    mAttenMult = 0.0;
    mAttenMult2 = 0.0;
    mReplaceLights = 0;
    mPrivate = 0;
    mChanged = 1;
}

void MgLighting::Default()
{
    mAmbient.SetRGB(0.2, 0.2, 0.2);
    mLocalViewer = 1;
    mAttenConst = 1.0;
    mAttenMult = 0.0;
    mReplaceLights = 1;

    mOverride = 0;
    mValid =
        F_AMBIENT        |
        F_LOCALVIEWER    |
        F_ATTENCONST     |
        F_ATTENMULT      |
        F_REPLACELIGHTS;
    mFlags = F_REPLACELIGHTS;

    mLightList.Clear();

    MgLight *pLight;

    pLight = new MgLight;
    pLight->SetAmbient (0.0,  0.0,   0.0);
    pLight->SetColor   (0.75, 0.75,  0.75);
    pLight->SetPosition(0.0,  0.0,  10.0, 0.0,  MgLight::F_GLOBAL);
    mLightList.AddLight(pLight);
    ::DeleteRef(pLight);

    pLight = new MgLight;
    pLight->SetAmbient (0.0, 0.0,  0.0);
    pLight->SetColor   (0.6, 0.6,  0.6);
    pLight->SetPosition(0.0, 1.0, -1.0, 0.0,  MgLight::F_GLOBAL);
    mLightList.AddLight(pLight);
    ::DeleteRef(pLight);

    pLight = new MgLight;
    pLight->SetAmbient (0.0,  0.0,  0.0);
    pLight->SetColor   (0.4,  0.4,  0.4);
    pLight->SetPosition(1.0, -2.0, -1.0, 0.0,  MgLight::F_GLOBAL);
    mLightList.AddLight(pLight);
    ::DeleteRef(pLight);

    mPrivate = 0;
    mChanged = 1;
}

MgLighting::MgLighting(const MgLighting &src)
{
    *this = src;
    mPrivate = 0;
    mChanged = 1;
}

MgLighting::~MgLighting()
{}


void MgLighting::SetAmbient(MgColor ambient) 
{
    mValid |= F_AMBIENT;
    mAmbient = ambient;
}

void MgLighting::SetLocalViewer(int localViewer) 
{
    mValid |= F_LOCALVIEWER;
    mLocalViewer = localViewer;
}

void MgLighting::SetAttenconst(double attenConst) 
{
    mValid |= F_ATTENCONST;
    mAttenConst = (float)attenConst;
}

void MgLighting::SetAttenmult(double attenMult) 
{
    mValid |= F_ATTENMULT;
    mAttenMult = (float)attenMult;
}

void MgLighting::SetAttenmult2(double attenMult2) 
{
    mValid |= F_ATTENMULT2;
    mAttenMult2 = (float)attenMult2;
}

void MgLighting::SetReplaceLights(int replaceLights)
{
    mReplaceLights = replaceLights;
}

void MgLighting::SetPrivate(int p) 
{
    mPrivate = p;
}

void MgLighting::CopyFrom(register MgLighting *from)
{
    if (!from) return;

    if (from != this) 
    {
        // *this = *from;
        mAmbient = from->mAmbient;
        mLocalViewer = from->mLocalViewer;
        mAttenConst = from->mAttenConst;
        mAttenMult = from->mAttenMult;
        mAttenMult2 = from->mAttenMult2;
        mReplaceLights = from->mReplaceLights;
        mValid = from->mValid;
        mOverride = from->mOverride;
        mPrivate = from->mPrivate;
        mChanged = from->mChanged;
        mLightList.Clear();
        mLightList.AddAllLightsFrom(&(from->mLightList));
    }
}


MgLighting * MgLighting::MergeNew(const MgLighting *src)
{
    register unsigned int mask;

    // Get the mask indicating what to merge
    mask = MgProperty::MergeMaskNew(this, src);
    if(mask == 0) {
        // No changes required, so just return new a reference to this
        return ::NewRef(this);
    }

    // If we get here, mask isn't 0, so there must be changes to be
    // made.  Create a duplicate, make the changes to it, and return a
    // pointer to it.

    register MgLighting *dst = new MgLighting(*this);
    // (This uses the copy constructor to create the duplicate.)

    dst->mChanged  |= src->mChanged;
    dst->mValid     =  (src->mValid    & mask) | (dst->mValid    & ~mask);
    dst->mOverride  =  (src->mOverride & mask) | (dst->mOverride & ~mask);
    if(mask & F_LOCALVIEWER) dst->mLocalViewer = src->mLocalViewer;
    if(mask & F_AMBIENT    ) dst->mAmbient     = src->mAmbient;
    if(mask & F_ATTENCONST ) dst->mAttenConst  = src->mAttenConst;
    if(mask & F_ATTENMULT  ) dst->mAttenMult   = src->mAttenMult;
    if(mask & F_ATTENMULT2 ) dst->mAttenMult2  = src->mAttenMult2;

    if (mask & F_REPLACELIGHTS)
    {
        /* F_REPLACELIGHTS: replace lights rather than merging with them */
        dst->mLightList.Clear();
    }
    dst->mLightList.AddAllLightsFrom(&(src->mLightList));

    return dst;
}


