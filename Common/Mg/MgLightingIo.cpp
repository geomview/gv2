#include "MgLighting.h"

#include "MgColor.h"
#include "MgLight.h"
//#include "IoOldOoglLexer.h"

enum
{
    L_AMBIENT,
    L_LOCALVIEWER,
    L_ATTENCONST,
    L_ATTENMULT,
    L_ATTENMULT2,
    L_REPLACE,
    L_LIGHT,
};

static KeywordTable lkeys[] =
{
    { "ambient",             L_AMBIENT,     MgLighting::F_AMBIENT,       3, ARGS_REAL },
    { "localviewer",   L_LOCALVIEWER, MgLighting::F_LOCALVIEWER,         1, ARGS_REAL },
    { "attenconst",    L_ATTENCONST,  MgLighting::F_ATTENCONST,  1, ARGS_REAL },
    { "attenmult",     L_ATTENMULT,   MgLighting::F_ATTENMULT,   1, ARGS_REAL },
    { "attenmult2",    L_ATTENMULT2,  MgLighting::F_ATTENMULT2,  1, ARGS_REAL },
    { "replacelights", L_REPLACE,           MgLighting::F_REPLACELIGHTS, 0, ARGS_NA },
    { "light",       L_LIGHT,       0,                           0, ARGS_NA },
};

const char *MgLighting::GetKeyword() { return "lighting"; }
const KeywordTable *MgLighting::GetKeywordTable() { return lkeys; }
int MgLighting::GetNumKeywords() { return sizeof(lkeys)/sizeof(lkeys[0]); }
const char *MgLighting::GetIndent() { return "  "; }

#if 0
IF0  int MgLighting::LoadProcess(IoOldOoglLexer *lex, int id, void *args)
IF0  {
IF0      float *v = (float *)args;
IF0      switch (id)
IF0      {
IF0      case L_AMBIENT:     { mAmbient = v; break; }
IF0      case L_LOCALVIEWER: { mLocalViewer = (int) v[0]; break; }
IF0      case L_ATTENCONST:  { mAttenConst = v[0]; break; }
IF0      case L_ATTENMULT:   { mAttenMult = v[0]; break; }
IF0      case L_ATTENMULT2:  { mAttenMult2 = v[0]; break; }
IF0      case L_LIGHT:       
IF0        {
IF0                  MgLight *light = new MgLight;
IF0                  if (light->Load(lex))
IF0                      mLightList.AddLight(light);
IF0                  ::DeleteRef(light);
IF0                  break;
IF0        }
IF0      }
IF0      return 1;
IF0  }
#endif

// This function is called only if the "valid" flag is Set for the property.
// The "valid" flag is Set if the property was specified by the user.

int MgLighting::SaveProcess(IoDataStream *s, int mask)
{
    switch (mask)
    {
    case F_LOCALVIEWER: s->PrintF("%d", mLocalViewer);  break;
    case F_ATTENCONST:  s->PrintF("%g", mAttenConst);   break;
    case F_ATTENMULT:   s->PrintF("%g", mAttenMult);    break;
    case F_ATTENMULT2:  s->PrintF("%g", mAttenMult2);   break;
    case F_AMBIENT:     
        s->PrintF("%g %g %g",
          mAmbient.GetRed(),
          mAmbient.GetGreen(),
          mAmbient.GetBlue());
        break;
    }
    return !s->error();
}

// This function is called after all flags have been processed.
// If the "valid" flag was Set for a property, then it has already been
// written out.  The old Geomview wrote out ALL of these properties, whether
// they were specified by the user or not.  To keep up this tradition,
// this function prints out the properties that were not previously written
// out.  Unless there is a good reason for writing these properties out,
// I would like to remove everything but the "for" loop at the end. -- Lori

int MgLighting::SaveProcessMore(IoDataStream *s)
{
// I hope these four get taken out.  Why do we print these characteristics
// even if they were never specified?  - Lori  Thu Sep 11 13:36:14 CDT 1997
// OK, I'm taking them out. I have no idea why they were here.
// I guess they were in the Unix version.  mbp Sun Dec 14 23:53:27 1997
#if 0
    const char *ind = GetIndent();
    if (!(mValid & F_AMBIENT))
        s->PrintF("\t%s   ambient %g %g %g\n", ind,
            mAmbient.GetRed(), mAmbient.GetGreen(), mAmbient.GetBlue());
    if (!(mValid & F_LOCALVIEWER))
        s->PrintF("\t%s   localviewer %d\n", ind, mLocalViewer);
    if (!(mValid & F_ATTENCONST))
        s->PrintF("\t%s   attenconst %g\n", ind, mAttenConst);
    if (!(mValid & F_ATTENMULT))
        s->PrintF("\t%s   attenmult %g\n", ind, mAttenMult);
#endif
// Delete until here.

    // Write out all lights.
    MgLightListIter it(mLightList);
    for ( ; it; ++it)
    {
        MgLight *light = it();
        if (!light->Save(s)) 
            return 0;
    }

    return !s->error();
}
