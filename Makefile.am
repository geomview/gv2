SUBDIRS = m4 Common glTrace Py

EXTRA_DIST = \
    reconf gv2design.gif gv2design.sda gv2.dsw gv2.mdl

# Note: gv2design.sda is a StarOffice drawing; gv2design.gif is
# a gif snapshot of it

EXTRA_DIST_DIRS = y1.9kstuff

dist-hook:
	TMPFILE=/tmp/$$$$.tmp ; \
	find ${EXTRA_DIST_DIRS} -name Debug -print > $$TMPFILE ; \
	tar -c -X $$TMPFILE -f - ${EXTRA_DIST_DIRS} | \
	  (cd $(distdir) ; tar xf -) ; \
	rm $$TMPFILE

DISTCLEANFILES = *.opt *.ncb

distclean: distclean-local

distclean-local:
	@if test -d include; then \
		rm -rf include; \
	else :; fi

MAINTAINERCLEANFILES = stamp-h.in


cvs-clean: maintainer-clean
	-/bin/rm -f config.h.in configure
	-find . -name 'Makefile.in' -print | xargs /bin/rm
