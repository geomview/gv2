#include "GvUniverse.h"

#include "GeomWrapped.h"
#include "GeomList.h"
#include "GvCamera.h"

GvUniverse::GvUniverse()
{
    mpUniverseBase = new GeomWrapped();
    mpUniverseList = new GeomList();
    mpWorldBase = new GeomWrapped();
    mpWorldList = new GeomList();

    mpUniverseBase->SetName("UniverseBase");
    mpUniverseList->SetName("UniverseList");
    mpWorldBase->SetName("WorldBase");
    mpWorldList->SetName("WorldList");

    mpUniverseBase->AddChild(mpUniverseList);
    mpUniverseList->AddChild(mpWorldBase);
    mpWorldBase->AddChild(mpWorldList);
}

GvUniverse::~GvUniverse()
{
    ::DeleteRef(mpUniverseBase);
    ::DeleteRef(mpUniverseList);
    ::DeleteRef(mpWorldBase);
    ::DeleteRef(mpWorldList);
}

void GvUniverse::AddGeometry(Geom *geom)
{
  GeomWrapped *w = new GeomWrapped(geom);
  mpWorldList->AddChild(w);
  ::DeleteRef(w);
}

void GvUniverse::DeleteGeometry(Geom *geom)
{
    mpWorldList->RemoveChild(geom);
}

void GvUniverse::AddFreeCamera(GvCamera *camera)
{
    GeomWrapped *wrap = new GeomWrapped();
    wrap->AddChild(camera);
    mpUniverseList->AddChild(wrap);
    ::DeleteRef(wrap);
    mCameras.AppendItem(camera);
}


void GvUniverse::DeleteFreeCamera(GvCamera *camera)
{
    //
    // First find the index of this camera in our list of Cameras.
    //
    int index;
    int count = mCameras.GetCount();
    UtBool found = UtFALSE;
    for (index=0; !found && index<count; ++index) {
        if (mCameras[index] == camera);
        found = UtTRUE;
    }
    if (!found) return;

    //
    // Remove it from the list
    //
    mCameras.RemoveItem(index);

    //
    // And remove it from the containing tree.  If it's contained
    // in a GeomWrapped, remove that GeomWrapped from the tree
    // too.
    //
    GeomParent *parent = camera->GetParent();
    parent->RemoveChild(camera);
    if (parent->IsInstanceOf(TYPE_INFO(GeomWrapped)))
    {
        GeomWrapped *wrap = (GeomWrapped*)parent;
        parent = wrap->GetParent();
        parent->RemoveChild(wrap);
    }
}

void GvUniverse::SetBaseAppearance(MgAppearance *ap)
{
    mpUniverseBase->SetAppearance(ap);
}

MgAppearance *GvUniverse::GetBaseAppearance()
{
    return mpUniverseBase->GetAppearance();
}


char * GvUniverse::IdentifyPointer(Geom *g)
{
  if (g == mpUniverseBase) { return "mpUniverseBase"; }
  if (g == mpUniverseList) { return "mpUniverseList"; }
  if (g == mpWorldBase) { return "mpWorldBase"; }
  if (g == mpWorldList) { return "mpWorldList"; }
  return NULL;
}

void GvUniverse::DumpTree(Geom *g, int indentLevel)
{
  char *id = IdentifyPointer(g);
  printf("%*s0x%8x", indentLevel, " ", g);
  if (id!=NULL) { printf(" [%s]", id); }
  printf("\n");

  if (g->IsInstanceOf(TYPE_INFO(GeomParent))) {
    GeomParent *p = (GeomParent*)g;
    int nchildren = p->GetChildCount();
    for (int i=0; i<nchildren; ++i) {
      DumpTree(p->GetChild(i), indentLevel+2);
    }
  }

}

void GvUniverse::Dump()
{
  printf("mpUniverseBase     = 0x%x\n", mpUniverseBase);
  printf("mpUniverseList        = 0x%x\n", mpUniverseList);
  printf("mpWorldBase = 0x%x\n", mpWorldBase);
  printf("mpWorldList    = 0x%x\n", mpWorldList);

  DumpTree(mpUniverseBase, 2);
}
