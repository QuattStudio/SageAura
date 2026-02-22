@echo off
setlocal enabledelayedexpansion
cls

echo Building...

set SRC=
for %%f in (src\*.c) do set SRC=!SRC! %%f

gcc !SRC! external\src\glad.c ^
-Lexternal\libs ^
-Iexternal\include ^
-Iinclude ^
-Isrc ^
-lglfw3dll -lopengl32 -lgdi32 ^
-o game.exe

if %errorlevel% neq 0 (
    echo.
    echo Build FAILED ❌
    pause
    exit /b
)

echo.
echo Build SUCCESS ✅
echo Running...
echo.

game.exe















