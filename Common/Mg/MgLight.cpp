#include "MgLight.h"

#include <string.h>
#include "MgColor.h"
//#include "MgMerge.h"
#include "IoDataStream.h"

#if 0
IF0  #include "IoOldOoglLexer.h"
IF0  #include "IoOldOoglParseException.h"
#endif

#include "UtMemoryTracker.h"

MgLight::~MgLight()
{
#if UTMEMORYTRACKER
    UtMemoryTracker::Delete(this, 0);
#endif
}


void MgLight::Init()
{
    static HPoint3 defposition = { 0.0, 0.0, 1.0, 0.0 };
    static MgColor deflight(1.0, 1.0, 1.0);
    static MgColor black(0.0, 0.0, 0.0);

    mAmbient = black;
    mColor = deflight;
    mPosition = defposition;
    mGlobalPosition = defposition;
    mIntensity = 1.0f;
    mPositionType = F_GLOBAL;
    mPrivate = 0;
    mChanged = 1;
}

void MgLight::CopyDataFrom(MgLight *src)
{
    // *this = *src;
    mAmbient = src->mAmbient;
    mColor = src->mColor;
    mPosition = src->mPosition;
    mGlobalPosition = src->mGlobalPosition;
    mIntensity = src->mIntensity;
    mPositionType = src->mPositionType;
    ////////////////
    mPrivate = 0;
    mChanged = 1;
}

void MgLight::CopyAllFrom(MgLight *src)
{
    // *this = *src;
    mAmbient = src->mAmbient;
    mColor = src->mColor;
    mPosition = src->mPosition;
    mGlobalPosition = src->mGlobalPosition;
    mIntensity = src->mIntensity;
    mPositionType = src->mPositionType;
    mPrivate = src->mPrivate;
    mChanged = src->mChanged;
    ////////////////
}

#if 0
  became CopyDataFrom ...
MgLight *
LtCopy( register MgLight *l1, register MgLight *l2 )
{
    if(l2 == NULL)
        l2 = NewMgLight(l2);
    *l2 = *l1;          /* Don't reset the 'changed' & 'Private' fields */
    l2->next = NULL;
    /* Reset private and changed flags */
    l2->Private = 0;
    l2->mChanged = 1;
    return l2;
}
#endif // if 0

#if 0
 became CopyAllFrom
MgLight *
LtMerge( register MgLight *l1, register MgLight *l2 )
{
    if(l2 == NULL)
        l2 = NewMgLight(l2);
    *l2 = *l1;          
    /* Don't reset the 'changed' & 'Private' fields */
    l2->next = NULL;
    return l2;
}
#endif  // if 0


enum
{
  LT_AMBIENT,
  LT_COLOR,
  LT_POSITION,
  LT_LOCATION,
  LT_GLOBAL,
  LT_CAMERA,
  LT_LOCAL,
};

static KeywordTable lkeys[] =
{
        { "ambient",    LT_AMBIENT,     0,                 3,   ARGS_REAL},
        { "color",      LT_COLOR,       0,                 3,   ARGS_REAL},
        { "position",   LT_POSITION,    0,                 4,   ARGS_REAL},
        { "location",   LT_LOCATION,    0,                 1,   ARGS_STRING},
};
static KeywordTable locations[] =
{
        { "global",     LT_GLOBAL,      MgLight::F_GLOBAL, 0,   ARGS_NA},
        { "camera",     LT_CAMERA,      MgLight::F_CAMERA, 0,   ARGS_NA},
        { "local",      LT_LOCAL,       MgLight::F_LOCAL,  0,   ARGS_NA},
};

const char *MgLight::GetKeyword() { return "light"; }
const KeywordTable *MgLight::GetKeywordTable() { return lkeys; }
int MgLight::GetNumKeywords() { return sizeof(lkeys)/sizeof(lkeys[0]); }
const char *MgLight::GetIndent() { return "    "; }

