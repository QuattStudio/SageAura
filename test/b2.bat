@echo off
setlocal enabledelayedexpansion
cls

echo Building SageAura DLL...

REM Collect all source files
set SRC=
for %%f in (src\*.c) do set SRC=!SRC! %%f

REM Compile dynamic library
gcc -shared -DSA_BUILD -o SageAura.dll ^
!SRC! external\src\glad.c ^
-Lexternal\libs ^
-Iexternal\include ^
-Iinclude ^
-Isrc ^
-lglfw3dll -lopengl32 -lgdi32 ^
-Wl,--out-implib,libSageAura.a

if %errorlevel% neq 0 (
    echo.
    echo Build FAILED ❌
    pause
    exit /b
)

echo.
echo Build SUCCESS ✅
echo SageAura.dll created!
pause