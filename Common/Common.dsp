# Microsoft Developer Studio Project File - Name="Common" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Common - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Common.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Common.mak" CFG="Common - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Common - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Common - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Common - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Common - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "..\glTrace" /I ".\Io" /I ".\Bases" /I ".\Ut" /I ".\Mg" /I ".\Geom" /I ".\Geometry" /D "__WIN32__" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Common - Win32 Release"
# Name "Common - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Geom\Geom.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomBezier.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomComment.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomList.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomOff.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomOoglParser.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomParent.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomQuad.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomSkel.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomVect.cpp
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomWrapped.cpp
# End Source File
# Begin Source File

SOURCE=.\Gv\GvAction.cpp
# End Source File
# Begin Source File

SOURCE=.\Gv\GvCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\Gv\GvMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\Gv\GvUniverse.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\HPoint3.cpp
# End Source File
# Begin Source File

SOURCE=.\Io\IoDataStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Io\IoOoglLexer.cpp
# End Source File
# Begin Source File

SOURCE=.\Io\IoOoglParseException.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\mallocp.c
# End Source File
# Begin Source File

SOURCE=.\Mg\MgAppearance.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgAppearanceIo.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgAppearanceStack.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgColor.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgContext.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgContextShade.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLight.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLighting.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLightingIo.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLightList.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgMaterial.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgMaterialIo.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgOpenGlContext.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgOpenGlContextDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgOpenGlContextMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgOpenGlContextShade.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\Mg\MgWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\Point3.cpp
# End Source File
# Begin Source File

SOURCE=.\Bases\RefObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Bases\StorageObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Geometry\Transform3.cpp
# End Source File
# Begin Source File

SOURCE=.\Bases\TypeObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\UtException.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\UtMemoryTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\UtString.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\UtUArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\UtVVec.cpp
# End Source File
# Begin Source File

SOURCE=.\Ut\vvecold.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Geom\Geom.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomBezier.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomComment.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\Geometry.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomHandle.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomList.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomMesh.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomOff.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomOoglParser.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomParent.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomQuad.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomSkel.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomVect.h
# End Source File
# Begin Source File

SOURCE=.\Geom\GeomWrapped.h
# End Source File
# Begin Source File

SOURCE=.\Gv\GvAction.h
# End Source File
# Begin Source File

SOURCE=.\Gv\GvCamera.h
# End Source File
# Begin Source File

SOURCE=.\Gv\GvMotion.h
# End Source File
# Begin Source File

SOURCE=.\Gv\GvUniverse.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\HPoint3.h
# End Source File
# Begin Source File

SOURCE=.\Io\IoDataStream.h
# End Source File
# Begin Source File

SOURCE=.\Io\IoOoglLexer.h
# End Source File
# Begin Source File

SOURCE=.\Io\IoOoglParseException.h
# End Source File
# Begin Source File

SOURCE=.\Io\IoOoglToken.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgAppearance.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgAppearanceStack.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgCamera.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgColor.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgContext.h
# End Source File
# Begin Source File

SOURCE=".\Mg\MgLight-new.h"
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLight.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLighting.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgLightList.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgMaterial.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgOpenGlContext.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgOpenGlContextShade.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgProperty.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgTexture.h
# End Source File
# Begin Source File

SOURCE=.\Mg\MgWindow.h
# End Source File
# Begin Source File

SOURCE=.\Mg\ooglutil.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\Point3.h
# End Source File
# Begin Source File

SOURCE=.\Bases\RefObject.h
# End Source File
# Begin Source File

SOURCE=.\Bases\StorageObject.h
# End Source File
# Begin Source File

SOURCE=.\Geometry\Transform3.h
# End Source File
# Begin Source File

SOURCE=.\Bases\TypeObject.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtDynamicListInterface.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtException.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtLList.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtLStack.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtLVec.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtMath.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtMemoryTracker.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtScalarArray.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtString.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtUArray.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtVArray.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtVRefPtrArray.h
# End Source File
# Begin Source File

SOURCE=.\Ut\UtVVec.h
# End Source File
# End Group
# End Target
# End Project
