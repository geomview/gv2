//-*-C++-*-
#ifndef UTLLIST_H
#define UTLLIST_H

#include <stdio.h>
#include <string.h>
#include "UtException.h"

// template class UtLList<Item>
//	prerequisites:
//	    compile: UtException.h
//	       link: UtException.o
// 
// This is a linked list template class.  It is intended for
// situations where you have another class (or type) that you want to
// store in a linked list.  This template provides a list class based
// on that class (or type), saving you from having to keep track of
// the "next" pointer, and also of course from implementing the list
// access and manipulation functions.
// 
// Usage is as follows:
// 
//   UtLList<Item> list;
//     // Declares a list which holds objects of class (or type) Item.
//     // The list holds actual Item objects, not pointers to them.
//     // Item itself could be a pointer type, though, in which case it's
//     // up to you to make sure the actual objects get allocated and freed
//     // at the right times.  In particular, the UtLList destructor does
//     // not call any Item * destructors if Item is a pointer type.
//   
//   Item item;
//   ...
//   list.AppendItem(item)
//     // Appends a copy of item to the list.  Implemented so as to avoid
//     // unnecessary copy operations (the argument is actually a
//     // reference to an Item, so only the reference is copied onto
//     // the stack for the call, and the function makes a single copy
//     // from that.)
//
//   Item *pItem;
//   ... <set pItem using an UtLListIterator<Item> object> ...
//   list.RemoveItem(pItem)
//     // Call this, with an Item * pointer retured by an iterator (see
//     // below), to remove an item from the list.  Note that once you do
//     // this, the ++ operator on the iterator won't work for this item
//     // because it will have been removed from the list.  The way to
//     // deal with this, if you want to continue using the iterator to
//     // step through the list after removing the current item, is to
//     // do the ++ before calling list.RemoveItem().  For example:
//     //
//     //    UtLListIter<Item> it(list);
//     //    while (it)
//     //    {
//     //        Item *pItem = it();
//     //        ++it; // advance iterator before removing current item
//     //        if (<this item is to be removed>)
//     //        { 
//     //            list.RemoveItem(pItem);
//     //        }
//     //    }
//     //
//     // (Note: you can do whatever tests you want with the Item *pItem
//     // pointer to determine which item in the list you're looking at.)
//
//   UtLListIter<Item> it(list);
//     // Declare an iterator for stepping through the items in the list
//   
//   if (it) { ... }
//     // Test whether there are more items in the list for this iterator
//   
//   Item *PItem = it();
//     // Get a pointer to the iterator's current item in the list.  You
//     // can use this pointer to read and/or write to the item, but
//     // don't delete it.  This pointer points to the actual copy stored
//     // in the list.
//   
//   ++it;
//     // Advance the iterator to the next item in the list
//
//   it.Reset();
//     // Reset iterator to start at beginning of list again.  It's OK if
//     // the contents of the list have changed since the iterator was
//     // constructed; Reset() always resets the iterator to the current
//     // head of the list.
//
// The UtLListIter class is designed for efficient use in loops like
// the example given above in the discussion of RemoveItem(), or like
// the following for loop:
//
//   UtLList<Item> list;
//   ...
//   for (UtLListIter<Item> it(list); it; ++it)
//   {
//       Item *pItem = it();
//       // Do something with pItem
//   }
//   
////////////////////////////////////////////////////////////////////////

// forward declaration:
template <class Item>
class UtLListIter;

template <class Item>
class UtLList 
{
public:
    UtLList() { mpHead = mpTail = NULL; }
    ~UtLList();

    // Append an item to the list.  We declare this to take an
    // Item reference rather than a pointer, because:
    //   1. It's really storing a copy of the Item object itself,
    //      not a pointer to it, so declaring it to take an Item *
    //      pointer might be misleading.
    //   2. Since it has to make a copy of the object, passing
    //      in a reference saves an extra copy operation that
    //      would happen if the argument were just the Item object
    //      itself.
    void AppendItem(const Item &item);

    // Remove an Item from the list.  This takes a pointer to an Item
    // known to be in the list.  IMPORTANT: this pointer must be the
    // address of one of the items stored in the list.  This is not
    // the same as the address of an item passed to AppendItem().  To
    // get the Item * pointer to pass to RemoveItem(), use a
    // UtLListIter object to access items in the list.
    int RemoveItemByPointer(Item *pItem);

    // The following method searches the list for the item to remove,
    // and then removes it.  Notice that it takes an Item rather than
    // an Item*.  This will work best, of course, if Item is a scalar
    // object, a pointer or a class with an overloaded operator=.
    int RemoveItemByContents(const Item &Item);

    // Remove all items from the list
    void Clear();

private:
    struct UtLListNode {
        Item mItem;
        UtLListNode *mpNext;
    };
    UtLListNode *mpHead;
    UtLListNode *mpTail;
    friend class UtLListIter<Item>;

};

template <class Item>
UtLList<Item>::~UtLList() 
{
    if (mpHead != NULL) 
    {
        UtLListNode *x, *n = mpHead;
        do 
        {
            x = n->mpNext;
            delete n;
            n = x;
        } while (n != NULL);
    }
}

