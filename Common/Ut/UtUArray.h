//
// class UtUArray
//     prerequisites: none
//
// A dynamic array object for storing pointers (?).  Seems similar
// to UtScalarArray; possibly use UtScalarArray instead.
// mbp Fri Feb  2 15:54:16 2001

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
 * UtUArray - dynamic array object.
 */

#ifndef UTUARRAY_H
#define UTUARRAY_H


class UtUArray {
public:
    UtUArray(int = 16);
    ~UtUArray();

    void*& operator[](int index);
    void Insert(void*, int index);
    void Remove(int index);
    int Index(void*);

    int Count();
    void Clear();
private:
    void Check(int index);
private:
    void** mpBuf;
    int mBufSize;
    int mCount;
};

inline int UtUArray::Count () { return mCount; }
inline void UtUArray::Clear () { mCount = 0; }

#define UTUARRAY_CLEAR(UTUARRAY, TYPE)                  \
{                                                       \
    for (int N = (UTUARRAY).Count(); N > 0; N--)        \
    {                                                   \
        TYPE P = (TYPE)(UTUARRAY)[N];                   \
        (UTUARRAY).Remove(N);                           \
        delete P;                                       \
    }                                                   \
}


#endif // UTUARRAY_H
