#include "MgAppearance.h"

#include "MgMaterial.h"
#include "MgLight.h"
#include "MgLighting.h"
#include "MgTexture.h"
#include "IoDataStream.h"

#if 0
IF0  #include "IoOldOoglLexer.h"
IF0  #include "IoOldOoglParseException.h"
#endif

#include <string.h>

enum {
    AP_DONE = 0,
    AP_APPEARANCE,
    AP_SHADING,
    AP_NORMSCALE,
    AP_LINEWIDTH,
    AP_MATERIAL,
    AP_BACKMATERIAL,
    AP_PATCHDICE,
    AP_LIGHT,
    AP_LIGHTING,
    AP_TEXTURE,
};

static struct KeywordTable ap_kw[] = {
 { "face",      AP_DONE,        MgAppearance::F_FACEDRAW,       0, ARGS_NA },
 { "edge",      AP_DONE,        MgAppearance::F_EDGEDRAW,       0, ARGS_NA },
 { "vect",      AP_DONE,        MgAppearance::F_VECTDRAW,       0, ARGS_NA },
 { "transparent",AP_DONE,       MgAppearance::F_TRANSPARENCY,   0, ARGS_NA },
 { "evert",     AP_DONE,        MgAppearance::F_EVERT,          0, ARGS_NA },
 { "keepcolor", AP_DONE,        MgAppearance::F_KEEPCOLOR,      0, ARGS_NA },
 { "texturing", AP_DONE,        0/*F_TEXTURE*/,                 0, ARGS_NA },
 { "backcull",  AP_DONE,        MgAppearance::F_BACKCULL,       0, ARGS_NA },
 { "shadelines",AP_DONE,        MgAppearance::F_SHADELINES,     0, ARGS_NA },
 { "concave",   AP_DONE,        MgAppearance::F_CONCAVE,        0, ARGS_NA },
 { "shading",   AP_SHADING,     MgAppearance::F_SHADING,        1, ARGS_STRING},
 { "mipmap",    AP_DONE,        0/*F_TXMIPMAP*/,                0, ARGS_NA },
 { "mipinterp", AP_DONE,        0/*F_TXMIPINTERP*/,             0, ARGS_NA },
 { "linear",    AP_DONE,        0/*F_TXLINEAR*/,                0, ARGS_NA },
 { "normal",    AP_DONE,        MgAppearance::F_NORMALDRAW,     0, ARGS_NA },
 { "normscale", AP_NORMSCALE,   MgAppearance::F_NORMALSCALE,    1, ARGS_REAL },
 { "linewidth", AP_LINEWIDTH,   MgAppearance::F_LINEWIDTH,      1, ARGS_INT },
 { "material",  AP_MATERIAL,    0,                              0, ARGS_NA },
 { "backmaterial", AP_BACKMATERIAL,     0,                      0, ARGS_NA },
 { "patchdice", AP_PATCHDICE,   MgAppearance::F_PATCHDICE,      2, ARGS_INT },
 { "lighting",  AP_LIGHTING,    0,                              0, ARGS_NA },
 { "texture",   AP_TEXTURE,     0,                              0, ARGS_NA },
}, shad_kw[] = {
 { "smooth",    AP_DONE,        MgAppearance::F_SMOOTH,         0, ARGS_NA },
 { "flat",      AP_DONE,        MgAppearance::F_FLAT,           0, ARGS_NA },
 { "constant",  AP_DONE,        MgAppearance::F_CONSTANT,       0, ARGS_NA },
 { "csmooth",   AP_DONE,        MgAppearance::F_CSMOOTH,        0, ARGS_NA },
};

const char *MgAppearance::GetKeyword() { return "appearance"; }
const KeywordTable *MgAppearance::GetKeywordTable() { return ap_kw; }
int MgAppearance::GetNumKeywords() { return sizeof(ap_kw)/sizeof(ap_kw[0]); }

