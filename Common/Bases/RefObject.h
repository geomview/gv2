//-*-C++-*-
#ifndef REFOBJECT_H
#define REFOBJECT_H

// template class RefObject:
//       Base class for reference-counted objects.
//
// 1. Any class that is to be reference counted should be declared
//    to be a "virtual public RefObject" (or should inherit from
//    such a class).  The virtual is necessary to insure that the object
//    has just one RefObject base, in case of multiple inheritance.
// 
// 2. Use the global (template) functions ::NewRef() and ::DeleteRef()
//    to obtain and release references to a reference counted object.
//    They both take a pointer to the object in question.  ::NewRef()
//    returns that pointer back, after incrementing the reference count.
//    ::DeleteRef() returns void, after decrementing the reference count,
//    and possibly calling operator delete on the object.   If it
//    does call operator delete, that triggers a call to the object's
//    destructor function, if it has one.
// 
// 3. Think of ::NewRef() and ::DeleteRef() as analogous to "new"
//    and "delete"; you use them in place of these lower level functions,
//    except that the first time an object is created, "new" has to
//    be called.  So the normal life cycle of a RefObject looks something
//    like this:
// 
//      class MyObject : virtual public RefObject {
//      ...
//      };
// 
//      MyObject *obj = new MyObject;
//         // This allocates a new object and sets its reference count to
//         // 1 (the call to "new" triggers a call to the RefObject
//         // constructor, which initializes the reference count).
// 
//      ...
// 
//      MyObject *pointer = ::NewRef(obj);
//         // Create a new reference to the object.
// 
//      ...
// 
//      ::DeleteRef(pointer);
//         // Release that reference
// 
//      ...
//        // In general there can be any number of calls to ::NewRef()
//        // and ::DeleteRef().  The rule is that over the life of the
//        // object the total number of calls to ::DeleteRef() should be
//        // equal to the total number of calls to ::NewRef(), plus one
//        // (for the initial "new").
// 
// 4. The tricky part of reference counting is to make sure that
//    the calls to ::NewRef() and ::DeleteRef() stay balanced.
//    The best rule to follow to insure this seems to be to AVOID
//    PASSING THE RESPONSIBILITY TO CALL ::DeleteRef() UP OR DOWN
//    THE CALL STACK.  Specifically:
// 
//    4a. Design code so that the ::DeleteRef() corresponding to a
//        ::NewRef() is at the same "level" in the code.  For example,
//        when implementing a list class which holds references to
//        objects, its code should call ::NewRef() when asked to insert
//        an object into the list, and it should call ::DeleteRef() when
//        it's finished with that object.  This almost certainly means
//        that the list class needs to have a destructor which calls
//        ::DeleteRef() on any objects it still contains.  There may also
//        need to be other ::DeleteRef() calls in the list's
//        implementation, for example when an element in the list is
//        removed.  The important thing is that client code for the
//        list class should not have to think about managing the list's
//        reference counting; the list will take care of it.
//        
//    4b. Avoid writing functions which call ::NewRef()
//        on an object and which then expect their caller to call
//        ::DeleteRef() to release that reference.  The only functions
//        which should do this are ones that by their very nature create
//        a new object (such as the object parsing functions).
//        (There are currently a few more functions that do this,
//        in particular the various Merge functions.)  In any case,
//        any function which does this should DOCUMENT VERY LOUDLY,
//        with comments near both the declaration (in the header file)
//        and the implementation (in the .cpp file), the fact that
//        the caller should call ::DeleteRef() on the returned object.
// 
//    4c. Avoid writing functions which take an argument which is
//        a pointer to a RefObject and which expect that
//        they can take over that reference without calling ::NewRef().
//        I can't think of any reason to have such a function.  If a
//        function needs to store a reference to an object, it should get
//        a new one by calling ::NewRef(), and some corresponding piece
//        of code in the same class should call ::DeleteRef().
// 
//    4d. Whenever writing a call to a function that takes a pointer
//        to a RefObject, assume that the function will create its
//        own reference to the object if it needs one.  For example:
// 
//            GeomList *list;
//            ...
//            GeomThing *thing = GeomLoad("file.thing");
//            list->AppendItem(thing);
//            ::DeleteRef(thing);
// 
//        We need to call ::DeleteRef(thing) in this fragment because
//        GeomLoad returned a new reference to a GeomThing, and although
//        GeomList stores a reference, it stores one that it increments
//        itself, so we need to release the one that GeomLoad() returned.

#include "TypeObject.h"

class RefObject : virtual public TypeObject
{
    TYPE_DECLARE_TYPEINFO(RefObject);

private:
    int mRefCount;

public:
    RefObject();
    virtual ~RefObject() {}

    void AddRef();
    void DeleteRef();

    int RefCount() { return mRefCount; }

};

template <class Item>
inline Item *NewRef(Item *obj)
{
    obj->AddRef();
    return obj;
}

template <class Item>
inline void DeleteRef(Item *obj)
{
    obj->DeleteRef();
}

#endif /* REFOBJECT_H */
