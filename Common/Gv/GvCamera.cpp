#include "GvCamera.h"

TYPE_IMPLEMENT_TYPEINFO1(GvCamera, Geom);

GvCamera::GvCamera()
{
    mpTarget = NULL;
}

GvCamera::~GvCamera()
{
    if (mpTarget) ::DeleteRef(mpTarget);
}

void GvCamera::SetMgContext(class MgContext *mg)
{
    mpMgContext = mg;
    mpMgContext->SetCamera(&mMgCamera);
}


void GvCamera::Render()
{
  if (!mpMgContext || !mpTarget) { return; }
  mpMgContext->WorldBegin();
  mpTarget->Draw(mpMgContext);
  mpMgContext->WorldEnd();
}



void GvCamera::Draw(MgContext *mg)
{
    // unimplemented
}
