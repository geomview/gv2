//-*-C++-*-
#ifndef UTVARRAY_H
#define UTVARRAY_H

// This is an array/list class which provides a random read/sequential
// write access.  The idea is that we want to be able to add elements
// to the list one at a time, just as we would a linked list, but then
// we want to be able to efficiently access the i'th element in the
// list.  Notice that operator[] returns a copy of an item, instead of
// a reference, this means that you cannot set an item by this means.
// (If item is a pointer of course, you have full access to the object
// to which it points, but you cannot change the pointer itself.

#include "UtMath.h"

template <class Item>
class UtVArray
{
public:
    UtVArray(unsigned int size = 0);
    UtVArray(unsigned int size, Item *Buffer, unsigned int nValid = -1);
    UtVArray(const UtVArray<Item> &array);
    virtual ~UtVArray();

    virtual UtVArray<Item> &operator=(const UtVArray<Item> &array);

    virtual Item operator[](unsigned int i) const
    {
        if (i < mCount) return(mpBuffer[i]); 
        else
        {
            throw new UtException(UtException::ERROR,
             "Index greater than array size in UtVArray operator []");
        }
        return NULL;
    }


    virtual void AppendItem(Item newItem);
    virtual void RemoveItem(unsigned int index);

    virtual void Resize(unsigned int size);
    virtual int GetSize() { return(mSize); }
    virtual int GetCount() { return(mCount); }
    virtual void Clear(unsigned int size = 0);
    virtual void SetBlockSize(unsigned int size = 5) { if (size > 0) mBlockSize = size; else mBlockSize = 5; }

protected:
    Item *mpBuffer;
    unsigned int mSize;  // the total size of the buffer
    unsigned int mCount;   // the current size of the list
    unsigned int mBlockSize;
};

template <class Item>
void UtVArray<Item>::Clear(unsigned int size)
{
    if (mpBuffer)
    {
        delete [] mpBuffer;
        mpBuffer = NULL;
    }
    mSize = size;
    if (size > 0)
    {
        mpBuffer = new Item[mSize];
        memset(mpBuffer, 0, mSize * sizeof(Item));
    }
    mCount = 0;
}

template <class Item>
UtVArray<Item>::UtVArray(unsigned int size)
{
    mpBuffer = NULL;  // so Clear() doesn't try to delete it !
    mBlockSize = 5;
    Clear(size);
}

template <class Item>
UtVArray<Item>::UtVArray(unsigned int size, Item *Buffer, unsigned int nValid)
{
    mSize = size;
    mpBuffer = new Item[mSize];
    mBlockSize = 5;

    int end;
    if (nValid < 0)
        end = size;
    else
        end = UtMathMIN(size, nValid);

    for (int i = 0; i < size; i++)
    {
        mpBuffer[i] = Buffer[i];
    }
    mCount = 0;
}

template <class Item>
UtVArray<Item>::UtVArray(const UtVArray<Item> &array)
{
    mSize = array.mSize;
    mpBuffer = new Item[mSize];
    mBlockSize = array.mBlockSize;

    for (unsigned int i = 0; i < mSize; i++)
        mpBuffer[i] = array[i];

    mCount = array.mCount;
}

template <class Item>
UtVArray<Item> &UtVArray<Item>::operator=(const UtVArray<Item> &array)
{
    delete [] mpBuffer;
        
    mSize = array.mSize;
    mpBuffer = new Item[mSize];

    for (unsigned int i = 0; i < mSize; i++)
        mpBuffer[i] = array[i];

    mCount = array.mCount;

    return(*this);
}

template <class Item>
UtVArray<Item>::~UtVArray()
{
    delete [] mpBuffer;
}

template <class Item>
void UtVArray<Item>::Resize(unsigned int size)
{
    Item *tmp = mpBuffer;
    mpBuffer = new Item[size];

    for (unsigned int i = 0; i < UtMathMIN(mSize, size); i++)
        mpBuffer[i] = tmp[i];

    delete [] tmp;

    mSize = size;
    if (mCount > mSize)
        mCount = mSize;
}

template <class Item>
void UtVArray<Item>::AppendItem(Item newItem)
{
    if (mCount >= mSize)
        Resize(mSize + mBlockSize);   
        
    mpBuffer[mCount] = newItem;

    mCount++;
}

template <class Item>
void UtVArray<Item>::RemoveItem(unsigned int index)
{
    memcpy(mpBuffer + index, mpBuffer + index + 1, (mCount - (index + 1)) * sizeof(Item));
    mCount--;
}

#endif // UTVARRAY_H
