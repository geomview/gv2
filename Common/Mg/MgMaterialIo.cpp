#include "MgMaterial.h"
//#include "IoOldOoglLexer.h"

/*
 * Load Material from file.
 * Syntax:
 *      < "filename_containing_material"        [or]
 *    {   keyword  value   keyword  value   ...  }
 *
 *   Each keyword may be prefixed by "*", indicating that its value should
 *   override corresponding Settings in child objects.  [By default,
 *   children's appearance values supercede those of their parents.]
 *
 *  Note: don't overwrite ka, kd, ks if they're already Set when we read in 
 *        the corresponding color.
 */

enum
{
    MT_DONE = 0,
    MT_SHININESS,
    MT_KA,
    MT_KD,
    MT_KS,
    MT_ALPHA,
    MT_EMISSION,
    MT_AMBIENT,
    MT_DIFFUSE,
    MT_SPECULAR,
    MT_EDGECOLOR,
    MT_NORMALCOLOR,
};

static KeywordTable mat_kw[] =
{
    { "shininess",    MT_SHININESS, MgMaterial::F_SHININESS,1, ARGS_REAL},
    { "ka",           MT_KA,        MgMaterial::F_KA,       1, ARGS_REAL},
    { "kd",           MT_KD,        MgMaterial::F_KD,       1, ARGS_REAL},
    { "ks",           MT_KS,        MgMaterial::F_KS,       1, ARGS_REAL},
    { "alpha",        MT_ALPHA,     MgMaterial::F_ALPHA,    1, ARGS_REAL},
    { "backdiffuse",  MT_EMISSION,  MgMaterial::F_EMISSION, 3, ARGS_REAL},
    { "emission",     MT_EMISSION,  MgMaterial::F_EMISSION, 3, ARGS_REAL},
    { "ambient",      MT_AMBIENT,   MgMaterial::F_AMBIENT,  3, ARGS_REAL},
    { "diffuse",      MT_DIFFUSE,   MgMaterial::F_DIFFUSE,  3, ARGS_REAL},
    { "specular",     MT_SPECULAR,  MgMaterial::F_SPECULAR, 3, ARGS_REAL},
    { "edgecolor",    MT_EDGECOLOR, MgMaterial::F_EDGECOLOR,3, ARGS_REAL},
    { "normalcolor", MT_NORMALCOLOR,MgMaterial::F_NORMALCOLOR,3,ARGS_REAL},
};

const char *MgMaterial::GetKeyword() { return "material"; }
const KeywordTable *MgMaterial::GetKeywordTable() { return mat_kw; }
int MgMaterial::GetNumKeywords() { return sizeof(mat_kw)/sizeof(mat_kw[0]); }
const char *MgMaterial::GetIndent() { return "  "; }

#if 0
IF0  int MgMaterial::LoadProcess(IoOldOoglLexer *lex, int id, void *args)
IF0  {
IF0      float *v = (float *)args;
IF0      switch (id)
IF0      {
IF0      case MT_SHININESS:  mShininess = v[0]; break;
IF0      case MT_KA:         mKa = v[0]; break;
IF0      case MT_KD:         mKd = v[0]; break;
IF0      case MT_KS:         mKs = v[0]; break;
IF0      case MT_ALPHA:      mDiffuse.SetAlpha(v[0]); break;
IF0      case MT_EMISSION:   mEmission = v; break;
IF0      case MT_AMBIENT:    mAmbient = v; break;
IF0      case MT_DIFFUSE:    *(MgColor *)&mDiffuse = v; break;
IF0      case MT_SPECULAR:   mSpecular = v; break;
IF0      case MT_EDGECOLOR:  mEdgeColor = v; break;
IF0      case MT_NORMALCOLOR:        mNormalColor = v; break;
IF0      }
IF0      return 1;
IF0  }
#endif

int MgMaterial::SaveProcess(IoDataStream *s, int mask)
{
    float v;
    MgColor *c;

    switch (mask)
    {
    case F_KA: v = (float)mKa; goto pfloat;
    case F_KD: v = (float)mKd; goto pfloat;
    case F_KS: v = (float)mKs; goto pfloat;
    case F_SHININESS: v = (float)mShininess; goto pfloat;
    case F_ALPHA: v = (float)mDiffuse.GetAlpha(); goto pfloat;

    pfloat:
    s->PrintF("%f", v);
    break;

    case F_DIFFUSE:     c = (MgColor *)&mDiffuse; goto pcolor;
    case F_AMBIENT:     c = &mAmbient; goto pcolor;
    case F_EMISSION:    c = &mEmission; goto pcolor;
    case F_SPECULAR:    c = &mSpecular; goto pcolor;
    case F_EDGECOLOR:   c = &mEdgeColor; goto pcolor;
    case F_NORMALCOLOR: c = &mNormalColor; goto pcolor;

    pcolor:
    s->PrintF("%f %f %f", c->GetRed(), c->GetGreen(), c->GetBlue());
    break;
    }

    return !s->error();
}
