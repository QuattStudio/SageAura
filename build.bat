@echo off
setlocal enabledelayedexpansion
cls

echo Building SageAura DLL (static GLFW)...

REM Collect all source files
set SRC=
for %%f in (src\*.c) do set SRC=!SRC! %%f

REM Compile dynamic library with STATIC GLFW linking
gcc -shared -DSA_BUILD -DGLFW_STATIC ^
    !SRC! external\src\glad.c ^
    -o SageAura.dll ^
    -Lexternal\libs ^
    -Iexternal\include ^
    -Iinclude ^
    -Isrc ^
    -lglfw3 -lopengl32 -lgdi32 -limm32 ^
    -Wl,--out-implib,libSageAura.a

if %errorlevel% neq 0 (
    echo.
    echo Build FAILED ❌
    pause
    exit /b
)

echo.
echo Build SUCCESS ✅
echo SageAura.dll created! (no glfw3.dll needed at runtime)
pause