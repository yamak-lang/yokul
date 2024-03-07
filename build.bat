@ECHO off

SETLOCAL ENABLEEXTENSIONS
IF ERRORLEVEL 1 (
    ECHO "ERROR: Unable to enable extensions"
    EXIT
)

SETLOCAL EnableDelayedExpansion

SET ProjectRoot=%~dp0

SET DirBuild=%ProjectRoot%out
SET DirData=%ProjectRoot%dat
SET DirDependencies=%ProjectRoot%dep
SET DirConfiguration=%ProjectRoot%etc
SET DirSource=%ProjectRoot%src

SET BuildDirectoryEXE=%DirBuild%\win32\x64\bin
IF NOT EXIST %BuildDirectoryEXE% MKDIR %BuildDirectoryEXE%

SET BuildDirectoryDLL=%DirBuild%\win32\x64\lib
IF NOT EXIST %BuildDirectoryDLL% MKDIR %BuildDirectoryDLL%

SET /p VersionNumberOld=<%ProjectRoot%\version
SET /a VersionNumber=%VersionNumberOld% + 1
ECHO %VersionNumber%> %ProjectRoot%\version

SET Source=%DirSource%\main.c

SET TargetEXE=yokul.exe
SET TargetPathEXE=%BuildDirectoryEXE%\%TargetEXE%

SET TargetDLL=yokul.dll
SET TargetPathDLL=%BuildDirectoryDLL%\%TargetDLL%

WHERE clang >nul 2>&1
IF %ERRORLEVEL% EQU 0 (
    ECHO Syntax Check (Clang^) ===============================================

    PUSHD %BuildDirectoryDLL%
    ECHO Entering directory `!CD!'

    clang ^
          ^
          -g3 -gcodeview -O0 -fno-strict-aliasing -fwrapv -msse2 ^
          -iquote %DirSource% -I%DirDependencies%\inc ^
          ^
          --std=c17 -DUNICODE -D_UNICODE -DBUILD_INTERNAL -DBUILD_SLOW -DBUILD_DLL ^
          ^
          -Weverything -Wpedantic -pedantic-errors -Werror ^
          -Wno-extra-semi-stmt -Wno-declaration-after-statement -Wno-unused-function -Wno-unsafe-buffer-usage ^
          ^
          %Source% ^
          ^
          -shared -o %TargetPathDLL%.syntax_checking.dll -Wl,/debug,/pdb:%TargetPathDLL%.syntax_checking.pdb ^
          -Xlinker /subsystem:console ^
          -llibvcruntime -lshell32 ^
          -L%DirDependencies%\lib\gmp\win32\x64  -lgmp  ^
          -L%DirDependencies%\lib\mpc\win32\x64  -lmpc  ^
          -L%DirDependencies%\lib\mpfr\win32\x64 -lmpfr ^
          -L%DirDependencies%\lib\unicode\win32\x64  -licudt -licuin -licuio -licuuc

    DEL *syntax_checking.*

    PUSHD %BuildDirectoryEXE%
    ECHO Entering directory `!CD!'

    clang ^
          ^
          -g3 -gcodeview -O0 -fno-strict-aliasing -fwrapv -msse2 ^
          -iquote %DirSource% -I%DirDependencies%\inc ^
          ^
          --std=c17 -DUNICODE -D_UNICODE -DBUILD_INTERNAL -DBUILD_SLOW ^
          ^
          -Weverything -Wpedantic -pedantic-errors -Werror ^
          -Wno-extra-semi-stmt -Wno-declaration-after-statement -Wno-unused-function -Wno-unsafe-buffer-usage ^
          ^
          %Source% ^
          ^
          -o %TargetPathEXE%.syntax_checking.exe -Wl,/debug,/pdb:%TargetPathEXE%.syntax_checking.pdb ^
          -Xlinker /subsystem:console ^
          -llibvcruntime -lshell32 -lkernel32 ^
          -L%DirDependencies%\lib\gmp\win32\x64  -lgmp  ^
          -L%DirDependencies%\lib\mpc\win32\x64  -lmpc  ^
          -L%DirDependencies%\lib\mpfr\win32\x64 -lmpfr ^
          -L%DirDependencies%\lib\unicode\win32\x64  -licudt -licuin -licuio -licuuc

    DEL *syntax_checking.*
)

ECHO Compile (MSVC) =====================================================

SET CompilerExists=yes
WHERE cl >nul 2>&1
IF %ERRORLEVEL% NEQ 0 SET CompilerExists=no

IF %CompilerExists%==yes (
    PUSHD %BuildDirectoryDLL%
    ECHO Entering directory `!CD!'

    cl ^
       ^
       %Source% ^
       ^
       /nologo /Zi /FC /Oi /Od /I %DirSource% /I %DirDependencies%\inc ^
       /source-charset:utf-8 /execution-charset:utf-8 ^
       /GS- ^
       ^
       /std:c17 /DUNICODE /D_UNICODE /D_USRDLL /D_WINDLL /DBUILD_INTERNAL /DBUILD_SLOW /DBUILD_DLL ^
       ^
       /W4 /WX ^
       ^
       /Fe%TargetPathDLL% ^
       /link /DLL /fixed /incremental:no /opt:icf /opt:ref ^
       /SUBSYSTEM:CONSOLE ^
       libvcruntime.lib Shell32.lib ^
       /LIBPATH:%DirDependencies%\lib\gmp\win32\x64  gmp.lib  ^
       /LIBPATH:%DirDependencies%\lib\mpc\win32\x64  mpc.lib  ^
       /LIBPATH:%DirDependencies%\lib\mpfr\win32\x64 mpfr.lib ^
       /LIBPATH:%DirDependencies%\lib\unicode\win32\x64 icudt.lib icuin.lib icuio.lib icuuc.lib


    PUSHD %BuildDirectoryEXE%
    ECHO Entering directory `!CD!'

    cl ^
       ^
       %Source% ^
       ^
       /nologo /Zi /FC /Oi /Od /I %DirSource% /I %DirDependencies%\inc ^
       /source-charset:utf-8 /execution-charset:utf-8 ^
       /GS- ^
       ^
       /std:c17 /DUNICODE /D_UNICODE /DBUILD_INTERNAL /DBUILD_SLOW ^
       ^
       /W4 /WX ^
       ^
       /Fe%TargetPathEXE% ^
       /link /fixed /incremental:no /opt:icf /opt:ref ^
       /SUBSYSTEM:CONSOLE ^
       libvcruntime.lib Shell32.lib Kernel32.lib ^
       /LIBPATH:%DirDependencies%\lib\gmp\win32\x64  gmp.lib  ^
       /LIBPATH:%DirDependencies%\lib\mpc\win32\x64  mpc.lib  ^
       /LIBPATH:%DirDependencies%\lib\mpfr\win32\x64 mpfr.lib ^
       /LIBPATH:%DirDependencies%\lib\unicode\win32\x64 icudt.lib icuin.lib icuio.lib icuuc.lib
)

IF %CompilerExists%==no (
    ECHO MSVC installation not found
)

POPD
