//-*-C++-*-

// GvUniverse.h

#ifndef GvUniverse_H
#define GvUniverse_H

#include "GeomWrapped.h"
#include "GeomList.h"
#include "UtVRefPtrArray.h"
#include "UtLList.h"

class GvUniverse : public RefObject {

    // A GvUniverse holds all the information associated with a "universe"
    // in Geomview.  A "universe" is a graph of geometric objects,
    // appearances, transformations, and cameras for viewing the
    // objects.
    //               GeomWrapped [A]
    //               *mpUniverseBase
    //                     |
    //                     |
    //                  GeomList
    //         ------ *mpUniverseList --------------------------- ...
    //         |                     |                |     
    //         |                     |                |     
    //    GeomWrapped [T]       GeomWrapped [T]  GeomWrapped [T]
    //     *mpWorldBase              |                |     
    //         |                     |                |     
    //         |                 GvCamera         GvCamera  
    //     GeomList
    //   *mpWorldList
    //      |    |
    //      |    |
    //    Geom Geom ...
    //
    // The letters in square brackets after the GeomWrappeds above
    // indicate the purpose of the GeomWrapped; [A] means it's used
    // to hold an appearance only (no transform), [T] means it's used
    // for just the transform (no appearance).
    //
    // The GeomWrapped at the base of the containing tree (mpUniverseBase)
    // contains the "base" appearance for the universe.
    //
private:

    GeomWrapped       * mpUniverseBase;    // see diagram above
    GeomList          * mpUniverseList;    // see diagram above
    GeomWrapped       * mpWorldBase;       // see diagram above
    GeomList          * mpWorldList;       // see diagram above

    // List of paths to all the cameras in this universe.  This includes
    // both free and bound cameras.
    UtVRefPtrArray<Geom*>    mCameras;

    // List of actions to apply with each clock tick.
  //UtLList<class GvAction *> mActions;

public:

    GvUniverse();
    ~GvUniverse();

    // Add a (reference to) a Geom to the WorldList
    void AddGeometry(Geom *geom);

    // Delete a (reference to) a Geom from the WorldList
    void DeleteGeometry(Geom *geom);

    // Add a free camera
    void AddFreeCamera(class GvCamera *camera);

    // Delete a free camera
    void DeleteFreeCamera(class GvCamera *camera);

    // (Bound cameras are not currently supported.)

    // Apply one tick of the clock; i.e. go through the list of
    // actions and apply each one.
  //void Tick();

    void SetBaseAppearance(class MgAppearance *ap);
    class MgAppearance *GetBaseAppearance();

    GeomWrapped *GetUniverseBase() { return mpUniverseBase;     }
    GeomList    *GetUniverseList() { return mpUniverseList;        }
    GeomWrapped *GetWorldBase()    { return mpWorldBase; }
    GeomList    *GetWorldList()    { return mpWorldList;    }

  void Dump();
private:
  void DumpTree(Geom *g, int indentLevel);
  char * IdentifyPointer(Geom *g);

};



#endif // GvUniverse_H
