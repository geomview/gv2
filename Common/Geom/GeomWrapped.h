//-*-C++-*-
#ifndef WRAPPED_H
#define WRAPPED_H


// class GeomWrapped
// 
// The GeomWrapped geom class is like the old INST class.  It's used to attach
// appearances and/or transforms to another geom.
//
// OOGL ASCII format:
//      
//

#include "Geom.h"
#include "GeomParent.h"
#include "UtVRefPtrArray.h"
#include "UtScalarArray.h"

class GeomWrapped : public GeomParent
{
    TYPE_DECLARE_TYPEINFO(GeomWrapped);

public:
    GeomWrapped();
    GeomWrapped(Geom *geom)
    { 
      Init();
      AddChild(geom); 
    }

    virtual ~GeomWrapped();

  //    virtual int Load(class IoOldOoglLexer *lex, char *keyword = NULL);
    virtual int Load(class IoOoglLexer *lex, char *keyword = NULL);
    virtual int Save(class IoDataStream *s);
    virtual void Draw(class MgContext *mg);

    virtual void SetTransform(const Transform3 &T);
    virtual Transform3 *GetTransform();

    virtual void SetAppearance(MgAppearance *ap);
    virtual MgAppearance *GetAppearance();

    // Multiply transformation #i by T on either the right or the left.
    virtual void RightMultiply(Transform3 &T);
    virtual void LeftMultiply(Transform3 &T);

    // Clear out all information stored in this GeomWrapped --- remove
    // the child, transforms, appearances, and reset the flags,
    // leaving an empty object ready for reuse.
    void Clear();


    virtual int   GetChildCount();
    virtual Geom *GetChild(int index = 0);
    virtual void  AddChild(Geom *geom);
    virtual void  RemoveChild(Geom *geom);
    virtual int   GetChildIndex(Geom *geom);
    virtual void  RemoveChild(int index = 0);


    enum
    {
        WR_FOURDIM = 0x1,       // Four dimensional
    };

private:
  int           mFlags;
  MgAppearance *mpAppearance;
  Transform3    mTransform;
  Geom         *mpGeom;
  void		Init();
};


#endif // WRAPPED_H
