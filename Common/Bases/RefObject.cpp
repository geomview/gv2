#include "RefObject.h"
#include "UtException.h"

TYPE_IMPLEMENT_TYPEINFO(RefObject);

// Make these inline eventually.  For now, keep as functions for
// debugging.  mbp Tue May 13 11:00:53 1997

void RefObject::DeleteRef()
{
    if ((--mRefCount)==0) 
    {
        delete this;
    }
}

RefObject::RefObject()
{
    mRefCount = 1;
}

void RefObject::AddRef(void)
{
    ++mRefCount;
}
