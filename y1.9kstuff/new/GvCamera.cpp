#include "GvCamera.h"

void GvCamera::Render()
{
    Geom * targetGeom = mTarget.Resolve();
    mpMgContext->WorldBegin();
    targetGeom->Draw(mpMgContext);
    mpMgContext->WorldEnd();
}



void GvCamera::Draw()
{
    // unimplemented
}



