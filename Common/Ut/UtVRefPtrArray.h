//-*-C++-*-
#ifndef UTVREFPTRARRAY_H
#define UTVREFPTRARRAY_H

#include "UtVArray.h"
#include "UtMath.h"

// Item should always be a pointer to a refrence counted object.

template <class Item>
class UtVRefPtrArray : public UtVArray<Item>
{
public:
    UtVRefPtrArray(unsigned int size = 0);
    UtVRefPtrArray(unsigned int size, Item *Buffer, unsigned int nValid = -1);
    UtVRefPtrArray(const UtVRefPtrArray<Item> &array);
    virtual ~UtVRefPtrArray();

    virtual UtVRefPtrArray<Item> &operator=(const UtVRefPtrArray<Item> &array);

    virtual Item operator[](unsigned int i) const
    {
        if (i <= mCount)  // Remember that the array is padded with a trailing NULL
            return( mpBuffer[i] );
        else 
        {
            throw new UtException(UtException::ERROR,
                "UtVRefPtrArray operator[] index (%1d) out of bounds", i);
            return(NULL); // Must return something or VC++ complains.
        }
    }

    void AppendItem(const Item &newItem);
    void ReplaceItem(unsigned int index, const Item &newItem);
    void RemoveItem(unsigned int index);
    void Resize(unsigned int size);
    virtual void Clear(unsigned int size = 0);
};

template <class Item>
UtVRefPtrArray<Item>::UtVRefPtrArray(unsigned int size)
    : UtVArray<Item>(size)
{
}

template <class Item>
UtVRefPtrArray<Item>::UtVRefPtrArray(unsigned int size,
                                     Item *Buffer,
                                     unsigned int nValid) : UtVArray<Item>(size, Buffer, nValid)
{
// Changed this to call the base class constructor.
// jcm - 12/10/97

//    mSize = size;
//    mpBuffer = new Item[mSize];

//    int end;
//    if (nValid < 0)
//        end = size;
//    else
//        end = UtMathMIN(size, nValid);

    for (unsigned int i = 0; i < size; i++)
        ::NewRef(mpBuffer[i]);

//    mCount = 0;
}

template <class Item>
UtVRefPtrArray<Item>::UtVRefPtrArray(const UtVRefPtrArray<Item> &array) : UtVArray<Item>(array)
{
// Changed this to call the base class constructor.
// jcm - 12/10/97

//    mSize = array.mSize;
//    mpBuffer = new Item[mSize];
//    unsigned int i;

    for (unsigned int i = 0; i < mSize; i++)
        ::NewRef(mpBuffer[i]);

//    mCount = array.mCount;
}

template <class Item>
UtVRefPtrArray<Item> &UtVRefPtrArray<Item>::operator=(const UtVRefPtrArray<Item> &array)
{
// Changed this to call the base class operator.
// jcm - 12/10/97
/*
    unsigned int i;

    for (i = 0; i < mCount; i++)
    {
        mpBuffer[i]->DeleteRef();
    }

    delete [] mpBuffer;
        
    mSize = array.mSize;
    mpBuffer = new Item[mSize];

    for (i = 0; i < mSize; i++)
        mpBuffer[i] = ::NewRef(array[i]);

    mCount = array.mCount;

    return(*this);
*/
  unsigned int i;

    for (i = 0; i < mCount; i++)
    {
        mpBuffer[i]->DeleteRef();
    }

    for (i = 0; i < mSize; i++)
        ::NewRef(array.mpBuffer[i]);

    UtVArray<Item>::operator=(array);

    return(*this);
}

template <class Item>
UtVRefPtrArray<Item>::~UtVRefPtrArray()
{
    for (unsigned int i = 0; i < mCount; i++)
        if (mpBuffer[i]) ::DeleteRef(mpBuffer[i]);

    // UtVArray destructor does "delete [] mpBuffer";
}

template <class Item>
void UtVRefPtrArray<Item>::Resize(unsigned int size)
{
    Item *tmp = mpBuffer;
    mpBuffer = new Item[size];
    unsigned int i;

    for (i = 0; i < UtMathMIN(mSize, size); i++)
        mpBuffer[i] = tmp[i];

    // For those that are getting deleted, decrement their references.
    for (i = size; i < mCount; i++)
    {
        if (mpBuffer[i]) ::DeleteRef(tmp[i]);
        mCount--;
    }

    // delete [] tmp;
    // '[]' taken out because this crashes on Unix, sez Lori.
    // ask John about it !!
    // mbp Wed Dec 03 11:56:30 1997: put [] back it.  It
    // really should be there. We'll have to figure out what's
    // wrong with the Unix version.
    delete [] tmp;

    mSize = size;
}

template <class Item>
void UtVRefPtrArray<Item>::ReplaceItem(unsigned int index, const Item &newItem)
{
    if (index < mCount)
    {
        if (mpBuffer[index]) ::DeleteRef(mpBuffer[index]);
        mpBuffer[index] = ::NewRef(newItem);
    }
    else
    {
        // If the index is beyond the end of the list, simply append it.
        // Maybe we want to throw an exception here -- not sure.  jcm 12/3/97
        AppendItem(newItem);
    }
}

template <class Item>
void UtVRefPtrArray<Item>::AppendItem(const Item &newItem)
{
    mCount++;

    if (mCount >= mSize)
        Resize(mSize + mBlockSize); 
        
    mpBuffer[mCount - 1] = ( newItem != NULL ? ::NewRef(newItem) : NULL );
    mpBuffer[mCount] = NULL;
}

template <class Item>
void UtVRefPtrArray<Item>::RemoveItem(unsigned int index)
{
    if (mpBuffer[index]) ::DeleteRef(mpBuffer[index]);

    memcpy(mpBuffer + index, mpBuffer + index + 1, (mCount - (index + 1)) * sizeof(Item));

    mpBuffer[mCount--] = NULL;
}

template <class Item>
void UtVRefPtrArray<Item>::Clear(unsigned int size)
{
    for (unsigned int i=0; i<mCount; ++i) {
        if (mpBuffer[i]) ::DeleteRef(mpBuffer[i]);
    }
    UtVArray<Item>::Clear(size);
}

#endif // UTVREFPTRARRAY_H
