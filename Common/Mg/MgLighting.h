//-*-C++-*-
#ifndef MGLIGHTING_H
#define MGLIGHTING_H


// class MgLighting
// 

#include "MgProperty.h"
#include "Geometry.h"
#include "MgColor.h"
#include "MgLightList.h"

class MgLighting : public MgProperty {
public:
    MgLighting() { Init(); }
    MgLighting(const MgLighting &src);
    ~MgLighting();

    void         CopyFrom(register MgLighting *from);

    MgLighting * MergeNew(const MgLighting *src);

    enum
    {
        F_LOCALVIEWER   = 0x1,   // Local viewer (flag valid)
        F_AMBIENT       = 0x2,   // Ambient light color
        F_ATTENCONST    = 0x4,   // attenuation constant factor
        F_ATTENMULT     = 0x8,   // attenuation linear factor
        F_ATTENMULT2    = 0x20,  // 1/r^2 attenuation factor
        F_REPLACELIGHTS = 0x10,  // When merging, use only new lights, not union
    };

    void Default();

    void SetAmbient(MgColor ambient);
    void SetLocalViewer(int localviewer);
    void SetAttenconst(double attenConst);
    void SetAttenmult(double attenMult);
    void SetAttenmult2(double attenMult2);
    void SetPrivate(int p);
    void SetReplaceLights(int replaceLights);

    MgColor        *GetAmbient()        { return &mAmbient; }
    int             GetLocalViewer()    { return mLocalViewer; }
    float           GetAttenConst()     { return mAttenConst; }
    float           GetAttenMult()      { return mAttenMult; }
    float           GetAttenMult2()     { return mAttenMult2; }
    int             GetPrivate()        { return mPrivate; }
    int             GetChanged()        { return mChanged; }
    MgLightList    *GetLightList()         { return &mLightList; }


  //    virtual int LoadProcess(IoOldOoglLexer *lex, int id, void *args);
    virtual int SaveProcess(IoDataStream *s, int mask);
    virtual int SaveProcessMore(IoDataStream *s);

    virtual const char *         GetKeyword();
    virtual const KeywordTable * GetKeywordTable();
    virtual int                  GetNumKeywords();
    virtual const char *         GetIndent();

private:
    void Init();

private:
    MgColor         mAmbient;
    int             mLocalViewer;
    float           mAttenConst;
    float           mAttenMult;
    float           mAttenMult2;
    int             mReplaceLights;
    int             mPrivate;
    int             mChanged;
    MgLightList     mLightList;
};


#endif MGLIGHTING_H
