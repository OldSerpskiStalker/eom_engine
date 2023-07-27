# Microsoft Developer Studio Project File - Name="gpstress" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gpstress - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gpstress.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gpstress.mak" CFG="gpstress - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gpstress - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gpstress - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gpstress - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W4 /WX /GX /O2 /I "../../common" /I "../../" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "GSI_COMMON_DEBUG" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "gpstress - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gpstress___Win32_Debug"
# PROP BASE Intermediate_Dir "gpstress___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W4 /WX /Gm /GX /ZI /Od /I "../../common" /I "../../" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "GSI_COMMON_DEBUG" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gpstress - Win32 Release"
# Name "gpstress - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\gpstress.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "PresenceSDK"

# PROP Default_Filter "c,h"
# Begin Source File

SOURCE=..\gp.c
# End Source File
# Begin Source File

SOURCE=..\gp.h
# End Source File
# Begin Source File

SOURCE=..\gpi.c
# End Source File
# Begin Source File

SOURCE=..\gpi.h
# End Source File
# Begin Source File

SOURCE=..\gpiBuddy.c
# End Source File
# Begin Source File

SOURCE=..\gpiBuddy.h
# End Source File
# Begin Source File

SOURCE=..\gpiBuffer.c
# End Source File
# Begin Source File

SOURCE=..\gpiBuffer.h
# End Source File
# Begin Source File

SOURCE=..\gpiCallback.c
# End Source File
# Begin Source File

SOURCE=..\gpiCallback.h
# End Source File
# Begin Source File

SOURCE=..\gpiConnect.c
# End Source File
# Begin Source File

SOURCE=..\gpiConnect.h
# End Source File
# Begin Source File

SOURCE=..\gpiInfo.c
# End Source File
# Begin Source File

SOURCE=..\gpiInfo.h
# End Source File
# Begin Source File

SOURCE=..\gpiKeys.c
# End Source File
# Begin Source File

SOURCE=..\gpiKeys.h
# End Source File
# Begin Source File

SOURCE=..\gpiOperation.c
# End Source File
# Begin Source File

SOURCE=..\gpiOperation.h
# End Source File
# Begin Source File

SOURCE=..\gpiPeer.c
# End Source File
# Begin Source File

SOURCE=..\gpiPeer.h
# End Source File
# Begin Source File

SOURCE=..\gpiProfile.c
# End Source File
# Begin Source File

SOURCE=..\gpiProfile.h
# End Source File
# Begin Source File

SOURCE=..\gpiSearch.c
# End Source File
# Begin Source File

SOURCE=..\gpiSearch.h
# End Source File
# Begin Source File

SOURCE=..\gpiTransfer.c
# End Source File
# Begin Source File

SOURCE=..\gpiTransfer.h
# End Source File
# Begin Source File

SOURCE=..\gpiUnique.c
# End Source File
# Begin Source File

SOURCE=..\gpiUnique.h
# End Source File
# Begin Source File

SOURCE=..\gpiUtility.c
# End Source File
# Begin Source File

SOURCE=..\gpiUtility.h
# End Source File
# End Group
# Begin Group "GsCommon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\darray.c
# End Source File
# Begin Source File

SOURCE=..\..\darray.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsAssert.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsAssert.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsAvailable.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsAvailable.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsDebug.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsDebug.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsMemory.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsMemory.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatform.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatform.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatformSocket.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatformSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatformThread.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatformThread.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatformUtil.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsPlatformUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsStringUtil.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsStringUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\common\gsUdpEngine.c
# End Source File
# Begin Source File

SOURCE=..\..\common\gsUdpEngine.h
# End Source File
# Begin Source File

SOURCE=..\..\hashtable.c
# End Source File
# Begin Source File

SOURCE=..\..\hashtable.h
# End Source File
# Begin Source File

SOURCE=..\..\md5.h
# End Source File
# Begin Source File

SOURCE=..\..\md5c.c
# End Source File
# End Group
# Begin Group "TransportSDK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\gt2\gt2.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Auth.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Auth.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Buffer.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Callback.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Callback.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Connection.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Connection.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Encode.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Encode.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Filter.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Filter.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Main.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Main.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Message.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Message.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Socket.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Socket.h
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Utility.c
# End Source File
# Begin Source File

SOURCE=..\..\gt2\gt2Utility.h
# End Source File
# End Group
# End Target
# End Project
