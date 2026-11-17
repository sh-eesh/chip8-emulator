@echo off
setlocal
cd /d "%~dp0"

if not exist bin mkdir bin

echo Building CHIP-8 [RELEASE]...

g++ -O3 -DNDEBUG -mwindows -Iexternal/raylib/include -Iheader src/main.cpp -Lexternal/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o bin/Chip8.exe

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build successful!
echo Starting release build...

start "" "bin\Chip8.exe"
