#include "GvApp.h"
#include "GvUniverse.h"

GvApp::GvApp()
{
}

GvApp::~GvApp()
{
}


void GvApp::AddWorld(class GvUniverse *world)
{
    mWorlds.AppendItem(world);
}

void GvApp::RemoveWorld(class GvUniverse *world)
{
    mWorlds.RemoveItemByContents(world);
}


