//-*-C++-*-
#ifndef GVAPP_H
#define GVAPP_H

// GvApp.h

#include "UtLList.h"
//#include "GvUniverse.h"

class GvApp {
public:
    GvApp();
    ~GvApp();

    void AddWorld(class GvUniverse *world);
    void RemoveWorld(class GvUniverse *world);

protected:
    UtLList<class GvUniverse *> mWorlds;

};

// Ms-specific stuff:
// CMsGvApp : GvApp, CWinApp

#endif GVAPP_H
