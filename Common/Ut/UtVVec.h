//-*-C++-*-
#ifndef UtVVec_CLASS_H
#define UtVVec_CLASS_H


// class UtVVec
//
// by Lori
// 
// A UtVVec is a variable length array or vector.
// The size of the elements in the array is specified when the class instance
// is created.  An optional initial value for the elements may also be
// specified at creation.  The initial size of the allocated buffer is
// 16 elements unless otherwise specified at creation.  The size of the
// buffer grows as necessary.
// 
// The best way to get and set elements of the array is to use the Get(i)
// function.  First it makes sure that at least 'i' elements exist in the
// array.  Then it returns a pointer to the i'th element.  You can then set
// the element by dereferencing the pointer.
//
// The elements are kept in a single continuous buffer.  If you have the
// pointer to the i'th element, you can assume that the i+1'th element begins
// 'sizeOf' bytes after that, PROVIDED THAT YOU HAVE ALREADY CALLED Get ON
// i+1 OR GREATER.
//
// GetInsert(i) inserts a new element at 'i' and then returns a pointer
// to the i'th element.  The elements >= i are shifted down.
//
// Set and Insert can also be used to add elements.  (They call Get and
// GetInsert to get a pointer to the right place.)  However, they are
// not recommended because they don't work for data types that are cast
// to other data types when passed as the argument of a function.
// For example, char's and short's are cast up to int's, and float's are
// cast to double's.  In these cases, when 'sizeOf' bytes are copied from
// the argument, the value will be incorrect.
// This class works best for managing struct's
//
// Here is an example of a possible use of this class:
//
//      struct elem { int i; char c; };
//      struct elem example = { 1, 'a' };
//
//      UtVVec vv(sizeof(elem));
//      *(struct elem*)vv.Get(0) = example;
//      vv.Set(1, example);
//      struct elem *e = (struct elem*)vv.Get(2);
//      e->i = 2; e->c = 'b';
//
// SPECIAL NOTE:  If you don't care whether the elements are on one
// continuous buffer, using the UtUArray class is probably more efficient.
// It keeps an array of pointers.  When it has to resize the buffer, only
// the pointers are copied, not the entire structures.

#include <stddef.h>

class UtVVec {
public:
    UtVVec(int sizeOf = sizeof(char), void *init = NULL, int defaultSize = 16);
    ~UtVVec();

    // Get and Set data.  (see above for more details)
    unsigned char *Get(int index);
    unsigned char *GetInsert(int index = -1);   // <0 appends to the en.
    void Set(int index, ... /* element */);     // These two don't work for
    void Insert(int index, ... /* element */);  // char, short, and float.

    // Removes the index'th element, shifting data after index down to
    // fill the space.
    void Remove(int index);

    // Grab the buffer from this class instance, leaving it with nothing.
    // It is now your responsibility to free the buffer.
    // (It is safe to use this instance for more data afterwards.)
    unsigned char *StealBuf();

    // Gets rid of unneeded buffer space.  Typically you'll want to trim
    // to the size of the valid data, in which case use Trim();
    // But if you want to trim to a different size, use Trim(newbufsize);
    // If you pick a new buffer size that is greater than the current,
    // the function ignores the request.
    void Trim(int newbufsize);
    inline void Trim() { Trim(mCount); }

    inline int SizeOf() { return mSizeOf; }
    inline int GetCount() { return mCount; }
    inline void Clear() { mCount = 0; }

private:
    // Make sure the buffer is big enough for the given index.
    void Check(int index);

private:
    unsigned char *mpBuf;
    unsigned char *mpInit;
    int mBufSize;
    int mCount;
    int mSizeOf;
};


#endif // UtVVec_CLASS_H
