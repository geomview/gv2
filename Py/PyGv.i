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
#include "GvTranslateMotion.h"
#include "GvScaleMotion.h"
#include "GvPath.h"
%}

%typemap(python,argout) double *OutValue {
  PyObject *o;
  o = PyFloat_FromDouble(*$source);
  if ((!$target) || ($target == Py_None)) {
    $target = 0;
  } else {
    if (!PyList_Check($target)) {
	PyObject *o2 = $target;
	$target = PyList_New(0);
	PyList_Append($target,o2);
	Py_XDECREF(o2);
    }
    PyList_Append($target, o);
    Py_XDECREF(o);
  }
}

%typemap(python,ignore) double *OutValue(double temp) {
  $target = &temp;
}

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
%include "../Common/Gv/GvTranslateMotion.i"
%include "../Common/Gv/GvScaleMotion.i"
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
