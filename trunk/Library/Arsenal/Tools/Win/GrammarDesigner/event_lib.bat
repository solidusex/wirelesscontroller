@echo off


:x86
set s_path=..\..\..\binary\Win32\LibRelease\GrammarDesigner.exe
set d_path=..\..\..\misc\GrammarDesigner_x86.exe
call :copy_file %s_path% %d_path%


:X64
set s_path=..\..\..\binary\X64\LibRelease\GrammarDesigner.exe
set d_path=..\..\..\misc\GrammarDesigner_X64.exe
call :copy_file %s_path% %d_path%


:end_point
echo copy successfully

pause
exit




:copy_file
	set s=%1
	set d=%2
	if not exist %s% goto :not_existed
	if exist %d% del %d% /q/f/s/a
	copy %s% %d%
	goto :eof
	
	:not_existed
	echo File %s% not existed!
	goto :eof


:clear_dir
	set path=%1\*.*
	if exist %path% (del  %path% /q/f/s/a)
	goto :eof

