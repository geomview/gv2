#include "GvWorld.h"

#inlcude "GeomWrapped.h"
#inlcude "GeomList.h"

GvWorld::GvWorld()
{
    mpBaseWrapped = new GeomWrapped();
    mpBaseList = new GeomList();
    mpGeometryWrapped = new GeomWrapped();
    mpGeometryList = new GeomList();

    mpBaseWrapped->SetChild(mpBaseList);
    mpBaseList->AddChild(mpGeometryWrapped);
    mpGeometryWrapped->SetChild(mpGeometryList);

    mGeometry.SetRoot(mpBaseWrapped);
    mGeometry.FindPathTo(mpGeometryList);

    mBase.SetRoot(mpBaseWrapped);
    mBase.FindPathTo(mpBaseList);
}

GvWorld::~GvWorld()
{
    ::DeleteRef(mpBaseWrapped);
    ::DeleteRef(mpBaseList);
    ::DeleteRef(mpGeometryWrapped);
    ::DeleteRef(mpGeometryList);
}

void GvWorld::AddAction(GvAction *action)
{
    //
    // Delete like actions
    //
    UtLListIter<GvAction *> it(mActions);
    while (it)
    {
        GvAction *a = it();
        if (a->IsLike(action) && a->IsFragile())
        {
            it.RemoveCurrentItem(); // this does an implicit ++it
        }
        else
        {
            ++it;
        }
    }

    //
    // Add this action to the list
    //
    mActions.AppendItem(action);
}

void GvWorld::ClearAllActions()
{
    mActions.Clear();
}


void GvWorld::AddGeometry(Geom *geom)
{
    mGeometry.AddChild(geom);
}

void GvWorld::DeleteGeometry(Geom *geom)
{
    mGeometry.RemoveChild(geom);
}

// Idea: consider making 
// 
//     GeomList::AddChild
//     GeomList::RemoveChild
//     GeomWrapped::SetChild
// 
// & etc private, so they can't be called outside the class, and have
// GvPath be a friend class of these, so it can actually call them.
// Then clients will be forced to only do these operations in terms
// of GvPaths, which is possibly what we want.


void AddFreeCamera(GvCamera *camera)
{
    GeomWrapped wrap = new GeomWrapped();
    wrap.SetChild(camera);
    mBase.AddChild(wrap);
    ::DeleteRef(wrap);
    GvPath path;
    path.SetRoot(mpBaseWrapped);
    path.FindPathTo(camera);
    mCameras.AppendItem(path);
}


void DeleteFreeCamera(GvCamera *camera)
{
    GvPath path;
    UtBool found = UtFALSE;

    //
    // First find the path to this camera in our list of paths
    // (mCameras), and remove it from the list, but keep a copy of it
    // in local variable "path".
    //

    UtLListIter<GvPath> it(mCameras);
    while (it)
    {
        GvPath path = it();
        if (path.Resolve() == ((Geom*)camera))
        {
            found = UtTRUE;
            it.RemoveCurrent();
            break;
        }
        ++it;
    }
    if (!found) return;

    //
    // Now use this path to remove the wrapped camera from our base list.
    //

    path.RemoveLastIndex();
    // path now goes to the GeomWrapped above the GvCamera.

    int index = path.GetLastIndex();
    // This is the index of that GeomWrapped in the base list.

    path.RemoveLastIndex();            
    // path now goes to the base list; it should now be the same as
    // mBase, so if we wanted to do some sanity checking here, we could
    // do something like ASSERT( path == mBase ), assuming we had an
    // overloaded operator== for GvPath.

    path.RemoveChild(index);
    // This removes the wrapped camera from the base list.  It also
    // takes care of all the necessary ::DeleteRef()s, so we don't
    // have to do any of that here.
}


void Tick()
{
    UtLListIter<GvAction *> it(mActions);
    while (it)
    {
        GvAction *a = it();
        a->Execute();
        if (a->IsFinished())
        {
            it.RemoveCurrentItem(); // this does an implicit ++it
        }
        else
        {
            ++it;
        }
    }
}

void SetBaseAppearance(MgAppearance *ap)
{
    mpBaseWrapped->SetAppearance(ap);
}

MgAppearance *GetBaseAppearance()
{
    return mpBaseWrapped->GetAppearance();
}


