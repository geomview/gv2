//-*-C++-*-
#ifndef UTLVEC_H
#define UTLVEC_H

//
//  STOP STOP STOP STOP
//
//  This class seems to be about the same as UtScalarArray(), and
//  UtScalarArray() seems better designed.  Use it instead.  I'm
//  keeping this file around for a while before discarding it
//  completely, in case there really does turn out to be a difference.
//  mbp Fri Feb  2 15:44:32 2001
//
#if DONT_USE_UTLVEC

// template class UtLVec<Item>
//	prerequisites: none
//
// This file gives a template for a variable-length vector class.
//
// The 'L' in the name of this class is because it's implemented
// using linked lists, I think.

#include <stdio.h>

template <class Item>
class UtLVec {

private:
  Item *base;
  int	num_allocated;
  int	blocksize;
  
public:
  UtLVec();
  UtLVec(int n);
  UtLVec(int n, int blocksize);
  ~UtLVec();
  void SetSize(int n);
  void SetBlockSize(int n);
  int  getSize();
  Item & operator[] (int n);
};

template <class Item>
UtLVec<Item>::UtLVec()
{
  blocksize = 1;
  base = NULL;
  num_allocated = 0;
}

template <class Item>
UtLVec<Item>::UtLVec(int n)
{
  blocksize = 1;
  if (n > 0) {
    SetSize(n);
  } else {
    base = NULL;
    num_allocated = 0;
  }

}

template <class Item>
UtLVec<Item>::UtLVec(int n, int blocksize)
{
  this->blocksize = blocksize;
  if (n > 0) {
    SetSize(n);
  } else {
    base = NULL;
    num_allocated = 0;
  }
}

template <class Item>
UtLVec<Item>::~UtLVec()
{
  if (base) { delete [] base; }
}

template <class Item>
int UtLVec<Item>::getSize()
{
  return num_allocated;
}

template <class Item>
void UtLVec<Item>::SetBlockSize(int n)
{
  blocksize = n;
}

template <class Item>
void UtLVec<Item>::SetSize(int n)
{
  if (n > num_allocated) {
    int new_num_allocated = ( (n - 1) / blocksize + 1 ) * blocksize;
    Item *old_base = base;
    base = new Item[new_num_allocated];
    if (old_base != NULL) {
      for (int i=0; i<num_allocated; ++i) {
	base[i] = old_base[i];
      }
    }
    num_allocated = new_num_allocated;
  }
}

template <class Item>
inline Item & UtLVec<Item>::operator[] (int n)
{
  if (n >= num_allocated) SetSize(n+1);
  return base[n];
}

#endif // DONT_USE_UTLVEC

#endif // UTLVEC_H
