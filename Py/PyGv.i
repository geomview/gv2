%module PyGv

%{
#include "UtException.h"
#include "Geom.h"
#include "GeomParent.h"
#include "GeomWrapped.h"
#include "GeomList.h"
#include "GeomOoglParser.h"
#include "Transform3.h"
#include "MgWindow.h"
#include "MgContext.h"
#include "MgOpenGlContext.h"
#include "MgCamera.h"
#include "GvCamera.h"
#include "GvUniverse.h"
#include "GvAction.h"
#include "GvMotion.h"
#include "GvRotateMotion.h"
#include "GvPath.h"
%}

%include "../Common/Geom/Geom.i"
%include "../Common/Geom/GeomParent.i"
%include "../Common/Geom/GeomWrapped.i"
%include "../Common/Geom/GeomList.i"
%include "../Common/Geom/GeomOoglParser.i"
%include "../Common/Geometry/Transform3.i"
%include "../Common/Mg/MgWindow.i"
%include "../Common/Mg/MgContext.i"
%include "../Common/Mg/MgOpenGlContext.i"
%include "../Common/Gv/GvCamera.i"
%include "../Common/Gv/GvUniverse.i"
%include "../Common/Gv/GvAction.i"
%include "../Common/Gv/GvMotion.i"
%include "../Common/Gv/GvRotateMotion.i"
%include "../Common/Gv/GvPath.i"

%except(python) {
  try {
    $function
  }
  catch (UtException e) {
    static char errmsg[256];
    sprintf(errmsg, "C Exception: %s", e.Message());
    PyErr_SetString(PyExc_RuntimeError, errmsg);
    return NULL;
  }
}
