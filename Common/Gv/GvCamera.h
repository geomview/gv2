//-*-C++-*-
#ifndef GVCAMERA_H
#define GVCAMERA_H

// GvCamera.h

#include "Geom.h"
#include "MgCamera.h"
#include "UtMath.h"

class GvCamera : public Geom {

    TYPE_DECLARE_TYPEINFO(GvCamera);

public:

    GvCamera();
    ~GvCamera();

    // Redraw the window associated with this camera.
    void Render();

    // Draw the camera itself, if camera-drawing is turned on.
    void Draw(class MgContext *mg);

    // Set/Get the MgContext:
    void SetMgContext(class MgContext *mg);
    class MgContext *GetMgContext()        { return mpMgContext; }

    // Get/Set the target tree
    void SetTarget(Geom *geom)             { mpTarget = ::NewRef(geom); }
    Geom *GetTarget()                      { return mpTarget; }

    MgCamera *GetMgCamera()                { return &mMgCamera; }


    // MgCamera-specific functions.  We could eliminate the need to put
    // all these here by having GvCamera inherit from MgCamera, but
    // that would open up the entire MgCamera interface to GvCamera
    // clients, which I'm not sure is a good idea.  The MgCamera class
    // interface is not very well thought out (it's bascially a
    // bunch of accessor/manipulator methods for dealing with the old
    // C-style mgcamera struct), so I think for now at least it's best
    // to only provide access to the ones that GvCamera clients really
    // need.  Actually, I'm not really sure we need all the ones below,
    // but at least they seem likely, since they're related to setting
    // up the camera, and reading its values (which the user interface
    // needs to be able to do).

    typedef enum Projection {
        ORTHOGONAL = MgCamera::ORTHOGONAL,
        PERSPECTIVE = MgCamera::PERSPECTIVE,
    } Projection;

    void SetProjection(Projection p)     { mMgCamera.SetProjection((MgCamera::Projection)p);        }
    Projection GetProjection()           { return (Projection)(mMgCamera.GetProjection());  }
    void   SetW2C(Transform3 *T)         { mMgCamera.SetW2C(T);               }
    void   GetW2C(Transform3 *T)         { mMgCamera.GetW2C(T);               }
    void   SetFOV(double degrees)        { mMgCamera.SetFOV(degrees);         }
    double GetFOV()                      { return mMgCamera.GetFOV();         }
    void   SetHalfYField(double val)     { mMgCamera.SetHalfYField(val);      }
    double GetHalfYField()               { return mMgCamera.GetHalfYField();  }
    void   SetHalfField(double val)      { mMgCamera.SetHalfField(val);       }
    double GetHalfField()                { return mMgCamera.GetHalfField();   }
    void   SetAspectRatio(double aspect) { mMgCamera.SetAspectRatio(aspect);  }
    double GetAspectRatio()              { return mMgCamera.GetAspectRatio(); }
    void   SetFocus(double f)            { mMgCamera.SetFocus(f);             }
    double GetFocus()                    { return mMgCamera.GetFocus();       }
    void   SetNearClip(double z)         { mMgCamera.SetNearClip(z);          }
    double GetNearClip()                 { return mMgCamera.GetNearClip();    }
    void   SetFarClip(double z)          { mMgCamera.SetFarClip(z);           }
    double GetFarClip()                  { return mMgCamera.GetFarClip();     }
    void  Reset(void)                    { mMgCamera.Reset();                 }

private:
    // The MgCamera associated with this GvCamera:
    MgCamera      mMgCamera;

    // The MgContext associated with this GvCamera. Clients of
    // GvCamera must set this; the usual situation is that they'd
    // set it to point to an instance of a graphics-specific subclass
    // of MgContext (such as MgOpenGlContext).
    class MgContext   * mpMgContext;

    // The camera's "target tree", i.e. the geometry tree
    // that this camera sees.
    Geom        * mpTarget;

};


    // Determine whether or not an action does anything which
    // necessitates redrawing this camera's window.
    //
    // NOTE: not sure if this best belongs here, or in the action code
    // itself; it's conceivable that advanced tests for whether the
    // action changes something in this camera's window might best be
    // done while the action is actually being executed, especially if
    // it involves things like visibility testing, bounding boxes,
    // etc.  But the current implementation just does a superficial
    // check for whether the action moves anything in the camera's
    // target tree, so we put it here for now.
//    UtBool      ForcesRedraw(class GvAction *action);

#endif // GVCAMERA_H
