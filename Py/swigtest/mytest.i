%module mytest

%{
#include "MyTest.h"
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

%include "MyTest.i"
