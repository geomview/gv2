#include "MgTexture.h"

#include <string.h>
//#include "MgMerge.h"
//#include "IoOldOoglLexer.h"
//#include "IoOldOoglParseException.h"

MgTexture::MgTexture()
{
    mFlags = mValid = mOverride = 0;
    _filename = NULL;
    _alphafilename = NULL;
    mData = NULL;
    int _xsize = _ysize = _channels = 0;
    int _apply = 0;
    int _coords = 0;
    mpNext = NULL;
}

MgTexture::~MgTexture()
{
    if (_filename)      delete _filename;
    if (_alphafilename) delete _alphafilename;
    if (mData)          delete mData;
    if (mpNext)         delete mpNext;
}


/*
 * Load Texture from file.
 * Syntax:
 *      < "filename_containing_material"        [or]
 *    {   keyword  value   keyword  value   ...  }
 *
 *   Each keyword may be prefixed by "*", indicating that its value should
 *   override corresponding settings in child objects.  [By default,
 *   children's appearance values supercede those of their parents.]
 *
 *  Note: don't overwrite ka, kd, ks if they're already set when we read in 
 *        the corresponding color.
 */

enum
{
    TX_DONE = 0,
    TX_CLAMP,
    TX_FILE,
    TX_ALPHAFILE,
    TX_APPLY,
    TX_TRANSFORM,
    TX_XSIZE,
    TX_YSIZE,
    TX_CHANNELS,
    TX_BACKGROUND,
    TX_COORDS,
};

static KeywordTable txtr_kw[] =
{
    { "clamp",          TX_CLAMP,       MgTexture::F_DOCLAMP,   1,ARGS_STRING },
    { "file",           TX_FILE,        MgTexture::F_FILE,      1,ARGS_STRING },
    { "alphafile",      TX_ALPHAFILE,   MgTexture::F_ALPHAFILE, 1,ARGS_STRING },
    { "apply",          TX_APPLY,       MgTexture::F_APPLY,     1,ARGS_STRING },
    { "transform",      TX_TRANSFORM,MgTexture::F_HANDLE_TRANSFORM, 0,ARGS_NA },
    { "xsize",          TX_XSIZE,       MgTexture::F_XSIZE,     1,ARGS_INT },
    { "ysize",          TX_YSIZE,       MgTexture::F_YSIZE,     1,ARGS_INT },
    { "channels",       TX_CHANNELS,    MgTexture::F_CHANNELS,  1,ARGS_INT },
    { "background",     TX_BACKGROUND,  MgTexture::F_BACKGROUND,4,ARGS_REAL },
    { "coords",         TX_COORDS,      MgTexture::F_COORDS,    1,ARGS_STRING },
}, clamp_kw[] = {
    { "none",           TX_DONE,  0,                            0, ARGS_NA },
    { "s",              TX_DONE,  MgTexture::TXF_SCLAMP,        0, ARGS_NA },
    { "t",              TX_DONE,  MgTexture::TXF_TCLAMP,        0, ARGS_NA },
    { "st",             TX_DONE,  MgTexture::TXF_SCLAMP|
                                  MgTexture::TXF_TCLAMP,        0, ARGS_NA },
}, apply_kw[] = {
    { "modulate",       TX_DONE,  MgTexture::TXF_MODULATE,      0, ARGS_NA },
    { "blend",          TX_DONE,  MgTexture::TXF_BLEND,         0, ARGS_NA },
    { "decal",          TX_DONE,  MgTexture::TXF_DECAL,         0, ARGS_NA },
}, coord_kw[] = {
    { "given",          TX_DONE,  MgTexture::TXF_COORD_GIVEN,   0, ARGS_NA },
    { "local",          TX_DONE,  MgTexture::TXF_COORD_LOCAL,   0, ARGS_NA },
    { "camera",         TX_DONE,  MgTexture::TXF_COORD_CAMERA,  0, ARGS_NA },
    { "normal",         TX_DONE,  MgTexture::TXF_COORD_NORMAL,  0, ARGS_NA },
};

