/*
 * Copyright (c) 1990, 1991 Stanford University
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Stanford not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Stanford makes no representations about
 * the suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * STANFORD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
 * IN NO EVENT SHALL STANFORD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * UtUArray implementation.
 */

#include "UtUArray.h"
#include <stdlib.h>
#include <memory.h>

/*****************************************************************************/

UtUArray::UtUArray (int defaultSize) {
    mBufSize = defaultSize;
    mpBuf = new void*[mBufSize];
    mCount = 0;
}

UtUArray::~UtUArray () { delete mpBuf; }

void UtUArray::Check (int index) {
    void** newbuf;

    if (index >= mBufSize) {
        mBufSize = (index+1) * 2;
        newbuf = new void*[mBufSize];
        memcpy(newbuf, mpBuf, mCount*sizeof(void*));
        delete mpBuf;
        mpBuf = newbuf;
    }
}

void UtUArray::Insert (void* v, int index) {
    void** spot;
    index = (index < 0) ? mCount : index;

    if (index < mCount) {
        Check(mCount+1);
        spot = &mpBuf[index];
        memcpy(spot+1, spot, (mCount - index)*sizeof(void*));

    } else {
        Check(index);
        spot = &mpBuf[index];
    }
    *spot = v;
    ++mCount;
}

void UtUArray::Remove (int index) {
    if (0 <= index && index < mCount) {
        --mCount;
        void** spot = &mpBuf[index];
        memcpy(spot, spot+1, (mCount - index)*sizeof(void*));
    }
}

int UtUArray::Index (void* v) {
    for (int i = 0; i < mCount; ++i) {
        if (mpBuf[i] == v) {
            return i;
        }
    }
    return -1;
}

void*& UtUArray::operator[] (int index) {
    Check(index);
    if (index+1 > mCount) mCount = index+1;
    return mpBuf[index];
}
