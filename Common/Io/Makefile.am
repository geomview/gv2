INCLUDES = $(default_includes)
EXTRA_DIST = Headers IoOoglLexer.re
EXTRA_DIST_DIRS = old

noinst_LIBRARIES = libIo.a

libIo_a_SOURCES = IoDataStream.cpp IoDataStream.h                   \
		  IoOoglParseException.cpp IoOoglParseException.h   \
		  IoOoglLexer.h IoOoglLexer.cpp

IoOoglLexer.cpp: IoOoglLexer.re
	re2c IoOoglLexer.re > IoOoglLexer.cpp

IoOoglLexer.o: IoOoglLexer.cpp IoOoglLexer.h

.PHONY: _always

../Ut/libUt.a: _always
	cd ../Ut ; ${MAKE}

tlex: tlex.cpp libIo.a ../Ut/libUt.a
	${CXX} ${INCLUDES} -o tlex tlex.cpp libIo.a ../Ut/libUt.a

MAINTAINERCLEANFILES = IoOoglLexer.cpp

dist-hook:
	tar -c -f - ${EXTRA_DIST_DIRS} | (cd $(distdir) ; tar xf -)
