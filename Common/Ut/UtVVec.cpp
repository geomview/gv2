#include "UtVVec.h"

#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>

// This code assumes that sizeof(unsigned char) == 1.

UtVVec::UtVVec(int sizeOf, void *init, int defaultSize)
{
    mSizeOf = sizeOf / sizeof(unsigned char);
    mBufSize = defaultSize;
    mpBuf = new unsigned char[mBufSize * mSizeOf];

    if (init != NULL)
    {
        mpInit = new unsigned char[1*mSizeOf];
        memcpy(mpInit, init, 1*mSizeOf);
        for (int i=0; i<mBufSize; i++)
            memcpy(&mpBuf[i*mSizeOf], mpInit, 1*mSizeOf);
    }
    else
        mpInit = NULL;

    mCount = 0;
}

UtVVec::~UtVVec()
{
    if (mpBuf) delete mpBuf;
    if (mpInit) delete mpInit;
}

// Grabs the buffer from this class, leaving it with nothing.
// It is now your responsibility to free the buffer.
unsigned char *UtVVec::StealBuf()
{
    unsigned char *steal = mpBuf;
    mBufSize = mCount = 0;
    mpBuf = NULL;
    return steal;
}

// Make sure the buffer is big enough for the given index.
void UtVVec::Check(int index)
{
    // If it's not big enough, ...
    if (index >= mBufSize)
    {
        // Create a new buffer twice as big as the needed size.
        mBufSize = (index+1) * 2;
        unsigned char *newbuf = new unsigned char[mBufSize * mSizeOf];

        // Initialize the new buffer (copy from the old if necessary).
        if (mCount) memcpy(newbuf, mpBuf, mCount*mSizeOf);
        if (mpInit)
            for (int i=mCount; i<mBufSize; i++)
                memcpy(&newbuf[i*mSizeOf], mpInit, 1*mSizeOf);

        // Delete the old buffer and install the new!
        if (mpBuf) delete mpBuf;
        mpBuf = newbuf;
    }
}

// Make sure the buffer is big enough for the given index
// and return a pointer to the element at that index.
unsigned char *UtVVec::Get(int index)
{
    Check(index);
    if (mCount < index+1) mCount = index+1;
    return &mpBuf[index * mSizeOf];
}

// Make sure the buffer is big enough for the given index
// and set the element at that index to the given element (...).
void UtVVec::Set(int index, ...)
{
    va_list alist;
    va_start(alist, index); // 'index' is the argument before the variable arg.
    memcpy(Get(index), alist, mSizeOf);
    va_end(alist);
}

// Make sure the buffer is big enough to insert an element the given index
// and return a pointer to the element at that index.
unsigned char *UtVVec::GetInsert(int index)
{
    unsigned char *spot;
    index = (index < 0) ? mCount : index;

    if (index < mCount)
    {
        Check(mCount+1);
        spot = &mpBuf[index * mSizeOf];
        memcpy(spot+mSizeOf, spot, (mCount - index)*mSizeOf);
    }
    else
    {
        Check(index);
        spot = &mpBuf[index * mSizeOf];
    }

    ++mCount;
    return spot;
}

// Make sure the buffer is big enough to insert an element the given index
// and set the element at that index to the given element (...).
void UtVVec::Insert(int index, ...)
{
    va_list alist;
    va_start(alist, index); // 'index' is the argument before the variable arg.
    memcpy(GetInsert(index), alist, mSizeOf);
    va_end(alist);
}

// Removes the index'th element, shifting data after index down to
// fill the space.
void UtVVec::Remove(int index)
{
    if (0 <= index && index < mCount)
    {
        --mCount;
        unsigned char *spot = &mpBuf[index * mSizeOf];
        memcpy(spot, spot+mSizeOf, (mCount - index)*mSizeOf);
    }
}

// Look up a value and return its index.
#if 0
                 // We would need an argument before the ... to call va_start.
int UtVVec::Index(...)
{
    int i;
    va_list alist;
    va_start(alist, ?);

    for (int i = mCount; --i >= 0; )
        if (memcmp(mpBuf[i*mSizeOf], alist, mSizeOf) == 0)
            break;
    va_end(alist);
    return i;
}
#endif

// Gets rid of unneeded buffer space.
void UtVVec::Trim(int newbufsize)
{
    // Make sure the requested new buffer size if valid.
    if (newbufsize < 0 || newbufsize >= mBufSize) return;

    // Reallocate the buffer.
    unsigned char *newbuf = (unsigned char*)realloc(mpBuf, newbufsize * mSizeOf);

    // As long as it worked, put the new buffer in place.
    if (newbuf != NULL)
    {
        // The old buffer is already destoryed.
        mpBuf = newbuf;
        mBufSize = newbufsize;
        if (mCount > newbufsize) mCount = newbufsize;
    }
}

