PYTHONINC = /usr/include/python2.2
# PYTHONINC = /usr/local/include/python2.0
CFLAGS = -g

INCLUDES = -I.. $(default_includes) -I${PYTHONINC}

EXTRA_DIST = \
  gv2 gv2.py \
  PyGv.i \
  NOTES \
  CameraCanvas.py  EventHandler.py  PyGv.py \
  CameraFrame.py   GeomviewApp.py \
  PyGv_wrap.cpp dodec.off person.oogl data.oogl \
  loadtest.cpp TestTimer.py \
  dodec.off hdodec.off .gdbinit \
  nmakefile setenv.bat Py.dsp \
  pystructure motion.tex

COMMONLIBS = \
    ../Common/Gv/libGv.a	     \
    ../Common/Geom/libGeom.a	     \
    ../Common/Mg/libMg.a	     \
    ../Common/Bases/libBases.a	     \
    ../Common/Geometry/libGeometry.a \
    ../Common/Io/libIo.a	     \
    ../Common/Ut/libUt.a


LDADD = ${COMMONLIBS} ${GLTRACE} -lGL -lGLU -L/usr/X11R6/lib -lXmu

# Above line formerly had -ltk -ltcl, but it seems to be
# unnecessary.  Good.

all: PyGvcmodule.so loadtest

PyGv_wrap.o: PyGv_wrap.cpp
	${CXX} ${CFLAGS} -c ${INCLUDES} -o PyGv_wrap.o PyGv_wrap.cpp

PyGvcmodule.so: PyGv_wrap.o MAKE_COMMONLIBS
	${CXX} ${CFLAGS} -shared -o PyGvcmodule.so PyGv_wrap.o ${LDADD}

loadtest.o: loadtest.cpp
	${CXX} ${CFLAGS} ${INCLUDES} -c loadtest.cpp

loadtest: loadtest.o MAKE_COMMONLIBS
	${CXX} ${CFLAGS} -o loadtest loadtest.o ${LDADD}

doit: doit.cpp ../Common/Ut/libUt.a
	${CXX} ${CFLAGS} -o doit doit.cpp ../Common/Ut/libUt.a

MAKE_COMMONLIBS: _always
	cd ../Common; ${MAKE}

COMMONIFILES =                      \
    ../Common/Geom/Geom.i	    \
    ../Common/Geom/GeomOoglParser.i \
    ../Common/Geom/GeomParent.i	    \
    ../Common/Geom/GeomWrapped.i    \
    ../Common/Geom/GeomList.i       \
    ../Common/Geometry/Transform3.i \
    ../Common/Gv/GvAction.i	    \
    ../Common/Gv/GvCamera.i	    \
    ../Common/Gv/GvMotion.i	    \
    ../Common/Gv/GvRotateMotion.i   \
    ../Common/Gv/GvTranslateMotion.i \
    ../Common/Gv/GvUniverse.i	    \
    ../Common/Gv/GvPath.i	    \
    ../Common/Mg/MgContext.i	    \
    ../Common/Mg/MgOpenGlContext.i  \
    ../Common/Mg/MgWindow.i

PyGv.py PyGv_wrap.cpp: PyGv.i ${COMMONIFILES}
	swig -o PyGv_wrap.cpp -python -c++ -shadow PyGv.i

CLEANFILES = PyGvmodule.so \
	     *.pyc \
	     *.o *.obj \
	     core

DISTCLEANFILES = *.so loadtest PyGvc.*

MAINTAINERCLEANFILES = PyGv_wrap.cpp PyGv.py PyGv_wrap.cpp


.PHONY: _always MAKE_COMMONLIBS
