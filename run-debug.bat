@echo off
setlocal
cd /d "%~dp0"

if not exist bin mkdir bin

echo Building CHIP-8 [DEBUG]...

g++ -g -O0 -D_DEBUG -Iexternal/raylib/include -Iheader src/*.cpp -Lexternal/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o bin/Chip8-Debug.exe

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build successful!
echo Starting debug build...

bin\Chip8-Debug.exe

pause
