//-*-C++-*-

// GvWorld.h

class GvWorld {

    // A GvWorld holds all the information associated with a "world"
    // in Geomview.  This includes the world's geometry tree, all the
    // cameras which are looking at the world, and any actions which
    // apply to the world (or its cameras).  The geometry and cameras
    // are stored in a structure called the "containing tree":
    //
    //               GeomWrapped [A]
    //               *mpBaseWrapped
    //                     |
    //                     |
    //                   GeomList
    //          ------ *mpBaseList --------------------------- ...
    //          |                     |                |     
    //          |                     |                |     
    //     GeomWrapped [T]       GeomWrapped [T]  GeomWrapped [T]
    //   *mpGeometryWrapped           |                |     
    //          |                     |                |     
    //          |                 GvCamera         GvCamera  
    //      GeomList
    //   *mpGeometryList
    //     |    |
    //     |    |
    //    Geom Geom ...
    //
    // The letters in square brackets after the GeomWrappeds above
    // indicate the purpose of the GeomWrapped; [A] means it's used
    // to hold an appearance only (no transform), [T] means it's used
    // for just the transform (no appearance).
    //
    // The GeomWrapped at the base of the containing three (mpBaseWrapped)
    // contains the "base" appearance for the world.
    //
    // The mpBaseList list contains one child (mpGeometryWrapped) which
    // represents all the geometry in the world (all encased in a
    // GeomWrapped), plus one child for each "free" camera.  (A free
    // camera is one that is not specificlly attached to a piece of
    // geometry in the world.  A camera that is attached to a piece of
    // geometry is called a "bound" camera.)  Each free camera is
    // wrapped in a GeomWrapped which holds a transform that gives
    // that camera's position in the world.

private:

    GeomWrapped       * mpBaseWrapped;           // see diagram above
    GeomList          * mpBaseList;              // see diagram above
    GeomWrapped       * mpGeometryWrapped;       // see diagram above
    GeomList          * mpGeometryList;          // see diagram above

    // Path from mpBaseWrapped to mpBaseList:
    GvPath              mBase;

    // Path from mpBaseWrapped to mpGeometryList:
    GvPath              mGeometry;

    // List of paths to all the cameras in this world.  This includes
    // both free and bound cameras.
    UtLList<GvPath>     mCameras;

    // List of actions to apply with each clock tick.
    UtLList<GvAction *> mActions;

public:

    GvWorld();
    ~GvWorld();

    // Add an action to this world's action list.  Deletes any
    // inertial "like" motions from the list.
    void AddAction(GvAction *action);

    // Remove all actions.
    void ClearAllActions();

    // Add a (reference to) a Geom to the world's GeometryList.
    void AddGeometry(Geom *geom);

    // Delete a (reference to) a Geom from the world's GeometryList.
    void DeleteGeometry(Geom *geom);

    // Add a free camera
    void AddFreeCamera(GvCamera *camera);

    // Delete a free camera
    void DeleteFreeCamera(GvCamera *camera);

    // (Bound cameras are not currently supported.)

    // Apply one tick of the clock; i.e. go through the list of
    // actions and apply each one.
    void Tick();

    void SetBaseAppearance(MgAppearance *ap);
    MgAppearance *GetBaseAppearance();

    GeomList *GetBaseList() { return mpBaseList; }

};


// CMsGvDoc : GvWorld, CDocument
//    contains Ms-specific stuff

