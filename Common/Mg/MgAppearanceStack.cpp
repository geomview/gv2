#include "MgAppearanceStack.h"

MgAppearanceStack::MgAppearanceStack()
{
    MgAppearanceStackNode *pBase = UtLStack<MgAppearanceStackNode>::Push();
    MgAppearance *pAp = new MgAppearance();
    pAp->Default();
    pBase->SetAppearance(pAp);
    ::DeleteRef(pAp);
}

MgAppearanceStack::~MgAppearanceStack()
{
    while (Depth())
    {
        UtLStack<MgAppearanceStackNode>::Pop();
    }
}

MgAppearanceStackNode *MgAppearanceStack::Push()
{
    MgAppearanceStackNode *pOldTop, *pNewTop;
    pOldTop = UtLStack<MgAppearanceStackNode>::Top();
    pNewTop = UtLStack<MgAppearanceStackNode>::Push();
    pNewTop->SetAppearance( pOldTop->GetAppearance() );
    return pNewTop;
}

void MgAppearanceStack::Pop()
{
    if (Depth() <= 1)
        throw new UtException(UtException::ERROR,
          "Attempt to pop appearance stack when depth is <= 1 (depth is %1d)",
                              Depth());
    UtLStack<MgAppearanceStackNode>::Pop();
}

MgAppearanceStackNode *MgAppearanceStack::Top()
{
    return UtLStack<MgAppearanceStackNode>::Top();
}

MgAppearanceStackNode *MgAppearanceStack::Second()
{
    if (Depth() >= 2)
    {
        return UtLStack<MgAppearanceStackNode>::Second();
    }
    else
        return NULL;
}

void MgAppearanceStack::Merge(const MgAppearance *ap)
{
   MgAppearanceStackNode *pTop = UtLStack<MgAppearanceStackNode>::Top();
   MgAppearance *pTopAp = pTop->GetAppearance();
   pTopAp = pTopAp->MergeNew(ap);
   pTop->SetAppearance(pTopAp);
   ::DeleteRef(pTopAp);
}