#if 0
IF0  int MgLight::LoadProcess(IoOldOoglLexer *lex, int id, void *args)
IF0  {
IF0      float *v = (float *)args;
IF0      switch (id)
IF0      {
IF0  ///////////////////////////////////////////////////////////////////////////
IF0  // Added by John McDonald 6/4/97 -- The new notation for setting an      //
IF0  // MgColor equal to an array is now simpler because of the = operator    //
IF0  // This was to fix a problem with the base class -- see MgColor.h.       //
IF0  ///////////////////////////////////////////////////////////////////////////
IF0      case LT_AMBIENT:    mAmbient = v; break;
IF0      case LT_COLOR:      mColor = v; mIntensity = (float)mColor.Normalize(); break;
IF0      case LT_POSITION:   mPosition = *(HPoint3 *)v; break;
IF0      case LT_LOCATION:
IF0        {
IF0          int i;
IF0          // Get the next token and search for it in the list of location types.
IF0          const char *w = *((const char **)args);
IF0  
IF0          for (i = sizeof(locations)/sizeof(locations[0]); --i >= 0; )
IF0              if (!strcmp(locations[i].word, w))
IF0                  break;
IF0  
IF0          if (i < 0)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading light, Unknown location %s", w);
IF0  
IF0          mPositionType = (PositionType)(locations[i].mask);
IF0          break;
IF0        }
IF0      }
IF0      return 1;
IF0  }
#endif


// This function is called only if the "valid" flag is set for the property.
// The "valid" flag is set if the property was specified by the user.

int MgLight::SaveProcess(IoDataStream *s, int mask)
{
    switch (mask)
    {
    case LT_AMBIENT:    
        s->PrintF("%f %f %f\n",
                  mAmbient.GetRed(),
                  mAmbient.GetGreen(),
                  mAmbient.GetBlue());
        break;
    case LT_COLOR:      
        s->PrintF("%f %f %f\n",
                  mIntensity*mColor.GetRed(),
                  mIntensity*mColor.GetGreen(),
                  mIntensity*mColor.GetBlue());
        break;
    case LT_POSITION:   
        s->PrintF("%f %f %f %f\n",
                  mPosition.x,
                  mPosition.y,
                  mPosition.z,
                  mPosition.w);
        break;
    case LT_LOCATION:
      {
        int i;
        for (i = sizeof(locations)/sizeof(locations[0]); --i >= 0; )
            if (locations[i].mask == mPositionType)
            { 
                s->PrintF( "%s\n", locations[i].word); 
                break; 
            }
        break;
      }
    }
    return !s->error();
}

// This function is called after all flags have been processed.
// If the "valid" flag was set for a property, then it has already been
// written out.  The old Geomview wrote out ALL of these properties, whether
// they were specified by the user or not.  To keep up this tradition,
// this function prints out the properties that were not previously written
// out.  Unless there is a good reason for writing these properties out,
// I would like to remove this whole function. -- Lori

int MgLight::SaveProcessMore(IoDataStream *s)
{
    const char *ind = GetIndent();

    if (!(mValid & LT_AMBIENT))
        s->PrintF("\t%s   ambient %f %f %f\n", ind,
                  mAmbient.GetRed(),
                  mAmbient.GetGreen(),
                  mAmbient.GetBlue());
    if (!(mValid & LT_COLOR))
        s->PrintF("\t%s   color %f %f %f\n", ind,
                  mIntensity*mColor.GetRed(),
                  mIntensity*mColor.GetGreen(),
                  mIntensity*mColor.GetBlue());
    if (!(mValid & LT_POSITION))
        s->PrintF("\t%s   position %f %f %f %f\n", ind,
                  mPosition.x,
                  mPosition.y,
                  mPosition.z,
                  mPosition.w);
    if (!(mValid & LT_LOCATION))
        if (mPositionType != F_GLOBAL)
            s->PrintF("\t%s   location %s\n", ind,
                      mPositionType == F_CAMERA ? "camera" : "local");
  
  /*
   *  s->PrintF("intensity %f\n", mIntensity);
   */

    return !s->error();
}

