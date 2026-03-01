@echo off
setlocal
cls

echo =========================
echo   Building Test Game
echo =========================

REM ensure DLL is beside exe
if not exist SageAura.dll (
    echo ERROR: SageAura.dll not found!
    pause
    exit /b
)

REM compile game
gcc -mconsole ^
    test\test.c ^
    -Iinclude ^
    -L. ^
    -lmingw32 ^
    -lSageAura ^
    -o game.exe

if %errorlevel% neq 0 (
    echo.
    echo ❌ BUILD FAILED
    pause
    exit /b
)

echo.
echo Build Success
echo Running...
echo.

game.exe

REM pause