//-*-C++-*-
#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H

// class TypeObject
// 
// This class implements run-time type checking.  To use:
// 
// 1. Make this class a virtual public base class of a class that you
//    want to be able to do run-time type checking on:
// 
//       class MyClass : virtual public TypeObject
// 
//    Or arrange for TypeObject to be a virtual public base class of some
//    superclass of MyClass; your class doesn't have to be an immediate
//    child of TypeObject in the class heirarchy.  (The 'virtual public'
//    bit arranges that your class has at most one TypeObject in its
//    class ancestry.)
// 
// 2. Put the statement
// 
//      TYPE_DECLARE_TYPEINFO(MyClass);
// 
//    inside your class declaration.  Might as well put it at the top, as
//    in
//       class MyClass : virtual public TypeObject {
//         TYPE_DECLARE_TYPEINFO(MyClass);
//         ... 
//       };
// 
// 3. In your class's implementation (.cpp) file, put a statement like
// 
//         TYPE_IMPLEMENT_TYPEINFO(MyClass);
// 
//    There are actually 5 versions of the TYPE_IMPLEMENT_TYPEINFO macro,
//    depending on how many (immediate) base classes your class has.
//    The case above is is for a situation where the only base class
//    is TypeObject.  If your class also inherits from MyBase, then use
// 
//         TYPE_IMPLEMENT_TYPEINFO1(MyClass, MyBase);
// 
//    If it inherits from both MyBase1 and MyBase2, use
// 
//         TYPE_IMPLEMENT_TYPEINFO2(MyClass, MyBase1, MyBase2);
// 
//    There are also TYPE_IMPLEMENT_TYPEINFO3 and TYPE_IMPLEMENT_TYPEINFO4
//    macros, for the cases of 3 and 4 base classes as well.
// 
//    I (mbp Fri Feb  2 17:04:43 2001) believe that these base classes
//    all have to also inherit from TypeObject as well.  (It's probably
//    OK to have a base class that doesn't inherit from TypeObject, as
//    long as you don't mention that class in TYPE_IMPLEMENT_TYPEINFO*.
//    In this case, that base class is simply invisible to the run-time
//    typeinfo system.)
// 
// 4. Having done all this, you can now get run-time type info about
//    instances of MyClass, as follows:
// 
//         MyClass *obj;
//         ...
//	   // To get a string representing the name of the class
//	   // of an object:
//         printf("obj is of class %s\n", obj->GetType()->mpName);
// 
//         // To check to see if 'otherobj' is a pointer to an
// 	   // object of class MyClass (either directly, or via inheritance):
//         if (otherobj->IsInstanceOf(TYPE_INFO(MyClass))) {
//           ...
//         }
//
//         // To check to see if OneClass inherits from AnotherClass
//	   // (both OneClass and AnotherClass are types):
//         if (TypeInfo::InheritsFrom(TYPE_INFO(OneClass),
//                                    TYPE_INFO(AnotherClass))) {
//           printf("OneClass inherits from AnotherClass\n");
//         }


#include <stdio.h>

#define TYPE_INFO_MAX_TYPES 4

class TypeObject
{
public:
  typedef struct TypeInfo
  {
    char *mpName;
    int mObjectSize;
    TypeInfo *mpBaseClasses[TYPE_INFO_MAX_TYPES];
  } TypeInfo;

  // The following function compares Type1 to Type2 to determine if Type1 is
  // an instance of, or is derived from Type2.
  static int InheritsFrom(const TypeObject::TypeInfo *Type1,
			  const TypeObject::TypeInfo *Type2);

  virtual TypeInfo *GetType() const = 0;

  int IsInstanceOf(const TypeInfo *Type) {
    return(TypeObject::InheritsFrom(GetType(), Type));
  }
};

#define TYPE_INFO(class_name) &(class_name::sClass##class_name) 

#define TYPE_DECLARE_TYPEINFO(class_name) \
    public: \
        static TypeObject::TypeInfo sClass##class_name; \
        virtual TypeObject::TypeInfo *GetType() const

#define TYPE_IMPLEMENT_TYPEINFO(class_name) \
    TypeObject::TypeInfo class_name::sClass##class_name = \
    { #class_name, sizeof(class_name), NULL, NULL, NULL, NULL}; \
    TypeObject::TypeInfo *class_name::GetType() const \
    { return(&(class_name::sClass##class_name)); }

#define TYPE_IMPLEMENT_TYPEINFO1(class_name, base_class_1) \
    TypeObject::TypeInfo class_name::sClass##class_name = \
    { #class_name, sizeof(class_name), TYPE_INFO(base_class_1), \
      NULL, NULL, NULL}; \
    TypeObject::TypeInfo *class_name::GetType() const \
    { return(&(class_name::sClass##class_name)); }

#define TYPE_IMPLEMENT_TYPEINFO2(class_name, base_class_1, base_class_2) \
    TypeObject::TypeInfo class_name::sClass##class_name = \
    { #class_name, sizeof(class_name), TYPE_INFO(base_class_1), \
      TYPE_INFO(base_class_2), NULL, NULL }; \
    TypeObject::TypeInfo *class_name::GetType() const \
    { return(&(class_name::sClass##class_name)); }

#define TYPE_IMPLEMENT_TYPEINFO3(class_name, base_class_1, base_class_2, base_class_3) \
    TypeObject::TypeInfo class_name::sClass##class_name = \
    { #class_name, sizeof(class_name), TYPE_INFO(base_class_1), \
      TYPE_INFO(base_class_2), TYPE_INFO(base_class_3), NULL }; \
    TypeObject::TypeInfo *class_name::GetType() const \
    { return(&(class_name::sClass##class_name)); }

#define TYPE_IMPLEMENT_TYPEINFO4(class_name, base_class_1, base_class_2, base_class_3, base_class_4) \
    TypeObject::TypeInfo class_name::sClass##class_name = \
    { #class_name, sizeof(class_name), TYPE_INFO(base_class_1), \
      TYPE_INFO(base_class_2), TYPE_INFO(base_class_3), TYPE_INFO(base_class_4) }; \
    TypeObject::TypeInfo *class_name::GetType() const \
    { return(&(class_name::sClass##class_name)); }



#endif // TYPEOBJECT_H