#if 0
IF0  int MgAppearance::LoadProcess(IoOldOoglLexer *lex, int id, void *args)
IF0  {
IF0    int i;
IF0      // Some keywords require more processing than just Setting a flag.
IF0      switch (id)
IF0      {
IF0      case AP_DONE: break;
IF0  
IF0      // shading { smooth | flat | constant | csmooth }
IF0      case AP_SHADING:
IF0        {
IF0          // Get the next token and search for it in the list of shading types.
IF0          const char *w = *((const char **)args);
IF0          for(i = sizeof(shad_kw)/sizeof(shad_kw[0]); --i >= 0; )
IF0            if(!strcmp(shad_kw[i].word, w))
IF0              break;
IF0  
IF0          if (i < 0)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading appearance.  Unknown shading type %s", w);
IF0          mShading = ShadingType(shad_kw[i].mask);
IF0          break;
IF0        }
IF0  
IF0      // normscale <float>
IF0      case AP_NORMSCALE:
IF0        mNormalScale = *((float *)args); break;
IF0  
IF0      // linewidth <integer>
IF0      case AP_LINEWIDTH:
IF0        mLineWidth = *((int *)args); break;
IF0  
IF0      // material { ... }
IF0      case AP_MATERIAL:
IF0        {
IF0          MgMaterial *mat = new MgMaterial;
IF0          if (mat->Load(lex)) {
IF0            mpMat = mat;
IF0          } else {
IF0            delete mat;
IF0            return 0;
IF0          }
IF0        }
IF0        break;
IF0  
IF0      // lighting { ... }
IF0      case AP_LIGHTING:
IF0        {
IF0          MgLighting *lighting = new MgLighting;
IF0          if (lighting->Load(lex)) {
IF0            mpLighting = lighting;
IF0          } else {
IF0            delete lighting;
IF0            return 0;
IF0          }
IF0        }
IF0        break;
IF0  
IF0      // backmaterial { ... }
IF0      case AP_BACKMATERIAL:
IF0        {
IF0          MgMaterial *mat = new MgMaterial;
IF0          if (mat->Load(lex)) {
IF0            mpBackMat = mat;
IF0          } else {
IF0            delete mat;
IF0            return 0;
IF0          }
IF0        }
IF0        break;
IF0  
IF0      // texture { ... }
IF0      case AP_TEXTURE:
IF0        {
IF0          MgTexture *txtr = new MgTexture;
IF0          if (txtr->Load(lex)) {
IF0            mpTexture = txtr;
IF0          } else {
IF0            delete txtr;
IF0            return 0;
IF0          }
IF0        }
IF0        break;
IF0  
IF0      // patchdice <u_short> <v_short>
IF0      case AP_PATCHDICE:
IF0        mDice[0] = ((int *)args)[0];
IF0        mDice[1] = ((int *)args)[1];
IF0        break;
IF0  
IF0      default:
IF0        /* GEOMVIEW ERROR -- this should never happen */
IF0          throw new IoOldOoglParseException(lex,
IF0              "Reading appearance.  Unknown keyword number %d.  Please report this error to software@geom.umn.edu", id);
IF0      }
IF0  
IF0      return 1;
IF0  }
#endif

int MgAppearance::SaveProcess(IoDataStream *s, int mask)
{
    switch(mask)
    {
    case F_SHADING:
        switch(mShading)
        {
        case F_SMOOTH:          s->PutS("smooth");              break;
        case F_FLAT:            s->PutS("flat");                break;
        case F_CONSTANT:        s->PutS("constant");            break;
        case F_CSMOOTH:         s->PutS("csmooth");             break;
        default:                s->PrintF("%d", mShading);      break;
        }
        break;
    case F_NORMALSCALE:         s->PrintF("%g", mNormalScale);  break;
    case F_LINEWIDTH:           s->PrintF("%d ", mLineWidth);   break;
    case F_PATCHDICE:           s->PrintF("%d %d", mDice[0], mDice[1]); break;
    }
    return 1;
}

int MgAppearance::SaveProcessMore(IoDataStream *s)
{
#if 0
    s->PrintF("###### mpMat      = %8x\n", mpMat);
    s->PrintF("###### mpBackMat  = %8x\n", mpBackMat);
    s->PrintF("###### mpLighting = %8x\n", mpLighting);
    s->PrintF("###### mpTexture  = %8x\n", mpTexture);
#endif
    if (mpMat && !mpMat->Save(s))
        return 0;

    if (mpBackMat && !mpBackMat->Save(s, "backmaterial"))
        return 0;

    if (mpLighting && !mpLighting->Save(s))
        return 0;

    if (mpTexture && !mpTexture->Save(s))
        return 0;

  return 1;
}
