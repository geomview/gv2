//-*-C++-*-
#ifndef MGMATERIAL_H
#define MGMATERIAL_H


// class MgMaterial
// 

#include "MgProperty.h"
#include "MgColor.h"

class MgMaterial : public MgProperty
{
public:
    enum
    {
        F_EMISSION      = 0x1,
        F_AMBIENT       = 0x2,
        F_DIFFUSE       = 0x4,
        F_SPECULAR      = 0x8,
        F_KA            = 0x10,
        F_KD            = 0x20,
        F_KS            = 0x40,
        F_ALPHA         = 0x80,
        F_SHININESS     = 0x100,
        F_EDGECOLOR     = 0x200,
        F_NORMALCOLOR   = 0x400
    };
    static const double sMaxShininess;

    MgMaterial() { Init(); }

    MgMaterial(const MgMaterial &src);

    void Default();

    inline MgColor *  GetEmission() { return &mEmission; }
    inline MgColor *  GetAmbient() { return &mAmbient; }
    inline MgColorA * GetDiffuse() { return &mDiffuse; }
    inline float *    GetDiffuseF() { return (float*)mDiffuse; }
    inline MgColor *  GetSpecular() { return &mSpecular; }
    inline double     GetShininess() { return mShininess; }
    inline double     GetKa() { return mKa; }
    inline double     GetKd() { return mKd; }
    inline double     GetKs() { return mKs; }
    inline MgColor *  GetEdgeColor() { return &mEdgeColor; }
    inline MgColor *  GetNormalColor() { return &mNormalColor; }

    void SetEmission(MgColor emission);
    void SetAmbient(MgColor ambient);
    void SetDiffuse(MgColorA diffuse);
    void SetSpecular(MgColor specular);
    void SetShininess(float shininess);
    void SetKa(double ka);
    void SetKd(double kd);
    void SetKs(double ks);
    void SetEdgeColor(MgColor edgecolor);
    void SetNormalColor(MgColor normalcolor);

    void CopyFrom(MgMaterial *src);

    MgMaterial * MergeNew(const MgMaterial *src);

  //    virtual int LoadProcess(class IoOldOoglLexer *lex, int id, void *args);
    virtual int SaveProcess(class IoDataStream *s, int mask);

    virtual const char *         GetKeyword();
    virtual const KeywordTable * GetKeywordTable();
    virtual int                  GetNumKeywords();
    virtual const char *         GetIndent();

private:
    void Init();

private:
    MgColor     mEmission;
    MgColor     mAmbient;
    MgColorA    mDiffuse;
    MgColor     mSpecular;
    double      mShininess;
    double      mKa, mKd, mKs;
    MgColor     mEdgeColor;     // Color for polygon edges and other vectors
    MgColor     mNormalColor;   // Color for surface-normal vectors */
    int         mPrivate;
    int         mChanged;
};


#endif // MGMATERIAL_H
