# Microsoft Developer Studio Project File - Name="MsGv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MsGv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MsGv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MsGv.mak" CFG="MsGv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MsGv - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MsGv - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MsGv - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MsGv - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MsGv - Win32 Release"
# Name "MsGv - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\AppearanceDlg.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\ChildFrm.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\ColorButton.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\DebugDlg.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\EventHandler.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MainFrm.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorChoice.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorDialog.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorSlider.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorWindow.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGv.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGv.rc"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvDoc.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvOpenGlWindow.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvThread.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvView.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\OkMessageDlg.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\StdAfx.cpp"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\TreeDlg.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\AppearanceDlg.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\ChildFrm.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\ColorButton.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\DebugDlg.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\EventHandler.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MainFrm.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorChoice.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorDialog.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorSlider.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MgColorWindow.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGv.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvDoc.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvOpenGlWindow.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvThread.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\MsGvView.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\OkMessageDlg.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\Resource.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\StdAfx.h"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\TreeDlg.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\res\MsGv.ico"
# End Source File
# Begin Source File

SOURCE="\gv-2.0a1\y1.9kstuff\Ms\MsGv\res\MsGvDoc.ico"
# End Source File
# End Group
# End Target
# End Project
