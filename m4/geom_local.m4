dnl 
dnl GEOM_FIND_L_OPTION(LIB, FUNC, DIRS, OTHERLIBS)
dnl 
dnl Figure out what -L option might be needed to link with the library
dnl LIB. FUNC should be some function from that library.  DIRS should be a
dnl list of directories to try, one of them can be "" which means use no
dnl -L option.  OTHERLIBS, if present, can be a list of other libraries to
dnl link with.  Upon return:
dnl 
dnl    * If linking was successful, then the shell variable GEOM_L_OPTION
dnl      is set to the first -L option (including the "-L") that worked,
dnl      unless what worked was linking with no -L option, in which case
dnl      GEOM_L_OPTION is the empty string.
dnl 
dnl    * If linking didn't work with any of the dirs in DIRS, then
dnl      GEOM_L_OPTION is 0.
dnl 
AC_DEFUN(GEOM_FIND_L_OPTION,[
geom_lib=$1
geom_func=$2
geom_dirs='$3'
geom_otherlibs=$4
geom_saved_LIBS=$LIBS
AC_MSG_CHECKING([how to link with $geom_lib])
for geom_z in $geom_dirs ; do
  geom_z=`eval echo $geom_z`
  if test "$geom_z" != "" ; then
    geom_l_option="-L$geom_z"
  else
    geom_l_option=""
  fi
  LIBS="$geom_l_option $geom_lib $geom_otherlibs"
  AC_TRY_LINK_FUNC($geom_func,
	           [ GEOM_L_OPTION="$geom_l_option"
                     break ],
	           [ GEOM_L_OPTION="0" ]
	          )
done
LIBS=$geom_saved_LIBS
if test "$GEOM_L_OPTION" != "0" ; then
  AC_MSG_RESULT([$geom_l_option $geom_lib])
else
  AC_MSG_RESULT([not found])
fi
])
dnl 
dnl 
dnl 
dnl 
dnl 
dnl 
dnl 
dnl GEOM_FIND_I_OPTION(HEADER, DIRS)
dnl 
# Find out what -I argument we need in order to get the header file HEADER.
# DIRS should be a list of strings to use as -I arguments; the empty
# string corresponds to no -I option at all.  If we're successful, return
# with GEOM_I_OPTION set to the relevant -I option (including the "-I" itself).
# Note that this might be the empty string, which corresponds to no -I
# option at all.  If we don't find HEADER in any of the dirs listed in DIRS,
# return with GEOM_I_OPTION = "0".
AC_DEFUN(GEOM_FIND_I_OPTION,[
geom_header=$1
geom_dirs='$2'
geom_saved_CPPFLAGS=$CPPFLAGS
GEOM_I_OPTION="0"
AC_MSG_CHECKING([for $geom_header])
for geom_z in $geom_dirs ; do
  geom_z=`eval echo $geom_z`
  if test "$geom_z" != "" ; then
    CPPFLAGS="-I$geom_z"
  else
    CPPFLAGS=""
  fi
  AC_TRY_CPP([ #include <$geom_header> ],
	     [ GEOM_I_OPTION=$CPPFLAGS
               break ]
	     )
done
CPPFLAGS=$geom_saved_CPPFLAGS
if test "$GEOM_I_OPTION" = "0" ; then
  AC_MSG_RESULT([not found])
else
  if test "$GEOM_I_OPTION" != "" ; then
    AC_MSG_RESULT($GEOM_I_OPTION)
  else
    AC_MSG_RESULT([(found with no -I required)])
  fi
fi
])
dnl 
dnl 
dnl GEOM_FIND_LIBC_VERSION
dnl 
dnl Try to figure out which version of the libc library is installed on
dnl a linux system.  Return with GEOM_LIBC_VERSION set to:
dnl
dnl       5	for the old libc (libc.so.5)
dnl       6	for glibc (i.e., libc.so.6) (RedHat 5.0 and later)
dnl
dnl default to 6 if we can't figure it out.  Note that this test is
dnl not really correct; I think there is yet another version of libc
dnl that we probably need to distinguish, but I'm not sure and I don't
dnl know how to detect it, so this'll have to do for now.  If you know
dnl more about this, please email me at mbp@geomtech.com.
dnl
AC_DEFUN(GEOM_FIND_LIBC_VERSION,[
if test -e "/lib/libc.so.6" ; then
  GEOM_LIBC_VERSION="6"
else
  if test -e "/lib/libc.so.5" ; then
    GEOM_LIBC_VERSION="5"
  else
    GEOM_LIBC_VERSION="6"
  fi
fi
])
