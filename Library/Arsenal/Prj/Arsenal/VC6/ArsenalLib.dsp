# Microsoft Developer Studio Project File - Name="ArsenalLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ArsenalLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ArsenalLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ArsenalLib.mak" CFG="ArsenalLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ArsenalLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ArsenalLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ArsenalLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Binary\x86\Lib\Release\"
# PROP Intermediate_Dir "..\..\..\Temp\x86\LIBRelease\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_UNICODE" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ArsenalLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Binary\x86\Lib\Debug\"
# PROP Intermediate_Dir "..\..\..\Temp\x86\LIBDebug\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_UNICODE" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "ArsenalLib - Win32 Release"
# Name "ArsenalLib - Win32 Debug"
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\algo.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\buffer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\common.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\common.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\crtstr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\heap.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\memory.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\platform.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\random.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\strconv.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\string.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\strtable.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\textfile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\thread.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\thread_apple.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\thread_posix.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\thread_win.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Common\utilities.c
# End Source File
# End Group
# Begin Group "Lex"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\lex.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\lex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\match.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\match.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\rgx.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\rgx_compile.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\rgx_exec.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\rgx_misc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\rgx_node.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Lex\rgx_parser.c
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\grammar.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\grammar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lalr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lalr_build.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lalr_config.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lalr_config_aux.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lalr_state.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lr_action.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\lr_action.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\parser.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\parser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\parser_aux.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\parser_in.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\parser_in.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\report.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\symbol.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Parser\symbol.h
# End Source File
# End Group
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\grammar_codegen.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\grammar_collector.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\grammar_config.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\serializer.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\serializer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\tools.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tools\tools.h
# End Source File
# End Group
# Begin Group "Tengu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tengu.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tengu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tgu_parser_impl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tguparser.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tguparser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tgusyntree.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tguutility.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tguvm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Tengu\tguvm.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\Arsenal\Arsenal.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Arsenal\Arsenal.h
# End Source File
# End Target
# End Project
