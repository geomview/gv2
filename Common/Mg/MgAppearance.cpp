#include "MgAppearance.h"

#include "MgMaterial.h"
#include "MgLight.h"
#include "MgLighting.h"
#include "MgTexture.h"

MgAppearance::~MgAppearance()
{
    if (mpMat) ::DeleteRef(mpMat);
    if (mpLighting) ::DeleteRef(mpLighting);
}

void MgAppearance::Init()
{
    mValid = mOverride = mFlags = 0;

    mNormalScale = 1.0f;
    mLineWidth = 1;
    mShading = F_CONSTANT;
    mDice[0] = mDice[1] = 0;

    mpMat = NULL;
    mpBackMat = NULL;
    mpLighting = NULL;
    mpTexture = NULL;
}


void MgAppearance::Default()
{
    mValid =
        F_FACEDRAW      |
        F_EDGEDRAW      |
        F_VECTDRAW      |
        F_SHADING       |
        F_NORMALSCALE   |
        F_LINEWIDTH     |
        F_TRANSPARENCY  |
        F_EVERT         |
        F_NORMALDRAW;

    mFlags =
        F_FACEDRAW      |
        F_EDGEDRAW      |
        F_VECTDRAW;

    mOverride = 0;

    mShading = F_FLAT;

    mNormalScale = 1.0;
    mLineWidth = 1;

    mpMat = new MgMaterial();
    mpMat->Default();
    mpLighting = new MgLighting();
    mpLighting->Default();

    mpBackMat = NULL;
    mpTexture = NULL;
}


void MgAppearance::SetFrontMaterial(MgMaterial *mat)
{
    if (mpMat) ::DeleteRef(mpMat);
    mpMat = ::NewRef(mat);
}

void MgAppearance::SetBackMaterial(MgMaterial *mat)
{
    if (mpBackMat) ::DeleteRef(mpBackMat);
    mpBackMat = ::NewRef(mat);
}

void MgAppearance::SetLighting(MgLighting *lighting)
{
    if (mpLighting) ::DeleteRef(mpLighting);
    mpLighting = ::NewRef(lighting);
}

void MgAppearance::SetNormalScale(double normalScale)
{
    mNormalScale = (float)normalScale;
    mValid |= F_NORMALSCALE;
}

void MgAppearance::SetLineWidth(int lineWidth)
{
    mLineWidth = lineWidth;
    mValid |= F_LINEWIDTH;
}


void MgAppearance::SetShading(ShadingType shading)
{
    mShading = shading;
    mValid |= F_SHADING;
}

void MgAppearance::SetPatchDice(int u, int v)
{
    mDice[0] = u;
    mDice[1] = v;
    mValid |= F_PATCHDICE;
}


// Copies just the MgAppearance part, not its MgMaterial and MgLighting
// children.
// Pointers to the latter are retained BUT their reference counts are NOT
// incremented.  The caller MUST either RefIncr() or reassign mat and lighting.
void MgAppearance::CopyShallow( MgAppearance *ap )
{
    if (ap == NULL) return;
    mFlags       = ap->mFlags;
    mValid       = ap->mValid;
    mOverride    = ap->mOverride;
    mNormalScale = ap->mNormalScale;
    mLineWidth   = ap->mLineWidth;
    mShading     = ap->mShading;
    mDice[0]     = ap->mDice[0];
    mDice[1]     = ap->mDice[1];
}
    
void MgAppearance::Copy( MgAppearance *ap )
{
    CopyShallow(ap);
    // if(ap->mpMat) mpMat = MtCopy(ap->mpMat, mpMat;)
    if (ap->mpMat) {
        // ??? should we refDecr() the old mpMat here ???
        // mbp Mon May 05 18:39:42 1997
        mpMat = new MgMaterial;
        mpMat->CopyFrom(ap->mpMat);
    }
    //if(ap->mpBackMat) mpBackMat = MtCopy(ap->mpBackMat, mpBackMat);
    if (ap->mpBackMat) {
        // ??? should we refDecr() the old mpBackMat here ???
        // mbp Mon May 05 18:39:42 1997
        mpBackMat = new MgMaterial;
        mpBackMat->CopyFrom(ap->mpBackMat);
    }
    //if(ap->mpLighting) mpLighting = LmCopy(ap->mpLighting, mpLighting);
    if (ap->mpLighting) mpLighting->CopyFrom(ap->mpLighting);
}

