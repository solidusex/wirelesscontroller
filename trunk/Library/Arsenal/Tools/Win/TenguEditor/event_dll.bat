@echo off


:x86
set s_dir=..\..\..\binary\win32\DLLRelease
set d_dir=..\..\..\misc\TenguEditor_x86
call :copy_files %s_dir% %d_dir%


:X64
set s_dir=..\..\..\binary\X64\DLLRelease
set d_dir=..\..\..\misc\TenguEditor_X64
call :copy_files %s_dir% %d_dir%


:end_point
echo copy successfully

pause
exit


:copy_files

	set s_dir=%1
	set d_dir=%2

	if not exist %s_dir% goto :eof
	if not exist %d_dir% mkdir %d_dir%

	set s=%s_dir%\TenguEditor.exe
	set d=%d_dir%\TenguEditor.exe
	call :copy_file %s% %d%

	set s=%s_dir%\Arsenal.dll
	set d=%d_dir%\Arsenal.dll
	call :copy_file %s% %d%

	goto :eof





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

