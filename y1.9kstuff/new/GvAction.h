//-*-C++-*-

// GvAction.h

class GvAction {

private:
    // Path to the Geom (tree) that this action affects.
    GvPath      mTarget;

public:
    // Execute the action.
    void        Execute();

    // After Execute()-ing this action, call IsFinished() to see
    // whether the action is finished or not.  Some actions are
    // one-time things, some stick around indefinitely and apply
    // repeatedly, and others may stick around for a particular period
    // of time, or until other conditions are met.  Anyway, the point
    // is that this is how the action tells you whether it's done doing
    // its thing.
    virtual UtBool      IsFinished();

    // IsFragile() says whether the action should be eliminated by new
    // actions which are similar to it.  For example, an inertial
    // rotation gets wiped out by another rotation, so the inertial
    // rotation's IsFragile would return UtTRUE.  One-time actions are
    // not fragile.  Also, if we implement things like actions that
    // work for a certain period of time or rotate through a fixed
    // angle, etc, they would probably not be fragile.
    virtual UtBool      IsFragile();

    // Says whether this motion is "like" another one.  Does
    // not look at whether either is inertial --- just checks
    // for motion type & target relationships.
    UtBool      IsLike(GvAction *action);

};