void MgAppearance::CopyShared( MgAppearance *ap )
{
    CopyShallow(ap);
    if(ap->mpMat) {
        if (mpMat)
            mpMat->CopyFrom(ap->mpMat);
        else
            mpMat = ::NewRef(ap->mpMat);
    } else {
        if (mpMat) {
            // invalidate everything, since src appearance doesn't
            // have a material
            mpMat->SetValid(0);
            mpMat->SetOverride(0);
        }
    }
    if(ap->mpBackMat) {
        if (mpBackMat)
            mpBackMat->CopyFrom(ap->mpBackMat);
        else
            mpBackMat = ::NewRef(ap->mpBackMat);
    } else {
        if (mpBackMat) {
            // invalidate everything, since src appearance doesn't
            // have a material
            mpBackMat->SetValid(0);
            mpBackMat->SetOverride(0);
        }
    }
    if(ap->mpLighting) {
        if (mpLighting)
            mpLighting->CopyFrom(ap->mpLighting);
        else
            mpLighting = ::NewRef(ap->mpLighting);
    } else {
        if (mpLighting) {
            // invalidate everything, since src appearance doesn't
            // have a lighting
            mpLighting->SetValid(0);
            mpLighting->SetOverride(0);
            mpLighting->GetLightList()->Clear();
        }
    }
}

MgAppearance *MgAppearance::MergeNew(const MgAppearance *src)
{
    register unsigned int mask;
    MgMaterial *pNewMat=NULL, *pNewBackMat=NULL;
    MgLighting *pNewLighting=NULL;
 
    mask = MgProperty::MergeMaskNew(this, src);

    if (src->mpMat) {
        if (mpMat)
            pNewMat = mpMat->MergeNew(src->mpMat);
        else
            pNewMat = ::NewRef(src->mpMat);
    }
    else
    {
        if (mpMat)
            pNewMat = ::NewRef(mpMat);
    }


    if (src->mpBackMat) {
        if (mpBackMat)
            pNewBackMat = mpBackMat->MergeNew(src->mpBackMat);
        else
            pNewBackMat = ::NewRef(src->mpBackMat);
    }
    else
    {
        if (mpBackMat)
            pNewBackMat = ::NewRef(mpBackMat);
    }

    if (src->mpLighting) {
        if (mpLighting)
            pNewLighting = mpLighting->MergeNew(src->mpLighting);
        else
            pNewLighting = ::NewRef(src->mpLighting);
    }
    else
    {
        if (mpLighting)
            pNewLighting = ::NewRef(mpLighting);
    }


    if( mask         == 0          &&
        pNewMat      == mpMat      &&
        pNewBackMat  == mpBackMat  &&
        pNewLighting == mpLighting )
    {
        // No changes needed, so we return a new reference to this
        // appearance.  But first we need to release the new references
        // we may have created for the materials and lighting.
        if (pNewMat)      ::DeleteRef(pNewMat);
        if (pNewBackMat)  ::DeleteRef(pNewBackMat);
        if (pNewLighting) ::DeleteRef(pNewLighting);
        return ::NewRef(this);
    }

    // If we get this far, then some changes are needed, either in the
    // appearance itself, or else one of its pointer objects
    // (material/lighting) has changed.  So create a duplicate
    // appearance, make the changes to it, and return a pointer to it.
    register MgAppearance *dst = new MgAppearance();
    dst->CopyShallow(this);
    
    // Now assign the new pointers
    dst->mpMat      = pNewMat;
    dst->mpBackMat  = pNewBackMat;
    dst->mpLighting = pNewLighting;

    // And finally, merge in appearance-specific data
    if(mask) {
        dst->mFlags    = (src->mFlags    & mask) | (dst->mFlags    & ~mask);
        dst->mValid    = (src->mValid    & mask) | (dst->mValid    & ~mask);
        dst->mOverride = (src->mOverride & mask) | (dst->mOverride & ~mask);
        if(mask & F_NORMALSCALE) dst->mNormalScale = src->mNormalScale;
        if(mask & F_LINEWIDTH)   dst->mLineWidth   = src->mLineWidth;
        if(mask & F_SHADING)     dst->mShading     = src->mShading;
        if(mask & F_PATCHDICE) {
            dst->mDice[0] = src->mDice[0];
            dst->mDice[1] = src->mDice[1];
        }
    }

    return dst;
}



