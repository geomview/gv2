//-*-C++-*-

// class UtDynamicListInterface

// This abstract base class defines an interface that all
// "dynamic list" objects should implement.  A "dynamic list"
// object is a list- or array-like object whose size changes
// dynamically.

class UtDynamicListInterface
{
    // Return the number of elements actually used / valid
    virtual int GetCount() = 0;

    // Return the number of elements allocated
    virtual int GetSize() = 0;

    // Reallocate to the given size
    virtual void Reize(unsigned int size) = 0;

    // Clear out (remove) all current entries, and re-initialize
    // to have the given size allocated.
    virtual void Clear(unsigned int size = 0) = 0;
};