const char *MgTexture::GetKeyword() { return "texture"; }
const KeywordTable *MgTexture::GetKeywordTable() { return txtr_kw; }
int MgTexture::GetNumKeywords() { return sizeof(txtr_kw)/sizeof(txtr_kw[0]); }
const char *MgTexture::GetIndent() { return "  "; }

#if 0
IF0  int MgTexture::LoadProcess(IoOldOoglLexer *lex, int id, void *args)
IF0  {
IF0      KeywordTable *tab;
IF0      unsigned int *var;
IF0      const char *w;
IF0      int i;
IF0  
IF0      switch (id)
IF0      {
IF0      case TX_CLAMP:      tab = clamp_kw; var = &mFlags;  goto Find;
IF0      case TX_APPLY:      tab = apply_kw; var = &_apply;  goto Find;
IF0      case TX_COORDS:     tab = coord_kw; var = &_coords; goto Find;
IF0  
IF0      Find:
IF0          w = *((const char **)args);
IF0          for (i = sizeof(tab)/sizeof(tab[0]); --i >= 0; )
IF0            if (!strcmp(tab[i].word, w))
IF0              break;
IF0  
IF0          if (i < 0)
IF0              throw new IoOldOoglParseException(lex,
IF0                  "Reading texture.  Unknown ... %s", w);
IF0  
IF0          *var |= tab[i].mask;
IF0          break;
IF0  
IF0      case TX_FILE:       _filename       = strdup(*(char **)args); break;
IF0      case TX_ALPHAFILE:  _alphafilename  = strdup(*(char **)args); break;
IF0  
IF0      case TX_XSIZE:      _xsize    = *(int*)args; break;
IF0      case TX_YSIZE:      _ysize    = *(int*)args; break;
IF0      case TX_CHANNELS:   _channels = *(int*)args; break;
IF0  
IF0      case TX_BACKGROUND: _background = (float*)args; break;
IF0  
IF0      case TX_TRANSFORM:  
IF0  //              GeomOldOoglParser::Load(lex, &_tfm); 
IF0                  break;
IF0      }
IF0  
IF0      return 1;
IF0  }
#endif

int MgTexture::SaveProcess(IoDataStream *s, int mask)
{
//    float v;
//  MgColor *c;

    switch (mask)
    {
    case TX_CLAMP:      
        switch (mFlags&(TXF_SCLAMP|TXF_TCLAMP))
        {
        case 0:                         s->PutS("none");break;
        case TXF_SCLAMP:                s->PutS("s");   break;
        case TXF_TCLAMP:                s->PutS("t");   break;
        case TXF_SCLAMP|TXF_TCLAMP:     s->PutS("st");  break;
        }
        break;

    case TX_APPLY:      
        switch (_apply)
        {
        case TXF_MODULATE:      s->PutS("modulate");    break;
        case TXF_BLEND:         s->PutS("blend");       break;
        case TXF_DECAL:         s->PutS("decal");       break;
        default:                s->PrintF("%d", _apply);break;
        }
        break;

    case TX_COORDS:     
        switch (_coords)
        {
        case TXF_COORD_GIVEN:   s->PutS("given");       break;
        case TXF_COORD_LOCAL:   s->PutS("local");       break;
        case TXF_COORD_CAMERA:  s->PutS("camera");      break;
        case TXF_COORD_NORMAL:  s->PutS("normal");      break;
        default:                s->PrintF("%d", _coords);break;
        }
        break;

    case TX_FILE:       s->PrintF("%s", _filename);     break;
    case TX_ALPHAFILE:  s->PrintF("%s", _alphafilename);break;
    case TX_XSIZE:      s->PrintF("%d", _xsize);        break;
    case TX_YSIZE:      s->PrintF("%d", _ysize);        break;
    case TX_CHANNELS:   s->PrintF("%d", _channels);     break;

    case TX_BACKGROUND: s->PrintF("%g %g %g %g",
                        _background.GetRed(), _background.GetGreen(),
                        _background.GetBlue(), _background.GetAlpha());
                        break;

    case TX_TRANSFORM:  
//              return GeomOldOoglParser::Save(s, &_tfm);
                break;  // Dummy command (VC++ complains if this is empty???? -- jcm 10/22/97)
    }

    return !s->error();
}

