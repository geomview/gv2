//-*-C++-*-
#ifndef UtScalarArray_H
#define UtScalarArray_H

// UtScalarArray.h
//
// template class UtScalarArray<Item>
//
// mbp Thu Nov 06 00:36:26 1997
//
// This is a a variable-length vector class.  The elements of the
// vector should be a scalar type (i.e. not a pointer); my intention
// is that this class will be used for variable-length arrays of ints,
// doubles, floats, etc, although in theory it could be used for more
// complicated (non-pointer) objects too.
//
// Quick summary of usage (using an array of ints as an example):
//
//     UtScalarArray<int> v;    // declare it
//
//     v[0] = 1;                // use it; just start accessing it
//     v[1] = 3;                // with operator [] as if it were
//     v[2] = 5;                // an array; it'll grow as necessary
//
//     v.getCount()             // returns 1 + the highest index
//                              // used so far; i.e. the number of
//                              // elements "used", assuming they're
//                              // inserted seqentially.
//
// There are other member functions for controlling how the array space
// is allocated and how it grows / shrinks.  See below for details.

#include <stdio.h>

template <class Item>
class UtScalarArray {

public:
    // Default constructor.
    UtScalarArray();

    // Construct a new array with a given initial number
    // of entries already allocated.
    UtScalarArray(int initialSize);

    // Construct a new array with a given initial number
    // of entries already allocated, and specify a block size
    // for allocations, all at once.  (See also SetBlockSize().)
    UtScalarArray(int initialSize, int blockSize);

    // Copy Constructor
    UtScalarArray(const UtScalarArray<Item> &array);

    // Destructor
    ~UtScalarArray();

    // Assignment Operator
    UtScalarArray &operator=(const UtScalarArray<Item> &array);

    // Set the size of the blocks in which array elements are
    // allocated.  The array will be sized/resized in such a
    // way that its length is always a multiple of the block size.
    // The default block size is 1.
    void SetBlockSize(int n);

    // Set the size of the array to make sure that it includes
    // room for AT LEAST n elements.  The actual size will be
    // a multiple of the block size.  If there is already room for
    // at least n elements, this does nothing.
    void Resize(int n);

    // Return the current size, i.e. the number of items allocated for.
    int  GetSize();

    // Return 1 + the highest index accessed so far.  If you're using
    // the elements in sequential order (not skipping any), this'll be
    // the same as the number of elements used (hence the name of the
    // function).
    int  GetCount();

    // Trim any extra storage from the end of the array so that
    // the size is just big enough to hold the used elements.
    void Trim();

    // Clear out the array (re-initialize to 0 allocated, 0 used)
    void Clear();

    // Your basic [] access operator.
    Item & operator[] (int n);

    // This item inserts an element into the array, all trailing elements
    // up to mCount - 1 are shifted up by 1.
    void InsertItem(int location, const Item &newItem);


#if 0
    // for debugging only
    void print();
#endif

private:
    Item *mpBase;
    unsigned short int  mSize;
    unsigned short int  mCount;
    unsigned short int  mBlockSize;
    void Realloc(int size);
  
};

#if 0
#include <iostream.h>
template <class Item>
void UtScalarArray<Item>::print()
{
    cout << "UtScalarArray:\n"
         << "  mBlockSize    = " << mBlockSize    << "\n"
         << "  mSize         = " << mSize         << "\n"
         << "  mCount      = " << mCount      << "\n";
    if (mCount > 0)
    {
        cout << "  {";
        for (int i=0; i<mCount; ++i)
        {
            cout << mpBase[i];
            if (i<mCount-1) cout << ", ";
        }
        cout << "}\n";
    }
    cout << "\n";
}
#endif

template <class Item>
void UtScalarArray<Item>::Clear()
{
    if (mpBase) { delete [] mpBase; }
    mpBase = NULL;
    mCount = 0;
    mSize = 0;
}

template <class Item>
UtScalarArray<Item>::UtScalarArray()
{
    mBlockSize = 1;
    mCount = 0;
    mpBase = NULL;
    mSize = 0;
}

template <class Item>
UtScalarArray<Item>::UtScalarArray(int n)
{
    mBlockSize = 1;
    mpBase = NULL;
    mSize = 0;
    mCount = 0;
    if (n > 0)
    {
        Resize(n);
    }
}

template <class Item>
UtScalarArray<Item>::UtScalarArray(int n, int blockSize)
{
    mpBase = NULL;
    mSize = 0;
    mBlockSize = blockSize;
    mCount = 0;
    if (n > 0)
    {
        Resize(n);
    }
}

template <class Item>
UtScalarArray<Item>::UtScalarArray(const UtScalarArray<Item> &array)
{
    mSize = array.mSize;
    mBlockSize = array.mBlockSize;
    mCount = array.mCount;
    
    mpBase = new Item[mSize];
    for (int i = 0; i < mCount; i++)
        mpBase[i] = array.mpBase[i];
}   

template <class Item>
UtScalarArray<Item>::~UtScalarArray()
{
    if (mpBase) { delete [] mpBase; }
}

template <class Item>
UtScalarArray<Item> &UtScalarArray<Item>::operator=(const UtScalarArray<Item> &array)
{
    if (mpBase) delete [] mpBase;

    mSize = array.mSize;
    mBlockSize = array.mBlockSize;
    mCount = array.mCount;
    
    mpBase = new Item[mSize];
    for (int i = 0; i < mCount; i++)
        mpBase[i] = array.mpBase[i];

    return(*this);
}   

template <class Item>
int UtScalarArray<Item>::GetSize()
{
    return mSize;
}

template <class Item>
int UtScalarArray<Item>::GetCount()
{
    return mCount;
}

template <class Item>
void UtScalarArray<Item>::SetBlockSize(int n)
{
    mBlockSize = n;
}

template <class Item>
void UtScalarArray<Item>::Resize(int n)
{
    if (n > mSize)
    {
        int newNumAllocated = ( (n - 1) / mBlockSize + 1 ) * mBlockSize;
        Realloc(newNumAllocated);
        mSize = newNumAllocated;
    }
}

template <class Item>
void UtScalarArray<Item>::Realloc(int size)
{
    Item *pOldBase = mpBase;
    mpBase = new Item[size];
    if (pOldBase != NULL)
    {
        for (int i=0; i<mCount && i<size; ++i)
        {
            mpBase[i] = pOldBase[i];
        }
        delete [] pOldBase;
    }
    mSize = size;
}

template <class Item>
void UtScalarArray<Item>::Trim()
{
    if (mSize > mCount)
    {
        Realloc(mCount);
    }
}

template <class Item>
inline Item & UtScalarArray<Item>::operator[] (int n)
{
    if (n >= mSize) Resize(n+1);
    if (n >= mCount) mCount = n+1;
    return mpBase[n];
}

template <class Item>
inline void UtScalarArray<Item>::InsertItem(int location, const Item &newItem)
{
    if (++mCount >= mSize) Resize(mSize + mBlockSize);
    
    Item *Base = mpBase + location;
    memcpy(Base + 1, Base, (mCount - (location + 1)) * sizeof(Item));
    mpBase[location] = newItem;
}

#endif // UtScalarArray_H
