//-*-C++-*-
#ifndef UTLSTACK_H
#define UTLSTACK_H

// template class UtLStack<Item>
//	prerequisites:
//	    compile: UtException.h
//	       link: UtException.o
//
// This file gives a template for a stack class.  Each node in
// the stack contains an (instance of) an object of type (or class)
// Item.  (The stack node contains the actual Item object, not a
// pointer to it.)
//
// Doing a "push" operation on the stack pushes the existing nodes
// on the stack down one level and creates a top node with an empty
// Item object. You then put data into that top node using a pointer
// to it (returned by the Push() call, or by a subsequent call to Top()).
// 
// Popping the stack discards the top node and the Item object
// contained therein.
//
// The 'L' in the name of this class is because it's implemented
// using linked lists, I think.

#include <stdio.h>
#include "UtException.h"

// UtLStackNode is the type used to store nodes in the stack; it's not used
//   outside the UtLStack class but has to be declared outside it because
//   it's a template.  (Is there a better way to do this?  It'd be nice not
//   to have to introduce another global name for this structure.)
template <class Item>
struct UtLStackNode {
  Item          m_item;
  UtLStackNode   *m_next_p;
};

template <class Item>
class UtLStack {

private:
  UtLStackNode<Item> *m_top_p;
  int m_depth;

public:
  // CONSTRUCTORS/DESTRUCTORS
  UtLStack();
  ~UtLStack();


  // MANIPULATORS
  
  // Push the stack; creates a new "top" node which currently has no data
  //   in it.  Returns a pointer to the new Item on the top of the stack.
  Item *Push();

  // Pop the stack, discarding (and deleting) the top node.
  void Pop();


  // ACCESSORS

  // Return a pointer to the top item in the stack.
  Item *Top();

  // Return a pointer to the second item in the stack (just
  //   under the top)
  Item *Second();

  // Return the current depth of the stack (0 means its empty)
  int Depth();

  // Test whether the stack is empty
  int Empty();
};

template <class Item>
inline UtLStack<Item>::UtLStack()
{
  m_top_p = NULL;
  m_depth = 0;
}

template <class Item>
inline Item *UtLStack<Item>::Push() {
  UtLStackNode<Item> *n = new UtLStackNode<Item>;
  n->m_next_p = m_top_p;
  m_top_p = n;
  ++m_depth;
  return &(m_top_p->m_item);
}

template <class Item>
inline Item *UtLStack<Item>::Top() {
  if (m_top_p==NULL) { return NULL; }
  return &(m_top_p->m_item);
}

template <class Item>
inline Item *UtLStack<Item>::Second() {
  if (m_top_p==NULL) { return NULL; }
  if (m_top_p->m_next_p==NULL) { return NULL; }
  return &(m_top_p->m_next_p->m_item);
}

template <class Item>
inline void UtLStack<Item>::Pop() {
  if (m_top_p==NULL) throw new UtException(UtException::ERROR, "attempt to pop empty UtLStack");
  UtLStackNode<Item> *n = m_top_p;
  m_top_p = n->m_next_p;
  delete n;
  --m_depth;
}

template <class Item>
inline int UtLStack<Item>::Depth() {
  return m_depth;
}

template <class Item>
inline int UtLStack<Item>::Empty() {
  return (m_depth==0);
}


template <class Item>
UtLStack<Item>::~UtLStack() {
  if (m_top_p != NULL) {
    UtLStackNode<Item> *x, *n = m_top_p;
    do {
      x = n->m_next_p;
      delete n;
      n = x;
    } while (n != NULL);
  }
}

#endif // UTLSTACK_H
