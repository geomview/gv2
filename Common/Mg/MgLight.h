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
    MgLight() { Init(); }
    ~MgLight();

    inline void      SetAmbient(MgColor color) { mAmbient = color; }
    inline void      SetAmbient(double r, double g, double b) {
        mAmbient.SetRGB(r,g,b);
    }
    inline MgColor   GetAmbientColor() { return mAmbient; }

    inline void      SetColor(MgColor color) { mColor = color; }
    inline void      SetColor(double r, double g, double b) {
        mColor.SetRGB(r,g,b);
    }
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
    void SetPosition(float x, float y, float z, float w,
                     PositionType type) {
        mPosition.x = x;
        mPosition.y = y;
        mPosition.z = z;
        mPosition.w = w;
        mPositionType = type;
    }
    inline HPoint3      GetPosition() { return mPosition; }
    inline PositionType GetPositionType() { return mPositionType; }

    inline void    SetGlobalPosition(HPoint3 position)
                     {mGlobalPosition=position;}
    inline HPoint3 GetGlobalPosition() { return mGlobalPosition; }
    inline float * GetGlobalPositionF() { return (float*)(&mGlobalPosition); }

    MgLight * CopyList(int mergeflag);
    void      DeleteList();

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

