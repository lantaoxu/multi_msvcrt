@echo off
set _CD_=%~dp0
for %%i in (80 90 100 110 70) do call :SETUP %%i
goto :EOF

:SETUP
setlocal

if "%1"=="70" goto :WDK
goto :SDK

:WDK
set _REG_EXE_=%SystemRoot%\SysWOW64\reg.exe
if not exist %_REG_EXE_% set _REG_EXE_=%SystemRoot%\System32\reg.exe
for /F "skip=2 usebackq tokens=3*" %%i in (`%_REG_EXE_% QUERY HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\KitSetup\configured-kits\{B4285279-1846-49B4-B8FD-B9EAF0FF17DA}\{68656B6B-555E-5459-5E5D-6363635E5F61} /v setup-install-location`) do set _WDK_=%%i
echo WDK="%_WDK_%"
call %_WDK_%\bin\setenv.bat %_WDK_% fre WXP no_oacr
cd /d %_CD_%
set LIB=%BASEDIR%\lib\crt\i386;%BASEDIR%\lib\wxp\i386;%LB_WSDK71_LIB%;%LIB%
set INCLUDE=%CRT_INC_PATH%;%SDK_INC_PATH%\crt\stl70;%DDK_INC_PATH%;%LB_WSDK71_INC%;%INCLUDE%;
set _CRTOBJ_=msvcrt_winxp.obj
goto :NEXT

:SDK
set _VSCOMNTOOLS_=VS%1COMNTOOLS
for /F "tokens=2 delims==" %%i in ('set %_VSCOMNTOOLS_%') do call "%%i\..\..\vc\vcvarsall.bat"
goto :NEXT

:NEXT
cl /? > test_%1.txt
cl /nologo /LD /MD /Fetest_%1.dll %_CRTOBJ_% test.c
cl /nologo /MD /Femain_%1.exe %_CRTOBJ_% main.c
endlocal
goto :EOF
