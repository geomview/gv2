//-*-C++-*-
#ifndef MGAPPEARANCESTACK_H
#define MGAPPEARANCESTACK_H

#include "UtLStack.h"
#include "MgAppearance.h"
#include "MgMaterial.h"
#include "MgLighting.h"

class MgAppearanceStackNode {
private:
    MgAppearance *mpAp;
    unsigned int mAppearanceSeq;
    unsigned int mMaterialSeq;
    unsigned int mLightingSeq;
public:
    MgAppearanceStackNode() {
        mpAp = NULL;
        mAppearanceSeq =
        mMaterialSeq   =
        mLightingSeq   = 0;
    }
    ~MgAppearanceStackNode() {
        if (mpAp) ::DeleteRef(mpAp);
    }
    MgAppearance *GetAppearance() { return mpAp; }
    void SetAppearance(MgAppearance *ap) {
        if (mpAp) ::DeleteRef(mpAp);
        mpAp = ::NewRef(ap);
    }
    int GetAppearanceSeq() { return mAppearanceSeq; }
    int GetMaterialSeq()   { return mMaterialSeq;   }
    int GetLightingSeq()   { return mLightingSeq;   }
    void AppearanceSeqIncr() { ++mAppearanceSeq; }
    void MaterialSeqIncr()   { ++mMaterialSeq;   }
    void LightingSeqIncr()   { ++mLightingSeq;   }
 };

class MgAppearanceStack : public UtLStack<MgAppearanceStackNode> {

    // This class implements a stack of appearances for Mg to use in
    // the course of drawing a tree of Geoms.  This stack starts out
    // with one appearance in it, and always has at least one
    // appearance in it. That appearance, called the "base
    // appearance", cannot be popped from the stack.  It has every
    // field set to some valid value (and hence can be used for
    // drawing).  If you want to use a different base appearance, just
    // call Merge() to merge in the differences you want before
    // pushing the stack; that has the effect of changing the base
    // appearance.

public:
    //
    // Creators
    //
    MgAppearanceStack();
    ~MgAppearanceStack();


    //
    // MANIPULATORS
    //
  
    // Push the stack; pushes a duplicate of the current top node onto
    // the stack, and returns a pointer to the new appearance on the
    // top.
    MgAppearanceStackNode *Push();

    // Merge the given appearance in with the one on the top of the
    // stack, creating a new appearance which has the settings from
    // whichever fields of *ap are valid, and inherits all others from
    // the existing stack-top appearance.  Does not modify *ap.
    void Merge(const MgAppearance *ap);

    // Pop the stack, discarding (and deleting) the top node.
    void Pop();


    //
    // ACCESSORS
    //

    // Return a pointer to the top appearance on the stack.
    MgAppearanceStackNode *Top();

    // Return a pointer to the second appearance on the stack (just
    // under the top).  Returns NULL if the stack is only 1 deep.
    MgAppearanceStackNode *Second();

    //
    // Inherited from UtLStack:
    //
    // Return the current depth of the stack (0 means its empty)
    // int Depth();
    //
    // Test whether the stack is empty
    // int Empty();
};

#endif // MGAPPEARANCESTACK_H
