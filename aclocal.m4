dnl aclocal.m4 generated automatically by aclocal 1.4

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.

# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AC_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package]))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

# Like AC_CONFIG_HEADER, but automatically create stamp file.

AC_DEFUN(AM_CONFIG_HEADER,
[AC_PREREQ([2.12])
AC_CONFIG_HEADER([$1])
dnl When config.status generates a header, we must update the stamp-h file.
dnl This file resides in the same directory as the config header
dnl that is generated.  We must strip everything past the first ":",
dnl and everything past the last "/".
AC_OUTPUT_COMMANDS(changequote(<<,>>)dnl
ifelse(patsubst(<<$1>>, <<[^ ]>>, <<>>), <<>>,
<<test -z "<<$>>CONFIG_HEADERS" || echo timestamp > patsubst(<<$1>>, <<^\([^:]*/\)?.*>>, <<\1>>)stamp-h<<>>dnl>>,
<<am_indx=1
for am_file in <<$1>>; do
  case " <<$>>CONFIG_HEADERS " in
  *" <<$>>am_file "*<<)>>
    echo timestamp > `echo <<$>>am_file | sed -e 's%:.*%%' -e 's%[^/]*$%%'`stamp-h$am_indx
    ;;
  esac
  am_indx=`expr "<<$>>am_indx" + 1`
done<<>>dnl>>)
changequote([,]))])

dnl Copyright (C) 1988 Eleftherios Gkioulekas <lf@amath.washington.edu>
dnl  
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2 of the License, or
dnl (at your option) any later version.
dnl 
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl 
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software 
dnl Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
dnl 
dnl As a special exception to the GNU General Public License, if you 
dnl distribute this file as part of a program that contains a configuration 
dnl script generated by Autoconf, you may include it under the same 
dnl distribution terms that you use for the rest of that program.
 
# ------------------------------------------------------------------------
# The following macro is useful for deep packages. It allows you to
# link all the header files *.h under a certain set of directories
# to be linked under an include directory from the toplevel.
# To use this feature in your configure.in call:
#   LF_LINK_HEADERS(dir1 dir2 dir3 .... , [directory] )
# where directory -> put links under include/directory
#       dir1 ...  -> the directories with header files we want to link
# WARNING: This macro will do  --> rm -rf include
# ------------------------------------------------------------------------

AC_DEFUN(LF_LINK_HEADERS,[
  # Find out how to link files if we haven't already
  if test -z "$LN_S"
  then
    AC_PROG_LN_S
  fi

  # Remove the include directory if we haven't done that yet
  if test -z "$lf_link_headers"
  then
    lf_link_headers="we are all Kosh"
    rm -rf "$srcdir/include"
  fi

  # Get the directory from the second argument which is optional
  ifelse([$2], ,  
         [lf_directory="$srcdir/include"] , 
         [lf_directory="$srcdir/include/$2"])
  ${srcdir}/mkinstalldirs "$lf_directory"

  # Link them
  lf_subdirs="`echo $1`"
  for lf_dir in $lf_subdirs
  do
    # Otherwise go ahead and link
    echo "linking headers from $srcdir/$lf_dir"
    # Check if the Headers file exists
    if test -f "$srcdir/$lf_dir/Headers"
    then
      for lf_file in `(cd $srcdir/$lf_dir; cat Headers)`
      do
        rm -f $lf_directory/$lf_file
        $LN_S "`pwd`/$srcdir/$lf_dir/$lf_file" "$lf_directory/$lf_file"
      done
    else
      echo "Warning: No Headers file for $srcdir/$lf_dir"
    fi
  done
])

# --------------------------------------------------------------------------
# The following macro is useful for deep packages. 
# To use it in your configure.in call
#   LF_SET_INCLUDES(dir1 dir2 dir3 ...)
# and in your Makefile.am set
#   @default-includes@
# Then this symbol will be substituted with
#   INCLUDES = -I$(prefix) -I$(top_builddir)/include/dir1 ...
# The prefix entry will be skipped if the prefix is equal to /usr/local
# or /usr
# --------------------------------------------------------------------------

AC_DEFUN(LF_SET_INCLUDES,[
  # See whether to put an entry for the prefix
  if test "$prefix" = "/usr" || test "$prefix" = "/usr/local"
  then
    default_includes=""
  else
    default_includes="-I\$(prefix) "
  fi

  # Get the directory list
  lf_dirs="`echo $1`"
  
  # Check whether we have a lib directory. If so put it in
  AC_MSG_CHECKING([whether sources have a lib directory])
  if test -d "`pwd`/$srcdir/lib"
  then
    AC_MSG_RESULT([yes])
    default_includes="$default_includes -I\$(top_srcdir)/lib"
  else
    AC_MSG_RESULT([no])
  fi

  # Now add in the directories. If the list is empty then just add include/
  # If the list is not empty then add the subdirectories.
  if test -z "$lf_dirs"
  then
    default_includes="$default_includes -I\$(top_srcdir)/include"
  else
    for lf_dir in $lf_dirs
    do
      default_includes="$default_includes -I\$(top_srcdir)/include/$lf_dir"
    done
  fi

  # And that's it
  AC_SUBST(default_includes)
])

