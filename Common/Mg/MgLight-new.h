//-*-C++-*-
#ifndef MGLIGHT_H
#define MGLIGHT_H


// class MgLight
// 

#include "MgProperty.h"

#include "Geometry.h"
#include "MgColor.h"

class MgLight : public MgProperty {
public:
    friend class MgLighting;

    MgLight() { Init(); }
    ~MgLight();

    inline void      SetAmbientColor(MgColor color) { mAmbient = color; }
    inline MgColor   GetAmbientColor() { return mAmbient; }

    inline void      SetColor(MgColor color) { mColor = color; }
    inline MgColor   GetColor() { return mColor; }

    inline void      SetIntensity(double intensity)
                       { mIntensity=(float)intensity; }
    inline double    GetIntensity() { return mIntensity; }

    typedef enum                // How to interpret Position:
    {
        F_GLOBAL,               //  global coordinate system
        F_CAMERA,               //  camera coordinates
        F_LOCAL                 //  local coords where appearance is attached
    } PositionType;

    void SetPosition(HPoint3 position, PositionType type) {
        mPosition = position;
        mPositionType = type;
    }
    inline HPoint3      GetPosition() { return mPosition; }
    inline PositionType GetPositionType() { return mPositionType; }

    inline void    SetGlobalPosition(HPoint3 position)
                     {mGlobalPosition=position;}
    inline HPoint3 GetGlobalPosition() { return mGlobalPosition; }
    inline float * GetGlobalPositionF() { return (float*)(&mGlobalPosition); }

    // Appends a copy of the lights in one list (*src) to
    // another list (*dst).
    static void CopyList(class UtLList<MgLight> *dst,
                         class UtLList<MgLight> *src,
                         int mergeflag);

    inline void SetPrivate(int p) { mPrivate = p; }
    inline int  GetPrivate() { return mPrivate; }

    inline void SetChanged(int changed) { mChanged = (short)changed; }
    inline int  GetChanged() { return mChanged; }


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
    MgColor         mColor;
    HPoint3         mPosition;       // application-specified light position
    HPoint3         mGlobalPosition; // real light position; set/used only by mg
    float           mIntensity;
    PositionType    mPositionType;   // was "location"
    short           mChanged;
    int             mPrivate;

    void CopyDataFrom(MgLight *src); // was LtCopy
    void CopyAllFrom(MgLight *src);  // was LtMerge
};






#endif // MGLIGHT_H

