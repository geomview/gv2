
#include "TypeObject.h"

int TypeObject::InheritsFrom(const TypeObject::TypeInfo *Type1,
			     const TypeObject::TypeInfo *Type2)
{
    if ((Type1 == NULL) || (Type2 == NULL)) 
        return(0);

    if (Type1 == Type2)   // TypeInfo's are static, so we can compare pointers.
        return(1);

    for (int i = 0; i < TYPE_INFO_MAX_TYPES; i++)
    {
        if (InheritsFrom(Type1->mpBaseClasses[i], Type2))
            return(1);
    }
    return(0);
}

