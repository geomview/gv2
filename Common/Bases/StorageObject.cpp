
// Implementations for the StorageObject base class.

#include "StorageObject.h"

TYPE_IMPLEMENT_TYPEINFO(StorageObject);

int StorageObject::Load(char *fName)
{
	IoDataStream s(fName, "r");

	return(Load(s));
}

int StorageObject::Save(char *fName)
{
	IoDataStream s(fName, "r");

	return(Load(s));
}
