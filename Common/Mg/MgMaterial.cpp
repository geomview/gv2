#include "MgMaterial.h"

const double MgMaterial::sMaxShininess = 1024.0;

MgMaterial::MgMaterial(const MgMaterial &src)
{
    *this = src;
    mPrivate = 0;
    mChanged = 1;
}

void MgMaterial::Init()
{
    // mbp-purify: maybe changed a few lines in this function
    mValid = mOverride = 0;

    mShininess = 0.0;
    mKa = 0.0;
    mKd = 0.0;
    mKs = 0.0;
    mDiffuse.SetAlpha(1.0);
    mPrivate = 0;
    mChanged = 1;
}

void MgMaterial::Default()
{
    mOverride = 0;
    mShininess = 15.0;
    mKa = 0.3;
    mKd = 1.0;
    mKs = 0.3;
    mDiffuse.SetRGBA   (0.9, 0.9, 0.9, 1.0);
    mAmbient.SetRGB    (1.0, 1.0, 1.0);
    mSpecular.SetRGB   (1.0, 1.0, 1.0);
    mEdgeColor.SetRGB  (0.0, 0.0, 0.0);
    mNormalColor.SetRGB(1.0, 1.0, 1.0);

    mValid =
        F_SHININESS     |
        F_KA            |
        F_KD            |
        F_KS            |
        F_DIFFUSE       |
        F_ALPHA         |
        F_AMBIENT       |
        F_SPECULAR      |
        F_EDGECOLOR     |
        F_NORMALCOLOR;

    mPrivate = 0;
    mChanged = 1;
}

void MgMaterial::SetEmission(MgColor emission)
{
    mEmission = emission;
    mValid |= F_EMISSION;
}

void MgMaterial::SetAmbient(MgColor ambient)
{
    mAmbient = ambient;
    mValid |= F_AMBIENT;
}

void MgMaterial::SetDiffuse(MgColorA diffuse)
{
    mDiffuse = diffuse;
    mValid |= F_DIFFUSE;
}

void MgMaterial::SetSpecular(MgColor specular)
{
    mSpecular = specular;
    mValid |= F_SPECULAR;
}

void MgMaterial::SetShininess(float shininess)
{
    mShininess = shininess;
    mValid |= F_SHININESS;
}

void MgMaterial::SetKa(double ka)
{
    mKa = ka;
    mValid |= F_KA;
}

void MgMaterial::SetKd(double kd)
{
    mKd = kd;
    mValid |= F_KD;
}

void MgMaterial::SetKs(double ks)
{
    mKs = ks;
    mValid |= F_KS;
}

void MgMaterial::SetEdgeColor(MgColor edgecolor)
{
    mEdgeColor = edgecolor;
    mValid |= F_EDGECOLOR;
}

void MgMaterial::SetNormalColor(MgColor normalcolor)
{
    mNormalColor = normalcolor;
    mValid |= F_NORMALCOLOR;
}


////////////////////////////////////////////////////////////////////////


void MgMaterial::CopyFrom(MgMaterial *src)
{
    if (!src) return;

    // *this = *src;
    mEmission    = src->mEmission;
    mAmbient     = src->mAmbient;
    mDiffuse     = src->mDiffuse;
    mSpecular    = src->mSpecular;
    mShininess   = src->mShininess;
    mKa          = src->mKa;
    mKd          = src->mKd;
    mKs          = src->mKs;
    mEdgeColor   = src->mEdgeColor;
    mNormalColor = src->mNormalColor;
    mValid       = src->mValid;
    mOverride    = src->mOverride;
    ////////////////

    mPrivate = 0;
    mChanged = 1;
}

MgMaterial * MgMaterial::MergeNew(const MgMaterial *src)
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

    register MgMaterial *dst = new MgMaterial(*this);
    // (This uses the copy constructor to create the duplicate.)

    // Merge in the changes
    dst->mChanged  |= src->mChanged;
    dst->mValid     = (src->mValid    & mask) | (mValid    & ~mask);
    dst->mOverride  = (src->mOverride & mask) | (mOverride & ~mask);
    if(mask & F_EMISSION   ) dst->mEmission    = src->mEmission;
    if(mask & F_AMBIENT    ) dst->mAmbient     = src->mAmbient;
    if(mask & F_DIFFUSE    ) dst->mDiffuse     = src->mDiffuse;
    if(mask & F_SPECULAR   ) dst->mSpecular    = src->mSpecular;
    if(mask & F_KA         ) dst->mKa          = src->mKa;
    if(mask & F_KD         ) dst->mKd          = src->mKd;
    if(mask & F_KS         ) dst->mKs          = src->mKs;
    if(mask & F_SHININESS  ) dst->mShininess   = src->mShininess;
    if(mask & F_EDGECOLOR  ) dst->mEdgeColor   = src->mEdgeColor;
    if(mask & F_NORMALCOLOR) dst->mNormalColor = src->mNormalColor;

    return dst;
}