template <class Item>
void UtLList<Item>::AppendItem(const Item &item)
{
    if (mpTail == NULL) 
    {
        mpHead = mpTail = new UtLListNode;
    } 
    else 
    {
        mpTail = (mpTail->mpNext = new UtLListNode);
    }
    mpTail->mItem = item;
    mpTail->mpNext = NULL;
}

template <class Item>
int UtLList<Item>::RemoveItemByPointer(Item *pItem)
{
    // If the list is empty, give up immediately
    if (mpHead == NULL) return 0;

    // If the item to be deleted is the head item, delete it
    // and reset the head to be the next item in the list.
    // Also reset the tail pointer, if it was pointing to this
    // node.
    if (pItem == &(mpHead->mItem))
    {
        UtLListNode *oldNode = mpHead;
        mpHead = oldNode->mpNext;
        if (mpTail == oldNode) mpTail = oldNode->mpNext;
        delete oldNode;
        return 1;
    }

    // Otherwise, search through the list looking for the item,
    // and remove it.  Be sure to reset the tail pointer, if
    // it turns out that the removed item is the last one in
    // the list.
    UtLListNode *node = mpHead;
    UtLListNode *prev = NULL;
    while (node->mpNext != NULL)
    {
        if (pItem == &(node->mpNext->mItem))
        {
            UtLListNode *oldNode = node->mpNext;
            node->mpNext = oldNode->mpNext;
            if (mpTail == oldNode) mpTail = prev;
            delete oldNode;
            return 1;
        }
        else
        {
            prev = node;
            node = node->mpNext;
        }
    }
    // If we got this far, it wasn't in the list
    return 0;
}

template <class Item>
int UtLList<Item>::RemoveItemByContents(const Item &item)
{
    if (mpHead == NULL) return 0;

    if (item == (mpHead->mItem))
    {
        UtLListNode *oldNode = mpHead;
        mpHead = oldNode->mpNext;
        if (mpTail == oldNode) mpTail = oldNode->mpNext;
        delete oldNode;
        return 1;
    }

    UtLListNode *node = mpHead;
    UtLListNode *prev = NULL;
    while (node->mpNext != NULL)
    {
        if (item == (node->mpNext->mItem))
        {
            UtLListNode *oldNode = node->mpNext;
            node->mpNext = oldNode->mpNext;
            if (mpTail == oldNode) mpTail = prev;
            delete oldNode;
            return 1;
        }
        else
        {
            prev = node;
            node = node->mpNext;
        }
    }
    return 0;
}

template <class Item>
void UtLList<Item>::Clear()
{
    UtLListNode *next, *node = mpHead;
    while (node)
    {
        next = node->mpNext;
        delete node;
        node = next;
    }
    mpHead = mpTail = NULL;
}


template <class Item>
class UtLListIter {
private:
    UtLList<Item>::UtLListNode *mpCurrent;
    UtLList<Item>::UtLListNode *mpPrevious;
    UtLList<Item> *mpList;
public:
    UtLListIter(UtLList<Item> & list) {
        mpList = &list;
        Reset();
    }
    ~UtLListIter() {}

    // The following example shows the intended use for the operators
    // below:
    //   for (UtLListIter<Item> it(&UtLList); it; ++it) {
    //     Item *item = it();
    //     // do something with item
    //   }

    // VALID CURRENT ITEM TEST:
    // "cast to void *" operator; used for testing whether we really
    // have a current item in the list. (i.e. is it OK to call the "cast
    // to Item" operator). Should return non-NULL if there are more
    // items, NULL if not.
    operator void *() {
        return mpCurrent;
    }

    // GET CURRENT ITEM:
    // "cast to Item" operator; returns the current item.  This should
    // only be called after a non-NULL return from the "cast to void *"
    // operator above.
    Item * operator()() {
        if (!(mpCurrent)) {
            throw UtException(UtException::ERROR, "UtLListIter has no current value");
        }
        return &(mpCurrent->mItem);
    }

    // ADVANCE TO NEXT ITEM:
    // pre-increment operator; advances to the next item in the list
    Item * operator ++ () {
        mpPrevious = mpCurrent;
        mpCurrent = mpCurrent->mpNext;
        return (Item*)this;
    }

    // REMOVE CURRENT ITEM: 
    // This does an implicit "ADVANCE TO NEXT ITEM" as well; in fact,
    // it's equivalent to that, except that it removes the current
    // item from the list before advancing.
    Item * RemoveCurrentItem() {
        UtLList<Item>::UtLListNode *newCurrent = mpCurrent->mpNext;

        // If there was a previous item, set its mpNext to point to
        // the item after the current one; this eliminates the current
        // one from the list.
        if (mpPrevious) mpPrevious->mpNext = newCurrent;

        // If the current one was the head, update the head pointer
        if (mpList->mpHead == mpCurrent) mpList->mpHead = newCurrent;

        // If the current one was the tail, update the tail pointer
        if (mpList->mpTail == mpCurrent) mpList->mpTail = mpPrevious;

        // delete the item
        delete mpCurrent;

        // advance to the next item:
        mpCurrent = newCurrent;

        return (Item*)this;
    }

    // RESET TO BEGINNING OF LIST
    void Reset() {
        mpCurrent = mpList->mpHead;
        mpPrevious = NULL;
    }
    
};


#endif // UTLLIST_H
